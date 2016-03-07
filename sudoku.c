#include <stdio.h>
#include <stdlib.h>
#define MAX 9


void afficher(int t[MAX][MAX])
//affiche un tableau à 2 dimensions
{
    int i,j,k;

    for(i=0;i<MAX;i++)
    {
        for(k=0;k<MAX;k++)
            printf("+---");

        printf("+\n");

        for(j=0;j<MAX;j++)
        {
            if(t[i][j]==0)printf("|   ");
            else printf("| %d ",t[i][j]);
        }

    printf("|\n");
    }
    for(k=0;k<MAX;k++)
        printf("+---");
    printf("+\n");
}

int erreur(int t[])
//prend 10 valeurs et verifie qu'il n'y en ai pas 2 ou plus de la meme valeur, de 1 à 9
{
    int k;
    for(k=1;k<=9;k++)
    {
        if(t[k]>1)
        {
            printf("ERREUR: Il y a plusieurs '%d' ",k);
            return 1;
        }
    }
    return 0;
}

int verifier(int t[MAX][MAX])
{
    //verifie que les valeurs ne dépassent pas 9 (MAX)
    int i,j,k,valeurs[10]={0,0,0,0,0,0,0,0,0,0},petitCarre;
    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            if(t[i][j]>MAX)
            {
                printf("Les valeurs du tableau ne sont pas correctes (ligne %d, colonne %d\n",i+1,j+1);
                return 1;
            }

        }
    }

    //control des lignes avec la fonction erreur()
    for(i=0;i<MAX;i++)
    {
        int valeurs[10]={0,0,0,0,0,0,0,0,0,0};
        for(j=0;j<MAX;j++)
        {
            valeurs[t[i][j]]++;
        }
        for(k=1;k<=MAX;k++)
        {
            //if(valeurs[k]>0)printf("Nombre de %d sur la ligne %d: %d \n",k,i+1,valeurs[k]);
            if(erreur(valeurs))
            {
                printf("sur la ligne %d\n",i+1);
                return 1;
            }
        }
    }
    //controle des colonnes
    for(j=0;j<MAX;j++)
    {
        int valeurs[10]={0,0,0,0,0,0,0,0,0,0};
        for(i=0;i<MAX;i++)
        {
            valeurs[t[i][j]]++;
        }
        for(k=1;k<=MAX;k++)
        {
            //if(valeurs[k]>0)printf("Nombre de %d sur la colonne %d: %d \n",k,j+1,valeurs[k]);
            if(erreur(valeurs))
            {
                printf("sur la colonne %d\n",j+1);
                return 1;
            }
        }
    }
    //controle des 9 carrés
    for(petitCarre=0;petitCarre<9;petitCarre++)
    {
        int valeurs[10]={0,0,0,0,0,0,0,0,0,0};
        for(i=(petitCarre/3)*3;i<(petitCarre/3)*3+3;i++)
        {
            for(j=(petitCarre%3)*3;j<(petitCarre%3)*3+3;j++)
                valeurs[t[i][j]]++;
        }
        //for(k=1;k<=MAX;k++)if(valeurs[k]>0)printf("Nombre de %d sur le carre %d: %d \n",k,petitCarre+1,valeurs[k]);
        if(erreur(valeurs))
        {
            printf("sur le carre %d\n",petitCarre+1);
            return 1;
        }
    }

    return 0;
}


