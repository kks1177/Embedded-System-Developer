# 통신 코드.py

import tensorflow.compat.v1 as tf
import numpy as np
import socket, sys
tf.disable_v2_behavior()

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 8088))
server.listen(1)
print("Setting OK")

# 가중치 파일 저장한 경로
w = np.loadtxt('C:\\Embedded_System\\04_LabVIEW\\Programming_SourceCode\\Test\\weight.csv', delimiter=',', dtype=np.float32)
w_data = w[:]

while True:
    conn, addr = server.accept()
    cmnd = conn.recv(4)  # The default size of the command packet is 4 bytes

    if 'INIT' in str(cmnd):
        # 랩뷰에서 특징(결과)값 저장한 파일 경로 (!주의!  랩뷰 경로와 똑같이 맞출 것!!)
        x = np.loadtxt('C:\\Embedded_System\\04_LabVIEW\\Programming_SourceCode\\Test\\Real_Data.csv', delimiter=',', dtype=np.float32)
        x_data = x[:]
        x_trans = x_data.reshape(1,16)

        out = tf.matmul(x_trans, w_data)
        pred = tf.nn.softmax(out)
        prediction = tf.argmax(pred, 1)

        with tf.Session() as sess:
            sess.run(tf.global_variables_initializer())
            print(sess.run([pred]))
            print('예측: {}'.format(sess.run([prediction])))
            data = '{}'.format(sess.run([prediction]))
            conn.sendall(data.encode())
          
    elif 'QUIT'in str(cmnd):
        # Do the quiting action
        conn.sendall(b'QUIT-DONE')
        break

server.close()
