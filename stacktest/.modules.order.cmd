cmd_/home/ppw/KETag/stacktest/modules.order := {   echo /home/ppw/KETag/stacktest/stacktest.ko; :; } | awk '!x[$$0]++' - > /home/ppw/KETag/stacktest/modules.order
