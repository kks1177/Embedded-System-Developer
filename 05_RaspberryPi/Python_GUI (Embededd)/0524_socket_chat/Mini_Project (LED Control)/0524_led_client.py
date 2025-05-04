# 0524_led_client.py

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
        window.title("Remote Lamp Client")
        window.geometry("320x240+10+10")

        # 접속할 서버의 IP 입력
        self.connectServerIpStringVar = StringVar()
        self.connectServerIpStringVar.set("127.0.0.1")
        connectServerIpEntry = Entry(window, textvariable=self.connectServerIpStringVar)
        connectServerIpEntry.place(x=80, y=30, width=160)

        # 전송을 위한 버튼 선언, 위치 및 크기 정의
        # MainFrame 클래스 내 sendMsg() 함수 연결
        serverConnectButton = Button(window, text="Connect", command=self.connect)
        serverConnectButton.place(x=80, y=60, width=160)

        # Tkinter Label과 연결할 변수 지정
        self.connectStateVal = StringVar()
        self.connectStateVal.set("disconnect")

        # 현재 연결 상태를 보여줄 Label 선언, 위치 및 크기 정의
        connectStateLabel = Label(window, textvariable=self.connectStateVal)
        connectStateLabel.place(x=0, y=90, width=320)

        # ON 신호를 전송하기 위한 버튼 생성, sendCommand 함수 연결
        sendButtonOn = Button(window, text="ON", command=self.sendCommand)
        sendButtonOn.place(x=60, y=140, width=80, height=80)

        # OFF 신호를 전송하기 위한 버튼 생성, sendCommand 함수 연결
        sendButtonOn = Button(window, text="OFF", command=self.sendCommand)
        sendButtonOn.place(x=180, y=140, width=80, height=80)

    def connect(self):
        pass

    def sendCommand(self):
        pass

    ######################################
    # 클라이언트 소켓 생성하고 데이터 수신 대기
    ######################################
    def clientSocket(self):
        try:
            # 소켓 생성
            self.client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

            # 서버의 IP와 포트 설정
            server_address = (self.connectServerIpStringVar.get(), 10000)
            print(self.connectServerIpStringVar.get())

            # 서버로 접속 시도
            self.client_sock.connect(server_address)
            self.connectStateVal.set("Connected")

            while True:
                # 아래는 서버에 접속할 시 처리할 동작 기술
                data = self.client_sock.recv(4096)
                if data:
                    print(data.decode('utf-8'))
                else:
                    self.connectStateVal.set("Disconnect")
                    break

        except Exception as err:
            print(err)

    ################
    # 서버 연결 시도
    ################
    def connect(self):
        self.t = threading.Thread(target=self.clientSocket)
        self.t.start()

    ####################################
    # id와 cmd를 인자로 패킷을 구성하여 전송
    ####################################
    def sendCommand(self, id, cmd):
        message = id + ", " + cmd + ", "
        message = message + "\n"
        message = message.encode('utf-8')
        self.client_sock.sendall(message)


##########################
#        메인 코드
##########################
if __name__ == '__main__':
    try:
        window = Tk()
        MainFrame = MainFrame(window)
        window.mainloop()
    except KeyboardInterrupt:
        print("program force quit")
        sys.exit()
