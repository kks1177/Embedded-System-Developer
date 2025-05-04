import cv2
import time
import threading
import socket
from collections import deque # queue는 put 시 자동으로 pop이 되지 않으며, 이 때 코드가 blocking되는 문제가 있음
import numpy as np

from ..Utility import *

class UDPMJPEGServer():
    # camera : 카메라 클래스
    # fps : 카메라 영상으로부터 프레임을 추출할 때 지정
    # save_path : 추출한 프레임을 저장할 위치
    def __init__(self, camera=None, ip="127.0.0.1", port=5000):
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

            self.socketServer = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
            # self.socketServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

            # UDP 방식으로 보낼 수 있는 패킷의 최대 크기는 65,535바이트로, IP 및 UDP 헤더는 최소 28바이트로 결합된다.
            # 따라서 UDP로 데이터를 보낼 때 패킷의 최대 크기를 (65535 - 28) 로 제한한다.
            # https://stackoverflow.com/questions/44607737/dividing-udp-datagram-messages
            self.MAX_BUFFER_SIZE = 65535 - 28

            self.sendData_thread = threading.Thread(target=self.sendData)
            self.sendData_thread.daemon = True
            self.sendData_thread.start()

    
    def stop(self):
        if(self.isRunning):
            self.socketServer.close()
            self.isRunning = False
    
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
            
            try:
                buffer_final = (b"--frame\r\n" + 
                    b"Content-Type: image/jpeg\r\n" + 
                    b"Content-Length: " + str(len(buffer)).encode() + b"\r\n\r\n" +
                    buffer)
                
                if(len(buffer_final) > self.MAX_BUFFER_SIZE):
                    send_max_count = int(len(buffer_final) / self.MAX_BUFFER_SIZE) + 1
                else:
                    send_max_count = 1
                
                for i in range(send_max_count):
                    send_data = buffer_final[ i * self.MAX_BUFFER_SIZE : (i + 1) * self.MAX_BUFFER_SIZE ]

                    self.socketServer.sendto(
                        send_data,
                        (self.server_ip, self.server_port)
                    )
                
            # except ConnectionResetError:
            #     csocket.close()
            #     self.clients.remove(csocket)
            #     break
            # except socket.error:
            #     csocket.close()
            #     self.clients.remove(csocket)
            #     break
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
