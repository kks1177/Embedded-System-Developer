# 0523_grid.py

import tkinter

window = tkinter.Tk()
window.title("Hi! My name is Window")
window.geometry("320x240+100+100")
window.resizable(False, False)

side1 = tkinter.Label(window, width=10, background="#FF0000")
side2 = tkinter.Label(window, width=10, background="#00FF00")
side3 = tkinter.Label(window, width=10, background="#0000FF")
side4 = tkinter.Label(window, width=10, background="#FF00FF")

side1.grid(row=0, column=0, sticky="nsew")
side2.grid(row=0, column=1, sticky="nsew")
side3.grid(row=1, column=0, sticky="nsew")
side4.grid(row=1, column=1, sticky="nsew")

window.grid_columnconfigure(0, weight=1)
window.grid_columnconfigure(1, weight=9)
window.grid_rowconfigure(0, weight=4)
window.grid_rowconfigure(1, weight=6)

# side1.pack(side="top", expand="true")
# side2.pack(side="bottom", expand="true")
# side3.pack(side="left", expand="true")
# side4.pack(side="right", expand="true")

window.mainloop()
