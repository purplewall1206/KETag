import os

start = 0xffff800000000000
kasanstart = 0xffffec0000000000
kasanend = 0xfffffbffffffffff

moduleend = 0xfffffffffeffffff
_stext = 0xffffffff80000000
end = 0xffffffffffffffff

TB = 2 ** 40
kasan = ((kasanend-kasanstart)/TB)
total = ((end-start)/TB/8)
print("kasan:")
print(kasan)
print("total")
print (total)

# (startx-start)/8+ketag_offset = kasanstart
print("ketag text :")
_stext_ketag = int((_stext-start)/8+kasanstart)
print("%#x"%_stext_ketag)
print(_stext_ketag-kasanstart)
print(_stext_ketag-kasanend)