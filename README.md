# Jeu-de-dame
[1]F.
Pour faire le jeu de dame je m'inspire du jeu de taquin qu'on avait fait l'année dernière.
Pour le moment surtout pour :
- MakeFile, 
- menu, 
- les grilles,
- les permutations(euuuuuuuuuuuuuuh non ?).

Explications :
- 0 pour cases blanches, 1 pour noires.

Problèmes :
- Le menu s'affiche 2 fois
- Les valeurs du tableaux doivent être que des 0 et des 1. OKAY
- Placer les pions sur les cases noires -> 20 + 20 (40 pions au total)
    Donc 1 remplacés en P or plus tard quand P va bouger des 1 doivent réapparaitre ?
    Pas sûre de ça... TRop compliqué pour ce que c'est.
    Mieux vaut peut-être utiliser SDL


Liens utiles pour SDL :
https://www.youtube.com/watch?v=Lwx9rSgwoDg&t=413s
https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/la-sdl/#1-presentation-de-la-sdl





Notes pour moi :
Les pions peuvent avancer que d'une case en diagonale.
Ils ne peuvent pas aller en arrière
Pour 'manger' un pion adverse il faut que la case (dans la ligne diagonale) après 
le pion A doit être vide. Le pion peut donc ensuite sauter sur le pion A et le manger.


[2]E.
Dans le main,
- On initialise le serv et le cli
- On lance le jeu
- On ferme si un joueur déco ou si partie finie
- Et puis quoi ? Qui joue ? Les spec ? On demande si revanche ? On relance tout ? 

Dans server, 
- fonctions d'initialisation
- 
