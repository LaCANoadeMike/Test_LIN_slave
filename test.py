#  byte p0 = BIT(addr,0) ^ BIT(addr,1) ^ BIT(addr,2) ^ BIT(addr,4);
#   byte p1 = ~(BIT(addr,1) ^ BIT(addr,3) ^ BIT(addr,4) ^ BIT(addr,5));
#   return (p0 | (p1<<1))<<6;
#addrbyte = (ident&0x3f) | addrParity(ident); //new

                #  7654 3210         
direccion = 0x15  #0001 0101
print (direccion)
p0 = 1 ^ 0 ^ 1 ^ 1
p1 = not(0 ^ 0 ^ 1 ^ 0)
print (bin(p0))  #0000 0001
print (bin(p1))  #1000 0010

result = (p0 | (p1 <<1)) <<6

addrbyte = (direccion & 0x3f) |  result

print (bin(addrbyte))
print(hex(addrbyte))
