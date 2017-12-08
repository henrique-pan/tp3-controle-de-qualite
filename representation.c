// **************************************************************
// Nom de l’auteur: Henrique Nascimento
// Version/Date: 02 décembre 2017
// Rôle: Étudiant
// **************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "representation.h"

// *****************************************************************************
// Representation constructeur(int taille, int base)
//
// Fabrique une representation de taille taille en base base et initialise son
// tableau nombre avec la taille taille.
//
// Postcondition :
//     nb->nombre doit etre libere avec un free
//
// INPUT :
//     int taille:
//         La taille du nombre a fabriquer
//     long base :
//         La base du nombre a fabriquer
//
// OUTPUT :
//     Representation nb avec
//         nb->base = base,
//         nb->taille = taille
//         nb->nombre = un tableau de longueur taille. Son contenu n'est pas
//             initialise. Il peut etre nul, il peut etre autre chose. Seule
//             sa taille est garantie.
//
// Exemples :
//     constructeur(2, 16) = {{0,0}, 2, 16}
//     constructeur(11, 2) = {{0,0,0,0,0,0,0,0,0,0,0}, 11, 2}
//     constructeur(3, 16) = {{0,0,0}, 3, 16}
//     constructeur(2,  8) = {{0,0}, 2, 8}
//
// *****************************************************************************
Representation constructeur(int taille, int base)
{
    Representation nb;
    nb.base = base;
    nb.taille = taille; 
    //nb.nombre = (int *) malloc (sizeof(int)*nb.taille);
    nb.nombre = (int *) calloc(nb.taille, sizeof(int));
    if (nb.nombre == NULL)
    {
	   fprintf(stderr, "ALLOCATION DE MEMOIRE ECHOUEE\n");
	   exit(0);
    }
    return nb;
}

// *****************************************************************************
// Representation traduireEntree(char* chaine, int base)
//
// Prend une chaine de caracteres (chaine) qui represente un nombre dans la base
// base fabrique une represnetation nb. La fonction met les indices appropries
// dans nb.nombre. Si chaine comprend des symboles qui depassent la base base,
// un message d'erreur est affiche et le programme s'arrete. L'appeleur est
// responsable de liberer la memoire utilisee par nb.nombre.
//
// Cette fonction est utile si on veut lire un nombre dans une base autre que
// la base 10.
//
// INPUT :
//     char* chaine :
//         Une chaine de caractere contenant un nombre dans la base base.
//     int base : 
//         La base dans laquelle est ecrite chaine.
//
// OUTPUT :
//     Une reprensentation du nombre entre dans la meme base.
//
// Exemples :
//     traduireEntree("FF1", 16) = ({15, 15, 1}, 3, 16)
//     traduireEntree("10001", 2) = ({1, 0, 0, 0, 1}, 5, 2)
//     traduireEntree("9", 8) = ERREUR 9 n'est pas un symbole dans la base 8.
//
// *****************************************************************************
Representation traduireEntree(char* chaine, int base)
{
    Representation nb = constructeur(strlen(chaine), base);
    for (int i = 0 ; i < nb.taille ; i++)
    {
    	int ind = 0;
    	while (SYMBOLES[ind] != chaine[i])
    	{
    	    ind++;
    	    if (ind >= nb.base)
    	    {
        		fprintf(stderr, "SYMBOLES '%c' INVALIDE POUR LA BASE %d\n", chaine[i], nb.base);
        		exit(0);
    	    }
    	    
    	}
    	nb.nombre[i] = ind;
    }
    return nb;
}

// *****************************************************************************
// Representation decimalABase(int baseCible, long valeurSource)
//
// Fabrique une representation pour un nombre de valeur valeurSource et en base
// baseCible. L'appeleur est responsable de liberer la memoire utilisee par
// nb->nombre. la variable valeurSource doit etre une valeur en decimal.
//
// Préconditions :
//     baseCible doit etre entre 2 et BASE_MAX
//
// Postcondition :
//     nb->nombre doit etre libere avec un free
//
// INPUT :
//     int baseCible :
//         La base cible
//     long valeurSource :
//         La valeur en decimal qu'on doit traduire dans la base cible
//
// OUTPUT :
//     Representation nb avec
//         nb->base = baseCible,
//         nb->taille = longueur du nombre et
//         nb->nombre = un tableau dans le tas contenant la representation en
//             base baseCible de valeurSource.
//
// Exemples :
//     decimalABase(16,   10) = {{10}, 1, 16}
//     decimalABase( 2, 1025) = {{1,0,0,0,0,0,0,0,0,0,1}, 11, 2}
//     decimalABase(16, 1025) = {{4,0,1}, 3, 16}
//     decimalABase(16,  255) = {{15,15}, 2, 16}
//     decimalABase( 8,   25) = {{3,1}, 2, 8}
//
// *****************************************************************************
Representation decimalABase(int base, long valeur)
{   
    long result = valeur;
    int temp[100];
    int size = 0;

    do {        
        int remain = result % base;
        result = (result / base);    
        temp[size] = remain;
        size++;
    } while(result != 0);

    Representation nb = constructeur(size, base); 
    for (int i = 0, j = (size - 1); i < size; ++i, j--) {
        nb.nombre[i] = temp[j];        
    }    
      
    return nb;
}

// *****************************************************************************
// long baseADecimal(Representation* nb)
//
// Fabrique une representation pour un nombre de valeur valeurSource et en base
// baseCible.  la representation place son nombre dans le tas avec un
// malloc. L'appeleur est responsable de liberer la memoire utilisee. la
// variable valeurSource doit etre une valeur en decimal.
//
// Préconditions :
//     baseCible doit etre entre BASE_MIN et BASE_MAX
//
// Postconditions :
//     nb->nombre doit etre libere avec un free
//
// INPUT :
//     int baseCible :
//         La base cible
//     long valeurSource :
//         La valeur en decimal qu'on doit traduire dans la base cible
//
// OUTPUT :
//     Representation nb avec
//         nb->base = baseCible,
//         nb->taille = longueur du nombre et
//         nb->nombre = un tableau dans le tas contenant la representation en
//             base baseCible de valeurSource.
//
// Exemples :
//     baseADecimal({{10}, 1, 16}) = 16
//     baseADecimal({{1,0,0,0,0,0,0,0,0,0,1}, 11, 2}) = 1025
//     baseADecimal({{4,0,1}, 3, 16}) = 1025 
//     baseADecimal({{15,15}, 2, 16}) = 255
//     baseADecimal({{3,1}, 2, 8}) = 25
//
// *****************************************************************************
long baseADecimal(Representation* nb)
{ 
    int *v = (*nb).nombre;
    int size = (*nb).taille;
    int base = (*nb).base;

    long result = 0;

    for(int i = 0, j = (size - 1); i < size; i++, j--) {
        int p = (int) pow((double) base, j);
        result += (v[i] * p);
    }

    return result;
}
