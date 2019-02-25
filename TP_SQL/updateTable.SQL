/* Fichier permettant de modifier les tables précédemment créées */

/* insérer dans une table

INSERT INTO client (prenom, nom, ville, age)
 VALUES
 ('Rébecca', 'Armand', 'Saint-Didier-des-Bois', 24),
 ('Aimée', 'Hebert', 'Marigny-le-Châtel', 36),
 ('Marielle', 'Ribeiro', 'Maillères', 27),
 ('Hilaire', 'Savary', 'Conie-Molitard', 58);

*/

-- Défnir une clé étrangère à une table déjà existante
ALTER table PRISEPOTION ADD foreign key(nomPotion) references POTION(nomPotion)
ALTER table COMPOSITION ADD foreign key(nomIngredient) references INGREDIENT(nomIngredient)
ALTER table POTION MODIFY posologie integer -- change le type de la colonne posologie dans la table POTION
ALTER table POTION ADD foreign key(druideCreateur) references VILLAGEOIS(nomVillageois)

-- Insertion d'éléments (tuples) dans les tables

/*
Necessité de créer :
  - des villageois, patients, potions, prises, composition, ingrédients
  - des patients de lutèce qui exercent le métier de Barde et de Poissonnier
  - des potions qui ont une origine à null
  - des potions de genre curatif et magique
  - des potions créées par Amnésix et Panoramix en 52 av JC
  - dates autour de 52 av JC
  - des druides ayant créé des potions de tous les genres
  - des potions originaires des villages de patients
  - des druides qui ont créé plus de potions qu'Amnésix et Panoramix
  - des origines BR
  - posologie > 5g
  - faire en sorte que des patients consomment plus qu'une potion
  - panoramix druideCreateur
  - faire des druides gaulois
  - faire des potions composées de thym, gui, coriandre (pas forcément les 3 en même temps)
  - obélix consomme des potions tout au long de l'année
  - des ingrédients qui ne sont pas utilisés
  - Déboitementduménix, Panoramix, Astérix, Amnésix, Obélix, AssuranceTourix, Florianix, Guillaumix
*/

-- VILLAGEOIS (nomVillageois, prénom, sexe, âge, profession, village, nationalité)*/

INSERT INTO VILLAGEOIS VALUES ('Guillaumix', NULL, 'M', 20, 'Druide', 'Pontivix', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Florianix', NULL, 'M', 20, 'Druide', 'Lutèce', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Panoramix', NULL, 'M', 200, 'Druide', 'Alésia', 'Gaulois');
INSERT ALL
  INTO VILLAGEOIS VALUES ('Déboitementduménix', NULL, 'M', 80, 'Druide', 'Lyon', 'Gaulois')
  INTO VILLAGEOIS VALUES ('Amnésix', NULL, 'M', 30, 'Druide', 'Marseille', 'Latin')
  INTO VILLAGEOIS VALUES ('Toinonix', NULL, 'F', 30, 'Prof', 'Nantix', 'Gaulois')
  INTO VILLAGEOIS VALUES ('Astérix', NULL, 'M', 25, 'Guerrier', 'Lutèce', 'Gaulois')
  INTO VILLAGEOIS VALUES ('Obélix', NULL, 'M', 27, 'Guerrier', 'Lutèce', 'Gaulois')
  INTO VILLAGEOIS VALUES ('César', 'Jules', 'M', 40, 'Empereur', 'Rome', 'Romain')
  INTO VILLAGEOIS VALUES ('Abraracoursix', NULL, 'M', 50, 'Chef', 'Lutèce', 'Gaulois')
  SELECT 1 from DUAL -- car insert all nécessite une réqête SELECT  (INSERT ALL requires a SELECT subquery. To get around that, SELECT 1 FROM DUAL is used to give a single row of dummy data.))
INSERT INTO VILLAGEOIS(nomVillageois, sexe, age, profession, village, nationalite) VALUES ('Romainix', 'M', 20, 'Guerrier', 'Rome', 'Romain')
INSERT INTO VILLAGEOIS VALUES ('Matthix', NULL, 'M', 20, 'Philosophe', 'BR', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Pécaudix', NULL, 'M', 80, 'Psychanalyste', 'BR', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Panoramix', NULL, 'M', 200, 'Druide', 'Alésia', 'Gaulois');

-- PATIENT (nomPatient, druideTraitant)

INSERT INTO PATIENT VALUES ('Astérix', 'Panoramix');
INSERT INTO PATIENT VALUES ('César', 'Amnésix');
INSERT INTO PATIENT VALUES ('Obélix', 'Panoramix');
INSERT INTO PATIENT VALUES ('Matthix', 'Déboitementduménix');
INSERT INTO PATIENT VALUES ('Pécaudix', 'Déboitementduménix');
INSERT INTO PATIENT VALUES ('Toinonix', 'Guillaumix');
INSERT INTO PATIENT VALUES ('Toinonix', 'Florianix');
INSERT INTO PATIENT VALUES ('Abraracoursix', 'Panoramix');
INSERT INTO PATIENT VALUES ('Romainix', 'Amnésix');

-- POTION (nomPotion, posologie, villeOrigine, druideCréateur, genre, dateCréation)

INSERT INTO POTION VALUES ('Potion1', 10, 'Lyon', 'Guillaumix', 'curatif', '10-02-56');
-- ne fonctionne pas, renvoie une date ap JC
INSERT INTO POTION VALUES ('Potion2', 15, 'Lyon', 'Guillaumix', 'magique', to_date('01/01/-0045','mm/dd/syyyy'));









/* NOTES

la création d'un integer de base génère un number(38,0) càd 38 chiffres 0 décimales

le point virgule provoque une erreur, possibilité de ne pas renseigner une colonne en la mettant à NULL

double quote ne fonctionne pas

Quand on insère un tuple, si on ne spécifie pas tous les champs, on peut préciser le nom des champs que l'on remplit dans la commande
Apparemment les champs sont transformés en majuscule sous oracle (pas de prise en compte de la casse)

Lorsque les lignes sont séparées par un point virgule, il faut sélectionner les lignes à exécuter avant d'envoyer la requête

possibilité de modifier directement les tuples dans oracle en mode graphique


*/
