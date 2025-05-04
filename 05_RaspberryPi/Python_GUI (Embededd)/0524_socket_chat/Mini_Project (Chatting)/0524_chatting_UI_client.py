# 0524_chatting_UI_client.py

# _*_ coding : utf-8 _*_
from tkinter import *
import socket
import sys
import threading


#####################################
#       Tkinter + Client
#####################################
class MainFrame:
    # 가장 먼저 실행되는 코드
    def __init__(self, window):
        # Tkinter의 타이틀과 창 크기, 좌표 지정
        window.title("Chatting Client")
        window.geometry("320x240+10+10")

        # 접속할 서버의 IP 입력
        self.connectServerIpStringVar = StringVar()
        self.connectServerIpStringVar.set("127.0.0.1")
        connectServerIpEntry = Entry(window, textvariable=self.connectServerIpStringVar)
        connectServerIpEntry.place(x=80, y=30, width=160)

        # 전송을 위한 버튼 선언, 위치 및 크기 정의
        # MainFrame 클래스 내 sendMessage() 함수 연결
        serverConnectButton = Button(window, text="Connect", command=self.connect)
        serverConnectButton.place(x=80, y=60, width=160)

        # Tkinter Label과 연결할 변수 지정
        self.connectStateVal = StringVar()
        self.connectStateVal.set("disconnect")

        # 현재 연결 상태를 보여줄 Label 선언, 위치 및 크기 정의
        connectStateLabel = Label(window, textvariable=self.connectStateVal)
        connectStateLabel.place(x=0, y=90, width=320)

        # 현재 수신 받은 메세지를 출력할 변수 지정 (recvMsgVal)
        self.recvMsgVal = StringVar()
        self.recvMsgVal.set("-")

        # 현재 수신 받은 메세지를 출력할 Label을 선언, 위치 및 크기 정의
        self.recvMsgLabel = Label(window, textvariable=self.recvMsgVal)
        self.recvMsgLabel.place(x=80, y=120, width=160)

        # 메시지 전송을 위한 변수 지정
        self.sendMsgVar = StringVar()
        # 메시지 전송을 위한 엔트리 선언, 위치 및 크기 정의
        sendMsgEntry = Entry(window, textvariable=self.sendMsgVar)
        sendMsgEntry.place(x=80, y=150, width=160)

        # 전송을 위한 버튼을 선언, 위치 및 크기 정의
        # MainFrame 클래스 내 sendMsg() 함수 연결
        sendButton = Button(window, text="Send", command=self.sendMessage)
        sendButton.place(x=80, y=180, width=160)

    ############################################
    # 클라이언트 소켓을 생성하고 데이터 수신을 대기한다.
    ############################################
    def clientSocket(self):
        while True:
            try:
                # 소켓 생성
                self.client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

                # 서버의 IP와 포트 설정
                server_address = (self.connectServerIpStringVar.get(), 10000)
                print(self.connectServerIpStringVar.get())

                # 서버로 접속 시도
                self.client_sock.connect(server_address)
                self.connectStateVal.set("connected")

                while True:
                    # 아래는 서버에 접속할 시 처리할 동작들 기술
                    data = self.client_sock.recv(4096)
                    if data:
                        print(data.decode('utf-8'))
                        self.recvMsgVal.set(data.decode('utf-8'))
                    else:
                        self.connectStateVal.set("disconnect")
                        break

            except Exception as err:
                print(err)

    ################
    # 서버 연결 시도
    ################
    def connect(self):
        # 실시간으로 상태를 변경시키는 ultrasonicStateThread 동작 시키기 위한 쓰레드 생성
        self.t = threading.Thread(target=self.clientSocket)
        self.t.start()

    ######################
    # 메시지를 전송하는 함수
    ######################
    def sendMessage(self):
        message = self.sendMsgVar.get()
        message = message + "\n"
        message = message.encode('utf-8')
        self.client_sock.sendall(message)


##########################
#       메인 코드
##########################
if __name__ == '__main__':
    try:
        window = Tk()
        MainFrame(window)
        window.mainloop()

    except KeyboardInterrupt:
        print("program force quit")
        sys.exit()
