#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void menu()
{
    int s;
    switch (afficheMenu()) 
    {
    case 1:
        printf("Vous avez choisi de commencer à jouer !\n\n");
        start(1);
        break; 
 
    case 2:   
        system("clear");
        
        printf("Vous avez choisi lire les Règles du jeu !\n\n");
        printf("Déplacez vous en diagonal sur les cases vides.\n Mangez un pion adverse si une case libre le précède.\n Mangez tous les pions adverses.\n"

		"\nÀ vous de jouer !\n");
        menu();
	break;
 
    case 3:
        printf("Vous avez choisi de continuer depuis la sauvegarde !\n Mais ce n'est pas du tout implémenté :/\n");
        start(2);
	break;

    case 4:
        printf("Vous avez choisi de créer un nouveau compte !\n");
        start(2);
	break;

    case 5:
        printf("Connectez-vous à partir d'un compte déjà existant !\n");
        start(2);
	break;
 
    case 6:
        printf("Appuyez de nouveau sur 6 pour confirmer.\n"); 
        scanf("%d",&s);
	if(s==6)
	{
        	system("clear");
		exit(0);
	}
	else
	{
		system("clear");
		menu();
	}
        break;
	
    default:
	system("clear");
	menu();
        break;
    }
}



void mouvement (s_grille * g, struct pion p, char *to)
{
	//Change le pion de place
}

int victoire(s_grille * grid)
{	
	//Si nombre de pions d'un joueur = 0 alors victoire
}



void start()
{
	int i,j,n=10;
	s_grille grid;
	s_permutation melange;

		grid.taille=n; 
		grid.tabValeurs=tabToGrid(grid.taille,permute(melange));

	
	//init de la case vide 
    	for(i=0;i<grid.taille;i++){
			for(j=0;j<grid.taille;j++){
        		if(grid.tabValeurs[i][j]==0){
					grid.x=i;
					grid.y=j;	
        		}
			}    
    	}


	//Placer les pions
	    /*for(i=1;i<grid.taille;i+=2){
			for(j=0;j<grid.taille;j++){
				printf("p");
			}    
    	}*/
	
	for(;!victoire(&grid);)
	{	
		sauve(&grid);
		afficheGrille(grid);
		mouvement(&grid);
		system("clear");
	}

	afficheGrille(grid);
	printf("Vous avez gagné!\n");
	libereTab(grid.tabValeurs,grid.taille);

	//retour au menu
	menu();
}
