from tkinter import *
import time

def drawPoint(canvas, x, y, color="black"):
    canvas.create_rectangle(x,y,x,y, fill=color, width=0)

nbDisques = 4

listeHanoi= [[],[],[]]
for i in range(nbDisques,0,-1):
    listeHanoi[0].append(i)

"""window = Tk()

w = Canvas(window, width=900, height=600)
w.pack()"""
"""w.create_line(100, 50, 200, 500)
w.create_line(300, 50, 400, 500)
w.create_line(500, 50, 600, 500)
w.create_line(0, 100, 200, 0, fill = "red")
w.create_rectangle(50, 25, 150, 75, fill = "blue")"""



def piquet(canvas):
    canvas.delete("all")
    for i in range(1,4):
        canvas.create_line(250*i, 500, 250*i, 100)
        canvas.create_line(250*i-75,500,250*i+75,500)

def updateCanvas(canvas, p1, p2, p3):
    for i in range(len(p1)):
        canvas.create_line(250-p1[i]*10,500-(i+1)*10,250+p1[i]*10,500-(i+1)*10)
    for i in range(len(p2)):
        canvas.create_line(500-p2[i]*10,500-(i+1)*10,500+p2[i]*10,500-(i+1)*10)
    for i in range(len(p3)):
        canvas.create_line(750-p3[i]*10,500-(i+1)*10,750+p3[i]*10,500-(i+1)*10)


def move(p1, p2):
    p2.append(p1[-1])
    p1.pop()

def hanoi(n,a,c,b):
    time.sleep(1)
    piquet(w)
    updateCanvas(w,a,b,c)
    w.update
    if n>1:
        hanoi(n-1,a,b,c)
    move(a, c)
    print("déplacer {} de {} vers {}".format(n,a,c))
    if n>1:
        hanoi(n-1,b,c,a)

"""piquet(w)
updateCanvas(w,listeHanoi[0],listeHanoi[2],listeHanoi[1])
mainloop()

hanoi(nbDisques,listeHanoi[0],listeHanoi[2],listeHanoi[1])"""

    
