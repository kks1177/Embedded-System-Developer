import cv2
import os
import platform
import subprocess
from .PyCamera import PyCamera
from .Utility import *

# Gstreamer 카메라
class GSTCamera(PyCamera):
    # 주의 : OpenCV가 GStreamer가 지원되어야만 사용 가능함
    # camera_index : 카메라 포트 번호
    # camera_width : 카메라 영상 너비 설정
    # camera_height : 카메라 영상 높이 설정
    # display_width : 디스플레이될 영상 너비 설정
    # display_height : 디스플레이될 영상 높이 설정
    # framerate : Frame rate 설정 (지원하지 않는 Frame rate 혹은 해상도일 경우 영상을 읽어오지 못하니 주의)
    # flip_method : 이미지 좌우 반전 옵션 (GStreamer 관련 문서 참고)
    # interpolation_method : 이미지 리사이즈 옵션 (GStreamer 관련 문서 참고)
    # is_csicamera : 라즈베리파이 카메라와 같은 임베디드 장치일 경우 선택
    def __init__(
        self,
        camera_index=None,
        camera_width=None,
        camera_height=None,
        display_width=None,
        display_height=None,
        framerate=None,
        flip_method=0,
        interpolation_method=4,
        is_csicamera=False
    ):
        super(GSTCamera, self).__init__()

        if(camera_index == None):
            raise Exception("Camera 번호가 지정되지 않았습니다.")
            
        self.camera_index = camera_index
        self.camera_width = camera_width
        self.camera_height = camera_height
        self.display_width = display_width
        self.display_height = display_height
        self.framerate = framerate
        self.flip_method = flip_method
        self.interpolation_method = interpolation_method
        self.is_csicamera = is_csicamera
        self.camera_source = None

        self.__open__()

    def __open__(self):
        # OpenCV 버전 확인
        # cv2_version_info = (cv2.__version__).split('.')
        cv2_version_info = getOpenCV_Version()[:3]
        (major_ver, minor_ver, subminor_ver) = [int(i) for i in cv2_version_info]

        # opencv camera index
        cv2_index = int(self.camera_index)

        # OpenCV에서 GStreamer 지원 여부 확인
        info = cv2.getBuildInformation()
        info_gst_support = [line for line in info.split('\n') if 'GStreamer' in line][0]
        is_gst_support = (info_gst_support.find("YES") != -1)

        # OpenCV에서 GStreamer 지원을 안 할 경우 index를 VideoCapture에 그냥 넣어줌
        if(not is_gst_support):
            print("현재 설치되어 있는 OpenCV는 GStreamer를 지원하지 않습니다. 일부 설정이 제한될 수 있습니다.")
            self.camera = cv2.VideoCapture(cv2_index)
            # 명시적으로 너비 혹은 높이를 지정했을 때 아래와 같이 수동으로 카메라 설정을 조작
            if(self.camera_width is not None):
                self.camera.set(3, self.camera_width)
            if(self.camera_height is not None):
                self.camera.set(4, self.camera_height)
        else:
            # OS 정보 가져오기
            os_name = self.getOSName()
            # PC에서는 CSI 카메라를 지원하지 않으므로 예외처리
            if(self.is_csicamera and os_name in ["windows", "ubuntu"]):
                raise Exception("PC에서는 CSI 카메라를 지원하지 않습니다. (Windows, Ubuntu)")

            self.camera_source = self.gstreamer_pipeline(
                cv2_index,
                self.camera_width,
                self.camera_height,
                self.display_width,
                self.display_height,
                self.framerate,
                self.flip_method,
                self.interpolation_method,
                self.is_csicamera,
                os_name
            )
            self.camera = cv2.VideoCapture(self.camera_source, cv2.CAP_GSTREAMER)

        # 카메라 현재 상태 (포트가 겹치면 cv2.isOpened 함수로 판단할 수 없기 때문에 1프레임을 읽어와서 현재 상태(self.camera_status)를 갱신하도록 한다.)
        self.get_frame()

        # 카메라 연결이 되어있지 않은 경우
        if(not self.camera_status):
            print("카메라 장치에서 이미지를 받아올 수 없습니다.")
            print("카메라 장치가 연결되지 않았거나 카메라에서 지원하지 않는 해상도/프레임 레이트일 수도 있습니다.")
            print("현재 사이즈 : {0}x{1}".format(self.camera_width, self.camera_height))
            print("현재 프레임 레이트 : {0}".format(self.framerate))
            print("GStreamer 소스 : {0}".format(self.camera_source))
            return

        # self.camera_width = self.camera.get(3)
        # self.camera_height = self.camera.get(4)
        
        # 카메라의 정보 출력
        self.printCameraInformation()

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
        if(self.camera_source is None):
            print("Camera Index : {0}".format(int(self.camera_index)))
        else:
            print("Camera Source : {0}".format(self.camera_source))

        print("Camera Width : {0}".format(self.camera.get(3)))
        print("Camera Height : {0}".format(self.camera.get(4)))

    def getOSName(self):
        os_info = None

        if (platform.system() == "Linux"):
            # if [ `uname -m` == \"aarch64\" ] && [ -f /proc/device-tree/model ] && [ `tail /proc/device-tree/model | grep -ic \".*jetson.*\"` > 0 ]; then echo true; fi
            uname = subprocess.Popen("uname -m", shell=True, stdout=subprocess.PIPE).stdout.read().decode('utf-8').strip()
            is_device = os.path.isfile("/proc/device-tree/model")

            if(uname == "aarch64" and is_device):
                with open("/proc/device-tree/model", "r") as f:
                    contents = f.read()
                    if(contents.lower().find("jetson") != -1):
                        os_info = "jetson"
                    elif(contents.lower().find("raspberry") != -1):
                        os_info = "raspberry"
                    else:
                        os_info = "unknown_device"
            else:
                os_info = "ubuntu"
        
        elif(platform.system() == "Windows"):
            os_info="windows"
        
        return os_info

    def gstreamer_pipeline(
        self,
        camera_index=0,
        camera_width=None,
        camera_height=None,
        display_width=None,
        display_height=None,
        framerate=None,
        flip_method=0,
        interpolation_method=4,
        is_csicamera=False,
        os_name=""
    ):
        # jetson interpolation method)
        # Nearest: 0(Default), Bilinear: 1, 5-tap: 2, 10-tap: 3, Smart: 4, Nicest=5

        # rpi interpolation method)
        # Nearest-neighbour: 0(Default), Bilinear: 1, 4-tap: 2, lanczos: 3, bilinear2: 4, sinc: 5, hermite: 6, spline: 7, catrom: 8, mitchell: 9

        # NVMM(3264x2464)에서 CPU로 이미지(1280x720)를 보냄
        if(os_name == "jetson"):
            if(is_csicamera):
                # default value
                camera_width = 3264 if(camera_width == None) else camera_width
                camera_height = 2464 if(camera_height == None) else camera_height
                display_width = 1280 if(display_width == None) else display_width
                display_height = 720 if(display_height == None) else display_height
                framerate = 30 if(framerate == None) else framerate

                return (
                    "nvarguscamerasrc sensor-id=%d ! "
                    "video/x-raw(memory:NVMM),"
                    "width=(int)%d, height=(int)%d, "
                    "format=(string)NV12, framerate=(fraction)%d/1 ! "
                    "nvvidconv flip-method=%d interpolation-method=%d ! "
                    "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGRx ! "
                    "videoconvert ! "
                    "video/x-raw, format=(string)BGR ! appsink"
                    % (
                        camera_index,
                        camera_width,
                        camera_height,
                        framerate,
                        flip_method,
                        interpolation_method,
                        display_width,
                        display_height
                    )
                )
            else:
                # default value
                camera_width = 1280 if(camera_width == None) else camera_width
                camera_height = 720 if(camera_height == None) else camera_height
                framerate = None if(framerate == None) else framerate

                return (
                    "v4l2src device=/dev/video%s ! "
                    "video/x-raw,"
                    "width=(int)%d, height=(int)%d"
                    "%s ! "
                    "videoflip method=%d ! videoscale method=%d ! "
                    "videoconvert ! "
                    "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGR ! appsink"
                    % (
                        camera_index,
                        camera_width,
                        camera_height,
                        "" if framerate is None else "framerate=(fraction){0}/1 ! ".format(framerate),
                        flip_method,
                        interpolation_method,
                        display_width,
                        display_height
                    )
                )
                
        # if(os_name == "raspberry"):
        #     return (
        #         "v4l2src device=/dev/video%s ! "
        #         "video/x-raw,"
        #         "width=(int)%d, height=(int)%d, "
        #         "framerate=(fraction)%d/1 ! "
        #         "videoflip method=%d ! videoscale method=%d ! "
        #         "videoconvert ! "
        #         "video/x-raw, format=(string)BGR ! appsink"
        #     )

        if(os_name == "windows"):
            # window에서 1280x720 해상도, 30fps 설정 시 오류 발생 (단, frame rate를 지정 안 하면 오류가 생기지 않았음)
            return (
                "ksvideosrc device-index=%d ! "
                "video/x-raw,"
                "width=(int)%d, height=(int)%d"
                "%s ! "
                "videoflip method=%d ! videoscale method=%d ! "
                "videoconvert ! "
                "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGR ! appsink"
                % (
                    camera_index,
                    camera_width,
                    camera_height,
                    "" if framerate is None else "framerate=(fraction){0}/1 ! ".format(framerate),
                    flip_method,
                    interpolation_method,
                    display_width,
                    display_height
                )
            )
        else:
            raise Exception("지원되지 않는 OS입니다.")
        

