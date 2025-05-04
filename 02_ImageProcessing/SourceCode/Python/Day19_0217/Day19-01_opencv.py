##  Image Processing using Python (Ver 2.3)
# OpenCV용 OpenDocument/SaveDocument

import math
import os.path
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import cv2
import numpy as np

## 함수부
def malloc3D(h,w,t,initValue=0) :
    memory = [[[initValue for _ in range(w)] for _ in range(h)] for _ in range(t)]
    return memory

def  OnOpenDocument() :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global m_inPhoto, m_outPhoto
    global window, canvas, paper, filename
    filename = askopenfilename(parent=window,
            filetypes=(("Color 파일", "*.jpg;*.png;*.bmp;*.tif"), ("모든파일", "*.*")))
    # 중요! 입력 영상의 크기를 파악
    m_inPhoto = cv2.imread(filename)
    m_inH = m_inPhoto.shape[0]
    m_inW = m_inPhoto.shape[1]

    # 메모리 할당
    m_inImage = malloc3D(m_inH, m_inW, RGB)

    # openCV 개체 --> 메모리
    for i in range(m_inH):
        for k in range(m_inW):
            m_inImage[RR][i][k] = m_inPhoto.item(i, k, BB)
            m_inImage[GG][i][k] = m_inPhoto.item(i, k, GG)
            m_inImage[BB][i][k] = m_inPhoto.item(i, k, RR)

    OnEqualImage()


def OnSaveDocument() :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global m_inPhoto, m_outPhoto
    global window, canvas, paper

    if m_outImage == None or len(m_outImage) == 0 : # 영상처리를 한적이 없다면
        return
    saveFp = asksaveasfile(parent=window, mode='wb', defaultextension="*.raw",
                          filetypes=(("PNG 파일", "*.png"), ("All Files", "*.*")))

    # 빈 OpenCV 개체 생성
    savePhoto = np.zeros((m_outH, m_outW, 3), np.uint8)

    for i in range(m_outH):
        for k in range(m_outW):
            tup = tuple((m_outImage[BB][i][k], m_outImage[GG][i][k], m_outImage[RR][i][k]))
            savePhoto[i][k] = tup

    cv2.imwrite(saveFp.name, savePhoto)
    messagebox.showinfo("성공", saveFp.name + " 저장됨")

def moveMouse(event) :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper, sbar, filename
    global  sx, sy, ex, ey, boxLine
    ex = event.x
    ey = event.y
    if boxLine != None :
        canvas.delete(boxLine)
    boxLine = canvas.create_rectangle (sx,sy,ex,ey, width=1)

def rightMouse(event) :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper, sbar, filename
    global  sx, sy, ex, ey, boxLine
    if boxLine != None :
        canvas.delete(boxLine)
    sx,sy,ex,ey=[-1] * 4

def leftMouse(event) :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper, sbar, filename
    global  sx, sy, ex, ey, boxLine
    if boxLine != None :
        canvas.delete(boxLine)
    sx = event.x
    sy = event.y

def dropMouse(event) :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper, sbar, filename
    global sx, sy, ex, ey, boxLine
    if boxLine != None :
        canvas.delete(boxLine)
    ex = event.x
    ey = event.y
    if sx > ex :
        sx, ex = ex, sx
    if sy > ey :
        sy, ey = ey, sy
    boxLine = canvas.create_rectangle (sx,sy,ex,ey, width=1)

def OnDraw() :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper, sbar, filename
    if canvas != None :
        canvas.destroy()

    window.geometry(str(int(m_outW*1.2)) + 'x' + str(int(m_outH*1.2)) )
    ## 캔버스/페이퍼 생성
    canvas = Canvas(window, height=m_outH, width=m_outW)
    canvas.bind("<Button-1>", leftMouse)
    canvas.bind("<B1-Motion>", moveMouse)
    canvas.bind("<Button-3>", rightMouse)
    canvas.bind("<ButtonRelease-1>", dropMouse)
    paper = PhotoImage(height=m_outH, width=m_outW)
    canvas.create_image((m_outW / 2, m_outH / 2), image=paper, state='normal')
    ## 메모리 --> 화면으로 찍기
    rgbString=""
    for i in range(m_outH):
        tmpString = ""
        for k in range(m_outW):
            r = m_outImage[RR][i][k]
            g = m_outImage[GG][i][k]
            b = m_outImage[BB][i][k]
            tmpString += "#%02x%02x%02x " % (r, g, b) # 제일 뒤에 공백
        rgbString += '{' + tmpString + '} ' # 제일 뒤에 공백
    paper.put(rgbString)
    canvas.pack(expand=1, anchor=CENTER)
    sbar.configure(text=str(m_outH)+'x'+str(m_outW)+'  '+filename)


### 영상처리 함수 모음 ###
def OnEqualImage() :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper
    # 중요! 출력영상의 크기를 결정 --> 알고리즘에 의존
    m_outH = m_inH
    m_outW = m_inW
    # 메모리 할당
    m_outImage = malloc3D(m_outH, m_outW, RGB)
    ## ** 진짜 영상처리 알고리즘 ** ##
    for rgb in range(RGB) :
        for i in range(m_inH) :
            for k in range(m_inW) :
                m_outImage[rgb][i][k] = m_inImage[rgb][i][k]
    #################################
    OnDraw()


def OnReverseImage() :
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper
    # 중요! 출력영상의 크기를 결정 --> 알고리즘에 의존
    m_outH = m_inH
    m_outW = m_inW
    # 메모리 할당
    m_outImage = malloc3D(m_outH, m_outW, RGB)
    ## ** 진짜 영상처리 알고리즘 ** ##
    for rgb in range(RGB) :
        for i in range(m_inH) :
            for k in range(m_inW) :
                if sx == -1 :
                    m_outImage[rgb][i][k] = 255 - m_inImage[rgb][i][k]
                else :
                    if (sx <= k < ex) and (sy <= i < ey) : #현재점이 네모박스안?
                        m_outImage[rgb][i][k] = 255 - m_inImage[rgb][i][k]
                    else :
                        m_outImage[rgb][i][k] = m_inImage[rgb][i][k]
    #################################
    OnDraw()

## 전역변수부
m_inImage, m_outImage = [], []  # unsinged char ** m_inImage, ** m_outImage
m_inH, m_inW, m_outH, m_outW = [0] * 4
m_inPhoto, m_outPhoto = None, None
window, canvas, paper = None, None, None
RGB = 3
RR, GG, BB = 0, 1, 2
sbar = None
filename=''
sx,sy,ex,ey=[-1] * 4
boxLine = None

## 메인코드부
window = Tk() # 벽
window.title("영상처리 Ver2.3")
window.geometry('500x500')

## 상태바 생성
sbar = Label(window, text='상태바', bd=1, relief=SUNKEN, anchor=W)
sbar.pack(side=BOTTOM, fill=X)

mainMenu = Menu(window) # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu) # 상위 메뉴(파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=OnOpenDocument)
fileMenu.add_command(label='저장', command=OnSaveDocument)
fileMenu.add_separator()
fileMenu.add_command(label='종료')

image1Menu = Menu(mainMenu) # 상위 메뉴(파일)
mainMenu.add_cascade(label='화소점처리', menu=image1Menu)
image1Menu.add_command(label='동일영상', command=OnEqualImage)
image1Menu.add_command(label='반전영상', command=OnReverseImage)

window.mainloop()