from typing import Deque
import cv2
import time
import threading
from socketserver import ThreadingMixIn
from collections import deque # queue는 put 시 자동으로 pop이 되지 않으며, 이 때 코드가 blocking되는 문제가 있음
import numpy as np

from ..Utility import *

if getPythonVersion()[0] == 3:
    from http.server import BaseHTTPRequestHandler, HTTPServer
else:
    from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer

class HTTPMJPEGServer():
    # camera : 카메라 클래스
    # fps : 카메라 영상으로부터 프레임을 추출할 때 지정
    # save_path : 추출한 프레임을 저장할 위치
    def __init__(self, camera=None, ip="0.0.0.0", port=8090, streamPath="/"):
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
        # MJPEG 서버 영상 스트리밍 주소 무결성 검사
        if(streamPath == ""):
            streamPath = "/"
        if(streamPath[0] != "/"):
            streamPath = "/" + streamPath
        # MJPEG 서버 영상 스트리밍 주소
        self.streamPath = streamPath
        # MJPEG 서버 실행 여부
        self.isRunning = False

        # HTTP Handler
        class MJPEGServer_Handler(BaseHTTPRequestHandler):
            camera = None
            image_queue = None
            streamPath = "/"
            isRunning = True

            def do_GET(self):
                try:
                    if self.path == self.streamPath:
                        self.send_response(200)
                        self.send_header('Content-type', 'multipart/x-mixed-replace; boundary=frame')
                        self.end_headers()
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

                            self.wfile.write(b"--frame\r\n")
                            self.send_header('Content-type', 'image/jpeg')
                            self.send_header('Content-length', str(len(buffer)))
                            self.end_headers()

                            self.wfile.write(buffer)
                            self.wfile.write(b'\r\n')
                    else:
                        self.send_response(404)
                        self.send_header('Content-type', 'text/html')
                        self.end_headers()
                        self.wfile.write('<html><head></head><body>'.encode())
                        self.wfile.write('<h1>{0!s} not found</h1>'.format(self.path).encode())
                        self.wfile.write('</body></html>'.encode())
                except (ConnectionResetError, ConnectionAbortedError) as e:
                    pass

            def log_message(self, format, *args):
                return
        
        self.handler = MJPEGServer_Handler
        self.handler.camera = self.camera
        self.handler.image_queue = self.image_queue
        self.handler.streamPath = self.streamPath

        # 여러 개의 연결을 받을 수 있도록 하기 위해 해당 클래스로 감쌈
        class ThreadingHTTPServer(ThreadingMixIn, HTTPServer):
            daemon_threads = True

        self.httpServer = ThreadingHTTPServer((self.server_ip, self.server_port), MJPEGServer_Handler)
        self.printCameraInformation()

    # MJPEG 스트리밍 시작
    def start(self):
        if(not self.isRunning):
            self.httpServer_thread = threading.Thread(target=self.httpServer.serve_forever)
            self.httpServer_thread.daemon = True
            self.httpServer_thread.start()
            self.isRunning = True
    
    def stop(self):
        if(self.isRunning):
            # 파이썬 httpServer에서는 shutdown 함수 호출 시 바로 종료되지 않는다.
            # shutdown 요청 후 적어도 한 번 이상 접속 요청이 있어야 종료 작업에 들어간다.
            self.httpServer.shutdown()
            self.isRunning = False
            self.handler.isRunning = False
    
    def registerCamera(self, camera):
        if(not hasattr(camera, "get_frame")):
            raise Exception("잘못된 PyCamera 형식입니다.")
        self.camera = camera
        self.handler.camera = camera
    
    def unregisterCamera(self):
        self.camera = None
        self.handler.camera = None

    # 수동으로 이미지 업데이트 (만약, 카메라가 등록되어있으면 자동으로 업데이트되니 참고할 것)
    def update(self, frame):
        self.image_queue.append(frame)

    def printCameraInformation(self):
        print("MJPEG Server IP : {0}".format(self.server_ip))
        print("MJPEG Server Port : {0}".format(self.server_port))
        print("MJPEG Streaming Path : http://{0}:{1}{2}".format(self.server_ip, self.server_port, self.streamPath))

    def __enter__(self):
        self.start()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.stop()
