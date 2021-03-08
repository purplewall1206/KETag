cmd_/home/ppw/KETag/p3test/modules.order := {   echo /home/ppw/KETag/p3test/p3test.ko; :; } | awk '!x[$$0]++' - > /home/ppw/KETag/p3test/modules.order
