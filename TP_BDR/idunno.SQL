/* */

ALTER table COMPOSITION
  add constraint cleEtrangerePotion foreign key nomIngredient
    references POTION(nomPotion)

ALTER table COMPOSITION
  ADD foreign key(nomIngredient)
    references INGREDIENT(nomIngredient);

alter table COMPOSITION modify constraint SYS_C00479414
  foreign key(nomIngredient) references INGREDIENT(nomIngredient) or POTION(nomPotion)

-- question 1
-- on commence par supprimer la contrainte
alter table COMPOSITION drop constraint SYS_C00479414

/*Partie 1 de la question 1 skipped, possibilité d'y répondre
  en ajoutant un trigger qui vérifie à l'insertion si nomIngredient
  est dans la table INGREDIENT ou dans la table POTION*/

/* Une potion ne peut pas contenir plus de 5 ingrédients directs et doit au moins en contenir un.*/

CREATE OR REPLACE TRIGGER compteNbIng
  before INSERT OR DELETE ON COMPOSITION
  for each row
  declare nb int;
  begin
    select count(*) into nb from COMPOSITION where nomPotion = :new.nomPotion group by nomPotion;
    if INSERTING and nb >= 5 then
        RAISE_APPLICATION_ERROR(-20000, 'Erreur insertion : nombre d ingrédients max atteint sur la potion ' + :new.nomPotion);
    end if;
    if DELETING and nb <= 1 then
        RAISE_APPLICATION_ERROR(-20000, 'Erreur suppression : nombre d ingrédients min atteint sur la potion ' + :new.nomPotion);
    end if;
  end;
/

-- Erreur
CREATE OR REPLACE TRIGGER compteNbIngMin
  before DELETE ON COMPOSITION
  for each row
  declare nb int;
  begin
    select count(*) into nb from COMPOSITION where nomPotion = :new.nomPotion group by nomPotion;
    if nb <= 1 then
        RAISE_APPLICATION_ERROR(-20000, 'Erreur suppression : nombre d ingrédients min atteint sur la potion ');
    end if;
  end;
/


delete from COMPOSITION where nomPotion = 'Amour';

/*SORTIE CONSOLE :
Erreur commençant à la ligne: 26 de la commande -
delete from COMPOSITION where nomPotion = 'Amour'
Rapport d'erreur -
ORA-04091: la table E168386D.COMPOSITION est en mutation ; le déclencheur ou la fonction ne peut la voir
ORA-06512: à "E168386D.COMPTENBINGMIN", ligne 3
ORA-04088: erreur lors d'exécution du déclencheur 'E168386D.COMPTENBINGMIN'
*/


/* Question 2 Clé primaire*/

-- définir la nouvelle colonne
alter table POTION add noPotion integer;

-- définir une séquence
CREATE sequence seqNoPotion start with 1;

-- définition du trigger, seqNoPotion fait référence à la séquence définie précedemment
-- trigger before
CREATE OR REPLACE trigger idInsert
    before INSERT on POTION
    for each row
    begin
        select seqNoPotion.NEXTVAL into :new.noPotion from DUAL;
    end;
/

-- trigger after, ne fonctionne pas
-- erreur ORA-04091: la table E168386D.POTION est en mutation ; le déclencheur ou la fonction ne peut la voir
CREATE OR REPLACE trigger idInsertAfter
    after INSERT on POTION
    for each row
    begin
        update POTION set noPotion = seqNoPotion.NEXTVAL;
    end;
/

-- disable un trigger
alter trigger idInsert disable;

-- Partie III

-- ajout de la colonne nbIngredients dans la table POTION
ALTER TABLE POTION add nbIngredients integer;

-- remplissage de cette nouvelle colonne
UPDATE POTION set nbIngredients =
(select count(*) from COMPOSITION
    where COMPOSITION.nomPotion = POTION.nomPotion
        group by COMPOSITION.nomPotion)

-- création du trigger
-- attention : max(null) renvoie 0
-- Notre trigger fonctionne lorsque l'on ajoute un ingrédient dans composition à une potion ne possédant pas déjà d'ingrédients grâce au max()
CREATE OR REPLACE trigger comptePotions
    before INSERT on COMPOSITION
    for each row
    declare
    nbIng integer := 0;
    begin
        select max(count(*)) into nbIng from COMPOSITION
          where COMPOSITION.nomPotion = :new.nomPotion
            group by COMPOSITION.nomPotion;
        nbIng:=nbIng + 1;
        update POTION set nbIngredients = nbIng
            where POTION.nomPotion = :new.nomPotion;
    end;
