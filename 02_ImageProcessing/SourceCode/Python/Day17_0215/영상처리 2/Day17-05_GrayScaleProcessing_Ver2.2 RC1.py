# Day17-05_GrayScaleProcessing Ver2.2 RC1.py (Grayscale Image Processing)
# GrayScale Image Processing using Python (Ver2.2)

import math
import os.path
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *

# 전역 변수부 ================================================================================
m_inImage, m_outImage = [], []  # unsigned char ** m_inImage, ** m_outImage
m_inH, m_inW, m_outH, m_outW = [0] * 4  # 초기화       ... 이게 돼..?
window, canvas, paper = None, None, None  # 초기화


# 함수 정의부 ================================================================================
def malloc2D(h, w, initValue=0):  # 디폴트 파라미터
    retMemory = [[initValue for _ in range(w)] for _ in range(h)]
    return retMemory


def OnOpenDocument():
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper

    filename = askopenfilename(parent=window,
                               filetypes=(("RAW 파일", "*.raw"), ("모든 파일", "*.*")))

    # 중요! 입력 영상의 크기 파악
    fSize = os.path.getsize(filename)  # 파일 크기 (Byte)
    m_inH = m_inW = int(math.sqrt(fSize))  # 256x256

    # 메모리 할당
    m_inImage = malloc2D(m_inH, m_inW)

    rfp = open(filename, 'rb')
    for i in range(m_inH):
        for k in range(m_inW):
            m_inImage[i][k] = ord(rfp.read(1))
    rfp.close()
    OnEqualImage()


def OnDraw():
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper

    if canvas is not None:  # 캔버스에 전에 업로드 된 영상이 있는지 확인
        canvas.destroy()

    window.geometry(str(m_outH) + 'x' + str(m_outW))

    # 캔버스 + 페이퍼
    canvas = Canvas(window, height=m_outH, width=m_outW)  # 칠판 준비
    paper = PhotoImage(height=m_outH, width=m_outW)  # 작성할 종이 준비
    canvas.create_image((m_outH / 2, m_outW / 2), image=paper, state='normal')

    # 메모리 --> 화면
    """
    for i in range(m_outH):
        for k in range(m_outW):
            r = g = b = m_outImage[i][k]
            paper.put("#%02x%02x%02x" % (r, g, b), (k, i))
    """
    # C언어의 더블버퍼링을 응용한 기법
    rgbString = ""
    for i in range(m_outH):
        tmpString = ""
        for k in range(m_outW):
            r = g = b = m_outImage[i][k]
            tmpString += "#%02x%02x%02x " % (r, g, b)   # 제일 뒤에 공백
        rgbString += '{' + tmpString + '} '             # 제일 뒤에 공백
    paper.put(rgbString)

    canvas.pack()  # 화면에 출력


### 영상처리 함수 모음 ###
def OnEqualImage():
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    m_outH = m_inH
    m_outW = m_inW

    # 메모리 할당
    m_outImage = malloc2D(m_outH, m_outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(m_inH):
        for k in range(m_inW):
            m_outImage[i][k] = m_inImage[i][k]
    ################################################
    OnDraw()


def OnReverseImage():
    global m_inImage, m_outImage, m_inH, m_inW, m_outH, m_outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    m_outH = m_inH
    m_outW = m_inW

    # 메모리 할당
    m_outImage = malloc2D(m_outH, m_outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(m_inH):
        for k in range(m_inW):
            m_outImage[i][k] = 255 - m_inImage[i][k]
    ################################################
    OnDraw()



# 메인 함수부 ================================================================================
window = Tk()
window.title(" GrayScale Image Processing Ver2.2 RC1 ")
window.geometry('500x500')

# 메뉴 틀
mainMenu = Menu(window)  # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=OnOpenDocument)  # add_command : 누르면 실행
fileMenu.add_command(label='저장')
fileMenu.add_separator()
fileMenu.add_command(label='종료')

image1Menu = Menu(mainMenu)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label='화소점 처리', menu=image1Menu)
image1Menu.add_command(label='동일 영상', command=OnEqualImage)
image1Menu.add_command(label='반전 영상', command=OnReverseImage)

window.mainloop()


