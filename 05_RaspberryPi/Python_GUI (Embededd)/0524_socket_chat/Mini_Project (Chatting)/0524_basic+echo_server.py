# 0524_basic+echo_server.py

# _*_ coding : utf-8 _*_
import socket
import sys
import threading


#####################################
#       console + Server
#####################################
class MainFrame:
    # 가장 먼저 실행되는 코드
    def __init__(self):
        # 서버가 시작 됐음을 알림
        print("\n >>>--- Chatting Server ---<<< ")

        # 서버를 수행하기 위한 소켓 스레드를 호출
        ServerSocketThread = threading.Thread(target=self.serverSocket)
        # ServerSocketThread.setDaemon(True)      # setDaemon : 이 프로그램이 종료되면 쓰레드도 종료할지, but 생략 가능
        ServerSocketThread.start()

        while True:
            try:
                message = input()
                self.sendMessage(message)
            except Exception as err:
                print(err)

    ########################################
    # 서버 소켓을 생성하고 데이터 수신을 대기한다.
    ########################################
    def serverSocket(self):
        while True:
            # 서버 소켓 통신은 예외 처리 (try ~ except) 필수로 해주기
            try:
                # 서버 소켓을 오픈
                # socket.AF_INET은 IPv4 주소체계를 의미
                # socket.SOCK_STREAM TCP 소켓을 의미
                self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

                # 소켓 옵션 설정. SOL_SOCKET은 소켓의 레벨 의미
                # socket.SO_REUSEADDR, 1 옵션은 소켓을 재할당이 가능하게 함
                self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

                # 서버 소켓의 IP와 포트 의미. 공백은 로컬을 읠미
                server_address = ('', 10000)
                print("[Server] : StartServer", server_address)
                # 서버를 위 IP와 포트로 바인드(연결)
                self.sock.bind(server_address)
                # 대기하는 연결 요청. 큐의 수 설정
                self.sock.listen(1)

                # 연결 성공시 연결 client 소켓인 connection 과 연결 client의 정보 수집
                self.connection, client_address = self.sock.accept()
                print("[Server] : Connection from" + str(client_address))

                # 서버는 연결이 끊이지 않는 한 루프를 돌며 수신 값을 받음
                while True:
                    # 수신 바이트 버퍼수
                    data = self.connection.recv(4096)
                    if data:
                        # 바이트로 데이터를 받기 때문에 UTF-8로 디코딩
                        print("[Client] :", data.decode('utf-8'))
                    else:
                        print("disconnect..from ", client_address)
                        break

            except Exception as err:
                print(err)

            # finally: - 정상 실행을 하든 에러가 발생하든 finally 코드는 무조건 실행
            finally:
                self.sock.close()
                print("disconnect")

    ######################
    # 메시지를 전송하는 함수
    ######################
    def sendMessage(self, message):
        message = message + "\n"
        message = message.encode('utf-8')
        self.connection.sendall(message)  #


##########################
#       메인 코드
##########################
if __name__ == '__main__':
    try:
        MainFrame()
    except KeyboardInterrupt:
        print("program force quit")
        sys.exit()
