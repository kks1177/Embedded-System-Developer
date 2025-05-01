##컬러 영상처리
from tkinter import *
from tkinter import messagebox
from tkinter.colorchooser import *
from tkinter.simpledialog import *
from tkinter.filedialog import *
import os
import math
import cv2
import numpy as np
import tkinter
import cv2
import mediapipe as mp
import time
import dlib
from cvzone.HandTrackingModule import HandDetector
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_pose = mp.solutions.pose

## 공통함수
def malloc2D(h, w, init=0) :
    memory = [ [  [ init for _ in range(w)]  for _ in range(h) ] for _ in range(RGB) ]
    return memory

def openImage() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto
    # 파일 선택하고 크기 계산
    filename = askopenfilename(parent=window, filetypes=(("칼라 파일", "*.jpg;*.png;*.bmp;*.tif;*.tiff"), ("모든파일","*.*")))
    # 파일 --> OpenCV 개체
    cvInPhoto = cv2.imread(filename)
    # (중요!) 영상의 크기 알아내기
    m_inH, m_inW = cvInPhoto.shape[:2]
    # 메모리 할당
    m_InputImage = malloc2D(m_inH, m_inW)
    # OpenCV --> 메모리
    for i in range(m_inH) :
        for k in range(m_inW) :
            m_InputImage[RR][i][k] = cvInPhoto.item(i, k, BB)
            m_InputImage[GG][i][k] = cvInPhoto.item(i, k, GG)
            m_InputImage[BB][i][k] = cvInPhoto.item(i, k, RR)


    equalImage()

def displayImage() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    if canvas != None :
        canvas.destroy()
    window.geometry(str(1200) + "x" + str(700))
    canvas = Canvas(window, height=m_outH, width=m_outW)
    paper = PhotoImage(height=m_outH, width=m_outW)
    canvas.create_image( (m_outW/2, m_outH/2), image=paper, state='normal' )
    # 메모리 --> 화면에 찍기
    rgbString=""
    for i in range(m_outH) :
        tmpStr = "" # 한 줄짜리
        for k in range(m_outW) :
            r = m_OutputImage[RR][i][k]
            g = m_OutputImage[GG][i][k]
            b = m_OutputImage[BB][i][k]
            tmpStr += "#%02x%02x%02x " % (r, g, b)
        rgbString += "{" + tmpStr + "} "
    paper.put(rgbString)
    canvas.pack()
    status.configure(text=str(m_inW) + 'x' + str(m_inH) + '    ' + filename)

def saveImage() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    # 빈 OpenCV 개체 생성
    saveCvPhoto = np.zero( (m_outH, m_outW, 3), np.uint8 )

    #출력리스트 --> 넘파이
    for i in range(m_inH):
        for k in range(m_inW):
            tp = tuple( [m_OutputImage[BB][i][k], m_OutputImage[GG][i][k], m_OutputImage[RR][i][k]] )
            saveCvPhoto[i][k] = tp

    saveFp = asksaveasfile(parent=window, mode='wb', defaultextension='.',
                           filetypes=(("칼라 파일", "*.jpg;*.png;*.bmp;*.tif;*.tiff"), ("모든파일","*.*")) )
    cv2.imwrite((saveFp.name, saveCvPhoto))
    print('Save')

## 영상처리 함수
def equalImage() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH) :
            for k in range(m_inW) :
                m_OutputImage[rgb][i][k] = m_InputImage[rgb][i][k]
    displayImage()

def reverseImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    start = time.time()  # 시작 시간 저장
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)

    for rgb in range(RGB):
        for i in range(m_inH):
            for k in range(m_inW):
                m_OutputImage[rgb][i][k] = 255 - m_InputImage[rgb][i][k]


    displayImage()
    print("time :", time.time() - start)  # 현재시각 - 시작시간 = 실행 시간


### 반전 이미지 마우스 클릭 관력 --> ###
def reverseImageMouse():
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global sx, sy, ex, ey
    # 마우스 이벤트를 받을 준비를 시키기
    canvas.bind("<Button-1>", reverseImage_leftClick)
    canvas.bind("<ButtonRelease-1>", reverseImage_leftDrop)
    canvas.bind("<B1-Motion>", reverseImage_leftMove)


def reverseImage_leftClick(event) :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global sx, sy, ex, ey
    sx = event.x
    sy = event.y


def reverseImage_leftMove(event) :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global sx, sy, ex, ey, boxLine
    ex = event.x
    ey = event.y
    if boxLine == None :
        pass
    else :
        canvas.delete(boxLine)

    boxLine = canvas.create_rectangle(sx, sy ,ex, ey, fill=None)


def reverseImage_leftDrop(event) :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global sx, sy, ex, ey
    ex = event.x
    ey = event.y
    if sx > ex :
        sx, ex = ex, sx
    if sy > ey :
        sy, ey = ey, sy

    _reverseImage()

    canvas.unbind("<Button-1>")
    canvas.unbind("<ButtonRelease-1>")

def _reverseImage():
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global sx, sy, ex, ey

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    ##출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB):
        for i in range(m_inH):
            for k in range(m_inW):
                if (sx <= k <= ex) and (sy <= i <= ey):
                    m_OutputImage[rgb][i][k] = 255 - m_InputImage[rgb][i][k]
                else:
                    m_OutputImage[rgb][i][k] = m_InputImage[rgb][i][k]

    displayImage()



### 반전 이미지 마우스 클릭 관력 --> ###

def lightImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    alpha = askinteger("밝기 조절", "밝기 조절 값을 입력해주세요.")
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH) :
            for k in range(m_inW) :
                if (m_InputImage[rgb][i][k] + alpha > 255) : m_OutputImage[rgb][i][k] = 255
                elif (m_InputImage[rgb][i][k] + alpha < 0) : m_OutputImage[rgb][i][k] = 0
                else : m_OutputImage[rgb][i][k] = m_InputImage[rgb][i][k] + alpha
    displayImage()

def bwImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    bw = askinteger("이진화", "임계값을 입력해주세요.(0~255)", minvalue=0, maxvalue=255)

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                if ((m_InputImage[0][i][k] + m_InputImage[1][i][k] + m_InputImage[2][i][k])/3 > bw) :  m_OutputImage[rgb][i][k] = 255
                elif ((m_InputImage[0][i][k] + m_InputImage[1][i][k] + m_InputImage[2][i][k])/3 <= bw) :  m_OutputImage[rgb][i][k] = 0
    displayImage()

def muldivImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    alpha = askfloat("곱셈/나눗셈", "값을 입력해주세요.(0~100)", minvalue=0, maxvalue=100)
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                if (m_InputImage[rgb][i][k] * alpha > 255) : m_OutputImage[rgb][i][k] = 255
                else : m_OutputImage[rgb][i][k] = int(m_InputImage[rgb][i][k] * alpha)
    displayImage()

def gammaImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    gamma = askfloat("감마 보정", "감마값을 입력해주세요.(0.1~3.0)", minvalue=0.1, maxvalue=3.0)
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH) :
            for k in range(m_inW) :
                m_OutputImage[rgb][i][k] = int(255 * pow(m_InputImage[rgb][i][k]/255, 1/gamma))
    displayImage()

def paraImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                m_OutputImage[rgb][i][k] = int(255 - 255*pow(m_InputImage[rgb][i][k]/127, 2))
                if (m_OutputImage[rgb][i][k] > 255) : m_OutputImage[rgb][i][k] = 255
                elif (m_OutputImage[rgb][i][k] < 0) : m_OutputImage[rgb][i][k] = 0
    displayImage()

def zoomImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    size = askinteger("이미지 확대", "확대배율을 입력해주세요.")
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = int(m_inH*size)
    m_outW = int(m_inW*size)
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                rx = (m_inW - 1) * i // (m_outW - 1)
                ry = (m_inH - 1) * k // (m_outH - 1)

                x1 = rx
                y1 = ry

                x2 = min(x1 + 1, m_inW - 1)
                y2 = min(y1 + 1, m_inH - 1)

                p = rx - x1
                q = ry - y1

                m_OutputImage[rgb][k][i] = int((1-p)*(1-q)*m_InputImage[rgb][y1][x1] + p*(1-q)*m_InputImage[rgb][y1][x2] + (1-p)*q*m_InputImage[rgb][y2][x1] + p*q*m_InputImage[rgb][y2][x2])
    displayImage()

