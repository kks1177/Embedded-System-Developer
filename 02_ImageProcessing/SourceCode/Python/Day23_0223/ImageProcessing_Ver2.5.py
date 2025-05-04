# Image Processing_Ver2.6.py (Color Image Processing with OpenCV)
# Image Processing using python Ver 2.5 (include OpenCV, 머신러닝 + 딥러닝)
# 3차원 Color Image Procsessing

# 칼라, OpenCV, 상태바, 마우스 이벤트, 박스라인


import cv2
import numpy as np
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import random
import time
import datetime
import threading
import pafy
import math

from collections import deque
from imutils.video import VideoStream
import argparse
import imutils

import matplotlib.pyplot as plt  # 다양한 plot기능을 가진 Python Plot Library, 이미지를 zoom하거나 하나의 화면에 여러개의 이미지를 보고자 할 때 유용

# *************************** < 전역 변수부 > ***************************
mainMenu = None
inImage, outImage = [], []  # unsigned char** inImage, ** outImage
inH, inW, outH, outW = [0] * 4  # 초기화
inPhoto, outPhoto = None, None
window, canvas, paper = None, None, None  # 초기화
histoImage, window_histo, canvas_histo, paper_histo = None, None, None, None  # 초기화
RGB = 3  # 전역 상수 선언
RR, GG, BB = 0, 1, 2
stateBar, boxLine = None, None  # 상태바, 박스라인
filename = ''
sx, sy, ex, ey = [-1] * 4  # start x, start y, end x, end y        # -1 로 초기화 ==> 0을 값으로 가지고 있을수도 있기 때문
nowTime = datetime.datetime.now().strftime('%y-%m-%d_%H-%M-%S')
url = ""


# *************************** < 메뉴 함수 정의부 > ***************************
## 전체 메뉴 ##
def mainThread():
    # 전역 변수
    global mainMenu
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    ### 메뉴 틀 ###
    mainMenu = Menu(window)  # 메뉴 탭
    window.config(menu=mainMenu)

    ## 파일 메뉴 ##
    fileMenu = Menu(mainMenu)  # 상위 메뉴 (파일)
    mainMenu.add_cascade(label='파일', menu=fileMenu)
    fileMenu.add_command(label='열기', command=openImage)  # add_command : 누르면 실행
    fileMenu.add_command(label='저장', command=saveImage)
    fileMenu.add_separator()
    fileMenu.add_command(label='종료')

    functionMenu()  # 영상처리 기능 메뉴
    CVfunctionMenu()  # OpenCV 영상처리 기능 메뉴
    AIfunctionMenu()  # 인공지능 기능 메뉴

    window.mainloop()

## 영상처리 기능 메뉴 ##
def functionMenu():
    # 전역 변수
    global mainMenu
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    funcMenu = Menu(mainMenu)  # 상위 메뉴 (기능)
    mainMenu.add_cascade(label='영상 처리', menu=funcMenu)

    # 1. 화소점 처리
    pxDotMenu = Menu(funcMenu)  # 상위 메뉴 (파일)
    clear = Menu(pxDotMenu)  # 선명도 조절
    BW = Menu(pxDotMenu)  # 흑백
    BITCalc = Menu(pxDotMenu)  # BIT 연산
    parabola = Menu(pxDotMenu)  # 파라볼라 변환

    funcMenu.add_cascade(label='1. 화소점 처리', menu=pxDotMenu)
    pxDotMenu.add_command(label='1. 동일 영상', command=equalImage)
    pxDotMenu.add_command(label='2. 반전 영상', command=reverseImage)
    pxDotMenu.add_command(label='3. 밝기 조절 (입력)', command=brightControlImage)
    pxDotMenu.add_cascade(label='4. 선명도 조절 (입력)', menu=clear)  # command=lambda: btnClick('이거다'))
    clear.add_command(label='선명하게', command=lambda: clearControlImage(1))
    clear.add_command(label='흐릿하게', command=lambda: clearControlImage(2))
    pxDotMenu.add_cascade(label='5. 흑백', menu=BW)
    BW.add_command(label='GrayScale', command=lambda: BWImage(1))
    BW.add_command(label='128 기준', command=lambda: BWImage(2))
    BW.add_command(label='평균값 기준', command=lambda: BWImage(3))
    BW.add_command(label='입력 범위 기준 (2입력)', command=lambda: BWImage(4))
    pxDotMenu.add_cascade(label='6. 비트 연산', menu=BITCalc)
    BITCalc.add_command(label='AND 연산 (입력)', command=lambda: BitCalc(1))
    BITCalc.add_command(label='OR 연산 (입력)', command=lambda: BitCalc(2))
    BITCalc.add_command(label='XOR 연산 (입력)', command=lambda: BitCalc(3))
    BITCalc.add_command(label='NOT 연산', command=lambda: BitCalc(4))
    pxDotMenu.add_command(label='7. 감마 변환 (입력)', command=gammaImage)
    pxDotMenu.add_command(label='8. 범위 강조 (2입력)', command=rangeEmphasis)
    pxDotMenu.add_cascade(label='9. 파라볼라 변환', menu=parabola)
    parabola.add_command(label='파라볼라 CAP', command=lambda: parabolaImage(1))
    parabola.add_command(label='파라볼라 CUP', command=lambda: parabolaImage(2))
    pxDotMenu.add_command(label='10. 명암대비 스트래칭 (입력)', command=stretchedImage)

    # 2. 히스토그램 처리
    histoMenu = Menu(funcMenu)  # 상위 메뉴 (파일)

    funcMenu.add_cascade(label='2. 히스토그램 처리', menu=histoMenu)
    # histoMenu.add_command(label='1. 히스토그램 출력', command=printHisto)
    histoMenu.add_command(label='1. 히스토그램 스트래칭', command=histoStretch)
    histoMenu.add_command(label='2. 히스토그램 엔드-인 탐색', command=histoEndIn)
    histoMenu.add_command(label='3. 히스토그램 평활화', command=histoEqual)

    # 3. 화소 영역 처리
    pxAreaMenu = Menu(funcMenu)  # 상위 메뉴 (파일)
    blurring = Menu(pxAreaMenu)  # 블러링
    Sharpning = Menu(pxAreaMenu)  # 샤프닝

    funcMenu.add_cascade(label='3. 화소 영역 처리', menu=pxAreaMenu)
    pxAreaMenu.add_command(label='1. 엠보싱', command=embossing)
    pxAreaMenu.add_cascade(label='2. 블러링', menu=blurring)
    blurring.add_command(label='3x3 블러링', command=lambda: blurringImage(1))
    blurring.add_command(label='5x5 블러링', command=lambda: blurringImage(2))
    blurring.add_command(label='스무딩 (가우시안)', command=smoothing)
    pxAreaMenu.add_cascade(label='3. 샤프닝', menu=Sharpning)
    Sharpning.add_command(label='샤프닝', command=lambda: sharpningImage(1))
    Sharpning.add_command(label='HPF 처리 샤프닝', command=lambda: sharpningImage(2))
    Sharpning.add_command(label='LPF 처리 샤프닝', command=lambda: sharpningImage(3))

    # 4. 엣지 검출 처리
    edgeDetectMenu = Menu(funcMenu)  # 상위 메뉴 (파일)
    shiftDiffer = Menu(edgeDetectMenu)

    funcMenu.add_cascade(label='4. 엣지 검출 처리', menu=edgeDetectMenu)
    edgeDetectMenu.add_cascade(label='이동과 차분 엣지', menu=shiftDiffer)
    shiftDiffer.add_command(label='수직 엣지', command=lambda: shiftDifferEdgeImage(1))
    shiftDiffer.add_command(label='수평 엣지', command=lambda: shiftDifferEdgeImage(2))
    shiftDiffer.add_command(label='수직 수평 엣지', command=lambda: shiftDifferEdgeImage(3))

    # 5. 기하학 처리
    geometryMenu = Menu(funcMenu)  # 상위 메뉴 (파일)
    mirroring = Menu(geometryMenu)  # 미러링
    Turn = Menu(geometryMenu)  # 회전
    turnRight = Menu(Turn)  # 시계 방향 회전
    turnLeft = Menu(Turn)  # 반시계 방향 회전
    turnFree = Menu(Turn)  # 자유 회전
    size = Menu(geometryMenu)  # 이미지 사이즈

    funcMenu.add_cascade(label='5. 기하학 처리', menu=geometryMenu)
    geometryMenu.add_cascade(label='1. 미러링', menu=mirroring)
    mirroring.add_command(label='좌우 미러링', command=lambda: mirroringImage(1))
    mirroring.add_command(label='상하 미러링', command=lambda: mirroringImage(2))
    mirroring.add_command(label='상하+좌우 미러링', command=lambda: mirroringImage(3))
    geometryMenu.add_cascade(label='2. 회전', menu=Turn)
    Turn.add_cascade(label='1. 시계 방향', menu=turnRight)
    turnRight.add_command(label='90도', command=lambda: turnImage(1))
    turnRight.add_command(label='180도', command=lambda: turnImage(2))
    turnRight.add_command(label='270도', command=lambda: turnImage(3))
    Turn.add_cascade(label='2. 반시계 방향', menu=turnLeft)
    turnLeft.add_command(label='90도', command=lambda: turnImage(4))
    turnLeft.add_command(label='180도', command=lambda: turnImage(5))
    turnLeft.add_command(label='270도', command=lambda: turnImage(6))
    Turn.add_cascade(label='3. 자유 회전 (입력)', menu=turnFree)
    turnFree.add_command(label='자유 회전 (백워딩 + 중앙)', command=lambda: turnImage(7))
    geometryMenu.add_cascade(label='3. 확대/축소', menu=size)
    size.add_command(label='이미지 크기 확대 (백워딩)', command=lambda: imageSizeUpDown(1))
    size.add_command(label='이미지 크기 축소 (백워딩)', command=lambda: imageSizeUpDown(2))
    # geometryMenu.add_command(label='4. 이미지 이동', command=moveImage)
    # geometryMenu.add_command(label='5. 워핑', command=warpingImage)
## OpenCV용 메뉴 ##
def CVfunctionMenu():
    # 전역 변수
    global mainMenu
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    openCVfuncMenu = Menu(mainMenu)  # 상위 메뉴 (OpenCV)
    mainMenu.add_cascade(label='OpenCV', menu=openCVfuncMenu)

    # 1. 화소점 처리_OpenCV
    CVpxDotMenu = Menu(openCVfuncMenu)  # 상위 메뉴 (파일)
    CVclear = Menu(CVpxDotMenu)  # 선명도 조절
    CVBW = Menu(CVpxDotMenu)  # 흑백
    CVBITCalc = Menu(CVpxDotMenu)  # BIT 연산
    CVparabola = Menu(CVpxDotMenu)  # 파라볼라 변환

    openCVfuncMenu.add_cascade(label='1. 화소점 처리_CV', menu=CVpxDotMenu)
    CVpxDotMenu.add_command(label='1.동일 영상_CV', command=cvEqualImage)
    CVpxDotMenu.add_command(label='2.반전 영상_CV', command=cvReverseImage)
    CVpxDotMenu.add_command(label='3. 밝기 조절_CV (입력)', command=cvBrightControlImage)
    CVpxDotMenu.add_cascade(label='4. 선명도 조절_CV (입력)', menu=CVclear)  # command=lambda: btnClick('이거다'))
    CVclear.add_command(label='선명하게_CV', command=lambda: cvClearControlImage(1))
    CVclear.add_command(label='흐릿하게_CV', command=lambda: cvClearControlImage(2))
    CVpxDotMenu.add_cascade(label='5. 흑백_CV', menu=CVBW)
    CVBW.add_command(label='GrayScale_CV', command=lambda: cvBWImage(1))
    CVBW.add_command(label='128 기준_CV', command=lambda: cvBWImage(2))
    CVBW.add_command(label='평균값 기준_CV', command=lambda: cvBWImage(3))
    CVBW.add_command(label='카툰이미지_CV', command=lambda: cvBWImage(4))
    # CVBW.add_command(label='입력 범위 기준_CV (2입력)', command=lambda: cvBWImage(5))
    CVpxDotMenu.add_cascade(label='6. 비트 연산_CV', menu=CVBITCalc)
    CVBITCalc.add_command(label='AND 연산_CV (입력)', command=lambda: cvBitCalcImage(1))
    CVBITCalc.add_command(label='OR 연산_CV (입력)', command=lambda: cvBitCalcImage(2))
    CVBITCalc.add_command(label='XOR 연산_CV (입력)', command=lambda: cvBitCalcImage(3))
    CVBITCalc.add_command(label='NOT 연산_CV', command=lambda: cvBitCalcImage(4))
    # CVpxDotMenu.add_command(label='7. 감마 변환_CV (입력)', command=cvGammaImage)
    # CVpxDotMenu.add_command(label='8. 범위 강조_CV (2입력)', command=cvRangeEmphasis)
    # CVpxDotMenu.add_cascade(label='9. 파라볼라 변환_CV', menu=CVparabola)
    # CVparabola.add_command(label='파라볼라 CAP_CV', command=lambda: cvParabolaImage(1))
    # CVparabola.add_command(label='파라볼라 CUP_CV', command=lambda: cvParabolaImage(2))
    # CVpxDotMenu.add_command(label='10. 명암대비 스트래칭_CV (입력)', command=cvStretchedImage)

    # 2. 히스토그램 처리_OpenCV
    CVhistoMenu = Menu(openCVfuncMenu)  # 상위 메뉴 (파일)

    openCVfuncMenu.add_cascade(label='2. 히스토그램 처리_CV', menu=CVhistoMenu)
    # CVhistoMenu.add_command(label='1. 히스토그램 출력_CV', command=cvPrintHisto)
    CVhistoMenu.add_command(label='1. 히스토그램 스트레칭_CV', command=cvHistoStretch)
    CVhistoMenu.add_command(label='2. 히스토그램 엔드-인 탐색_CV', command=cvHistoEndIn)
    CVhistoMenu.add_command(label='3. 히스토그램 평활화_CV', command=cvHistoEqual)

    # 3. 화소 영역 처리_OpenCV
    CVpxAreaMenu = Menu(openCVfuncMenu)  # 상위 메뉴 (파일)
    CVblurring = Menu(CVpxAreaMenu)  # 블러링
    CVSharpening = Menu(CVpxAreaMenu)  # 샤프닝

    openCVfuncMenu.add_cascade(label='3. 화소 영역 처리_CV', menu=CVpxAreaMenu)
    CVpxAreaMenu.add_command(label='1. 엠보싱_CV', command=cvEmbossing)
    CVpxAreaMenu.add_cascade(label='2. 블러링_CV', menu=CVblurring)
    CVblurring.add_command(label='3x3 블러링_CV', command=lambda: cvBlurring(1))
    CVblurring.add_command(label='5x5 블러링_CV', command=lambda: cvBlurring(2))
    CVblurring.add_command(label='가우시안 블러링_CV', command=lambda: cvBlurring(3))
    CVpxAreaMenu.add_cascade(label='3. 샤프닝_CV', menu=CVSharpening)
    CVSharpening.add_command(label='샤프닝_CV', command=lambda: cvSharpeningImage(1))
    CVSharpening.add_command(label='HPF 처리 샤프닝_CV', command=lambda: cvSharpeningImage(2))
    CVSharpening.add_command(label='LPF 처리 샤프닝_CV', command=lambda: cvSharpeningImage(3))

    # 4. 엣지 검출_OpenCV
    CVedgeDetectMenu = Menu(openCVfuncMenu)
    CVshiftDiffer = Menu(CVedgeDetectMenu)
    CVcontour = Menu(CVedgeDetectMenu)
    CVcorner = Menu(CVedgeDetectMenu)

    openCVfuncMenu.add_cascade(label='4. 엣지 검출_CV', menu=CVedgeDetectMenu)
    CVedgeDetectMenu.add_cascade(label='1.이동과 차분 엣지', menu=CVshiftDiffer)
    CVshiftDiffer.add_command(label='수직 엣지_CV', command=lambda: cvShiftDifferEdgeImage(1))
    CVshiftDiffer.add_command(label='수평 엣지_CV', command=lambda: cvShiftDifferEdgeImage(2))
    CVedgeDetectMenu.add_command(label='2.라플라시안 엣지_CV', command=cvLaplacianImage)
    CVedgeDetectMenu.add_command(label='3.캐니 엣지_CV', command=cvCannyImage)
    CVedgeDetectMenu.add_cascade(label='4.윤곽선 검출', menu=CVcontour)
    CVcontour.add_command(label='일반_CV', command=lambda: cvContourImage(1))
    CVcontour.add_command(label='다각형 근사_CV', command=lambda: cvContourImage(2))
    CVedgeDetectMenu.add_cascade(label='5.코너 검출', menu=CVcorner)
    CVcorner.add_command(label='GFTT-1_CV', command=lambda: cvCornerImage(1))
    CVcorner.add_command(label='GFTT-2_CV', command=lambda: cvCornerImage(2))
    CVcorner.add_command(label='Harris_CV', command=lambda: cvCornerImage(3))
    CVcorner.add_command(label='FAST_CV', command=lambda: cvCornerImage(4))


    # 5. 기하학 처리_OpenCV
    CVgeometryMenu = Menu(openCVfuncMenu)  # 상위 메뉴 (파일)
    CVmirroring = Menu(CVgeometryMenu)  # 미러링
    CVTurn = Menu(CVgeometryMenu)  # 회전
    # CVturnRight = Menu(CVTurn)  # 시계 방향 회전
    # CVturnLeft = Menu(CVTurn)  # 반시계 방향 회전
    # CVturnFree = Menu(CVTurn)  # 자유 회전
    CVsize = Menu(CVgeometryMenu)  # 이미지 사이즈

    openCVfuncMenu.add_cascade(label='5. 기하학 처리_CV', menu=CVgeometryMenu)
    CVgeometryMenu.add_cascade(label='1. 미러링_CV', menu=CVmirroring)
    CVmirroring.add_command(label='좌우 미러링_CV', command=lambda: cvMirroringImage(1))
    CVmirroring.add_command(label='상하 미러링_CV', command=lambda: cvMirroringImage(2))
    CVmirroring.add_command(label='상하+좌우 미러링_CV', command=lambda: cvMirroringImage(3))
    CVgeometryMenu.add_cascade(label='2. 회전_CV', menu=CVTurn)
    # CVTurn.add_cascade(label='1. 시계 방향_CV', menu=CVturnRight)
    # CVturnRight.add_command(label='90도_CV', command=lambda: cvTurnImage(1))
    # CVturnRight.add_command(label='180도_CV', command=lambda: cvTurnImage(2))
    # CVturnRight.add_command(label='270도_CV', command=lambda: cvTurnImage(3))
    # CVTurn.add_cascade(label='2. 반시계 방향_CV', menu=CVturnLeft)
    # CVturnLeft.add_command(label='90도_CV', command=lambda: cvTurnImage(4))
    # CVturnLeft.add_command(label='180도_CV', command=lambda: cvTurnImage(5))
    # CVturnLeft.add_command(label='270도_CV', command=lambda: cvTurnImage(6))
    # CVTurn.add_cascade(label='3. 자유 회전 (입력)_CV', menu=CVturnFree)
    CVTurn.add_command(label='자유 회전 (백워딩 + 중앙)_CV', command=lambda: cvTurnImage(7))
    CVgeometryMenu.add_cascade(label='3. 확대/축소_CV', menu=CVsize)
    CVsize.add_command(label='이미지 크기 확대 (백워딩)_CV', command=lambda: cvImageSizeUpDown(1))
    CVsize.add_command(label='이미지 크기 축소 (백워딩)_CV', command=lambda: cvImageSizeUpDown(2))
    # geometryMenu.add_command(label='4. 이미지 이동_CV', command=cvMoveImage)
    # geometryMenu.add_command(label='5. 워핑_CV', command=cvWarpingImage)

    # 6. 웹캠 영상 처리_OpenCV
    CVwebCamMenu = Menu(openCVfuncMenu)  # 상위 메뉴 (파일)
    openCVfuncMenu.add_cascade(label='6. 웹캠 영상 처리_CV', menu=CVwebCamMenu)
    CVwebCamMenu.add_command(label='1.캐니 엣지 검출_CV', command=lambda: WebCam_ImageProcessing(1))
    CVwebCamMenu.add_command(label='2.그레디언트 엣지 검출_CV', command=lambda: WebCam_ImageProcessing(2))
    CVwebCamMenu.add_command(label='3.라플라시안 엣지 검출_CV', command=lambda: WebCam_ImageProcessing(3))
    CVwebCamMenu.add_separator()
    CVwebCamMenu.add_cascade(label='4.OpenCV 공 추적_CV', command=CVwebCamMenu_TraceBall)

    openCVfuncMenu.add_separator()
    openCVfuncMenu.add_command(label='HSV 변환_CV', command=cvHSVImage)
    openCVfuncMenu.add_command(label='색상 추출_CV', command=cvMyColorImage)
