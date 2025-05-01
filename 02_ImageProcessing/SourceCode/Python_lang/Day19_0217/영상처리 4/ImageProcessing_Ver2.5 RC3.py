# Image Processing_Ver2.5 RC3.py (Color Image Processing with OpenCV)
# Image Processing using python Ver 2.5 (include OpenCV)
# 3차원 Color Image Procsessing

# 칼라, OpenCV, 상태바, 마우스 이벤트, 박스라인


import math
import os.path
import threading
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import cv2
import numpy as np
import matplotlib.pyplot as plt

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
sx, sy, ex, ey = [-1] * 4       # start x, start y, end x, end y        # -1 로 초기화 ==> 0을 값으로 가지고 있을수도 있기 때문


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
    fileMenu.add_command
    fileMenu.add_separator()
    fileMenu.add_command(label='종료')

    functionMenu()          # 영상처리 기능 메뉴
    CVfunctionMenu()        # OpenCV 영상처리 기능 메뉴

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
    pxAreaMenu.add_cascade(label='3. 샤프닝', menu=Sharpning)
    Sharpning.add_command(label='샤프닝', command=lambda: sharpningImage(1))
    Sharpning.add_command(label='HPF 처리 샤프닝', command=lambda: sharpningImage(2))
    Sharpning.add_command(label='LPF 처리 샤프닝', command=lambda: sharpningImage(3))
    pxAreaMenu.add_command(label='4. 스무딩 (가우시안)', command=smoothing)

    # 4. 엣지 검출 처리
    edgeDetectMenu = Menu(funcMenu)  # 상위 메뉴 (파일)

    funcMenu.add_cascade(label='4. 엣지 검출 처리', menu=edgeDetectMenu)
    edgeDetectMenu.add_command(label='1. 수직 엣지', command=lambda: shiftDifferEdgeImage(1))
    edgeDetectMenu.add_command(label='2. 수평 엣지', command=lambda: shiftDifferEdgeImage(2))
    edgeDetectMenu.add_command(label='3. 수직 수평 엣지', command=lambda: shiftDifferEdgeImage(3))

    # 5. 기하학 처리
    geometryMenu = Menu(funcMenu)  # 상위 메뉴 (파일)
    mirroring = Menu(geometryMenu)  # 미러링
    Turn = Menu(geometryMenu)  # 회전
    turnRight = Menu(Turn)  # 시계 방향 회전
    turnLeft = Menu(Turn)  # 반시계 방향 회전
    Turn_Free = Menu(Turn)  # 자유 회전
    size = Menu(geometryMenu)  # 이미지 사이즈

    funcMenu.add_cascade(label='5. 기하학 처리', menu=geometryMenu)
    geometryMenu.add_cascade(label='1. 미러링', menu=mirroring)
    mirroring.add_command(label='좌우 미러링', command=lambda: mirroringImage(1))
    mirroring.add_command(label='상하 미러링', command=lambda: mirroringImage(2))
    mirroring.add_command(label='상하+좌우 미러링', command=lambda: mirroringImage(3))
    geometryMenu.add_cascade(label='2. 회전', menu=Turn)
    Turn.add_cascade(label='1. 시계 방향', menu=turnRight)
    turnRight.add_command(label='90도', command=lambda: turnRightImage(1))
    turnRight.add_command(label='180도', command=lambda: turnRightImage(2))
    turnRight.add_command(label='270도', command=lambda: turnRightImage(3))
    Turn.add_cascade(label='2. 반시계 방향', menu=turnLeft)
    turnLeft.add_command(label='90도', command=lambda: turnLeftImage(1))
    turnLeft.add_command(label='180도', command=lambda: turnLeftImage(2))
    turnLeft.add_command(label='270도', command=lambda: turnLeftImage(3))
    Turn.add_cascade(label='3. 자유 회전 (입력)', menu=Turn_Free)
    # turn_Free.add_command(label='자유 회전', command=turnFree)
    # turn_Free.add_command(label='자유 회전 (백워딩 + 중앙)', command=turnFreeCenter)
    geometryMenu.add_cascade(label='3. 확대/축소', menu=size)
    # size.add_command(label='이미지 크기 확대 (포워딩)', command=sizeUp)
    # size.add_command(label='이미지 크기 확대 (백워딩)', command=backwardMappingSizeUp)
    # size.add_command(label='이미지 크기 축소 (포워딩)', command=sizeDown)
    # size.add_command(label='이미지 크기 축소 (백워딩)', command=backwardMappingSizeDown)
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
    CVBITCalc.add_command(label='AND 연산_CV (입력)', command=lambda: cvBitCalc(1))
    CVBITCalc.add_command(label='OR 연산_CV (입력)', command=lambda: cvBitCalc(2))
    CVBITCalc.add_command(label='XOR 연산_CV (입력)', command=lambda: cvBitCalc(3))
    CVBITCalc.add_command(label='NOT 연산_CV', command=lambda: cvBitCalc(4))
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

    # 3. 화소 영역 처리
    CVpxAreaMenu = Menu(openCVfuncMenu)  # 상위 메뉴 (파일)
    CVblurring = Menu(CVpxAreaMenu)  # 블러링
    CVSharpening = Menu(CVpxAreaMenu)  # 샤프닝

    openCVfuncMenu.add_cascade(label='3. 화소 영역 처리_CV', menu=CVpxAreaMenu)
    CVpxAreaMenu.add_command(label='1. 엠보싱_CV', command=cvEmbossing)
    CVpxAreaMenu.add_cascade(label='2. 블러링_CV', menu=CVblurring)
    CVblurring.add_command(label='3x3 블러링_CV', command=lambda: cvBlurring(1))
    CVblurring.add_command(label='5x5 블러링_CV', command=lambda: cvBlurring(2))
    CVpxAreaMenu.add_cascade(label='3. 샤프닝_CV', menu=CVSharpening)
    CVSharpening.add_command(label='샤프닝_CV', command=lambda: cvSharpeningImage(1))
    CVSharpening.add_command(label='HPF 처리 샤프닝_CV', command=lambda: cvSharpeningImage(2))
    CVSharpening.add_command(label='LPF 처리 샤프닝_CV', command=lambda: cvSharpeningImage(3))
    # CVpxAreaMenu.add_command(label='4. 스무딩 (가우시안)_CV', command=cvSmoothing)

    openCVfuncMenu.add_command(label='HSV 변환_CV', command=cvHSVImage)
    openCVfuncMenu.add_command(label='색상 추출_CV', command=cvMyColorImage)


