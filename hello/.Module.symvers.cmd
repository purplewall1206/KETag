cmd_/home/ppw/KETag/hello/Module.symvers := sed 's/ko$$/o/' /home/ppw/KETag/hello/modules.order | scripts/mod/modpost  -a   -o /home/ppw/KETag/hello/Module.symvers -e -i Module.symvers   -T -
