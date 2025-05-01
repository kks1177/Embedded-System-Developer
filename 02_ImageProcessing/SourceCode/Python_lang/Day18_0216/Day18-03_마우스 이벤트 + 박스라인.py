# Day18-01_마우스 이벤트 2 + 박스라인.py
# Image Processing using python Ver 2.3 (without openCV, Library)
# 3차원 Color Image Procsessing

# 마우스 이벤트 + 범위만 변환

import math
import os.path
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
# import PIL
from PIL import Image, ImageFilter, ImageEnhance

# *************************** < 전역 변수부 > ***************************
inImage, outImage = [], []  # unsigned char** inImage, ** outImage
inH, inW, outH, outW = [0] * 4  # 초기화
window, canvas, paper = None, None, None  # 초기화
RGB = 3  # 전역 상수 선언
RR, GG, BB = 0, 1, 2
sbar = None  # 상태바
filename = ''
sx, sy, ex, ey = [-1] * 4
boxLine = None


# *************************** < 이미지 입출력 함수 정의부 > ***************************
# 2차원 배열 생성 함수 (동적 할당)
def malloc3D(h, w, t, initValue=0):  # 디폴트 매개변수
    retMemory = [[[initValue for _ in range(w)] for _ in range(h)] for _ in range(t)]  # 파이썬에서만 가능한 문법
    return retMemory


# 이미지 파일 열기 (입력)
def openImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, sbar, filename

    filename = askopenfilename(parent=window,
                               filetypes=(("Color 파일", "*.jpg; *.png; *.bmp; *.tif"), ("모든 파일", "*.*")))
    # 중요! 입력 영상의 크기 파악
    pillow = Image.open(filename)
    inH = pillow.height
    inW = pillow.width

    # 메모리 할당
    inImage = malloc3D(inH, inW, RGB)
    pillowRGB = pillow.convert('RGB')  # Red, Green, Blue

    for i in range(inH):
        for k in range(inW):
            r, g, b = pillowRGB.getpixel((k, i))
            inImage[RR][i][k] = r
            inImage[GG][i][k] = g
            inImage[BB][i][k] = b

    equalImage()


# 이미지 파일 저장
def saveImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, sbar, filename

    if outImage is None or len(outImage) == 0:  # 영상처리를 한 적이 없다면..
        return

    saveFp = asksaveasfile(parent=window, mode='wb', defaultextension="*.raw",
                           filetypes=(("PNG 파일", "*.png"), ("All Files", "*.*")))
    pillow = Image.new('RGB', (outW, outH))

    for i in range(outH):
        for k in range(outW):
            r, g, b = outImage[RR][i][k], outImage[GG][i][k], outImage[BB][i][k]
            pillow.putpixel((k, i), (r, g, b))

    pillow.save(saveFp.name)
    messagebox.showinfo("성공", saveFp.name + " 저장됨")


# 이미지 출력
def printImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, sbar, filename

    if canvas is not None:  # if (canvas != NULL)
        canvas.destroy()

    window.geometry(str(int(outW * 1.2)) + 'x' + str(int(outH * 1.2)))

    # 캔버스 + 페이퍼
    canvas = Canvas(window, height=outH, width=outW)
    canvas.bind("<Button-1>", leftMouse)
    canvas.bind("<B1-Motion>", moveMouse)
    canvas.bind("<Button-3>", rightMouse)
    canvas.bind("<ButtonRelease-1>", dropMouse)
    paper = PhotoImage(height=outH, width=outW)
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
    sbar.configure(text=str(outH) + 'x' + str(outW) + '  ' + filename)


# 마우스 좌클릭
def leftMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, sbar, filename
    global sx, sy, ex, ey, boxLine  # start x, start y, end x, end y

    if boxLine is not None:  # 드래그 할 때, 이미 박스라인이 있는 상황에 좌클릭 누르면
        canvas.delete(boxLine)  # 박스라인 삭제

    sx = event.x
    sy = event.y


# 마우스 우클릭
def rightMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, sbar, filename
    global sx, sy, ex, ey, boxLine

    if boxLine is not None:  # 드래그 할 때, 이미 박스라인이 있는 상황에 우클릭 누르면
        canvas.delete(boxLine)  # 박스라인 삭제
    sx, sy, ex, ey = [-1] * 4  # 초기화           # 0이 들어올 수도 있기 때문에 -1로 초기화


# 마우스 드래그
def moveMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, sbar, filename
    global sx, sy, ex, ey, boxLine

    ex = event.x
    ey = event.y

    if boxLine is not None:
        canvas.delete(boxLine)
    boxLine = canvas.create_rectangle(sx, sy, ex, ey, width=1)


def dropMouse(event):
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper, sbar, filename
    global sx, sy, ex, ey, boxLine

    if boxLine is not None:
        canvas.delete(boxLine)

    ex = event.x
    ey = event.y

    if sx > ex:  # 만약, 드래그 시작점이 끝점보다 더 x축에서 멀다면
        sx, ex = ex, sx  # 시작점과 끝점이
    if sy > ey:
        sy, ey = ey, sy
    boxLine = canvas.create_rectangle(sx, sy, ex, ey, width=1, fill='blue', stipple="gray25")


# *************************** < 1. 화소점 처리 기능 함수 정의부 > ***************************
# 동일 이미지
def equalImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc3D(outH, outW, RGB)

    ## ***** 영상처리 알고리즘 ***** ##
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                px = inImage[rgb][i][k]

                outImage[rgb][i][k] = px
    # ************************************************** #
    printImage()


# 반전 이미지
def reverseImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc3D(outH, outW, RGB)

    ## ***** 영상처리 알고리즘 ***** ##
    for rgb in range(RGB):
        for i in range(inH):
            for k in range(inW):
                if sx == -1:
                    px = 255 - inImage[rgb][i][k]
                    outImage[rgb][i][k] = px
                else:
                    if (sx <= k < ex) and (sy <= i < ey):  # 현재 점이 네모박스 안에 있나?    지정한 네모 박스 안
                        px = 255 - inImage[rgb][i][k]
                        outImage[rgb][i][k] = px
                    else:
                        outImage[rgb][i][k] = inImage[rgb][i][k]
    # ************************************************** #
    printImage()


# *************************** < 메인 함수 > ***************************
window = Tk()
window.title(" GrayScale Image Processing Ver2.3 RC 2 ")
window.geometry('500x500')

# 상태바 생성
sbar = Label(window, text='상태바', bd=1, relief=SUNKEN, anchor=W)
sbar.pack(side=BOTTOM, fill=X)

# 메뉴 틀
mainMenu = Menu(window)  # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=openImage)  # add_command : 누르면 실행
fileMenu.add_command(label='저장', command=saveImage)
fileMenu.add_separator()
fileMenu.add_command(label='종료')

# 전체 기능 메뉴
funcMenu = Menu(mainMenu)
mainMenu.add_cascade(label='영상 처리', menu=funcMenu)

# 1. 화소점 처리
pxDotMenu = Menu(funcMenu)

funcMenu.add_cascade(label='1. 화소점 처리', menu=pxDotMenu)

pxDotMenu.add_command(label='1. 동일 영상', command=equalImage)
pxDotMenu.add_command(label='2. 반전 영상', command=reverseImage)

window.mainloop()
