#include <stdio.h>
#include <stdlib.h>
#include "EstacFer.h"
#include <locale.h>

#define MAX 5

enum boolean
{
    true = 1, false = 0
};
typedef  enum boolean  bool;

typedef struct
{
    int id;
    int locomotivaAtrelada;

    bool emOperacao;
} Vagao;

typedef struct
{
    int qtdEspacsoLivrseParaVagoes;
    int id;
    int qtdVagoesAtrelados;
    Vagao espacosParaVagoesNaLocamotiva[MAX];
    char nomeManobrista[50];
} Locomotiva;

struct estacionamento
{
    int vagoesParados;
    int vagoesNaoParados;
    Vagao vagoesDoEstacionamento[MAX];
};

struct terminalFerreo
{
    Locomotiva locomotivas[3];
    int caminhoAtivado;
};

void inicializar()
{
    struct estacionamento est;
    struct terminalFerreo term;
    int i;
    int auxID;
    term.caminhoAtivado=1;

    est.vagoesParados=5;
    est.vagoesNaoParados=0;
    printf("Inicializando sistema 'Estacionamento Ferroviario'...\n\n");
    for(i=0; i<3; i++)
    {
        term.locomotivas[i].id=i;
        term.locomotivas[i].qtdEspacsoLivrseParaVagoes=5;
        term.locomotivas[i].qtdVagoesAtrelados=0;

    }
    for(i=0; i<MAX; i++)
    {
        est.vagoesDoEstacionamento[i].id=i;
        est.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;
        est.vagoesDoEstacionamento[i].emOperacao = false;

    }

    for(i=0; i<3; i++)
    {
        for(auxID=0; auxID<5; auxID++)
        {
            term.locomotivas[i].espacosParaVagoesNaLocamotiva[auxID].id=-1;
            term.locomotivas[i].espacosParaVagoesNaLocamotiva[auxID].locomotivaAtrelada=i;
            term.locomotivas[i].espacosParaVagoesNaLocamotiva[auxID].emOperacao = false;
        }
    }
    printf("\nDigite o nome do manobrista da primeira locomotiva: ");
    gets(term.locomotivas[0].nomeManobrista);
    printf("\nDigite o nome do manobrista da segunda locomotiva: ");
    gets(term.locomotivas[1].nomeManobrista);
    printf("\nDigite o nome do manobrista da terceira locomotiva: ");
    gets(term.locomotivas[2].nomeManobrista);
    printf("Programa inicializado...\n\n");
    engatarVagao(est, term);
}