def zoomoutImage():
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    size = askinteger("이미지 확대", "축소배율을 입력해주세요.")
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = int(m_inH/size)
    m_outW = int(m_inW/size)
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                m_OutputImage[rgb][int(i/size)][int(k/size)] = m_InputImage[rgb][i][k]
    displayImage()

def udMirImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                m_OutputImage[rgb][i][k] = m_InputImage[rgb][m_outH - 1 -i][k]
    displayImage()

def lrMirImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                m_OutputImage[rgb][i][k] = m_InputImage[rgb][i][m_outW - 1 - k]
    displayImage()

def rotateImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    ang = askinteger("회전 각도", "회전 각도를 입력해주세요.")
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    if (ang > 360) : ang = ang - 360 * int(ang / 360)
    pi = 3.141592
    rad = pi / 180
    theta = rad * ang

    if (ang == 360 or (ang <= 90 and ang >= 0)) :
        width = int(m_inH * math.sin(theta) + m_inW * math.cos(theta))
        height = int(m_inH * math.cos(theta) + m_inW * math.sin(theta))
        m_outH = height
        m_outW = width

    elif (ang > 90 and ang <= 180) :
        width = int(m_inH * math.cos(theta - (pi / 2)) + m_inW * math.cos(pi - theta))
        height = int(m_inW * math.sin(pi - theta) + m_inH * math.sin(theta - (pi / 2)))
        m_outH = height
        m_outW = width

    elif (ang > 180 and ang <= 270) :
        width = int(m_inH * math.sin(theta) + m_inW * math.cos(theta))
        height = int(m_inH * math.cos(theta) + m_inW * math.sin(theta))
        m_outH = height
        m_outW = width

    elif (ang > 270 and ang < 360) :
        width = int(m_inH * math.cos(theta - (pi / 2)) + m_inW * math.cos(pi - theta))
        height = int(m_inW * math.sin(pi - theta) + m_inH * math.sin(theta - (pi / 2)))
        m_outH = height
        m_outW = width

    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH + 10, m_outW + 10)

    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                if (ang == 360 or (ang <= 90 and ang >= 0)) :
                    h_val = int(k * math.sin(theta) + i * math.cos(theta))
                    w_val = int(k * math.cos(theta) - i * math.sin(theta) + m_inH * math.sin(theta))
                    m_OutputImage[rgb][h_val][w_val] = m_InputImage[rgb][i][k]

                elif (ang > 90 and ang <= 180):
                    h_val = int(k * math.sin(theta) + i * math.cos(theta) + m_inH * math.sin(theta - (pi / 2)))
                    w_val = int(k * math.cos(theta) - i * math.sin(theta) + m_inH * math.cos(theta - (pi / 2)) + m_inW * math.cos(pi - theta))
                    m_OutputImage[rgb][h_val][w_val] = m_InputImage[rgb][i][k];

                elif (ang > 180 and ang <= 270):
                    h_val = int(k * math.sin(theta) + i * math.cos(theta))
                    w_val = int(k * math.cos(theta) - i * math.sin(theta) + m_inH * math.sin(theta))
                    m_OutputImage[rgb][h_val][w_val] = m_InputImage[rgb][m_inH - 1 - i][k]

                elif (ang > 270 and ang < 360):
                    h_val = int(k * math.sin(theta) + i * math.cos(theta) + m_inH * math.sin(theta - (pi / 2)))
                    w_val = int(
                        k * math.cos(theta) - i * math.sin(theta) + m_inH * math.cos(theta - (pi / 2)) + m_inW * math.cos(
                            pi - theta))
                    m_OutputImage[rgb][h_val][w_val] = m_InputImage[rgb][m_inH - 1 - i][k];

    displayImage()

def moveImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    H = askinteger("가로 이동", "가로로 이동할 값 입력")
    W = askinteger("세로 이동", "세로로 이동할 값 입력")
    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH+H
    m_outW = m_inW+W
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                m_OutputImage[rgb][i+H][k+W] = m_InputImage[rgb][i][k]
    displayImage()

def embossImage() :
    start = time.time()  # 시작 시간 저장
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘

    mask = [[-1, 0, 0],
            [ 0, 0, 0],
            [ 0, 0, 1]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                tmpOutput[rgb][i][k] += 127

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()
    print("time :", time.time() - start)  # 현재시각 - 시작시간 = 실행 시간

def blurImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper
    blur = askinteger("블러링", "마스크 값을 입력해주세요.(홀수만가능, 1이상)")
    if (blur%2 == 0) :
        messagebox.showerror("에러.", "홀수가 아닙니다.")
        blur = askinteger("블러링", "마스크 값을 입력해주세요.(홀수만가능, 1이상)")
    elif (blur < 2) :
        messagebox.showerror("에러.", "1이상의 홀수를 입력해주세요.")
        blur = askinteger("블러링", "마스크 값을 입력해주세요.(홀수만가능, 1이상)")

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)

    mask = [  [ 0 for _ in range(blur)]  for _ in range(blur) ]

    for i in range(blur) :
        for k in range(blur) :
            mask[i][k] = 1/(blur*blur)

    ##진짜 영상처리 알고리즘
    tmpInput = malloc2D(m_inH + (blur - 1), m_inW + (blur - 1), 3)
    tmpOutput = malloc2D(m_outH, m_outW, 3)

    bum = int((blur - 2) - 0.5)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + bum][k + bum] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(blur):
                    for n in range(blur):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = int(v)

    displayImage()

def gaussianImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘

    mask = [[1/16, 1/8, 1/16],
            [ 1/8, 1/4,  1/8],
            [1/16, 1/8, 1/16]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                tmpOutput[rgb][i][k] += 127

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = int(v)

    displayImage()

def sharpImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘

    mask = [[ 0, -1,  0],
            [-1,  5, -1],
            [ 0, -1,  0]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()

def rbClick1() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘

    mask = [[-1, 0, 0],
            [0, 1, 0],
            [0, 0, 0]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()
    robertsImage()

def rbClick2() :
    global m_InputImagㅍe, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    mask = [[0, 0, -1],
            [0, 1, 0],
            [0, 0, 0]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()
    robertsImage()

def robertsImage() :
    global m_InputImagㅍe, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    button1 = Button(window, text="로버츠 행검출", fg='black', bg='yellow', command=rbClick1)
    button2 = Button(window, text="로버츠 열검출", fg='black', bg='yellow', command=rbClick2)

    button1.place(x=(m_outW/2)-100, y=0)
    button2.place(x=(m_outW/2), y=0)

def sbClick1() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    mask = [[-1, 0, 1],
            [-2, 0, 2],
            [-1, 0, 1]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()
    sobelImage()

def sbClick2() :
    global m_InputImagㅍe, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    mask = [[1, 2, 1],
            [0, 0, 0],
            [-1, -2, -1]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()
    sobelImage()

def sobelImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    button1 = Button(window, text="소벨 행검출", fg='black', bg='yellow', command=sbClick1)
    button2 = Button(window, text="소벨 열검출", fg='black', bg='yellow', command=sbClick2)

    button1.place(x=(m_outW/2)-100, y=0)
    button2.place(x=(m_outW/2), y=0)

def pwClick1() :
    global m_InputImagㅍe, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    mask = [[1, 1, 1],
            [0, 0, 0],
            [-1, -1, -1]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()
    prewittImage()

def pwClick2() :
    global m_InputImagㅍe, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘
    mask = [[-1, 0, 1],
            [-1, 0, 1],
            [-1, 0, 1]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()
    prewittImage()

def prewittImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    button1 = Button(window, text="프리윗 행검출", fg='black', bg='yellow', command=pwClick1)
    button2 = Button(window, text="프리윗 열검출", fg='black', bg='yellow', command=pwClick2)

    button1.place(x=(m_outW/2)-100, y=0)
    button2.place(x=(m_outW/2), y=0)

def laplacianImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘

    mask = [[ 0, 1, 0],
            [ 1, -4, 1],
            [ 0, 1, 0]]

    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(3):
                    for n in range(3):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()

def homogeneityImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)

    ##진짜 영상처리 알고리즘
    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)

    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    max = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                max = 0
                for m in range(3):
                    for n in range(3):
                        cha = tmpInput[rgb][i + 1][k + 1] - tmpInput[rgb][i + m][k + n]
                        if (cha < 0) : cha = -1 * cha
                        else : cha = cha

                        if(cha >= max) : max = cha
                tmpOutput[rgb][i][k] = max

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()

def DifferenceImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)

    ##진짜 영상처리 알고리즘
    tmpInput = malloc2D(m_inH + 2, m_inW + 2, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)

    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 1][k + 1] = m_InputImage[rgb][i][k]

    max = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                max = 0
                for m in range(3):
                    for n in range(3):
                        cha = tmpInput[rgb][i + 1][k + 1] - tmpInput[rgb][i + m][k + n]
                        if (cha < 0) : cha = -1 * cha
                        else : cha = cha

                        if(cha >= max) :
                            max = cha
                            if (tmpInput[rgb][i + 1][k + 1] - tmpInput[rgb][i + 1][k] >= max) :
                                max = tmpInput[rgb][i + 1][k + 1] - tmpInput[rgb][i + 1][k]
                tmpOutput[rgb][i][k] = max

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()

def LoGImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘

    mask = [[ 0,  0, -1,  0,  0],
            [ 0, -1, -2, -1,  0],
            [-1, -2, 16, -2, -1],
            [ 0, -1, -2, -1,  0],
            [ 0,  0, -1,  0,  0]]

    tmpInput = malloc2D(m_inH + 4, m_inW + 4, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)

    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 2][k + 2] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(5):
                    for n in range(5):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()

def DoGImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    # (중요!) 출력 영상 크기 결정 ---> 알고리즘에 따름
    m_outH = m_inH
    m_outW = m_inW
    # 출력 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    ##진짜 영상처리 알고리즘

    mask = [[ 0,  0, -1,  -1,  -1, 0, 0],
            [ 0, -2, -3, -3,  -3, -2, 0],
            [-1, -3, 5, 5, 5, -3, -1],
            [-1, -3, 5, 16, 5, -3, -1],
            [-1, -3, 5, 5, 5, -3, -1],
            [ 0, -2, -3, -3,  -3, -2, 0],
            [ 0,  0, -1,  -1,  -1, 0, 0]]

    tmpInput = malloc2D(m_inH + 6, m_inW + 6, 3)
    tmpOutput = malloc2D(m_inH, m_inW, 3)

    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                tmpInput[rgb][i + 3][k + 3] = m_InputImage[rgb][i][k]

    S = 0
    for rgb in range(RGB) :
        for i in range(m_inH):
            for k in range(m_inW):
                S = 0
                for m in range(7):
                    for n in range(7):
                        S += tmpInput[rgb][i + m][k + n] * mask[m][n]
                tmpOutput[rgb][i][k] = S

    for rgb in range(RGB) :
        for i in range(m_outH):
            for k in range(m_outW):
                v = tmpOutput[rgb][i][k]
                if (v > 255): v = 255
                if (v < 0): v = 0
                m_OutputImage[rgb][i][k] = v

    displayImage()

def equalizationImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    m_outH = m_inH;
    m_outW = m_inW;

    m_OutputImage = malloc2D(m_outH, m_outW, 3)

    his0 = [1 for _ in range(0, 256)]
    his1 = [1 for _ in range(0, 256)]
    his2 = [1 for _ in range(0, 256)]
    for i in range(256):his0[i] = 0
    for i in range(256):his1[i] = 0
    for i in range(256):his2[i] = 0

    for i in range(m_inH):
        for k in range(m_inW):
            gab0 = m_InputImage[0][i][k]
            his0[gab0] = his0[gab0] + 1
            gab1 = m_InputImage[1][i][k]
            his1[gab1] = his0[gab1] + 1
            gab2 = m_InputImage[2][i][k]
            his2[gab2] = his0[gab2] + 1

    sum0 = 0
    sum1 = 0
    sum2 = 0
    sumhis0 = [1 for _ in range(0, 256)]
    sumhis1 = [1 for _ in range(0, 256)]
    sumhis2 = [1 for _ in range(0, 256)]
    for i in range(1, 256):
        sum0 += his0[i]
        sumhis0[i] = int((sum0 * (255.0 / (m_outW * m_outH))))
        sum1 += his1[i]
        sumhis1[i] = int((sum1 * (255.0 / (m_outW * m_outH))))
        sum2 += his2[i]
        sumhis2[i] = int((sum2 * (255.0 / (m_outW * m_outH))))

    for i in range(m_inH):
        for k in range(m_inW):
            g0 = m_InputImage[0][i][k]
            g1 = m_InputImage[1][i][k]
            g2 = m_InputImage[2][i][k]
            m_OutputImage[0][i][k] = int(sumhis0[g0])
            m_OutputImage[1][i][k] = int(sumhis1[g1])
            m_OutputImage[2][i][k] = int(sumhis2[g2])

    displayImage()

def fireImage() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW, window, canvas, paper

    m_outH = m_inH
    m_outW = m_inW

    m_OutputImage = malloc2D(m_outH, m_outW, 3)

    BLKImage = [  [ 0 for _ in range(m_inW)]  for _ in range(m_inH) ]

    for i in range(m_outH):
        for k in range(m_outW):
            BLKImage[i][k] = int((m_InputImage[0][i][k] + m_InputImage[1][i][k] + m_InputImage[2][i][k]) / 3)

    for i in range(m_inH):
        for k in range(m_inW):
            A = BLKImage[i][k]
            if (A < 63) :
                m_OutputImage[0][i][k] = 0
                m_OutputImage[1][i][k] = 4 * A
                m_OutputImage[2][i][k] = 255

            elif (63 <= A and A < 126) :
                m_OutputImage[0][i][k] = int(0)
                m_OutputImage[1][i][k] = int(255)
                m_OutputImage[2][i][k] = int(255 - (4 * (A - 63)))

            elif (126 <= A and A <= 189) :
                m_OutputImage[0][i][k] = int(4 * (A - 126))
                m_OutputImage[1][i][k] = int(255)
                m_OutputImage[2][i][k] = int(0)

            elif (189 < A and A < 255) :
                m_OutputImage[0][i][k] = int(255)
                m_OutputImage[1][i][k] = int(255 - (4 * (A - 189)))
                m_OutputImage[2][i][k] = int(0)

    displayImage()

##OpenCV용 영상처리
def cv2OutImage() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    # (중요!) 영상의 크기 알아내기
    m_outH, m_outW = cvOutPhoto.shape[:2]
    # 메모리 할당
    m_OutputImage = malloc2D(m_outH, m_outW)
    # OpenCV --> 메모리
    for i in range(m_outH):
        for k in range(m_outW):
            if cvOutPhoto.ndim > 2 :
                m_OutputImage[RR][i][k] = cvOutPhoto.item(i, k, BB)
                m_OutputImage[GG][i][k] = cvOutPhoto.item(i, k, GG)
                m_OutputImage[BB][i][k] = cvOutPhoto.item(i, k, RR)
            else :
                m_OutputImage[RR][i][k] = cvOutPhoto.item(i, k)
                m_OutputImage[GG][i][k] = cvOutPhoto.item(i, k)
                m_OutputImage[BB][i][k] = cvOutPhoto.item(i, k)

def grayImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    cvOutPhoto = cv2.cvtColor(cvInPhoto, cv2.COLOR_RGB2GRAY)

    #이미지 출력
    cv2OutImage()
    displayImage()

def addImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    alpha = askinteger("밝기 조절", "밝기 조절 값을 입력해주세요.")
    if (alpha>255 or alpha<0) :
        messagebox.showerror("에러","min : 0, max : 255")
        alpha = askinteger("밝기 조절", "밝기 조절 값을 입력해주세요.")

    ##OpenCV용 알고리즘
    ary = np.full(cvInPhoto.shape, (alpha, alpha, alpha), dtype=np.uint8)
    cvOutPhoto = cv2.add(cvInPhoto, ary)

    #이미지 출력
    cv2OutImage()
    displayImage()

def subImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    alpha = askinteger("밝기 조절", "밝기 조절 값을 입력해주세요.")
    if (alpha > 255 or alpha < 0):
        messagebox.showerror("에러", "min : 0, max : 255")
        alpha = askinteger("밝기 조절", "밝기 조절 값을 입력해주세요.")

    ##OpenCV용 알고리즘
    ary = np.full(cvInPhoto.shape, (alpha, alpha, alpha), dtype=np.uint8)
    cvOutPhoto = cv2.subtract(cvInPhoto, ary)

    #이미지 출력
    cv2OutImage()
    displayImage()

def mulImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    alpha = askfloat("밝기 조절", "밝기 조절(곱셈) 값을 입력해주세요.")
    if (alpha<0):
        messagebox.showerror("에러", "0보다 커야 합니다.")
        alpha = askfloat("밝기 조절", "밝기 조절(곱셈) 값을 입력해주세요.")

    ##OpenCV용 알고리즘
    cvOutPhoto = np.clip(cvInPhoto * alpha, 0, 255).astype(np.uint8)

    #이미지 출력
    cv2OutImage()
    displayImage()

def reverseImage_cv() :
    start = time.time()  # 시작 시간 저장
    print("time :", time.time() - start)  # 현재시각 - 시작시간 = 실행 시간

    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    cvOutPhoto = cv2.bitwise_not(cvInPhoto) # 255-cvInPhoto 와 같다.

    #이미지 출력
    cv2OutImage()
    displayImage()
    print("time :", time.time() - start)  # 현재시각 - 시작시간 = 실행 시간

def gammaImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    gamma = askfloat("감마 보정", "감마 값을 입력해주세요.")
    if (gamma<0):
        messagebox.showerror("에러", "0이상의 값을 입력해주세요")
        alpha = askfloat("감마 보정", "감마 값을 입력해주세요.")

    ##OpenCV용 알고리즘
    cvOutPhoto = np.clip(255 * pow(cvInPhoto / 255, 1 / gamma), 0, 255).astype(np.uint8)

    #이미지 출력
    cv2OutImage()
    displayImage()

def paraImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    cvOutPhoto = np.clip(255 - 255*pow(cvInPhoto/127, 2), 0, 255).astype(np.uint8)

    #이미지 출력
    cv2OutImage()
    displayImage()

def bwImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    cvOutPhoto = cv2.cvtColor(cvInPhoto, cv2.COLOR_RGB2GRAY)
    cvOutPhoto = cv2.THRESH_OTSU(cvOutPhoto)

    #이미지 출력
    cv2OutImage()
    displayImage()

def embossImage_cv() :
    start = time.time()  # 시작 시간 저장

    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    mask = np.zeros((3,3), np.float32)
    mask[0][0] = -1.0
    mask[2][2] = 1.0
    cvOutPhoto = cv2.filter2D(cvInPhoto, -1, mask)
    cvOutPhoto += 127

    #이미지 출력
    cv2OutImage()
    displayImage()
    print("time :", time.time() - start)  # 현재시각 - 시작시간 = 실행 시간

def blurImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    blur = askinteger("블러링", "마스크 값을 입력해주세요.(홀수만가능, 1이상)")
    if (blur % 2 == 0):
        messagebox.showerror("에러.", "홀수가 아닙니다.")
        blur = askinteger("블러링", "마스크 값을 입력해주세요.(홀수만가능, 1이상)")
    elif (blur < 2):
        messagebox.showerror("에러.", "1이상의 홀수를 입력해주세요.")
        blur = askinteger("블러링", "마스크 값을 입력해주세요.(홀수만가능, 1이상)")

    ##OpenCV용 알고리즘
    mask = np.zeros((blur,blur), np.float32)
    mask[0:][0:] = 1/(blur*blur)
    cvOutPhoto = cv2.filter2D(cvInPhoto, -1, mask)

    #이미지 출력
    cv2OutImage()
    displayImage()

def gaussianImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    mask = np.zeros((3,3), np.float32)
    mask[0][0], mask[0][2], mask[2][0], mask[2][2] = 1.0/16.0, 1.0/16.0, 1.0/16.0, 1.0/16.0
    mask[0][1], mask[1][0], mask[1][2], mask[2][1] = 1.0/8.0, 1.0/8.0, 1.0/8.0, 1.0/8.0
    mask[1][1] = 1.0/4.0
    cvOutPhoto = cv2.filter2D(cvInPhoto, -1, mask)

    #이미지 출력
    cv2OutImage()
    displayImage()

def sharpImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    mask = np.zeros((3,3), np.float32)
    mask[0][0], mask[0][2], mask[2][0], mask[2][2] = 0.0, 0.0, 0.0, 0.0
    mask[0][1], mask[1][0], mask[1][2], mask[2][1] = -1.0, -1.0, -1.0, -1.0
    mask[1][1] = 5.0
    cvOutPhoto = cv2.filter2D(cvInPhoto, -1, mask)

    #이미지 출력
    cv2OutImage()
    displayImage()

def sobelImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    x = cv2.Sobel(cvInPhoto, cv2.CV_64F, 1, 0, ksize=3)
    x = cv2.convertScaleAbs(x)

    y = cv2.Sobel(cvInPhoto, cv2.CV_64F, 0, 1, ksize=3)
    y = cv2.convertScaleAbs(y)

    cvOutPhoto = cv2.addWeighted(x, 1, y, 1, 0)

    #이미지 출력
    cv2OutImage()
    displayImage()

def prewittImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    mask1 = np.zeros((3,3), np.float32)
    mask2 = np.zeros((3, 3), np.float32)

    mask1[0][0], mask1[0][1], mask1[0][2] = 1.0, 1.0, 1.0
    mask1[2][0], mask1[2][1], mask1[2][2] = -1.0, -1.0, -1.0

    mask2[2][0], mask2[2][1], mask2[2][2] = 1.0, 1.0, 1.0
    mask2[0][0], mask2[0][1], mask2[0][2] = -1.0, -1.0, -1.0

    x = cv2.filter2D(cvInPhoto, -1, mask1)
    y = cv2.filter2D(cvInPhoto, -1, mask2)

    cvOutPhoto = cv2.addWeighted(x, 1, y, 1, 0)

    #이미지 출력
    cv2OutImage()
    displayImage()

def robertImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    mask1 = np.zeros((3,3), np.float32)
    mask2 = np.zeros((3, 3), np.float32)

    mask1[0][0] = -1.0
    mask1[1][1] = 1.0

    mask1[0][2] = -1.0
    mask1[1][1] = 1.0

    x = cv2.filter2D(cvInPhoto, -1, mask1)
    y = cv2.filter2D(cvInPhoto, -1, mask2)

    cvOutPhoto = cv2.addWeighted(x, 1, y, 1, 0)

    #이미지 출력
    cv2OutImage()
    displayImage()

def rotImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    theta = askinteger("회전 이미지", "각도를 입력해주세요.")

    cp = (cvInPhoto.shape[1] / 2, cvInPhoto.shape[0] / 2)  # 영상의 가로 1/2, 세로 1/2
    rot = cv2.getRotationMatrix2D(cp, theta, 0.8)
    cvOutPhoto = cv2.warpAffine(cvInPhoto, rot, (0, 0))  # 돌리기

    cv2OutImage()
    displayImage()

def cartoonImage_cv() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ##OpenCV용 알고리즘
    cvOutPhoto = cv2.cvtColor(cvInPhoto, cv2.COLOR_RGB2GRAY)
    cvOutPhoto = cv2.medianBlur(cvOutPhoto, 7)
    edges = cv2.Laplacian(cvOutPhoto, cv2.CV_8U, ksize=5)
    ret, mask = cv2.threshold(edges, 100, 255, cv2.THRESH_BINARY_INV)
    cvOutPhoto = cv2.cvtColor(mask, cv2.COLOR_GRAY2RGB)

    #이미지 출력
    cv2OutImage()
    displayImage()

def equalizationImage_cv() :
    global m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    src_ycrcb = cv2.cvtColor(cvInPhoto, cv2.COLOR_BGR2YCrCb)
    ycrcb_planes = cv2.split(src_ycrcb)

    # 밝기 성분에 대해서만 히스토그램 평활화 수행
    ycrcb_planes[0] = cv2.equalizeHist(ycrcb_planes[0])

    dst_ycrcb = cv2.merge(ycrcb_planes)
    cvOutPhoto = cv2.cvtColor(dst_ycrcb, cv2.COLOR_YCrCb2BGR)

    cv2OutImage()
    displayImage()

def faceDetect_cv():
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto
    ## OpenCV용 알고리즘 ##
    gray = cv2.cvtColor(cvInPhoto, cv2.COLOR_RGB2GRAY)
    # 인공지능 불러오기 (모델, Classifire) --> Pre trained Model
    face_clf = cv2.CascadeClassifier("haarcascade_frontalface_alt.xml")
    # 얼구 찾기
    face_rects = face_clf.detectMultiScale(gray, 1.1, 5)
    cvOutPhoto = cvInPhoto[:]
    for (x, y, w, h) in face_rects :
        cv2.rectangle(cvOutPhoto, (x,y), (x+w, y+h), (0, 255, 0), 3)
    #####################
    cv2OutImage()
    displayImage()

def carDetect_cv():
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto
    ## OpenCV용 알고리즘 ##
    gray = cv2.cvtColor(cvInPhoto, cv2.COLOR_RGB2GRAY)
    # 인공지능 불러오기 (모델, Classifire) --> Pre trained Model
    face_clf = cv2.CascadeClassifier("cars.xml")
    # 얼구 찾기
    face_rects = face_clf.detectMultiScale(gray, 1.1, 5)
    cvOutPhoto = cvInPhoto[:]
    for (x, y, w, h) in face_rects :
        cv2.rectangle(cvOutPhoto, (x,y), (x+w, y+h), (0, 255, 0), 3)
    #####################
    cv2OutImage()
    displayImage()

## 체크박스
def radioFunc() :
    if chk.get() == 0 :
        equalImage()

    else :
        imgDeep()

def radioFunc2() :
    if chk2.get() == 0 :
        equalImage()

    else :
        camDeep()

## 딥러닝 영상처리
def ssdNet(image) :
    CONF_VALUE = 0.5
    CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
               "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
               "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
               "sofa", "train", "tvmonitor"]
    COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))
    net = cv2.dnn.readNetFromCaffe("MobileNetSSD_deploy.prototxt.txt", "MobileNetSSD_deploy.caffemodel")
    (h, w) = image.shape[:2]
    blob = cv2.dnn.blobFromImage(cv2.resize(image, (300, 300)), 0.007843, (300, 300), 127.5)
    net.setInput(blob)
    detections = net.forward()
    for i in np.arange(0, detections.shape[2]):
        confidence = detections[0, 0, i, 2]
        if confidence > CONF_VALUE:
            idx = int(detections[0, 0, i, 1])
            box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
            (startX, startY, endX, endY) = box.astype("int")
            label = "{}: {:.2f}%".format(CLASSES[idx], confidence * 100)
            cv2.rectangle(image, (startX, startY), (endX, endY),
                          COLORS[idx], 2)
            y = startY - 15 if startY - 15 > 15 else startY + 15
            cv2.putText(image, label, (startX, y),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, COLORS[idx], 2)
    return image

