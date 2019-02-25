import threading
from tampon_fifo import Tampon_fifo, tampon_retirer, tampon_deposer, tampon_est_plein, tampon_est_vide, tampon_nbElements
tprint = print
# A décommenter pour synchroniser l'affichage tprint()
from tprint import tprint


#
#   Problème des "Producteurs Consommateurs"
#   Solution à l'aide de moniteurs
#



#
# Définition du Moniteur Producteurs Consommateurs
#


class MoniteurProdCons () :
    def __init__(self, tampon) :
        # Les variables d'état du moniteur = ressources critiques
        self.tampon = tampon
        self.mutex = threading.Lock()
        self.fifoProd = threading.Condition(self.mutex)
        self.fifoCons = threading.Condition(self.mutex)



# Les Points d'entrée :

def moniteur_deposer(moniteur, nom, element)  :
    tprint("{nom} debute moniteur_deposer".format(nom=nom))
    moniteur.mutex.acquire()

    tprint("{nom} a pris le mutex".format(nom=nom))

    # a compléter : attendre (=wait) si tampon plein (tampon_est_plein( moniteur.tampon )....)
    while tampon_est_plein(moniteur.tampon):
        tprint("{nom} va en wait".format(nom=nom))
        moniteur.fifoProd.wait()


    tprint("        {nom} depose \"{element}\" dans le tampon...".format(nom=nom, element=element))
    tampon_deposer(moniteur.tampon, element)
    tprint("        {nom} a fini de deposee \"{element}\" dans le tampon".format(nom=nom, element=element))
    print(".................................................", tampon_nbElements(moniteur.tampon))
    assert(not tampon_est_vide( moniteur.tampon ))

    tprint("{nom} envoi un signal".format(nom=nom))

    moniteur.fifoCons.notify()

    tprint("{nom} termine moniteur_deposer".format(nom=nom))
    moniteur.mutex.release()

    tprint("{nom} a rendu le mutex".format(nom=nom))


def moniteur_retirer(moniteur, nom)  :
    tprint("{nom} debute moniteur_retirer".format(nom=nom))
    moniteur.mutex.acquire()

    tprint("{nom} a pris le mutex".format(nom=nom))

    while tampon_est_vide(moniteur.tampon):
        tprint("{nom} va en wait".format(nom=nom))
        moniteur.fifoCons.wait()

    tprint("        {nom} retire un element du tampon...".format(nom=nom))
    element = tampon_retirer(moniteur.tampon)
    tprint("        {nom} a fini de retirer \"{element}\" du tampon".format(nom=nom, element=element))
    print(".................................................", tampon_nbElements(moniteur.tampon))
    assert(not tampon_est_plein( moniteur.tampon ))

    tprint("{nom} envoi un signal".format(nom=nom))

    moniteur.fifoProd.notify()

    tprint("{nom} termine moniteur_retirer".format(nom=nom))
    moniteur.mutex.release()

    tprint("{nom} a rendu le mutex".format(nom=nom))

    return element


# fin de definition du moniteur





# Exemple d'utilisation

def test_moniteur_prod_cons():
    # Ressource Critique
    tailleMax=3
    tampon = Tampon_fifo(tailleMax)
    moniteur  =  MoniteurProdCons (tampon)
    nbCoups = 4

    # Fonction principales des threads "producteurs"
    def producteur(nom, moniteur)  :
        for i in range(nbCoups):
            element = nom[1:]
            moniteur_deposer(moniteur, nom, element)


    # Fonction principales des threads "consommateurs"
    def consommateur(nom, moniteur)  :
        for i in range(nbCoups):
            elt=moniteur_retirer(moniteur, nom )



    # Fonction principales de création et de démarrage des threads
    nomsThreads  =  ["c1","c2", "c3", "c4","p1", "p2", "p3", "p4"]
    threads = []

    for nomT in nomsThreads  :
        if nomT[0]=='p' :
            thread_main = producteur
        else :
           thread_main = consommateur
        threads.append( threading.Thread(target=thread_main, name=nomT, args=(nomT,moniteur)))

    tprint("Debut du test")

    for t in threads :
        t.start()
        #tprint("{name} demarre".format(name=t.name))

    for t in threads :
        t.join()
        #tprint("{name} est terminé".format(name=t.name))

    tprint("Fin du test")



if __name__ == "__main__" :
    test_moniteur_prod_cons()


# Exemple de trace d'éxécution (chronogramme)
# avec
#       tailleMax = 2
#       nomsThreads  =  ["c1","p1", "p2", "p3", "p4", "c2", "c3", "c4"]
#
# on obtient
#
#C1:C2:C3:C4::P1:P2:P3:P4::  T   :Etat : CV     : CP    :NC:NP:Comment
#W :  :  :  ::  :  :  :  ::      :vide :C1      :       :1 :  :
#  :  :  :  ::D :  :  :  ::1     :     :C1      :       :1 :  :
#W*:  :  :  ::S :  :  :  ::1     :     :        :       :1 :  :S->C1
#  :  :  :  ::F :  :  :  ::1     :     :        :       :1 :  :
#  : R:  :  ::  :  :  :  ::      :vide :        :       :1 :  :
#  : S:  :  ::  :  :  :  ::      :vide :        :       :1 :  : ?
#  : F:  :  ::  :  :  :  ::      :vide :        :       :1 :  :
#*W:  :  :  ::  :  :  :  ::      :vide :        :       :  :  : reprise C1 ?
#R :  :  :  ::  :  :  :  ::-1    :vide :        :       :  :  : c1 a retiré alors qu'il n'y avait plus rien
# ....
# A completer
# ....
#
#
#
# Avec :
# Consommateur={C1,C2,C3,C4}, Producteurs={P1,P2,P3,P4}
# CV: condition/liste attente tampon vide, CP: Condition/liste attente tampon plein
# T : le contenu du tampon
# Etat={vide,plein}: etat du tampon
# NC: nombre de consommateur en attente sur tampon vide CV (nbConsommateursAttenteVide)
# NP: nombre de producteurs en attente sur tampon plein CP (nbProducteursAttentePlein)
#
# Etat Consommateur:
#   - S : signal(CP)
#   - W : wait(CV), empiler et endormir
#   - W* : signal(CV) effectué par un autre processus ( producteur ), depiler
#   - *W : acquisition du mutex et reprise
#   - R : operation retirer
#   - F : fin
# Etat Producteur:
#   - S : signal(CV)
#   - W : wait(CP), empiler et endormir
#   - W* : signal(CP) effectué par un autre processus ( consommateur ), depiler
#   - *W : acquisition du mutex et reprise
#   - D : operation deposer
#   - F : fin
