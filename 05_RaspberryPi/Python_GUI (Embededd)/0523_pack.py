# 0523_pack.py

import tkinter

window = tkinter.Tk()
window.title("Hi! My name is Window")
window.geometry("320x240+100+100")
window.resizable(False, False)

side1 = tkinter.Label(window, background="#FF0000")
side2 = tkinter.Label(window, background="#00FF00")
side3 = tkinter.Label(window, background="#0000FF")
side4 = tkinter.Label(window, background="#FF00FF")

side1.pack(side="top", expand="true")
side2.pack(side="bottom", expand="true")
side3.pack(side="left", expand="true")
side4.pack(side="right", expand="true")

window.mainloop()

