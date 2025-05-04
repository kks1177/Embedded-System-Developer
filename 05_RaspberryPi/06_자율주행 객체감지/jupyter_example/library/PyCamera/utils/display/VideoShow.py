import cv2
import threading
import queue
import time

# 영상을 디스플레이하는 클래스
class VideoShow():
    def __init__(self, view_mode="autosize"):
        self.frame_list = {}
        self.event_list = {}
        self.display_options_list = {}
        self.display_thread = None

        self.is_running = False
        self.view_mode = view_mode

        # 주의 : 쓰레드를 2번 호출했을 때부터는 OpenCV의 imshow를 더 이상 사용할 수 없으니 반드시 쓰레드를 유지시켜야 함
        self.display_thread = threading.Thread(target=self.__display_show__)
        self.display_thread.daemon = True
        self.display_thread.start()

    def start(self):
        if(not self.is_running):
            self.is_running = True
        return self
    
    def stop(self):
        if(self.is_running):
            self.is_running = False
    
    def update(self, name, frame):
        if(name not in self.frame_list.keys()):
            self.frame_list[name] = queue.Queue(maxsize=1)
            self.event_list[name] = None
            self.display_options_list[name] = (True, "autosize") # isChanged, mode name
        
        self.frame_list[name].put(frame)

    def registerCamera(self, name, camera):
        if(name not in self.frame_list.keys()):
            self.frame_list[name] = queue.Queue(maxsize=1)
            self.event_list[name] = None
            self.display_options_list[name] = (True, "autosize") # isChanged, mode name
        if(hasattr(camera, "get_frame")):
            self.event_list[name] = camera

    def unregisterCamera(self, name):
        if(name in self.event_list.keys()):
            self.event_list[name] = None
    
    def __display_show__(self):
        current_mode = None
        while(True):
            while(self.is_running):
                frames = self.frame_list.copy()
                events = self.event_list.copy()
                for key, value in frames.items():
                    try:
                        frame = None
                        # 해당 name에 카메라로부터 영상을 받아오도록 등록되어있는 경우
                        if(key in events.keys() and events[key] is not None):
                            frame = events[key].get_frame() if events[key].isOpened() else None
                        elif(not value.empty()):
                            frame = value.get()

                        if(self.display_options_list[key][0] == False):
                            view_mode = self.display_options_list[key][1]
                            cv2.namedWindow(key, cv2.WINDOW_NORMAL)
                            cv2.destroyWindow(key)
                            if(view_mode == "fullscreen"):
                                cv2.namedWindow(key, cv2.WINDOW_NORMAL)
                                cv2.setWindowProperty(key, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
                            elif(view_mode == "autosize"):
                                cv2.namedWindow(key, cv2.WINDOW_AUTOSIZE)
                                cv2.setWindowProperty(key, cv2.WND_PROP_FULLSCREEN, 0)
                            elif(view_mode == "normal"):
                                cv2.namedWindow(key, cv2.WINDOW_NORMAL)
                                cv2.setWindowProperty(key, cv2.WND_PROP_FULLSCREEN, 0)
                            self.display_options_list[key] = (True, self.display_options_list[key][1])
                
                        if(frame is not None):
                            cv2.imshow(key, frame)
                        
                    except Exception as e:
                        import traceback
                        traceback.print_exc()
                        print(e)
                
                cv2.waitKey(1)

            frames = self.frame_list.copy()
            for key, value in frames.items():
                try:
                    if(cv2.getWindowProperty(key, 0) >= 0):
                        cv2.destroyWindow(key)
                except cv2.error:
                    pass
            time.sleep(0.5)

    def setViewMode(self, name, mode):
        if(name in self.display_options_list.keys() and self.display_options_list[name][1] != mode):
            self.display_options_list[name] = (False, mode)
        if(name not in self.display_options_list.keys()):
            self.frame_list[name] = queue.Queue(maxsize=1)
            self.event_list[name] = None
            self.display_options_list[name] = (False, mode) # isChanged, mode name
    
    def __enter__(self):
        self.start()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.stop()
