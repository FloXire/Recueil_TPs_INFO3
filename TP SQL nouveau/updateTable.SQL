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
ALTER table PRISEPOTION ADD foreign key(nomPotion) references POTION(nomPotion);
ALTER table COMPOSITION ADD foreign key(nomIngredient) references INGREDIENT(nomIngredient);
ALTER table POTION MODIFY posologie integer;
-- change le type de la colonne posologie dans la table POTION
ALTER table POTION ADD foreign key(druideCreateur) references VILLAGEOIS(nomVillageois);

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
INSERT INTO VILLAGEOIS(nomVillageois, sexe, age, profession, village, nationalite) VALUES ('Romainix', 'M', 20, 'Guerrier', 'Rome', 'Romain');
INSERT INTO VILLAGEOIS VALUES ('Matthix', NULL, 'M', 20, 'Philosophe', 'BR', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Pécaudix', NULL, 'M', 80, 'Psychanalyste', 'BR', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Panoramix', NULL, 'M', 200, 'Druide', 'Alésia', 'Gaulois');

INSERT INTO VILLAGEOIS VALUES ('Guillaumix', NULL, 'M', 20, 'Druide', 'Pontivix', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Florianix', NULL, 'M', 20, 'Druide', 'Lutèce', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Panoramix', NULL, 'M', 200, 'Druide', 'Alésia', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Déboitementduménix', NULL, 'M', 80, 'Druide', 'Lyon', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Amnésix', NULL, 'M', 30, 'Druide', 'Marseille', 'Latin');
INSERT INTO VILLAGEOIS VALUES ('Toinonix', NULL, 'F', 30, 'Prof', 'Nantix', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Astérix', NULL, 'M', 25, 'Guerrier', 'Lutèce', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Obélix', NULL, 'M', 27, 'Guerrier', 'Lutèce', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('César', 'Jules', 'M', 40, 'Empereur', 'Rome', 'Romain');
INSERT INTO VILLAGEOIS VALUES ('Abraracoursix', NULL, 'M', 50, 'Chef', 'Lutèce', 'Gaulois');
INSERT INTO VILLAGEOIS(nomVillageois, sexe, age, profession, village, nationalite) VALUES ('Romainix', 'M', 20, 'Guerrier', 'Rome', 'Romain');
INSERT INTO VILLAGEOIS VALUES ('Matthix', NULL, 'M', 20, 'Philosophe', 'BR', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Pécaudix', NULL, 'M', 80, 'Psychanalyste', 'BR', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Poissonix', NULL, 'M', 100, 'Poissonnier', 'BR', 'Gaulois');
INSERT INTO VILLAGEOIS VALUES ('Bardix', NULL, 'M', 50, 'Barde', 'BR', 'Gaulois');
UPDATE VILLAGEOIS SET village = 'Lutèce' where nomVillageois in('Poissonix', 'Bardix');


-- PATIENT (nomPatient, druideTraitant)

INSERT INTO PATIENT VALUES ('Astérix', 'Panoramix');
INSERT INTO PATIENT VALUES ('César', 'Amnésix');
INSERT INTO PATIENT VALUES ('Obélix', 'Panoramix');
INSERT INTO PATIENT VALUES ('Matthix', 'Déboitementduménix');
INSERT INTO PATIENT VALUES ('Pécaudix', 'Déboitementduménix');
INSERT INTO PATIENT VALUES ('Toinonix', 'Guillaumix');
INSERT INTO PATIENT VALUES ('Abraracoursix', 'Panoramix');
INSERT INTO PATIENT VALUES ('Romainix', 'Amnésix');
INSERT INTO PATIENT VALUES ('Poissonix', 'Amnésix');
INSERT INTO PATIENT VALUES ('Bardix', 'Amnésix');


-- POTION (nomPotion, posologie, villeOrigine, druideCréateur, genre, dateCréation)

INSERT INTO POTION VALUES ('Potion1', 10, NULL, 'Guillaumix', 'curatif', date '0056-10-02');
-- autre solution en utilisant un format français de date
INSERT INTO POTION VALUES ('Potion2', 15, NULL, 'Florianix', 'magique', to_date('01/01/0045','dd/mm/yyyy'));

INSERT INTO POTION VALUES ('Pétrolane', 2, 'Rome', 'Amnésix', 'curatif', date '0054-05-15');
INSERT INTO POTION VALUES ('Force', 33, 'Lutèce', 'Déboitementduménix', 'magique', date '0033-06-30');
INSERT INTO POTION VALUES ('Amour', 10, 'Lyon', 'Panoramix', 'magique', date '0060-01-09');
INSERT INTO POTION VALUES ('Rhum', 4, 'Rome', 'Panoramix', 'curatif', date '0052-02-19');
INSERT INTO POTION VALUES ('Star', 35, 'Lutèce', 'Amnésix', 'magique', date '0052-08-20');
INSERT INTO POTION VALUES ('Vérité', 12, 'Nantix', 'Amnésix', 'magique', date '0052-12-09');
INSERT INTO POTION VALUES ('Cocaine', 66, 'Marseille', 'Déboitementduménix', 'drogue', date '0053-11-19');
INSERT INTO POTION VALUES ('Vin', 20, 'Rome', 'Amnésix', 'curatif', date '0050-11-13');
INSERT INTO POTION VALUES ('Vinasse', 20, NULL, 'Amnésix', 'curatif', date '0050-11-13');


-- PRISEPOTION (nomPatient, nomPotion, date)
INSERT INTO PRISEPOTION VALUES ('Astérix', 'Force', date '0054-12-22');
INSERT INTO PRISEPOTION VALUES ('Astérix', 'Star', date '0055-03-24');
INSERT INTO PRISEPOTION VALUES ('César', 'Vin', date '0054-11-22');
INSERT INTO PRISEPOTION VALUES ('Obélix', 'Pétrolane', date '0043-07-02');
INSERT INTO PRISEPOTION VALUES ('Romainix', 'Vin', date '0050-11-13');
INSERT INTO PRISEPOTION VALUES ('Toinonix', 'Pétrolane', date '0060-04-14');
INSERT INTO PRISEPOTION VALUES ('Pécaudix', 'Cocaine', date '0051-07-28');
INSERT INTO PRISEPOTION VALUES ('Matthix', 'Vérité', date '0059-10-07');
INSERT INTO PRISEPOTION VALUES ('Matthix', 'Amour', date '0041-03-17');
INSERT INTO PRISEPOTION VALUES ('Matthix', 'Star', date '0045-07-27');
INSERT INTO PRISEPOTION VALUES ('Obélix', 'Amour', date '0045-07-27');
INSERT INTO PRISEPOTION VALUES ('Obélix', 'Vérité', date '0045-07-28');



-- INGREDIENT (nomIngredient, villeOrigine, type) : à renseigner avant la table COMPOSITION
INSERT INTO INGREDIENT VALUES ('Pétrole', 'Alger', 'Hydrocarbure');
INSERT INTO INGREDIENT VALUES ('Huile', 'Marseille', 'Hydrocarbure');
INSERT INTO INGREDIENT VALUES ('E330', 'Alger', 'Colorant');
INSERT INTO INGREDIENT VALUES ('Amidon', 'Nantix', 'glucide');
INSERT INTO INGREDIENT VALUES ('Eau', 'Pontivix', 'Boisson');
INSERT INTO INGREDIENT VALUES ('Taurine', 'Lutèce', 'Boisson');
INSERT INTO INGREDIENT VALUES ('Herbe', 'Marseille', 'Plante');
INSERT INTO INGREDIENT VALUES ('Cuivre', 'Rome', 'Métal');
INSERT INTO INGREDIENT VALUES ('Lavande', 'Alésia', 'Plante');
INSERT INTO INGREDIENT VALUES ('Alcool', 'Rome', 'Boisson');
INSERT INTO INGREDIENT VALUES ('Citron', 'Rome', 'Fruit');
INSERT INTO INGREDIENT VALUES ('Orange', 'Marseille', 'Fruit');
INSERT INTO INGREDIENT VALUES ('Or', 'Alger', 'Métal');
INSERT INTO INGREDIENT VALUES ('Argent', 'Rome', 'Métal');
INSERT INTO INGREDIENT VALUES ('Bronze', 'Lutèce', 'Métal');
INSERT INTO INGREDIENT VALUES ('Platine', 'Paris', 'Métal');
INSERT INTO INGREDIENT VALUES ('Diamant', 'Alger', 'Minerai');
INSERT INTO INGREDIENT VALUES ('Sucre', 'Alésia', 'glucide');
INSERT INTO INGREDIENT VALUES ('Farine', 'Lutèce', 'Poudre');
INSERT INTO INGREDIENT VALUES ('Raisin', 'Nantix', 'Fruit');
INSERT INTO INGREDIENT VALUES ('Pain', 'Paris', 'Aliment');
INSERT INTO INGREDIENT VALUES ('Viande', 'Lutèce', 'Aliment');

-- COMPOSITION (nomPotion, nomIngredient, quantiteUtilisee)
INSERT INTO COMPOSITION VALUES ('Pétrolane', 'Pétrole', 300);
INSERT INTO COMPOSITION VALUES ('Pétrolane', 'Huile', 200);
INSERT INTO COMPOSITION VALUES ('Pétrolane', 'E330', 20);
INSERT INTO COMPOSITION VALUES ('Pétrolane', 'Amidon', 36);
INSERT INTO COMPOSITION VALUES ('Pétrolane', 'Eau', 100);

INSERT INTO COMPOSITION VALUES ('Force', 'Taurine', 170);
INSERT INTO COMPOSITION VALUES ('Force', 'Eau', 20);
INSERT INTO COMPOSITION VALUES ('Force', 'Herbe', 10);
INSERT INTO COMPOSITION VALUES ('Force', 'Cuivre', 40);

INSERT INTO COMPOSITION VALUES ('Amour', 'Taurine', 10);
INSERT INTO COMPOSITION VALUES ('Amour', 'Lavande', 40);
INSERT INTO COMPOSITION VALUES ('Amour', 'Amidon', 40);
INSERT INTO COMPOSITION VALUES ('Amour', 'Alcool', 20);

INSERT INTO COMPOSITION VALUES ('Rhum', 'Alcool', 100);
INSERT INTO COMPOSITION VALUES ('Rhum', 'Citron', 20);
INSERT INTO COMPOSITION VALUES ('Rhum', 'Orange', 20);

INSERT INTO COMPOSITION VALUES ('Star', 'Eau', 20);
INSERT INTO COMPOSITION VALUES ('Star', 'Or', 20);
INSERT INTO COMPOSITION VALUES ('Star', 'Argent', 20);
INSERT INTO COMPOSITION VALUES ('Star', 'Bronze', 20);
INSERT INTO COMPOSITION VALUES ('Star', 'Platine', 20);
INSERT INTO COMPOSITION VALUES ('Star', 'Diamant', 20);
INSERT INTO COMPOSITION VALUES ('Star', 'Sucre', 1);

INSERT INTO COMPOSITION VALUES ('Vérité', 'Sucre', 10);
INSERT INTO COMPOSITION VALUES ('Vérité', 'Alcool', 50);
INSERT INTO COMPOSITION VALUES ('Vérité', 'Diamant', 13);

INSERT INTO COMPOSITION VALUES ('Cocaine', 'Alcool', 1);
INSERT INTO COMPOSITION VALUES ('Cocaine', 'E330', 100);
INSERT INTO COMPOSITION VALUES ('Cocaine', 'Sucre', 50);
INSERT INTO COMPOSITION VALUES ('Cocaine', 'Farine', 40);

INSERT INTO COMPOSITION VALUES ('Vin', 'Or', 3);
INSERT INTO COMPOSITION VALUES ('Vin', 'Alcool', 100);
INSERT INTO COMPOSITION VALUES ('Vin', 'Raisin', 20);
INSERT INTO COMPOSITION VALUES ('Vin', 'E330', 10);
INSERT INTO COMPOSITION VALUES ('Vin', 'Orange', 5);


-- modifications de table

-- question 2
-- permet de supprimer la contrainte sur la clé étrangère nomPotion
ALTER table COMPOSITION drop constraint SYS_C00478892;
-- permet de redéfinir la contrainte avec un trigger on delete cascade
ALTER table COMPOSITION add constraint supprComposition foreign key (nomPotion) references POTION(nomPotion) on DELETE CASCADE
DELETE from POTION where POTION.nomPotion NOT IN (select unique nomPotion from PRISEPOTION); -- nécessite les deux lignes du dessus pour fonctionner

-- question 3

DELETE from PATIENT where PATIENT.nomPatient in(SELECT nomVillageois from VILLAGEOIS
    where (profession in ('Barde', 'Poissonnier') and village = 'Lutèce'));

--question 4

DELETE from POTION where villeOrigine is NULL;

-- question 5

UPDATE VILLAGEOIS SET village = 'Armorique' where village = 'BR';


/* NOTES

la création d'un integer de base génère un number(38,0) càd 38 chiffres 0 décimales

le point virgule provoque une erreur, possibilité de ne pas renseigner une colonne en la mettant à NULL

double quote ne fonctionne pas

Quand on insère un tuple, si on ne spécifie pas tous les champs, on peut préciser le nom des champs que l'on remplit dans la commande
Apparemment les champs sont transformés en majuscule sous oracle (pas de prise en compte de la casse)

Lorsque les lignes sont séparées par un point virgule, il faut sélectionner les lignes à exécuter avant d'envoyer la requête

possibilité de modifier directement les tuples dans oracle en mode graphique

pour renseigner une date : date '0052-12-09' sous la forme 'yyyy-mm-dd'
pour renseigner une date sous un autre format on peut utiliser la fonciton to_date('01/01/0045','dd/mm/yyyy') 'dd/mm/yyyy' est le format de la date


erreur violation de contrainte unique correspond à une tentative de mettre une clé primaire déjà existante dans la base

Question 2, lorsque l'on tente des supprimer les potions qui ne sont pas administrées, on tombe sur cette erreur
erreur violation de contrainte (E168386D.SYS_C00478892) d'intégrité - enregistrement fils existant
-> résolution : grâce au code d'erreur SYS_C00478892 nous avons pu remonter à la contrainte d'intégrité qui était violée lors de la requête
  identification du code grâce à l'outil contraintes des tables sous SQL_developer
  ce code correspond à une contrainte sur une clé étrangère dans la table composition en l'occurence la clé nomPotion que l'on souhaite supprimer

  une fois que l'on a ce code, on supprime la contrainte et on crée la même contrainte avec un trigger on delete cascade
  qui permet de supprimer automatiquement les lignes correspondant aux nomPotion que l'on supprime

  solution plus simple pour ne pas avoir à rechercher l'id de la contrainte : affecter un nom à chaque contrainte dès la création de la table

Pour actualiser un tuple, on utilise la commande update nomTable set nomCol = expr where prédicat

ALTER table modifie les colonnes et les contraintes de la table
UPDATE table modifie les données de la table²

impossibilité de consommer deux fois la même potion à des dates différentes car nomPatient, nomPotion est la clé primaire
pour résoudre le problème il faudrait ne pas définir de clé primaire

*/
