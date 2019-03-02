DROP TABLE unicode;

CREATE TABLE unicode (
  codepoint nvarchar2(6) PRIMARY KEY,
  charname  nvarchar2(100) NOT NULL,
  category nchar(2) NOT NULL,
  combining number NOT NULL,
  bidi nvarchar2(3) NOT NULL,
  decomposition nvarchar2(100),
  decimal_ number,
  digit number,
  numeric_ nvarchar2(100),
  mirrored nchar(1) NOT NULL,
  oldname nvarchar2(100),
  comment_ nvarchar2(100),
  uppercase nvarchar2(6),
  lowercase nvarchar2(6),
  titlecase nvarchar2(6),
  CONSTRAINT fk_upper FOREIGN KEY (uppercase) REFERENCES unicode(codepoint),
  CONSTRAINT fk_lower FOREIGN KEY (lowercase) REFERENCES unicode(codepoint),
  CONSTRAINT fk_title FOREIGN KEY (titlecase) REFERENCES unicode(codepoint)
);

CREATE INDEX idx_charname ON unicode(charname);

CREATE INDEX idx_numeric ON unicode(numeric_);


-- désactivation des contraintes
alter table unicode disable constraint fk_upper;
alter table unicode disable constraint fk_lower;
alter table unicode disable constraint fk_title;

/*IMPORTATION DES DONNEES:
Sélection du format des données (csv)
Sélection du délimiteur (;)
Puis exécution du script généré
*/

-- ré-activation des contraintes
alter table unicode enable constraint fk_upper;
alter table unicode enable constraint fk_lower;
alter table unicode enable constraint fk_title;


-- Pour consulter l'analyse de la table UNICODE :
select * from user_tab_statistics where table_name = 'UNICODE';
-- donne des infos sur le nombre de blocs, de lignes, le nombre moyen de caractères par ligne

--Pour consulter l'analyse des colonnes de la table UNICODE
select * from user_tab_col_statistics where table_name = 'UNICODE';
-- donne des infos sur le nombre de valeurs distinctes dans la colonne, la valeur min, la valeur max, la densité, la longueur moyenne...

-- ne fonctionne pas : parametre size non valide
analyze table UNICODE compute statistics for columns category size
    (select count(distinct category) from UNICODE);

-- obligation de faire à part
select count(distinct category) from UNICODE
--> on trouve 29

-- On fait donc
analyze table UNICODE compute statistics for columns category size 29;

-- Puis
select * from user_tab_col_statistics where table_name = 'UNICODE' and column_name = 'CATEGORY';
-- on trouve frequency dans la colonne histogramme, ce qui prouve que le SGBD a bien créé un histogramme en fréquence

/* PARTIE 3 */
--
set serveroutput off;

-- On exécute notre requête
select u1.codepoint, u1.charname from UNICODE u1
    join UNICODE u2 on u2.codepoint=u1.uppercase
    where u2.category='Lu';

--Puis on affiche le plan d'exécution de la requête précédente avec :
select * from table(dbms_xplan.display_cursor(null, null, 'ALLSTATS LAST'));

--Le premier parametre à null correspond à SQL_ID (deuxième colonne du cache des requêtes exécutées)
--Le second parametre à null correspond au CHILD_ID

-- Pour obtenir le cache des requêtes exécutées :
select * from v$sql;
-- On obtient le texte de la requête, son SQL_ID

/*

SQL_ID  4rgkx2hu065w5, child number 3
-------------------------------------
select u1.codepoint, u1.charname from UNICODE u1     join UNICODE u2 on
u2.codepoint=u1.uppercase     where u2.category='Lu'

Plan hash value: 2187253078

--------------------------------------------------------------------------
| Id  | Operation          | Name    | E-Rows |  OMem |  1Mem | Used-Mem |
--------------------------------------------------------------------------
|   0 | SELECT STATEMENT   |         |        |       |       |          |
|*  1 |  HASH JOIN         |         |   1400 |  1236K|  1236K| 1348K (0)|
|*  2 |   TABLE ACCESS FULL| UNICODE |   1781 |       |       |          |
|*  3 |   TABLE ACCESS FULL| UNICODE |   1400 |       |       |          |
--------------------------------------------------------------------------

Predicate Information (identified by operation id):
---------------------------------------------------

   1 - access("U2"."CODEPOINT"="U1"."UPPERCASE")
   2 - filter("U2"."CATEGORY"=U'Lu')
   3 - filter("U1"."UPPERCASE" IS NOT NULL)

Note
-----
   - Warning: basic plan statistics not available. These are only collected when:

*/

