# 0524_socket_client_basic.py
# 클라이언트 만들기

import socket
import sys

if __name__ == '__main__':
    try:
        print("[Client] : Input Server IP = ", end="")
        message = input()
        serverinfo = message

        # 클라이언트와 서버를 연결하는 코드
        client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)     # 소켓 통신 옵션
        server_address = (serverinfo, 10000)        # 10000 : 연결할 포트 번호
        client_sock.connect(server_address)

        while True:
            print("[Client] : ", end="")
            message = input()

            # 연결된 이후부터의 코드 (서버에 접속 되었음을 알리는 코드)
            #message = "Connected"
            message = message.encode('utf-8')   # 인코딩
            client_sock.sendall(message)

            data = client_sock.recv(4096)       # 서버에서 데이터가 들어오기 전까지 대기
            if data:
                print("[Server] :", data.decode('utf-8'))      # 서버에서 보낸 데이터를 utf-8로 디코딩함

    except Exception as err:
        print(err)
    except KeyboardInterrupt:
        print("program force quit")
        sys.exit()