# *************************** < 이미지 입출력 함수 정의부 > ***************************
# 2차원 배열 생성 함수 (동적 할당)
def malloc3D(h, w, t, initValue=0):  # 디폴트 매개변수
    retMemory = [[[initValue for _ in range(w)] for _ in range(h)] for _ in range(t)]  # 파이썬에서만 가능한 문법
    return retMemory
# 이미지 파일 열기 (입력)
def openImage():
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    filename = askopenfilename(parent=window,
                               filetypes=(("Color 파일", "*.jpg; *.png; *.bmp; *.tif"), ("모든 파일", "*.*")))

    # 중요! 입력 영상의 크기 파악
    inPhoto = cv2.imread(filename)      # 이미지 파일 불러오기
    inH = inPhoto.shape[0]
    inW = inPhoto.shape[1]

    # 메모리 할당
    inImage = malloc3D(inH, inW, RGB)

    # OpenCV 개체 --> 메모리
    for i in range(inH):
        for k in range(inW):
            inImage[RR][i][k] = inPhoto.item(i, k, BB)      # 컴퓨터에 입력되는건 R,G,B 순서가 아닌 B,G,R 순서
            inImage[GG][i][k] = inPhoto.item(i, k, GG)
            inImage[BB][i][k] = inPhoto.item(i, k, RR)

    equalImage()
# 이미지 파일 저장
def saveImage():
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
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
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if canvas is not None:  # if (canvas != NULL)
        canvas.destroy()

    window.geometry(str(int(outW * 1.2)) + 'x' + str(int(outH * 1.2)))

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


# 마우스 좌클릭
def leftMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine  # start x, start y, end x, end y

    if boxLine is not None:  # 드래그 할 때, 이미 박스라인이 있는 상황에 좌클릭 누르면
        canvas.delete(boxLine)  # 박스라인 삭제

    sx = event.x
    sy = event.y