def imgDeep() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ## 딥러닝 기반의 사물 인식 ##
    cvOutPhoto = cvInPhoto
    cvImage = cvOutPhoto
    retImage = ssdNet(cvImage)

    cv2.imshow('', cvImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def camDeep() :
    global window, canvas, paper, filename, m_InputImage, m_OutputImage, m_inH, m_inW, m_outH, m_outW
    global cvInPhoto, cvOutPhoto

    ## 딥러닝 기반의 사물 인식 ##
    cvOutPhoto = cvInPhoto
    cvImage = cvOutPhoto
    capture = cv2.VideoCapture(0)
    s_factor = 0.8  # 화면 크기 비율 ( 조절 가능 )

    frameCount = 0
    while True:
        ret, frame = capture.read()
        if not ret:
            break

        ## 동영상 딥러닝 (SSD) ##
        frameCount += 1
        if frameCount % 5 == 0:
            frame = cv2.resize(frame, None, fx=s_factor, fy=s_factor, interpolation=cv2.INTER_AREA)
            frame = ssdNet(frame)
            cv2.imshow('Video', frame)
        ######################

        key = cv2.waitKey(10)
        if key == 27:  # ESC 키
            break

    capture.release()
    cv2.destroyAllWindows()

def poseDet() :
    IMAGE_FILES = []
    BG_COLOR = (192, 192, 192)  # gray
    with mp_pose.Pose(
            static_image_mode=True,
            model_complexity=2,
            enable_segmentation=True,
            min_detection_confidence=0.5) as pose:
        for idx, file in enumerate(IMAGE_FILES):
            image = cv2.imread(file)
            image_height, image_width, _ = image.shape
            # Convert the BGR image to RGB before processing.
            results = pose.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

            if not results.pose_landmarks:
                continue
            print(
                f'Nose coordinates: ('
                f'{results.pose_landmarks.landmark[mp_pose.PoseLandmark.NOSE].x * image_width}, '
                f'{results.pose_landmarks.landmark[mp_pose.PoseLandmark.NOSE].y * image_height})'
            )

            annotated_image = image.copy()
            # Draw segmentation on the image.
            # To improve segmentation around boundaries, consider applying a joint
            # bilateral filter to "results.segmentation_mask" with "image".
            condition = np.stack((results.segmentation_mask,) * 3, axis=-1) > 0.1
            bg_image = np.zeros(image.shape, dtype=np.uint8)
            bg_image[:] = BG_COLOR
            annotated_image = np.where(condition, annotated_image, bg_image)
            # Draw pose landmarks on the image.
            mp_drawing.draw_landmarks(
                annotated_image,
                results.pose_landmarks,
                mp_pose.POSE_CONNECTIONS,
                landmark_drawing_spec=mp_drawing_styles.get_default_pose_landmarks_style())
            cv2.imwrite('/tmp/annotated_image' + str(idx) + '.png', annotated_image)
            # Plot pose world landmarks.
            mp_drawing.plot_landmarks(
                results.pose_world_landmarks, mp_pose.POSE_CONNECTIONS)

    # For webcam input:
    filename = 'c:/images/dan2.mp4'
    cap = cv2.VideoCapture(filename)
    #cap = cv2.VideoCapture(0)
    with mp_pose.Pose(
            min_detection_confidence=0.5,
            min_tracking_confidence=0.5) as pose:
        while cap.isOpened():
            success, image = cap.read()
            if not success:
                print("Ignoring empty camera frame.")
                # If loading a video, use 'break' instead of 'continue'.
                continue

            # Flip the image horizontally for a later selfie-view display, and convert
            # the BGR image to RGB.
            image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
            # To improve performance, optionally mark the image as not writeable to
            # pass by reference.
            image.flags.writeable = False
            results = pose.process(image)

            # Draw the pose annotation on the image.
            image.flags.writeable = True
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            mp_drawing.draw_landmarks(
                image,
                results.pose_landmarks,
                mp_pose.POSE_CONNECTIONS,
                landmark_drawing_spec=mp_drawing_styles.get_default_pose_landmarks_style())
            cv2.imshow('MediaPipe Pose', image)
            if cv2.waitKey(5) & 0xFF == 27:
                break
    cap.release()

def chromakey() :
    import cv2
    import mediapipe as mp
    import numpy as np
    mp_drawing = mp.solutions.drawing_utils
    mp_selfie_segmentation = mp.solutions.selfie_segmentation

    # For static images:
    IMAGE_FILES = []
    BG_COLOR = (0, 255, 0)
    MASK_COLOR = (0, 255, 0)  # white
    with mp_selfie_segmentation.SelfieSegmentation(
            model_selection=0) as selfie_segmentation:
        for idx, file in enumerate(IMAGE_FILES):
            image = cv2.imread(file)
            image_height, image_width, _ = image.shape
            # Convert the BGR image to RGB before processing.
            results = selfie_segmentation.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

            # Draw selfie segmentation on the background image.
            # To improve segmentation around boundaries, consider applying a joint
            # bilateral filter to "results.segmentation_mask" with "image".
            condition = np.stack((results.segmentation_mask,) * 3, axis=-1) > 0.1
            # Generate solid color images for showing the output selfie segmentation mask.
            fg_image = np.zeros(image.shape, dtype=np.uint8)
            fg_image[:] = MASK_COLOR
            bg_image = np.zeros(image.shape, dtype=np.uint8)
            bg_image[:] = BG_COLOR
            output_image = np.where(condition, fg_image, bg_image)
            cv2.imwrite('/tmp/selfie_segmentation_output' + str(idx) + '.png', output_image)

    # For webcam input:
    BG_COLOR = (0, 255, 0)
    cap = cv2.VideoCapture(0)
    with mp_selfie_segmentation.SelfieSegmentation(
            model_selection=1) as selfie_segmentation:
        bg_image = None
        while cap.isOpened():
            success, image = cap.read()
            if not success:
                print("Ignoring empty camera frame.")
                # If loading a video, use 'break' instead of 'continue'.
                continue

            # Flip the image horizontally for a later selfie-view display, and convert
            # the BGR image to RGB.
            image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
            # To improve performance, optionally mark the image as not writeable to
            # pass by reference.
            image.flags.writeable = False
            results = selfie_segmentation.process(image)

            image.flags.writeable = True
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

            # Draw selfie segmentation on the background image.
            # To improve segmentation around boundaries, consider applying a joint
            # bilateral filter to "results.segmentation_mask" with "image".
            condition = np.stack(
                (results.segmentation_mask,) * 3, axis=-1) > 0.1
            # The background can be customized.
            #   a) Load an image (with the same width and height of the input image) to
            #      be the background, e.g., bg_image = cv2.imread('/path/to/image/file')
            #   b) Blur the input image by applying image filtering, e.g.,
            #      bg_image = cv2.GaussianBlur(image,(55,55),0)
            if bg_image is None:
                bg_image = np.zeros(image.shape, dtype=np.uint8)
                bg_image[:] = BG_COLOR
            output_image = np.where(condition, image, bg_image)

            cv2.imshow('MediaPipe Selfie Segmentation', output_image)
            if cv2.waitKey(5) & 0xFF == 27:
                break
    cap.release()

def camControl() :
    cap = cv2.VideoCapture(0)

    mpHands = mp.solutions.hands
    hands = mpHands.Hands(static_image_mode=False,
                          max_num_hands=2,
                          min_detection_confidence=0.9,
                          min_tracking_confidence=0.9)
    mpDraw = mp.solutions.drawing_utils

    pTime = 0
    cTime = 0

    while True:
        success, img = cap.read()
        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        results = hands.process(imgRGB)
        # print(results.multi_hand_landmarks)

        if results.multi_hand_landmarks:
            for handLms in results.multi_hand_landmarks:
                for id, lm in enumerate(handLms.landmark):
                    # print(id,lm)
                    h, w, c = img.shape
                    cx, cy = int(lm.x * w), int(lm.y * h)
                    # if id ==0:
                    cv2.circle(img, (cx, cy), 3, (255, 0, 255), cv2.FILLED)
                    if id == 8: cv2.circle(img, (cx, cy), 10, (255, 0, 0), cv2.FILLED)
                    if ((190 < cx < 210) and (190 < cy < 210)):
                        cv2.putText(img, str('!!!!! IH !!!!!!'), (180, 200), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 255),
                                    3)
                    if ((cx < 80) and (cy < 50)):
                        cv2.destroyWindow('Image')
                    if ((cx > 500) and (cy < 100)):
                        ary = np.full(img.shape, (10, 10, 10), dtype=np.uint8)
                        img = cv2.subtract(img, ary)
                    if ((cx > 500) and (cy > 400)):
                        ary = np.full(img.shape, (10, 10, 10), dtype=np.uint8)
                        img = cv2.add(img, ary)
                    if ((cx < 80) and (cy > 400)):
                        img = np.clip(255 - 255 * pow(img / 127, 2), 0, 255).astype(np.uint8)
                    if ((250 < cx < 350) and (cy > 400)):
                        openImage()
                    if ((cx < 80) and (200 < cy < 300)): img = cv2.resize(img, dsize=(0, 0), fx=1.5, fy=1.5)
                    if ((cx > 600) and (200 < cy < 300)):
                        ##OpenCV용 알고리즘
                        x = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=3)
                        x = cv2.convertScaleAbs(x)

                        y = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=3)
                        y = cv2.convertScaleAbs(y)

                        img = cv2.addWeighted(x, 1, y, 1, 0)
                    if ((250 < cx < 350) and (cy < 50)):
                        ##OpenCV용 알고리즘
                        mask = np.zeros((11, 11), np.float32)
                        mask[0:][0:] = 1 / (11 * 11)
                        img = cv2.filter2D(img, -1, mask)

                mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS)

        img = cv2.flip(img, 1)
        cTime = time.time()
        fps = 1 / (cTime - pTime)
        pTime = cTime
        
        cv2.putText(img, str(int(fps)), (50, 50), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 0), 3)
        cv2.putText(img, str('EXIT'), (500, 50), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)
        cv2.putText(img, str('Dark'), (20, 110), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)
        cv2.putText(img, str('Shine'), (20, 420), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)
        cv2.putText(img, str('Parabola'), (450, 420), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)
        cv2.putText(img, str('Open Image'), (220, 420), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)
        cv2.putText(img, str('Zoom'), (500, 250), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)
        cv2.putText(img, str('Sobel'), (20, 250), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)
        cv2.putText(img, str('Blur'), (300, 50), cv2.FONT_HERSHEY_PLAIN, 2, (255, 0, 255), 3)

        cv2.imshow("Image", img)
        key = cv2.waitKey(1)
        if key == 27:  # ESC 키
            break
            camControl()

