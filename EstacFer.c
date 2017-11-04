#include <stdio.h>
#include <stdlib.h>
#include "EstacFer.h"
#define MAX 5

typedef struct{
    int id;
    int locomotivaAtrelada;
}Vagao;

typedef struct{
    int qtdEspacoParaVagoes;
    int id;
    int vagaoDesejado;
    Vagao espacosParaVagoesNaLocamotiva[MAX];
}Locomotiva;

struct estacionamento{
    int vagoesParados;
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
    est.vagoesParados=5;
    printf("Inicializando...\n\n");
    for(i=0;i<3;i++){
        term.locomotivas[i].id=i;
        term.locomotivas[i].qtdEspacoParaVagoes=5;

    }
    for(i=0;i<MAX;i++){
        est.vagoesDoEstacionamento[i].id=i;
        est.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;
    }

    for(i=0;i<3;i++){
         for(auxID=0;auxID<5;auxID++){
            term.locomotivas[i].espacosParaVagoesNaLocamotiva[auxID].id=-1;
            term.locomotivas[i].espacosParaVagoesNaLocamotiva[auxID].locomotivaAtrelada=i;
         }
    }
    printf("Programa inicializado...\n\n");
    engatarVagao(est, term);
}

void engatarVagao(struct estacionamento EST, struct terminalFerreo TERM){
    //struct estacionamento est;
   // struct terminalFerreo term;
    int locomotivaEscolhida;
    int vagaoEscolhido;
    int qtVagoes;
    int i=4;
    int j=0;
    int aux;
    int vagoesQueFaltamPegar=0;
    int opcaoMenu;
    EST.vagoesParados=5;
    printf("Digite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
    scanf("%d", &opcaoMenu);
    while(opcaoMenu  != 1 && opcaoMenu != 2){
        printf("Opção inválida! Digite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
        scanf("%d", &opcaoMenu);
    }

    while(opcaoMenu ==1){
        printf("\n\nEscolha a locomotiva desejada (de 0 a 2): ");
        scanf("%d", &locomotivaEscolhida);
        while(locomotivaEscolhida != 0 && locomotivaEscolhida  != 1 && locomotivaEscolhida != 2){
            printf("Locomotiva inválida! Escolha novamente a locomotiva desejada(de 0 a 2): ");
            scanf("%d", &locomotivaEscolhida);
        }
        TERM.caminhoAtivado = locomotivaEscolhida;

        printf("\n\nDigite a quantidade de vagoes que deseja atrelar:");
        scanf("%d", &qtVagoes);
        while(qtVagoes != 1 && qtVagoes != 2 && qtVagoes != 3 && qtVagoes != 4 && qtVagoes!= 5){
            printf("Quantidade de vagões inválida! \nDigite a quantidade de vagoes que deseja atrelar (de 1 a 5): ");
            scanf("%d", &qtVagoes);
        }

        if(((TERM.locomotivas[locomotivaEscolhida].qtdEspacoParaVagoes)-qtVagoes)<0){
            printf("\nNão há espaço disponivel para a operação!\n\n");
        }else{
            if(EST.vagoesParados!=0){
                vagoesQueFaltamPegar=qtVagoes;
                while(vagoesQueFaltamPegar>0){
                    for(i=4; i>=0; i--){
                        if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==-1 && vagoesQueFaltamPegar>0){
                                EST.vagoesDoEstacionamento[i].locomotivaAtrelada=locomotivaEscolhida;
                                TERM.locomotivas[locomotivaEscolhida].espacosParaVagoesNaLocamotiva[TERM.locomotivas[locomotivaEscolhida].qtdEspacoParaVagoes-1].id = EST.vagoesDoEstacionamento[i].id;
                                EST.vagoesDoEstacionamento[i].id=-1;
                                vagoesQueFaltamPegar--;
                                TERM.locomotivas[locomotivaEscolhida].qtdEspacoParaVagoes--;
                                EST.vagoesParados--;
                        }
                    }
                }
            }else{
                printf("\nNão há vagoes estacionados suficientes para a operação!\n\n");
            }
        }
        printf("Digite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
        scanf("%d", &opcaoMenu);
        while(opcaoMenu  != 1 && opcaoMenu != 2){
        printf("Opção inválida! Digite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
        scanf("%d", &opcaoMenu);
        }
    //}
    }
    exit(0);


}



