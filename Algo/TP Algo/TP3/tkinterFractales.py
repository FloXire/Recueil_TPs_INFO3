from tkinter import *
import math

#un triangle est repéré par ses 3 coordonnées

def coordMilieu(coord1, coord2):
    return ((coord1[0]+coord2[0])//2,(coord1[1]+coord2[1])//2)

def creerLigne(canvas, coord1, coord2, coord3):
    canvas.create_line(coord1[0],coord1[1],coord2[0],coord2[1])
    canvas.create_line(coord2[0],coord2[1],coord3[0],coord3[1])
    canvas.create_line(coord1[0],coord1[1],coord3[0],coord3[1])

def fractale(coordTriangle, w): #crée 3 triangles au sein du triangle en question
    #condition d'arrêt
    if abs(coordTriangle[0][0]-coordTriangle[1][0]) < 5:
        return
    
    #coord3 : coord du mileu bas, 2 : milieu droit, 1 : milieuGauche
    coord3 = coordMilieu(coordTriangle[0], coordTriangle[1])
    coord2 = coordMilieu(coordTriangle[1], coordTriangle[2])
    coord1 = coordMilieu(coordTriangle[0], coordTriangle[2])
    creerLigne(w, coord1, coord2, coord3)
    coordNewTriangleUp = (coord2,coord1,coordTriangle[2])
    coordNewTriangleLeft = (coordTriangle[0],coord3,coord1)
    coordNewTriangleRight = (coord3,coordTriangle[1],coord2)

    fractale(coordNewTriangleUp, w)
    fractale(coordNewTriangleLeft, w)
    fractale(coordNewTriangleRight, w)

def creerTriangle(tailleCote):

    hauteur = int(math.sqrt(tailleCote**2-((tailleCote)/2)**2))
    window = Tk()
    w = Canvas(window, width=tailleCote+100, height=int(math.sqrt(tailleCote**2-((tailleCote)/2)**2))+100)
    w.pack()
    #coord1 : gauche, 2 : droite, 3 : milieu
    coord1 = (50, hauteur+50)
    coord2 = (50+tailleCote, hauteur+50)
    coord3 = (50+tailleCote//2, 50)
    coordTriangle = (coord1,coord2,coord3)

    creerLigne(w, coord1, coord2, coord3)

    fractale(coordTriangle, w)
    mainloop()



creerTriangle(700)
