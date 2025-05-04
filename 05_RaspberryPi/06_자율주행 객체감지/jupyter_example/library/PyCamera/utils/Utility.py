import cv2
import math
import os
import re
import sys
import numpy as np
import traceback
import urllib.request

# 파이썬 버전을 Tuple 형태로 가져옴
def getPythonVersion():
    return sys.version_info[:3]

# OpenCV 버전을 Tuple 형태로 가져옴
def getOpenCV_Version():
    if(hasattr(cv2, "version")):
        version_str = cv2.version.opencv_version.split('.')
    else:
        version_str = cv2.__version__.split('.')

    version_str = tuple(map(lambda x: re.sub("[^0-9]", "", x), version_str))

    return version_str

# base64 인코딩
def base64Encoding(image):
    import base64
    buffer = cv2.imencode('.jpg', image)[1]
    return base64.b64encode(buffer)

# base64 디코딩
def base64Decoding(text):
    import base64
    buffer = base64.b64decode(text)
    image_np = np.frombuffer(buffer, dtype=np.uint8)
    return cv2.imdecode(image_np, flags=1)

# 이미지를 1:1 비율에 맞게 Padding을 넣음
def addPadding(image=None, background_color=(0, 0, 0)):
    try:
        __original_height__, __original_width__, __channel__ = image.shape
        __borderType__ = cv2.BORDER_CONSTANT
        if(__original_height__ > __original_width__):
            __left__ = math.ceil((__original_height__ - __original_width__) / 2)
            __right__ = math.floor((__original_height__ - __original_width__) / 2)
            __top__, __bottom__ = (0, 0)
        elif(__original_height__ < __original_width__):
            __top__ = math.ceil((__original_width__ - __original_height__) / 2)
            __bottom__ = math.floor((__original_width__ - __original_height__) / 2)
            __left__, __right__ = (0, 0)
        return cv2.copyMakeBorder(image, __top__, __bottom__, __left__, __right__, __borderType__, None, background_color)
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# OpenCV2 이미지 읽기(Read)/쓰기(Write) - 한글 경로에 있는 것도 읽어들일 수 있음
def imread(filename, flags=cv2.IMREAD_COLOR, dtype=np.uint8):
    try:
        n = np.fromfile(filename, dtype)
        img = cv2.imdecode(n, flags)
        return img
    except Exception as e:
        print("[Error] 이미지 파일을 읽어들일 수 없습니다. (None 값 반환됨)")
        print("=> 파일명 : '{0}'".format(filename))
        return None

def imwrite(filename, img, params=None):
    try:
        dirName = os.path.dirname(filename)
        dirName = dirName if dirName != "" else "."
        if(not os.path.isdir(dirName)):
            os.makedirs(dirName)

        ext = os.path.splitext(filename)[1]
        result, n = cv2.imencode(ext, img, params)
        if result:
            with open(filename, mode='w+b') as f:
                n.tofile(f)
            return True
        else:
            return False
    except Exception as e:
        traceback.print_exc()
        print("imwrite {0} : ".format(e))
        return False

# URL 주소로부터 이미지 읽기
def imread_url(url, dtype=np.uint8):
    import ssl
    __context__ = ssl._create_unverified_context()

    try:
        headers = {"User-Agent":"Chrome/66.0.3359.181"}
        req = urllib.request.Request(url, headers=headers)
        html = urllib.request.urlopen(req, context=__context__)
        arr = np.asarray(bytearray(html.read()), dtype=dtype)
        img = cv2.imdecode(arr, -1)
        # 뒤의 Alpha는 지원하지 않도록 함 (다른 API간 호환성 대비)
        img = cv2.cvtColor(img, cv2.COLOR_BGRA2BGR)
        return img
    except Exception as e:
        print("[Error] 잘못된 이미지 타입이거나 이미지를 읽어들일 수 없습니다. (None 값 반환됨)")
        print("=> URL 주소 : '{0}'".format(url))
        return None