# 마우스 우클릭
def rightMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if boxLine is not None:  # 드래그 할 때, 이미 박스라인이 있는 상황에 우클릭 누르면
        canvas.delete(boxLine)  # 박스라인 삭제
    sx, sy, ex, ey = [-1] * 4  # 초기화           # 0이 들어올 수도 있기 때문에 -1로 초기화
# 마우스 드래그
def moveMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    ex = event.x
    ey = event.y

    if boxLine is not None:
        canvas.delete(boxLine)
    boxLine = canvas.create_rectangle(sx, sy, ex, ey, width=1)
def dropMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if boxLine is not None:
        canvas.delete(boxLine)

    ex = event.x
    ey = event.y

    if sx > ex:     # 만약, 드래그 시작점이 끝점보다 더 x축에서 멀다면
        sx, ex = ex, sx     # 시작점과 끝점의 값을 교환함
    if sy > ey:     # 만약, 드래그 시작점이 끝점보다 더 y축에서 멀다면
        sy, ey = ey, sy     # 시작점과 끝점의 값을 교환함
    boxLine = canvas.create_rectangle(sx, sy, ex, ey, width=1, fill='blue', stipple="gray25")


# 전역 변수, 영상 크기 설정, 메모리 할당, 예외 처리
def startFunc():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto        # src, dst
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc3D(outH, outW, RGB)

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다.")
        return


# # 전역 변수, 예외 처리
# def startCVFunc():
#     # 전역 변수
#     global inImage, outImage, inH, inW, outH, outW
#     global inPhoto, outPhoto
#     global window, canvas, paper, stateBar, filename
#     global sx, sy, ex, ey, boxLine
#
#     if not inPhoto:
#         messagebox.showinfo("경고!", "로드된 이미지가 없습니다.111")
#         return

print("")
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
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
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

    ## ***** 영상처리 알고리즘 ***** ##
    if clear == 1:
        clearUp()
    elif clear == 2:
        clearDown()
    # ************************************************** #
    printImage()

# 선명도 조절 (선명하게)
def clearUp():
    value = 0.0
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
def clearDown():
    value = 0.0
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


# 1-5.흑백 처리 (128/평균값/입력 범위/GrayScale 기준)
def BWImage(bw):
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    if bw == 1:
        BWImageGrayScale()
    elif bw == 2:
        BWImage128()
    elif bw == 3:
        BWImageAvg()
    elif bw == 4:
        BWImageRange()
    # ************************************************** #
    printImage()

# 흑백 처리 (Gray Scale)
def BWImageGrayScale():
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
def BWImage128():
    print("흑백 처리 (128 기준) 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
                if sx == -1:
                    if inImage[rgb][i][k] > 127:
                        pxR, pxG, pxB = 255, 255, 255
                    else:
                        pxR, pxG, pxB = 0, 0, 0
                    outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        if inImage[rgb][i][k] > 127:
                            pxR, pxG, pxB = 255, 255, 255
                        else:
                            pxR, pxG, pxB = 0, 0, 0

                        outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
# 흑백 처리 (평균값 기준)
def BWImageAvg():
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
                pxR, pxG, pxB = inImage[RR][i][k], inImage[GG][i][k], inImage[BB][i][k]
                if sx == -1:
                    if inImage[rgb][i][k] > pixAvg:
                        pxR, pxG, pxB = 255, 255, 255
                    else:
                        pxR, pxG, pxB = 0, 0, 0
                    outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        if inImage[rgb][i][k] > pixAvg:
                            pxR, pxG, pxB = 255, 255, 255
                        else:
                            pxR, pxG, pxB = 0, 0, 0
                        outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
# 흑백 처리 (2입력 범위 기준)
def BWImageRange():
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
                        pxR, pxG, pxB = 0, 0, 0
                    elif pxR > value2 or pxG > value2 or pxB > value2:
                        pxR, pxG, pxB = 255, 255, 255
                    else:
                        outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB

                    outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        if pxR <= value1 or pxG <= value1 or pxB <= value1:
                            pxR, pxG, pxB = 0, 0, 0
                        elif pxR > value2 or pxG > value2 or pxB > value2:
                            pxR, pxG, pxB = 255, 255, 255
                        else:
                            outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB

                        outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k] = pxR, pxG, pxB
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]


