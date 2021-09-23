from tkinter import *
import ctypes
divis = ctypes.CDLL('./long_division.so')


def addNumbers():
    f = open('indata.txt', 'w')
    f.write(first_number.get() + "\n" + first_order.get() + "\n" + second_number.get())
    f.close()
    divis.central()
    f = open('outdata.txt', 'r')
    k = f.read()
    myText.set(k)


def clear_all():
    first_number.delete(0, 'end')
    first_order.delete(0, 'end')
    second_number.delete(0, 'end')


master = Tk()
myText = StringVar()

Label(master, text="Требуется ввести 2 числа:\nдействительное, вида +-m.n E +-K\nи целое, не превышающее 30 знаков").grid(sticky=N)
Label(master, text="Под мантису действительного числа отведено 32 знака - 30 цифр + точка и знак\nзнак может быть только минус, плюс не вводить").grid(row=2, sticky=N)
Label(master, text="Первое число. Знак и m.n, m + n <= 30 зн.; знак и K, K <= 5 зн.").grid(row=3, sticky=W)

first_number = Entry(master, width=32)
first_order = Entry(master, width=7)
first_number.grid(row=3, column=1)
Label(master, text="E").grid(row=3, column=2)
first_order.grid(row=3, column=3)

Label(master, text="Второе число. Ввод части: знак и n <= 30 зн.").grid(row=5, column=0, sticky=W)

second_number = Entry(master, width=32)
second_number.grid(row=5, column=1)

Label(master, text="÷").grid(row=4, column=1)
get_result = Button(master, text="===", command=addNumbers)
get_result.grid(row=7, column=1, columnspan=2)
Button(master, text="Очистить", command=clear_all).grid(row=7, column=3, columnspan=2)
result = Label(master, text="REsult", textvariable=myText, background="white").grid(row=10, column=0,columnspan=2, rowspan=2,sticky=W+E+N+S, padx=15, pady=15)

mainloop()