## 인공지능 메뉴 ##
def AIfunctionMenu():
    # 전역 변수
    global mainMenu
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    aiMenu = Menu(mainMenu)  # 상위 메뉴(파일)
    mainMenu.add_cascade(label='인공지능', menu=aiMenu)

    # 사람 인식 메뉴_AI
    haarRecog = Menu(aiMenu)  # 상위 메뉴 (파일)
    haarHumanRecog = Menu(haarRecog)
    aiImageProcessing = Menu(haarRecog)

    aiMenu.add_cascade(label='1. 이미지 속 객체 인식 (Haar)', menu=haarRecog)
    haarRecog.add_cascade(label='1. 사람 인식 (Haar)', menu=haarHumanRecog)
    haarHumanRecog.add_command(label='정면 얼굴 인식', command=lambda: aiHumanImage(1))
    haarHumanRecog.add_command(label='눈 인식', command=lambda: aiHumanImage(2))
    haarHumanRecog.add_command(label='코 인식', command=lambda: aiHumanImage(3))
    haarHumanRecog.add_command(label='입 인식', command=lambda: aiHumanImage(4))
    haarHumanRecog.add_command(label='왼쪽 귀 인식', command=lambda: aiHumanImage(5))
    haarHumanRecog.add_command(label='오른쪽 귀 인식', command=lambda: aiHumanImage(6))
    haarRecog.add_cascade(label='2. 얼굴 영상처리', menu=aiImageProcessing)
    aiImageProcessing.add_command(label='정면 얼굴 인식', command=lambda: aiFace_ImageProcessing(0))
    aiImageProcessing.add_command(label='모자이크', command=lambda: aiFace_ImageProcessing(1))
    aiImageProcessing.add_command(label='카툰화', command=lambda: aiFace_ImageProcessing(2))
    haarRecog.add_separator()
    haarRecog.add_command(label='3. 자동차 인식 (haar)', command=aiCarImage)

    # 동영상 메뉴_AI
    aiVideoMenu = Menu(aiMenu)  # 상위 메뉴 (파일)

    aiMenu.add_cascade(label='2. 동영상', menu=aiVideoMenu)
    aiVideoMenu.add_command(label='이미지 속 객체 인식 (SSD)', command=DLImage_Photo)
    aiVideoMenu.add_command(label='동영상 속 객체 인식 (SSD)', command=DLImage_Video)

    # 웹캠 메뉴_AI
    WebCamMenu = Menu(aiMenu)  # 상위 메뉴 (파일)
    WebCam_aiImageProcessing = Menu(WebCamMenu)

    aiMenu.add_cascade(label='3. 웹캠', menu=WebCamMenu)
    WebCamMenu.add_command(label='입력키 리턴값 확인', command=checkRetKey)
    WebCamMenu.add_command(label='웹캠', command=WebCamDisplay_Threading)
    WebCamMenu.add_command(label='웹캠_객체 인식 (Haar)', command=haar_WebCamDisplay_Threading)
    WebCamMenu.add_command(label='웹캠_객체 인식 (SSD)', command=SSD_WebCamDisplay_Threading)

    WebCamMenu.add_cascade(label='웹캠 영상처리', menu=WebCam_aiImageProcessing)
    WebCam_aiImageProcessing.add_command(label='웹캠 모자이크', command=lambda: WebCam_aiFace_ImageProcessing(1))
    WebCam_aiImageProcessing.add_command(label='웹캠 카툰화', command=lambda: WebCam_aiFace_ImageProcessing(2))

    # 유튜브 메뉴_AI
    YoutubeMenu = Menu(aiMenu)  # 상위 메뉴 (파일)

    aiMenu.add_cascade(label='4. 유튜브', menu=YoutubeMenu)
    YoutubeMenu.add_command(label='유튜브', command=None)
    YoutubeMenu.add_command(label='유튜브_객체 인식 (Haar)', command=None)
    YoutubeMenu.add_command(label='유튜브_객체 인식 (SSD)', command=None)


# *************************** < 이미지 입출력 함수 정의부 > ***************************
# 2차원 배열 생성 함수 (동적 할당)
def malloc3D(h, w, t, initValue=0):  # 디폴트 매개변수
    retMemory = [[[initValue for _ in range(w)] for _ in range(h)] for _ in range(t)]  # 파이썬에서만 가능한 문법
    return retMemory


# 이미지 파일 열기 (입력)
def openImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    filename = askopenfilename(parent=window,
                               filetypes=(("Color 파일", "*.jpg; *.png; *.bmp; *.tif; *.mp4"), ("모든 파일", "*.*")))

    # 중요! 입력 영상의 크기 파악
    inPhoto = cv2.imread(filename)  # 이미지 파일 불러오기
    inH = inPhoto.shape[0]  # 입력 이미지의 높이 측정
    inW = inPhoto.shape[1]  # 입력 이미지의 넓이 측정

    # 메모리 할당
    inImage = malloc3D(inH, inW, RGB)

    # OpenCV 개체 --> 메모리
    for i in range(inH):
        for k in range(inW):
            inImage[RR][i][k] = inPhoto.item(i, k, BB)  # 컴퓨터에 입력되는건 R,G,B 순서가 아닌 B,G,R 순서
            inImage[GG][i][k] = inPhoto.item(i, k, GG)
            inImage[BB][i][k] = inPhoto.item(i, k, RR)

    print(filename)
    equalImage()


# 이미지 파일 저장
def saveImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if outImage is None or len(outImage) == 0:  # 영상처리를 한적이 없다면
        return

    saveFp = asksaveasfile(parent=window, mode='wb', defaultextension="*.raw",
                           filetypes=(("PNG 파일", "*.png"), ("All Files", "*.*")))

    # 빈 OpenCV 개체 생성
    savePhoto = np.zeros((outH, outW, 3), np.uint8)

    for i in range(outH):
        for k in range(outW):
            tup = tuple((outImage[BB][i][k], outImage[GG][i][k], outImage[RR][i][k]))
            savePhoto[i][k] = tup

    cv2.imwrite(saveFp.name, savePhoto)
    messagebox.showinfo("성공", saveFp.name + " 저장됨")


# 이미지 출력
def printImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if canvas is not None:  # if (canvas != NULL)
        canvas.destroy()

    window.geometry(str(int(outW * 1.1)) + 'x' + str(int(outH * 1.1)))

    # 캔버스 + 페이퍼
    canvas = Canvas(window, height=outH, width=outW)  # 칠판 준비
    canvas.bind("<Button-1>", leftMouse)
    canvas.bind("<Button-3>", rightMouse)
    canvas.bind("<B1-Motion>", moveMouse)
    canvas.bind("<ButtonRelease-1>", dropMouse)
    paper = PhotoImage(height=outH, width=outW)  # 작성할 종이 준비
    canvas.create_image((outW / 2, outH / 2), image=paper, state='normal')

    # 메모리 --> 화면
    # C++의 더블 버퍼링을 응용한 기법
    rgbString = ""
    for i in range(outH):
        tmpString = ""
        for k in range(outW):
            r = outImage[RR][i][k]
            g = outImage[GG][i][k]
            b = outImage[BB][i][k]
            tmpString += "#%02x%02x%02x " % (r, g, b)  # 제일 뒤에 공백
        rgbString += '{' + tmpString + '} '
    paper.put(rgbString)

    canvas.pack(expand=1, anchor=CENTER)
    stateBar.configure(text='크기:' + str(outH) + 'x' + str(outW) + '\t\t' + filename)  # 세로x가로(이미지 크기), 파일 경로


# *************************** < 마우스 기능 함수 정의부 > ***************************
# 마우스 좌클릭
def leftMouse(event):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine  # start x, start y, end x, end y

    if boxLine is not None:  # 드래그 할 때, 이미 박스라인이 있는 상황에 좌클릭 누르면
        canvas.delete(boxLine)  # 박스라인 삭제

    sx = event.x
    sy = event.y


# 마우스 우클릭
def rightMouse(event):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if boxLine is not None:  # 드래그 할 때, 이미 박스라인이 있는 상황에 우클릭 누르면
        canvas.delete(boxLine)  # 박스라인 삭제
    sx, sy, ex, ey = [-1] * 4  # 초기화           # 0이 들어올 수도 있기 때문에 -1로 초기화


# 마우스 드래그
def moveMouse(event):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    ex = event.x
    ey = event.y

    if boxLine is not None:
        canvas.delete(boxLine)
    boxLine = canvas.create_rectangle(sx, sy, ex, ey, width=1)


# 마우스 클릭 후
def dropMouse(event):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if boxLine is not None:
        canvas.delete(boxLine)

    ex = event.x
    ey = event.y

    if sx > ex:  # 만약, 드래그 시작점이 끝점보다 더 x축에서 멀다면
        sx, ex = ex, sx  # 시작점과 끝점의 값을 교환함
    if sy > ey:  # 만약, 드래그 시작점이 끝점보다 더 y축에서 멀다면
        sy, ey = ey, sy  # 시작점과 끝점의 값을 교환함
    boxLine = canvas.create_rectangle(sx, sy, ex, ey, width=1, fill='blue', stipple="gray25")


# 전역 변수, 영상 크기 설정, 메모리 할당, 예외 처리
def startFunc():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
        return

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc3D(outH, outW, RGB)


# *************************** < 1. 화소점 처리 기능 함수 정의부 > ***************************
# 1-1.동일 이미지
def equalImage():
    startFunc()

    print("동일 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                px = inImage[rgb][i][k]

                outImage[rgb][i][k] = px
    # ************************************************** #
    printImage()


# 1-2.반전 이미지
def reverseImage():
    startFunc()

    print("반전 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = inImage[rgb][i][k]
                    outImage[rgb][i][k] = 255 - px
                else:
                    if (sx <= k < ex) and (sy <= i < ey):           # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = 255 - inImage[rgb][i][k]
                        outImage[rgb][i][k] = px
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-3.밝기 조절 이미지 (입력)
def brightControlImage():
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    value = askinteger("밝기 조절", "밝기 조절 값 입력 : ", minvalue=-255, maxvalue=255)

    if value >= 0:
        print("밝기 %d 증가 이미지" % value)
    elif value < 0:
        print("밝기 %d 감소 이미지" % value)

    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = inImage[rgb][i][k] + value

                    if px > 255:
                        px = 255
                    elif px <= 0:
                        px = 0
                    else:
                        outImage[rgb][i][k] = px

                    outImage[rgb][i][k] = px
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = inImage[rgb][i][k] + value

                        if px > 255:
                            px = 255
                        elif px <= 0:
                            px = 0
                        else:
                            outImage[rgb][i][k] = px

                        outImage[rgb][i][k] = px
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-4.선명도(1.선명하게 2.흐릿하게) 조절 이미지 (입력)
def clearControlImage(clear):
    startFunc()

    value = 0.0
    # 선명도 조절 (선명하게)
    if clear == 1:
        value = askfloat("선명도(선명하게) 조절", "선명도 조절 값 입력 : ", minvalue=0, maxvalue=255)

        print("선명도 x%d 증가 이미지" % value)

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][i][k] * value

                        if px > 255:
                            px = 255
                        elif px <= 0:
                            px = 0
                        else:
                            outImage[rgb][i][k] = int(px)
                        outImage[rgb][i][k] = int(px)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][i][k] * value

                            if px > 255:
                                px = 255
                            elif px <= 0:
                                px = 0
                            else:
                                outImage[rgb][i][k] = int(px)
                            outImage[rgb][i][k] = int(px)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 선명도 조절 (흐릿하게)
    elif clear == 2:
        value = askfloat("선명도(선명하게) 조절", "선명도 조절 값 입력 : ", minvalue=0, maxvalue=255)

        print("선명도 /%d 감소 이미지" % value)

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][i][k] / value

                        if px > 255:
                            px = 255
                        elif px <= 0:
                            px = 0
                        else:
                            outImage[rgb][i][k] = int(px)
                        outImage[rgb][i][k] = int(px)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][i][k] / value

                            if px > 255:
                                px = 255
                            elif px <= 0:
                                px = 0
                            else:
                                outImage[rgb][i][k] = int(px)
                            outImage[rgb][i][k] = int(px)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-5.흑백 처리 (128/평균값/입력 범위/GrayScale 기준)
def BWImage(bw):
    startFunc()

    # 흑백 처리 (Gray Scale)
    if bw == 1:
        print("Gray Scale 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[RR][i][k] + inImage[GG][i][k] + inImage[BB][i][k]

                        outImage[rgb][i][k] = int(px / 3.0)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[RR][i][k] + inImage[GG][i][k] + inImage[BB][i][k]

                            outImage[rgb][i][k] = int(px / 3.0)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 흑백 처리 (128 기준)
    elif bw == 2:
        print("흑백 처리 (128 기준) 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    px = inImage[rgb][i][k]

                    if sx == -1:
                        if px > 127:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [255] * 3  # 255, 255, 255
                        else:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [0] * 3
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            if px > 127:
                                outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [255] * 3
                            else:
                                outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [0] * 3
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 흑백 처리 (평균값 기준)
    elif bw == 3:
        print("흑백 처리 (평균값 기준) 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        pixSum, pixAvg = 0, 0.0
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    px = inImage[rgb][i][k]

                    pixSum += px

            pixAvg = pixSum / (inH * inW)

        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    px = inImage[rgb][i][k]

                    if sx == -1:
                        if px > pixAvg:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [255] * 3
                        else:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [0] * 3
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            if px > pixAvg:
                                outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [255] * 3
                            else:
                                outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [0] * 3
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 흑백 처리 (2입력 범위 기준)
    elif bw == 4:
        ## ***** 영상처리 알고리즘 ***** ##
        value1 = askinteger("흑백 범위 기준 처리", "범위 시작 값 입력 : ", minvalue=0, maxvalue=255)
        value2 = askinteger("흑백 범위 기준 처리", "범위 끝 값 입력 : ", minvalue=0, maxvalue=255)

        print("흑백 처리 이미지 (범위 : %d ~ %d)" % (value1, value2))

        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
                    if sx == -1:
                        if pxR <= value1 or pxG <= value1 or pxB <= value1:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [0] * 3
                        elif pxR > value2 or pxG > value2 or pxB > value2:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [255] * 3
                        else:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            if pxR <= value1 or pxG <= value1 or pxB <= value1:
                                outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [0] * 3
                            elif pxR > value2 or pxG > value2 or pxB > value2:
                                outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = [255] * 3
                            else:
                                outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-6.비트 연산 (AND/OR/XOR/NOT)
def BitCalc(bit):
    startFunc()

    # 비트연산_AND (입력)
    if bit == 1:
        ## ***** 영상처리 알고리즘 ***** ##
        value = askinteger("BIT AND 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)

        print("AND 비트 연산 화면, 연산값 : %d" % value)

        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][i][k] & value

                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][i][k] & value

                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 비트연산_OR (입력)
    elif bit == 2:
        ## ***** 영상처리 알고리즘 ***** ##
        value = askinteger("BIT OR 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)

        print("OR 비트 연산 화면, 연산값 : %d" % value)

        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][i][k] | value

                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][i][k] | value

                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 비트연산_XOR (입력)
    elif bit == 3:
        ## ***** 영상처리 알고리즘 ***** ##
        value = askinteger("BIT XOR 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)

        print("XOR 비트 연산 화면, 연산값 : %d" % value)

        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][i][k] ^ value

                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][i][k] ^ value

                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 비트연산_NOT (입력)
    elif bit == 4:
        print("NOT 비트 연산 화면")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = 256 + ~inImage[rgb][i][k]

                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = 256 + ~inImage[rgb][i][k]

                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-7.감마 변환 이미지 (입력)