def finger() :
    import cv2
    import mediapipe as mp
    import time
    import numpy as np
    import math

    class handDetector():
        def __init__(self, mode=False, maxHands=2, detectionCon=0.8, trackCon=0.8):
            self.mode = mode
            self.maxHands = maxHands
            self.detectionCon = detectionCon
            self.trackCon = trackCon

            self.mpHands = mp.solutions.hands
            self.hands = self.mpHands.Hands(self.mode, self.maxHands, self.detectionCon, self.trackCon)
            self.mpDraw = mp.solutions.drawing_utils

        def findHands(self, img, draw=True):
            imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
            self.results = self.hands.process(imgRGB)
            # print(results.multi_hand_landmarks)

            if self.results.multi_hand_landmarks:
                for handLms in self.results.multi_hand_landmarks:
                    if draw:
                        self.mpDraw.draw_landmarks(img, handLms, self.mpHands.HAND_CONNECTIONS)
            return img

        def findPosition(self, img, handNo=0, draw=True):

            lmlist = []
            if self.results.multi_hand_landmarks:
                myHand = self.results.multi_hand_landmarks[handNo]
                for id, lm in enumerate(myHand.landmark):
                    h, w, c = img.shape
                    cx, cy = int(lm.x * w), int(lm.y * h)
                    lmlist.append([id, lm.x, lm.y])
                    if draw:
                        cv2.circle(img, (cx, cy), 3, (0, 0, 255), cv2.FILLED)
                        if id == 4: cv2.circle(img, (cx, cy), 10, (255, 0, 0), cv2.FILLED)
                        if id == 8: cv2.circle(img, (cx, cy), 10, (255, 0, 0), cv2.FILLED)

            return lmlist

    def chromakey():
        import cv2
        import mediapipe as mp
        import numpy as np
        mp_drawing = mp.solutions.drawing_utils
        mp_selfie_segmentation = mp.solutions.selfie_segmentation

        # For static images:
        IMAGE_FILES = []
        BG_COLOR = (0, 255, 0)
        MASK_COLOR = (0, 255, 0)  # white
        with mp_selfie_segmentation.SelfieSegmentation(
                model_selection=0) as selfie_segmentation:
            for idx, file in enumerate(IMAGE_FILES):
                image = cv2.imread(file)
                image_height, image_width, _ = image.shape
                # Convert the BGR image to RGB before processing.
                results = selfie_segmentation.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

                # Draw selfie segmentation on the background image.
                # To improve segmentation around boundaries, consider applying a joint
                # bilateral filter to "results.segmentation_mask" with "image".
                condition = np.stack((results.segmentation_mask,) * 3, axis=-1) > 0.1
                # Generate solid color images for showing the output selfie segmentation mask.
                fg_image = np.zeros(image.shape, dtype=np.uint8)
                fg_image[:] = MASK_COLOR
                bg_image = np.zeros(image.shape, dtype=np.uint8)
                bg_image[:] = BG_COLOR
                output_image = np.where(condition, fg_image, bg_image)
                cv2.imwrite('/tmp/selfie_segmentation_output' + str(idx) + '.png', output_image)

        # For webcam input:
        BG_COLOR = (0, 255, 0)
        cap = cv2.VideoCapture(0)
        with mp_selfie_segmentation.SelfieSegmentation(
                model_selection=1) as selfie_segmentation:
            bg_image = cv2.imread("C:/images/bob.jpg")
            while cap.isOpened():
                success, image = cap.read()
                if not success:
                    print("Ignoring empty camera frame.")
                    # If loading a video, use 'break' instead of 'continue'.
                    continue

                # Flip the image horizontally for a later selfie-view display, and convert
                # the BGR image to RGB.
                image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
                # To improve performance, optionally mark the image as not writeable to
                # pass by reference.
                image.flags.writeable = False
                results = selfie_segmentation.process(image)

                image.flags.writeable = True
                image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

                # Draw selfie segmentation on the background image.
                # To improve segmentation around boundaries, consider applying a joint
                # bilateral filter to "results.segmentation_mask" with "image".
                condition = np.stack(
                    (results.segmentation_mask,) * 3, axis=-1) > 0.1
                # The background can be customized.
                #   a) Load an image (with the same width and height of the input image) to
                #      be the background, e.g., bg_image = cv2.imread('/path/to/image/file')
                #   b) Blur the input image by applying image filtering, e.g.,
                #      bg_image = cv2.GaussianBlur(image,(55,55),0)
                if bg_image is None:
                    bg_image = np.zeros(image.shape, dtype=np.uint8)
                    bg_image[:] = BG_COLOR
                output_image = np.where(condition, image, bg_image)

                cv2.imshow('MediaPipe Selfie Segmentation', output_image)
                if cv2.waitKey(5) & 0xFF == 27:
                    break
                main()

    def face():
        import cv2
        import mediapipe as mp
        mp_face_detection = mp.solutions.face_detection
        mp_drawing = mp.solutions.drawing_utils

        # For static images:
        IMAGE_FILES = []
        with mp_face_detection.FaceDetection(
                model_selection=1, min_detection_confidence=0.5) as face_detection:
            for idx, file in enumerate(IMAGE_FILES):
                image = cv2.imread(file)
                # Convert the BGR image to RGB and process it with MediaPipe Face Detection.
                results = face_detection.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

                # Draw face detections of each face.
                if not results.detections:
                    continue
                annotated_image = image.copy()
                for detection in results.detections:
                    print('Nose tip:')
                    print(mp_face_detection.get_key_point(
                        detection, mp_face_detection.FaceKeyPoint.NOSE_TIP))
                    mp_drawing.draw_detection(annotated_image, detection)
                cv2.imwrite('/tmp/annotated_image' + str(idx) + '.png', annotated_image)

        # For webcam input:
        cap = cv2.VideoCapture(0)
        with mp_face_detection.FaceDetection(
                model_selection=0, min_detection_confidence=0.5) as face_detection:
            while cap.isOpened():
                success, image = cap.read()
                if not success:
                    print("Ignoring empty camera frame.")
                    # If loading a video, use 'break' instead of 'continue'.
                    continue

                # Flip the image horizontally for a later selfie-view display, and convert
                # the BGR image to RGB.
                image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
                # To improve performance, optionally mark the image as not writeable to
                # pass by reference.
                image.flags.writeable = False
                results = face_detection.process(image)

                # Draw the face detection annotations on the image.
                image.flags.writeable = True
                image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
                if results.detections:
                    for detection in results.detections:
                        mp_drawing.draw_detection(image, detection)
                cv2.imshow('MediaPipe Face Detection', image)
                if cv2.waitKey(5) & 0xFF == 27:
                    break
                main()
        cap.release()

    def main():
        cTime = time.time()
        pTime = 0
        cTime = 0
        cap = cv2.VideoCapture(0)
        detector = handDetector()

        while True:
            success, img = cap.read()
            img = detector.findHands(img)
            lmlist = detector.findPosition(img)
            h, w, c = img.shape
            if len(lmlist) != 0:
                # print(lmlist[8][1])
                x1 = float(lmlist[4][1])
                y1 = float(lmlist[4][2])
                x2 = float(lmlist[8][1])
                y2 = float(lmlist[8][2])
                x3 = float(lmlist[12][1])
                y3 = float(lmlist[12][2])
                x4 = float(lmlist[16][1])
                y4 = float(lmlist[16][2])
                x5 = float(lmlist[20][1])
                y5 = float(lmlist[20][2])

                x = (x2 - x1) * w
                y = (y2 - y1) * h
                d = (x * x) + (y * y)
                # print(d)
                # cv2.circle(lmlist[4], (cx, cy), 3, (255, 0, 255), cv2.FILLED)
                # cv2.circle(img, (int(300), int(300)), int(d/100), (0, 255, 0), 3)
                cv2.putText(img, str(int(d)), (300, 70), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)

                # img = cv2.resize(img, dsize=(0, 0), fx=float(d/10000), fy=float(d/10000), interpolation=cv2.INTER_CUBIC)
                # img = cv2.rectangle(img, (10,10), (200, 200), (0, 255, 0), 3)
                ###### V구하기 ######
                vx1 = (x1 - x5) * w
                vy1 = (y1 - y5) * h
                vx2 = (x5 - x4) * w
                vy2 = (y5 - y4) * h
                vx3 = (x4 - x1) * w
                vy3 = (y4 - y1) * h
                vd1 = (vx1 * vx1) + (vy1 * vy1)
                vd2 = (vx2 * vx2) + (vy2 * vy2)
                vd3 = (vx3 * vx3) + (vy3 * vy3)
                # print(vd1, vd2, vd3)
                if ((y1 > y2) and (y4 > y2) and (y5 > y2) and (y1 > y3) and (y4 > y3) and (y5 > y3) and (
                        vd1 < 300) and (vd2 < 300) and (vd3 < 300)):
                    chromakey()  # 캡처(스폰지밥) V포즈
                ############################################
                elif d < 200:
                    cv2.destroyWindow('MediaPipe Selfie Segmentation')  # 창닫기 (오케이)
                    cv2.waitKey(100)
                if (x5 > x1) and (x4 > x2) and (x2 < x3 < x4):
                    img = np.clip(255 - 255 * pow(img / 127, 2), 0, 255).astype(np.uint8)  # 반전

                theta = math.atan2(y, x) * (180 / math.pi)
                if (d > 16000):
                    m = cv2.imread("C:/images/bk.png")
                    img = img + m
                    cp = (img.shape[1] / 2, img.shape[0] / 2)  # 영상의 가로 1/2, 세로 1/2
                    rot = cv2.getRotationMatrix2D(cp, theta, 0.8)
                    img = cv2.warpAffine(img, rot, (0, 0))  # 돌리기

                ymf1 = float(lmlist[9][2])
                ymf2 = float(lmlist[13][2])
                ymf3 = float(lmlist[17][2])
                ymf1_val = abs(ymf1 - y3) * h
                ymf2_val = abs(ymf2 - y4) * h
                ymf3_val = abs(ymf3 - y5) * h
                if (ymf1_val < 10) and (ymf2_val < 10) and (ymf3_val < 10): face()  # 얼굴검출

            cTime = time.time()
            fps = 1 / (cTime - pTime)
            pTime = cTime

            cv2.putText(img, str(int(fps)), (10, 70), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)

            cv2.imshow("Image", img)
            cv2.waitKey(1)

    if __name__ == "__main__":
        main()

