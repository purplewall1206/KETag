cmd_/home/ppw/KETag/p2test/p2test.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 --build-id  -T ./scripts/module-common.lds -o /home/ppw/KETag/p2test/p2test.ko /home/ppw/KETag/p2test/p2test.o /home/ppw/KETag/p2test/p2test.mod.o;  true
