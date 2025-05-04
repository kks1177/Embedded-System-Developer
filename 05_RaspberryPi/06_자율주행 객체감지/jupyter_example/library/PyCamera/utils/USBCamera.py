import cv2
import platform
from .PyCamera import PyCamera
from .Utility import *

# USB 카메라로부터 프레임을 가져오는 클래스 (GStreamer 미테스트)
class USBCamera(PyCamera):
    # camera_index : 카메라 포트 번호
    # width : 카메라 영상 너비 설정
    # height : 카메라 영상 높이 설정
    # DSHOW_OPTION : 카메라로부터 캡처 시 사용할 백엔드를 지정
    def __init__(self, camera_index=None, camera_width=None, camera_height=None, DSHOW_OPTION=False):
        super(USBCamera, self).__init__()

        if(camera_index == None):
            raise Exception("Camera 번호가 지정되지 않았습니다.")

        self.camera_index = camera_index
        self.camera_width = camera_width
        self.camera_height = camera_height
        self.USE_DSHOW_OPTION = DSHOW_OPTION

        self.__open__()
    
    def __open__(self):
        # OpenCV 버전 확인
        # cv2_version_info = (cv2.__version__).split('.')
        cv2_version_info = getOpenCV_Version()[:3]
        (major_ver, minor_ver, subminor_ver) = [int(i) for i in cv2_version_info]

        # cv2.CAP_DSHOW 옵션 사용 여부
        cv2_index = int(self.camera_index) + cv2.CAP_DSHOW if self.USE_DSHOW_OPTION else int(self.camera_index)
        
        # OpenCV 3.4.3 이하는 VideoCapture에서 두 개 이상의 인자를 지정하지 못함 (apipreference를 지원하지 않음)
        # Jetson에서 apt-get으로 opencv를 설치하면 3.2.0 버전이 설치된다.
        if(major_ver <= 3 and minor_ver <= 4 and subminor_ver <= 3):
            self.camera = cv2.VideoCapture(cv2_index + (cv2.CAP_ANY if platform.system() != "Linux" else cv2.CAP_V4L2))
        else:
            self.camera = cv2.VideoCapture(cv2_index, cv2.CAP_ANY if platform.system() != "Linux" else cv2.CAP_V4L2)

        # 명시적으로 너비 혹은 높이를 지정했을 때 아래와 같이 수동으로 카메라 설정을 조작
        if(self.camera_width is not None):
            self.camera.set(3, self.camera_width)
        if(self.camera_height is not None):
            self.camera.set(4, self.camera_height)

        # if(self.camera.isOpened()):
        #     self.camera_width = self.camera.get(3)
        #     self.camera_height = self.camera.get(4)
        
        # 카메라의 정보 출력
        self.printCameraInformation()

        # 카메라 현재 상태 (포트가 겹치면 cv2.isOpened 함수로 판단할 수 없기 때문에 1프레임을 읽어와서 현재 상태(self.camera_status)를 갱신하도록 한다.)
        self.get_frame()

        # 현재 재접속 시도 중인지 여부 (상태 체크용)
        self.check_reconnect = False

    # 카메라 재접속 (연결이 끊겨있을 때만 사용 가능)
    def reconnect(self):
        self.check_reconnect = True
        if(not self.isOpened()):
            self.dispose()
            self.__open__()
        self.check_reconnect = False
    
    def printCameraInformation(self):
        # 카메라 유효값 체크
        if(not self.camera.isOpened()):
            print("Camera 연결이 종료되어 정보를 가져올 수 없습니다.")
            return
        
        # 카메라 정보 출력
        print("카메라 정보  : ")
        if(self.USE_DSHOW_OPTION):
            print("Camera Index : {0}".format(int(self.camera_index) + cv2.CAP_DSHOW))
        else:
            print("Camera Index : {0}".format(int(self.camera_index)))

        print("Camera Width : {0}".format(self.camera.get(3)))
        print("Camera Height : {0}".format(self.camera.get(4)))
        print("DSHOW_OPTION : {0}".format(self.USE_DSHOW_OPTION))
