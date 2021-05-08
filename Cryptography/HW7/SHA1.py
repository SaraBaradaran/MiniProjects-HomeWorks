import hashlib

bin_num = ['0000','0001','0010','0011','0100','0101','0110','0111','1000','1001']
bin_num_2 = ['1010','1011','1100','1101','1110','1111']

def hexTobin(hex_msg):
    res = ''
    for i in hex_msg:
        if(i <= '9') and (i >= '0'):
            res = res + bin_num[ord(i) - ord('0')]
        else:
            res = res + bin_num_2[ord(i) - ord('a')]
    return res

def pad(bin_d):
    while len(bin_d) % 512 != 448:
        bin_d = bin_d + '0'
    return bin_d

def chunks(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

def circular_left_shift(n, b):
    return ((n << b) | (n >> (32 - b))) & 0xffffffff

def sha1(data):

    h0 = 0x67452301
    h1 = 0xEFCDAB89
    h2 = 0x98BADCFE
    h3 = 0x10325476
    h4 = 0xC3D2E1F0

    bin_data = hexTobin((data.encode('ascii')).hex()) + '1'
    bin_d = pad(bin_data)
    
    bin_d = bin_d + '{0:064b}'.format(len(bin_data)-1)

    for c in chunks(bin_d, 512): 
        x = chunks(c, 32)
        w = [0] * 80

        for i in range(0, 16):
            w[i] = int(x[i], 2)

        for i in range(16, 80):
            w[i] = circular_left_shift((w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]), 1)

        a = h0
        b = h1
        c = h2
        d = h3
        e = h4

        for i in range(0, 80):
            if 0 <= i <= 19:
                f = (b & c) | ((~b) & d)
                k = 0x5A827999
            elif 20 <= i <= 39:
                f = b ^ c ^ d
                k = 0x6ED9EBA1
            elif 40 <= i <= 59:
                f = (b & c) | (b & d) | (c & d) 
                k = 0x8F1BBCDC
            elif 60 <= i <= 79:
                f = b ^ c ^ d
                k = 0xCA62C1D6

            last_a = a
            a = circular_left_shift(a, 5) + f + e + k + w[i] & 0xffffffff
            e = d
            d = c
            c = circular_left_shift(b, 30)
            b = last_a

        h0 = h0 + a & 0xffffffff
        h1 = h1 + b & 0xffffffff
        h2 = h2 + c & 0xffffffff
        h3 = h3 + d & 0xffffffff
        h4 = h4 + e & 0xffffffff

    return '%08x%08x%08x%08x%08x' % (h0, h1, h2, h3, h4)

if __name__ == "__main__":

    data = input("Enter your data : ")
    print("result of our sha1 function      : {}".format(sha1(data)))
    print("result of built-in sha1 function : {}".format(hashlib.sha1(data.encode('utf-8')).hexdigest()))