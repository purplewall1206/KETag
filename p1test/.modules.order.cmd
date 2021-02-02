cmd_/home/ppw/KETag/p1test/modules.order := {   echo /home/ppw/KETag/p1test/p1test.ko; :; } | awk '!x[$$0]++' - > /home/ppw/KETag/p1test/modules.order