/

/* à la place du max on aurait pu remplacer par
COALESCE (expr1, expr2)
qui équivaut à:
CASE WHEN expr1 IS NOT NULL THEN expr1 ELSE expr2 END
*/

-- test du trigger
insert into COMPOSITION values('Sirop', 'Citron', 10);


-- Partie 4 - Vues modifiables
-- synthaxe de création de vues :
CREATE or REPLACE VIEW Vue
(colonneA,colonneB,colonneC,colonneD)
AS SELECT colonne1,colonne2,colonneI,colonneII
FROM Nom_table1 Alias1,Nom_tableII AliasII
WHERE Alias1.colonne1 = AliasII.colonneI
AND Alias1.colonne2 = AliasII.colonneII

-- accès à la vue grâce à select * from Vue
-- drop grâce à drop view Vue

-- question 1 :
-- ne fonctionne pas avec un join on, renvoie l'erreur nom de colonne en double
--> solution : jointure naturelle
create or replace view potEtIng as
    select * from POTION natural join COMPOSITION;

-- accès grâce à
select * from potEtIng;

-- la vue se met automatiquement à jour après une modification d'une des tables sur lesquelles elle porte ex:
insert into COMPOSITION values ('Sirop', 'Lavande', 30);

-- question 2 :
delete from potEtIng where
    nomPotion in (select nomPotion from potEtIng
                    group by nomPotion having count(*) >= 3);
/* Attention, cette version supprime les éléments de la vue et également les occurences des potions présentes
 au moins 3 fois dans la table COMPOSITION (pas normal). Pour supprimer les potions de la table potion il faudrait changer
 delete from potEtIng en delete from POTION */

-- pour supprimer dans les bonnes tables on pourrait créer un trigger instead of delete on la vue


-- Partie 5 : Requêtes hierarchiques

-- question 1 : on commence par supprimer la contrainte établissant la colonne nomIngredient comme clé étrangère
-- dans la table INGREDIENT, on pourra ainsi ajouter des potions en ingrédient
alter table COMPOSITION drop constraint SYS_C00519413;

-- on ajoute une potion en ingrédient d'une autre potion
insert into COMPOSITION values ('Sirop', 'Force', 1);

-- requête pour la potion sirop
select nomIngredient from COMPOSITION
  connect by prior nomIngredient = nomPotion
    start with nomPotion = 'Sirop';

-- question 2
-- requête pour l'ingrédient eau
select nomPotion from COMPOSITION
    connect by prior nomPotion = nomIngredient
        start with nomIngredient = 'Eau';

-- Partie 6 : oracle avec python at home


-- CHAPITRE 2 :

-- Partie 1 : Consulter le dictionnaire des données

-- question 1
-- recherche des lignes de DICT qui correspondent aux utilisateurs
select * from DICT where table_name like 'DBA_U%';
-->  on trouve DBA_USER <-> Information about all users of the database
select * from DBA_USERS;

-- question 2
-- recherche des lignes de DICT qui correspondent aux privilèges
select * from DICT where table_name like '%PRIV%';
-- tables intéressantes : DBA_COL_PRIVS; DBA_ROLE_PRIVS; DBA_SYS_PRIVS; USER_COL_PRIVS; USER_ROLE_PRIVS (current user)
-- permet d'obtenir les privilèges de chaque utilisateur
select * from DBA_SYS_PRIVS;

-- question 3
-- recherche des lignes de DICT qui correspondent aux rôles
select * from DICT where table_name like '%ROLE%';

-- permet d'obtenir le rôle de chaque utilisateur
select * from DBA_ROLE_PRIVS;

-- trouver les bonnes tables
select * from DICT where table_name like '%ROLE%';
select * from DICT where table_name like '%PRIV%';