# 이미지를 좌/우 혹은 상/하 반전시킴
def flip(image=None, mode=1):
    try:
        return cv2.flip(image, mode)
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 이미지를 뿌옇게 만듬
# https://dsbook.tistory.com/194?category=802614
def blur(image=None, ksize=2, blur_type="normal"):
    try:
        image = image.copy()
        ksize = ksize * 2 + 1
        if(ksize == 0):
            ksize = 1
        # 일반적인 필터링 방법 (평균값 계산)
        if(blur_type == "default"):
            return cv2.blur(image, (ksize, ksize))
        # Gaussian Blur
        if(blur_type == "gaussian"):
            return cv2.GaussianBlur(image, (ksize, ksize), 0)
        # Median Blur
        if(blur_type == "median"):
            return cv2.medianBlur(image, ksize)
        # Bilateral Blur
        if(blur_type == "bilateral"):
            return cv2.bilateralFilter(image, ksize, 75, 75)
        # Motion Blur (이미지에 움직인 것과 같은 잔상 효과를 남김)
        if(blur_type == "motion"):
            __kernel = np.zeros((ksize, ksize))
            __kernel[int((ksize - 1) / 2), :] = np.ones(ksize)
            __kernel /= ksize
            __kernel = cv2.filter2D(image, -1, __kernel)
            return __kernel
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 노이즈 추가
def noise(image=None, noise_type="white"):
    try:
        image = image.copy()
        row, col, channel = image.shape
    
        # White Noise (백색 잡음)
        if (noise_type == "white"):
            image = (image / 255 + np.random.normal(scale = 0.1, size = image.shape)) * 255
            image = np.clip(image, 0, 255).astype('uint8')

        # Salte and Pepper Noise (랜덤으로 검거나 흰 점들이 소금이나 후추처럼 흩뿌려져 있는 노이즈)
        elif (noise_type == "s&p"):
            s_vs_p = 0.5 # 흰 점, 검은 점 비율
            amount = 0.004 # 생성할 점 비율
            salt_color = (255, 255, 255) # 소금 색깔
            pepper_color = (0, 0, 0) # 후추 색깔

            # Salt mode
            num_salt = np.ceil(amount * image.size * s_vs_p)
            coords = [np.random.randint(0, i - 1, int(num_salt)) for i in image.shape[0:2]]
            image[tuple(coords)] = salt_color

            # Pepper mode
            num_pepper = np.ceil(amount* image.size * (1. - s_vs_p))
            coords = [np.random.randint(0, i - 1, int(num_pepper)) for i in image.shape[0:2]]
            image[tuple(coords)] = pepper_color

        # elif (noise_type == "poisson"):
        #     vals = len(np.unique(image))
        #     vals = 2 ** np.ceil(np.log2(vals))
        #     image = np.random.poisson(image * vals) / float(vals)
        #     image = image.astype('uint8')

        #     image = np.random.poisson(image).astype('uint8')

        # elif (noise_type == "speckle"):
        #     # gauss = np.random.randn(row,col,channel)
        #     gauss = np.random.normal(scale = 0.1, size = image.shape)
        #     # gauss = gauss.reshape(row,col,channel)
        #     # image = image + image * gauss
        #     image = image * gauss
        #     image = image.astype('uint8')
        return image
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 이미지를 회색조로 변환
def color2gray(image):
    try:
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        image = cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)
        return image
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 이미지 회전하기
# image: 이미지 배열
# angle: 각도
# background_color: 이미지를 회전하면서 생긴 공백을 매꿀 색깔
def rotate(image, angle=90, background_color=(255, 255, 255), ):
    try:
        angle %= 360
        # 90도
        if(angle == 90):
            rotated_mat = cv2.rotate(image, cv2.ROTATE_90_CLOCKWISE)
        # 180도
        elif(angle == 180):
            rotated_mat = cv2.rotate(image, cv2.ROTATE_180)
        # 270도
        elif(angle == 270):
            rotated_mat = cv2.rotate(image, cv2.ROTATE_90_COUNTERCLOCKWISE)
        # 0도, 360도는 무시
        elif(angle == 0):
            rotated_mat = image.copy()
        # 그 이외일 경우
        else:
            # angle in degrees
            height, width = image.shape[:2]
            image_center = (width/2, height/2)
            rotation_mat = cv2.getRotationMatrix2D(image_center, -angle, 1)
            abs_cos = abs(rotation_mat[0,0])
            abs_sin = abs(rotation_mat[0,1])
            bound_w = int(height * abs_sin + width * abs_cos)
            bound_h = int(height * abs_cos + width * abs_sin)
            rotation_mat[0, 2] += bound_w/2 - image_center[0]
            rotation_mat[1, 2] += bound_h/2 - image_center[1]
            rotated_mat = cv2.warpAffine(image, rotation_mat, (bound_w, bound_h), borderValue=background_color)

        return rotated_mat
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 이미지를 반전시킴
def bitwise_not(image):
    try:
        return cv2.bitwise_not(image)
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 이미지의 밝기를 조절함
# brightly : 밝게
# darkly : 어둡게
# range : 밝기를 얼마만큼 조절할 지 (B, G, R에 해당)
def brightness(image, range_brightness=(10, 10, 10), mode="brightly"):
    try:
        if(mode == "brightly"):
            return cv2.add(image, np.full(image.shape, range_brightness, dtype=np.uint8))
        elif(mode == "darkly"):
            return cv2.subtract(image, np.full(image.shape, range_brightness, dtype=np.uint8))
        else:
            return image
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 이미지 잘라내기
def crop(image, startx, starty, endx, endy):
    try:
        startx = max(0, min(startx, image.shape[1]))
        starty = max(0, min(starty, image.shape[0]))
        endx = max(0, min(endx, image.shape[1]))
        endy = max(0, min(endy, image.shape[0]))

        return image[starty:endy, startx:endx].copy()
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 랜덤 이미지 잘라내기
def random_crop(image, width, height):
    try:
        import random
        width = max(0, min(width, image.shape[1]))
        height = max(0, min(height, image.shape[0]))

        startx = random.randint(0, image.shape[1] - width)
        starty = random.randint(0, image.shape[0] - height)
        endx = startx + width
        endy = starty + height

        return image[starty:endy, startx:endx].copy()
    except:
        print("[Error] 이미지 전처리 실패 (None 값 반환됨)")
        return None