# 1-6.비트 연산 (AND/OR/XOR/NOT)
def BitCalc(bit):
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    if bit == 1:
        BitCalcAnd()
    elif bit == 2:
        BitCalcOr()
    elif bit == 3:
        BitCalcXor()
    elif bit == 4:
        BitCalcNot()
    # ************************************************** #
    printImage()

# 비트연산_AND (입력)
def BitCalcAnd():
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
def BitCalcOr():
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
def BitCalcXor():
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
def BitCalcNot():
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


# 1-7.감마 변환 이미지 (입력)
def gammaImage():
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0.0
    value = askfloat("감마 변환 처리", "감마 변환 값 입력 : ", minvalue=0, maxvalue=255)

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

    ## ***** 영상처리 알고리즘 ***** ##
    if para == 1:
        parabolaCAP()
    elif para == 2:
        parabolaCUP()
    # ************************************************** #
    printImage()

# 파라볼라 CAP 변환
def parabolaCAP():
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
def parabolaCUP():
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
    Yy = 0
    Uu = 1
    Vv = 2

    yuvImage = []
    yuvImage = malloc3D(outH, outW, RGB)
    for i in range(inH):
        for k in range(inW):
            yuvImage[Yy][i][k] = inImage[RR][i][k] * 0.299 + inImage[GG][i][k] * 0.587 + inImage[BB][i][k] * 0.114
            yuvImage[Uu][i][k] = inImage[RR][i][k] * -0.169 + inImage[GG][i][k] * -0.331 + inImage[BB][i][
                k] * 0.500 + 128
            yuvImage[Vv][i][k] = inImage[RR][i][k] * 0.500 + inImage[GG][i][k] * -0.419 + inImage[BB][i][
                k] * -0.081 + 128

    histo = [0 for _ in range(256)]
    sumHisto = [0 for _ in range(256)]
    for i in range(inH):
        for k in range(inW):
            histo[int(yuvImage[Yy][i][k])] += 1

    # 2단계 : 누적 히스토그램 생성 (누적합 생성)
    sumHisto[0] = histo[0]
    for i in range(1, 256, 1):
        sumHisto[i] += sumHisto[i - 1] + histo[i]

    # 3단계 : 정규화된 누적 히스토그램 생성 (정규화된 누적합 생성)
    # n = sum * (1/(inH*inW)) * 255.0
    for i in range(256):
        sumHisto[i] = int(sumHisto[i] * (1/(inH * inW)) * 255.0)

    # 4단계 : 원래 값을 정규화 값으로 치환
    for i in range(inH):
        for k in range(inW):
            if sx == -1:
                tmpY = int(sumHisto[int(yuvImage[Yy][i][k])])

                outImage[RR][i][k] = int(tmpY + 1.4075 * (yuvImage[Vv][i][k] - 128))
                outImage[GG][i][k] = int(tmpY - 0.3455 * (yuvImage[Uu][i][k] - 128) - 0.7469 * (yuvImage[Vv][i][k] - 128))
                outImage[BB][i][k] = int(tmpY + 1.7790 * (yuvImage[Uu][i][k] - 128))
            else:
                if sx <= k <= ex and sy <= i < ey:
                    tmpY = int(sumHisto[int(yuvImage[Yy][i][k])])

                    outImage[RR][i][k] = int(tmpY + 1.4075 * (yuvImage[Vv][i][k] - 128))
                    outImage[GG][i][k] = int(
                        tmpY - 0.3455 * (yuvImage[Uu][i][k] - 128) - 0.7469 * (yuvImage[Vv][i][k] - 128))
                    outImage[BB][i][k] = int(tmpY + 1.7790 * (yuvImage[Uu][i][k] - 128))
                else:
                    for rgb in range(RGB):
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

    ## ***** 영상처리 알고리즘 ***** ##
    if blurr == 1:
        blurring33()
    elif blurr == 2:
        blurring55()
    # ************************************************** #
    printImage()

# 3x3 블러링
def blurring33():
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
# 5x5 블러링
def blurring55():
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


# 3-3.샤프닝 (샤프닝, HPF 처리, LPF 처리)
def sharpningImage(sharp):
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    if sharp == 1:
        sharpning()
    elif sharp == 2:
        HPFSharp()
    elif sharp == 3:
        LPFSharp()
    # ************************************************** #
    printImage()

