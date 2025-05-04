import cv2
import threading
import queue
import time

from numpy.core.numeric import full
from . import VideoShow

import numpy as np
from ..Utility import *

# 영상을 디스플레이하는 클래스
class MultipleVideoShow():
    # size : 한 화면에 대한 해상도 (너비 x 높이)
    # channel : 채널 종류 (3채널 고정)
    # view_size : 최대 몇 개의 화면을 보여줄 지 (열 x 행)
    # use_padding : 한 화면에 보여줄 이미지에 대하여 리사이즈를 할 때 위아래 padding을 추가할 지 여부
    # view_mode : 디스플레이 방법
    #  - autosize : 화면 크기에 맞게 자동으로 창 크기가 조정됨 (기본값)
    #  - normal : 사용자가 수동으로 창 크기를 조절할 수 있음
    #  - fullscreen : 풀스크린 모드
    def __init__(self, size=(640, 360), channel=3, view_size=(3, 2), use_padding=False, use_autoreconnect=False, view_mode="autosize"):
        self.size = size
        self.channel = channel
        self.view_size = view_size
        self.use_padding = use_padding
        self.use_autoreconnect = use_autoreconnect
        self.view_mode = view_mode
        self.canvas = np.zeros((self.size[1] * self.view_size[0], self.size[0] * self.view_size[1], self.channel), dtype=np.uint8)

        self.frame_list = {}
        self.event_list = {}
        self.display_thread = None

        self.is_running = False

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

    # 숫자형인지 확인
    def checkInteger(self, s):
        try:
            int(s)
            return True
        except ValueError:
            return False
            
    def update(self, index, frame):
        if(not self.checkInteger(index)):
            return

        index = int(index)
        if(index not in self.frame_list.keys()):
            self.frame_list[index] = queue.Queue(maxsize=1)
            self.event_list[index] = None
        
        self.frame_list[index].put(frame)

    def registerCamera(self, index, camera):
        if(not self.checkInteger(index)):
            return

        index = int(index)
        if(0 > index or index >= self.view_size[0] * self.view_size[1]):
            return
        
        if(index not in self.frame_list.keys()):
            self.frame_list[index] = queue.Queue(maxsize=1)
            self.event_list[index] = None
        if(hasattr(camera, "get_frame")):
            self.event_list[index] = camera

    def unregisterCamera(self, index):
        if(index in self.event_list.keys()):
            self.event_list[index] = None
    
    def preprocess(self, frame, size):
        if(self.use_padding):
            # if(size[1] > size[0]):
            #     frame = resize_keep_ratio(frame, height=size[1])
            # else:
            #     frame = resize_keep_ratio(frame, width=size[0])
            frame = resize_keep_ratio(frame, width=size[0])
            frame = addPadding(frame, background_color=(0, 0, 0))
            return cv2.resize(frame, size)
        else:
            return cv2.resize(frame, size)
    
    def setSize(self, size):
        self.size = size

    def setViewSize(self, vsize):
        self.view_size = vsize
    
    def setViewMode(self, mode):
        self.view_mode = mode
    
    def setPadding(self, value):
        self.use_padding = value
    
    def get_frame(self):
        return self.canvas
    
    def isOpened(self):
        return self.is_running

    def __display_show__(self):
        current_mode = None
        while(True):
            while(self.is_running):
                # size가 변경된 경우를 대비
                size = self.size
                vsize = self.view_size
                if(
                    self.canvas.shape[0] != size[1] * vsize[0] or 
                    self.canvas.shape[1] != size[0] * vsize[1]
                ):
                    self.canvas = np.zeros((size[1] * vsize[0], size[0] * vsize[1], self.channel), dtype=np.uint8)
                    print(self.canvas.shape)
                
                frames = self.frame_list.copy()
                events = self.event_list.copy()
                for key, value in frames.items():
                    # 할당 가능한 화면 번호가 없을 경우
                    if(0 > key or key >= vsize[0] * vsize[1]):
                        continue
                    try:
                        frame = None
                        # 해당 name에 카메라로부터 영상을 받아오도록 등록되어있는 경우
                        if(key in events.keys() and events[key] is not None):
                            if events[key].isOpened():
                                frame = events[key].get_frame()
                            else:
                                if(self.use_autoreconnect and events[key].check_reconnect == False):
                                    threading.Thread(target=events[key].reconnect, daemon=True).start()
                                frame = None
                        elif(not value.empty()):
                            frame = value.get()
                        if(frame is not None):
                            row_index = int(key % vsize[1])
                            col_index = int(key / vsize[1])
                            self.canvas[
                                size[1] * col_index : size[1] * (col_index + 1),
                                size[0] * row_index : size[0] * (row_index + 1)
                            ] = self.preprocess(frame, size)
                    except Exception as e:
                        import traceback
                        traceback.print_exc()
                        print(e)
                
                if(current_mode != self.view_mode):
                    current_mode = self.view_mode
                    cv2.namedWindow("MultiView", cv2.WINDOW_NORMAL)
                    cv2.destroyWindow("MultiView")
                    if(self.view_mode == "fullscreen"):
                        cv2.namedWindow("MultiView", cv2.WINDOW_NORMAL)
                        cv2.setWindowProperty("MultiView", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
                    elif(self.view_mode == "autosize"):
                        cv2.namedWindow("MultiView", cv2.WINDOW_AUTOSIZE)
                        cv2.setWindowProperty("MultiView", cv2.WND_PROP_FULLSCREEN, 0)
                    elif(self.view_mode == "normal"):
                        cv2.namedWindow("MultiView", cv2.WINDOW_NORMAL)
                        cv2.setWindowProperty("MultiView", cv2.WND_PROP_FULLSCREEN, 0)
        
                cv2.imshow("MultiView", self.canvas)
                cv2.waitKey(1)
            time.sleep(0.5)

    def __enter__(self):
        self.start()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.stop()
