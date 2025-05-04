# Day17-04_GUI 2.py

import tkinter  # 윈도우 창을 지원하는 GUI 제공
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *

## 전역 변수
filename = ""
window, canvas, paper = None, None, None  # 초기화        # 페이퍼 변수
ROW, COL = 256, 256
inImage = []
outImage = []


## 함수
def btnClick1():
    messagebox.showinfo("팝업창1", "요기가 내용1")


def btnClick2():
    messagebox.showinfo("팝업창2", "요기가 내용2")


def openFile():
    global inImage, outImage, ROW, COL, filename    # 전역변수

    filename = askopenfilename(parent=window,
                               filetypes=(("RAW 파일", "*.raw"), ("모든 파일", "*.*")))
    #label1.configure(text=str(filename))

    # 1-1 메모리 할당
    inImage = [[0 for _ in range(ROW)] for _ in range(COL)]
    outImage = [[0 for _ in range(ROW)] for _ in range(COL)]


    # 1-2. 불러오기 (대신 랜덤하게)
    rfp = open(filename, 'rb')
    for i in range(ROW):
        for k in range(COL):
            inImage[i][k] = ord(rfp.read(1))
        #outImage[i][k] = ord(rfp.read(1))       # ord() 함수 : 글자를 숫자로 바꿔주는 함수

    #print("이미지 불러오기 성공! ")
    rfp.close()
    printImage()


def printImage():
    global inImage, outImage, ROW, COL, filename    # 전역변수

    for i in range(ROW):
        for k in range(COL):
            r = g = b = inImage[i][k]
            paper.put("#%02x%02x%02x" % (r, g, b), (k, i))


def copyData():
    value = askinteger("제목", "설명~~~", minvalue=0, maxvalue=255)     # minvalue (o)   minValue (x)
    label1.configure(text=str(value))



## 메인 함수부
window = Tk()
window.title(" 제목 ")
window.geometry('400x300')

#CheckVar1 = IntVar()

# 캔버스 + 페이퍼
canvas = Canvas(window, height=256, width=256)      # 칠판 준비
paper = PhotoImage(height=256, width=256)           # 작성할 종이 준비
canvas.create_image((256/2, 256/2), image=paper, state='normal')



# 메뉴
mainMenu = Menu(window)     # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu)   # 상위 메뉴 (파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)     # add_cascade누르면 실행 x

fileMenu.add_command(label='열기', command=openFile)                    # add_command : 누르면 실행
fileMenu.add_command(label='저장')
fileMenu.add_separator()
fileMenu.add_command(label='종료')

editMenu = Menu(mainMenu)       # 상위 메뉴 (편집)
mainMenu.add_cascade(label='편집', menu=editMenu)     # add_cascade누르면 실행 x

editMenu.add_command(label='복사', command=copyData)  # add_command : 누르면 실행
editMenu.add_command(label='잘라내기')
editMenu.add_separator()
editMenu.add_command(label='붙여넣기')


# 위젯 == 컨트롤
label1 = Label(window, text="Text1", font=("궁서체", 20))
label2 = Label(window, text="Text2", font=("궁서체", 20))
button1 = Button(window, text="검은 버튼", fg='white', bg='black', font=("바탕체", 20), command=btnClick1)
button2 = Button(window, text="하얀 버튼", fg='black', bg='white', font=("바탕체", 20), command=btnClick2)
#checkButton1 = Checkbutton(window, text="체크 버튼", variable=CheckVar1)

"""
label1.place(x=70, y=30)
label2.place(x=230, y=30)
#checkButton1.pack(x=100, y=150)
button1.place(x=30, y=100)
button2.place(x=200, y=100)
"""
label1.pack(side=TOP)       # pack() : 생성한 버튼을 화면에 띄우기
button1.pack(side=TOP)
canvas.pack()
window.mainloop()