# 샤프닝
def sharpning():
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
# 고주파 필터 처리 샤프닝
def HPFSharp():
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
                tmpOut[rgb][i][k] = S * 8  # x8 : 효과 진해짐

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
# 저주파 필터 처리 샤프닝
def LPFSharp():
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


# 3-4.스무딩 (가우시안)
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


# *************************** < 4. 엣지 검출 처리 기능 함수 정의부 > ***************************
# 4-1.이동과 차분 엣지 검출 (수직, 수평, 수직수평)
# 화소의 위치를 위/아래/왼/오른쪽으로 하나씩 이동 -> 원래 화소 값 - 이동위치 화소 값
# 엣지 검출기는 대부분 이 방법 응용
# Shift & Difference
def shiftDifferEdgeImage(edge):
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    if edge == 1:
        horizontalEdge()
    elif edge == 2:
        verticalEdge()
    elif edge == 3:
        horiVertiEdge()
    # ************************************************** #
    printImage()

# 수직 엣지
def horizontalEdge():
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
def verticalEdge():
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
def horiVertiEdge():
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


# *************************** < 5. 기하학 처리 기능 함수 정의부 > ***************************
# 5-1.미러링 (좌우/상하/상하+좌우)
def mirroringImage(mirror):
    startFunc()

    ## ***** 영상처리 알고리즘 ***** ##
    if mirror == 1:
        LR_Mirroring()
    elif mirror == 2:
        TB_Mirroring()
    elif mirror == 3:
        TB_LR_Mirroring()
    # ************************************************** #
    printImage()

# 좌우 미러링
def LR_Mirroring():
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
def TB_Mirroring():
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
def TB_LR_Mirroring():
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


# 5-2.회전 (오른쪽 90/180/270)
def turnRightImage(turn):
    ## ***** 영상처리 알고리즘 ***** ##
    if turn == 1:
        turn90Right()
    elif turn == 2:
        turn180Right()
    elif turn == 3:
        turn270Right()
    # ************************************************** #
    printImage()

# 오른쪽 90도 회전
def turn90Right():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

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
                px = inImage[rgb][inH - k - 1][i]

                outImage[rgb][i][k] = px
