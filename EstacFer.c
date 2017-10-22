#include <stdio.h>
#include <stdlib.h>
#include "EstacFer.h"
#define MAX 5

typedef struct{
    int id;
    int locomotivaAtrelada;
}Vagao;

typedef struct{
    int lotada;
    int qtdVagoesAtrelados;
    int id;
    int vagaoDesejado;
    Vagao vagoesDaLocomotiva[MAX];
}Locomotiva;

struct estacionamento{
    Vagao vagoesDoEstacionamento[MAX];
};

struct terminalFerreo{
    Locomotiva locomotivas[3];
    int caminhoAtivado;
};

void inicializar(){
    struct estacionamento est;
    struct terminalFerreo term;
    int i; int auxID;
    term.caminhoAtivado=1;
    for(i=0;i<3;i++){
        term.locomotivas[i].id=i;
        term.locomotivas[i].lotada=0;
        term.locomotivas[i].qtdVagoesAtrelados=0;
    }
    for(i=0;i<5;i++){
        est.vagoesDoEstacionamento[i].id=i;
    }

    for(i=0;i<3;i++){
         for(auxID=0;auxID<5;auxID++){
            term.locomotivas[i].vagoesDaLocomotiva[auxID].id=auxID;
         }
    }
}



