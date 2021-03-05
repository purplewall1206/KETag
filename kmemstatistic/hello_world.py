from __future__ import print_function
from bcc import BPF

# BPF(text='int kprobe__sys_clone(void *ctx) { bpf_trace_printk("Hello, World!\\n"); return 0; }').trace_print()

# # define BPF program
# prog = """
# int hello(void *ctx) {
#     bpf_trace_printk("Hello, World!\\n");
#     return 0;
# }
# """

# # load BPF program
# b = BPF(text=prog)
# b.attach_kprobe(event=b.get_syscall_fnname("clone"), fn_name="hello")

# # header
# print("%-18s %-16s %-6s %s" % ("TIME(s)", "COMM", "PID", "MESSAGE"))

# # format output
# while 1:
#     try:
#         (task, pid, cpu, flags, ts, msg) = b.trace_fields()
#     except ValueError:
#         continue
#     print("%-18.9f %-16s %-6d %s" % (ts, task, pid, msg))

b = BPF(text="""
#include <uapi/linux/ptrace.h>

BPF_HASH(last);

int do_trace(struct pt_regs *ctx) {
    u64 ts, *tsp, delta, key = 0;

    // attempt to read stored timestamp
    tsp = last.lookup(&key);
    if (tsp != NULL) {
        delta = bpf_ktime_get_ns() - *tsp;
        if (delta > 1000000000) {
            // output if time is less than 1 second
            bpf_trace_printk("%d\\n", delta / 1000000);
        }
        last.delete(&key);
    }
    // update stored timestamp
    ts = bpf_ktime_get_ns();
    last.update(&key, &ts);
    return 0;
}
""")

b.attach_kprobe(event=b.get_syscall_fnname("sync"), fn_name="do_trace")
print("Tracing for quick sync's... Ctrl-C to end")

start = 0
while 1:
    (task, pid, cpu, flags, ts, ms) = b.trace_fields()
    if start == 0:
        start = ts
    ts = ts - start
    print("At time %.2f s: multiple syncs detected, last %s ms ago" % (ts, ms))