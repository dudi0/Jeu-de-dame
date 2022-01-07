#ifndef HEADER_h
#define HEADER_h

struct grille
{
	int taille;
	int x;
	int y;
	int ** tabValeurs;
};
typedef struct grille s_grille;

struct permutation
{
	int n;
	int * tab;
};
typedef struct permutation s_permutation;

#endif

//PROTOTYPES//

//jeu.c
void entree();
void menu();
void start();
void mouvement(s_grille * g);
int victoire(s_grille * grid);

//outils.c
int afficheMenu();
void afficheGrille(s_grille grid);
void libereTab(int ** tab, int n);
int ** creeTab2Dint(int n);
void swap(s_grille *g, int xDesti, int yDesti);
int ** tabToGrid(int n, int * permut);
char * recupFile();
int tailleGrid(char * buffer);

//generePermutation.c
int pariteCaseVide(s_permutation permut);
int pariteTranslations(s_permutation permut);
int * permutationIdentite(int n);
int testValidite(s_permutation permut);
int * permute(s_permutation permut);