-- rôles des utilisateurs et ceux qui les ont octroyé (null si pas de correspondance avec grantor)
select unique DBA_ROLE_PRIVS.grantee, granted_role, grantor from DBA_ROLE_PRIVS left join DBA_TAB_PRIVS
    on DBA_ROLE_PRIVS.grantee = DBA_TAB_PRIVS.grantee;

-- quetion 4
-- recherche des tables quotas
select * from DICT where table_name like '%QUOTAS%';
-- requête
select * from DBA_TS_QUOTAS;

-- II - gestion des utilisateurs
-- recherche des tablespace pour savoir quel tablespace donner par défaut
select * from DICT where table_name like '%TABLESPACE%';
-- vérification de la table
select * from DBA_TABLESPACES;

-- création utilisateur
create user E168386DIDEFIX identified by E168386DIDEFIX default tablespace BACASABLE;
-- attribution à cet utilisateur du droit à se connecter
grant connect to E168386DIDEFIX;

-- connexion :
connect E168386DIDEFIX/E168386DIDEFIX@matador:1521:orcl;
-- problème : déconnexion immédiate : La connexion créée via la commande de script CONNECT a été déconnectée
-- déconnexion normale avec exit

-- creation table après connexion (via création d'une session car sinon déconnexion immédiate)
CREATE TABLE test(
    test1 number(3),
    test2 varchar(30));
-- fonctionne sans avoir besoin d'attribuer à E168386DIDEFIX le privilège create table car cet utilisateur
-- a été créé par un utilisateur qui a tous les droits DBA, sinon on aurait du faire :
grant CREATE TABLE to E168386DIDEFIX;

-- donner le tablespace USERS par défaut et limiter la taille prise par l'utilisateur sur ce tablespace à 20 kilo octets
alter user E168386DIDEFIX default tablespace USERS quota 20K on USERS;

-- note : selectionner nos tables depuis la session d'idfix : SELECT * FROM E168386D.POTION;
-- pas besoin de grant select on POTION to E168386DIDEFIX car il a déjà tous les droits de base;

-- question 5
grant select on TEST to PUBLIC;

--- III - Rôles
-- création rôle
create role E168386DRoleIndex;

-- allocation de privilèges à ce rôle
grant create any index, alter any index, drop any index to E168386DRoleIndex;

-- allocation de ce rôle à Idefix
grant E168386DRoleIndex to E168386DIDEFIX;

-- Consulter ses privilèges sur les tables
select * from USER_TAB_PRIVS;

-- Vérifier ses privilèges
select * from DBA_SYS_PRIVS where grantee = 'E168386DIDEFIX';
-- Privilèges de la session en cours
select * from SESSION_PRIVS;

-- suppression de l'utilisateur et de ce qui s'en suit
drop user E168386DIDEFIX cascade;



/*NOTES

error-number : A vendor-specific number that is mapped to an error code before it is stored in a variable named SQLCODE. The RAISE_APPLICATION_ERROR procedure accepts user-defined error-number values from -20000 to -20999. The SQLCODE that is returned in the error message is SQL0438N. The SQLSTATE contains class 'UD' plus three characters that correspond to the last three digits of the error-number value.

FOR EACH ROW, FOR EACH STATEMENT
   Précise si la procédure du déclencheur doit être lancée pour chaque ligne affectée par l'événement ou simplement pour chaque instruction SQL. FOR EACH STATEMENT est la valeur par défaut.

Différentes actions en fonction de l'action à executer

   IF DELETING THEN
     Operation := 3;
     CustomerCode := :old_buffer.field1;
   END IF;

   IF INSERTING THEN
     Operation := 1;
     CustomerCode := :new_buffer.field1;
   END IF;

   IF UPDATING THEN
     Operation := 2;
     CustomerCode := :new_buffer.field1;
   END IF;

'Erreur : nombre d\'ingrédients max atteint' ne fonctionne pas
--> impossibilité d'escape les apostrophes

question 2 :
quand INSERT INTO POTION VALUES ('Sirop', 2, 'Alésia', 'Déboitementduménix', 'curatif', date '0042-05-29');
--> Erreur SQL : ORA-00947: nombre de valeurs insuffisant
00947. 00000 -  "not enough values"

--> solution : INSERT INTO POTION VALUES ('Sirop', 2, 'Alésia', 'Déboitementduménix', 'curatif', date '0042-05-29', NULL);
*/
