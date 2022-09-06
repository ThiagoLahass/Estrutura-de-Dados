#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arv {
    Aluno* aluno;
    struct arv* esq;
    struct arv* dir;
};

//cria uma arvore vazia
Arv* arv_cria_vazia(){
    return NULL;
}

//cria uma arvore com a informacao do no
//raiz aluno, e com subárvore esquerda 'e' e subárvores direita 'd'
Arv* arv_cria( Aluno* aluno, Arv* e, Arv* d) {
    Arv* p = (Arv*) calloc(1, sizeof(Arv));
    p->aluno = aluno;
    p->esq = e;
    p->dir = d;
    return p;
}

//libera o espaco de memoria ocupado pela arvore 'a'
Arv* arv_libera( Arv* a) {
    if( !arv_vazia( a )) {
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}

//retorna true se a arvore estiver vazia
//caso contrario, retorna false
int arv_vazia (Arv* a) {
    return a == NULL;
}

//indica a ocorrencia (1) ou nao (0) do aluno de nome "nome" na arvore 'a'
int arv_pertence (Arv* a, char* nome) {
    if( arv_vazia( a )) {
        return 0;
    }
    else {
        return ( (strcmp(aluno_nome (a->aluno), nome) == 0) || arv_pertence( a->esq, nome ) || arv_pertence( a->dir, nome ) );
    }
}

//imprime as informacoes dos nos da arvore
void arv_imprime( Arv* a) {
    printf("<");
    if( !arv_vazia ( a )) {
        aluno_imprime(a->aluno);
        arv_imprime(a->esq);
        arv_imprime(a->dir);
    }
    printf("> ");
}


/*
----------------- ORDEM DE PROCESSAMENTO -----------------

void arv_preordem (Arv* a) {
    if (!arv_vazia(a)) {
        processa(a); // por exemplo imprime
        arv_preordem(a->esq);
        arv_preordem(a->dir);
    }
}

void arv_inordem (Arv* a) {
    if (!arv_vazia(a)) {
        arv_inordem (a->esq);
        processa (a); // por exemplo imprime
        arv_inordem (a->dir);
    }
}

void arv_posordem (Arv* a) {
    if (!arv_vazia(a)) {
        arv_posordem (a->esq);
        arv_posordem (a->dir);
        processa (a); // por exemplo imprime
    }
}


void arv_preordem (Arv* a) {
    Arv* A[MAX]; //qual seria o valor de max?
    Arv* p; Arv* raiz; int topo;
    int acabou;
    topo = 0; p = a; acabou = arv_vazia(a); //inicializações
    while (!acabou) // enquanto houver nós para processar
    {
        while (!arv_vazia(p)) {
            processa (p->info);
            topo++; A[topo] = p;
            p = p->esq;
        }
        if (topo != 0) {
            p = A[topo]->dir;
            topo--;
        }
        else {
            acabou = 1;
        }
    }
}
---------------------------------------------------------
*/

static int max2 (int a, int b) {
    return (a > b) ? a : b;
}

// retorna altura de uma arvore
int arv_altura (Arv* a) {
    if (arv_vazia(a))
        return -1;
    else
        return ( 1 + max2 (arv_altura (a->esq), arv_altura (a->dir)) );
}

//retorna no pai de um no
Arv* arv_pai (Arv* a, char* nome) {
    if( arv_vazia ( a )) {
        return NULL;
    }
    if( ((!arv_vazia(a->esq)) && (strcmp(aluno_nome (a->esq->aluno), nome) == 0)) || ((!arv_vazia(a->dir) && (strcmp(aluno_nome (a->dir->aluno), nome) == 0)))) {
        return a;
    }

    Arv* aux = arv_pai(a->esq, nome);
    if( aux == NULL ) {
        aux = arv_pai( a->dir, nome );
    }

    return aux;
}

//retorna qauntidade de folhas de uma arvore binaria
int arv_folhas ( Arv* a ) {
    if(arv_vazia(a->esq) && arv_vazia(a->dir)) {
        return 1;
    }
    else if (!arv_vazia(a->esq) && arv_vazia(a->dir)){
        return arv_folhas(a->esq);
    }
    else if (arv_vazia(a->esq) && !arv_vazia(a->dir)){
        return arv_folhas(a->dir);
    }

    return arv_folhas(a->esq) + arv_folhas(a->dir);
}

//retorna numero de ocorrencias de um dado aluno na arvore
int arv_ocorrencias ( Arv* a, char* nome) {
    if(arv_vazia( a )){
        return 0;
    }
    if( strcmp( aluno_nome( a->aluno ), nome ) == 0){
        return (1 + arv_ocorrencias(a->esq, nome ) + arv_ocorrencias(a->dir, nome));
    }

    return (arv_ocorrencias(a->esq, nome) + arv_ocorrencias(a->dir, nome));
}

//retorna o campo informacao de um dado no
char* arv_info ( Arv* a ) {
    if( !arv_vazia( a )){
        return aluno_nome(a->aluno);
    }
    return "0";
}

