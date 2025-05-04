import cv2
import threading
import os
import time
import datetime

# 영상을 녹화하는 클래스
class CameraRecorder():
    recordStarted = False
    frame_rate = 30
    saveVideoDir = None

    # camera : 카메라 클래스
    # frame_rate : 카메라 영상으로부터 프레임을 추출할 때 지정
    # record_time : 녹화할 시간 (0 혹은 None이면 중단 없음)
    # save_dir : 추출한 프레임을 저장할 위치
    # display_show : 녹화 시 모니터 화면에 영상을 표시할 지 여부
    def __init__(self, camera, frame_rate=30, record_time=0, save_dir=None, video_format="mp4", display_show=True):
        self.current_class = camera.__class__
        self.base_class = camera.__class__.__base__
        self.camera = camera
        self.frame_rate = frame_rate
        self.record_time = record_time
        self.video_format = video_format
        self.display_show = display_show
        # 쓰레드 Lock
        self._record_func_lock_ = threading.Lock()

        self.fourcc = self.getVideoFormat(video_format)
        if(self.fourcc is None):
            raise Exception("지원하지 않는 영상 포맷입니다.")

        # # 해당 Camera 클래스가 PyCamera 클래스를 상속 받는 지 확인
        # if(self.base_class == None or self.base_class.__name__ != "PyCamera"):
        #     raise Exception("잘못된 PyCamera 형식입니다.")
        # if(self.current_class.__name__ == "ImagesReader"):
        #     raise Exception("ImagesReader 클래스는 Camera_Recorder 인스턴스를 생성할 수 없습니다.")

        if(not hasattr(camera, "get_frame")):
            raise Exception("잘못된 PyCamera 형식입니다.")
        
        if(save_dir == None):
            save_dir = "./record"
        self.save_dir = save_dir
        self.last_save_record_file = None

        os.makedirs(save_dir, exist_ok=True)
    
    def getVideoFormat(self, video_format="mp4"):
        if(video_format == "avi"):
            return cv2.VideoWriter_fourcc(*'XVID')
        if(video_format == "mp4"):
            return cv2.VideoWriter_fourcc('m','p','4','v')
        return None
        
    def setFrameRate(self, frame_rate):
        self.frame_rate = frame_rate
    
    def setRecordTime(self, record_time):
        self.record_time = record_time
    
    def getLastRecordFile(self):
        return self.last_save_record_file
    
    def start(self):
        self._record_func_lock_.acquire()
        if(self.recordStarted):
            self._record_func_lock_.release()
            return
        
        if(self.video_format == "avi"):
            file_name =  str(datetime.datetime.now().strftime("%Y-%m-%d_%H%M%S_video.avi"))
        elif(self.video_format == "mp4"):
            file_name =  str(datetime.datetime.now().strftime("%Y-%m-%d_%H%M%S_video.mp4"))
        else:
            print("지원하지 않는 영상 포맷입니다.")
            self._record_func_lock_.release()
            return

        self.last_save_record_file = save_file_name = os.path.join(self.save_dir, file_name)
        videoWriter = cv2.VideoWriter(save_file_name, self.fourcc, self.frame_rate, self.camera.getResolution())
        self.recordStarted = True
        self._record_func_lock_.release()

        last_record_time = time.time()
        while(self.recordStarted and (time.time() - last_record_time < self.record_time or self.record_time in [None, 0])):
            frame = self.camera.get_frame()
            if(frame is None):
                break
            videoWriter.write(frame)

            if(self.display_show):
                cv2.imshow("Video Recorder", frame)
            
            waitKey = cv2.waitKey(1)
            if waitKey == ord('q'):
                break
        
        videoWriter.release()
        cv2.destroyAllWindows()
        self.recordStarted = False

    def start_async(self):
        if(self.recordStarted):
            print("이미 프레임을 추출하고 있습니다.")

        self.extract_thread = threading.Thread(target=self.start)
        self.extract_thread.daemon = True
        self.extract_thread.start()
    
    def stop_async(self):
        self.recordStarted = False
        self.extract_thread = None