int disponible(int ligne, int colonne, int grille[MAX][MAX])
//verifie combien de valeurs sont possibles pour une case donnée et renvoie la valeur en question si elle est unique.
//ne renvoie rien si il existe plusieurs valeurs, et renvoie 0 si la case est deja remplie.
{
    int i,j,carre,nbrDispo=0,chiffreDispo=0;
    int dispo[9]={0,0,0,0,0,0,0,0,0};
    if (grille[ligne][colonne]!=0)return 0;

    //verifie les differentes valeurs possible sur chaque ligne
    for(i=0;i<9;i++)
    {
        if (grille[ligne][i]!=0)dispo[grille[ligne][i]-1]=grille[ligne][i];
    }

    //verifie les differentes valeurs possible sur chaque colonne
    for(j=0;j<9;j++)
    {
        if (grille[j][colonne]!=0)dispo[grille[j][colonne]-1]=grille[j][colonne];
    }

    //verifie les 9 carrés
    carre=(((ligne/3)*3)+colonne/3); //("carre" represente lequel des 9 carrés est concerné, allant de 0 à 8 (de gauche à droite, de haut en bas)
    for(i=(carre/3)*3;i<(carre/3)*3+3;i++)
    {
        for(j=(carre%3)*3;j<(carre%3)*3+3;j++)
            dispo[grille[i][j]-1]=grille[i][j];
    }


    for(i=0;i<9;i++)
    {
        if(dispo[i]==0)nbrDispo++;
    }
    //printf("Il y a %d possibilites: ",nbrDispo);

    for(i=0;i<9;i++)
    {
        if(dispo[i]==0)
        {
            //printf("%d ",i+1);
            chiffreDispo=i+1;
        }

    }
    if(nbrDispo==1)return chiffreDispo;


    return 0;

}

int remplir(int tab[MAX][MAX])
//rempli toutes les cases du tableau ou il existe qu'une possibilité (grace à disponible()
{
    int i,j,reponse=0;
    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            reponse=disponible(i,j,tab);

            if(reponse>0)
            {
                printf("ligne %d, colonne %d, ajout de : %d\n",i+1,j+1,reponse);
                tab[i][j]=reponse;
            }
        }
    }
return 0;
}

int casesVides(int t[MAX][MAX])
//renvoie 1 si il existe au moins une case vide, sinon renvoie 0
{
    int i,j;
    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            if(t[i][j]==0)
            {
                return 1;
            }
        }
    }

    return 0;

}

int main()
{
    int depart[]={1,7,5,1,8,9,
                  2,3,4,2,4,3,2,7,1,
                  3,1,6,3,3,1,3,4,4,3,5,7,3,6,5,3,7,8,3,8,2,
                  4,6,9,4,9,6,
                  5,1,2,5,4,5,5,5,3,5,6,8,5,9,9,
                  6,1,3,6,4,7,
                  7,2,6,7,3,3,7,4,2,7,5,8,7,6,7,7,7,9,7,9,1,
                  8,3,7,8,6,1,8,7,3,
                  9,2,2,9,3,8};
    int tab[MAX][MAX];
    int possible[80][10];
    int i,j,nbrDepart,ligne,colonne,valeur;

    if((sizeof(depart)/sizeof(int))%3 != 0)
    {
        printf("ERREUR DANS LE TABLEAU!!!!!\n");
        return 1;
    }

    nbrDepart = ((sizeof(depart)/sizeof(int))/3);

    //met toutes les valeurs de tab[] à 0:
    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            tab[i][j]=0;

        }
    }

    printf("grille\n");


    // rempli le tableau tab[] avec les valeurs dans depart[]:
    for(i=0;i<nbrDepart*3;i=i+3)
    {
        ligne=depart[i]-1;
        colonne=depart[i+1]-1;
        valeur=depart[i+2];
        tab[ligne][colonne]=valeur;
    }
    printf("il y a %d valeurs dans le tableau\n",nbrDepart);

    //verifie si le tableau contient une erreur
    if(verifier(tab))
    {
        afficher(tab);
        return 1;
    }

    afficher(tab); //affiche le tableau tel qu'il est au début.

    while(casesVides(tab))
    //tant qu'il reste des cases vides, faire:
    {

        getchar();//appuyer sur entree pour faire avancer la boucle
        printf("\n");
        remplir(tab);
        afficher(tab);
        printf("\n");
    }

    return 0;
}

