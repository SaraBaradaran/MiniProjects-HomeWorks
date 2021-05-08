import socket	 
import base64
import hashlib
import hmac
from Crypto.Cipher import AES
from random import randint
P = 40302273343993537574304330066074967659563243264386517454268541377294315262502533088222215811589431534649485041935446720876584585371297642846196428189595229097821672401312627175453066899460781876683059744428319686397864917267754993763904703186487325735252390067676413384247720864795923701378660494000616091396500517448783174591136595342577823282467525531120748592743561755052057752775715370537673494515663241308706321728401850888750778254065903734540543
G = 5238116339635683226345818856806382637093763819890735386545336621006145246386185455187064008442796203233841038392613764872596069657755956755517861023104922634166082661752669144733542175747380506736070854565799195266299039283382041713844922119983147083392935042512261131343476529814213896943097994045744255444866210830279697906450263496488388573305122373167632258148333953215352314504845881244179737133175785406704702295679609111751972794179291945735723

#public_key = G ^ private_key mod P

def key_generation():
    global client_public_key, private_key, P
    key = pow(client_public_key, private_key, P)
    key = hashlib.sha256(str(key).encode('utf-8')).digest()
    #print('session key : {}\n'.format(key))
    return key 

def pad(message):
    return message + (16 - len(message) % 16) * chr(16 - len(message) % 16)
def unpad(message):
    return message[:-ord(message[len(message) - 1:])]

def reciving_client_publickey(connection):
    global client_public_key
    data = connection.recv(1000)
    client_public_key = int(data.decode('utf-8'))
    print('client_public_key : {}\n'.format(client_public_key))

def sending_server_publickey(connection):
    connection.send(str(public_key).encode('utf-8'))
    print('server public key has been sent\n')

def reciving_client_message(connection, key):
    message = connection.recv(1000)
    print('encrypted recived message : {}\n'.format(message))
    sign = message[-64:]
    cipher = message[:len(message) - 64]
    print('sign : {}\n'.format(sign))
    print('cipher : {}\n'.format(cipher))
    plain = decryption(key, cipher)
    plain = unpad(plain)
    plain = plain.decode('utf-8')
    print("message integrity : {}" .format(check_sign(plain, sign, key)))
    print('recived message after decryption : {}\n'.format(plain))

def sending_server_message(connection, key):
    message = input('enter your message : ')
    sign = sign_message(key, message)
    message = pad(message)
    cipher = encryption(key, message)
    print('encrypted message : {}\n'.format(cipher))
    connection.send(cipher + sign)
    print('message has been sent\n')

def encryption(key, message):
    aes = AES.new(key, AES.MODE_ECB)
    cipher = aes.encrypt(message)
    cipher = base64.b64encode(cipher)
    return cipher

def decryption(key, message):
    message = base64.b64decode(message)
    aes = AES.new(key, AES.MODE_ECB)
    plain = aes.decrypt(message)
    return plain


def sign_message(key, message):
    message = bytes(message.encode('utf-8'))
    H = hmac.new(key, message, hashlib.sha256)
    return str(H.hexdigest()).encode('utf-8')

def check_sign(message, sign, key):
    message = bytes(message.encode('utf-8'))
    H = hmac.new(key, message, hashlib.sha256)
    return str(H.hexdigest()).encode('utf-8') == sign

if __name__ == "__main__":

    private_key = randint(2, P - 1)
    public_key = pow(G, private_key, P)
    print('server_public_key : {}\n'.format(public_key))
#   print('server_private_key : {}\n'.format(private_key))
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    if s == 0:
        print ('error in server socket creation\n')

    port = 5579
    local_addr = socket.gethostname()
    s.bind((local_addr, port))
    s.listen(5)
    print('listening ...\n')
    connection , client_addr = s.accept()

    reciving_client_publickey(connection)
    key = key_generation()
    sending_server_publickey(connection)
    
    while 1:
        reciving_client_message(connection, key)
        sending_server_message(connection, key)
    s.close()