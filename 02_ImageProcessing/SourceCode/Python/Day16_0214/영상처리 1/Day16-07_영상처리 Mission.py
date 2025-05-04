# Day16-07_영상처리 Mission.py

import random

##### 전역 변수부 #####
inImage = []
outImage = []
ROW, COL = 0, 0

inKey = 0


##### 메뉴 함수부 #####
def printMenu():
    while True:
        print(" [메뉴] 1.화소점 처리  2.히스토그램 처리  3.화소영역 처리  4.엣지 검출 처리  5.기하학 처리  0.프로그램 종료")
        menu = int(input(" 메뉴 선책 : "))

        if menu == 0:
            print("\n 프로그램 종료! ")
            return
        elif menu == 1:
            print("\n [화소점 처리 기능 선택] ")
            print(" [기능] 1.동일  2.반전  3.밝기 조절(입력)  4.선명도  5.흑백  6.비트 연산 ")
            print("       7.감마 변환  8.범위 강조  9.파라볼라 변환  10.명암대비 스트래칭 ")
            menuChoice(1)

        elif menu == 2:
            print(" [히스토그램 처리 기능 선택] ")
            print(" [기능] 1.히스토그램 출력  2.스트래칭  3.엔드-인 탐색  4.평활화 ")
            menuChoice(2)
        elif menu == 3:
            print(" [화소 영역 처리 기능 선택] ")
            print(" [기능] 1.엠보싱  2.블러링  3.샤프닝  4.스무딩 ")
            menuChoice(3)
        elif menu == 4:
            print(" [엣지 검출 처리 기능 선택] ")
            print(" [기능] 1.엣지 검출 ")
            menuChoice(4)
        elif menu == 5:
            print(" [기하학 처리 기능 선택] ")
            print(" [기능] 1.미러링  2.회전  3.확대/축소  4.워핑 ")
            menuChoice(5)


def menuChoice(choice):
    funcChoice = int(input(" 기능 선택 : "))

    # 화소점 처리 기능
    if choice == 1:
        if funcChoice == 1:
            equalImage()
        elif funcChoice == 2:
            brightControl()
        elif funcChoice == 3:
            print("1.127 기준  2.평균값 기준")
            inKey = int(input("흑백 기능 선택 : "))

            if inKey == 1:
                BW_127()
            elif inKey == 2:
                BW_Avg()
            else:
                print("잘못 입력!")

    # 히스토그램 처리 기능
    elif choice == 2:
        pass

    # 화소영역 처리 기능
    elif choice == 3:
        pass

    # 엣지 검출 처리 기능
    elif choice == 4:
        pass

    # 기하학 처리 기능
    elif choice == 5:
        pass



##### 이미지 입출력 함수부 #####
# 이미지 출력 함수
def printImage(res):
    if res == 0:
        print(" < 원본 이미지 > ")
        for i in range(5):  # for i in range(ROW):
            for k in range(5):  # for k in range(COL):
                print("%03d" % inImage[i][k], end=' ')
            print()
        print("\n============================================== \n")
    else:
        print(" < 원본 이미지 > \t\t\t  < %s 이미지 > " % res)

        for i in range(5):  # for i in range(ROW):
            for k in range(5):  # for k in range(COL):
                print("%03d" % inImage[i][k], end=' ')
            print('\t', end=' ')
            for k in range(5):
                print("%03d" % outImage[i][k], end=' ')
            print()
        print()
        print("============================================== \n")


# 이미지 open
def openImage():
    # 0-2. (파일 이미지) 불러오기 (대신 랜덤하게)
    for i in range(ROW):
        for k in range(COL):
            inImage[i][k] = random.randint(0, 255)
            outImage[i][k] = inImage[i][k]
    print("\n => 이미지 불러오기 성공! <= ")
    printImage(0)


# 입력 이미지 입력 여부 확인
def inImgCheck():
    if inImage is None:
        print("\n <주의!!!> 입력 이미지 없음!! 입력 이미지를 먼저 불러오세요! ")
        return


##### 화소점 처리 함수부 #####
# 1-0. 동일 이미지
def equalImage():
    inImgCheck()

    for i in range(ROW):
        for k in range(COL):
            px = inImage[i][k]

            outImage[i][k] = px

    imageName = "동일"
    printImage(imageName)


# 1-1. 반전 이미지
def reverseImage():
    for i in range(ROW):
        for k in range(COL):
            px = inImage[i][k]

            outImage[i][k] = 255 - px

    imageName = "반전"
    printImage(imageName)


# 1-2. 입력한 숫자만큼 밝게
def brightControl():
    value_Bright = int(input("밝기 조절값 입력 : "))

    for i in range(ROW):
        for k in range(COL):
            px = inImage[i][k] + value_Bright

            if px > 255:
                outImage[i][k] = 255
            elif px <= 0:
                outImage[i][k] = 0
            else:
                outImage[i][k] = px

    if value_Bright > 0:
        imageName = "밝기 %d 증가" % value_Bright
        printImage(imageName)
    else:
        imageName = "밝기 %d 감소" % value_Bright
        printImage(imageName)


# 1-3. 흑백 이미지 (127 기준)
def BW_127():
    for i in range(ROW):
        for k in range(COL):
            px = inImage[i][k]

            if px > 127:
                outImage[i][k] = 255
            else:
                outImage[i][k] = 0

    imageName = "흑백 처리 (127 기준)"
    printImage(imageName)


# 1-4. 흑백 이미지 (평균값 기준)
def BW_Avg():
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

    imageName = "흑백 처리 (평균값 %d 기준)" % pxAvg
    printImage(imageName)


##### 메인 함수부 #####
if __name__ == '__main__':
    ## 0. 파일 --> 메모리
    # 0-1 메모리 할당
    ROW = int(input("행 --> "))
    COL = int(input("열 --> "))
    inImage = [[0 for _ in range(ROW)] for _ in range(COL)]  # 입력 이미지 배열 생성
    outImage = [[0 for _ in range(ROW)] for _ in range(COL)]  # 입력 이미지 배열 생성

    openImage()

    printMenu()
