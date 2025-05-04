# 0523_Frame.py

import tkinter

def onCheckbutton():
    print(checkVar1.get())


window = tkinter.Tk()

window.title("Hi! My name is Window!")
window.geometry("320x240+100+100")
window.resizable(False, False)

frame = tkinter.Frame(window, background="#FF0000")
frame.pack(expand=True, fill="both")

button = tkinter.Button(frame, background="#00FF00", text="Button!")
button.pack(expand=True)

#checkVar1 = tkinter.IntVar()            # 1 or 0
checkVar1 = tkinter.BooleanVar()        # True or False

checkbutton1 = tkinter.Checkbutton(window, text="첫 번째 체크 버튼")
checkbutton1.configure(command=onCheckbutton)
checkbutton1.configure(variable=checkVar1)
checkbutton1.pack()

window.mainloop()