/* Explications :
L'optimiseur choisit de faire un hashJoin : utilisation de 1348K de mémoire
Accès aux table avec un directAccess dans chaque table
*/

--On peut égelement utiliser 'ALL+OUTLINE' à la place de 'ALLSTATS LAST'
select * from table(dbms_xplan.display_cursor(null, null, 'ALL +OUTLINE'));

/*On obtient :

SQL_ID  4rgkx2hu065w5, child number 0
-------------------------------------
select u1.codepoint, u1.charname from UNICODE u1     join UNICODE u2 on
u2.codepoint=u1.uppercase     where u2.category='Lu'

Plan hash value: 2187253078

------------------------------------------------------------------------------
| Id  | Operation          | Name    | Rows  | Bytes | Cost (%CPU)| Time     |
------------------------------------------------------------------------------
|   0 | SELECT STATEMENT   |         |       |       |   274 (100)|          |
|*  1 |  HASH JOIN         |         |  1400 |   108K|   274   (1)| 00:00:04 |
|*  2 |   TABLE ACCESS FULL| UNICODE |  1781 | 24934 |   137   (1)| 00:00:02 |
|*  3 |   TABLE ACCESS FULL| UNICODE |  1400 | 91000 |   137   (1)| 00:00:02 |
------------------------------------------------------------------------------

Query Block Name / Object Alias (identified by operation id):
-------------------------------------------------------------

   1 - SEL$58A6D7F6
   2 - SEL$58A6D7F6 / U2@SEL$1
   3 - SEL$58A6D7F6 / U1@SEL$1

Outline Data
-------------

  /*+
      BEGIN_OUTLINE_DATA
      IGNORE_OPTIM_EMBEDDED_HINTS
      OPTIMIZER_FEATURES_ENABLE('11.2.0.1')
      DB_VERSION('11.2.0.1')
      ALL_ROWS
      OUTLINE_LEAF(@"SEL$58A6D7F6")
      MERGE(@"SEL$1")
      OUTLINE(@"SEL$2")
      OUTLINE(@"SEL$1")
      FULL(@"SEL$58A6D7F6" "U1"@"SEL$1")
      FULL(@"SEL$58A6D7F6" "U2"@"SEL$1")
      LEADING(@"SEL$58A6D7F6" "U1"@"SEL$1" "U2"@"SEL$1")
      USE_HASH(@"SEL$58A6D7F6" "U2"@"SEL$1")
      SWAP_JOIN_INPUTS(@"SEL$58A6D7F6" "U2"@"SEL$1")
      END_OUTLINE_DATA
  */
/*
Predicate Information (identified by operation id):
---------------------------------------------------

   1 - access("U2"."CODEPOINT"="U1"."UPPERCASE")
   2 - filter("U2"."CATEGORY"=U'Lu')
   3 - filter("U1"."UPPERCASE" IS NOT NULL)

Column Projection Information (identified by operation id):
-----------------------------------------------------------

   1 - (#keys=1) "U1"."CODEPOINT"[NVARCHAR2,12],
       "U1"."CHARNAME"[NVARCHAR2,200]
   2 - "U2"."CODEPOINT"[NVARCHAR2,12]
   3 - "U1"."CODEPOINT"[NVARCHAR2,12], "U1"."CHARNAME"[NVARCHAR2,200],
       "U1"."UPPERCASE"[NVARCHAR2,12]
 */


--Autre possibilité :
select t.* from v$sql s, table(dbms_xplan.display_cursor(s.SQL_ID, NULL, 'ALLSTATS LAST')) t
where s.SQL_FULLTEXT like '%BOUT DE TEXTE DE LA REQUETE%';

