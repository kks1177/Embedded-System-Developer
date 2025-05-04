# Day17-03_GUI 1.py

import tkinter  # 윈도우 창을 지원하는 GUI 제공
from tkinter import *   # tkinter에서 제공하는 함수를 사용할 때 tkinter.Tk()를 해야 하는데
                        # 이 코드를 추가하면 빼도 사용 가능
                        # window = tkinter.Tk()  --> window = Tk()
from tkinter import messagebox

# 변수
filename = 'c:/images/Etc_Raw(squre)/LENA256.RAW'
window, canvas, paper = None, None, None  # 초기화        # 페이퍼 변수

# 함수
def btnClick():
    messagebox.showinfo("제목", "요기가 내용")


# 메인 함수부
window = Tk()  # 벽
window.title(" 제목 ")
window.geometry('300x400')

# 위젯 == 컨트롤
label1 = Label(window, text="Text1", font=("궁서체", 20))
button1 = Button(window, text="Button1", fg='red', bg='yellow', font=("굴림", 20), command=btnClick)        # 버튼 생성      # command=btnClick() x ---> command=btnClick



"""
label1.pack(side=LEFT)       # pack() : 생성한 버튼을 화면에 띄우기
button1.pack(side=LEFT)
"""
label1.place(x=100, y=30)
button1.place(x=50, y=230)
window.mainloop()
