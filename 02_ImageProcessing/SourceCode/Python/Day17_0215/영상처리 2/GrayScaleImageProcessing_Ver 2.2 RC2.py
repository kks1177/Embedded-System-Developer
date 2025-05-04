# GrayScaleImageProcessing_Ver2.2 RC2.py

import math
import os.path
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *

# *************************** < 전역 변수부 > ***************************
inImage, outImage = [], []
inH, inW, outH, outW = [0] * 4  # 초기화
window, canvas, paper = None, None, None  # 초기화


# *************************** < 이미지 입출력 함수 정의부 > ***************************
# 2차원 배열 생성 함수 (동적 할당)
def malloc2D(h, w, initValue=0):  # 디폴트 매개변수
    retMemory = [[initValue for _ in range(w)] for _ in range(h)]
    return retMemory


# 이미지 파일 열기 (입력)
def openImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    filename = askopenfilename(parent=window,
                               filetypes=(("RAW 파일", "*.raw"), ("모든 파일", "*.*")))
    # 중요! 입력 영상의 크기 파악
    fSize = os.path.getsize(filename)  # 파일 크기(Byte)
    inH = inW = int(math.sqrt(fSize))

    # 메모리 할당
    inImage = malloc2D(inH, inW)

    rfp = open(filename, 'rb')
    for i in range(inH):
        for k in range(inW):
            inImage[i][k] = ord(rfp.read(1))
    rfp.close()
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

    window.geometry(str(outH) + 'x' + str(outW))

    # 캔버스 + 페이퍼
    canvas = Canvas(window, height=outH, width=outW)  # 칠판 준비
    paper = PhotoImage(height=outH, width=outW)  # 작성할 종이 준비
    canvas.create_image((outH / 2, outW / 2), image=paper, state='normal')

    # 메모리 --> 화면
    # C++의 더블 버퍼링을 응용한 기법
    rgbString = ""
    for i in range(outH):
        tmpString = ""
        for k in range(outW):
            r = g = b = outImage[i][k]
            tmpString += "#%02x%02x%02x " % (r, g, b)  # 제일 뒤에 공백
        rgbString += '{' + tmpString + '} '
    paper.put(rgbString)

    canvas.pack()  # 화면에 출력


# *************************** < 1. 화소점 처리 기능 함수 정의부 > ***************************
# 동일 이미지
def equalImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            outImage[i][k] = px
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
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            outImage[i][k] = 255 - px
    # ************************************************** #
    printImage()


