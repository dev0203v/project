import base64
import threading
import cv2
import tensorflow as tf
import numpy as np
from socket import *
import json
import sys
from datetime import datetime

global BUF_SIZE
BUF_SIZE = 4096

TCP_IP = "10.10.21.116"
TCP_PORT = 9190

clnt_sock = socket(AF_INET, SOCK_STREAM)
clnt_sock.connect((TCP_IP,TCP_PORT))
def receive_image():
    data1 =clnt_sock.recv(BUF_SIZE)
    file_size = int(data1.decode())
    print(f'file_size: {file_size}')

    image_list = []
    try:
        temp_ = 0
        while file_size > temp_:
            data = clnt_sock.recv(BUF_SIZE)
            image_list.append(data)
            temp_ += len(data)
    finally:
        test = b''.join(image_list)
        temp = np.frombuffer(test, dtype=np.uint8)
        img = cv2.imdecode(temp, cv2.IMREAD_COLOR)
        print(type(temp))
        print('bye bye~')
        return img

def JUDGE_Image(img):
    model = tf.keras.models.load_model('Model/Testmodel')
    reimg = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    reimg = cv2.resize(reimg, (50, 50), interpolation=cv2.INTER_LINEAR)
    reimg = np.asarray(reimg[np.newaxis, :, :, :]) / 255
    result = model.predict(reimg)

    return result[0][0]

json_data = {
    'Select' : 12,
}

msg = json.dumps(json_data)

clnt_sock.sendall(msg.encode())

print('JSON 데이터 전송 완료')

while True:
    sys.stdout.flush()
    print('Waiting....')
    img = receive_image()
    result= JUDGE_Image(img)
    if result< 0.15:
        result_text = '착용'
        msg_ = result_text + '!'
        clnt_sock.send(msg_.encode())
    else:
        result_text = '미착용'
        msg_ = result_text + '!'
        clnt_sock.send(msg_.encode())

    print(msg_)
    print(result_text.encode())

    if img is None:
        break
    print('끝')

print('client sock close')
clnt_sock.close()
