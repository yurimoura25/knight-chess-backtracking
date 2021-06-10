#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


struct posicao
{
    int li;
    int co;
};

typedef struct posicao Posicao;

struct Node {
    int tamanho;
    Posicao *caminho;
    struct Node *prox;
};
typedef struct Node Node;

void *copiarVetor(Posicao *vetor, Posicao *vetor1, int tamanho) { 
    for(int i = 0; i < tamanho; i ++ ){
        vetor1[i].li = vetor[i].li;
        vetor1[i].co = vetor[i].co;

    }

}


Node *caminhosInvalidos;

int tabuleiro[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0}};


Node *alocarNovo(int tamanho, Posicao *vetor) {
    Node *novo = (Node*)malloc(sizeof(Node));
    novo->tamanho = tamanho;
    novo->caminho = vetor;
    novo->prox = NULL;

    return novo;
}

void inserirCaminho(int tamanho, Posicao vetor[]) {
    Node *novo = alocarNovo(tamanho, vetor);
    if(caminhosInvalidos == NULL) {
        caminhosInvalidos = novo;
    } else {
        novo->prox = caminhosInvalidos;
        caminhosInvalidos = novo;
    }
}




//  1  2 - ok - 03
// -1  2 - ok - 02
//  1 -2 - ok - 06
// -1 -2 - ok - 07
//  2  1 - ok - 04
// -2  1 - ok - 01
//  2 -1 - ok - 05
// -2 -1 - ok - 08

// 01 - 08 - 02 - 07 - 03 - 06 - 04 - 05

// 
//                  
//           C 
// 
//        

int estaPresente(Posicao *caminhoAtual, Posicao pos, int qtdCasas)
{
    int i;
    // printf("\npos: pos.li = %i, pos.co = %i", pos.li, pos.co);
    for (i = 0; i < qtdCasas; i++)
    {
        // printf("\ncaminhoAtual[%i]: %i, %i\n" ,i, caminhoAtual[i].li, caminhoAtual[i].co);
        // system("pause");
        if (caminhoAtual[i].li == pos.li && caminhoAtual[i].co == pos.co)
        {
            return 1;
        }
    }
    return 0;
}

Posicao movimento1(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li - 2;
    p.co = posAtual.co + 1;
    return p;
}
Posicao movimento2(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li - 1;
    p.co = posAtual.co + 2;
    return p;
}
Posicao movimento3(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li + 1;
    p.co = posAtual.co + 2;
    return p;
}
Posicao movimento4(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li + 2;
    p.co = posAtual.co + 1;
    return p;
}
Posicao movimento5(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li + 2;
    p.co = posAtual.co - 1;
    return p;
}
Posicao movimento6(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li + 1;
    p.co = posAtual.co - 2;
    return p;
}
Posicao movimento7(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li - 1;
    p.co = posAtual.co - 2;
    return p;
}
Posicao movimento8(Posicao posAtual)
{
    Posicao p;
    p.li = posAtual.li - 2;
    p.co = posAtual.co - 1;
    return p;
}

int isCaminhoInvalido(Posicao *vetor, Posicao pos, int qtdCasas) {
    Node *aux = caminhosInvalidos;
    int i;                    
    int contador = qtdCasas - 1;
    while(aux != NULL) {
        // printf("\nAux li: %i, co: %i;\n pos.li: %i, pos.co: %i", aux->caminho[qtdCasas].li, aux->caminho[qtdCasas].co, pos.li, pos.co);

            if(aux->caminho[qtdCasas].li == pos.li && aux->caminho[qtdCasas].co == pos.co) 
            {
                contador = qtdCasas;
                for(i = qtdCasas - 1; i >= 0; i--) 
                {
                        if(aux->caminho[i].li == vetor[i].li && aux->caminho[i].co == vetor[i].co) 
                        {
                            contador--;
                        }
                    if(contador == 0) return 1;
                }
            } 
        aux = aux->prox;
    }
    return 0;
}

int isValid(Posicao pos, Posicao *caminhoAtual, int qtdCasas)
{
    int b = 1;
    if (pos.co < 0 || pos.co > 7 || pos.li < 0 || pos.li > 7)
    {
        b = 0;
    }
    if(b && qtdCasas<64 && isCaminhoInvalido(caminhoAtual, pos, qtdCasas)) {
        b = 0;

    }

    return b;
}