def videofinger() :
    LENGTH_THRESHOLD = 50

    detector = HandDetector(detectionCon=0.8, maxHands=1)

    cap_cam = cv2.VideoCapture(0)
    cap_video = cv2.VideoCapture('C:/images/blackpink.mp4')
    cap_cam.set(cv2.CAP_PROP_FRAME_WIDTH, 300)
    cap_cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 300)

    w = int(cap_cam.get(cv2.CAP_PROP_FRAME_WIDTH))

    total_frames = int(cap_video.get(cv2.CAP_PROP_FRAME_COUNT))
    _, video_img = cap_video.read()

    def draw_timeline(img, rel_x):
        img_h, img_w, _ = img.shape
        timeline_w = max(int(img_w * rel_x) - 50, 50)
        cv2.rectangle(img, pt1=(50, img_h - 50), pt2=(timeline_w, img_h - 49), color=(0, 0, 255), thickness=-1)

    rel_x = 0
    frame_idx = 0
    draw_timeline(video_img, 0)

    while cap_cam.isOpened():
        _, cam_img = cap_cam.read()
        cam_img = cv2.flip(cam_img, 1)

        hands, cam_img = detector.findHands(cam_img)

        if hands:
            lm_list = hands[0]['lmList']
            fingers = detector.fingersUp(hands[0])

            length, info, cam_img = detector.findDistance(lm_list[4], lm_list[8], cam_img)  # thumb, index

            if fingers == [0, 0, 0, 0, 0]:  # 멈춰
                pass
            else:  # 영상 계속 틀어짐
                if length < LENGTH_THRESHOLD:
                    rel_x = lm_list[4][0] / w
                    frame_idx = int(rel_x * total_frames)
                    frame_idx = min(max(frame_idx, 0), total_frames)

                    cap_video.set(1, frame_idx)
                else:
                    frame_idx += 1
                    rel_x = frame_idx / total_frames

                _, video_img = cap_video.read()
                draw_timeline(video_img, rel_x)

        cv2.imshow('video', video_img)
        cv2.imshow('cam', cam_img)
        if cv2.waitKey(1) == ord('q'):
            break

