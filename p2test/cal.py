import sys

# calculate ketag's tag
start      = 0xffff800000000000
ketag_base = 0xffffb88000000000
TB = 2**40
ketag_offset = ketag_base - (start>>3)
print(hex(ketag_offset))
# 0xdfffc88000000000

# tag = (posx-start)/8 + ketag_base = posx/8 + ketag_base-start/8


ketag_base_tag = int((ketag_base-start)/8)+ketag_base
ketag_base_tag_end = int((ketag_base+TB*16-start)/8) + ketag_base

print(hex(ketag_base_tag))
print(hex(int(ketag_base/8) + ketag_offset))
print(hex(ketag_base_tag_end))
print(hex(int((ketag_base+TB*16)/8) + ketag_offset))

# 0xffffbf9000000000
# 0xffffc19000000000