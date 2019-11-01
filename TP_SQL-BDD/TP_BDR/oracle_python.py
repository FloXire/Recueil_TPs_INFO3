import cx_Oracle

ip = 'matador.polytech.univ-nantes.prive'
port = 1521
SID = 'orcl'
dsn_tns = cx_Oracle.makedsn(ip, port, SID)

conn_str = 'E168386D/E168386D@matador.polytech.univ-nantes.prive:1521/orcl'
# Etablissement d'une connection avec le serveur
#conn = cx_Oracle.connect('E168386D', 'E168386D', dsn_tns)
conn = cx_Oracle.connect(conn_str)

# curseur : objet qui sert a effectuer une requete et a recuperer le resultat d'une requete
c = conn.cursor()

# Exemple de requete :
c.execute('select nomPotion, quantiteUtilisee from COMPOSITION')

print(c)
c.close()
conn.close()
