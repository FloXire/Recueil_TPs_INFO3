import multiprocessing
import threading
import time
import random
tprint = print
# A décommenter pour synchroniser l'affichage tprint()
from tprint import tprint
import sys


# liste des noms de threads à créer
#NomsThreads = ["PONG","PING"]
# puis essayez avec:
NomsThreads = ["PONG","PING","PING","PONG","PING","PONG","PONG","PING"]
threads = []

# boucle de répétition de chaque thread
NbCoups = 10

# ressource critique: 
chaine_ping_pong = ''

# Les semaphores
Sping = threading.Semaphore(1)
Spong = threading.Semaphore(0)


# Threads de type Ping (resp. Pong)
def thread_ping_pong(nom) :
    global chaine_ping_pong
    tprint( '{nom} : Debut du thread nom={nom}, pid={pid}, tid={tid}'.format(nom=nom, pid=multiprocessing.current_process().pid, tid=threading.get_ident()))

    for i in range(NbCoups):
        time.sleep(random.randint(0, 3))

        if nom is "PING" :
            # prise d'un jeton dans le semaphore ping
            tprint( '{nom} : Demande P(Sping)'.format(nom=nom))
            Sping.acquire()
            tprint( '{nom} : Obtient P(Sping)'.format(nom=nom))
        else :
            # prise d'un jeton dans le semaphore pong
            tprint( '{nom} : Demande P(Spong)'.format(nom=nom))
            Spong.acquire()
            tprint( '{nom} : Obtient P(Spong)'.format(nom=nom))

        # Debut de section critique
        tprint( '{nom} : Debut de section critique'.format(nom=nom))

        time.sleep(random.randint(0, 3))
        chaine_ping_pong = chaine_ping_pong + nom + ' '
        tprint( '{nom} : \t (i={i}) chaine_ping_pong={chaine_ping_pong}'.format(nom=nom, i=i, chaine_ping_pong=chaine_ping_pong) )

        tprint( '{nom} : Fin de section critique'.format(nom=nom))
	# fin de section critique

        if nom is "PING" :
           # renvoi d'un jeton dans le semaphore pong
            tprint( '{nom} : renvoie V(Spong)'.format(nom=nom))
            Spong.release()
        else :
            # renvoi d'un jeton dans le semaphore ping
            tprint( '{nom} : renvoie V(Sping)'.format(nom=nom))
            Sping.release()
            
            
            
            
    tprint( '{nom} : Fin du thread'.format(nom=nom))



  
# Création des Thread
for nom in NomsThreads:
    threads.append(threading.Thread(target=thread_ping_pong, args=(nom,)))
# ou
# threads = [threading.Thread(target=thread_ping_pong, args=(nom,)) for nom in NomsThreads]

tprint('Debut du test avec {nom}'.format(nom=NomsThreads))

#sys.exit()

# Démarrage des threads
for t in threads:
    t.start()

# Attente de terminaison des threads
for t in threads:
    t.join()

tprint('Fin du test')

