# Day18-02_마우스 이벤트 1 + lambda.py

# import tkinter
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *


## 함수
def btnClick(para):
    messagebox.showinfo("제목", para)


def openFile():
    global image, ROW, COL, filename
    filename = askopenfilename(parent=window,
                               filetypes=(("RAW 파일", "*.raw"), ("모든파일", "*.*")))
    # 1-1 메모리 할당
    image = [[0 for _ in range(COL)] for _ in range(ROW)]
    # 1-2. 불러오기 (대신 랜덤)
    rfp = open(filename, 'rb')
    for i in range(ROW):
        for k in range(COL):
            image[i][k] = ord(rfp.read(1))
    rfp.close()
    printImage()


def printImage():
    global image, ROW, COL, filename
    for i in range(ROW):
        for k in range(COL):
            r = g = b = image[i][k]
            paper.put("#%02x%02x%02x" % (r, g, b), (k, i))


def copyData():
    value = askinteger("제목", "설명~~~~", minvalue=0, maxvalue=255)
    label1.configure(text=str(value))


def leftMouse(event):
    global sx, sy, ex, ey
    sx = event.x
    sy = event.y
    #label1. configure(text=str(xx)+", "+str(yy))        # 마우스 클릭한 곳의 x좌표, y좌표 출력


def rightMouse(event):
    global sx, sy, ex, ey
    ex = event.x
    ey = event.y
    canvas.create_line(sx, sy, ex, ey, width=3, fill='red')


## 전역 변수
sx, sy, ex, ey = [-1] * 4        # start x, start y, end x, end y           # 0이 들어올 수도 있기 때문에 -1로 초기화
filename = ""
window, canvas, paper = None, None, None
ROW, COL = 256, 256
image = []

## 메인
window = Tk()  # 벽
window.title("요기 제목")
window.geometry('300x400')


## 캔버스 + 페이퍼
canvas = Canvas(window, height=256, width=256)
paper = PhotoImage(width=256, height=256)
canvas.create_image((256 / 2, 256 / 2), image=paper, state='normal')

# 윈도창에 마우스 이벤트 추가
canvas.bind("<Button-1>", leftMouse)
canvas.bind("<ButtonRelease-1>", rightMouse)

## 메뉴
mainMenu = Menu(window)  # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu)  # 상위 메뉴(파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=openFile)
fileMenu.add_command(label='저장')
fileMenu.add_separator()
fileMenu.add_command(label='종료')

editMenu = Menu(mainMenu)  # 상위 메뉴(편집)
mainMenu.add_cascade(label='편집', menu=editMenu)
editMenu.add_command(label='복사', command=copyData)
editMenu.add_command(label='잘라내기')
editMenu.add_separator()
editMenu.add_command(label='붙여넣기')

# 위젯 == 컨트롤
label1 = Label(window, text="나는 글자다", font=("궁서체", 20))
button1 = Button(window, text="This is Button", fg='red', bg='yellow',
                 font=("Lucida Fax", 20), command=lambda: btnClick('이거다'))

label1.pack(side=TOP)
button1.pack(side=TOP)
canvas.pack()
# label1.place(x=100, y=30)
# button1.place(x=50, y=230)
window.mainloop()