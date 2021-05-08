
import hmac
import hashlib


def pad(a, l):
    while len(a) != l:
        a = a + b'\0'
    return a

def make_digest(text, key):
    key = bytes(key.encode('utf-8'))
    text = bytes(text.encode('utf-8'))
    h = hmac.new(key, text, hashlib.sha256)
    return h.hexdigest()

def hmac_func(text, k):

    k = k.encode('ascii')
    text = text.encode('ascii')

    t36 = bytes((x ^ 0x36) for x in range(256))
    t5C = bytes((x ^ 0x5C) for x in range(256))

    k = pad(k, 64)

    k_xor_ipad = k.translate(t36)
    k_xor_opad = k.translate(t5C)

    msg = k_xor_ipad + text

    h_msg = hashlib.sha256(msg).digest()

    msg = k_xor_opad + bytes(h_msg)

    h_msg = hashlib.sha256(msg).hexdigest()

    return h_msg

if __name__ == "__main__":

    text = input ("Enter text :")
    k = 'sara'

    print('the result of built-in hmac : {}'.format(make_digest(text, k)))
    print('the result of our hmac      : {}'.format(hmac_func(text, k)))