-- Pour purger la zone tampon entre chaque expérience :
ALTER system flush shared_pool;
ALTER system flush buffer_cache;

-- Explain plan, permet d'expliciter le plan d'exécution d'une requête sans l'exécuter
--(contrairement à display_cursor)
explain plan for
select u1.codepoint, u1.charname from UNICODE u1
    join UNICODE u2 on u2.codepoint=u1.uppercase
    where u2.category='Lu';
--> Explicité.

-- Puis on récupère le résultat du explain
select * from table(dbms_xplan.display);

--> résultat:
/*
Plan hash value: 2187253078

------------------------------------------------------------------------------
| Id  | Operation          | Name    | Rows  | Bytes | Cost (%CPU)| Time     |
------------------------------------------------------------------------------
|   0 | SELECT STATEMENT   |         |  1400 |   108K|   274   (1)| 00:00:04 |
|*  1 |  HASH JOIN         |         |  1400 |   108K|   274   (1)| 00:00:04 |
|*  2 |   TABLE ACCESS FULL| UNICODE |  1781 | 24934 |   137   (1)| 00:00:02 |
|*  3 |   TABLE ACCESS FULL| UNICODE |  1400 | 91000 |   137   (1)| 00:00:02 |
------------------------------------------------------------------------------

Predicate Information (identified by operation id):
---------------------------------------------------

   1 - access("U2"."CODEPOINT"="U1"."UPPERCASE")
   2 - filter("U2"."CATEGORY"=U'Lu')
   3 - filter("U1"."UPPERCASE" IS NOT NULL)
*/

/*
Conclusion : le plan d'exécution proposé par la commande explain plan est identique à celui
réalisé par l'optimiseur Oracle.
*/

/* PARTIE 4 */

-- on peut imposer l'usage d'une méthode dans le plan d'exécution grâce à des instructions d'exécution :
--Par exemple, pour imposer l’usage d’un index :
SELECT /*+ index(<nom-table> <nom-idx>) */ * FROM t WHERE <prédicat-col>;

-- Requête pour utilisation du full access
explain plan for
select * from UNICODE;

/* Parcours séquentiel pour retourner tous les éléments de la table donc on accède à toute la table */

-- Requête pour utilisation du filter
explain plan for
select * from UNICODE where category = 'Lu';

/* On utilise l'opérateur de sélection algèbre qui oblige à filtrer les résultats */

-- Requête pour utilisation de l'index unique scan
explain plan for
select * from UNICODE where codepoint = '0000';

/* Sélection sur une valeur de la clé primaire --> utilisation de l'index pour récuperer un unique tuple
(clé primaire donc valeur unique)*/

-- Requête pour utilisation de l'index range scan et du l'access by index rowid
explain plan for
select * from UNICODE where codepoint between '0000' and '0009';

/* Recherche sur un intervalle de valeur pour la clé primaire donc utilisation d'un index + parcours séquentiel de ses feuilles */

-- Requête pour utilisation du hash join
explain plan for
select u1.codepoint, u1.charname from UNICODE u1
    join UNICODE u2 on u2.codepoint=u1.uppercase
    where u2.category='Lu';

/* Utilisation du hash join car les tuples ayant la même valeur de codepoint et uppercase seront dans le même bucket */

-- Requête pour utilisation du merge join
explain plan for
select * from UNICODE u1, UNICODE u2
    where u1.codepoint > u2.uppercase;

/* Trie des tables rendu nécessaire par l'opérateur > qui rend inefficace le hash join */

-- Requête pour utilisation du merge join
explain plan for
select * from (select * from Unicode where codepoint like '00%') U1
    join (select * from Unicode where titlecase like '00%') U2
        on U1.codepoint = U2.titlecase;

/* Utilisation de l'opérateur Nested Loops car jointure sur deux tables comprenant peu de tuples et où on ne peut pas utiliser
    l'index sur la clé primaire car on a plus la table entière */

-- Requête pour l'utilisation du hash group by
explain plan for
select count(lowercase) from Unicode group by lowercase;

