# 0524_basic_client.py

# _*_ coding : utf-8 _*_
import socket
import sys
import threading


#####################################
#       console + Client
#####################################
class MainFrame:
    # 가장 먼저 실행되는 코드
    def __init__(self):
        # 서버가 시작 됐음을 알림
        print("\n >>>--- Chatting Client ---<<< ")

        # 서버 IP를 받아 옴
        print("[Client] : Input Server IP = ", end="")
        message = input()
        self.serverInfo = message
        self.connect()

        while True:
            try:
                message = input()
                self.sendMessage(message)
            except Exception as err:
                print(err)

    #############################################
    # 클라이언트 소켓을 생성하고 데이터 수신을 대기한다.
    #############################################
    def clientSocket(self):
        try:
            # 소켓 생성
            self.client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

            # 서버의 IP와 포트 설정
            server_address = (self.serverInfo, 10000)
            print("[Client] : Connect Server", server_address)
            # 서버로 접속을 시도
            self.client_sock.connect(server_address)
            print("[Client] : connected")

            # 서버는 연결이 끊기지 않는 한 루프를 돌며 수신 값을 받음
            while True:
                # 수신 바이트 버퍼 수
                data = self.client_sock.recv(4096)
                if data:
                    # 바이트로 데이터를 받기 때문에 UTF-8로 디코딩
                    print("[Server] :", data.decode('utf-8'))
                else:
                    print("disconnect..")
                    break

        except Exception as err:
            print(err)

    ######################
    # 메시지를 전송하는 함수
    ######################
    def connect(self):
        # 실시간으로 상태를 변경시키는 UltrasonicStateThread 동작 시키기 위한 쓰레드 생성
        self.t = threading.Thread(target=self.clientSocket)
        #self.t.setDaemon(True)
        self.t.start()

    ######################
    # 메시지를 전송하는 함수
    ######################
    def sendMessage(self, message):
        message = message + "\n"
        message = message.encode('utf-8')
        self.client_sock.sendall(message)


##########################
#       메인 코드
##########################
if __name__ == '__main__':
    try:
        MainFrame()
    except KeyboardInterrupt:
        print("program force quit")
        sys.exit()