void printTabuleiro(Posicao posicaoAtual)
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        printf("\n");
        for (j = 0; j < 8; j++)
        {
            if (posicaoAtual.li == i && posicaoAtual.co == j)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);
                printf("  ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else
            {
                if (tabuleiro[i][j] != 1)
                {
                    // if(i%2 ==0) {
                    //     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                    //     printf("  ");

                    //     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    // } else {
                    //     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128);
                    //     printf("  ");
                    //     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    // }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128);
                    printf("  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
                    printf("  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
            }
        }
    }
}

// void printLista() {
//     int i;
//     int j;
//     for(i = 0; i < qtdCaminhosInvalidos; i++) {
//         printf("\ni: %i", i);
//         for(j = 0; j < 64; j++) {
//             printf(", li: %i co: %i", caminhosInvalidos[i][j].li, caminhosInvalidos[i][j].co);
//         }
//     } 
// }

void printCaminhoAtual(Posicao *caminhoAtual, int qtdCasas) {
    int i;
    printf("\n\n");
    for( i = 0 ; i < qtdCasas ; i++) {
        printf(" (%i,%i)", caminhoAtual[i].li, caminhoAtual[i].co);
    }
}

void caminhar(Posicao *caminhoAtual, int qtdCasas)
{
    Posicao mov1 = movimento1(caminhoAtual[qtdCasas - 1]);
    Posicao mov2 = movimento2(caminhoAtual[qtdCasas - 1]);
    Posicao mov3 = movimento3(caminhoAtual[qtdCasas - 1]);
    Posicao mov4 = movimento4(caminhoAtual[qtdCasas - 1]);
    Posicao mov5 = movimento5(caminhoAtual[qtdCasas - 1]);
    Posicao mov6 = movimento6(caminhoAtual[qtdCasas - 1]);
    Posicao mov7 = movimento7(caminhoAtual[qtdCasas - 1]);
    Posicao mov8 = movimento8(caminhoAtual[qtdCasas - 1]);

    system("cls");
    printTabuleiro(caminhoAtual[qtdCasas - 1]);
    printCaminhoAtual(caminhoAtual, qtdCasas);
    // sleep(1);

    if (isValid(mov1, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov1, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov1;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if (isValid(mov8, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov8, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov8;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if (isValid(mov2, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov2, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov2;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if (isValid(mov7, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov7, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov7;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if (isValid(mov3, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov3, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov3;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if (isValid(mov6, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov6, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov6;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if (isValid(mov4, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov4, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov4;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if (isValid(mov5, caminhoAtual, qtdCasas) && !(estaPresente(caminhoAtual, mov5, qtdCasas)))
    {
        caminhoAtual[qtdCasas] = mov5;
        tabuleiro[caminhoAtual[qtdCasas].li][caminhoAtual[qtdCasas].co] = 1;
        qtdCasas++;
        caminhar(caminhoAtual, qtdCasas);
    }
    else if(qtdCasas < 64 && qtdCasas>0)
    {
        inserirCaminho(qtdCasas, caminhoAtual);
        Posicao *caminho = calloc(64, sizeof(Posicao));
        copiarVetor(caminhoAtual, caminho, qtdCasas - 1);
        tabuleiro[caminhoAtual[qtdCasas - 1].li][caminhoAtual[qtdCasas - 1].co] = 0;
        qtdCasas--;
        caminhar(caminho, qtdCasas);
    } else {
        printf("caminho encontrado!");
        system("pause");
    }
}


int main()
{
    Posicao *caminhoAtual = calloc(64, sizeof(Posicao));
    Posicao inicial;
    
    inicial.li = 0;
    inicial.co = 4;
    caminhoAtual[0].li = inicial.li;
    caminhoAtual[0].co = inicial.co;
    inserirCaminho(1, caminhoAtual);

    tabuleiro[caminhoAtual[0].li][caminhoAtual[0].co] = 1;
    caminhar(caminhoAtual, 1);
    int i;
    for(i = 0; i< 64;i ++) {
        printf("li= %i co= %i, ", caminhoAtual[i].li, caminhoAtual[i].co);
    }
    system("pause");
}
