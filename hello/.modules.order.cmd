cmd_/home/ppw/KETag/hello/modules.order := {   echo /home/ppw/KETag/hello/hello.ko; :; } | awk '!x[$$0]++' - > /home/ppw/KETag/hello/modules.order
