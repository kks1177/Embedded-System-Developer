import cv2
from .PyCamera import PyCamera
from .Utility import *

# 영상 파일로부터 프레임을 가져오는 클래스
class VideoCamera(PyCamera):
    # video_file : 영상 파일 이름
    # loop : 반복 재생 여부
    def __init__(self, video_file=None, loop=True):
        super(VideoCamera, self).__init__()
        # if(video_file == None):
        #     raise Exception("영상 파일이 지정되지 않았습니다.")

        self.video_file = video_file
        self.loop = loop

        self.__open__()

    def __open__(self):
        self.camera = cv2.VideoCapture(self.video_file)
        # self.camera_width = self.camera.get(3)
        # self.camera_height = self.camera.get(4)
        
        # 카메라의 정보 출력
        self.printCameraInformation()

        # 카메라 현재 상태
        self.camera_status = self.camera.isOpened()

        # 현재 재접속 시도 중인지 여부 (상태 체크용)
        self.check_reconnect = False

        # 영상을 불러올 수 없는 경우
        if(not self.camera_status):
            print("영상 파일이 지정되지 않았거나 잘못된 영상 형식입니다.")
            self.loop = False # 반복 재생을 False로 설정 (없는 영상을 계속 불러오는 걸 방지)

    # 카메라 재접속 (연결이 끊겨있을 때만 사용 가능)
    def reconnect(self):
        self.check_reconnect = True
        if(not self.isOpened()):
            self.dispose()
            self.__open__()
        self.check_reconnect = False
        
    # 카메라로부터 영상을 1 프레임 읽어들임
    def get_frame(self):
        self.read_lock.acquire()
        ret, frame = self.camera.read()
        self.read_lock.release()
        if(ret == False or frame is None):
            if(self.loop):
                print("비디오 영상이 종료되었으므로 다시 재생합니다.")
                self.read_lock.acquire()
                self.camera.release()
                self.camera = cv2.VideoCapture(self.video_file)
                ret, frame = self.camera.read()
                self.read_lock.release()
            else:
                print("비디오 영상이 종료되었습니다.")
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
            print("영상이 종료되어 정보를 가져올 수 없습니다.")
            return
        
        # 카메라 정보 출력
        print("영상 파일 정보 : ")
        print("Video File Name : {0}".format(self.video_file))
        print("Video Width : {0}".format(self.camera.get(3)))
        print("Video Height : {0}".format(self.camera.get(4)))