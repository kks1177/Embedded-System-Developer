# 0524_socket_server_basic.py
# 서버 만들기

import socket

if __name__ == '__main__':
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)        # 소켓 통신 옵션
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        server_address = ('', 10000)        # 10000 : 연결할 포트 번호
        print("[Server] : StartServer", server_address)
        sock.bind(server_address)
        sock.listen(1)

        connection, client_address = sock.accept()
        print("[Server] : Connection from" + str(client_address))

        while True:
            data = connection.recv(4096)                    # 서버에서 데이터가 들어오기 전까지 대기
            if data:    # 전송 받은 데이터가 있으면
                connection.sendall(data)                    # 전송 받은 데이터를 클라이언트에게 그대로 전송
            else:       # 전송 받은 데이터가 없으면
                print("disconnect..from ", client_address)
                break

    except Exception as err:
        print(err)
    print("disconnect")
