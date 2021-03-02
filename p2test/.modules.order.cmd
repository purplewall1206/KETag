cmd_/home/ppw/KETag/p2test/modules.order := {   echo /home/ppw/KETag/p2test/p2test.ko; :; } | awk '!x[$$0]++' - > /home/ppw/KETag/p2test/modules.order
