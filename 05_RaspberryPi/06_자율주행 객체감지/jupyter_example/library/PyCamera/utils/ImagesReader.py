import os
import glob
import random
from .PyCamera import PyCamera
from .Utility import *

# 폴더 내 이미지를 읽어오는 클래스
class ImagesReader(PyCamera):
    # image_dir : 이미지가 위치한 폴더
    # ext : 어떤 확장자를 가지는 이미지만 읽어들일 지
    # shufflt : 이미지를 무작위로 섞어 가져오고 싶으면 True
    # loop : 더 이상 검색할 이미지가 없을 때 다시 처음부터 읽어들일 지 여부
    def __init__(self, image_dir=None, ext=["png", "jpg", "gif"], shuffle=False, loop=True):
        super(ImagesReader, self).__init__()

        if(image_dir == None):
            raise Exception("이미지가 저장된 폴더가 지정되지 않았습니다.")
        if(not os.path.isdir(image_dir)):
            raise Exception("해당 폴더는 존재하지 않는 경로입니다.")

        self.image_dir = image_dir
        self.image_ext = ext
        self.image_list = []
        self.image_index = 0
        self.shuffle = shuffle
        self.loop = loop

        # 이미지 파일 목록을 가져온다.
        for e in ext:
            self.image_list += glob.glob(self.image_dir + '/*.' + e)
        
        # 이미지를 랜덤으로 섞을 지 여부
        if(self.shuffle):
            random.shuffle(self.image_list)
        
        # 이미지의 총 개수
        self.image_count = len(self.image_list)

        # 폴더의 정보 출력
        self.printCameraInformation()

        # 현재 상태
        self.camera_status = self.image_count > 0

        # 현재 재접속 시도 중인지 여부 (상태 체크용)
        self.check_reconnect = False

    def reconnect(self):
        pass

    # 이미지 1개를 가져옴 (파일명도 같이 반환)
    def get_frame(self):
        while(True):
            # 더 이상 검색할 이미지가 없을 때
            if(self.image_index >= self.image_count):
                # 검색할 이미지가 아예 없을 때
                if(self.image_count == 0):
                    print("검색할 이미지가 더 이상 없습니다.")
                    self.camera_status = False
                    return (None, None)
                if(self.loop):
                    print("검색할 이미지가 더 이상 없습니다. 이미지를 다시 검색합니다.")
                    self.refreshSearch(printInfo=False)
                    continue
                else:
                    print("검색할 이미지가 더 이상 없습니다.")
                    self.camera_status = False
                    return (None, None)

            # 검색할 이미지의 경로
            image_file_path = self.image_list[self.image_index]

            # 해당 이미지가 존재하지 않는 경우 무시하고 다음 이미지를 검색함
            if(not os.path.isfile(image_file_path)):
                self.image_index += 1
                continue

            frame = imread(image_file_path)
            
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
            
            self.image_index += 1

            self.camera_status = True

            return ([image_file_path, frame.shape[1], frame.shape[0]], frame)
    
    # 폴더 내 이미지를 재검색합니다. (index는 0으로 초기화됩니다.)
    def refreshSearch(self, shuffle=None, printInfo=True):
        self.image_list = []
        self.image_index = 0

        # 이미지 파일 목록을 가져온다.
        for e in self.image_ext:
            self.image_list += glob.glob(self.image_dir + '/*.' + e)
        
        if(shuffle == True or (shuffle is None and self.shuffle)):
            random.shuffle(self.image_list)

        # 이미지의 총 개수
        self.image_count = len(self.image_list)

        # 폴더의 정보 출력
        if(printInfo):
            self.printCameraInformation()

    def printCameraInformation(self):
        # 폴더 정보 출력
        print("폴더 정보  : ")
        print("Directory Path : {0}".format(self.image_dir))
        print("Image Count : {0}".format(self.image_count))
    
    # 폴더 정보 초기화
    def dispose(self):
        self.image_list = []
        self.image_count = 0
        self.camera_status = False