def facedetect() :
    detector = dlib.get_frontal_face_detector()
    sp = dlib.shape_predictor('C:/CookPython/mediapipe/facedet/shape_predictor_68_face_landmarks.dat')
    facerec = dlib.face_recognition_model_v1(
        'C:/CookPython/mediapipe/facedet/dlib_face_recognition_resnet_model_v1.dat')

    def read_img(img_path):
        img = cv2.imread(img_path)
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        return img

    def encode_face(img):
        dets = detector(img, 1)

        if len(dets) == 0:
            return np.empty(0)

        for k, d in enumerate(dets):
            shape = sp(img, d)
            face_descriptor = facerec.compute_face_descriptor(img, shape)

            return np.array(face_descriptor)

    img1_path = "C:/images/mee.jpg"  # me
    img1 = read_img(img1_path)
    img1_encoded = encode_face(img1)
    # img2 = read_img(img2_path)

    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        exit()

    while True:
        ret, img2 = cap.read()
        if not ret:
            break

        img2 = cv2.resize(img2, (640, img2.shape[0] * 640 // img2.shape[1]))
        img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2RGB)
        img2_encoded = encode_face(img2)

        ret, frame = cap.read()  # Read 결과와 frame

        if (ret):
            cv2.imshow('', frame)  # 컬러 화면 출력
            if cv2.waitKey(1) == ord('q'):
                break

        if len(img2_encoded) == 0:
            continue

        dist = np.linalg.norm(img1_encoded - img2_encoded, axis=0)

        if dist < 0.5:
            print("규혁이입니다.")
        else:
            print("누~구~세~요~???")
            messagebox.showerror("누구요.", "누~구~세~요~?")

        # print('%s, Distance: %s' % (dist < 0.6, dist))

    cap.release()
    cv2.destroyAllWindows()

## 전역
m_InputImage, m_OutputImage = None, None
m_inH, m_inW, m_outH, m_outW = [0] * 4
window, canvas, paper = None, None, None
filename = ""
RGB, RR, GG, BB = 3, 0, 1, 2
cvInPhoto, cvOutPhoto = None, None
sx, sy, ex, ey = [-1]*4
boxLine = None

## 메인
window = Tk()

window.title("컬러 영상처리 Ver 3.0 (Include OpenCV)")
window.geometry("1200x700")
window.resizable(width=FALSE, height=FALSE)

status = Label(window, text='정보', bd=1, relief=SUNKEN, anchor=W)
status.pack(side=BOTTOM, fill=X)

chk = IntVar()
chk2 = IntVar()
para = Checkbutton(window, text = "물체 검출", variable = chk2, command=radioFunc2)
reverse = Checkbutton(window, text = "캠 물체 검출", variable = chk, command=radioFunc)


#reverse.place(x=0, y=10)
#para.place(x=0, y=30)


mainMenu = Menu(window)
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=openImage)
fileMenu.add_separator()
fileMenu.add_command(label='저장', command=saveImage)