# 엣지 검출
def auto_canny(image, sigma=0.33):
    # compute the median of the single channel pixel intensities
    v = np.median(image)

    # apply automatic Canny edge detection using the computed median
    lower = int(max(0, (1.0 - sigma) * v))
    upper = int(min(255, (1.0 + sigma) * v))
    edged = cv2.Canny(image, lower, upper)

    # return the edged image
    return edged

# 리사이즈
def resize(image, dsize, interpolation=cv2.INTER_AREA):
    try:
        result = cv2.resize(src=image, dsize=dsize, fx=0, fy=0, interpolation=interpolation)
    except:
        print("[Error] 이미지 리사이즈 실패 (None 값 반환됨)")
        return None
    return result

# 리사이즈 (배율)
def resize_scale(image, fsize, interpolation=cv2.INTER_AREA):
    try:
        result = cv2.resize(src=image, dsize=(0, 0), fx=fsize[0], fy=fsize[1], interpolation=interpolation)
    except:
        print("[Error] 이미지 리사이즈 실패 (None 값 반환됨)")
        return None
    return result

# 리사이즈 (원본의 비율을 망치지 않음)
def resize_keep_ratio(image, width=None, height=None, interpolation=cv2.INTER_AREA):
    # initialize the dimensions of the image to be resized and
    # grab the image size
    dim = None
    (h, w) = image.shape[:2]

    # if both the width and height are None, then return the
    # original image
    if width is None and height is None:
        return image

    # check to see if the width is None
    if width is None:
        # calculate the ratio of the height and construct the
        # dimensions
        r = height / float(h)
        dim = (int(w * r), height)

    # otherwise, the height is None
    else:
        # calculate the ratio of the width and construct the
        # dimensions
        r = width / float(w)
        dim = (width, int(h * r))

    # resize the image
    resized = cv2.resize(image, dim, interpolation = interpolation)

    # return the resized image
    return resized

# 이미지 밝음 여부 확인
def isLight(frame, threshld=127):
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    is_light = np.mean(frame) > threshld
    return is_light

# 이미지 어두움 여부 확인
def isDarkness(frame, threshld=127):
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    is_darkness = np.mean(frame) <= threshld
    return is_darkness

# 주로 딥러닝에서 사용하는 전처리 방식
def preprocess_ai(frame, mode="tf"):
    x = frame.copy()
    if mode == "tf":
        x /= 127.5
        x -= 1.
        return x
    if mode == "torch":
        x /= 255.
        mean = [0.485, 0.456, 0.406]
        std = [0.229, 0.224, 0.225]
    if mode == "vgg16":
        mean = [103.939, 116.779, 123.68]
        std = None
    if mode == "teachable":
        x = (x / 127.0) - 1
        return x
    
    x[..., 0] -= mean[0]
    x[..., 1] -= mean[1]
    x[..., 2] -= mean[2]
    if std is not None:
        x[..., 0] /= std[0]
        x[..., 1] /= std[1]
        x[..., 2] /= std[2]
    return x
    

