sudo bpftrace -vl tracepoint:kmem:kmalloc
sudo bpftrace -e 'tracepoint:kmem:kmalloc { printf("%016lx\n", args->ptr); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { @bytes_alloc = hist(args->bytes_alloc) }'
# sudo bpftrace -e 'tracepoint:kmem:kmalloc { @[args->ptr] = count(); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { @[args->bytes_alloc] = count(); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { printf("%016lx, %8d, %8d\n", args->ptr, args->bytes_req, args->bytes_alloc); }'
sudo bpftrace -e 'tracepoint:kmem:kmalloc { @[args->bytes_alloc] = count();  printf("%016lx, %8d, %8d\n", args->ptr, args->bytes_req, args->bytes_alloc); } interval:s:600 { exit(); }' -o kmallocstatistic.txt