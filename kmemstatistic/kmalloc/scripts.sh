sudo bpftrace -vl tracepoint:kmem:kmalloc
# tracepoint:kmem:kmalloc
#     unsigned long call_site;
#     const void * ptr;
#     size_t bytes_req;
#     size_t bytes_alloc;
#     gfp_t gfp_flags;
