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
        printf("Vous avez choisi de Commencer à jouer !\n\n");
        start(1);
        break; 
 
    case 2:   
        system("clear");
        
        printf("Vous avez choisi lire les Règles du jeu !\n\n");
        printf("Mettre règles du jeu du jeu de dame\n"

		"\nÀ vous de jouer !\n");
        menu();
	break;
 
    case 3:
        printf("Vous avez choisi de continuer depuis la sauvegarde !\n");
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
        printf("Appuyez de nouveau sur 6 pour confirmer vouloir quitter notre super jeu D:\n"); 
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



void mouvement (s_grille * g)
{
	char dir;
	printf("Votre coup : ");
	scanf("%c",&dir);
	if((dir=='d')&&((g->y-1)>=0))
	{
		swap(g,g->x,g->y-1);
    		g->y=g->y-1;
	}
	else if((dir=='g')&&((g->y+1)<g->taille))
	{
		swap(g,g->x,g->y+1);
    		g->y=g->y+1;
	}
	else if((dir=='b')&&((g->x-1)>=0))
	{
		swap(g,g->x-1,g->y);
    		g->x=g->x-1;
	}
	else if((dir=='h')&&((g->x+1)<g->taille))
	{
		swap(g,g->x+1,g->y);
    		g->x=g->x+1;
	}
	else
	{
		printf("\n");
	}
}

int victoire(s_grille * grid)
{	
	int i, j;
	//création d'une grille identité à comparer avec la grille courante
	int ** identite = tabToGrid(grid->taille, permutationIdentite(grid->taille*grid->taille));
	for(i=0;i<grid->taille;i++)
	{
		for(j=0;j<grid->taille;j++)
		{
			if(identite[i][j]!=grid->tabValeurs[i][j])
			{
				libereTab(identite,grid->taille);
				return 0 ; //0 vaut "faux"
			}
		}
	}
	libereTab(identite, grid->taille);
	
	return 1; //1 vaut true
}

int charge(s_permutation * permut)
{
	int i;
	char * saveBloc = recupFile();
	int nGrid=tailleGrid(saveBloc);
	permut->n=nGrid*nGrid;

    	const char * delim =";";
    	permut->tab[0]= atoi(strtok(saveBloc, delim));
    
    	for(i=1;i<permut->n;i++)
    	{
        	permut->tab[i]=atoi(strtok(NULL, delim));
		i++;
    	}
	return nGrid;
}

void sauve(s_grille * grid) 
{
        FILE *fichier = fopen("sauve.txt", "w+");
	if(fichier==NULL){exit(0);}

        int i,j;

        for(i=0; i<grid->taille; i++)
        {
                for(j=0; j<grid->taille; j++)
                {
                        fprintf(fichier, "%d;", grid->tabValeurs[i][j]);
                }
        }
        rewind(fichier); 

        fclose(fichier);
	
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