/* La clause group by sur une colonne qui n'est pas indexée implique l'utilisation de l'opérateur hash group by */

-- Requête pour l'utilisation du sort aggregate
explain plan for
select max(age) from Villageois;

 /* Le sort aggregate est ici utilisé pour trier puis aggréger le résultat d'un fast full scan */

 -- Requête pour l'utilisation du union
 explain plan for
select * from ((select * from Unicode where lowercase like '00%')
    union (select * from Unicode where lowercase like '02%'));

/* Oracle utilise d'abord l'opérateur union all qui fait une union classique sans élimination des doublons suivie d'un
    sort unique qui trie les valeurs pour ensuite éliminer les doublons */
-- en effet avec cette requête :
explain plan for
select * from ((select * from Unicode where lowercase like '00%')
    union all (select * from Unicode where lowercase like '02%'));
-- L'optimiseur n'utilise que l'opérateur union all

/* Liste complémentaire */

-- Utilisation de l'opérateur BITMAP : opération à partir d'index bitmap

-- Création des index
create bitmap index IX_Bitmap_Mirrored on Unicode(mirrored);
create bitmap index IX_Bitmap_Combining on Unicode(combining);

-- Requêtes utilisant les deux index bitmap créés
explain plan for
select * from Unicode where combining = 1 and mirrored = 'N';

/* L'utilisation des index bitmap permet de vérifier très rapidement les cas où les deux conditions sont respectées
    Les index bitmap sont ici utilisés car les colonnes combining et mirrored ne prennent que deux types de valeurs :
    combining prend les valeurs 0 ou 1 et mirrored les valeurs 'N' ou 'Y' */


-- Utilisation de l'opérateur PARTITION : accès aux enregistrements par l’un des fragments de la table

-- Création d'une table partitionnée
create table Partitions(
    nb number
    )
partition by range(nb)(
partition inf10 values less than(10),
partition inf100 values less than(100),
partition inf1000 values less than(1000),
partition sup1000 values less than (MAXVALUE)
);

-- Insertion d'une ligne dans chaque partition de la table Partitions
insert into Partitions values (5);
insert into Partitions values (50);
insert into Partitions values (500);
insert into Partitions values (5000);

-- Requête sur la table partitionnée
select * from Partitions;
select * from table(dbms_xplan.display_cursor(null, null, 'ALL +OUTLINE'));

/* L'opérateur partition est utilisée par l'optimiseur pour rechercher des tuples sur une table partitionnée */


-- Utilisation de l'opérateur MAT_VIEW : recherche d’enregistrements à partir d’une vue matérialisée

-- Création de la vue matérialisée
create materialized view Vue_Join_Unicode as
    select U1.codepoint from Unicode U1 join Unicode U2 on U1.codepoint = U2.lowercase
        where U1.mirrored = 'N';

-- Requête sur la vue matérialisée :
explain plan for
select * from Vue_Join_Unicode where codepoint like '0%';

/* Oracle utilise donc l'opérateur MAT_VIEW (full access ici) pour rechercher sur une vue matérialisée */


/* REQUETES RECURSIVES */

-- Création de la table Edge
create table Edge (
    f number not null,
    t number not null,
    constraint PK_Edge primary key (t, f)
    );

-- Ajout d'arcs grâce à un petit script python :
/*
for i in range(1,40):
    print("insert into Edge values ({},{});".format(i, i+1))
*/
--> produit les commandes suivantes :
insert into Edge values (1,2);
insert into Edge values (2,3);
insert into Edge values (3,4);
insert into Edge values (4,5);
            ...
insert into Edge values (39,40);

-- Première requête récursive :
WITH trcl(f,t) AS (
SELECT * FROM Edge
UNION ALL
SELECT g.f, t.t FROM Edge g, trcl t WHERE g.t = t.f
)
SELECT t FROM trcl WHERE f=1 ;

/*
Explications de la requête récursive
A partir de la table Edge, on consrtuit une nouvelle table trcl dans laquelle on associe à chaque noeud de la table Edge tous ses descendants.

*/

-- Utilisation d'un opérateur RECURSIVE pour gérer la récursion
