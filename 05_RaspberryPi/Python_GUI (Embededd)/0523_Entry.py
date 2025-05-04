# 0523_Entry.py

import tkinter
import time

def onClickResult():
    print("onClick : " + entry.get())       # entry.get() : Entry 값 읽어 이벤트 처리

def eventFunc():
    print(entry.get())


window = tkinter.Tk()

window.title("Hi! My name is Window!")
window.geometry("320x240+100+100")
window.resizable(False, False)

entry = tkinter.Entry(window)
entry.insert(0, "******")                       # entry.insert() : Entry 내 특정 위치에 문자열 추가
entry.insert(3, "Hi!")
entry.bind("<Return>", eventFunc)
entry.pack()

button = tkinter.Button(window, text="Click", command=onClickResult)
button.pack()

window.mainloop()




'''
# textLcd_1.py

import i2c_lcd_driver
import tkinter

LCD_length = 16

textLcd = i2c_lcd_driver.lcd()


def onClickResult():
    bufLine1 = "{}".format(entry1.get())
    bufLine2 = "{}".format(entry2.get())

    if (len(bufLine1) > LCD_length):
        Line1 = bufLine1[:LCD_length]
        Line2 = bufLine1[LCD_length:]

    textLcd.lcd_display_string(Line1, 1, pos=0)
    textLcd.lcd_display_string(Line2, 2, pos=0)


window = tkinter.Tk()

window.title("Hi! My name is Window!")
window.geometry("320x240+100+100")
window.resizable(False, False)

button = tkinter.Button(window, text="Click", command=onClickResult)
entry1 = tkinter.Entry(window)
entry2 = tkinter.Entry(window)

entry1.pack()
entry2.pack()
button.pack()

window.mainloop()
'''
