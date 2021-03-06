#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#include <ctype.h>
#include "CatClis.h"


/*Structs*/
struct cli {
	char* codCli;
	int flag;
};

struct cat_clis {
	int validos;
	int total;
	AVL clis;
};


/*Operações sobre clientes*/
Boolean validaCliente (char* cliente) {	/* devolve 1 quando o cliente é válido*/
	if (!isupper(cliente[0])) return false; 
	
	if (cliente[1] == '5') {	/*único nº com 1º algarismo = 5 é o 5000*/
		for (int i = 2; i < 5; i++)
			if (cliente[i] != '0') return false;
	}
	else if (cliente[1] >= '1' && cliente[1] <= '4') {	/*válido entre 1000 e 5000*/
		for (int i = 2; i < 5; i++)
			if (!isdigit(cliente[i])) return false;
	} else return false;	/*primeiro algarismo > 5*/

	return true;
}

Cliente criaCli (char* codCli) {
	Cliente c = malloc(sizeof(struct cli));
	c->codCli = strdup(codCli);
	c->flag = 0;
	return c;
}

void free_Cli (Cliente c) {
	free(c->codCli);
	free(c);
}

int comparaClis (Cliente c1, Cliente c2) {
	return strcmp(c1->codCli,c2->codCli);
}


/*Operações sobre Cat_Clis*/
Cat_Clis inicializa_CatClis () {
	Cat_Clis catc = malloc(sizeof(struct cat_clis));
	
	catc->clis = malloc(sizeof(struct avl));
		
	catc->clis = NULL;
	catc->total = 0;
	catc->validos = 0;
	
	return catc;
}

void free_Catc (Cat_Clis catc) {
	free_AVL(catc->clis,'c');
	free(catc);
}

Cat_Clis insereCli (Cat_Clis catc, Cliente c) {
	int aum = 0;
	catc->clis = insereAVL(catc->clis,c,&aum,'c');
	catc->validos++;
	return catc;
}

Boolean existeCli (Cat_Clis catc, Cliente c) {
	return lookupAVL(catc->clis,c,'c');
}

Cat_Clis mudaFlagCli (Cat_Clis catc, Cliente c, int fil) {
	catc->clis = mudaFlagAVL(catc->clis,c,'c',fil);
	return catc;
}


/*Getters e setters*/
/*1 - F1, 2 - F2, 3 - F3, 4 - F1+F2, 5 - F1+F3, 6 - F2+F3, 7 - F1+F2+F3*/
Cliente setFlagCli (Cliente c, int fil) {
	if (c->flag == 0) c->flag = fil;
	else if (fil == 1) {
		if (c->flag == 2) c->flag = 4;
		if (c->flag == 3) c->flag = 5;
		if (c->flag == 6) c->flag = 7;
	}
	else if (fil == 2) {
		if (c->flag == 1) c->flag = 4;
		if (c->flag == 3) c->flag = 6;
		if (c->flag == 5) c->flag = 7;
	}
	else if (fil == 3) {
		if (c->flag == 1) c->flag = 5;
		if (c->flag == 2) c->flag = 6;
		if (c->flag == 4) c->flag = 7;
	}
	return c;
}

Cat_Clis incTotalClis (Cat_Clis catc) {
	catc->total++;
	return catc;
}

AVL getAVLClis (Cat_Clis catc) {
	return catc->clis;
}

int getTotalClis (Cat_Clis catc) {
	return catc->total;
}

int getValClis (Cat_Clis catc) {
	return catc->validos;
}

char* getCli (Cliente c) {
	return c->codCli;
}

int getFlagC (Cliente c) {
	return c->flag;
}


/*Outras*/
int numClisQ6 (Cat_Clis catc) {
	return numNuncaComp(0,catc->clis,1);
}