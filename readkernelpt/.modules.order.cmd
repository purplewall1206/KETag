cmd_/home/ppw/KETag/readkernelpt/modules.order := {   echo /home/ppw/KETag/readkernelpt/readkernelpt.ko; :; } | awk '!x[$$0]++' - > /home/ppw/KETag/readkernelpt/modules.order
