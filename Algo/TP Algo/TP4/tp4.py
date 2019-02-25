class Tableau:
    def __init__(self,liste):
        self.tab = liste


    def ajouterA(self, elmt):
        self.tab.append(elmt)

    def accesA(self, indice):
        return self.tab[indice]

    def afficher(self):
        print(self.tab)
        
    def insererElmt(self, indice, elmt):
        
        self.ajouterA(self.tab[-1])
        for i in range(len(self.tab)-1, indice-1, -1):
            self.tab[i] = self.accesA(i-1)
        self.tab[indice] = elmt

    def concatener(self, tab1):
        for i in range(len(tab1)):
            self.ajouterA(tab1[i])

    def rechercher(self, recherche):
        for i in range(len(self.tab)):
            if recherche == self.accesA(i):
                return i
        return False
        
"""a = [i for i in range(5)]
tab = Tableau(a)
tab.insererElmt(3,20)
tab.concatener([1,2,3,4,5,6,7,9])
print(tab.rechercher(200))
tab.afficher()"""

class Maillon:
    def __init__(self, val, prec=None, suiv=None):
        self.val = val
        self.prec = prec
        self.suiv = suiv
        
class ListeChainee:
    def __init__(self, tete=None):
        self.tete = tete

    def ajouter(self, maillon):
        courant = self.tete
        while courant.suiv != None:
            courant = courant.suiv
        courant.suiv = maillon
        maillon.prec = courant

    def inserer(self, maillon, indice):
        courant = self.tete
        for i in range(indice-1):
            courant = courant.suiv
        suivant = courant.suiv
        maillon.prec = courant
        maillon.suiv = suivant
        courant.suiv = maillon
        suivant.prec = maillon

    def afficher(self):
        if self.tete != None: #s'il y a plus d'un elmt dans la liste
            courant = self.tete
            while courant != None:
                print(courant.val)
                courant = courant.suiv

    def concatener(self, l1):
        courant = self.tete
        while courant.suiv != None:
            courant = courant.suiv
        courant.suiv = l1.tete
        l1.tete.prec = courant

    def recherche(self, elmt):
        find = False
        courant = self.tete
        while not(find or courant.suiv == None):
            if courant.val == elmt:
                find = True
            courant = courant.suiv
        return find
        
                
"""m3 = Maillon(13)
m2 = Maillon(12)
m1 = Maillon(0)
l = ListeChainee(m1)
l.ajouter(m2)
l.inserer(m3, 1)
l.inserer(Maillon(14), 1)
l1 = ListeChainee(Maillon(545))
l1.concatener(l)
print(l1.recherche(545))
#l1.afficher()
##l.afficher()"""

#+ - 4 * 3 2 / 5 2 = (4-(3*2))+(5/2)
#5/2
#3*2
#4-3*2
#...

#((3−4)/(6−12))∗((7 + 2)/6)
# * / - 3 4 - 6 12 / + 7 2 6

class Pile:
    def __init__(self, chaine):
        self.chaine = chaine
        self.longueur = len(chaine)
        self.indChaine = len(chaine)-1
        self.liste = []

    def isEmpty(self):
        return self.liste == []
    
    def push(self, val):
        self.liste.append(val)

    def pop(self):
        if not(self.isEmpty()):
            retour = self.liste[-1]
            self.liste = self.liste[:-1]
            return retour
        return False
    
    def top(self):
        if not(self.isEmpty()):
            return self.liste[-1]

    def evalChaine(self):
        while self.indChaine > 0:
            temp = ""
            while self.chaine[self.indChaine] != " ":
                if "0" <= self.chaine[self.indChaine] <= "9":
                    temp = self.chaine[self.indChaine] + temp
                self.indChaine -= 1
                
            if temp != "":
                self.push(int(temp))
                
            else :
                print(self.chaine[self.indChaine+1])
                if self.chaine[self.indChaine+1] == "+":
                    self.push(self.pop()+self.pop())
                    
                elif self.chaine[self.indChaine+1] == "-":
                    self.push(self.pop()-self.pop())

                elif self.chaine[self.indChaine+1] == "*":
                    self.push(self.pop()*self.pop())

                elif self.chaine[self.indChaine+1] == "/":
                    self.push(self.pop()/self.pop())

            self.indChaine -= 1
##            print(self.indChaine)

        return self.top()

chaine = " * / - 3 4 - 6 12 / + 7 2 6"
pile = Pile(chaine)
print(((3-4)/(6-12))*((7 + 2)/6))
print(pile.evalChaine())
            
                    
        
        
