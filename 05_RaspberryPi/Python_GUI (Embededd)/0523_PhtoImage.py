# 0523_PhtoImage.py

import tkinter

window = tkinter.Tk()
window.title("Hi! My name is Window!")
window.geometry("320x240+100+100")
window.resizable(False, False)

photoimage = tkinter.PhotoImage(file="1-3.png")

label = tkinter.Label(window, image=photoimage)
label.pack()

window.mainloop()
