/* Fichier permettant de créer les tables */

/*
exemple de création de table

CREATE TABLE utilisateur
(
    id INT PRIMARY KEY NOT NULL,
    nom VARCHAR(100),
    prenom VARCHAR(100),
    email VARCHAR(255),
    date_naissance DATE,
    pays VARCHAR(255),
    ville VARCHAR(255),
    code_postal VARCHAR(5),
    nombre_achat INT
)
*/

CREATE table VILLAGEOIS
(
  nomVillageois varchar(30) primary key,
  prenom varchar(30),
  sexe char,
  age integer check(age >= 0), -- vérifie que l'age est un nombre positif
  profession varchar(30),
  village varchar(30),
  nationalite varchar(30)
);

CREATE table PATIENT
(
  nomPatient varchar(30) primary key,
  druideTraitant varchar(30),
  foreign key(nomPatient) references VILLAGEOIS(nomVillageois)
);

CREATE table POTION
(
  nomPotion varchar(30) primary key,
  posologie varchar(200),
  villeOrigine varchar(30),
  druideCreateur varchar(30),
  genre varchar(30),
  dateCreation date -- la date de creation est un champ de type date
);

CREATE table PRISEPOTION
(
  nomPatient varchar(30),
  nomPotion varchar(30),
  datePrise date,
  primary key(nomPatient, nomPotion),
  foreign key(nomPatient) references PATIENT(nomPatient) -- permet de s'assurer que le patient est présent dans la table PATIENT
);

CREATE table COMPOSITION
(
  nomPotion varchar(30),
  nomIngredient varchar(30),
  quantiteUtilisee integer,
  primary key(nomPotion, nomIngredient),
  foreign key(nomPotion) references POTION(nomPotion)
);

CREATE table INGREDIENT
(
  nomIngredient varchar(30) primary key,
  villeOrigine varchar(30),
  type varchar(30)
);

-- note : ne pas oublier de mettre des ; entre chaque commande
-- note2 : ne pas inclure de commentaires dans les commandes
