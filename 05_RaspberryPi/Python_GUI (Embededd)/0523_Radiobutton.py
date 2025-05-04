# 0523_Radiobutton.py

import tkinter

window = tkinter.Tk()
window.title("Hi! My name is Window!")

def onRadiobutton():
    print(radioVar1.get())


radioVar1 = tkinter.IntVar()

radiobutton1 = tkinter.Radiobutton(window, text="첫 번째 라디오 버튼")
radiobutton1.configure(command=onRadiobutton)
radiobutton1.configure(variable=radioVar1)
radiobutton1.configure(value=1) 
radiobutton1.pack()

window.mainloop()