void engatarVagao(struct estacionamento EST, struct terminalFerreo TERM)
{
    int locomotivaEscolhida;
    int qtVagoes;
    int i=4;
    int qtdQueFaltaNoEstacionamento=0;
    int vagoesQueFaltamPegar=0;
    int opcaoMenu;
    EST.vagoesParados=5;
    printf("\n\nDigite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
    scanf("%d", &opcaoMenu);
    while(opcaoMenu  != 1 && opcaoMenu != 2)
    {
        printf("Opção inválida! Digite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
        scanf("%d", &opcaoMenu);
    }

    while(opcaoMenu ==1)
    {
        printf("\n\nEscolha a locomotiva desejada (de 0 a 2): ");
        scanf("%d", &locomotivaEscolhida);
        while(locomotivaEscolhida != 0 && locomotivaEscolhida  != 1 && locomotivaEscolhida != 2)
        {
            printf("Locomotiva inválida! Escolha novamente a locomotiva desejada(de 0 a 2): ");
            scanf("%d", &locomotivaEscolhida);
        }
        TERM.caminhoAtivado = locomotivaEscolhida;

        printf("Digite a quantidade de vagoes que deseja atrelar:");
        scanf("%d", &qtVagoes);
        while(qtVagoes != 1 && qtVagoes != 2 && qtVagoes != 3 && qtVagoes != 4 && qtVagoes!= 5)
        {
            printf("Quantidade de vagões inválida! \nDigite a quantidade de vagoes que deseja atrelar (de 1 a 5): ");
            scanf("%d", &qtVagoes);
        }

        if(((TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes)-qtVagoes)<0)
        {
            printf("\nNão há espaço disponivel para a operação!\n\n");
        }
        else
        {
            if(EST.vagoesParados!=0 && (EST.vagoesParados >= qtVagoes))
            {
                vagoesQueFaltamPegar=qtVagoes;
                while(vagoesQueFaltamPegar>0)
                {
                    for(i=4; i>=0; i--)
                    {
                        if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==-1 && vagoesQueFaltamPegar>0)
                        {
                            EST.vagoesDoEstacionamento[i].locomotivaAtrelada=locomotivaEscolhida;
                            TERM.locomotivas[locomotivaEscolhida].espacosParaVagoesNaLocamotiva[TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes-1].id = EST.vagoesDoEstacionamento[i].id;
                            EST.vagoesDoEstacionamento[i].id=-1;
                            EST.vagoesDoEstacionamento[i].emOperacao = true;
                            vagoesQueFaltamPegar--;
                            TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes--;
                            EST.vagoesParados--;
                            EST.vagoesNaoParados++;
                            TERM.locomotivas[locomotivaEscolhida].qtdVagoesAtrelados++;
                        }
                    }
                }
            }
            else
            {
                vagoesQueFaltamPegar=qtVagoes;
                qtdQueFaltaNoEstacionamento = (vagoesQueFaltamPegar) - (EST.vagoesParados);

                if(locomotivaEscolhida==0)
                {
                    while(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[1].qtdVagoesAtrelados!=0)
                    {
                        for(i=0; i<=4; i++)
                        {
                            if(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[1].qtdVagoesAtrelados!=0)
                            {
                                if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==1 && vagoesQueFaltamPegar>0)
                                {
                                    EST.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;
                                    EST.vagoesDoEstacionamento[i].emOperacao = true;
                                    EST.vagoesNaoParados--;
                                    EST.vagoesDoEstacionamento[i].id=i;
                                    TERM.locomotivas[1].espacosParaVagoesNaLocamotiva[TERM.locomotivas[1].qtdEspacsoLivrseParaVagoes].id = -1;
                                    TERM.locomotivas[1].espacosParaVagoesNaLocamotiva[TERM.locomotivas[1].qtdEspacsoLivrseParaVagoes].emOperacao = true;
                                    TERM.locomotivas[1].qtdVagoesAtrelados--;
                                    TERM.locomotivas[1].qtdEspacsoLivrseParaVagoes++;

                                    EST.vagoesParados++;
                                    qtdQueFaltaNoEstacionamento--;
                                }
                            }
                        }
                    }

                    while(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[2].qtdVagoesAtrelados!=0)
                    {
                        for(i=0; i<=4; i++)
                        {
                            if(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[2].qtdVagoesAtrelados!=0)
                            {
                                if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==2 && vagoesQueFaltamPegar>0)
                                {
                                    EST.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;

                                    EST.vagoesNaoParados--;
                                    EST.vagoesDoEstacionamento[i].emOperacao = true;
                                    EST.vagoesDoEstacionamento[i].id=i;
                                    TERM.locomotivas[2].espacosParaVagoesNaLocamotiva[TERM.locomotivas[2].qtdEspacsoLivrseParaVagoes].id = -1;
                                    TERM.locomotivas[2].qtdVagoesAtrelados--;
                                    TERM.locomotivas[2].qtdEspacsoLivrseParaVagoes++;

                                    EST.vagoesParados++;
                                    qtdQueFaltaNoEstacionamento--;
                                }
                            }
                        }
                    }
                    while(vagoesQueFaltamPegar>0)
                    {
                        for(i=4; i>=0; i--)
                        {
                            if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==-1 && vagoesQueFaltamPegar>0)
                            {
                                EST.vagoesDoEstacionamento[i].locomotivaAtrelada=locomotivaEscolhida;
                                TERM.locomotivas[locomotivaEscolhida].espacosParaVagoesNaLocamotiva[TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes-1].id = EST.vagoesDoEstacionamento[i].id;
                                EST.vagoesDoEstacionamento[i].id=-1;
                                EST.vagoesDoEstacionamento[i].emOperacao = true;
                                vagoesQueFaltamPegar--;
                                TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes--;
                                EST.vagoesParados--;
                                EST.vagoesNaoParados++;
                                TERM.locomotivas[locomotivaEscolhida].qtdVagoesAtrelados++;
                            }
                        }
                    }
                }

                if(locomotivaEscolhida==1)
                {
                    while(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[0].qtdVagoesAtrelados!=0)
                    {
                        for(i=0; i<=4; i++)
                        {
                            if(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[0].qtdVagoesAtrelados!=0)
                            {
                                if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==0 && vagoesQueFaltamPegar>0)
                                {
                                    EST.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;

                                    EST.vagoesNaoParados--;
                                    EST.vagoesDoEstacionamento[i].id=i;
                                    EST.vagoesDoEstacionamento[i].emOperacao = true;
                                    TERM.locomotivas[0].espacosParaVagoesNaLocamotiva[TERM.locomotivas[0].qtdEspacsoLivrseParaVagoes].id = -1;
                                    TERM.locomotivas[0].qtdVagoesAtrelados--;
                                    TERM.locomotivas[0].qtdEspacsoLivrseParaVagoes++;

                                    EST.vagoesParados++;
                                    qtdQueFaltaNoEstacionamento--;
                                }
                            }
                        }
                    }

                    while(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[2].qtdVagoesAtrelados!=0)
                    {
                        for(i=0; i<=4; i++)
                        {
                            if(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[2].qtdVagoesAtrelados!=0)
                            {
                                if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==2 && vagoesQueFaltamPegar>0)
                                {
                                    EST.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;

                                    EST.vagoesNaoParados--;
                                    EST.vagoesDoEstacionamento[i].emOperacao = true;
                                    EST.vagoesDoEstacionamento[i].id=i;
                                    TERM.locomotivas[2].espacosParaVagoesNaLocamotiva[TERM.locomotivas[2].qtdEspacsoLivrseParaVagoes].id = -1;
                                    TERM.locomotivas[2].qtdVagoesAtrelados--;
                                    TERM.locomotivas[2].qtdEspacsoLivrseParaVagoes++;

                                    EST.vagoesParados++;
                                    qtdQueFaltaNoEstacionamento--;
                                }
                            }
                        }
                    }
                    while(vagoesQueFaltamPegar>0)
                    {
                        for(i=4; i>=0; i--)
                        {
                            if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==-1 && vagoesQueFaltamPegar>0)
                            {
                                EST.vagoesDoEstacionamento[i].locomotivaAtrelada=locomotivaEscolhida;
                                TERM.locomotivas[locomotivaEscolhida].espacosParaVagoesNaLocamotiva[TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes-1].id = EST.vagoesDoEstacionamento[i].id;
                                EST.vagoesDoEstacionamento[i].id=-1;
                                EST.vagoesDoEstacionamento[i].emOperacao = true;
                                vagoesQueFaltamPegar--;
                                TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes--;
                                EST.vagoesParados--;
                                EST.vagoesNaoParados++;
                                TERM.locomotivas[locomotivaEscolhida].qtdVagoesAtrelados++;
                            }
                        }
                    }
                }
                if(locomotivaEscolhida==2)
                {
                    while(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[1].qtdVagoesAtrelados!=0)
                    {
                        for(i=0; i<=4; i++)
                        {
                            if(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[1].qtdVagoesAtrelados!=0)
                            {
                                if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==1 && vagoesQueFaltamPegar>0)
                                {
                                    EST.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;

                                    EST.vagoesNaoParados--;
                                    EST.vagoesDoEstacionamento[i].id=i;
                                    EST.vagoesDoEstacionamento[i].emOperacao = true;
                                    TERM.locomotivas[1].espacosParaVagoesNaLocamotiva[TERM.locomotivas[1].qtdEspacsoLivrseParaVagoes].id = -1;
                                    TERM.locomotivas[1].qtdVagoesAtrelados--;
                                    TERM.locomotivas[1].qtdEspacsoLivrseParaVagoes++;

                                    EST.vagoesParados++;
                                    qtdQueFaltaNoEstacionamento--;
                                }
                            }
                        }
                    }

                    while(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[0].qtdVagoesAtrelados!=0)
                    {
                        for(i=0; i<=4; i++)
                        {
                            if(qtdQueFaltaNoEstacionamento>0 && TERM.locomotivas[0].qtdVagoesAtrelados!=0)
                            {
                                if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==0 && vagoesQueFaltamPegar>0)
                                {
                                    EST.vagoesDoEstacionamento[i].locomotivaAtrelada=-1;

                                    EST.vagoesNaoParados--;
                                    EST.vagoesDoEstacionamento[i].id=i;
                                    EST.vagoesDoEstacionamento[i].emOperacao = true;
                                    TERM.locomotivas[0].espacosParaVagoesNaLocamotiva[TERM.locomotivas[0].qtdEspacsoLivrseParaVagoes].id = -1;
                                    TERM.locomotivas[0].qtdVagoesAtrelados--;
                                    TERM.locomotivas[0].qtdEspacsoLivrseParaVagoes++;

                                    EST.vagoesParados++;
                                    qtdQueFaltaNoEstacionamento--;
                                }
                            }
                        }
                    }
                    while(vagoesQueFaltamPegar>0)
                    {
                        for(i=4; i>=0; i--)
                        {
                            if(EST.vagoesDoEstacionamento[i].locomotivaAtrelada==-1 && vagoesQueFaltamPegar>0)
                            {
                                EST.vagoesDoEstacionamento[i].locomotivaAtrelada=locomotivaEscolhida;
                                TERM.locomotivas[locomotivaEscolhida].espacosParaVagoesNaLocamotiva[TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes-1].id = EST.vagoesDoEstacionamento[i].id;
                                EST.vagoesDoEstacionamento[i].id=-1;
                                EST.vagoesDoEstacionamento[i].emOperacao = true;
                                vagoesQueFaltamPegar--;
                                TERM.locomotivas[locomotivaEscolhida].qtdEspacsoLivrseParaVagoes--;
                                EST.vagoesParados--;
                                EST.vagoesNaoParados++;
                                TERM.locomotivas[locomotivaEscolhida].qtdVagoesAtrelados++;
                            }
                        }
                    }

                }
            }

        }
        printf("\n\nDigite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
        scanf("%d", &opcaoMenu);
        while(opcaoMenu  != 1 && opcaoMenu != 2)
        {
            printf("Opção inválida! Digite a opção desejada:\n1 - Engatar vagao\n2 - Sair\n");
            scanf("%d", &opcaoMenu);
        }

    }
    exit(0);


}



