# 0523_place.py

import tkinter

window = tkinter.Tk()
window.title("Hi! My name is Window")
window.geometry("320x240+100+100")
window.resizable(False, False)

side1 = tkinter.Label(window, text="(0,0)", background="#FF0000")
side2 = tkinter.Label(window, text="(160,0)", background="#00FF00")
side3 = tkinter.Label(window, text="(0,160)", background="#0000FF")
side4 = tkinter.Label(window, text="(160,160)", background="#FF00FF")

side1.place(width=64, height=32, x=0, y=0)
side2.place(width=64, height=32, x=100, y=0)
side3.place(width=64, height=32, x=0, y=100)
side4.place(width=64, height=32, x=100, y=100)

window.mainloop()
