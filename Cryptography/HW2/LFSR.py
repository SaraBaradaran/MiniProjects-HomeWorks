

import numpy as np
alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5']


def get_initialization_vector(ciphertext, plaintext):
    c_len = len(ciphertext)
    p_len = len(plaintext)
    key = []
    keystream = ''
    for i in range (0 ,p_len):
        key.append(alphabet.index(ciphertext[i]) ^ alphabet.index(plaintext[i]))

    for i in key:
        keystream += (str(bin(i)[2:]).zfill(5))
    return keystream

def calculate_coeficients(keystream, LFSR_degree):
    c = []
    x = []
    for i in range(0, LFSR_degree):
        for j in range(i, LFSR_degree + i):
            x.append(int(keystream[j]))
        c.append(x)
        x = []
    
    a = np.array(c)
    for i in range (LFSR_degree, 2* LFSR_degree):
        x.append(int(keystream[i]))
    b = np.array(x)
    p = []  
    res = np.linalg.solve(a,b)
    
    for i in res :
        p.append(int(i % 2))
    
    return p
    
def XOR(sequence):
    s = 0
    for i in sequence:
       s += int(i)
    if s % 2 == 0:
        return 0
    else:
        return 1
        
def AND(in1, in2):
    s = ''
    for i in range(0, len(in1)):
        s += str(int(in1[i]) & int(in2[i]))
    return s    
    
def shift(sequence, new_bit):
    l = len(sequence)
    new_seq = ''
    for i in range(1, l):
        new_seq += sequence[i]
    new_seq += str(new_bit)
    print('new_seq')    
    print(new_seq)
    return new_seq
    
def decimal(sequence):
    s = 0
    e = 16
    for i in sequence:
        s += int(i) * e
        e /= 2    
    return int(s)
    
    
def generate_keystream(initialization_vector, p, c_len, LFSR_degree):
    sequence = initialization_vector
    x = ''
    for i in p:
        x += str(i)
    
    keystream = initialization_vector
    i = LFSR_degree
    while i < c_len * 5:
        new_bit = XOR(AND(x, sequence))
        print('new_bit')
        print(new_bit)
        keystream += str(new_bit)
        sequence = shift(sequence, new_bit)
        i += 1
        
    print('keystream :')    
    print(keystream)        
    return keystream    
    
def extract_plaintext(keystream, ciphertext):
    
    c_binary = ''
    for i in ciphertext:
        c_binary += bin(alphabet.index(i))[2:].zfill(5)
        
    print('ciphertext')
    print(c_binary)
    
    p_binary = ''
    for i in range(0, len(c_binary)):
        p_binary += str(int(keystream[i]) ^ int(c_binary[i]))
        
    print('plaintext')
    print(p_binary)
    
    plaintext = ''
    i = 0
    while i < len(p_binary):
        plaintext += alphabet[decimal(p_binary[i : i + 5])]
        i += 5
    
    print(plaintext)

if __name__ == '__main__':

    ciphertext = 'j5a0edj2b'
    plaintext = 'wpi'
    LFSR_degree = 6
    keystream = get_initialization_vector(ciphertext, plaintext)
    initialization_vector = keystream[0 : LFSR_degree]
    print('known key stream')
    print(keystream)
    print('initialization_vector')
    print(initialization_vector)
    p = calculate_coeficients(keystream, LFSR_degree)
    print('coeficients = [p0, p1, p2, ...]')
    print(p)
    keystream = generate_keystream(initialization_vector, p, len(ciphertext), LFSR_degree)
    extract_plaintext(keystream, ciphertext)

