// **************************************************************
// Nom de l’auteur: Claude Bernard & Henrique Nascimento
// Version/Date: 02 décembre 2017
// Rôle: Étudiants
// **************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "representation.h"
#include "representationTest.h"

void baseADecimalCase(char *decimalString, int base, long expectedResult);
void decimalABaseCase(int base, long d, int expectedSize, int *expectedArray);

//******************************************************************
// void baseADecimalTest()
//
// Tests unitaires pour la fonction
// long baseADecimal(Representation* nb)
//
//******************************************************************
void baseADecimalTest() {

	// Teste 1
    int base = 2;
    long expectedResult = 91635;
    baseADecimalCase("10110010111110011", base, expectedResult);

    // Teste 2
    base = 4;
    expectedResult = 97872;
    baseADecimalCase("113321100", base, expectedResult);
    
	// Teste 3
	base = 8;
    expectedResult = 2455;
    baseADecimalCase("4627", base, expectedResult);

	// Teste 4
	base = 10;
    expectedResult = 94889;
    baseADecimalCase("94889", base, expectedResult);

	// Teste 5
	base = 14;
    expectedResult = 2455;
    baseADecimalCase("C75", base, expectedResult);

	// Teste 6
	base = 24;
    expectedResult = 97937;
    baseADecimalCase("720H", base, expectedResult);

    // Teste 7
	base = 32;
    expectedResult = 142609;
    baseADecimalCase("4B8H", base, expectedResult);

	// Teste 8
	base = 36;
    expectedResult = 66209;
    baseADecimalCase("1F35", base, expectedResult);

	// Teste 9
	base = 60;
    expectedResult = 59249;
    baseADecimalCase("GRT", base, expectedResult);
	
    // Teste 10
	base = 10;
    expectedResult = 1;
    baseADecimalCase("1", base, expectedResult);

    // Teste 11
	base = 10;
    expectedResult = LONG_MAX;
    baseADecimalCase("9223372036854775807", base, expectedResult);

    // Teste 12
	base = 10;
    expectedResult = 0;
    baseADecimalCase("0", base, expectedResult);
}

// *****************************************************************************
// void baseADecimalCase(char *decimalString, int base, long expectedResult)
//
// Function qui facilite la creation de cas de teste.
// Elle reçoit les paramètres et fait la validation.
//
// INPUT :
//     char *decimalString:
//         Le chiffre comme String
//     int base :
//         La base du chiffre entré
//	   long expectedResult:
//         Le resultat atendu après de la convertion
//
// OUTPUT :
// 		"printf" dans le cas d'échèque.
//
// Exemples :
//     baseADecimalCase("10110010111110011", 2, 91635);
//
// *****************************************************************************
void baseADecimalCase(char *decimalString, int base, long expectedResult) {
	char mot[256];
	strcpy(mot, decimalString);
	Representation nb = traduireEntree(mot, base);
	long d = baseADecimal(&nb);
	free(nb.nombre);
	if(d != expectedResult) {
		printf("%s à la base %d doit être égal à %ld: %ld\n\n", mot, base, expectedResult, d);
	} 
}

//******************************************************************
// void decimalABaseTest()
//
// Tests unitaires pour la fonction
// Representation decimalABase(int base, long valeur)
//
//******************************************************************
void decimalABaseTest() {
	//Teste 1
	int base = 2;
	long d = 91635;
	int expectedSize = 17;
	int expectedArray1[17] = {1,0,1,1,0,0,1,0,1,1,1,1,1,0,0,1,1};
	decimalABaseCase(base, d, expectedSize, expectedArray1);

	//Teste 2
	base = 4;
	d = 97872;
	expectedSize = 9;
	int expectedArray2[9] = {1,1,3,3,2,1,1,0,0};
	decimalABaseCase(base, d, expectedSize, expectedArray2);

	//Teste 3
	base = 8;
	d = 2455;
	expectedSize = 4;
	int expectedArray3[4] = {4,6,2,7};
	decimalABaseCase(base, d, expectedSize, expectedArray3);

	//Teste 4
	base = 10;
	d = 94889;
	expectedSize = 5;
	int expectedArray4[5] = {9,4,8,8,9};
	decimalABaseCase(base, d, expectedSize, expectedArray4);

	//Teste 5
	base = 12;
	d = 2455;
	expectedSize = 4;
	int expectedArray5[4] = {1,5,0,7};
	decimalABaseCase(base, d, expectedSize, expectedArray5);

	//Teste 6
	base = 3;
	d = 97937;
	expectedSize = 11;
	int expectedArray6[11] = {1,1,2,2,2,1,0,0,0,2,2};
	decimalABaseCase(base, d, expectedSize, expectedArray6);

	//Teste 7
	base = 7;
	d = 142609;
	expectedSize = 7;
	int expectedArray7[7] = {1,1,3,2,5,2,5};
	decimalABaseCase(base, d, expectedSize, expectedArray7);

	//Teste 8
	base = 6;
	d = 66209;
	expectedSize = 7;
	int expectedArray8[7] = {1,2,3,0,3,0,5};
	decimalABaseCase(base, d, expectedSize, expectedArray8);

	//Teste 9
	base = 11;
	d = 59249;
	expectedSize = 5;
	int expectedArray9[5] = {4,0,5,7,3};
	decimalABaseCase(base, d, expectedSize, expectedArray9);

	//Teste 10
	base = 2;
	d = 1;
	expectedSize = 1;
	int expectedArray10[1] = {1};
	decimalABaseCase(base, d, expectedSize, expectedArray10);

	//Teste 11
	base = 2;
	d = 9223372036854775807;
	expectedSize = 63;
	int expectedArray11[63] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	decimalABaseCase(base, d, expectedSize, expectedArray11);

	//Teste 12
	base = 2;
	d = 0;
	expectedSize = 1;
	int expectedArray12[1] = {0};
	decimalABaseCase(base, d, expectedSize, expectedArray12);
}

// *****************************************************************************
// void decimalABaseCase(int base, long d, int expectedSize, int *expectedArray)
//
// Function qui facilite la creation de cas de teste.
// Elle reçoit les paramètres et fait la validation.
//
// INPUT :
//     int base:
//         La base du chiffre decimal
//     long d :
//         Le decimal
//	   int expectedSize:
//         La taille du tableau de la structure Representation
//     int *expectedArray:
//         Le tableau des elements de la Representation
//
// OUTPUT :
// 		"printf" dans le cas d'échèque.
//
// Exemples :
//     decimalABaseCase(11, 59249, 5, {4,0,5,7,3});
//
// *****************************************************************************
void decimalABaseCase(int base, long d, int expectedSize, int *expectedArray) {
	Representation n = decimalABase(base, d);
	free(n.nombre);

	if(n.taille != expectedSize) {
		printf("La taille de la representation doit être égal à %d: %d\n", expectedSize, n.taille);
		return;
	}

	if(n.base != base) {
		printf("La taille de la representation doit être égal à %d: %d\n", base, n.base);
		return;
	}

	for(int i = 0; i < n.taille; i++) {
		if(n.nombre[i] != expectedArray[i]) {
			printf("La representation du nombre n'est pas validepour le cas: (base = %d, decimal = %ld)\n", base, d);
			break;
		}
	}
}
