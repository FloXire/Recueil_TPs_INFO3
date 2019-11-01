/* Fichier permettant de consulter les tables */

-- question 1

SELECT nomPotion, villeOrigine from POTION;

-- question 2

SELECT nomPotion from POTION where villeOrigine = 'Rome' and posologie > 5;

-- question 3

select * from(
        select * from
            (select VILLAGEOIS.VILLAGE, PRISEPOTION.NOMPATIENT, PRISEPOTION.NOMPOTION
                from VILLAGEOIS INNER JOIN PRISEPOTION ON PRISEPOTION.nomPatient = VILLAGEOIS.nomVillageois)
            Res
            INNER JOIN POTION ON potion.nompotion = Res.nomPotion)
    where village = villeOrigine
    group by nompatient having count(*) >= 2

-- NE MARCHE PAS !!!

-- question 4

select nompatient from prisepotion, potion
    where prisepotion.nompotion = potion.nompotion and potion.druidecreateur = 'Panoramix'
        and not exists
            (select unique nompatient from prisepotion, potion
             where prisepotion.nompotion = potion.nompotion and
                 potion.druidecreateur != 'Panoramix')

-- question 5

select nompatient from prisepotion, potion where prisepotion.nompotion = potion.nompotion
    and potion.genre not in ('magique', 'curatif')

-- question 6
-- variante avec "orange", "diamant", "citron"

select nompotion from potion
    where nompotion in
        (select potion.nompotion from potion, composition
            where potion.nompotion = composition.nompotion
            and composition.nomIngredient in ('Orange', 'Diamant', 'Citron'))
        or nompotion in
        (select potion.nompotion from potion, villageois
            where potion.druidecreateur = villageois.nomVillageois
            and villageois.nationalite = 'Gaulois')

-- question 7
-- les dates sont sous entendues comme négatives
select nomPotion from POTION where
    druideCreateur in ('Amnésix', 'Panoramix') and to_char(dateCreation, 'yy') = '52';

-- question 8
select * from PRISEPOTION where PRISEPOTION.nomPatient = 'Obélix'
    group by dateprise
        


/* NOTES



*/
