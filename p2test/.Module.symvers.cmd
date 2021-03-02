cmd_/home/ppw/KETag/p2test/Module.symvers := sed 's/ko$$/o/' /home/ppw/KETag/p2test/modules.order | scripts/mod/modpost  -a   -o /home/ppw/KETag/p2test/Module.symvers -e -i Module.symvers   -T -
