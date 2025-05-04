import cv2
import threading
import os
import time
import datetime
from .Utility import *

# 카메라 영상으로부터 프레임 추출하기
class Camera_Frame_Extractor():
    frame_unit_sec = None
    save_index = 0
    save_dir = None
    is_run_extract = False
    extract_thread = None

    # camera : 카메라 클래스
    # fps : 카메라 영상으로부터 프레임을 추출할 때 지정
    # save_dir : 추출한 프레임을 저장할 위치
    def __init__(self, camera, frame_unit_sec=0.2, save_dir=None):
        self.current_class = camera.__class__
        self.base_class = camera.__class__.__base__

        # # 해당 Camera 클래스가 PyCamera 클래스를 상속 받는 지 확인
        # if(self.base_class == None or self.base_class.__name__ != "PyCamera"):
        #     raise Exception("잘못된 PyCamera 형식입니다.")
        # if(self.current_class.__name__ == "ImagesReader"):
        #     raise Exception("ImagesReader 클래스는 Camera_Recorder 인스턴스를 생성할 수 없습니다.")

        if(not hasattr(camera, "get_frame")):
            raise Exception("잘못된 PyCamera 형식입니다.")
        
        self.camera = camera
        self.frame_unit_sec = frame_unit_sec
        self.save_dir = save_dir
        self.current_time = datetime.datetime.now()
    
    # 몇 초(second)마다 Frame을 가져올 지 설정합니다.
    def setUnitsSecond(self, frame_unit_sec):
        self.frame_unit_sec = frame_unit_sec
    
    # Frame을 저장할 경로를 지정합니다.
    def setSavePath(self, save_dir):
        self.save_dir = save_dir
    
    # Frame 저장 (클래스 내부에서 처리)
    def save_frame(self, frame):
        file_name = str(self.current_time.strftime("%Y-%m-%d_%H%M%S_{0:08d}.jpg".format(self.save_index)))
        
        imwrite(os.path.join(self.save_dir, file_name), frame)
        self.save_index += 1

    # 프레임 추출 시작
    # max_save : 추출할 최대 프레임 개수 (0일 경우 무한 반복)
    def start(self, max_save=100, display=False):
        self.is_run_extract = True

        if(self.save_dir == None):
            print("추출된 프레임을 저장할 경로가 지정되지 않았습니다.")
            return
        if(not os.path.isdir(self.save_dir)):
            os.makedirs(self.save_dir)
            print("추출된 프레임을 저장할 경로가 지정되지 않아 폴더를 새로 생성하였습니다.")
        
        self.save_index = 0
        self.current_time = datetime.datetime.now()

        if(self.camera.__class__.__name__ == "VideoCamera"):
            # 초당 프레임 가져오기
            fps = self.camera.camera.get(cv2.CAP_PROP_FPS) # Gets the frames per second
            multiplier = fps * self.frame_unit_sec
            # 동영상이 끝날 때까지 프레임 추출을 반복
            while((self.save_index < max_save or max_save == 0) and self.is_run_extract):
                frameId = int(round(self.camera.camera.get(1))) #current frame number
                frame = self.camera.get_frame()
                if frame is None:
                    break
                if frameId % multiplier < 1:
                    # 프레임 저장
                    frame = self.camera.get_frame()
                    self.save_frame(frame)
                if(display):
                    cv2.imshow("test", frame)
                    cv2.waitKey(1)
        else:
            check_time = 0
            while((self.save_index < max_save or max_save == 0) and self.is_run_extract):
                if(time.time() - check_time > self.frame_unit_sec):
                    check_time = time.time()
                    frame = self.camera.get_frame()
                    # 프레임 저장
                    self.save_frame(frame)
                if(display):
                    cv2.imshow("test", frame)
                    cv2.waitKey(1)
        
        print("프레임 추출이 종료되었습니다.")
        print("총 프레임 수 : {0}장".format(self.save_index))
        
        cv2.destroyAllWindows()
        self.is_run_extract = False
    
    # 비동기로 프레임 추출 시작
    # max_save : 추출할 최대 프레임 개수 (0일 경우 무한 반복)
    def start_async(self, max_save=100):
        if(self.is_run_extract):
            print("이미 프레임을 추출하고 있습니다.")
        # 지연 문제 방지를 위해 이미지 읽기는 별도의 쓰레드에서 돌아가도록 설정함
        self.extract_thread = threading.Thread(target=self.start, args=(max_save,))
        self.extract_thread.daemon = True
        self.extract_thread.start()
    
    # 프레임 추출 종료 (비동기일 경우 사용)
    # max_save : 추출할 최대 프레임 개수 (0일 경우 무한 반복)
    def stop_async(self, max_save=100):
        self.is_run_extract = False
        self.extract_thread = None