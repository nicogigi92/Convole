# Convole un outil de manipulation de matrice

### format d'un fichier.mat ###

#CommentaireEnUnSeulMot
2 3
1.2 1.5 
7.9 

### format d'un fichier.mat ###
remarque : 
  - premiere ligne : ligne de commentaire, le commentaire ne doit pas contenir d'espace.
  - deuxième ligne : ligne de taille de la matrice, nombre de lignes (ici 2) de colonnes de la matrice (ici 3).
  - le reste : doubles qui composent la matrice, si il y'a moins de colonne sur une ligne que prévu c'est que les doubles mannquant sont des zéro (ici la première ligne est 1.2 1.3 0.0 et la deuxième ligne est 7.9 0.0 0.0)
  
### utilisation de l'outil convole ###

$Convole 
-->Convole affichera une matrice 3x3 généré aléatoirement

$Convole 1 2 3 4
--> générera et affichera une matrice 1x2 puis 3x4.

$Convole a.mat b.mat
--> lit et affiche le contenu des fichiers a.mat et b.mat s'ils existent.

$Convole 5x5 -o a.mat 
--> génère une matrice 5x5 et l'enregistre dans le fichier a.mat 

$Convole 5x5 -o a.mat -k commentaireàajouter
--> génère une matrice 5x5 et l'enregistre dans le fichier a.mat en ajoutant le commentaire "commentaireàajouter"

$Convole -l a.mat 
--> lit et affiche la matrice contenu dans le fichier a.mat

### utilisation de l'outil convole ###