# 오른쪽 180도 회전
def turn180Right():
    startFunc()

    print("시계방향 180도 회전 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                px = inImage[rgb][inH - i - 1][inW - k - 1]

                outImage[rgb][i][k] = px
# 오른쪽 270도 회전
def turn270Right():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

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
                px = inImage[rgb][k][inW - i - 1]

                outImage[rgb][i][k] = px


# 회전 (왼쪽 90/180/270)
def turnLeftImage(turn):
    ## ***** 영상처리 알고리즘 ***** ##
    if turn == 1:
        turn90Left()
    elif turn == 2:
        turn180Left()
    elif turn == 3:
        turn270Left()
    # ************************************************** #
    printImage()

# 왼쪽 90도 회전
def turn90Left():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

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
                px = inImage[rgb][k][inW - i - 1]

                outImage[rgb][i][k] = px
# 왼쪽 180도 회전
def turn180Left():
    startFunc()

    print("반시계방향 180도 회전 이미지")

    ## ***** 영상처리 알고리즘 ***** ##
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                px = inImage[rgb][inH - i - 1][inW - k - 1]

                outImage[rgb][i][k] = px
# 왼쪽 270도 회전
def turn270Left():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

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
                px = inImage[rgb][inH - k - 1][i]

                outImage[rgb][i][k] = px



# *************************** < OpenCV 전용 메뉴 > ***************************
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
    if outPhoto.ndim > 2:       # ndim : 넘파이 차원수 확인
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
                    # 박스라인 이외의 영역은 원본 이미지 그대로
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
    outPhoto = inPhoto.copy()
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


# 1-3.밝기 조절 이미지 (입력)
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


# 1-4.선명도(1.선명하게 2.흐릿하게) 조절 이미지 (입력)
def cvClearControlImage(clear):
    ## ***** 영상처리 알고리즘 ***** ##
    if clear == 1:
        cvClearUp()
    elif clear == 2:
        cvClearDown()
    # ************************************************** #
    cv2outImage()
    printImage()

# 선명도 조절 (선명하게)
def cvClearUp():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0.0
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
# 선명도 조절 (흐릿하게)
def cvClearDown():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0.0
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


# 1-5.흑백 처리 (128/평균값/입력 범위/GrayScale 기준)
def cvBWImage(bw):
    ## ***** 영상처리 알고리즘 ***** ##
    if bw == 1:
        cvBWImageGrayScale()
    elif bw == 2:
        cvBWImage128()
    elif bw == 3:
        cvBWImageAvg()
    elif bw == 4:
        cvCartoonImage()
    elif bw == 5:
        cvBWImageRange()
    # ************************************************** #
    cv2outImage()
    printImage()

# 흑백 처리 (Gray Scale)
def cvBWImageGrayScale():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

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
# 흑백 처리 (128 기준)
def cvBWImage128():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

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
# 흑백 처리 (평균값 기준)
def cvBWImageAvg():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    print("[OpenCV] 흑백 처리 (평균값 기준) 이미지")

    ### openCV용 함수 활용 ###
    grayPhoto = None
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
# 카툰이미지_OpenCV
def cvCartoonImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    print("[OpenCV] 카툰 이미지")

    ### openCV용 함수 활용 ###
    outPhoto = cv2.cvtColor(inPhoto, cv2.COLOR_RGB2GRAY)
    outPhoto = cv2.medianBlur(outPhoto, 7)
    edges = cv2.Laplacian(outPhoto, cv2.CV_8U, ksize=5)
    ret, mask = cv2.threshold(edges, 100, 255, cv2.THRESH_BINARY_INV)

    outPhoto = cv2.cvtColor(mask, cv2.COLOR_GRAY2RGB)
# 흑백 처리 (2입력 범위 기준)
def cvBWImageRange():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

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


# 1-6.비트 연산 (AND/OR/XOR/NOT)
def cvBitCalc(bit):
    ## ***** 영상처리 알고리즘 ***** ##
    if bit == 1:
        cvBitCalcAnd()
    elif bit == 2:
        cvBitCalcOr()
    elif bit == 3:
        cvBitCalcXor()
    elif bit == 4:
        cvBitCalcNot()
    # ************************************************** #
    cv2outImage()
    printImage()

# 비트연산_AND (입력)
def cvBitCalcAnd():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0
    value = askinteger("비트 연산_AND", "비트 연산할 값", minvalue=0, maxvalue=255)

    print("[OpenCV] AND 비트 연산 화면, 연산값 : %d" % value)

    ### openCV용 함수 활용 ###
    #openAnotherImg()
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
# 비트연산_OR (입력)
def cvBitCalcOr():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

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
# 비트연산_XOR (입력)
def cvBitCalcXor():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

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
# 비트연산_NOT (입력)
def cvBitCalcNot():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    if not inImage:
        messagebox.showinfo("경고!", "로드된 이미지가 없습니다. ")
        return

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


# 1-7.감마 변환 이미지 (입력)
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
    #outPhoto = int(inPhoto ** (1 / gammaValue) * 255.0)
    # outPhoto = inPhoto.astype(np.float)
    # outPhoto = int(((outPhoto / 255.0) ** (1.0 / gammaValue)) * 255.0)
    #outPhoto = outPhoto.astype(np.float)
    #outPhoto = pow(inPhoto / 255.0, (1.0 / gammaValue) * 255.0)
    gamma_cvt = np.zeros((256, 1), dtype='uint8')

    for i in range(256):
        gamma_cvt[i][0] = 255 * (float(i)/255) ** (1.0/gammaValue)

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


# 1-8.범위 강조 이미지 (2입력)
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


# 2-1.히스토그램 스트레칭
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


# 2-2.히스토그램 엔드-인 탐색
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


# 2-3.히스토그램 평활화
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

    print("[OpenCV] 엠보싱 이미지")

    ### openCV용 함수 활용 ###
    # 3x3마스크 생성
    Emask = np.zeros((3, 3), np.float32)
    Emask[0][0] = -1.0
    Emask[2][2] = 1.0
    print(Emask)

    outPhoto = cv2.filter2D(inPhoto, -1, Emask)
    outPhoto += 127         # 각 화소에 127을 더해줌
    ########################
    cv2outImage()
    printImage()


# 3-2.블러링 (3x3 블러링, 5x5 블러링)
def cvBlurring(blurr):
    ## ***** 영상처리 알고리즘 ***** ##
    if blurr == 1:
        cvBlurring33()
    elif blurr == 2:
        cvBlurring55()
    # ************************************************** #
    cv2outImage()
    printImage()

# 3x3 블러링
def cvBlurring33():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    print("[OpenCV] 3x3 블러링 이미지")

    ### openCV용 함수 활용 ###
    # 3x3마스크 생성
    B3mask = np.zeros((3, 3), np.float32)
    B3mask[:3][:3] = 1. / 9
    print(B3mask)

    outPhoto = cv2.filter2D(inPhoto, -1, B3mask)

    # # 후처리 (마스크의 합이 0이 아니면 주석 처리)
    # outPhoto += 127       # 각 화소에 127을 더해줌
# 5x5 블러링
def cvBlurring55():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    print("[OpenCV] 5x5 블러링 이미지")

    ### openCV용 함수 활용 ###
    # 5x5마스크 생성
    B5mask = np.zeros((5, 5), np.float32)
    B5mask[:5][:5] = 1. / 25
    print(B5mask)

    outPhoto = cv2.filter2D(inPhoto, -1, B5mask)

    # # 후처리 (마스크의 합이 0이 아니면 주석 처리)
    # outPhoto += 127       # 각 화소에 127을 더해줌


# 3-3.샤프닝
def cvSharpeningImage(sharp):
    ## ***** 영상처리 알고리즘 ***** ##
    if sharp == 1:
        cvSharpening()
    elif sharp == 2:
        cvHPF_sharp()
    elif sharp == 3:
        cvLPF_sharp()
    # ************************************************** #
    cv2outImage()
    printImage()

# 샤프닝
def cvSharpening():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

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
# 고주파필터 처리 샤프닝
def cvHPF_sharp():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    print("[OpenCV] 고주파필터 처리 샤프닝 이미지")

    ### openCV용 함수 활용 ###
    # 3x3마스크 생성
    HPFmask = np.zeros((3, 3), np.float32)
    HPFmask[:3][:3] = -1. / 9
    HPFmask[1][1] = 8. / 9
    print(HPFmask)

    outPhoto = cv2.filter2D(inPhoto, -1, HPFmask)

    # 후처리 (마스크의 합이 0이 아니면 주석 처리)
    outPhoto += 127       # 각 화소에 127을 더해줌
# 저주파필터 처리 샤프닝
def cvLPF_sharp():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

    print("[OpenCV] 저주파필터 처리 샤프닝 이미지")

    ### openCV용 함수 활용 ###
    # 3x3마스크 생성
    LPFmask = np.zeros((3, 3), np.float32)
    LPFmask[0][0], LPFmask[0][2], LPFmask[2][0], LPFmask[2][2] = [1. / 16] * 4
    LPFmask[0][1], LPFmask[1][0], LPFmask[1][2], LPFmask[2][1] = [2. / 16] * 4
    LPFmask[1][1] = 4. / 16
    print(LPFmask)

    outPhoto = cv2.filter2D(inPhoto, -1, LPFmask)

    # 후처리 (마스크의 합이 0이 아니면 주석 처리)
    #outPhoto += 127  # 각 화소에 127을 더해줌


# HSV 변환_OpenCV
def cvHSVImage():
    # 전역 변수
    global inImage, outImage, inH, inW, outH, outW
    global inPhoto, outPhoto
    global window, canvas, paper, stateBar, filename
    global sx, sy, ex, ey, boxLine

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


# *************************** < 메인 함수 > ***************************
window = Tk()
window.title(" GrayScale Image Processing Ver2.5 RC 3 ")
window.geometry('500x500')

# 상태바 생성
stateBar = Label(window, text='이미지 정보', bd=1, relief=SUNKEN, anchor=W)
stateBar.pack(side=BOTTOM, fill=X)

# 메인 메뉴
if __name__ == '__main__':
    thread_main = threading.Thread(target=mainThread(), args=())
    thread_main.daemon = True
    thread_main.start()

