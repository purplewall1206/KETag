sudo bpftrace -vl tracepoint:kmem:kmalloc
sudo bpftrace -e 'tracepoint:kmem:kmalloc { printf("%016lx\n", args->ptr); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { @bytes_alloc = hist(args->bytes_alloc) }'
# sudo bpftrace -e 'tracepoint:kmem:kmalloc { @[args->ptr] = count(); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { @[args->bytes_alloc] = count(); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { printf("%016lx, %8d, %8d\n", args->ptr, args->bytes_req, args->bytes_alloc); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { @[args->bytes_alloc] = count();  printf("%016lx, %8d, %8d\n", args->ptr, args->bytes_req, args->bytes_alloc); } interval:s:600 { exit(); }' -o kmallocstatistic.txt

sudo bpftrace -e 'kprobe:vmalloc { printf("param : %016lx  %016lx", arg1, arg2); }  kretprobe:vmalloc {printf("  ret: %016lx\n", retval); @[kstack]=count(); }'
sudo bpftrace -e 'kprobe:do_execve {printf("filename: %s\n", arg0);}'
sudo bpftrace -e 'tracepoint:syscalls:sys_enter_execve {}'

sudo bpftrace -vl tracepoint:syscalls:sys_enter_execve
sudo bpftrace -e 'tracepoint:syscalls:sys_enter_execve { printf ("filename: %s\n",  str(args->filename)); }'

sudo bpftrace -l | grep execve
    # tracepoint:syscalls:sys_enter_execve
    # tracepoint:syscalls:sys_exit_execve
    # tracepoint:syscalls:sys_enter_execveat
    # tracepoint:syscalls:sys_exit_execveat
    # kprobe:audit_log_execve_info
    # kprobe:__do_execve_file
    # kprobe:__ia32_compat_sys_execve
    # kprobe:__ia32_compat_sys_execveat
    # kprobe:__x32_compat_sys_execveat
    # kprobe:__x32_compat_sys_execve
    # kprobe:do_execve_file
    # kprobe:do_execve
    # kprobe:__ia32_sys_execve
    # kprobe:__x64_sys_execve
    # kprobe:do_execveat
    # kprobe:__ia32_sys_execveat
    # kprobe:__x64_sys_execveat

sudo bpftrace -e 'tracepoint:syscalls:sys_enter_vfork 
        { printf("fork trigger PID %d\n", pid); } 
         tracepoint:syscalls:sys_enter_fork { 
         printf("fork trigger PID %d\n", pid); } 
           tracepoint:syscalls:sys_enter_execve
            { printf ("PID %d, filename: %s\n", pid, str(args->filename)); } '


sudo bpftrace -e 'tracepoint:syscalls:sys_enter_execve
                { printf ("sys_enter_execve PID %d \n", pid); }
                tracepoint:syscalls:sys_enter_close 
                { printf ("sys_enter_close PID %d\n", pid); }
                tracepoint:syscalls:sys_enter_exit_group
                { printf ("sys_enter_exit_group PID %d\n",
                 pid); }'

sudo bpftrace -e 'tracepoint:syscalls:sys_enter_execve
                { printf ("sys_enter_execve PID %d \n", pid); }
                tracepoint:syscalls:sys_enter_exit_group
                { printf ("sys_enter_exit_group PID %d\n",
                 pid); }'