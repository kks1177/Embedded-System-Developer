import cv2
import numpy as np

# with 구문 사용 가능하도록 함

class VideoCapture(cv2.VideoCapture):
    def __enter__(self):
        return self
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.release()
    def __iter__(self):
        noread = (False, None)
        if self.isOpened():
            for _, frame in iter(self.read, noread):
                yield frame
