# Day11-01_SimpleServer.py

import socket

"192.168.0.1"
port = 8089
serverSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSock.bind(('localhost', port))
serverSock.listen(1)
print("Setting OK")

while True:
    conn, addr = serverSock.accept()
    cmnd = conn.recv(4)
    print(cmnd)

    if 'INIT' in str(cmnd):
        conn.sendall(b'INIT-Done')
    elif 'PLAY' in str(cmnd):
        conn.sendall(b'PLAY-Done')
    elif 'QUIT' in str(cmnd):
        conn.sendall(b'QUIT-Done')
        break

serverSock.close()