pixelMenu = Menu(mainMenu)
mainMenu.add_cascade(label='화소점 처리', menu=pixelMenu)
pixelMenu.add_command(label='밝기 조절', command=lightImage)
pixelMenu.add_command(label='곱셈/나눗셈 연산', command=muldivImage)
pixelMenu.add_command(label='이진화', command=bwImage)
pixelMenu.add_command(label='반전', command=reverseImage)
pixelMenu.add_command(label='반전(마우스)', command=reverseImageMouse)
pixelMenu.add_separator()
pixelMenu.add_command(label='감마', command=gammaImage)
pixelMenu.add_command(label='파라볼라', command=paraImage)
pixelMenu.add_separator()
pixelMenu.add_command(label='평활화', command=equalizationImage)
pixelMenu.add_command(label='열화상 카메라', command=fireImage)

mathMenu = Menu(mainMenu)
mainMenu.add_cascade(label='기하학적 처리', menu=mathMenu)
mathMenu.add_command(label='확대', command=zoomImage)
mathMenu.add_command(label='축소', command=zoomoutImage)
mathMenu.add_command(label='이동', command=moveImage)
mathMenu.add_command(label='회전', command=rotateImage)
mathMenu.add_command(label='상하반전', command=udMirImage)
mathMenu.add_command(label='좌우반전', command=lrMirImage)

areaMenu = Menu(mainMenu)
mainMenu.add_cascade(label='영역 처리', menu=areaMenu)
areaMenu.add_command(label='엠보싱', command=embossImage)
areaMenu.add_command(label='블러링', command=blurImage)
areaMenu.add_command(label='가우시안', command=gaussianImage)
areaMenu.add_command(label='샤프닝', command=sharpImage)
areaMenu.add_command(label='로버츠', command=robertsImage)
areaMenu.add_command(label='소벨', command=sobelImage)
areaMenu.add_command(label='프리윗', command=prewittImage)
areaMenu.add_command(label='라플라시안', command=laplacianImage)
areaMenu.add_command(label='유사연산자', command=homogeneityImage)
areaMenu.add_command(label='차연산자', command=DifferenceImage)
areaMenu.add_command(label='LoG', command=LoGImage)
areaMenu.add_command(label='DoG', command=DoGImage)

opencvMenu = Menu(mainMenu)
mainMenu.add_cascade(label='OpenCV 화소점처리', menu=opencvMenu)
opencvMenu.add_command(label='흑백', command=grayImage_cv)
opencvMenu.add_command(label='이진화', command=bwImage_cv)
opencvMenu.add_command(label='밝은 이미지', command=addImage_cv)
opencvMenu.add_command(label='어두운 이미지', command=subImage_cv)
opencvMenu.add_command(label='이미지 곱셈/나눗셈', command=mulImage_cv)
opencvMenu.add_command(label='반전', command=reverseImage_cv)
opencvMenu.add_command(label='감마보정', command=gammaImage_cv)
opencvMenu.add_command(label='파라볼라', command=paraImage_cv)
opencvMenu.add_command(label='', command=None)
pixelMenu.add_separator()
opencvMenu.add_command(label='평활화', command=equalizationImage_cv)

opencvMenu1 = Menu(mainMenu)
mainMenu.add_cascade(label='OpenCV 기하학적처리', menu=opencvMenu1)
opencvMenu1.add_command(label='회전', command=rotImage_cv)

opencvMenu2 = Menu(mainMenu)
mainMenu.add_cascade(label='OpenCV 영역처리', menu=opencvMenu2)
opencvMenu2.add_command(label='엠보싱', command=embossImage_cv)
opencvMenu2.add_command(label='블러링', command=blurImage_cv)
opencvMenu2.add_command(label='가우시안', command=gaussianImage_cv)
opencvMenu2.add_command(label='샤프닝', command=sharpImage_cv)
opencvMenu2.add_command(label='소벨', command=sobelImage_cv)
opencvMenu2.add_command(label='프리윗', command=prewittImage_cv)
opencvMenu2.add_command(label='로버츠', command=robertImage_cv)

opencvMenu3 = Menu(mainMenu)
mainMenu.add_cascade(label='OpenCV 기타', menu=opencvMenu3)
opencvMenu3.add_command(label='카툰이미지', command=cartoonImage_cv)
opencvMenu3.add_command(label='사람얼굴인식', command=faceDetect_cv)
opencvMenu3.add_command(label='차량인식', command=carDetect_cv)

opencvMenu4 = Menu(mainMenu)
mainMenu.add_cascade(label='물체 검출', menu=opencvMenu4)
opencvMenu4.add_command(label='이미지 물체 검출', command=imgDeep)
opencvMenu4.add_command(label='캠 물체 검출', command=camDeep)
opencvMenu4.add_command(label='캠 포즈 검출', command=poseDet)
opencvMenu4.add_command(label='크로마키', command=chromakey)
opencvMenu4.add_command(label='캡으로 선택하기', command=camControl)
opencvMenu4.add_command(label='손으로 영상제어', command=finger)
opencvMenu4.add_command(label='손으로 영상재생', command=videofinger)
opencvMenu4.add_command(label='얼굴 나만 인식', command=facedetect)

#start = time.time()  # 시작 시간 저장
#print("time :", time.time() - start)  # 현재시각 - 시작시간 = 실행 시간


window.mainloop()