# v1.5.5
import cv2
from numpy.core.numeric import full
from .PyCamera import PyCamera
from .Utility import *

# USB 카메라로부터 프레임을 가져오는 클래스 (GStreamer 미테스트)
class ScreenCamera(PyCamera):
    # screen_index : 모니터 번호 (지원 안 함, 현재 주 모니터만 사용 가능)
    # screen_size : 스크린 샷 사이즈 (4개의 요소를 가지는 튜플 형태로 주어져야 하며, 각각 시작/끝 좌표, 너비/높이를 나타낸다.)
    # fullscreen : 풀스크린 여부`
    def __init__(self, screen_index=0, screen_size=None, fullscreen=None):
        super(ScreenCamera, self).__init__()

        try:
            import pyautogui
            self.camera = pyautogui
        except ImportError:
            raise Exception("pyautogui 파이썬 패키지가 설치되어있지 않아 ScreenCamera 클래스 사용이 불가능합니다.")

        if(screen_index == None):
            raise Exception("Screen 번호가 지정되지 않았습니다.")

        if(screen_size is None):
            screen_size=(0, 0, 300, 300)
            if(fullscreen is None):
                fullscreen = True
        elif(fullscreen is None):
                fullscreen = False

        self.screen_index = 0
        self.screen_x = screen_size[0]
        self.screen_y = screen_size[1]
        self.screen_width = screen_size[2]
        self.screen_height = screen_size[3]
        self.fullscreen = fullscreen

        self.__open__()
    
    def __open__(self):
        # # 명시적으로 너비 혹은 높이를 지정했을 때 아래와 같이 수동으로 카메라 설정을 조작
        # if(self.camera_width is not None):
        #     self.camera.set(3, self.camera_width)
        # if(self.camera_height is not None):
        #     self.camera.set(4, self.camera_height)

        # self.camera_width = self.camera.get(3)
        # self.camera_height = self.camera.get(4)
        
        # 카메라의 정보 출력
        self.printCameraInformation()

        # 현재 재접속 시도 중인지 여부 (상태 체크용)
        self.check_reconnect = False

    # 카메라 재접속 (연결이 끊겨있을 때만 사용 가능)
    def reconnect(self):
        pass
    
    # 카메라로부터 영상을 1 프레임 읽어들임
    def get_frame(self):
        if(self.fullscreen):
            frame = self.camera.screenshot()
        else:
            frame = self.camera.screenshot(region=(self.screen_x, self.screen_y, self.screen_width, self.screen_height))

        frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
        if(frame is None):
            self.camera_status = False
            print("디스플레이 연결이 종료되었습니다. None 값 반환됨.")
            return frame

        self.camera_status = True

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
        # 카메라 정보 출력
        print("스크린 캡처 정보  : ")
        print("Screen Index : {0}".format(int(self.screen_index)))
        print("Screen Width : {0}".format(self.screen_width))
        print("Screen Height : {0}".format(self.screen_height))
        print("Screen Axis : {0}".format((self.screen_x, self.screen_y)))

    def isOpened(self):
        return True

    def dispose(self):
        pass