import cv2
import time
import threading
import socket
from collections import deque # queue는 put 시 자동으로 pop이 되지 않으며, 이 때 코드가 blocking되는 문제가 있음
import numpy as np

from ..Utility import *

class TCPMJPEGServer():
    # camera : 카메라 클래스
    # fps : 카메라 영상으로부터 프레임을 추출할 때 지정
    # save_path : 추출한 프레임을 저장할 위치
    def __init__(self, camera=None, ip="0.0.0.0", port=5000):
        self.current_class = camera.__class__
        self.base_class = camera.__class__.__base__

        # v1.9.4 : 굳이 PyCamera 형식이 아니어도 스트리밍이 가능하도록 함
        # if(not hasattr(camera, "get_frame")):
        #     raise Exception("잘못된 PyCamera 형식입니다.")

        # MJPEG 서버에 스트리밍할 카메라
        self.camera = camera
        # MJPEG 서버에 스트리밍할 이미지 큐 (카메라가 등록되어있지 않을 때 사용)
        self.image_queue = deque(maxlen=1)
        # MJPEG 서버 아이피 및 포트
        self.server_ip = ip
        self.server_port = port
        # MJPEG 서버 실행 여부
        self.isRunning = False
        # 클라이언트 목록
        self.clients = []
        # 서버 소켓
        self.socketServer = None

        self.printCameraInformation()

    # MJPEG 스트리밍 시작
    def start(self):
        if(not self.isRunning):
            self.isRunning = True

            self.socketServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
            self.socketServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.socketServer.bind((self.server_ip, self.server_port))

            self.tcpServer_thread = threading.Thread(target=self._socket_server)
            self.tcpServer_thread.daemon = True
            self.tcpServer_thread.start()

            self.sendData_thread = threading.Thread(target=self.sendData)
            self.sendData_thread.daemon = True
            self.sendData_thread.start()

    
    def stop(self):
        if(self.isRunning):
            self.socketServer.close()
            self.isRunning = False

    def _socket_server(self):
        while(self.isRunning):
            try:
                # 클라이언트 소켓 연결 대기 (listen은 연결 요청 큐의 수)
                self.socketServer.listen(1)

                # 클라이언트 연결 성공 시 client 소켓과 연결 정보를 받는다.
                client_socket, client_address = self.socketServer.accept()

                # socketReceiverThread = threading.Thread(target=self.sendData, args=(clientSocket, clientAddress,))
                # socketReceiverThread.setDaemon(True)
                # socketReceiverThread.start()

                print("클라이언트가 접속되었습니다. ({0})".format(client_address))
                self.clients.append(client_socket)
            except Exception as e:
                self.isRunning = False
                break
    
    def sendData(self):
        frame = np.zeros(shape=(224, 224, 3))

        while(self.isRunning):
            if(self.camera is not None):
                self.image_queue.append(self.camera.get_frame())
            
            if(len(self.image_queue) != 0):
                frame = self.image_queue.pop()
            
            if self.camera is not None and not self.camera.isOpened():
                time.sleep(1)
                continue
            
            buffer = cv2.imencode('.jpg', frame)[1].tobytes()
            
            for csocket in self.clients:
                try:
                    csocket.sendall(
                        b"--frame\r\n" + 
                        b"Content-Type: image/jpeg\r\n" + 
                        b"Content-Length: " + str(len(buffer)).encode() + b"\r\n\r\n" +
                        buffer
                    )

                except ConnectionResetError:
                    csocket.close()
                    self.clients.remove(csocket)
                    break
                except socket.error:
                    csocket.close()
                    self.clients.remove(csocket)
                    break
                finally:
                    time.sleep(0.01)

    def registerCamera(self, camera):
        if(not hasattr(camera, "get_frame")):
            raise Exception("잘못된 PyCamera 형식입니다.")
        self.camera = camera
    
    def unregisterCamera(self):
        self.camera = None

    # 수동으로 이미지 업데이트 (만약, 카메라가 등록되어있으면 자동으로 업데이트되니 참고할 것)
    def update(self, frame):
        self.image_queue.append(frame)
    
    def printCameraInformation(self):
        print("MJPEG Server IP : {0}".format(self.server_ip))
        print("MJPEG Server Port : {0}".format(self.server_port))
        print("MJPEG Streaming Path : tcp://{0}:{1}".format(self.server_ip, self.server_port))

    def __enter__(self):
        self.start()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.stop()
