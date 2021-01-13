# Convole un outil de manipulation de matrice

## Format d'un fichier.mat 

 #CommentaireEnUnSeulMot  
 2 3  
 1.2 1.5   
 7.9   

### Remarques sur le format d'un fichier

Première ligne : ligne de commentaire, le commentaire ne doit pas contenir d'espace.  
  
Deuxième ligne : taille de la matrice  
  
	Nombre de lignes : ici 2.  
	Nombre de colonnes : ici 3.  
  
 Si il y'a moins de colonne sur une ligne que prévu c'est que les doubles manquants sont des zéros :   
  
	La première ligne est 1.2 1.3 0.0  
	La deuxième ligne est 7.9 0.0 0.0  
   
  
## Utilisation de l'outil convole : 

	$Convole  
-->Convole affichera une matrice 3x3 généré aléatoirement  

	$Convole 1 2 3 4  
--> Génére et affiche une matrice 1x2 puis 3x4.  

	$Convole a.mat b.mat  
--> Lit et affiche le contenu des fichiers a.mat et b.mat s'ils existent.  

	$Convole -l a.mat   
--> Lit et affiche la matrice contenu dans le fichier a.mat  

	$Convole -c t a.mat  
--> Transpose et affiche la transposé de la matrice contenu dans le fichier a.mat  

	$Convole -c + a.mat b.mat  
--> Calcule a + b et affiche le résultat  

	$Convole -c - a.mat b.mat  
--> Calcule a + b et affiche le résultat  


### Remarques sur l'utilisation de l'outil Convole : 

	
On peut coupler -l et -o de sorte à générer une matrice, l'enregister et visualiser le contenu du fichier :  

	$Convole 1 2 -o a.mat -l a.mat  

On peut rajouter l'option -o fichier.mat pour enregister le résultat de :   

Une génération de matrice unique.  
	
	exemple : $Convole 1 2 -o a.mat  
	
	
Un calcul (transposition, +, -)  

	Exemple : $Convole -c - a.mat b.mat -o aplusb.mat  

	

