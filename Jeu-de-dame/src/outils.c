#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void swap(s_grille * g, int xDesti, int yDesti)
{
	int tmp = g->tabValeurs[g->x][g->y];
	g->tabValeurs[g->x][g->y] = g->tabValeurs[xDesti][yDesti];
	g->tabValeurs[xDesti][yDesti] = tmp;
	
}

char * recupFile()
{
    FILE * fd= fopen("sauve.txt","r");
    if(fd==NULL)
    {
        perror("Problème à l'ouverture du fichier.");
        exit(-1);
    }

    char * buffer = malloc(sizeof(char) * 100) ;
    if(buffer==NULL){exit(-1);}
        

    fread(buffer,sizeof(char),100, fd);
 
    fclose(fd);
    return buffer;
 
}

int tailleGrid(char * buffer)
{
    //Les tailles correspondent au format que prend la permutation dans le fichier
	if(strlen(buffer)==18)
	{
		return 3;
	}
	else if(strlen(buffer)==38)
	{
		return 4;
	}
	else if(strlen(buffer)==65)
	{
		return 5;
	}
	else {return -1;}
}

int ** tabToGrid(int n, int * permut)
{
	int i,j,k=0;
    n=10;
	int ** grille = creeTab2Dint(n);

	for(i=0;i<n;i++)
	{ 
		for(j=0;j<n;j++)
		{		
			grille[i][j]=permut[k];
			k++;
		}
	}

	return grille;	
}

int afficheMenu() 
{
    int choix; 
 
    printf("\n   ---Menu---\n\n");
    printf("1. Commencer à jouer\n");
    printf("2. Règles du jeu\n");
    printf("3. Charger la sauvegarde (coming soon!)\n");
    printf("4. Créer un compte\n");
    printf("5. Se connecter\n");
    printf("6. Quitter\n\n");

    printf("\nVotre choix ?\n");
    scanf("%d", &choix);
    return choix; 
}

void afficheGrille(s_grille grid)
{   
    int i,j;
    for(i=0;i<grid.taille;i++)
    { 
        for(j=0;j<grid.taille;j++)
        {   
            if(i%2==0 && j%2==0){
                printf("   | |   ");
            }
            else if(i%2!=0 && j%2==0)
            {
                printf("   |%d|   ", 1);
            }
            else if(i%2!=0 && j%2!=0)
            {
                printf("   | |   ");
            }
            else{
                printf("   |%d|   ", 1);
            }
            
        }
        printf("\n\n");
    }
  
}

int ** creeTab2Dint(int n)
{
        int **M;
        int i,d=0;
        M=(int**)malloc(n*sizeof(int*));
        if(M==NULL){exit(0);}
        for (i=0; i<n; i++)
        {
                M[i]= malloc (n*sizeof(int));
                if(M[i]==NULL)
                {
                    d=1;
                }
        }
        if(d==1)
        {
                for(i=0;i<n;i++)
                {
                        free(M[i]);
                }
                exit(0);
        }
 
        return M;
       
}

void libereTab(int ** tab, int n)
{
   	int i;
	for(i=0;i<n;i++)
	{
		free(tab[i]); tab[i]=NULL;
	}
	free(tab);
} 