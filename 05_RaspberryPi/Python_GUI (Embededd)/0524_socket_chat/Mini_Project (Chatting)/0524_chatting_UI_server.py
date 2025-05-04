# 0524_chatting_UI_server.py

# _*_ coding : utf-8 _*_
from tkinter import *
import socket
import sys
import threading


#####################################
#       Tkinter + Server
#####################################
class MainFrame:
    # 가장 먼저 실행되는 코드
    def __init__(self, window):
        # Tkinter의 타이틀과 창 크기, 좌표 지정
        window.title("Chatting Server")
        window.geometry("320x240+10+10")

        # Tkinter Label과 연결할 변수 지정
        self.connectStateVal = StringVar()
        self.connectStateVal.set("disconnect")

        # 현재 연결 상태를 보여줄 Label을 선언, 위치 및 크기 정의
        connectStateLabel = Label(window, textvariable=self.connectStateVal)
        connectStateLabel.place(x=0, y=30, width=320)

        # 현재 수신 받은 메세지를 출력할 변수 지정 (recvMsgVal)
        self.recvMsgVal = StringVar()
        self.recvMsgVal.set("-")

        # 현재 수신 받은 메세지를 출력할 Label을 선언, 위치 및 크기 정의
        self.recvMsgLabel = Label(window, textvariable=self.recvMsgVal)
        self.recvMsgLabel.place(x=80, y=60, width=160)

        # 메시지 전송을 위한 변수 지정
        self.sendMsgVar = StringVar()
        # 메시지 전송을 위한 엔트리 선언, 위치 및 크기 정의
        sendMsgEntry = Entry(window, textvariable=self.sendMsgVar)
        sendMsgEntry.place(x=80, y=90, width=160)

        # 전송을 위한 버튼을 선언, 위치 및 크기 정의
        # MainFrame 클래스 내 sendMsg() 함수 연결
        sendButton = Button(window, text="Send", command=self.sendMessage)
        sendButton.place(x=80, y=120, width=160)

        # 서버를 수행하기 위한 소켓 스레드 호출
        ServerSocketThread = threading.Thread(target=self.serverSocket)
        ServerSocketThread.start()

    #########################################
    # 서버 소켓을 생성하고 데이터 수신을 대기한다.
    #########################################
    def serverSocket(self):
        while True:
            try:
                self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                server_address = ('', 10000)

                self.sock.bind(server_address)
                self.sock.listen(1)

                self.connection, client_address = self.sock.accept()
                print("[Server] : connection from " + str(client_address))
                self.connectStateVal.set("Connction from" + str(client_address))

                while True:
                    data = self.connection.recv(4096)
                    if data:
                        tempData = data.decode('utf-8')
                        print("[Client] : ", tempData)
                        self.recvMsgVal.set(tempData)
                    else:
                        print("disconnect..from ", client_address)
                        break

            except Exception as err:
                print(err)

            finally:
                self.sock.close()
                self.connectStateVal.set("disconnect")

    ######################
    # 메시지를 전송하는 함수
    ######################
    def sendMessage(self):
        message = self.sendMsgVar.get()
        message = message + "\n"
        message = message.encode('utf-8')
        self.connection.sendall(message)


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
