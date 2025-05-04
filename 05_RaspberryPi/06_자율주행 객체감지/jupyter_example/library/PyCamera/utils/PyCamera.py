# v1.5.5
import cv2
import threading
from .Utility import *

# 전처리 FLAG
class Augmentation_Option:
    PADDING = 1
    HORIZONTAL_FLIP = 2
    VERTICAL_FLIP = 3
    GAUSSIAN_BLUR = 4
    GRAY_SCALE = 5

# 카메라 interface 클래스
class PyCamera:
    def __init__(self):
        self.camera = None
        self.camera_status = False
        self.camera_width = 0
        self.camera_height = 0
        
        # 전처리 사용 여부
        self.USE_PADDING = False
        self.USE_HORIZONTAL_FLIP = False
        self.USE_VERTICAL_FLIP = False
        self.USE_GAUSSIAN_BLUR = False
        self.USE_GRAY_SCALE = False
        self.USE_DSHOW_OPTION = False

        # 전처리 옵션 목록
        self.preprocessing_options = {}

        # 프레임 읽기 Lock (동시 접근으로 인한 오류 방지)
        self.read_lock = threading.Lock()

        # raise Exception("PyCamera 클래스는 interface 클래스이므로 인스턴트 생성을 지원하지 않습니다.")

    # 카메라로부터 영상을 1 프레임 읽어들임
    def get_frame(self):
        self.read_lock.acquire()
        ret, frame = self.camera.read()
        self.read_lock.release()

        if(ret == False or frame is None):
            self.camera_status = ret
            print("카메라와 연결이 종료되었습니다. None 값 반환됨.")
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

    # # 카메라 옵션 설정 (삭제 예정)
    # def set_option(self, option=None, status=True):
    #     if(option == Augmentation_Option.PADDING):
    #         self.USE_PADDING = status
    #     elif(option == Augmentation_Option.HORIZONTAL_FLIP):
    #         self.USE_HORIZONTAL_FLIP = status
    #     elif(option == Augmentation_Option.VERTICAL_FLIP):
    #         self.USE_VERTICAL_FLIP = status
    #     elif(option == Augmentation_Option.GAUSSIAN_BLUR):
    #         self.USE_GAUSSIAN_BLUR = status
    #     elif(option == Augmentation_Option.GRAY_SCALE):
    #         self.USE_GRAY_SCALE = status

    #     return

    # 카메라 해상도 가져오기
    def getResolution(self):
        return (int(self.camera.get(3)), int(self.camera.get(4)))
    
    def getWidth(self):
        return int(self.camera.get(3))
    
    def getHeight(self):
        return int(self.camera.get(4))

    # 카메라 재접속 (연결이 끊겨있을 때만 사용 가능)
    def reconnect(self):
        if(not self.isOpened()):
            pass
    
    # 카메라가 열려있는 지 여부
    def isOpened(self):
        return self.camera_status

    # 카메라 자원 할당 해제
    def dispose(self):
        self.camera_status = False
        self.camera.release()

    # 프레임을 읽어서 값을 리턴하기 전에 처리될 옵션 (전처리 관련)
    # name : 전처리 옵션 이름
    # enable : 활성화 여부 (True, False)
    # func : 전처리 함수
    # args : 전처리 함수에 들어갈 인자(리스트)
    # kwargs : 전처리 함수에 들어갈 인자(딕셔너리)
    def set_option(self, name, enable, func=None, *args, **kwargs):
        if(enable == True and not hasattr(func, '__call__')):
            print("유효하지 않는 전처리 함수입니다.")
            return
        
        if(enable == False and name in self.preprocessing_options.keys()):
            del self.preprocessing_options[name]
            return
        
        self.preprocessing_options[name] = {
            "function": func,
            "args": args,
            "kwargs": kwargs
        }

    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.dispose()

    def __iter__(self):
        while(self.isOpened()):
            yield self.get_frame()
