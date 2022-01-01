#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"



int pariteCaseVide(s_permutation permut)
{    
    //On cherche le numéro de l'emplacement de la case vide
    int caseVide, i;
    for(i=0;i<permut.n;i++)
    {
        if(permut.tab[i]==0)
        {
            caseVide=i;
        }    
    }
    //Et on renvoie sa parité
    return (caseVide%2); //retourne 0 si pair, 1 sinon
}

int pariteTranslations(s_permutation permut)
{
    int i,j,tmp, compteur=0;

	//copie du tableau permut dans un tableau auxilliaire
	int *aux = malloc(permut.n*sizeof(int));
	for(i=0;i<permut.n;i++)
	{
		aux[i]=permut.tab[i];
	}
	
	//reconstitution de la permut identité 
	//et comptage du nombre de translation
    for(i=0;i<permut.n;i++)
    {
        for(j=i; j<permut.n; j++)
        {
            if(aux[j] == i+1)
            {
                tmp = aux[i];
                aux[i] = aux[j];
                aux[j] = tmp;
				
				if(i!=j)
                {compteur++;}
            }
        }
    }
	free(aux);aux=NULL;
    return (compteur%2); //retourne 0 si pair, 1 sinon
}

int * permutationIdentite(int n)
{
    int * t = malloc(n*sizeof(int)) ;
    int i ;
    if(t==NULL){exit(0);} ;

    for(i=0;i<n-1;i++)
    {
        t[i]=i+1 ;
    }
    t[n-1]=0;
    return t ;
}

int testSolubilite(s_permutation permut)
{
	int n=1;
	//si le num de la case vide et le nb de trans ont la m parite : ok
	if(pariteCaseVide(permut)==pariteTranslations(permut))
	{ n=0; }
    return n; //0 vaut "pas d'erreur"
}

int testPermut(s_permutation permut)
{
    int i ;
	//incrémentation des cases d'aux associées aux valeurs de permut
    int * aux= calloc(permut.n, sizeof(int)) ;
    if(aux==NULL){exit(0);}
    for(i=0;i<permut.n;i++)
    {
         aux[permut.tab[i]]++ ;
    }
	//verification de la presence de toutes les valeurs
    for(i=0;i<permut.n;i++)
    {
        if(aux[i]!=1)
        {
            free(aux);aux=NULL;
            return 1;
        }
    }
    free(aux);aux=NULL;
    return 0 ; //0 vaut "pas d'erreur"
}

int * permute(s_permutation permut)
{
    permut.tab = permutationIdentite(permut.n);
    int i, j, k, tmp;
    
	//mélange de permut identité jusqu'à validité et solubilité
    do
    {
        for(k=0;k<permut.n;k++)
        {
            i=rand()%permut.n;
            j=rand()%permut.n;
                
            tmp=permut.tab[i];
            permut.tab[i]=permut.tab[j];
            permut.tab[j]=tmp;
        }
    }while(!testPermut(permut)&&testSolubilite(permut));

    return permut.tab;
}

