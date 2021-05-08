
A = [0] * 93  #93
B = [0] * 84  #84
C = [0] * 111 #111
C[108] = C[109] = C[110] = 1
    
def XOR(A , B):
    
    if (int(A) + int(B)) % 2 == 0:
        return '0'
    else:    
        return '1'
        
def AND(A , B):
    
    if (int(A) * int(B)) == 1:
        return '1'
    else:
        return '0'
def clk():
    
    V1 = XOR(XOR(A[65] , AND(A[90], A[91])), A[92])
    V2 = XOR(XOR(B[68] , AND(B[81], B[82])), B[83])
    V3 = XOR(XOR(C[65] , AND(C[108], C[109])), C[110])
    
    new_bit = XOR(XOR(V1, V2), V3)
    print('new_bit')
    print(new_bit)
    
    A0 = XOR(A[68], V3)
    B0 = XOR(B[77], V1)
    C0 = XOR(C[86], V2)
    
    i = 92
    while i > 0 :
        A[i] = A[i - 1]
        i -= 1
    A[0] = A0
    print ('A0')
    print(A0)
    print(A)
    
    i = 83
    while i > 0 :
        B[i] = B[i - 1]
        i -= 1
    B[0] = B0
    print ('B0')
    print(B0)
    print(B)
    
    i = 110
    while i > 0 :
        C[i] = C[i - 1]
        i -= 1
    C[0] = C0
    print ('c0')
    print(C0)
    print(C)
    return new_bit
    

if __name__ == '__main__':

    
    print(A)
    print(B)
    print(C)

    keystream = ''
    for i in range(0, 70):
        keystream += clk()
        
    print('keystream')    
    print(keystream[0 : 70])    

        
    