# 밝기 조절 이미지 (입력)
def brightControlImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = askinteger("밝기 조절", "밝기 조절 값 입력 : ", minvalue=-255, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] + value

            if px > 255:
                px = 255
            elif px <= 0:
                px = 0
            else:
                outImage[i][k] = px

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 선명도(1.선명하게 2.흐릿하게) 조절 이미지 (입력)
def clearUp():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0.0
    value = askfloat("선명도(선명하게) 조절", "선명도 조절 값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            # if clear == 1:
            px = inImage[i][k] * value

            if px > 255:
                px = 255
            elif px <= 0:
                px = 0
            else:
                outImage[i][k] = int(px)

            outImage[i][k] = int(px)

        # elif clear == 2:
        #     px = inImage[i][k] / value
        #
        #     if px > 255:
        #         px = 255
        #     elif px <= 0:
        #         px = 0
        #     else:
        #         outImage[i][k] = px
        #     outImage[i][k] = px
    # ************************************************** #
    printImage()


# 선명도(흐릿하게) 조절 이미지 (입력)
def clearDown():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0.0
    value = askfloat("선명도(흐릿하게) 조절", "선명도 조절 값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] / value

            if px > 255:
                px = 255
            elif px <= 0:
                px = 0
            else:
                outImage[i][k] = int(px)

            outImage[i][k] = int(px)
    # ************************************************** #
    printImage()


# 흑백 처리 (127 기준)
def BWImage127():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            if px > 127:
                px = 255
            else:
                px = 0

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 흑백 처리 (평균값 기준)
def BWImageAvg():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    pixSum, pixAvg = 0, 0.0
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            pixSum += px

    pixAvg = pixSum / (inH * inW)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            if px > pixAvg:
                px = 255
            else:
                px = 0

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 흑백 처리 (2입력 범위 기준)
def BWImageRange():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value1 = askinteger("흑백 범위 기준 처리", "범위 시작 값 입력 : ", minvalue=0, maxvalue=255)
    value2 = askinteger("흑백 범위 기준 처리", "범위 끝 값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            if px <= value1:
                px = 0
            elif px > value2:
                px = 255
            else:
                outImage[i][k] = px

            outImage[i][k] = px

    # ************************************************** #
    printImage()


# 비트연산_AND (입력)
def BitCalcAnd():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = askinteger("BIT AND 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] & value

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 비트연산_OR (입력)
def BitCalcOr():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = askinteger("BIT AND 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] | value

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 비트연산_XOR (입력)
def BitCalcXor():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = askinteger("BIT AND 연산 처리", "연산값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] ^ value

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 비트연산_NOT (입력)
def BitCalcNot():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = 256 + ~inImage[i][k]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 감마 변환 이미지 (입력)
def gammaImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = 0.0
    value = askfloat("감마 변환 처리", "감마 변환 값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            gamma = pow(px, 1 / value)

            if gamma > 255:
                gamma = 255
            elif gamma <= 0:
                gamma <= 0
            else:
                outImage[i][k] = int(gamma)

            outImage[i][k] = int(gamma)
    # ************************************************** #
    printImage()


# 범위 강조 이미지 (2입력)
def rangeEmphasis():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value1 = askfloat("범위 강조 처리", "범위 시작 값 입력 : ", minvalue=0, maxvalue=255)
    value2 = askfloat("범위 강조 처리", "범위 끝 값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            if (value1 <= px) and (px <= value2):
                outImage[i][k] = 255
            else:
                outImage[i][k] = px
    # ************************************************** #
    printImage()


# 파라볼라 CAP 변환
def parabolaCAP():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = (4 / 255.0) * inImage[i][k] * (255 - inImage[i][k])

            outImage[i][k] = int(px)
    # ************************************************** #
    printImage()


# 파라볼라 CUP 변환
def parabolaCUP():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = (4 / 255.0) * inImage[i][k] * (inImage[i][k] - 255) + 255

            outImage[i][k] = int(px)
    # ************************************************** #
    printImage()


# 명암대비 스트래칭 (입력)
def stretchedImage():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    value = askfloat("명암대비 스트래칭", "스트래칭 값 입력 : ", minvalue=0, maxvalue=255)

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] + (outImage[i][k] - 128) * value

            if px > 255:
                px = 255
            elif px <= 0:
                px = 0
            else:
                outImage[i][k] = int(px)

            outImage[i][k] = int(px)
    # ************************************************** #
    printImage()


# *************************** < 2. 히스토그램 (화소점) 처리 기능 함수 정의부 > ***************************
# 히스토그램 출력
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
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    histo = [0 for _ in range(256)]
    # 초기화
    for i in range(256):
        histo[i] = 0

    # 빈도수 조사
    for i in range(inH):
        for k in range(inW):
            value = inImage[i][k]
            histo[value] += 1

    # 정규화
    min, max = 0, 0
    dif = 0
    hNum = 0

    for i in range(256):
        if histo[i] <= min:
            min = histo[i]
        elif histo[i] >= max:
            max = histo[i]
    dif = max - min

    # 정규화된 히스토그램
    scaleHisto = [0 for _ in range(256)]
    for i in range(256):
        scaleHisto[i] = (histo[i] - min) * HIGH / dif

    # 정규화된 히스토그램 출력

    # 정규화된 히스토그램의 값은 출력배열에 검은 점으로 표현
    #    for i in range(outH):
    #        for k in range(scaleHisto[i]):
    #            OutImage[outW * (outH - k - 1) + i] = 0

    # ************************************************** #
    printImage()


# 히스토그램 스트래칭
def histoStretch():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    min = inImage[0][0]
    max = inImage[0][0]

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            if px < min:
                min = px
            elif px > max:
                max = px

    for i in range(inH):
        for k in range(inW):
            px = 255.0 * (inImage[i][k] - min) / (max - min)

            outImage[i][k] = int(px)

    # ************************************************** #
    printImage()


# 히스토그램 엔드-인 탐색
def histoEndIn():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    min = inImage[0][0]
    max = inImage[0][0]

    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k]

            if px < min:
                min = px
            elif px > max:
                max = px

    min += 50
    max -= 50
    for i in range(inH):
        for k in range(inW):
            px = 255.0 * (inImage[i][k] - min) / (max - min)

            if px <= 0.0:
                outImage[i][k] = 0
            elif px > 255.0:
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(px)

    # ************************************************** #
    printImage()


# 히스토그램 평활화
def histoEqual():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    # 1단계 : 히스토그램 생성
    histo = [0 for _ in range(256)]
    for i in range(inH):
        for k in range(inW):
            histo[inImage[i][k]] += 1

    # 2단계 : 누적 히스토그램 생성 (누적합 생성)
    sumHisto = [0 for _ in range(256)]
    sumHisto[0] = histo[0]
    for i in range(1, 256, 1):
        sumHisto[i] = sumHisto[i - 1] + histo[i]

    # 3단계 : 정규화된 누적 히스토그램 생성 (정규화된 누적합 생성)
    # n = sum * (1/(inH*inW)) * 255.0
    for i in range(256):
        sumHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0

    # 4단계 : 원래 값을 정규화 값으로 치환
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = int(sumHisto[inImage[i][k]])
    # ************************************************** #
    printImage()


# *************************** < 3. 화소 영역 처리 기능 함수 정의부 > ***************************
# 엠보싱
def embossing():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 엠보싱 마스크
    Emask = [[-1, 0, 0],
             [0, 0, 0],
             [0, 0, 1]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * Emask[m][n]
            tmpOut[i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 3x3 블러링
def blurring33():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 3x3 블러링 마스크
    B3mask = [[1. / 9, 1. / 9, 1. / 9],
              [1. / 9, 1. / 9, 1. / 9],
              [1. / 9, 1. / 9, 1. / 9]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * B3mask[m][n]
            tmpOut[i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크의 합이 0이 아니므로 주석 처리
    """
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0
    """

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 5x5 블러링
def blurring55():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 5
    # 5x5 블러링 마스크
    B5mask = [[1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
              [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
              [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
              [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25],
              [1. / 25, 1. / 25, 1. / 25, 1. / 25, 1. / 25]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 2][k + 2] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * B5mask[m][n]
            tmpOut[i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크의 합이 0이 아니므로 주석 처리
    """
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0
    """

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 샤프닝
def sharpning():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 샤프닝 마스크
    Smask = [[-1, -1, -1],
             [-1, 9, -1],
             [-1, -1, -1]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * Smask[m][n]
            tmpOut[i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크의 합이 0이 아니므로 주석 처리
    """
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0
    """

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 고주파 필터 처리 샤프닝
def HPFSharp():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 고주파 필터 마스크
    HPFmask = [[-1. / 9, -1. / 9, -1. / 9],
               [-1. / 9, 8 / 9, -1. / 9],
               [-1. / 9, -1. / 9, -1. / 9]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * HPFmask[m][n]
            tmpOut[i][k] = S * 8  # x8 : 효과 진해짐

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 저주파 필터 처리 샤프닝
def LPFSharp():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 저주파 필터 마스크
    LPFmask = [[1. / 16, 2. / 16, 1. / 16],
               [2. / 16, 4. / 16, 2. / 16],
               [1. / 16, 2. / 16, 1. / 16]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * LPFmask[m][n]
            tmpOut[i][k] = tmpIn[i][k] - S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    """
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0
    """

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 스무딩 (가우시안)
def smoothing():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 스무딩(가우시안) 마스크
    SMmask = [[1. / 16, 1. / 8, 1. / 16],
              [1. / 8, 1. / 4, 1. / 8],
              [1. / 16, 1. / 8, 1. / 16]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * SMmask[m][n]
            tmpOut[i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    """
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0
    """

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# *************************** < 4. 엣지 검출 처리 기능 함수 정의부 > ***************************
# 수직 엣지
def horizontalEdge():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 엠보싱 마스크
    Hmask = [[0, 0, 0],
             [-1, 1, 0],
             [0, 0, 0]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * Hmask[m][n]
            tmpOut[i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 수평 엣지
def verticalEdge():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    MSIZE = 3
    # 엠보싱 마스크
    Vmask = [[0, -1, 0],
             [0, 1, 0],
             [0, 0, 1]]

    # 임시 입출력 메모리 할당
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tmpIn[i + m][k + n] * Vmask[m][n]
            tmpOut[i][k] = S

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    for i in range(outH):
        for k in range(outW):
            tmpOut[i][k] += 127.0

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v = tmpOut[i][k]

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# 수직 수평 엣지
def horiVertiEdge():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

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
    tmpIn = malloc2D(inH + MSIZE - 1, inW + MSIZE - 1)
    tmpOut1 = malloc2D(inH, inW)
    tmpOut2 = malloc2D(inH, inW)

    # 임시 입력을 0으로 초기화
    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpIn[i][k] = 0.0

    # 임시 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
    for i in range(inH):
        for k in range(inW):
            tmpIn[i + 1][k + 1] = inImage[i][k]

    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S1 = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S1 += tmpIn[i + m][k + n] * Hmask[m][n]
            tmpOut1[i][k] = S1
    # 회선 연산 --> 마스크로 긁어가면서 계산하기
    for i in range(inH):
        for k in range(inW):
            S2 = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S2 += tmpIn[i + m][k + n] * Vmask[m][n]
            tmpOut2[i][k] = S2

    # 후처리 (마스크의 합계에 따라서 정제..)
    # 마스크 합계가 0일 경우 추가
    for i in range(outH):
        for k in range(outW):
            tmpOut1[i][k] += 127.0
            tmpOut2[i][k] += 127.0

    # 임시 출력 --> 출력 메모리
    for i in range(inH):
        for k in range(inW):
            v1 = tmpOut1[i][k]
            v2 = tmpOut2[i][k]
            v = v1 + v2

            if v > 255.0:
                outImage[i][k] = 255
            elif v <= 0.0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = int(v)
    # ************************************************** #
    printImage()


# *************************** < 5. 기하학 처리 기능 함수 정의부 > ***************************
# 좌우 미러링
def LR_Mirroring():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][((inW - 1) - k)]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 상하 미러링
def TB_Mirroring():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[((inH - 1) - i)][k]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 상하+좌우 미러링
def TB_LR_Mirroring():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[((inH - 1) - i)][((inW - 1) - k)]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 오른쪽 90도 회전
def turn90Right():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inW
    outW = inH

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inW):
        for k in range(inH):
            px = inImage[inH - k - 1][i]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 오른쪽 180도 회전
def turn180Right():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[inH - i - 1][inW - k - 1]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 오른쪽 270도 회전
def turn270Right():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inW
    outW = inH

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inW):
        for k in range(inH):
            px = inImage[k][inW - i - 1]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 왼쪽 90도 회전
def turn90Left():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inW
    outW = inH

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inW):
        for k in range(inH):
            px = inImage[k][inW - i - 1]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 왼쪽 180도 회전
def turn180Left():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inH):
        for k in range(inW):
            px = inImage[inH - i - 1][inW - k - 1]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# 왼쪽 270도 회전
def turn27Left():
    global inImage, outImage, inH, inW, outH, outW
    global window, canvas, paper

    # 중요! 출력 영상의 크기를 결정 --> 알고리즘에 의존
    outH = inW
    outW = inH

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    ## ***** 영상처리 알고리즘 ***** ##
    for i in range(inW):
        for k in range(inH):
            px = inImage[inH - k - 1][i]

            outImage[i][k] = px
    # ************************************************** #
    printImage()


# *************************** < 메인 함수 > ***************************
window = Tk()
window.title(" GrayScale Image Processing Ver2.2 RC 2 ")
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
clearControl = Menu(pxDotMenu)  # 선명도 조절
BW = Menu(pxDotMenu)  # 흑백
BITCalc = Menu(pxDotMenu)  # BIT 연산
parabola = Menu(pxDotMenu)  # 파라볼라 변환

funcMenu.add_cascade(label='1. 화소점 처리', menu=pxDotMenu)

pxDotMenu.add_command(label='1. 동일 영상', command=equalImage)
pxDotMenu.add_command(label='2. 반전 영상', command=reverseImage)
pxDotMenu.add_command(label='3. 밝기 조절 (입력)', command=brightControlImage)
pxDotMenu.add_cascade(label='4. 선명도 조절 (입력)', menu=clearControl)
clearControl.add_command(label='선명하게', command=clearUp)
clearControl.add_command(label='흐릿하게', command=clearDown)
pxDotMenu.add_cascade(label='5. 흑백', menu=BW)
BW.add_command(label='127 기준', command=BWImage127)
BW.add_command(label='평균값 기준', command=BWImageAvg)
BW.add_command(label='입력 범위 기준 (2입력)', command=BWImageRange)
pxDotMenu.add_cascade(label='6. 비트 연산', menu=BITCalc)
BITCalc.add_command(label='AND 연산 (입력)', command=BitCalcAnd)
BITCalc.add_command(label='OR 연산 (입력)', command=BitCalcOr)
BITCalc.add_command(label='XOR 연산 (입력)', command=BitCalcXor)
BITCalc.add_command(label='NOT 연산', command=BitCalcNot)
pxDotMenu.add_command(label='7. 감마 변환 (입력)', command=gammaImage)
pxDotMenu.add_command(label='8. 범위 강조 (2입력)', command=rangeEmphasis)
pxDotMenu.add_cascade(label='9. 파라볼라 변환', menu=parabola)
parabola.add_command(label='파라볼라 CAP', command=parabolaCAP)
parabola.add_command(label='파라볼라 CUP', command=parabolaCUP)
pxDotMenu.add_command(label='10. 명암대비 스트래칭 (입력)', command=stretchedImage)

# 2. 히스토그램 처리
histoMenu = Menu(funcMenu)

funcMenu.add_cascade(label='2. 히스토그램 처리', menu=histoMenu)

histoMenu.add_command(label='1. 히스토그램 출력', command=printHisto)
histoMenu.add_command(label='2. 히스토그램 스트래칭', command=histoStretch)
histoMenu.add_command(label='3. 히스토그램 엔드-인 탐색', command=histoEndIn)
histoMenu.add_command(label='4. 히스토그램 평활화', command=histoEqual)

# 3. 화소 영역 처리
pxAreaMenu = Menu(funcMenu)
blurring = Menu(pxAreaMenu)
sharp = Menu(pxAreaMenu)

funcMenu.add_cascade(label='3. 화소 영역 처리', menu=pxAreaMenu)

pxAreaMenu.add_command(label='1. 엠보싱', command=embossing)
pxAreaMenu.add_cascade(label='2. 블러링', menu=blurring)
blurring.add_command(label='3x3 블러링', command=blurring33)
blurring.add_command(label='5x5 블러링', command=blurring55)
pxAreaMenu.add_cascade(label='3. 샤프닝', menu=sharp)
sharp.add_command(label='샤프닝', command=sharpning)
sharp.add_command(label='HPF 처리 샤프닝', command=HPFSharp)
sharp.add_command(label='LPF 처리 샤프닝', command=LPFSharp)
pxAreaMenu.add_command(label='4. 스무딩 (가우시안)', command=smoothing)

# 4. 엣지 검출 처리
edgeDetectMenu = Menu(funcMenu)

funcMenu.add_cascade(label='4. 엣지 검출 처리', menu=edgeDetectMenu)

edgeDetectMenu.add_command(label='1. 수직 엣지', command=horizontalEdge)
edgeDetectMenu.add_command(label='2. 수평 엣지', command=verticalEdge)
edgeDetectMenu.add_command(label='3. 수직 수평 엣지', command=horiVertiEdge)

# 5. 기하학 처리
geometryMenu = Menu(funcMenu)
mirroring = Menu(geometryMenu)
turn = Menu(geometryMenu)
turnRight = Menu(turn)
turnLeft = Menu(turn)
Turn_Free = Menu(turn)
size = Menu(geometryMenu)

funcMenu.add_cascade(label='5. 기하학 처리', menu=geometryMenu)

geometryMenu.add_cascade(label='1. 미러링', menu=mirroring)
mirroring.add_command(label='좌우 미러링', command=LR_Mirroring)
mirroring.add_command(label='상하 미러링', command=TB_Mirroring)
mirroring.add_command(label='상하좌우 미러링', command=TB_LR_Mirroring)
geometryMenu.add_cascade(label='2. 회전', menu=turn)
turn.add_cascade(label='1. 시계 방향', menu=turnRight)
turnRight.add_command(label='90도', command=turn90Right)
turnRight.add_command(label='180도', command=turn180Right)
turnRight.add_command(label='270도', command=turn270Right)
turn.add_cascade(label='2. 반시계 방향', menu=turnLeft)
turnLeft.add_command(label='90도', command=turn90Left)
turnLeft.add_command(label='180도', command=turn90Left)
turnLeft.add_command(label='270도', command=turn90Left)
geometryMenu.add_cascade(label='2. 자유 회전 (입력)', menu=Turn_Free)
# turn_Free.add_command(label='자유 회전', command=turnFree)
# turn_Free.add_command(label='자유 회전 (백워딩 + 중앙)', command=turnFreeCenter)
geometryMenu.add_cascade(label='3. 확대/축소', menu=size)
# size.add_command(label='이미지 크기 확대 (포워딩)', command=sizeUp)
# size.add_command(label='이미지 크기 확대 (백워딩)', command=backwardMappingSizeUp)
# size.add_command(label='이미지 크기 축소 (포워딩)', command=sizeDown)
# size.add_command(label='이미지 크기 축소 (백워딩)', command=backwardMappingSizeDown)
# geometryMenu.add_command(label='4. 이미지 이동', command=moveImage)
# geometryMenu.add_command(label='5. 워핑', command=warpingImage)


window.mainloop()
