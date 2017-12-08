// **************************************************************
// Nom de l’auteur: Henrique Nascimento
// Version/Date: 02 décembre 2017
// Rôle: Étudiant
// **************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    int base = 16;
    long expectedResult = 16;
    baseADecimalCase("10", base, expectedResult);
    
	// Teste 2
	base = 2;
    expectedResult = 1025;
    baseADecimalCase("10000000001", base, expectedResult);

	// Teste 3
	base = 16;
    expectedResult = 1025;
    baseADecimalCase("401", base, expectedResult);

	// Teste 4
	base = 16;
    expectedResult = 255;
    baseADecimalCase("FF", base, expectedResult);

	// Teste 5
	base = 8;
    expectedResult = 25;
    baseADecimalCase("31", base, expectedResult);
	
}

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
	int base = 16;
	long d = 10;
	int expectedSize = 1;
	int expectedArray1[100] = {10};
	decimalABaseCase(base, d, expectedSize, expectedArray1);

	//Teste 2
	base = 2;
	d = 1025;
	expectedSize = 11;
	int expectedArray2[100] = {1,0,0,0,0,0,0,0,0,0,1};
	decimalABaseCase(base, d, expectedSize, expectedArray2);

	//Teste 3
	base = 16;
	d = 1025;
	expectedSize = 3;
	int expectedArray3[100] = {4,0,1};
	decimalABaseCase(base, d, expectedSize, expectedArray3);

	//Teste 4
	base = 16;
	d = 255;
	expectedSize = 2;
	int expectedArray4[100] = {15,15};
	decimalABaseCase(base, d, expectedSize, expectedArray4);

	//Teste 5
	base = 8;
	d = 25;
	expectedSize = 2;
	int expectedArray5[100] = {3,1};
	decimalABaseCase(base, d, expectedSize, expectedArray5);

}

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
