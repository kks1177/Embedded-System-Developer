# Day18-01_Image Processing_Ver2.3 RC1.py (Color Image Processing)
# Image Processing using python Ver 2.3 (without openCV, Library)
# 3차원 Color Image Procsessing

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


# *************************** < 이미지 입출력 함수 정의부 > ***************************
# 2차원 배열 생성 함수 (동적 할당)
def malloc3D(h, w, t, initValue=0):  # 디폴트 매개변수
    retMemory = [[[initValue for _ in range(w)] for _ in range(h)] for _ in range(t)]  # 파이썬에서만 가능한 문법
    return retMemory


# 이미지 파일 열기 (입력)
def openImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

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
    global window, canvas, paper

    if outImage is None or len(outImage) == 0:  # 영상처리를 한 적이 없다면..
        return
    saveFp = asksaveasfile(parent=window, mode='wb', defaultextension="*.raw",
                           filetypes=(("RAW 파일", "*.raw"), ("All Files", "*.*")))
    import struct

    for i in range(outH):
        for k in range(outW):
            saveFp.write(struct.pack('B', outImage[i][k]))
    saveFp.close()
    messagebox.showinfo("성공", saveFp.name + " 저장됨")


# 이미지 출력
def printImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    if canvas is not None:  # if (cavas != NULL)
        canvas.destroy()

    window.geometry(str(outW) + 'x' + str(outH))

    # 캔버스 + 페이퍼
    canvas = Canvas(window, height=outH, width=outW)  # 칠판 준비
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

    canvas.pack() # 화면에 출력


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
                px = inImage[rgb][i][k]

                outImage[rgb][i][k] = 255 - px
    # ************************************************** #
    printImage()


# *************************** < 메인 함수 > ***************************
window = Tk()
window.title(" GrayScale Image Processing Ver2.3 RC 1 ")
window.geometry('500x500')

# 메뉴 틀
mainMenu = Menu(window)
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