def gammaImage():
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0.0
    value = askfloat("감마 변환 처리", "감마 변환 값 입력 : ", minvalue=0.3, maxvalue=1.6)

    print("감마 변환 이미지, 변환값 : %.1f" % value)

    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = inImage[rgb][i][k]

                    gamma = pow(px, 1 / value)

                    if gamma > 255:
                        gamma = 255
                    elif gamma <= 0:
                        gamma = 0
                    else:
                        outImage[rgb][i][k] = int(gamma)

                    outImage[rgb][i][k] = int(gamma)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = inImage[rgb][i][k]

                        gamma = pow(px, 1 / value)

                        if gamma > 255:
                            gamma = 255
                        elif gamma <= 0:
                            gamma = 0
                        else:
                            outImage[rgb][i][k] = int(gamma)

                        outImage[rgb][i][k] = int(gamma)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-8.범위 강조 이미지 (2입력)
def rangeEmphasis():
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    value1 = askfloat("범위 강조 처리", "범위 시작 값 입력 : ", minvalue=0, maxvalue=255)
    value2 = askfloat("범위 강조 처리", "범위 끝 값 입력 : ", minvalue=0, maxvalue=255)

    print("범위 강조 이미지 (범위 : %d ~ %d)" % (value1, value2))

    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = inImage[rgb][i][k]

                    if (value1 <= px) and (px <= value2):
                        outImage[rgb][i][k] = 255
                    else:
                        outImage[rgb][i][k] = px
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = inImage[rgb][i][k]

                        if (value1 <= px) and (px <= value2):
                            outImage[rgb][i][k] = 255
                        else:
                            outImage[rgb][i][k] = px
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-9.파라볼라 변환 (CAP, CUP)
# (CAP : 밝은 곳이 입체적으로 보임, CUP : 어두운 곳이 입체적으로 보임)
def parabolaImage(para):
    startFunc()

    # 파라볼라 CAP 변환
    if para == 1:
        print("파라볼라 CAP 변환 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = (4 / 255.0) * inImage[rgb][i][k] * (255 - inImage[rgb][i][k])

                        outImage[rgb][i][k] = int(px)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = (4 / 255.0) * inImage[rgb][i][k] * (255 - inImage[rgb][i][k])

                            outImage[rgb][i][k] = int(px)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 파라볼라 CUP 변환
    elif para == 2:
        print("파라볼라 CUP 변환 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = (4 / 255.0) * inImage[rgb][i][k] * (inImage[rgb][i][k] - 255) + 255

                        outImage[rgb][i][k] = int(px)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = (4 / 255.0) * inImage[rgb][i][k] * (inImage[rgb][i][k] - 255) + 255

                            outImage[rgb][i][k] = int(px)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 1-10.명암대비 스트레칭 (입력)
def stretchedImage():
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    value = askfloat("명암대비 스트래칭", "스트래칭 값 입력 : ", minvalue=0, maxvalue=255)

    print("명암대비 스트레칭 이미지, 변환값 : %.1f" % value)

    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = inImage[rgb][i][k] + (outImage[rgb][i][k] - 128) * value

                    if px > 255:
                        px = 255
                    elif px <= 0:
                        px = 0
                    else:
                        outImage[rgb][i][k] = int(px)

                    outImage[rgb][i][k] = int(px)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = inImage[rgb][i][k] + (outImage[rgb][i][k] - 128) * value

                        if px > 255:
                            px = 255
                        elif px <= 0:
                            px = 0
                        else:
                            outImage[rgb][i][k] = int(px)

                        outImage[rgb][i][k] = int(px)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# *************************** < 2. 히스토그램 (화소점) 처리 기능 함수 정의부 > ***************************
# 2-1.히스토그램 출력
def printHisto():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = 256
    outW = 256
    reSize = outH * outW

    LOW = 0
    HIGH = 256
    value = 0

    # 메모리 할당
    outImage = malloc3D(outH, outW, RGB)

    print("히스토그램 출력 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    histo = [0 for _ in range(256)]
    # 초기화
    for i in range(256):
        histo[i] = 0

    # 빈도수 조사
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                value = inImage[rgb][i][k]
                histo[value] += 1

    # 정규화
    MIN, MAX = 0, 0
    dif = 0
    hNum = 0

    for i in range(256):
        if histo[i] <= min:
            min = histo[i]
        elif histo[i] >= max:
            max = histo[i]
    dif = MAX - MIN

    # 정규화된 히스토그램
    scaleHisto = [0 for _ in range(256)]
    for i in range(256):
        scaleHisto[i] = (histo[i] - MIN) * HIGH / dif

    # 정규화된 히스토그램 출력

    # 정규화된 히스토그램의 값은 출력배열에 검은 점으로 표현
    # for rgb in range(RGB):
    #    for i in range(outH):
    #        for k in range(scaleHisto[i]):
    #            OutImage[outW * (outH - k - 1) + i] = 0

    # ************************************************** #
    printImage()


# 2-2.히스토그램 스트레칭
def histoStretch():
    startFunc()

    print("히스토그램 스트레칭 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    MIN = inImage[0][0][0]
    MAX = inImage[0][0][0]

    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                px = inImage[rgb][i][k]

                if px < MIN:
                    MIN = px
                elif px > MAX:
                    MAX = px

    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = 255.0 * (inImage[rgb][i][k] - MIN) / (MAX - MIN)

                    outImage[rgb][i][k] = int(px)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = 255.0 * (inImage[rgb][i][k] - MIN) / (MAX - MIN)

                        outImage[rgb][i][k] = int(px)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]

    # minR, minG, minB = inImage[RR][0][0], inImage[GG][0][0], inImage[BB][0][0]
    # maxR, maxG, maxB = inImage[RR][0][0], inImage[GG][0][0], inImage[BB][0][0]
    #
    # for i in range(inH):
    #     for k in range(inW):
    #         pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
    #
    #         if pxR <= minR:
    #             minR = pxR
    #         elif pxR > maxR:
    #             maxR = pxR
    #
    #         if pxG <= minG:
    #             minG = pxG
    #         elif pxG > maxG:
    #             maxG = pxG
    #
    #         if pxB <= minB:
    #             minB = pxB
    #         elif pxB > maxB:
    #             maxB = pxB
    #
    #     for i in range(inH):
    #         for k in range(inW):
    #             pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
    #
    #             outImage[RR][i][k] = int((pxR - minR) / (maxR - minR) * 255.0)
    #             outImage[GG][i][k] = int((pxG - minG) / (maxG - minG) * 255.0)
    #             outImage[BB][i][k] = int((pxB - minB) / (maxB - minB) * 255.0)
    print("")
    # ************************************************** #
    printImage()


# 2-3.히스토그램 엔드-인 탐색
def histoEndIn():
    startFunc()

    print("히스토그램 엔드-인 탐색 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    MIN = inImage[0][0][0]
    MAX = inImage[0][0][0]

    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                px = inImage[rgb][i][k]

                if px < MIN:
                    MIN = px
                elif px > MAX:
                    MAX = px

    MIN += 50
    MAX -= 50
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = 255.0 * (inImage[rgb][i][k] - MIN) / (MAX - MIN)

                    if px <= 0.0:
                        outImage[rgb][i][k] = 0
                    elif px > 255.0:
                        outImage[rgb][i][k] = 255
                    else:
                        outImage[rgb][i][k] = int(px)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = 255.0 * (inImage[rgb][i][k] - MIN) / (MAX - MIN)

                        if px <= 0.0:
                            outImage[rgb][i][k] = 0
                        elif px > 255.0:
                            outImage[rgb][i][k] = 255
                        else:
                            outImage[rgb][i][k] = int(px)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]

    # ************************************************** #
    printImage()


# 2-4.히스토그램 평활화
def histoEqual():
    startFunc()

    print("히스토그램 평활화 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    # 1단계 : 히스토그램 생성
    histoR, histoG, histoB = [0 for _ in range(256)], [0 for _ in range(256)], [0 for _ in range(256)]
    for i in range(inH):
        for k in range(inW):
            histoR[inImage[RR][i][k]] += 1
            histoG[inImage[GG][i][k]] += 1
            histoB[inImage[BB][i][k]] += 1

    # 2단계 : 누적 히스토그램 생성 (누적합 생성)
    sumHistoR, sumHistoG, sumHistoB = [0 for _ in range(256)], [0 for _ in range(256)], [0 for _ in range(256)]
    for i in range(1, 256, 1):
        sumHistoR[i] = sumHistoR[i - 1] + histoR[i]
        sumHistoG[i] = sumHistoG[i - 1] + histoG[i]
        sumHistoB[i] = sumHistoB[i - 1] + histoB[i]

    ## 3단계 : 정규화된 누적 히스토그램 생성 (정규화된 누적합 생성)
    normalHistoR, normalHistoG, normalHistoB = [0 for _ in range(256)], [0 for _ in range(256)], [0 for _ in range(256)]
    for i in range(256):
        normalHistoR[i] = sumHistoR[i] * (1.0 / (inH * inW)) * 255.0
        normalHistoG[i] = sumHistoG[i] * (1.0 / (inH * inW)) * 255.0
        normalHistoB[i] = sumHistoB[i] * (1.0 / (inH * inW)) * 255.0

    # 4단계 : 원래값을 정규화 값으로 치환
    for rgb in range(RGB):
        for i in range(outH):
            for k in range(outW):
                if sx == -1:
                    outImage[RR][i][k] = int(normalHistoR[inImage[RR][i][k]])
                    outImage[GG][i][k] = int(normalHistoG[inImage[GG][i][k]])
                    outImage[BB][i][k] = int(normalHistoB[inImage[BB][i][k]])
                else:
                    if (sx <= k < ex) and (sy <= i < ey):
                        outImage[RR][i][k] = int(normalHistoR[inImage[RR][i][k]])
                        outImage[GG][i][k] = int(normalHistoG[inImage[GG][i][k]])
                        outImage[BB][i][k] = int(normalHistoB[inImage[BB][i][k]])
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# *************************** < 3. 화소 영역 처리 기능 함수 정의부 > ***************************
# 3-1.엠보싱
def embossing():
    startFunc()

    print("엠보싱 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 엠보싱 마스크
    Emask = [[-1, 0, 0],
             [0, 0, 0],
             [0, 0, 1]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
    tmpOut = malloc3D(inH, inW, RGB)

    # 임시 입력을 0으로 초기화
    for rgb in range(RGB + 2):
        for i in range(inH + 2):
            for k in range(inW + 2):
                tmpIn[rgb][i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                S = 0.0
                for m in range(MSIZE):
                    for n in range(MSIZE):
                        S += tmpIn[rgb][i + m][k + n] * Emask[m][n]
                tmpOut[rgb][i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    for rgb in range(RGB):
        for i in range(outH):
            for k in range(outW):
                tmpOut[rgb][i][k] += 127.0

    # 임시 출력 --> 출력 메모리
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    v = tmpOut[rgb][i][k]

                    if v > 255.0:
                        outImage[rgb][i][k] = 255
                    elif v <= 0.0:
                        outImage[rgb][i][k] = 0
                    else:
                        outImage[rgb][i][k] = int(v)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        v = tmpOut[rgb][i][k]

                        if v > 255.0:
                            outImage[rgb][i][k] = 255
                        elif v <= 0.0:
                            outImage[rgb][i][k] = 0
                        else:
                            outImage[rgb][i][k] = int(v)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 3-2.블러링 (3x3 블러링, 5x5 블러링)
def blurringImage(blurr):
    startFunc()

    # 3x3 블러링
    if blurr == 1:
        print("3x3 블러링 이미지")
        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 3
        # 3x3 블러링 마스크
        B3mask = [[1. / 9, 1. / 9, 1. / 9],
                  [1. / 9, 1. / 9, 1. / 9],
                  [1. / 9, 1. / 9, 1. / 9]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB + 2):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S += tmpIn[rgb][i + m][k + n] * B3mask[m][n]
                    tmpOut[rgb][i][k] = S
    # 5x5 블러링
    elif blurr == 2:
        print("5x5 블러링 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 5
        # 5x5 블러링 마스크
        B5mask = [[1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
                  [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
                  [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
                  [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
                  [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB + 2):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 2][k + 2] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S += tmpIn[rgb][i + m][k + n] * B5mask[m][n]
                    tmpOut[rgb][i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크의 합이 0이 아니므로 주석 처리
    """
    for rgb in range(RGB):
        for i in range(outH):
            for k in range(outW):
                tmpOut[rgb][i][k] += 127.0
    """

    # 임시 출력 --> 출력 메모리
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    v = tmpOut[rgb][i][k]

                    if v > 255.0:
                        outImage[rgb][i][k] = 255
                    elif v <= 0.0:
                        outImage[rgb][i][k] = 0
                    else:
                        outImage[rgb][i][k] = int(v)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        v = tmpOut[rgb][i][k]

                        if v > 255.0:
                            outImage[rgb][i][k] = 255
                        elif v <= 0.0:
                            outImage[rgb][i][k] = 0
                        else:
                            outImage[rgb][i][k] = int(v)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 3-3.스무딩 (가우시안)
def smoothing():
    startFunc()

    print("스무딩(가우시안) 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 스무딩(가우시안) 마스크
    SMmask = [[1. / 16, 1. / 8, 1. / 16],
              [1. / 8, 1. / 4, 1. / 8],
              [1. / 16, 1. / 8, 1. / 16]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
    tmpOut = malloc3D(inH, inW, RGB)

    # 임시 입력을 0으로 초기화
    for rgb in range(RGB + 2):
        for i in range(inH + 2):
            for k in range(inW + 2):
                tmpIn[rgb][i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                S = 0.0
                for m in range(MSIZE):
                    for n in range(MSIZE):
                        S += tmpIn[rgb][i + m][k + n] * SMmask[m][n]
                tmpOut[rgb][i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    """
    for rgb in range(RGB):
        for i in range(outH):
            for k in range(outW):
                tmpOut[rgb][i][k] += 127.0
    """

    # 임시 출력 --> 출력 메모리
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    v = tmpOut[rgb][i][k]

                    if v > 255.0:
                        outImage[rgb][i][k] = 255
                    elif v <= 0.0:
                        outImage[rgb][i][k] = 0
                    else:
                        outImage[rgb][i][k] = int(v)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        v = tmpOut[rgb][i][k]

                        if v > 255.0:
                            outImage[rgb][i][k] = 255
                        elif v <= 0.0:
                            outImage[rgb][i][k] = 0
                        else:
                            outImage[rgb][i][k] = int(v)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 3-4.샤프닝 (샤프닝, HPF 처리, LPF 처리)
def sharpningImage(sharp):
    startFunc()

    # 샤프닝
    if sharp == 1:
        print("샤프닝 처리 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 3
        # 샤프닝 마스크
        Smask = [[-1, -1, -1],
                 [-1, 9, -1],
                 [-1, -1, -1]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB + 2):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S += tmpIn[rgb][i + m][k + n] * Smask[m][n]
                    tmpOut[rgb][i][k] = S

        # 후처리 (마스크의 합계에 따라서 정제..)
        # 마스크의 합이 0이 아니므로 주석 처리
        """
        for i in range(outH):
            for k in range(outW):
                tmpOut[i][k] += 127.0
        """
    # 고주파 필터 처리 샤프닝
    elif sharp == 2:
        print("HPF(고주파 필터 처리) 샤프닝 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 3
        # 고주파 필터 마스크
        HPFmask = [[-1. / 9, -1. / 9, -1. / 9],
                   [-1. / 9, 8 / 9, -1. / 9],
                   [-1. / 9, -1. / 9, -1. / 9]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S += tmpIn[rgb][i + m][k + n] * HPFmask[m][n]
                    tmpOut[rgb][i][k] = S

        # 후처리 (마스크의 합계에 따라서 정제..)
        # 마스크 합계가 0일 경우 추가
        for rgb in range(RGB):
            for i in range(outH):
                for k in range(outW):
                    tmpOut[rgb][i][k] += 127.0
    # 저주파 필터 처리 샤프닝
    elif sharp == 3:
        print("LPF(저주파 필터 처리) 샤프닝 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 3
        # 저주파 필터 마스크
        LPFmask = [[1. / 16, 2. / 16, 1. / 16],
                   [2. / 16, 4. / 16, 2. / 16],
                   [1. / 16, 2. / 16, 1. / 16]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB + 2):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S += tmpIn[rgb][i + m][k + n] * LPFmask[m][n]
                    tmpOut[rgb][i][k] = tmpIn[rgb][i][k] - S

        # 후처리 (마스크의 합계에 따라서 정제..)
        # 마스크 합계가 0일 경우 추가
        """
        for rgb in range(RGB):
            for i in range(outH):
                for k in range(outW):
                    tmpOut[rgb][i][k] += 127.0
        """

    # 임시 출력 --> 출력 메모리
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    v = tmpOut[rgb][i][k]

                    if v > 255.0:
                        outImage[rgb][i][k] = 255
                    elif v <= 0.0:
                        outImage[rgb][i][k] = 0
                    else:
                        outImage[rgb][i][k] = int(v)
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        v = tmpOut[rgb][i][k]

                        if v > 255.0:
                            outImage[rgb][i][k] = 255
                        elif v <= 0.0:
                            outImage[rgb][i][k] = 0
                        else:
                            outImage[rgb][i][k] = int(v)
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# *************************** < 4. 엣지 검출 처리 기능 함수 정의부 > ***************************
# 4-1.이동과 차분 엣지 검출 (수직, 수평, 수직수평)
# 화소의 위치를 위/아래/왼/오른쪽으로 하나씩 이동 -> 원래 화소 값 - 이동위치 화소 값
# 엣지 검출기는 대부분 이 방법 응용
# Shift & Difference
def shiftDifferEdgeImage(edge):
    startFunc()

    # 수직 엣지
    if edge == 1:
        print("수직 엣지 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 3
        # 엠보싱 마스크
        Hmask = [[0, 0, 0],
                 [-1, 1, 0],
                 [0, 0, 0]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB + 2):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S += tmpIn[rgb][i + m][k + n] * Hmask[m][n]
                    tmpOut[rgb][i][k] = S

        # 후처리 (마스크의 합계에 따라서 정제..)
        # 마스크 합계가 0일 경우 추가
        for rgb in range(RGB):
            for i in range(outH):
                for k in range(outW):
                    tmpOut[rgb][i][k] += 127.0

        # 임시 출력 --> 출력 메모리
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        v = tmpOut[rgb][i][k]

                        if v > 255.0:
                            outImage[rgb][i][k] = 255
                        elif v <= 0.0:
                            outImage[rgb][i][k] = 0
                        else:
                            outImage[rgb][i][k] = int(v)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            v = tmpOut[rgb][i][k]

                            if v > 255.0:
                                outImage[rgb][i][k] = 255
                            elif v <= 0.0:
                                outImage[rgb][i][k] = 0
                            else:
                                outImage[rgb][i][k] = int(v)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 수평 엣지
    elif edge == 2:
        print("수평 엣지")

        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 3
        # 엠보싱 마스크
        Vmask = [[0, -1, 0],
                 [0, 1, 0],
                 [0, 0, 1]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB + 2):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S += tmpIn[rgb][i + m][k + n] * Vmask[m][n]
                    tmpOut[rgb][i][k] = S

        # 후처리 (마스크의 합계에 따라서 정제..)
        # 마스크 합계가 0일 경우 추가
        for rgb in range(RGB):
            for i in range(outH):
                for k in range(outW):
                    tmpOut[rgb][i][k] += 127.0

        # 임시 출력 --> 출력 메모리
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        v = tmpOut[rgb][i][k]

                        if v > 255.0:
                            outImage[rgb][i][k] = 255
                        elif v <= 0.0:
                            outImage[rgb][i][k] = 0
                        else:
                            outImage[rgb][i][k] = int(v)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            v = tmpOut[rgb][i][k]

                            if v > 255.0:
                                outImage[rgb][i][k] = 255
                            elif v <= 0.0:
                                outImage[rgb][i][k] = 0
                            else:
                                outImage[rgb][i][k] = int(v)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 수직 수평 엣지
    elif edge == 3:
        print("수직 수평 엣지")

        ## ***** 영상처리 알고리즘 ***** ##
        MSIZE = 3
        # 엠보싱 마스크
        Hmask = [[0, 0, 0],
                 [-1, 1, 0],
                 [0, 0, 0]]
        Vmask = [[0, -1, 0],
                 [0, 1, 0],
                 [0, 0, 1]]

        # 임시 입출력 메모리 할당
        tmpIn = malloc3D(inH + MSIZE - 1, inW + MSIZE - 1, RGB + MSIZE - 1)
        tmpOut1 = malloc3D(inH, inW, RGB)
        tmpOut2 = malloc3D(inH, inW, RGB)

        # 임시 입력을 0으로 초기화
        for rgb in range(RGB + 2):
            for i in range(inH + 2):
                for k in range(inW + 2):
                    tmpIn[rgb][i][k] = 0.0

        # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    tmpIn[rgb][i + 1][k + 1] = inImage[rgb][i][k]

        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S1 = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S1 += tmpIn[rgb][i + m][k + n] * Hmask[m][n]
                    tmpOut1[rgb][i][k] = S1
        # 회선 연산 --> 마스크로 긁어가면서 계산하기
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    S2 = 0.0
                    for m in range(MSIZE):
                        for n in range(MSIZE):
                            S2 += tmpIn[rgb][i + m][k + n] * Vmask[m][n]
                    tmpOut2[rgb][i][k] = S2

        # 후처리 (마스크의 합계에 따라서 정제..)
        # 마스크 합계가 0일 경우 추가
        for rgb in range(RGB):
            for i in range(outH):
                for k in range(outW):
                    tmpOut1[rgb][i][k] += 127.0
                    tmpOut2[rgb][i][k] += 127.0

        # 임시 출력 --> 출력 메모리
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        v1 = tmpOut1[rgb][i][k]
                        v2 = tmpOut2[rgb][i][k]
                        v = v1 + v2

                        if v > 255.0:
                            outImage[rgb][i][k] = 255
                        elif v <= 0.0:
                            outImage[rgb][i][k] = 0
                        else:
                            outImage[rgb][i][k] = int(v)
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            v1 = tmpOut1[rgb][i][k]
                            v2 = tmpOut2[rgb][i][k]
                            v = v1 + v2

                            if v > 255.0:
                                outImage[rgb][i][k] = 255
                            elif v <= 0.0:
                                outImage[rgb][i][k] = 0
                            else:
                                outImage[rgb][i][k] = int(v)
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# *************************** < 5. 기하학 처리 기능 함수 정의부 > ***************************
# 5-1.미러링 (좌우/상하/상하+좌우)
def mirroringImage(mirror):
    startFunc()

    # 좌우 미러링
    if mirror == 1:
        print("좌우 미러링 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][i][((inW - 1) - k)]

                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][i][((inW - 1) - k)]

                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 상하 미러링
    elif mirror == 2:
        print("상하 미러링 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][((inH - 1) - i)][k]

                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][((inH - 1) - i)][k]

                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 상하+좌우 미러링
    elif mirror == 3:
        print("상하+좌우 미러링 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][(inH - 1) - i][(inW - 1) - k]

                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][(inH - 1) - i][(inW - 1) - k]

                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# 5-2.회전 (오른쪽,왼쪽 90/180/270, 자유회전)
def turnImage(turn):
    # 90도 회전 (시계 방향)
    if turn == 1:
        # 전역 변수
        global inImage, outImage, inH, inW, outH, outW
        global inPhoto, outPhoto  # src, dst
        global window, canvas, paper, stateBar, filename
        global sx, sy, ex, ey, boxLine

        if not inImage:
            messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
            return

        # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
        outH = inW
        outW = inH

        # 메모리 할당
        outImage = malloc3D(outH, outW, RGB)

        print("시계방향 90도 회전 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inW):
                for k in range(inH):
                    if sx == -1:
                        px = inImage[rgb][inH - k - 1][i]
                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][inH - k - 1][i]
                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 180도 회전 (시계 방향)
    elif turn == 2:
        startFunc()

        print("시계방향 180도 회전 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][inH - i - 1][inW - k - 1]
                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][inH - i - 1][inW - k - 1]
                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 270도 회전 (시계 방향)
    elif turn == 3:
        # # 전역 변수
        # global inImage, outImage, inH, inW, outH, outW
        # global inPhoto, outPhoto  # src, dst
        # global window, canvas, paper, stateBar, filename
        # global sx, sy, ex, ey, boxLine

        if not inImage:
            messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
            return

        # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
        outH = inW
        outW = inH

        # 메모리 할당
        outImage = malloc3D(outH, outW, RGB)

        print("시계방향 270도 회전 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inW):
                for k in range(inH):
                    if sx == -1:
                        px = inImage[rgb][k][inW - i - 1]
                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][k][inW - i - 1]
                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]

    # 90도 회전 (반시계 방향)
    if turn == 4:
        # # 전역 변수
        # global inImage, outImage, inH, inW, outH, outW
        # global inPhoto, outPhoto  # src, dst
        # global window, canvas, paper, stateBar, filename
        # global sx, sy, ex, ey, boxLine

        if not inImage:
            messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
            return

        # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
        outH = inW
        outW = inH

        # 메모리 할당
        outImage = malloc3D(outH, outW, RGB)

        print("반시계방향 90도 회전 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inW):
                for k in range(inH):
                    if sx == -1:
                        px = inImage[rgb][k][inW - i - 1]
                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][k][inW - i - 1]
                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 180도 회전 (반시계 방향)
    elif turn == 5:
        startFunc()

        print("반시계방향 180도 회전 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inH):
                for k in range(inW):
                    if sx == -1:
                        px = inImage[rgb][inH - i - 1][inW - k - 1]
                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][inH - i - 1][inW - k - 1]
                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]
    # 270도 회전 (반시계 방향)
    elif turn == 6:
        # # 전역 변수
        # global inImage, outImage, inH, inW, outH, outW
        # global inPhoto, outPhoto  # src, dst
        # global window, canvas, paper, stateBar, filename
        # global sx, sy, ex, ey, boxLine

        if not inImage:
            messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
            return

        # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
        outH = inW
        outW = inH

        # 메모리 할당
        outImage = malloc3D(outH, outW, RGB)

        print("반시계방향 270도 회전 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(inW):
                for k in range(inH):
                    if sx == -1:
                        px = inImage[rgb][inH - k - 1][i]
                        outImage[rgb][i][k] = px
                    else:
                        if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                            px = inImage[rgb][inH - k - 1][i]
                            outImage[rgb][i][k] = px
                        else:
                            outImage[rgb][i][k] = inImage[rgb][i][k]

    # 자유 회전 (백워딩 + 중앙회전)
    if turn == 7:
        # # 전역 변수
        # global inImage, outImage, inH, inW, outH, outW
        # global inPhoto, outPhoto  # src, dst
        # global window, canvas, paper, stateBar, filename
        # global sx, sy, ex, ey, boxLine

        if not inImage:
            messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
            return

        value = askfloat("자유 회전_백워딩+중앙회전 (시계방향)", "회전 각도 입력 : ", minvalue=-360, maxvalue=360)

        print("자유 회전 %.1f도 회전 이미지" % value)

        radian = value * math.pi / 180.0

        # 출력영상의 크기를 결정 --> 알고리즘에 의존
        outW = int(abs(inH * math.cos(math.pi / 2 - radian)) + abs(inW * math.cos(radian)) + 3.5)
        outH = int(abs(inH * math.cos(radian)) + abs(inW * math.cos(math.pi / 2 - radian)) + 3.5)

        # 메모리 할당
        outImage = malloc3D(outH, outW, RGB)

        cx = outH / 2
        cy = outW / 2

        in_cx = inH / 2
        in_cy = inW / 2

        ## ***** 영상처리 알고리즘 ***** ##
        for xd in range(outH):
            for yd in range(outW):
                xs = math.cos(radian) * (xd - cx + 0.5) + math.sin(radian) * (yd - cy + 0.5)
                ys = -math.sin(radian) * (xd - cx + 0.5) + math.cos(radian) * (yd - cy + 0.5)

                xs += in_cx
                ys += in_cy

                if (0 <= xs < inH) and (0 <= ys < inW):
                    for rgb in range(RGB):
                        outImage[rgb][xd][yd] = inImage[rgb][int(xs)][int(ys)]
    # ************************************************* #
    printImage()


# 5-3.이미지 크기(규격) 확대/축소
def imageSizeUpDown(size):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
        return

    # 이미지 크기 확대 (백워딩)
    elif size == 1:
        ratio = askinteger("이미지 크기 확대 (백워딩)", "확대 배율 입력 : ", minvalue=0, maxvalue=10)

        print("%d배 확대(백워딩) 이미지" % ratio)

        if ratio < 0:
            ratio = 0

        # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
        outH = inH * ratio
        outW = inW * ratio

        # 메모리 할당
        outImage = malloc3D(outH, outW, RGB)

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(outH):
                for k in range(outW):
                    px = inImage[rgb][int(i / ratio)][int(k / ratio)]
                    outImage[rgb][i][k] = px
    # 이미지 크기 축소 (백워딩)
    elif size == 2:
        ratio = askinteger("이미지 크기 축소 (백워딩)", "축소 배율 입력 : ", minvalue=0, maxvalue=10)

        print("%d배 축소(백워딩) 이미지" % ratio)

        if ratio <= 0:
            ratio = 0

        # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
        outH = int(inH / ratio)
        outW = int(inW / ratio)

        # 메모리 할당
        outImage = malloc3D(outH, outW, RGB)

        ## ***** 영상처리 알고리즘 ***** ##
        for rgb in range(RGB):
            for i in range(outH):
                for k in range(outW):
                    px = inImage[rgb][i * ratio][k * ratio]
                    outImage[rgb][i][k] = px
    # ************************************************* #
    printImage()

# *************************** < OpenCV 전용 메뉴 > ***************************
# 결과 화면에 출력
def cv2outImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    # 중요! 입력 영상의 크기 파악
    outH = outPhoto.shape[0]
    outW = outPhoto.shape[1]

    # 메모리 할당
    outImage = malloc3D(outH, outW, RGB)

    # OpenCV 개체 --> 메모리
    # 3차원 스케일
    if outPhoto.ndim > 2:  # ndim : 넘파이 차원수 확인
        for i in range(outH):
            for k in range(outW):
                # 마우스로 드래그한 영역(박스라인)이 존재하지 않는 경우
                if sx == -1:
                    outImage[RR][i][k] = outPhoto.item(i, k, BB)  # 컴퓨터에 입력되는건 R,G,B 순서가 아닌 B,G,R 순서
                    outImage[GG][i][k] = outPhoto.item(i, k, GG)
                    outImage[BB][i][k] = outPhoto.item(i, k, RR)
                else:
                    # 마우스로 드래그한 영역(박스라인)이 존재하는 경우
                    if (sx <= k < ex) and (sy <= i < ey):
                        outImage[RR][i][k] = outPhoto.item(i, k, BB)  # 컴퓨터에 입력되는건 R,G,B 순서가 아닌 B,G,R 순서
                        outImage[GG][i][k] = outPhoto.item(i, k, GG)
                        outImage[BB][i][k] = outPhoto.item(i, k, RR)
                    # 박스라인 12이외의 영역은 원본 이미지 그대로
                    else:
                        outImage[RR][i][k] = inImage[RR][i][k]
                        outImage[GG][i][k] = inImage[GG][i][k]
                        outImage[BB][i][k] = inImage[BB][i][k]
    # 단일 스케일
    else:
        for i in range(outH):
            for k in range(outW):
                # 마우스로 드래그한 영역(박스라인)이 존재하지 않는 경우
                if sx == -1:
                    outImage[RR][i][k] = outPhoto.item(i, k)
                    outImage[GG][i][k] = outPhoto.item(i, k)
                    outImage[BB][i][k] = outPhoto.item(i, k)
                else:
                    # 마우스로 드래그한 영역(박스라인)이 존재하는 경우
                    if (sx <= k < ex) and (sy <= i < ey):
                        outImage[RR][i][k] = outPhoto.item(i, k)
                        outImage[GG][i][k] = outPhoto.item(i, k)
                        outImage[BB][i][k] = outPhoto.item(i, k)
                    # 박스라인 이외의 영역은 원본 이미지 그대로
                    else:
                        outImage[RR][i][k] = inImage[RR][i][k]
                        outImage[GG][i][k] = inImage[GG][i][k]
                        outImage[BB][i][k] = inImage[BB][i][k]


# *************************** < 1. [OpenCV] 화소점 처리 기능 함수 정의부 > ***************************
# 1-1.동일 이미지_OpenCV
# 불러온 이미지 파일 -> 출력할 변수에 복사
def cvEqualImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 동일 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = inPhoto[:]   # == outPhoto = inPhoto.copy()
    # ************************************************** #
    cv2outImage()
    printImage()


# 1-2.반전 이미지_OpenCV
def cvReverseImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 반전 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = 255 - inPhoto
    # ************************************************** #
    cv2outImage()
    printImage()


# 1-3.밝기 조절 이미지 (입력)_OpenCV
def cvBrightControlImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    value = askinteger("밝기 조절", "밝기 조절 값 입력 : ", minvalue=-255, maxvalue=255)

    if value >= 0:
        print("[OpenCV] 밝기 %d 증가 이미지" % value)
    elif value < 0:
        print("[OpenCV] 밝기 %d 감소 이미지" % value)

    ### openCV용 함수 활용 ###
    outPhoto = cv2.add(inPhoto, (value, value, value, 0), mask=None, dtype=None)
    # ************************************************** #
    cv2outImage()
    printImage()

    # for rgb in range(RGB):
    #     for i in range(inH):
    #         for k in range(inW):
    #             if sx == -1:
    #                 px = inImage[rgb][i][k] + value
    #
    #                 if px > 255:
    #                     px = 255
    #                 elif px <= 0:
    #                     px = 0
    #                 else:
    #                     outImage[rgb][i][k] = px
    #
    #                 outImage[rgb][i][k] = px
    #             else:
    #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
    #                     px = inImage[rgb][i][k] + value
    #
    #                     if px > 255:
    #                         px = 255
    #                     elif px <= 0:
    #                         px = 0
    #                     else:
    #                         outImage[rgb][i][k] = px
    #
    #                     outImage[rgb][i][k] = px
    #                 else:
    #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    # printImage()


# 1-4.선명도(1.선명하게 2.흐릿하게) 조절 이미지 (입력)_OpenCV
def cvClearControlImage(clear):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    value = 0.0
    # 선명도 조절 (선명하게)_OpenCV
    if clear == 1:
        ## ***** 영상처리 알고리즘 ***** ##
        value = askfloat("선명도(선명하게) 조절", "선명도 조절 값 입력 : ", minvalue=0, maxvalue=255)

        print("[OpenCV] 선명도 x%.1f 증가 이미지" % value)

        ### openCV용 함수 활용 ###
        outPhoto = cv2.multiply(inPhoto, (value, value, value, 0), scale=None, dtype=None)

        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             if sx == -1:
        #                 px = inImage[rgb][i][k] * value
        #
        #                 if px > 255:
        #                     px = 255
        #                 elif px <= 0:
        #                     px = 0
        #                 else:
        #                     outImage[rgb][i][k] = int(px)
        #                 outImage[rgb][i][k] = int(px)
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     px = inImage[rgb][i][k] * value
        #
        #                     if px > 255:
        #                         px = 255
        #                     elif px <= 0:
        #                         px = 0
        #                     else:
        #                         outImage[rgb][i][k] = int(px)
        #                     outImage[rgb][i][k] = int(px)
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # 선명도 조절 (흐릿하게)_OpenCV
    elif clear == 2:
        ## ***** 영상처리 알고리즘 ***** ##
        value = askfloat("선명도(흐릿하게) 조절", "선명도 조절 값 입력 : ", minvalue=0, maxvalue=255)

        print("[OpenCV] 선명도 x%.1f 감소 이미지" % value)

        ### openCV용 함수 활용 ###
        outPhoto = cv2.divide(inPhoto, (value, value, value, 0), scale=None, dtype=None)

        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             if sx == -1:
        #                 px = inImage[rgb][i][k] / value
        #
        #                 if px > 255:
        #                     px = 255
        #                 elif px <= 0:
        #                     px = 0
        #                 else:
        #                     outImage[rgb][i][k] = int(px)
        #                 outImage[rgb][i][k] = int(px)
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     px = inImage[rgb][i][k] / value
        #
        #                     if px > 255:
        #                         px = 255
        #                     elif px <= 0:
        #                         px = 0
        #                     else:
        #                         outImage[rgb][i][k] = int(px)
        #                     outImage[rgb][i][k] = int(px)
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    cv2outImage()
    printImage()


# 1-5.흑백 처리 (128/평균값/입력 범위/GrayScale 기준)_OpenCV
def cvBWImage(bw):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 흑백 처리 (Gray Scale)_OpenCV
    if bw == 1:
        print("[OpenCV] Gray Scale 이미지")

        ### openCV용 함수 활용 ###
        outPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_BGR2GRAY)

        # ## ***** 영상처리 알고리즘 ***** ##
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             if sx == -1:
        #                 px = inImage[RR][i][k] + inImage[GG][i][k] + inImage[BB][i][k]
        #
        #                 outImage[rgb][i][k] = int(px / 3.0)
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     px = inImage[RR][i][k] + inImage[GG][i][k] + inImage[BB][i][k]
        #
        #                     outImage[rgb][i][k] = int(px / 3.0)
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # 흑백 처리 (128 기준)_OpenCV
    elif bw == 2:
        print("[OpenCV] 흑백 처리 (128 기준) 이미지")

        ### openCV용 함수 활용 ###
        outPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_BGR2GRAY)
        _, outPhoto = cv2.threshold(outPhoto, 128, 255, cv2.THRESH_BINARY)

        # ## ***** 영상처리 알고리즘 ***** ##
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
        #             if sx == -1:
        #                 if pxR > 128 or pxG > 128 or pxB > 128:
        #                     pxR, pxG, pxB = 255, 255, 255
        #                 else:
        #                     pxR, pxG, pxB = 0, 0, 0
        #
        #                 outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     if pxR > 128 or pxG > 128 or pxB > 128:
        #                         pxR, pxG, pxB = 255, 255, 255
        #                     else:
        #                         pxR, pxG, pxB = 0, 0, 0
        #
        #                     outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # 흑백 처리 (평균값 기준)_OpenCV
    elif bw == 3:
        print("[OpenCV] 흑백 처리 (평균값 기준) 이미지")

        ### openCV용 함수 활용 ###
        grayPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_BGR2GRAY)
        outPhoto = cv2.adaptiveThreshold(grayPhoto, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 33, -5)

        # ## ***** 영상처리 알고리즘 ***** ##
        # pixSum, pixAvg = 0, 0.0
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             px = inImage[rgb][i][k]
        #
        #             pixSum += px
        #
        #     pixAvg = pixSum / (inH * inW)
        #
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
        #             if sx == -1:
        #                 if pxR > pixAvg or pxG > pixAvg or pxB > pixAvg:
        #                     pxR, pxG, pxB = 255, 255, 255
        #                 else:
        #                     pxR, pxG, pxB = 0, 0, 0
        #
        #                 outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     if pxR > pixAvg or pxG > pixAvg or pxB > pixAvg:
        #                         pxR, pxG, pxB = 255, 255, 255
        #                     else:
        #                         pxR, pxG, pxB = 0, 0, 0
        #
        #                     outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # 카툰이미지_OpenCV_OpenCV
    elif bw == 4:
        print("[OpenCV] 카툰 이미지")

        ### openCV용 함수 활용 ###
        outPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        outPhoto = cv2.medianBlur(outPhoto, 7)
        edges = cv2.Laplacian(outPhoto, cv2.CV_8U, ksize=5)
        ret, mask = cv2.threshold(edges, 100, 255, cv2.THRESH_BINARY_INV)

        outPhoto = cv2.cvtColor(mask, cv2.COLOR_GRAY2RGB)
    # 흑백 처리 (2입력 범위 기준)_OpenCV
    elif bw == 5:
        ## ***** 영상처리 알고리즘 ***** ##
        low = askinteger("흑백 범위 기준 처리", "범위 시작 값 입력 : ", minvalue=0, maxvalue=255)
        high = askinteger("흑백 범위 기준 처리", "범위 끝 값 입력 : ", minvalue=0, maxvalue=255)

        print("[OpenCV] 흑백 처리 이미지 (범위 : %d ~ %d)" % low, high)

        ### openCV용 함수 활용 ###

        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
        #             if sx == -1:
        #                 if pxR <= value1 or pxG <= value1 or pxB <= value1:
        #                     pxR, pxG, pxB = 0, 0, 0
        #                 elif pxR > value2 or pxG > value2 or pxB > value2:
        #                     pxR, pxG, pxB = 255, 255, 255
        #                 else:
        #                     outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #
        #                 outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     if pxR <= value1 or pxG <= value1 or pxB <= value1:
        #                         pxR, pxG, pxB = 0, 0, 0
        #                     elif pxR > value2 or pxG > value2 or pxB > value2:
        #                         pxR, pxG, pxB = 255, 255, 255
        #                     else:
        #                         outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #
        #                     outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    cv2outImage()
    printImage()


# 1-6.비트 연산 (AND/OR/XOR/NOT)_OpenCV
def cvBitCalcImage(bit):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 비트연산_AND (입력)_OpenCV
    if bit == 1:
        ## ***** 영상처리 알고리즘 ***** ##
        value = 0
        value = askinteger("비트 연산_AND", "비트 연산할 값", minvalue=0, maxvalue=255)

        print("[OpenCV] AND 비트 연산 화면, 연산값 : %d" % value)

        ### openCV용 함수 활용 ###
        # openAnotherImg()
        outPhoto = cv2.bitwise_and(inPhoto, (value, value, value, 0), mask=None)

        # ## ***** 영상처리 알고리즘 ***** ##
        # value = askinteger("BIT AND 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)
        #
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             if sx == -1:
        #                 px = inImage[rgb][i][k] & value
        #
        #                 outImage[rgb][i][k] = px
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     px = inImage[rgb][i][k] & value
        #
        #                     outImage[rgb][i][k] = px
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # 비트연산_OR (입력)_OpenCV
    elif bit == 2:
        ## ***** 영상처리 알고리즘 ***** ##
        value = 0
        value = askinteger("비트 연산_OR", "비트 연산할 값", minvalue=0, maxvalue=255)

        print("[OpenCV] OR 비트 연산 화면, 연산값 : %d" % value)

        ### openCV용 함수 활용 ###
        # openAnotherImg()
        outPhoto = cv2.bitwise_or(inPhoto, (value, value, value, 0), mask=None)

        # ## ***** 영상처리 알고리즘 ***** ##
        # value = askinteger("BIT AND 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             if sx == -1:
        #                 px = inImage[rgb][i][k] | value
        #
        #                 outImage[rgb][i][k] = px
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     px = inImage[rgb][i][k] | value
        #
        #                     outImage[rgb][i][k] = px
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # 비트연산_XOR (입력)_OpenCV
    elif bit == 3:
        ## ***** 영상처리 알고리즘 ***** ##
        value = 0
        value = askinteger("비트 연산_XOR", "비트 연산할 값", minvalue=0, maxvalue=255)

        print("[OpenCV] XOR 비트 연산 화면, 연산값 : %d" % value)

        ### openCV용 함수 활용 ###
        # openAnotherImg()
        outPhoto = cv2.bitwise_xor(inPhoto, (value, value, value, 0), mask=None)

        # ## ***** 영상처리 알고리즘 ***** ##
        # value = askinteger("BIT AND 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)
        #
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             if sx == -1:
        #                 px = inImage[rgb][i][k] ^ value
        #
        #                 outImage[rgb][i][k] = px
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     px = inImage[rgb][i][k] ^ value
        #
        #                     outImage[rgb][i][k] = px
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # 비트연산_NOT (입력)_OpenCV
    elif bit == 4:
        print("[OpenCV] NOT 비트 연산 화면")

        ### openCV용 함수 활용 ###
        outPhoto = cv2.bitwise_not(inPhoto, mask=None)

        # ## ***** 영상처리 알고리즘 ***** ##
        # for rgb in range(RGB):
        #     for i in range(inH):
        #         for k in range(inW):
        #             if sx == -1:
        #                 px = 256 + ~inImage[rgb][i][k]
        #
        #                 outImage[rgb][i][k] = px
        #             else:
        #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
        #                     px = 256 + ~inImage[rgb][i][k]
        #
        #                     outImage[rgb][i][k] = px
        #                 else:
        #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    cv2outImage()
    printImage()


# 1-7.감마 변환 이미지 (입력)_OpenCV
def cvGammaImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    gammaValue = 0.0
    gammaValue = askfloat("감마 변환 처리", "감마 변환 값(0.3~1.6) 입력 : ", minvalue=0, maxvalue=255)

    print("[OpenCV] 감마 변환 이미지, 변환값 : %.1f" % gammaValue)

    ### openCV용 함수 활용 ###
    # outPhoto = int(inPhoto ** (1 / gammaValue) * 255.0)
    # outPhoto = inPhoto.astype(np.float)
    # outPhoto = int(((outPhoto / 255.0) ** (1.0 / gammaValue)) * 255.0)
    # outPhoto = outPhoto.astype(np.float)
    # outPhoto = pow(inPhoto / 255.0, (1.0 / gammaValue) * 255.0)
    gamma_cvt = np.zeros((256, 1), dtype='uint8')

    for i in range(256):
        gamma_cvt[i][0] = 255 * (float(i) / 255) ** (1.0 / gammaValue)

    outPhoto = cv2.LUT(inPhoto, gamma_cvt)
    # ************************************************** #
    cv2outImage()
    printImage()

    # for rgb in range(RGB):
    #     for i in range(inH):
    #         for k in range(inW):
    #             if sx == -1:
    #                 px = inImage[rgb][i][k]
    #
    #                 gamma = pow(px, 1 / value)
    #
    #                 if gamma > 255:
    #                     gamma = 255
    #                 elif gamma <= 0:
    #                     gamma = 0
    #                 else:
    #                     outImage[rgb][i][k] = int(gamma)
    #
    #                 outImage[rgb][i][k] = int(gamma)
    #             else:
    #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
    #                     px = inImage[rgb][i][k]
    #
    #                     gamma = pow(px, 1 / value)
    #
    #                     if gamma > 255:
    #                         gamma = 255
    #                     elif gamma <= 0:
    #                         gamma = 0
    #                     else:
    #                         outImage[rgb][i][k] = int(gamma)
    #
    #                     outImage[rgb][i][k] = int(gamma)
    #                 else:
    #                     outImage[rgb][i][k] = inImage[rgb][i][k]


# 1-8.범위 강조 이미지 (2입력)_OpenCV
def cvRangeEmphasis():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    low = askinteger("범위 강조 처리", "범위 시작 값 입력 : ", minvalue=0, maxvalue=255)
    high = askinteger("범위 강조 처리", "범위 끝 값 입력 : ", minvalue=0, maxvalue=255)

    print("[OpenCV] 범위 강조 이미지 (범위 : %d ~ %d)" % low, high)

    ### openCV용 함수 활용 ###
    for rgb in range(RGB):
        for i in range(outH):
            for k in range(outW):
                if low <= outImage[rgb][i][k] <= high:
                    outImage[rgb][i][k] = 255
                else:
                    outImage[rgb][i][k] = inPhoto
    # ************************************************** #
    cv2outImage()
    printImage()

    # for rgb in range(RGB):
    #     for i in range(inH):
    #         for k in range(inW):
    #             if sx == -1:
    #                 px = inImage[rgb][i][k]
    #
    #                 if (value1 <= px) and (px <= value2):
    #                     outImage[rgb][i][k] = 255
    #                 else:
    #                     outImage[rgb][i][k] = px
    #             else:
    #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
    #                     px = inImage[rgb][i][k]
    #
    #                     if (value1 <= px) and (px <= value2):
    #                         outImage[rgb][i][k] = 255
    #                     else:
    #                         outImage[rgb][i][k] = px
    #                 else:
    #                     outImage[rgb][i][k] = inImage[rgb][i][k]
    # # ************************************************** #
    # printImage()


# # 1-9.파라볼라 변환 (CAP, CUP)
# # (CAP : 밝은 곳이 입체적으로 보임, CUP : 어두운 곳이 입체적으로 보임)
# def cvParabolaImage(para):
#     ## ***** 영상처리 알고리즘 ***** ##
#     if para == 1:
#         cvParabolaCAP()
#     elif para == 2:
#         cvParabolaCUP()
#     # ************************************************** #
#     cv2outImage()
#     printImage()
#
# # 파라볼라 CAP 변환
# def cvParabolaCAP():
#     # 전역 변수
#     global inImage, outImage, inH, inW, outH, outW
#     global inPhoto, outPhoto
#     global window, canvas, paper, stateBar, filename
#     global sx, sy, ex, ey, boxLine
#
#     if not inImage:
#         messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
#         return
#
#     print("[OpenCV] 파라볼라 CAP 변환 이미지")
#
#     ### openCV용 함수 활용 ###
#     outPhoto = (4 / 255.0) * inPhoto * (255 - inPhoto)
#
#     # ## ***** 영상처리 알고리즘 ***** ##
#     # for rgb in range(RGB):
#     #     for i in range(inH):
#     #         for k in range(inW):
#     #             if sx == -1:
#     #                 px = (4 / 255.0) * inImage[rgb][i][k] * (255 - inImage[rgb][i][k])
#     #
#     #                 outImage[rgb][i][k] = int(px)
#     #             else:
#     #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
#     #                     px = (4 / 255.0) * inImage[rgb][i][k] * (255 - inImage[rgb][i][k])
#     #
#     #                     outImage[rgb][i][k] = int(px)
#     #                 else:
#     #                     outImage[rgb][i][k] = inImage[rgb][i][k]
# # 파라볼라 CUP 변환
# def cvParabolaCUP():
#     # 전역 변수
#     global inImage, outImage, inH, inW, outH, outW
#     global inPhoto, outPhoto
#     global window, canvas, paper, stateBar, filename
#     global sx, sy, ex, ey, boxLine
#
#     if not inImage:
#         messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
#         return
#
#     print("[OpenCV] 파라볼라 CUP 변환 이미지")
#
#     ### openCV용 함수 활용 ###
#     outPhoto = (4 / 255.0) * inPhoto * (inPhoto - 255) + 255
#
#     # ## ***** 영상처리 알고리즘 ***** ##
#     # for rgb in range(RGB):
#     #     for i in range(inH):
#     #         for k in range(inW):
#     #             if sx == -1:
#     #                 px = (4 / 255.0) * inImage[rgb][i][k] * (inImage[rgb][i][k] - 255) + 255
#     #
#     #                 outImage[rgb][i][k] = int(px)
#     #             else:
#     #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
#     #                     px = (4 / 255.0) * inImage[rgb][i][k] * (inImage[rgb][i][k] - 255) + 255
#     #
#     #                     outImage[rgb][i][k] = int(px)
#     #                 else:
#     #                     outImage[rgb][i][k] = inImage[rgb][i][k]


# # 1-10.명암대비 스트래칭 (입력)
# def cvStretchedImage():
#     # 전역 변수
#     global inImage, outImage, inH, inW, outH, outW
#     global inPhoto, outPhoto
#     global window, canvas, paper, stateBar, filename
#     global sx, sy, ex, ey, boxLine
#
#     if not inImage:
#         messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
#         return
#
#     ## ***** 영상처리 알고리즘 ***** ##
#     value = askfloat("명암대비 스트래칭", "스트래칭 값 입력 : ", minvalue=0, maxvalue=255)
#
#     print("[OpenCV] 명암대비 스트레칭 이미지, 변환값 : %.1f" % value)
#
#     outPhoto = inPhoto + (inPhoto - 128) * value
#     # ************************************************** #
#     cv2outImage()
#     printImage()
#     # for rgb in range(RGB):
#     #     for i in range(inH):
#     #         for k in range(inW):
#     #             if sx == -1:
#     #                 px = inImage[rgb][i][k] + (outImage[rgb][i][k] - 128) * value
#     #
#     #                 if px > 255:
#     #                     px = 255
#     #                 elif px <= 0:
#     #                     px = 0
#     #                 else:
#     #                     outImage[rgb][i][k] = int(px)
#     #
#     #                 outImage[rgb][i][k] = int(px)
#     #             else:
#     #                 if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
#     #                     px = inImage[rgb][i][k] + (outImage[rgb][i][k] - 128) * value
#     #
#     #                     if px > 255:
#     #                         px = 255
#     #                     elif px <= 0:
#     #                         px = 0
#     #                     else:
#     #                         outImage[rgb][i][k] = int(px)
#     #
#     #                     outImage[rgb][i][k] = int(px)
#     #                 else:
#     #                     outImage[rgb][i][k] = inImage[rgb][i][k]
#     # # ************************************************** #
#     # printImage()


print(" ")
# *************************** < 2. [OpenCV] 히스토그램 처리 기능 함수 정의부 > ***************************
def cvHistogramImage(hist):
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global histoImg, window_histo, canvas_histo, paper_histo
    global sx, sy, ex, ey, boxLine

    # 가장 높은 높이가 100으로 제한을 둠
    histoImg = np.full((100, 256), 255, dtype=np.uint8)

    histMax = np.max(hist)  # histmax = 255
    for x in range(256):
        pt1 = (x, 100)  # 시작점, 좌측 상단 기준
        pt2 = (x, 100 - int(hist[x, 0] * 100 / histMax))  # 끝점, 100을 곱하고 255로 나눠 단위 통일
        cv2.line(histoImg, pt1, pt2, 0)  # 직선을 그려 히스토그램 그리기
    return histoImg


# # 히스토그램 출력_OpenCV
# def cvHistogramImage():
#     # 전역 변수
#     global inImage, outImage, inH, inW, outH, outW
#     global inPhoto, outPhoto, histoImage
#     global window, canvas, paper, stateBar, filename
#     global sx, sy, ex, ey, boxLine
#
#     # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
#     outH = 256
#     outW = 256
#
#     # 메모리 할당
#     outImage = malloc3D(outH, outW, RGB)
#     # 히스토그램 데이터 초기화
#     reSize = outH * outW
#
#     LOW = 0
#     HIGH = 256
#
#     print("[OpenCV] 히스토그램 출력 이미지")
#
#     ## ***** 영상처리 알고리즘 ***** ##
#     histoR = [0 for _ in range(256)]
#     histoG = [0 for _ in range(256)]
#     histoB = [0 for _ in range(256)]
#
#     # 초기화
#     for i in range(256):
#         histoR, histoG, histoB = [0] * 3
#
#     # 빈도수 조사
#     for rgb in range(RGB):
#         for i in range(outH):
#             for k in range(outW):
#                 value = outImage[rgb][i][k]
#                 histoR[value] += 1
#                 histoG[value] += 1
#                 histoB[value] += 1
#
#     # 정규화
#     minR, minG, minB = [0] * 3
#     maxR, maxB, maxB = [0] * 3
#     difR, difG, difB = [0] * 3
#
#     for i in range(256):
#         if histoR[i] <= minR:
#             minR = histoR[i]
#         elif histoR[i] >= maxR:
#             maxR = histoR[i]
#         if histoG[i] <= minG:
#             minG = histoG[i]
#         elif histoG[i] >= maxG:
#             maxG = histoG[i]
#         if histoB[i] <= minB:
#             minB = histoB[i]
#         elif histoB[i] >= maxB:
#             maxB = histoB[i]
#
#     difR = maxR - minR
#     difG = maxG - minG
#     difB = maxB - minB
#
#     # 정규화된 히스토그램
#     scaleHistoR = [0 for _ in range(256)]
#     scaleHistoG = [0 for _ in range(256)]
#     scaleHistoB = [0 for _ in range(256)]
#     for i in range(outH):
#         scaleHistoR[i] = (histoR[i] - minR) * HIGH / difR
#         scaleHistoG[i] = (histoG[i] - minG) * HIGH / difG
#         scaleHistoB[i] = (histoB[i] - minB) * HIGH / difB
#
#     # 정규화된 히스토그램 출력
#     outImageR = [0 for _ in range(reSize)]
#     outImageG = [0 for _ in range(reSize)]
#     outImageB = [0 for _ in range(reSize)]
#
#     # 정규화된 히스토그램의 값은 출력배열에 검은 점으로 표현
#     for i in range(outH):
#         for k in range(scaleHistoR[i]):
#             outImageR[outW * (outH - k - 1) + i] = 0
#         for k in range(scaleHistoG[i]):
#             outImageG[outW * (outH - k - 1) + i] = 0
#         for k in range(scaleHistoB[i]):
#             outImageB[outW * (outH - k - 1) + i] = 0
#
#     histoNum = 0
#     # BGR로 출력
#     for i in range(outH):
#         for k in range(outW):
#             histoImage[RR][i][k] = outImageR[histoNum]
#             histoImage[GG][i][k] = outImageG[histoNum]
#             histoImage[BB][i][k] = outImageB[histoNum]
#             histoNum += 1
#     # ************************************************** #
#     cvPrintImage()


print(" ")
# 히스토그램 출력_OpenCV
def cvPrintHisto():
    hist = cv2.calcHist([inPhoto], [0], None, [256], [0, 256])
    histImg = cvHistogramImage(hist)


# 2-1.히스토그램 스트레칭_OpenCV
def cvHistoStretch():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 히스토그램 스트레칭 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = cv2.normalize(inPhoto, None, 0, 255, cv2.NORM_MINMAX)  # 히스토그램 스트레칭은 NORM_MINMAX

    # 넘파이로 히스토그램 스트레칭 구현
    gmin = np.min(inPhoto)
    gmax = np.max(inPhoto)
    outPhoto = np.clip((inPhoto - gmin) * 255. / (gmax - gmin), 0, 255).astype(np.uint8)
    # ************************************************** #
    cv2outImage()
    printImage()


# 2-2.히스토그램 엔드-인 탐색_OpenCV
def cvHistoEndIn():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 히스토그램 엔드-인 탐색 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = cv2.normalize(inPhoto, None, 0, 255, cv2.NORM_MINMAX)
    # ************************************************** #
    cv2outImage()
    printImage()


# 2-3.히스토그램 평활화_OpenCV
def cvHistoEqual():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 히스토그램 평활화 이미지")

    ### openCV용 함수 활용 ###
    yuvPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_BGR2YUV)
    yuvPhoto[:, :, 0] = cv2.equalizeHist(yuvPhoto[:, :, 0])
    outPhoto = cv2.cvtColor(yuvPhoto, cv2.COLOR_YUV2BGR)
    # ************************************************** #
    cv2outImage()
    printImage()


# *************************** < 3. [OpenCV] 화소 영역 처리 기능 함수 정의부 > ***************************
# 엠보싱_OpenCV
def cvEmbossing():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 엠보싱 이미지")

    ### openCV용 함수 활용 ###
    # 3x3마스크 생성
    Emask = np.zeros((3, 3), np.float32)
    Emask[0][0] = -1.0
    Emask[2][2] = 1.0
    print(Emask)

    outPhoto = cv2.filter2D(inPhoto, -1, Emask)
    outPhoto += 127  # 각 화소에 127을 더해줌
    # ************************************************** #
    cv2outImage()
    printImage()


# 3-2.블러링 (3x3 블러링, 5x5 블러링)_OpenCV
def cvBlurring(blurr):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 3x3 블러링_OpenCV
    if blurr == 1:
        print("[OpenCV] 3x3 블러링 이미지")

        ### openCV용 함수 활용 ###
        # 3x3마스크 생성
        B3mask = np.zeros((3, 3), np.float32)
        B3mask[:3][:3] = 1. / 9
        print(B3mask)

        outPhoto = cv2.filter2D(inPhoto, -1, B3mask)

        # # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        # outPhoto += 127       # 각 화소에 127을 더해줌
    # 5x5 블러링_OpenCV
    elif blurr == 2:
        print("[OpenCV] 5x5 블러링 이미지")

        ### openCV용 함수 활용 ###
        # 5x5마스크 생성
        B5mask = np.zeros((5, 5), np.float32)
        B5mask[:5][:5] = 1. / 25
        print(B5mask)

        outPhoto = cv2.filter2D(inPhoto, -1, B5mask)

        # # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        # outPhoto += 127       # 각 화소에 127을 더해줌
    # 스무딩(가우시안) 블러링
    elif blurr == 3:
        print("[OpenCV] 가우시안 블러링 이미지")

        ### openCV용 함수 활용 ###
        # 3x3마스크 생성
        Smask = np.zeros((3, 3), np.float32)
        Smask[0][0], Smask[0][2], Smask[2][0], Smask[2][2] = [1. / 16] * 4
        Smask[0][1], Smask[1][0], Smask[1][2], Smask[2][1] = [1. / 8] * 4
        Smask[1][1] = 1. / 4

        outPhoto = cv2.filter2D(inPhoto, -1, Smask)

        # # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        # outPhoto += 127       # 각 화소에 127을 더해줌
    # ************************************************** #
    cv2outImage()
    printImage()


# 3-3.샤프닝_OpenCV
def cvSharpeningImage(sharp):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 샤프닝_OpenCV
    if sharp == 1:
        print("[OpenCV] 샤프닝 이미지")

        ### openCV용 함수 활용 ###
        # 3x3마스크 생성
        Smask = np.zeros((3, 3), np.float32)
        Smask[:3][:3] = -1.0
        Smask[1][1] = 9.0
        print(Smask)

        outPhoto = cv2.filter2D(inPhoto, -1, Smask)

        # # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        # outPhoto += 127       # 각 화소에 127을 더해줌
    # 고주파필터 처리 샤프닝_OpenCV
    elif sharp == 2:
        print("[OpenCV] 고주파필터 처리 샤프닝 이미지")

        ### openCV용 함수 활용 ###
        # 3x3마스크 생성
        HPFmask = np.zeros((3, 3), np.float32)
        HPFmask[:3][:3] = -1. / 9
        HPFmask[1][1] = 8. / 9
        print(HPFmask)

        outPhoto = cv2.filter2D(inPhoto, -1, HPFmask)

        # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        outPhoto += 127  # 각 화소에 127을 더해줌
    # 저주파필터 처리 샤프닝_OpenCV
    elif sharp == 3:
        print("[OpenCV] 저주파필터 처리 샤프닝 이미지")

        ### openCV용 함수 활용 ###
        # 3x3마스크 생성
        LPFmask = np.zeros((3, 3), np.float32)
        LPFmask[0][0], LPFmask[0][2], LPFmask[2][0], LPFmask[2][2] = [1. / 16] * 4
        LPFmask[0][1], LPFmask[1][0], LPFmask[1][2], LPFmask[2][1] = [2. / 16] * 4
        LPFmask[1][1] = 4. / 16
        print(LPFmask)

        outPhoto = cv2.filter2D(inPhoto, -1, LPFmask)

        # # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        # outPhoto += 127  # 각 화소에 127을 더해줌
    # ************************************************** #
    cv2outImage()
    printImage()


# *************************** < 4. [OpenCV] 엣지 검출 기능 함수 정의부 > ***************************
# 4-1.이동과 차분 엣지 검출_OpenCV (수직, 수평)
def cvShiftDifferEdgeImage(edge):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 수직 엣지 검출_OpenCV
    if edge == 1:
        print("[OpenCV] 이동과 차분 수직 엣지 검출")

        ### openCV용 함수 활용 ###
        # 3x3마스크 생성
        Hmask = np.zeros((3, 3), np.float32)
        Hmask[:3][:3] = 0
        Hmask[1][0] = -1
        Hmask[1][1] = 1
        print(Hmask)

        outPhoto = cv2.filter2D(inPhoto, -1, Hmask)

        # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        outPhoto += 127       # 각 화소에 127을 더해줌
    # 수평 엣지 검출_OpenCV
    elif edge == 2:
        print("[OpenCV] 이동과 차분 수평 엣지 검출")

        ### openCV용 함수 활용 ###
        # 3x3마스크 생성
        Vmask = np.zeros((3, 3), np.float32)
        Vmask[:3][:3] = 0
        Vmask[0][1] = -1
        Vmask[1][1] = 1
        print(Vmask)

        outPhoto = cv2.filter2D(inPhoto, -1, Vmask)

        # 후처리 (마스크의 합이 0이 아니면 주석 처리)
        outPhoto += 127  # 각 화소에 127을 더해줌
    # ************************************************** #
    cv2outImage()
    printImage()

# 4-2.라플라시안 엣지_OpenCV
def cvLaplacianImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 라플라시안 엣지 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = cv2.Laplacian(inPhoto, cv2.CV_8U, ksize=3)
    # ************************************************** #
    cv2outImage()
    printImage()


# 4-3.캐니 엣지_OpenCV
def cvCannyImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 캐니 엣지 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = cv2.Canny(inPhoto, 60, 200, apertureSize = 3, L2gradient = True)
    # ************************************************** #
    cv2outImage()
    printImage()


# 4-4.윤곽형 검출 (일반, 다각형 근사)_OpenCV
def cvContourImage(contour):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 윤곽선 일반 검출_OpenCV
    if contour == 1:
        print("[OpenCV] 윤곽선 일반 검출 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        outPhoto = inPhoto[:]  # == inPhoto.copy()
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))

        grayPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        _, binaryPhoto = cv2.threshold(grayPhoto, 220, 255, cv2.THRESH_BINARY)
        morpPhoto = cv2.morphologyEx(binaryPhoto, cv2.MORPH_CLOSE, kernel, iterations=2)
        image = cv2.bitwise_not(morpPhoto)
        contours, _ = cv2.findContours(image, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

        ### openCV용 함수 활용 ###
        cv2.drawContours(outPhoto, contours, -1, (0, 255, 0), 5)
    # 윤곽선 다각형 근사 검출_OpenCV
    elif contour == 2:
        print("[OpenCV] 윤곽선 다각형 근사 검출 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        outPhoto = inPhoto[:]  # == inPhoto.copy()
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))

        grayPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        _, binaryPhoto = cv2.threshold(grayPhoto, 220, 255, cv2.THRESH_BINARY)
        morpPhoto = cv2.morphologyEx(binaryPhoto, cv2.MORPH_CLOSE, kernel, iterations=2)
        image = cv2.bitwise_not(morpPhoto)
        contours, _ = cv2.findContours(image, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

        ### openCV용 함수 활용 ###
        for i in contours:
            perimeter = cv2.arcLength(i, True)
            epsilon = perimeter * 0.05
            approx = cv2.approxPolyDP(i, epsilon, True)
            cv2.drawContours(outPhoto, [approx], 0, (0, 255, 0), 5)
            for j in approx:
                cv2.circle(outPhoto, tuple(j[0]), 2, (0, 0, 255), -1)
    # ************************************************** #
    cv2outImage()
    printImage()

# 코너 검출 (GFTT-1, GFTT-2, Harris, FAST)_OpenCV
def cvCornerImage(corner):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # GFTT-1_OpenCV
    if corner == 1:
        print("[OpenCV] GFTT-1 검출 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        outPhoto = inPhoto[:]  # == inPhoto.copy()
        grayPhoto = cv2.cvtColor(outPhoto, cv2.COLOR_RGB2GRAY)

        ### openCV용 함수 활용 ###
        corners = cv2.goodFeaturesToTrack(grayPhoto, 100, 0.01, 5, blockSize=3, useHarrisDetector=True, k=0.03)

        for i in corners:
            cv2.circle(outPhoto, tuple((int(i[0][0]), int(i[0][1]))), 3, (255, 0, 0), 5)

        criteria = (cv2.TERM_CRITERIA_MAX_ITER + cv2.TERM_CRITERIA_EPS, 30, 0.001)
        cv2.cornerSubPix(grayPhoto, corners, (5, 5), (-1, -1), criteria)

        for i in corners:
            cv2.circle(outPhoto, tuple((int(i[0][0]), int(i[0][1]))), 3, (0, 255, 0), 5)
    # GFTT-2_OpenCV
    elif corner == 2:
        print("[OpenCV] GFTT-2 검출 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        outPhoto = inPhoto[:]  # == inPhoto.copy()
        grayPhoto = cv2.cvtColor(outPhoto, cv2.COLOR_RGB2GRAY)

        ### openCV용 함수 활용 ###
        gftt = cv2.GFTTDetector_create()
        point = gftt.detect(grayPhoto, None)
        outPhoto = cv2.drawKeypoints(outPhoto, point, None)
    # Harris_OpenCV
    elif corner == 3:
        print("[OpenCV] Harris 검출 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        outPhoto = inPhoto[:]  # == inPhoto.copy()
        grayPhoto = cv2.cvtColor(outPhoto, cv2.COLOR_RGB2GRAY)

        ### openCV용 함수 활용 ###
        corner = cv2.cornerHarris(grayPhoto, 2, 3, 0.05)
        outPhoto[corner > 0.01 * corner.max()] = [0, 0, 255]

        normal_out = cv2.normalize(corner, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
    # FAST_OpenCV
    elif corner == 4:
        print("[OpenCV] FAST 검출 이미지")

        ## ***** 영상처리 알고리즘 ***** ##
        outPhoto = inPhoto[:]  # == inPhoto.copy()
        grayPhoto = cv2.cvtColor(outPhoto, cv2.COLOR_RGB2GRAY)

        ### openCV용 함수 활용 ###
        fast = cv2.FastFeatureDetector_create(50)
        point = fast.detect(grayPhoto, None)
        outPhoto = cv2.drawKeypoints(outPhoto, point, None, color=(0, 255, 0))
    # ************************************************** #
    cv2outImage()
    printImage()


# *************************** < 5. [OpenCV] 기하학 처리 기능 함수 정의부 > ***************************
# 5-1.미러링 (좌우/상하/상하+좌우)_OpenCV
def cvMirroringImage(mirror):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 좌우 미러링_OpenCV
    if mirror == 1:
        print("[OpenCV] 좌우 미러링 이미지")

        ### openCV용 함수 활용 ###
        outPhoto = cv2.flip(inPhoto, 1)
    # 상하 미러링_OpenCV
    elif mirror == 2:
        print("[OpenCV] 상하 미러링 이미지")

        ### openCV용 함수 활용 ###
        outPhoto = cv2.flip(inPhoto, 0)
    # 상하+좌우 미러링_OpenCV
    elif mirror == 3:
        print("[OpenCV] 상하 좌우 미러링 이미지")

        ### openCV용 함수 활용 ###
        outPhoto = cv2.flip(inPhoto, -1)
    # ************************************************** #
    cv2outImage()
    printImage()


# 5-2.자유 회전 (백워딩 + 중앙회전)_OpenCV
def cvTurnImage(turn):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    value = askfloat("자유 회전_백워딩+중앙회전 (시계방향)", "회전 각도 입력 : ", minvalue=-360, maxvalue=360)

    print("[OpenCV] 자유 회전 %.1f도 회전 이미지" % value)

    center = (inW / 2, inH / 2)
    scale_ratio = 1  # 화면 크기 비율 (조절 가능)

    ### openCV용 함수 활용 ###
    matrix = cv2.getRotationMatrix2D(center, value, scale_ratio)

    radians = math.radians(value)
    sin = math.sin(radians)
    cos = math.cos(radians)
    bound_w = int((outH * scale_ratio * abs(sin)) + (outW * scale_ratio * abs(cos)))
    bound_h = int((outH * scale_ratio * abs(cos)) + (outW * scale_ratio * abs(sin)))

    matrix[0, 2] += ((bound_w / 2) - center[0])
    matrix[1, 2] += ((bound_h / 2) - center[1])

    outPhoto = cv2.warpAffine(inPhoto, matrix, (bound_w, bound_h))
    # ************************************************* #
    cv2outImage()
    printImage()


# 5-3.이미지 크기(규격) 확대/축소_OpenCV
def cvImageSizeUpDown(size):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto  # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
        return

    # 이미지 크기 확대 (백워딩)_OpenCV
    elif size == 1:
        ## OpenCV용 알고리즘 ##
        ratio = askinteger("이미지 크기 확대 (백워딩)", "확대 배율(2의 제곱) 입력 : ", minvalue=0, maxvalue=10)

        print("%d배 확대(백워딩) 이미지" % ratio)

        outPhoto = inPhoto.copy()
        for _ in range(ratio):
            outPhoto = cv2.pyrUp(outPhoto)  # 피라미드 업
    # 이미지 크기 축소 (백워딩)_OpenCV
    elif size == 2:
        ## OpenCV용 알고리즘 ##
        ratio = askinteger("이미지 크기 축소 (백워딩)", "축소 배율(2의 제곱) 입력 : ", minvalue=0, maxvalue=10)

        print("%d배 축소(백워딩) 이미지" % ratio)

        outPhoto = inPhoto.copy()
        for _ in range(ratio):
            outPhoto = cv2.pyrDown(outPhoto)  # 피라미드 다운
    # ************************************************* #
    cv2outImage()
    printImage()


# *************************** < 6. [OpenCV] 웹캠 영상처리 기능 함수 정의부 > ***************************
# 웹캠 영상처리
def WebCam_ImageProcessing(func):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    print("[웹캠_캐니 엣지 검출]")
    print("캡쳐:C, 녹화:R, 녹화 종료(Ctrl+R), 종료:ESC")

    capture = cv2.VideoCapture(0)

    record = False
    isFirst = True

    while True:
        ret, frame = capture.read()

        if not ret:     # 프레임 정보를 정상적으로 읽지 못하면 while 문 빠져나가기
            break

        ## 웹캠 인식 (=객체 인식) ##
        frame = cv2.flip(frame, 1)          # 이미지 반전,  0:상하, 1 : 좌우

        # 웹캠 (원본) 출력
        cv2.imshow('Original', frame)

        # 웹캠 캐니 엣지 검출_OpenCV
        if func == 1:
            # 영상처리 웹캠 출력
            edges = cv2.Canny(frame, 100, 200)
            cv2.imshow('Canny Edges', edges)

        # 그레디언트 엣지 검출_OpenCV
        elif func == 2:
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

            lower_red = np.array([30, 150, 50])
            upper_red = np.array([255, 255, 180])

            mask = cv2.inRange(hsv, lower_red, upper_red)
            res = cv2.bitwise_and(frame, frame, mask=mask)

            laplacian = cv2.Laplacian(frame, cv2.CV_64F)
            sobelx = cv2.Sobel(frame, cv2.CV_64F, 1, 0, ksize=5)
            sobely = cv2.Sobel(frame, cv2.CV_64F, 0, 1, ksize=5)

            # 영상처리 웹캠 춮력
            #cv2.imshow('Mask', mask)
            cv2.imshow('laplacian', laplacian)
            cv2.imshow('sobelx', sobelx)
            cv2.imshow('sobely', sobely)

        # 라플라시안 엣지 검출_OpenCV
        elif func == 3:
            # 영상처리 웹캠 출력
            edges = cv2.Laplacian(frame, cv2.CV_8U, ksize=3)
            cv2.imshow('Laplacian Edges', edges)

        ## 키 입력 ##
        key = cv2.waitKey(6)
        # 종료 --> ESC키 입력
        if key == 27:  # ESC 키
            outPhoto = frame
            cv2outImage_WebCam()
            printImage()
            print("웹캠 종료!!")
            break

        # 캡쳐 --> C키 입력
        if key == ord('C') or key == ord('c'):
            # cv2.imwrite("경로 및 제목", 이미지)
            cv2.imwrite('./CaptureFile/WebCamCapture ' + str(nowTime) + '.png', frame)
            print("웹캠 캡쳐 완료!")

        # 녹화 --> R키 입력
        if key == ord('R') or key == ord('r'):
            print("녹화 시작!")
            record = True
            # cv2.VideoWriter("경로 및 제목", 비디오 포맷 코드, FPS, (녹화 파일 너비, 녹화 파일 높이))
            video = cv2.VideoWriter("./Save/RecordFile/WebCamRecord " + str(nowTime) + ".avi", fourcc,
                                    20.0, (frame.shape[1], frame.shape[0]))  # 20.0 : FPS (영상이 바뀌는 속도 의미, 화면의 부드러움 정도)
        # 녹화 종료 --> Ctrl+R 키 입력
        elif key == 18:  # Ctrl+R
            print("녹화 종료!")
            record = False
            video.release()  # 메모리 해제
        # record 가 True 면, 화면 녹화
        elif record is True:
            video.write(frame)  # 비디오를 '프레임'에 저장
            if isFirst:
                print("녹화 중..")
                isFirst = False

    cv2.destroyAllWindows()     # 화면에 나타난 윈도우 종료
    capture.release()


# 공 추적하기_OpenCV
def CVwebCamMenu_TraceBall():
    print("공 추적하기")

    # construct the argument parse and parse the arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-v", "--video",
                    help="path to the (optional) video file")
    ap.add_argument("-b", "--buffer", type=int, default=64,
                    help="max buffer size")
    args = vars(ap.parse_args())

    # define the lower and upper boundaries of the "green"
    # ball in the HSV color space, then initialize the
    # list of tracked points
    greenLower = (29, 86, 6)
    greenUpper = (64, 255, 255)
    pts = deque(maxlen=args["buffer"])

    # if a video path was not supplied, grab the reference
    # to the webcam
    if not args.get("video", False):
        capture = VideoStream(src=0).start()

    # otherwise, grab a reference to the video file
    else:
        # vs = cv2.VideoCapture(args["video"])      # 동영상 파일 실행 시
        capture = cv2.VideoCapture(0)                    # 웹캠 사용 시

    # allow the camera or video file to warm up
    time.sleep(2.0)

    record = False
    isFirst = True

    # keep looping
    while True:
        # grab the current frame
        frame = capture.read()

        # handle the frame from VideoCapture or VideoStream
        frame = frame[1] if args.get("video", False) else frame

        # if we are viewing a video and we did not grab a frame,
        # then we have reached the end of the video
        if frame is None:
            break

        ## 웹캠 인식 (=객체 인식) ##
        frame = cv2.flip(frame, 1)  # 이미지 반전,  0:상하, 1 : 좌우

        # resize the frame, blur it, and convert it to the HSV
        # color space
        frame = imutils.resize(frame, width=600)
        blurred = cv2.GaussianBlur(frame, (11, 11), 0)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

        # construct a mask for the color "green", then perform
        # a series of dilations and erosions to remove any small
        # blobs left in the mask
        mask = cv2.inRange(hsv, greenLower, greenUpper)
        mask = cv2.erode(mask, None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)

        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                                cv2.CHAIN_APPROX_SIMPLE)
        # cnts = cnts[0] if imutils.is_cv2() else cnts[1]
        cnts = imutils.grab_contours(cnts)
        center = None

        # only proceed if at least one contour was found
        if len(cnts) > 0:
            # find the largest contour in the mask, then use
            # it to compute the minimum enclosing circle and
            # centroid
            c = max(cnts, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

            # only proceed if the radius meets a minimum size
            if radius > 10:
                # draw the circle and centroid on the frame,
                # then update the list of tracked points
                cv2.circle(frame, (int(x), int(y)), int(radius),
                           (0, 255, 255), 2)
                cv2.circle(frame, center, 5, (0, 0, 255), -1)

        # update the points queue
        pts.appendleft(center)

        # loop over the set of tracked points
        for i in range(1, len(pts)):
            # if either of the tracked points are None, ignore
            # them
            if pts[i - 1] is None or pts[i] is None:
                continue

            # otherwise, compute the thickness of the line and
            # draw the connecting lines
            thickness = int(np.sqrt(args["buffer"] / float(i + 1)) * 2.5)
            cv2.line(frame, pts[i - 1], pts[i], (0, 0, 255), thickness)

        # show the frame to our screen
        cv2.imshow("Frame", frame)

        ## 키 입력 ##
        key = cv2.waitKey(6)
        # 종료 --> ESC키 입력
        if key == 27:  # ESC 키
            outPhoto = frame
            cv2outImage_WebCam()
            printImage()
            print("웹캠 종료!!")
            break

        # 캡쳐 --> C키 입력
        if key == ord('C') or key == ord('c'):
            # cv2.imwrite("경로 및 제목", 이미지)
            cv2.imwrite('./CaptureFile/WebCamCapture ' + str(nowTime) + '.png', frame)
            print("웹캠 캡쳐 완료!")

        # 녹화 --> R키 입력
        if key == ord('R') or key == ord('r'):
            print("녹화 시작!")
            record = True
            # cv2.VideoWriter("경로 및 제목", 비디오 포맷 코드, FPS, (녹화 파일 너비, 녹화 파일 높이))
            video = cv2.VideoWriter("./Save/RecordFile/WebCamRecord " + str(nowTime) + ".avi", fourcc,
                                    20.0, (frame.shape[1], frame.shape[0]))  # 20.0 : FPS (영상이 바뀌는 속도 의미, 화면의 부드러움 정도)
        # 녹화 종료 --> Ctrl+R 키 입력
        elif key == 18:  # Ctrl+R
            print("녹화 종료!")
            record = False
            video.release()  # 메모리 해제
        # record 가 True 면, 화면 녹화
        elif record is True:
            video.write(frame)  # 비디오를 '프레임'에 저장
            if isFirst:
                print("녹화 중..")
                isFirst = False

    # if we are not using a video file, stop the camera video stream
    if not args.get("video", False):
        capture.stop()

    # otherwise, release the camera
    else:
        capture.release()

    # close all windows
    cv2.destroyAllWindows()

    # 참고 : https://diy-project.tistory.com/96


# HSV 변환_OpenCV
def cvHSVImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] HSV 변환 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_BGR2HSV)
    ########################
    cv2outImage()
    printImage()


# 색상 추출 (오렌지 색상)_OpenCV
def cvMyColorImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 색상 추출 (오렌지 색상) ")

    ### openCV용 함수 활용 ###
    outPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_BGR2HSV)
    h, s, v = cv2.split(outPhoto)
    h_orange = cv2.inRange(h, 8, 20)
    outPhoto = cv2.bitwise_and(outPhoto, outPhoto, mask=h_orange)
    outPhoto = cv2.cvtColor(outPhoto, cv2.COLOR_HSV2BGR)
    #######################
    cv2outImage()
    printImage()


# *************************** < AI_OpenCV 전용 메뉴 > ***************************
# ssdNet (딥러닝 함수)_AI
def ssdNet(image, confPara):
    CONF_VALUE = confPara
    CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
               "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
               "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
               "sofa", "train", "tvmonitor"]
    COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))
    # 아래 코드가 핵심! OpenCV
    net = cv2.dnn.readNetFromCaffe("./MobileNetSSD/MobileNetSSD_deploy.prototxt.txt",
                                   "./MobileNetSSD/MobileNetSSD_deploy.caffemodel")
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


# *************************** < 1. 사람 인식 기능 함수 정의부 > ***************************
### 머신러닝 알고리즘
### 딥러닝 기반의 객체
# clf를 이용한 사람 인식
def aiHumanImage(ai):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    # 정면 얼굴 인식_AI
    if ai == 1:
        print("인공지능 - 정면 얼굴 인식")

        ## ***** 영상처리 알고리즘 ***** ##
        # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
        clf = cv2.CascadeClassifier("./Haar/haarcascade_frontalface_alt.xml")  # frontalface : 정면 얼굴

        # 얼굴 찾기
        gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        face_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

        outPhoto = inPhoto[:]  # == inPhoto.copy()
        for (x, y, w, h) in face_rects:
            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (0, 0, 255), 2)
            cv2.putText(outPhoto, 'Face', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # 눈 인식_AI
    elif ai == 2:
        print("인공지능 - 눈 인식")

        ## ***** 영상처리 알고리즘 ***** ##
        # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
        clf = cv2.CascadeClassifier("./Haar/haarcascade_eye.xml")

        # 얼굴 찾기
        gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        eyes_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

        outPhoto = inPhoto[:]  # == inPhoto.copy()
        for (x, y, w, h) in eyes_rects:
            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.putText(outPhoto, 'Eyes', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # 코 인식_AI
    elif ai == 3:
        print("인공지능 - 코 인식")

        ## ***** 영상처리 알고리즘 ***** ##
        # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
        clf = cv2.CascadeClassifier("./Haar/haarcascade_mcs_nose.xml")

        # 얼굴 찾기
        gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        nose_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

        outPhoto = inPhoto[:]  # == inPhoto.copy()
        for (x, y, w, h) in nose_rects:
            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (255, 0, 0), 2)
            cv2.putText(outPhoto, 'Nose', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # 입 인식_AI
    elif ai == 4:
        print("인공지능 - 입 인식")

        ## ***** 영상처리 알고리즘 ***** ##
        # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
        clf = cv2.CascadeClassifier("./Haar/haarcascade_mcs_mouth.xml")

        # 얼굴 찾기
        gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        mouth_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

        outPhoto = inPhoto[:]  # == inPhoto.copy()
        for (x, y, w, h) in mouth_rects:
            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (255, 0, 0), 2)
            cv2.putText(outPhoto, 'mouth', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # 왼쪽 귀 인식_AI
    elif ai == 5:
        print("인공지능 - 왼쪽 귀 인식")

        ## ***** 영상처리 알고리즘 ***** ##
        # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
        clf = cv2.CascadeClassifier("./Haar/haarcascade_mcs_leftear.xml")

        # 얼굴 찾기
        gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        leftEar_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

        outPhoto = inPhoto[:]  # == inPhoto.copy()
        for (x, y, w, h) in leftEar_rects:
            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (255, 0, 0), 2)
            cv2.putText(outPhoto, 'L_Ear', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # 오른쪽 귀 인식_AI
    elif ai == 6:
        print("인공지능 - 오른쪽 귀 인식")

        ## ***** 영상처리 알고리즘 ***** ##
        # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
        clf = cv2.CascadeClassifier("./Haar/haarcascade_mcs_rightear.xml")

        # 얼굴 찾기
        gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        rightEar_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

        outPhoto = inPhoto[:]  # == inPhoto.copy()
        for (x, y, w, h) in rightEar_rects:
            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (255, 0, 0), 2)
            cv2.putText(outPhoto, 'R_Ear', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # ************************************************** #
    cv2outImage()
    printImage()


# 얼굴 인식 영상처리(Haar)_AI
def aiFace_ImageProcessing(func):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
    clf = cv2.CascadeClassifier("./Haar/haarcascade_frontalface_alt.xml")  # frontalface : 정면 얼굴

    # 얼굴 찾기
    gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
    face_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

    outPhoto = inPhoto[:]  # == inPhoto.copy()
    for (x, y, w, h) in face_rects:
        # 찾은 사각형 내부 이미지 : crop
        crop = outPhoto[y:y + h, x:x + w]

        # 정면 얼굴 인식
        if func == 0:
            print("인공지능 - 정면 얼굴 인식")

            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (0, 0, 255), 2)
            cv2.putText(outPhoto, 'Face', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)

        # 얼굴 모자이크 (Haar)_AI
        elif func == 1:
            print("인공지능 - 얼굴 모자이크")

            scale_ratio = 0.6  # 화면 크기 비율 (조절 가능)
            small = cv2.resize(crop, None, fx=scale_ratio, fy=scale_ratio, interpolation=cv2.INTER_NEAREST)
            outPhoto[y:y + h, x:x + w] = cv2.resize(small, crop.shape[:2][::-1], interpolation=cv2.INTER_NEAREST)
        # 얼굴 카툰화 (Haar)_AI
        elif func == 2:
            print("인공지능 - 얼굴 카툰화")

            crop = cv2.cvtColor(crop, cv2.COLOR_RGB2GRAY)
            crop = cv2.medianBlur(crop, 7)
            edges = cv2.Laplacian(crop, cv2.CV_8U, ksize=5)
            ret, mask = cv2.threshold(edges, 100, 255, cv2.THRESH_BINARY_INV)
            outPhoto[y:y + h, x:x + w] = cv2.cvtColor(mask, cv2.COLOR_GRAY2RGB)
    # ************************************************** #
    cv2outImage()
    printImage()


# clf를 이용한 자동차 인식
def aiCarImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("인공지능 - 자동차 인식")

    ## ***** 영상처리 알고리즘 ***** ##
    # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
    clf = cv2.CascadeClassifier("./Haar/cars.xml")

    # 얼굴 찾기
    gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
    car_rects = clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

    outPhoto = inPhoto[:]  # == inPhoto.copy()
    for (x, y, w, h) in car_rects:
        cv2.rectangle(outPhoto, (x, y), (x+w, y+h), (0, 0, 255), 2)
        cv2.putText(outPhoto, 'Car', (x-5, y-5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)


# *************************** < 2. 동영상 인식 기능 함수 정의부 > ***************************
# MobileNet SSD를 이용한 인식
# 이미지 속 객체 인식_AI (SSD)
def DLImage_Photo():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global now

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("인공지능 - 이미지 속 객체 인식 ")

    ## 이미지 인식 (=객체 인식) ##
    cvImage = cv2.imread(filename)
    retImage = ssdNet(cvImage, 0.6)

    cv2.imshow(filename, retImage)  # 읽어드린 이미지 파일을 윈도우 창에 출력
    cv2.waitKey(0)  # 키 입력 전까지 무한 대기
    cv2.destroyAllWindows()  # 화면에 나타난 윈도우 종료, 일반적으로 위에 코드들과 같이 사용됨


# 동영상 속 객체 인식_AI (SSD)
def DLImage_Video():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("인공지능 - 동영상 속 객체 인식 ")

    ## 동영상 인식 (=객체 인식) ##
    capture = cv2.VideoCapture(filename)
    scale_factor = 0.6  # 화면 크기 비율 (조절 가능)

    frameCount = 0
    while True:
        ret, frame = capture.read()

        if not ret:
            break

        # 동영상 딥러닝
        # frameCount += 1
        # if frameCount % 5 == 0:
        frame = cv2.resize(frame, None, fx=scale_factor, fy=scale_factor,
                           interpolation=cv2.INTER_AREA)
        frame = ssdNet(frame, 0.7)
        cv2.imshow(filename, frame)

        ## 키 입력 ##
        key = cv2.waitKey(20)
        # 캡쳐 --> C키 입력
        if key == ord('c') or key == ord('C'):
            nowTime = datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
            cv2.imwrite('./CaptureFile/VideoSave ' + str(nowTime) + '.png', frame)
            print("동영상 캡쳐 완료!")

        # 동영상 중간에 중단할 때 --> esc키 입력
        elif key == 27:  # esc
            break

    capture.release()
    cv2.destroyAllWindows()


# *************************** < 3. 웹캠 인식 기능 함수 정의부 > ***************************
# 결과 화면에 출력
def cv2outImage_WebCam():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    # 중요! 입력 영상의 크기 파악
    outH = outPhoto.shape[0]
    outW = outPhoto.shape[1]

    # 메모리 할당
    outImage = malloc3D(outH, outW, RGB)

    # OpenCV 개체 --> 메모리
    # 3차원 스케일
    if outPhoto.ndim > 2:  # ndim : 넘파이 차원수 확인
        for i in range(outH):
            for k in range(outW):
                outImage[RR][i][k] = outPhoto.item(i, k, BB)  # 컴퓨터에 입력되는건 R,G,B 순서가 아닌 B,G,R 순서
                outImage[GG][i][k] = outPhoto.item(i, k, GG)
                outImage[BB][i][k] = outPhoto.item(i, k, RR)
    # 단일 스케일
    else:
        for i in range(outH):
            for k in range(outW):
                outImage[RR][i][k] = inImage[RR][i][k] = outPhoto.item(i, k)
                outImage[GG][i][k] = inImage[GG][i][k] = outPhoto.item(i, k)
                outImage[BB][i][k] = inImage[BB][i][k] = outPhoto.item(i, k)
    inH, inW = outH, outW
# 입력키 리턴값 확인
def checkRetKey():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    image = np.zeros((100, 100, 3), np.uint8)
    cv2.imshow("keytest", image)

    ret = cv2.waitKey(0)
    print('pressed key is {0}'.format(ret))


# 웹캠 인식
def WebCamDisplay():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    print("[웹캠 인식]")
    print("캡쳐:C, 녹화:R, 녹화 종료(Ctrl+R), 종료:ESC")

    webcam = cv2.VideoCapture(0)       # captureDevice = camera ## 카메라 캡쳐를 백에드에서 시키기
    scale_ratio = 1  # 화면 크기 비율 (조절 가능)
    # fourcc : 디지털 미디어 포맷 코드, 인코딩 방식 설정
    # fourCC의 종류
    # CVID, Default, DIB, DIVX, H261, H263, H264, IV32, IV41, IV50, IYUB,
    # MJPG, MP42, MP43, MPG4, MSVC, PIM1, Prompt, XVID
    fourcc = cv2.VideoWriter_fourcc(*'DIVX')  # 인코딩 방식 설정, 디지털 미디어 포맷 코드를 생성 (*'DIVX' == *'코덱')
    record = False
    isFirst = True

    while True:
        ret, frame = webcam.read()  # ret = return

        if not ret:  # 프레임 정보를 정상적으로 읽지 못하면 while 문 빠져나가기
            break

        ## 웹캠 인식 (=객체 인식) ##
        frame = cv2.resize(frame, None, fx=scale_ratio, fy=scale_ratio,
                           interpolation=cv2.INTER_AREA)
        frame = cv2.flip(frame, 1)  # 이미지 반전,  0:상하, 1 : 좌우
        cv2.imshow('WebCam', frame)

        ## 키 입력 ##
        key = cv2.waitKey(6)
        # 종료 --> ESC키 입력
        if key == 27:  # ESC 키
            outPhoto = frame
            cv2outImage_WebCam()
            printImage()
            print("웹캠 종료!!")
            break

        # 캡쳐 --> C키 입력
        if key == ord('C') or key == ord('c'):
            # cv2.imwrite("경로 및 제목", 이미지)
            cv2.imwrite('./CaptureFile/WebCamCapture ' + str(nowTime) + '.png', frame)
            print("웹캠 캡쳐 완료!")

        # 녹화 --> R키 입력
        if key == ord('R') or key == ord('r'):
            print("녹화 시작!")
            record = True
            # cv2.VideoWriter("경로 및 제목", 비디오 포맷 코드, FPS, (녹화 파일 너비, 녹화 파일 높이))
            video = cv2.VideoWriter("./Save/RecordFile/WebCamRecord " + str(nowTime) + ".avi", fourcc,
                                    20.0, (frame.shape[1], frame.shape[0]))  # 20.0 : FPS (영상이 바뀌는 속도 의미, 화면의 부드러움 정도)
        # 녹화 종료 --> Ctrl+R 키 입력
        elif key == 18:  # Ctrl+R
            print("녹화 종료!")
            record = False
            video.release()  # 메모리 해제
        # record 가 True 면, 화면 녹화
        elif record is True:
            video.write(frame)  # 비디오를 '프레임'에 저장
            if isFirst:
                print("녹화 중..")
                isFirst = False

    webcam.release()
    cv2.destroyAllWindows()     # 화면에 나타난 윈도우 종료
def WebCamDisplay_Threading():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    thread_UCC = threading.Thread(target=WebCamDisplay(), daemon=True)
    thread_UCC.start()
    thread_UCC.join()


# 웹캠 인식_Haar (머신러닝)
def haar_WebCamDisplay():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    print("[웹캠 인식_Haar]")
    print("캡쳐:C, 녹화:R, 녹화 종료(Ctrl+R), 종료:ESC")

    webcam = cv2.VideoCapture(0)       # captureDevice = camera ## 카메라 캡쳐를 백에드에서 시키기
    scale_ratio = 1  # 화면크기 비율 ( 조절 가능 )
    # fourcc : 디지털 미디어 포맷 코드, 인코딩 방식 설정
    # fourCC의 종류
    # CVID, Default, DIB, DIVX, H261, H263, H264, IV32, IV41, IV50, IYUB,
    # MJPG, MP42, MP43, MPG4, MSVC, PIM1, Prompt, XVID
    fourcc = cv2.VideoWriter_fourcc(*'DIVX')  # 인코딩 방식 설정, 디지털 미디어 포맷 코드를 생성 (*'DIVX' == *'코덱')
    record = False
    isFirst = True

    frameCount = 0
    while True:
        ret, frame = webcam.read()

        if not ret:  # 프레임 정보를 정상적으로 읽지 못하면 while 문 빠져나가기
            break

        ## 웹캠 머신러닝(haar) ##
        # frameCount += 1
        # if frameCount % 2 == 0:
        frame = cv2.resize(frame, None, fx=scale_ratio, fy=scale_ratio,
                           interpolation=cv2.INTER_AREA)
        frame = cv2.flip(frame, 1)  # 이미지 반전,  0:상하, 1 : 좌우
        gray = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)

        # 인공지능 불러오기 (모델, Classifire) --> Pre trained data
        face_clf = cv2.CascadeClassifier("./Haar/haarcascade_frontalface_alt.xml")

        # 얼굴 찾기
        face_rects = face_clf.detectMultiScale(gray, 1.1, 6)  # 인식률 높이기 위해선 마지막 매개변수 값 높이기

        outPhoto = frame[:]
        for (x, y, w, h) in face_rects:
            cv2.rectangle(outPhoto, (x, y), (x + w, y + h), (0, 0, 255), 2)
            cv2.putText(outPhoto, 'Face', (x - 5, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
        frame = outPhoto
        cv2.imshow('WebCam_Haar', frame)

        ## 키 입력 ##
        key = cv2.waitKey(6)
        # 종료 --> ESC키 입력
        if key == 27:  # ESC 키
            outPhoto = frame
            cv2outImage_WebCam()
            printImage()
            print("웹캠 종료!!")
            break

        # 캡쳐 --> C키 입력
        if key == ord('c') or key == ord('C'):
            nowTime = datetime.datetime.now().strftime('%y-%m-%d_%H-%M-%S')
            cv2.imwrite('./CaptureFile/WebCamCapture ' + str(nowTime) + '.png', frame)
            print("웹캠 캡쳐 완료!")

        # 녹화 --> R키 입력
        if key == ord('R') or key == ord('r'):
            print("녹화 시작!")
            record = True
            # cv2.VideoWriter("경로 및 제목", 비디오 포맷 코드, FPS, (녹화 파일 너비, 녹화 파일 높이))
            video = cv2.VideoWriter("./Save/RecordFile/WebCamRecord (Haar) " + str(nowTime) + ".avi", fourcc,
                                    20.0, (frame.shape[1], frame.shape[0]))  # 20.0 : FPS (영상이 바뀌는 속도 의미, 화면의 부드러움 정도)
        # 녹화 종료 --> Ctrl+R 키 입력
        elif key == 18:  # Ctrl+R
            print("녹화 종료!")
            record = False
            video.release()  # 메모리 해제
        # record 가 True 면, 화면 녹화
        elif record is True:
            video.write(frame)  # 비디오를 '프레임'에 저장
            if isFirst:
                print("녹화 중..")
                isFirst = False

    webcam.release()
    cv2.destroyAllWindows()  # 화면에 나타난 윈도우 종료
def haar_WebCamDisplay_Threading():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    thread_UCC = threading.Thread(target=haar_WebCamDisplay(), daemon=True)
    thread_UCC.start()
    thread_UCC.join()


# 웹캠 인식_ssd (딥러닝)
def SSD_WebCamDisplay():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    print("[웹캠 인식_SSD]")
    print("캡쳐:C, 녹화:R, 녹화 종료(Ctrl+R), 종료:ESC")

    webcam = cv2.VideoCapture(0)  # captureDevice = camera ## 카메라 캡쳐를 백에드에서 시키기
    scale_ratio = 1  # 화면크기 비율 ( 조절 가능 )
    # fourcc : 디지털 미디어 포맷 코드, 인코딩 방식 설정
    # fourCC의 종류
    # CVID, Default, DIB, DIVX, H261, H263, H264, IV32, IV41, IV50, IYUB,
    # MJPG, MP42, MP43, MPG4, MSVC, PIM1, Prompt, XVID
    fourcc = cv2.VideoWriter_fourcc(*'DIVX')  # 인코딩 방식 설정, 디지털 미디어 포맷 코드를 생성 (*'DIVX' == *'코덱')
    record = False
    isFirst = True

    frameCount = 0
    while True:
        ret, frame = webcam.read()

        if not ret:  # 프레임 정보를 정상적으로 읽지 못하면 while 문 빠져나가기
            break

        ## 웹캠 딥러닝(SSD) ##
        # frameCount += 1
        # if frameCount % 10 == 0:
        frame = cv2.resize(frame, None, fx=scale_ratio, fy=scale_ratio,
                           interpolation=cv2.INTER_AREA)
        frame = cv2.flip(frame, 1)  # 이미지 반전,  0:상하, 1 : 좌우
        outPhoto = ssdNet(frame, 0.6)
        frame = outPhoto
        cv2.imshow('WebCam_SSD', frame)

        ## 키 입력 ##
        key = cv2.waitKey(6)
        # 종료 --> ESC키 입력
        if key == 27:  # ESC 키
            outPhoto = frame
            cv2outImage_WebCam()
            printImage()
            print("웹캠 종료!!")
            break

        # 캡쳐 --> C키 입력
        if key == ord('c') or key == ord('C'):
            nowTime = datetime.datetime.now().strftime('%y-%m-%d_%H-%M-%S')
            cv2.imwrite('./CaptureFile/WebCamCapture ' + str(nowTime) + '.png', frame)
            print("웹캠 캡쳐 완료!")

        # 녹화 --> R키 입력
        if key == ord('R') or key == ord('r'):
            print("녹화 시작!")
            record = True
            # cv2.VideoWriter("경로 및 제목", 비디오 포맷 코드, FPS, (녹화 파일 너비, 녹화 파일 높이))
            video = cv2.VideoWriter("./Save/RecordFile/WebCamRecord (SSD) " + str(nowTime) + ".avi", fourcc,
                                    20.0, (frame.shape[1], frame.shape[0]))  # 20.0 : FPS (영상이 바뀌는 속도 의미, 화면의 부드러움 정도)
        # 녹화 종료 --> Ctrl+R 키 입력
        elif key == 18:  # Ctrl+R
            print("녹화 종료!")
            record = False
            video.release()  # 메모리 해제
        # record 가 True 면, 화면 녹화
        elif record is True:
            video.write(frame)  # 비디오를 '프레임'에 저장
            if isFirst:
                print("녹화 중..")
                isFirst = False

    webcam.release()
    cv2.destroyAllWindows()  # 화면에 나타난 윈도우 종료
def SSD_WebCamDisplay_Threading():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    thread_UCC = threading.Thread(target=SSD_WebCamDisplay(), daemon=True)
    thread_UCC.start()
    thread_UCC.join()


# 웹캠 얼굴 인식 영상처리(Haar)_AI
def WebCam_aiFace_ImageProcessing(func):
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime

    print("인공지능 - 웹캠 속 객체 인식 ")

    ## 동영상 인식 (=객체 인식) ##
    webcam = cv2.VideoCapture(0)

    record = False
    isFirst = True

    ## ***** 영상처리 알고리즘 ***** ##
    # 인공지능 불러오기 (모델, Classifire, clf) --> pre-Trained Data
    clf = cv2.CascadeClassifier("./Haar/haarcascade_frontalface_alt.xml")  # frontalface : 정면 얼굴

    while True:
        ret, frame = webcam.read()

        if not ret:
            break

        ## 웹캠 인식 (=객체 인식) ##
        frame = cv2.flip(frame, 1)  # 이미지 반전,  0:상하, 1 : 좌우

        # 웹캠 (원본) 출력
        cv2.imshow('Original', frame)

        gray = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
        face_rects = clf.detectMultiScale(gray, 1.1, 6)  # 얼굴 인식 4개의 좌표

        # 얼굴 찾기
        outPhoto = inPhoto[:]  # == inPhoto.copy()
        for (x, y, w, h) in face_rects:
            # 찾은 사각형 내부 이미지 : crop
            crop = frame[y:y + h, x:x + w]

            # 웹캠 모자이크 (Haar)_AI
            if func == 1:
                print("인공지능 - 웹캠 얼굴 모자이크")

                scale_ratio = 0.05
                small = cv2.resize(crop, None, fx=scale_ratio, fy=scale_ratio, interpolation=cv2.INTER_NEAREST)
                frame[y:y + h, x:x + w] = cv2.resize(small, crop.shape[:2][::-1], interpolation=cv2.INTER_NEAREST)

                # 영상처리 웹캠 출력
                cv2.imshow('Mosaic', frame)
            # 얼굴 카툰화 (Haar)_AI
            elif func == 2:
                print("인공지능 - 얼굴 카툰화")

                crop = cv2.cvtColor(crop, cv2.COLOR_RGB2GRAY)
                crop = cv2.medianBlur(crop, 7)
                edges = cv2.Laplacian(crop, cv2.CV_8U, ksize=5)
                ret, mask = cv2.threshold(edges, 100, 255, cv2.THRESH_BINARY_INV)
                outPhoto[y:y + h, x:x + w] = cv2.cvtColor(mask, cv2.COLOR_GRAY2RGB)

                # 영상처리 웹캠 출력
                cv2.imshow('Cartoon', frame)


        ## 키 입력 ##
        key = cv2.waitKey(6)
        # 종료 --> ESC키 입력
        if key == 27:  # ESC 키
            outPhoto = frame
            cv2outImage_WebCam()
            printImage()
            print("웹캠 종료!!")
            break

        # 캡쳐 --> C키 입력
        if key == ord('C') or key == ord('c'):
            # cv2.imwrite("경로 및 제목", 이미지)
            cv2.imwrite('./CaptureFile/WebCamCapture ' + str(nowTime) + '.png', frame)
            print("웹캠 캡쳐 완료!")

        # 녹화 --> R키 입력
        if key == ord('R') or key == ord('r'):
            print("녹화 시작!")
            record = True
            # cv2.VideoWriter("경로 및 제목", 비디오 포맷 코드, FPS, (녹화 파일 너비, 녹화 파일 높이))
            video = cv2.VideoWriter("./Save/RecordFile/WebCamRecord " + str(nowTime) + ".avi", fourcc,
                                    20.0, (frame.shape[1], frame.shape[0]))  # 20.0 : FPS (영상이 바뀌는 속도 의미, 화면의 부드러움 정도)
        # 녹화 종료 --> Ctrl+R 키 입력
        elif key == 18:  # Ctrl+R
            print("녹화 종료!")
            record = False
            video.release()  # 메모리 해제
        # record 가 True 면, 화면 녹화
        elif record is True:
            video.write(frame)  # 비디오를 '프레임'에 저장
            if isFirst:
                print("녹화 중..")
                isFirst = False

    webcam.release()
    cv2.destroyAllWindows()


# *************************** < 4. 유튜브 인식 기능 함수 정의부 > ***************************
# 딥러닝 기반의 객체
# 유튜브 연동 함수
def YouTubeDisplay():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime, url

    print("[YouTube_영상 출력]")
    url = askstring("유튜브 링크 입력창", "화면에 출력할 유튜브 영상의 URL 입력")

    if not url or url == "":
        return

    ytVideo = pafy.new(url)
    best = ytVideo.getbest(preftype='mp4')  # 'webm','3gp'
    capture = cv2.VideoCapture(best.url)

    title = ytVideo.title
    frameCount = 0
    s_factor = 0.8  # 화면크기 비율 ( 조절 가능 )

    while True:
        ret, frame = capture.read()

        if not ret:  # 프레임 정보를 정상적으로 읽지 못하면 while 문 빠져나가기
            break

        ## 동영상 딥러닝(SSD) ##
        frameCount += 1
        if frameCount % 5 == 0:
            frame = cv2.resize(frame, None, fx=s_factor, fy=s_factor, interpolation=cv2.INTER_AREA)
            # frame = ssdNet(frame)
            # 화면출력
            cv2.imshow("Youtube", frame)
        key = cv2.waitKey(25)

        ## 키 입력 ##
        key = cv2.waitKey(6)
        # 종료 --> ESC키 입력
        if key == 27:  # ESC 키
            outPhoto = frame
            filename = title
            cv2outImage_WebCam()
            printImage()
            print("유튜브 종료!!")
            break

        # 캡쳐 --> C키 입력
        if key == ord('C') or key == ord('c'):
            filename = title
            # cv2.imwrite("경로 및 제목", 이미지)
            cv2.imwrite('./CaptureFile/YouTubeCapture ' + str(nowTime) + '.png', frame)
            print("유튜브 캡쳐 완료!")

        # # 녹화 --> R키 입력
        # if key == ord('R') or key == ord('r'):
        #     print("녹화 시작!")
        #     record = True
        #     # cv2.VideoWriter("경로 및 제목", 비디오 포맷 코드, FPS, (녹화 파일 너비, 녹화 파일 높이))
        #     video = cv2.VideoWriter("./Save/RecordFile/YouTubeRecord " + str(nowTime) + ".avi", fourcc,
        #                             20.0, (frame.shape[1], frame.shape[0]))  # 20.0 : FPS (영상이 바뀌는 속도 의미, 화면의 부드러움 정도)
        # # 녹화 종료 --> Ctrl+R 키 입력
        # elif key == 18:  # Ctrl+R
        #     print("녹화 종료!")
        #     record = False
        #     video.release()  # 메모리 해제
        # # record 가 True 면, 화면 녹화
        # elif record is True:
        #     video.write(frame)  # 비디오를 '프레임'에 저장
        #     print("녹화 중..")

    capture.release()
    cv2.destroyAllWindows()  # 화면에 나타난 윈도우 종료
# Youtube영상출력 쓰레드
def YouTubeDisplay_Threading():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine
    global nowTime, url

    thread_Youtube = threading.Thread(target=YouTubeDisplay(), daemon=True)
    thread_Youtube.start()
    thread_Youtube.join()


# *************************** < 메인 함수 > ***************************
window = Tk()
window.title(" GrayScale Image Processing Ver2.6 ")
window.geometry('500x500')

# 상태바 생성
stateBar = Label(window, text='이미지 정보', bd=1, relief=SUNKEN, anchor=W)
stateBar.pack(side=BOTTOM, fill=X)

# 메인 메뉴
if __name__ == '__main__':
    thread_main = threading.Thread(target=mainThread(), args=())
    thread_main.daemon = True
    thread_main.start()
