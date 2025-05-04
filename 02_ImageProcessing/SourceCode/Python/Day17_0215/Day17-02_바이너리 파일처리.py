# Day17-02_바이너리 파일처리.py

import random


##### 전역 변수부 #####
filename = 'c:/images/Etc_Raw(squre)/flower512.raw'
inImage = []
outImage = []
ROW, COL = 512, 512


##### 함수부 #####
def printImage():
    for i in range(5):
        for k in range(5):
            print("%03d" % outImage[i][k], end=' ')
        print()
    print()


##### 메인 함수부 #####
# 1. 파일 --> 메모리
# 1-1 메모리 할당
ROW = int(input("행 --> "))
COL = int(input("열 --> "))
inImage = [[0 for _ in range(ROW)] for _ in range(COL)]
outImage = [[0 for _ in range(ROW)] for _ in range(COL)]

rfp = open(filename, 'rb')

# 1-2. 불러오기 (대신 랜덤하게)
for i in range(ROW):
    for k in range(COL):
        inImage[i][k] = random.randint(0, 255)
        outImage[i][k] = ord(rfp.read(1))       # ord() 함수 : 글자를 숫자로 바꿔주는 함수

print("이미지 불러오기 성공! ")
rfp.close()
printImage()


# 2. 영상처리
# 2-1. 반전
for i in range(ROW):
    for k in range(COL):
        outImage[i][k] = 255 - inImage[i][k]

print("< 반전 이미지 > ")
printImage()

# 2-2. 입력한 숫자만큼 밝게
value_Bright = int(input("밝기 조절값 입력 : "))

for i in range(ROW):
    for k in range(COL):
        px = inImage[i][k]

        outImage[i][k] = px + value_Bright

if value_Bright > 255:
    print("< 밝기 %d 증가 이미지 > " % value_Bright)
else:
    print("< 밝기 %d 감소 이미지 > " % value_Bright)
printImage()

# 2-3. 흑백 처리
for i in range(ROW):
    for k in range(COL):
        px = inImage[i][k]

        if px > 127:
            outImage[i][k] = 255
        else:
            outImage[i][k] = 0

print("< 흑백(127기준) 처리 화면 > ")
printImage()

# 2-4. 흑백 (평균값)
pxSum = 0
pxAvg = 0
for i in range(ROW):
    for k in range(COL):
        px = inImage[i][k]

        pxSum += px

pxAvg = pxSum / (ROW * COL)

for i in range(ROW):
    for k in range(COL):
        px = inImage[i][k]

        if px > pxAvg:
            outImage[i][k] = 255
        else:
            outImage[i][k] = 0

print("< 평균값(%d) 처리 화면 > " % pxAvg)
printImage()
