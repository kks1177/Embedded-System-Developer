# 0520_GUI.py
# 윈도창 생성, 스크린 배치 및 크기 조정

'''
import tkinter
window = tkinter.Tk()
window.mainloop()       # Tkinter창 생성, UI의 메인루프를 동작하는 용도
                        # 프로그램 코드 가장 하단에 위치
'''

'''
import tkinter
import time

window = tkinter.Tk()

window.title("Hi! My name is Window!")
window.geometry("320x240+100+100")
window.resizable(False, False)



window.mainloop()
'''


import threading
import tkinter
import time
from random import randint

window = tkinter.Tk()


# 화면 중앙, 윈도 창 크기 설정 및 출력
def centerWindow():
    # window.geometry("480x500")                             # geometry() : 창의 크기 설정 및 시작 좌표         # 너비x높이+X좌표+Y좌표

    # 스크린 높이, 너비 구하기
    RES_H = window.winfo_screenheight()  # 1920
    RES_W = window.winfo_screenwidth()  # 1080

    # 생성할 윈도창 크기
    WIN_W = 480
    WIN_H = 400
    # 스크린 50% 크기로 창 크기 생성
    # WIN_H = int(RES_H / 2)
    # WIN_W = int(RES_W / 2)

    # 스크린과 창 크기에 비례해서 중앙 좌표 계산
    X = int((RES_W / 2) - (WIN_W / 2))
    Y = int((RES_H / 2) - (WIN_H / 2))

    # 창에 출력하도록 좌표를 format하여 제작
    # "480x800+720+140"
    result = "{}x{}+{}+{}".format(WIN_W, WIN_H, X, Y)
    window.geometry(result)
    print(result + "\n")


'''
Tkinter 창 내에 텍스트를 출력하는 용도로 사용
이미지를 출력하기 위한 위젯으로도 사용
구현에 따라 영상도 출력 가능
배경 색상 지정, 이미지 지정 가능
'''
def labelWindow():
    '''
    anchor : 택스트 배치
    nw      n       ne
    w       c       e
    sw      s       se
    '''
    label = tkinter.Label(window, text="Hello World!", textvariable=value, anchor="c", background="RED")

    value.set("Bye")
    label.pack(expand=True, fill="both")  # 위젯 창 배치

    t1 = threading.Thread(target=countUp)
    t1.start()


def buttonWindow():
    label = tkinter.Button(window, text="Hello World!", background="#ff9900", command=onClick, repeatdelay=2000, repeatinterval=100)

    value.set("Bye")
    label.pack(expand=True, fill="both")  # 위젯 창 배치


def onClick():
    print(time.time())
    #window.destroy()


def countUp():
    while True:
        count = randint(0, 100)
        value.set(count)
        #count += 1
        time.sleep(1)


window.title("Hi! My name is Window!")
window.protocol('WM_DELETE_WINDOW', window.destroy)  # 창을 닫는 이벤트 수행

centerWindow()
window.resizable(False, False)              # resizable() : 창 크기 고정할지 말지 결정        # (상하 가능 여부, 좌우 가능 여부)
# window.attributes('-fullscreen', True)                  # 전체화면으로 전환

value = tkinter.StringVar()

labelWindow()

buttonWindow()

window.mainloop()
