/* Fichier permettant de créer les tables */

CREATE table VILLAGEOIS
(
  nomVillageois varchar(30) primary key,
  prenom varchar(30),
  sexe char,
  age integer check(age >= 0),
  -- vérifie que l'age est un nombre positif
  profession varchar(30),
  village varchar(30),
  nationalite varchar(30),
  constraint sexe check(sexe = 'M' OR sexe = 'F')
);

CREATE table PATIENT
(
  nomPatient varchar(30) primary key,
  druideTraitant varchar(30),
  foreign key(nomPatient) references VILLAGEOIS(nomVillageois),
  foreign key(druideTraitant) references VILLAGEOIS(nomVillageois)
);

CREATE table POTION
(
  nomPotion varchar(30) primary key,
  posologie integer,
  villeOrigine varchar(30),
  druideCreateur varchar(30),
  genre varchar(30),
  dateCreation date,
  -- la date de creation est un champ de type date
  foreign key(druideCreateur) references VILLAGEOIS(nomVillageois)
);

CREATE table PRISEPOTION
(
  nomPatient varchar(30),
  nomPotion varchar(30),
  datePrise date,
  primary key(nomPatient, nomPotion),
  foreign key(nomPatient) references PATIENT(nomPatient),
  -- permet de s'assurer que le patient est présent dans la table PATIENT
  foreign key(nomPotion) references POTION(nomPotion)
);

-- La table INGREDIENT doit être insérée avant la table COMPOSITION car cette dernière a une clé étrangère pointant vers la table INGREDIENT
CREATE table INGREDIENT
(
  nomIngredient varchar(30) primary key,
  villeOrigine varchar(30),
  type varchar(30)
);

CREATE table COMPOSITION
(
  nomPotion varchar(30),
  nomIngredient varchar(30),
  quantiteUtilisee integer,
  primary key(nomPotion, nomIngredient),
  foreign key(nomPotion) references POTION(nomPotion),
  foreign key(nomIngredient) references INGREDIENT(nomIngredient)
);

-- note : ne pas oublier de mettre des ; entre chaque commande
-- note2 : ne pas inclure de commentaires dans les commandes

