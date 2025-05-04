import cv2

# with 구문 사용 가능하도록 함

class VideoWriter(cv2.VideoWriter):
    def __enter__(self):
        return self
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.release()
