import os
import numpy as np

w = np.loadtxt(r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\Softmax\Test\weight.csv', delimiter=',', dtype=np.float32)
w_data = w[:]
w_trans = w_data.reshape(16,7)
wr = np.mat(w_trans)

import socket, sys

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)    
server.bind(('localhost', 8086))
server.listen(1)
print("Setting OK")

while True:
    conn, addr = server.accept()
    cmnd = conn.recv(9)
    
    if 'SEND' in str(cmnd):

     x = np.loadtxt(r'C:\Users\User\Desktop\이덕규\LabVIEW\교육\2022\2022.03.24~2022.03.25, 2022.04.21~2022.04.22 대한상공회의소\2022.04.21~2022.04.22 Final Project\프로젝트(대한상공회의소)\프로젝트\Data\Softmax\Test\Real Data.csv', delimiter=',', dtype=np.float32)
     x_data = x[:]
     x_trans = x_data.reshape(1,16)
     xr = np.mat(x_trans)

     R = xr*wr

     np.argmax(R)
     
     b = data = '{}'.format(np.argmax(R))   
     conn.sendall(b.encode())
    

    
    elif 'QUIT'in str(cmnd):
        conn.sendall(b'QUIT-DONE')
        break

server.close()