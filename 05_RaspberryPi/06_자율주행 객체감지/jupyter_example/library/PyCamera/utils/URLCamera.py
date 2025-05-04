import cv2
import threading
import time
from .PyCamera import PyCamera
from .Utility import *

# 주소 형식(tcp, http 등)으로부터 프레임을 가져오는 클래스
class URLCamera(PyCamera):
    # camera_url : 카메라 주소
    def __init__(self, camera_url=None, live_thread=True):
        super(URLCamera, self).__init__()

        if(camera_url == None):
            raise Exception("Camera 주소가 지정되지 않았습니다.")

        self.camera_url = camera_url
        self.live_thread = live_thread

        # # 읽어들인 이미지를 저장할 Queue
        # self.frame_queue = queue.Queue()

        self.__open__()

    def __open__(self):
        self.camera = cv2.VideoCapture(self.camera_url)
        self.camera.set(cv2.CAP_PROP_BUFFERSIZE, 1)

        # self.camera_width = self.camera.get(3)
        # self.camera_height = self.camera.get(4)
        self.frame = self.camera.read()[1]

        # URL로부터 이미지를 읽어들일 경우 (영상 지연 문제로 쓰레드를 별도로 만들어 아래와 같이 비동기로 읽어들임)
        if(self.live_thread):
            self.is_run = True
            self.read_thread = threading.Thread(target=self._reader)
            self.read_thread.daemon = True
            self.read_thread.start()

        # 카메라의 정보 출력
        self.printCameraInformation()

        # 카메라 현재 상태
        self.camera_status = self.camera.isOpened()

        # 현재 재접속 시도 중인지 여부 (상태 체크용)
        self.check_reconnect = False
    
    # 카메라 재접속 (연결이 끊겨있을 때만 사용 가능)
    def reconnect(self):
        self.check_reconnect = True
        if(not self.isOpened()):
            self.dispose()
            self.__open__()
        self.check_reconnect = False
    
    # while문 안에서 이미지를 계속 읽어들임
    def _reader(self):
        while(self.is_run):
            ret, self.frame = self.camera.read()
            if(ret == False or self.frame is None):
                self.camera_status = ret
                break
            # if not self.frame_queue.empty():
            #     try:
            #         self.frame_queue.get_nowait()
            #     except queue.Empty:
            #         pass
            # self.frame_queue.put(frame) 
            self.camera_status = ret
            time.sleep(0.001)
        self.is_run = False

    # 카메라로부터 영상을 1 프레임 읽어들임 (_reader 함수로 인하여 아래와 같이 함수 재정의)
    def get_frame(self):
        if(self.live_thread):
            if(self.is_run == True and self.read_thread.is_alive()):
                # frame = self.frame_queue.get()
                frame = self.frame
            else:
                print("카메라와 연결이 종료되었습니다. None 값 반환됨.")
                frame = None
                return frame
        else:
            ret, frame = self.camera.read()
            if(ret == False or frame is None):
                print("카메라와 연결이 종료되었습니다. None 값 반환됨.")
                self.camera_status = ret
                return frame
            self.camera_status = ret
        
        for i in self.preprocessing_options.keys():
            p = self.preprocessing_options[i]
            frame = p["function"](frame, *p["args"], **p["kwargs"])
        
        # # 만약 option으로 PADDING 지정 시, 이미지를 1:1 비율에 맞게 Padding을 넣고 리턴함 (삭제 예정)
        # if(self.USE_PADDING == True):
        #     frame = addPadding(frame, color=(0, 0, 0))
        # if(self.USE_HORIZONTAL_FLIP == True):
        #     frame = cv2.flip(frame, 1)
        # if(self.USE_VERTICAL_FLIP == True):
        #     frame = cv2.flip(frame, 0)
        # if(self.USE_GAUSSIAN_BLUR == True):
        #     frame = cv2.GaussianBlur(frame, (5, 5), 0)
        # if(self.USE_GRAY_SCALE == True):
        #     frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        #     frame = cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR)

        return frame

    def printCameraInformation(self):
        # 카메라 유효값 체크
        if(not self.camera.isOpened()):
            print("Camera 연결이 종료되어 정보를 가져올 수 없습니다.")
            return
        
        # 카메라 정보 출력
        print("카메라 정보  : ")
        print("Camera Address : {0}".format(self.camera_url))
        print("Camera Width : {0}".format(self.camera.get(3)))
        print("Camera Height : {0}".format(self.camera.get(4)))
    
        # 카메라 자원 할당 해제
    def dispose(self):
        self.is_run = False
        while(self.read_thread is not None and self.read_thread.is_alive()):
            time.sleep(1)
            
        self.camera_status = False
        self.camera.release()
        self.read_thread = None
