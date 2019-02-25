from tkinter import *
from hanoi import drawPoint
#drawPoint(canvas,x,y)

window = Tk()
w = Canvas(window, width=450, height=300)
w.pack()

a=(50, 50)
b=(300, 200)

"""def creerSegment(canvas, a,b):
    
    diffX = a[0]-b[0] #mettre des coordonnées x et y différentes entre les deux points
    diffY = a[1]-b[1]
    rapportX = abs(diffX/diffY) #si rapport > 1, il faudra descendre plus vite dans les x, sinon dans les y
    rapportY = abs(diffY/diffX)
    
    if diffX > 0:
        signeX = -1
    else:
        signeX = 1
        
    if diffY > 0:
        signeY = -1
    else:
        signeY = 1

    newRapportX = rapportX
    newRapportY = rapportY
    
    def creerPoints(canvas, a, b, rapportX, rapportY, signeX, signeY, newRapportX, newRapportY): #crée le segment de a vers b
        #creer un nouveau point
        print("aaa")
        while newRapportX>1:
            drawPoint(canvas, a[0]+signeX, a[1])
            a[0] += 1
            newRapportX-=1
        newRapportX += rapportX
        while newRapportY>1:
            drawPoint(canvas, a[0], a[1]+signeY)
            a[1] += 1
            rapportY-=1
        newRapportY += rapportY
            
        return creerPoints(canvas, a, b, rapportX, rapportY, signeX, signeY, newRapportX, newRapportY)

    creerPoints(w, a, b, rapportX, rapportY, signeX, signeY, newRapportX, newRapportY)

creerSegment(w,a,b)"""

def creerSegmentSmart(canvas,a,b):
    if abs(a[0]-b[0])+abs(a[1]-b[1]) <= 2:
        return
    else:
        coordMilieu = ((a[0]+b[0])//2,(a[1]+b[1])//2)
        drawPoint(canvas, coordMilieu[0], coordMilieu[1])
        creerSegmentSmart(canvas, a, coordMilieu)
        creerSegmentSmart(canvas, coordMilieu, b)

creerSegmentSmart(w,a,b)

mainloop()
