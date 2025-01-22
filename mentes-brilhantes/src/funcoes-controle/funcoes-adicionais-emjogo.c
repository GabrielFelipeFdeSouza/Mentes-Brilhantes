/*
-->FUNÇÕES ADICIONAIS EM JOGO<--
Funções básicas reultilizaveis para as partes dos controles dos jogos,
aqui todas as partes de processamentos e analizes das coisas que ocorrem
durante o jogo são feitas.*/

//---------------------------------
// INCLUDES
//---------------------------------

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "funcoes-emjogo-bot.h"
#include "funcoes-controle-geral.h"
#include "desenho-geral.h"
#include "cores.h"
#include <math.h>
#include <stdbool.h>
#include "funcoes-adicionais-emjogo.h"
#include <time.h>
#include "funcoes-rede.h"
#include "escrever-arquivos.h"

//---------------------------------
// FUNÇOES ADICIONAIS
//---------------------------------

// Função que é chamada no inicio de cada jogo, preparando para jogar
void iniciar_jogo_bot(Carta **cartas_bot, Carta **cartas_jogador, int quantidades_cartas[2])
{

    int cartas_escolhidas[quantidade_cartas]; // Usado para determinar os indices das cartas de cada jogador

    // Preencher o array com valores possiveis de cartas, ids possiveis de acesso ao vetor de cartas:
    for (int i = 0; i < quantidade_cartas; i++)
    {
        cartas_escolhidas[i] = i;
    }

    // Embaralhar o array, usando random:
    for (int i = quantidade_cartas - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = cartas_escolhidas[i];
        cartas_escolhidas[i] = cartas_escolhidas[j];
        cartas_escolhidas[j] = temp;
    }

    for (int k = 0; k < quantidade_cartas; k++)
    {
        if (k % 2 == 0)
        {
            // Copia vetor cartas para o bot:
            quantidades_cartas[0]++;
            *cartas_bot = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));
            (*cartas_bot)[quantidades_cartas[0] - 1] = cartas[cartas_escolhidas[k]];
        }
        else
        {
            // Copia vetor cartas para o jogador:
            quantidades_cartas[1]++;
            *cartas_jogador = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));
            (*cartas_jogador)[quantidades_cartas[1] - 1] = cartas[cartas_escolhidas[k]];
        }
    } // For que copia as informações das cartas aleatorias geradas para cada baralho, atualizando tambem a quantidade de cartas

    return;
} // Função que prepara o jogo para iniciar

// Função que a cada final de rodada é chamada para verificar as condições de vitória de cada rodada:
void clicado(int *btn_clicado, Carta **cartas_bot, Carta **cartas_jogador, Carta **pilha_empate, int *quantidades_cartas, int tipo)
{
    Carta temporaria; // Usada para copiar as informações da primeira carta

    //---------------------------------
    // CASO SUPER TRUNFO
    //---------------------------------

    if ((*cartas_bot)[0].super_trunfo || (*cartas_jogador)[0].super_trunfo)
    {
        if ((*cartas_bot)[0].super_trunfo)
        {
            if ((*cartas_jogador)[0].hexadecimal[1] == 'A')
            {
                quantidades_cartas[1]++;                                                                      // Aumenta o vetor de cartas do jogador
                quantidades_cartas[0]--;                                                                      // Diminui o vetor de cartas do bot
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta)); // Realoca o vetor de cartas do jogador
                (*cartas_jogador)[quantidades_cartas[1] - 1] = (*cartas_bot)[0];                              // Copia carta perdida do bot para o baralho do player
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                } // Ajusta as cartas do bot para ele perder a primeira carta
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta)); // Realoca o baralho do bot para ficar no tamanho correto

                temporaria = (*cartas_jogador)[0]; // Usa a carta temporaria para colocar a carta da mão do player no fim do baralho
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                } // Ajusta as cartas do jogador
                (*cartas_jogador)[quantidades_cartas[1] - 1] = temporaria; // Coloca a ultima carta

                distribuiPilha(cartas_jogador, &quantidades_cartas[1], pilha_empate, quantidades_cartas); // Chama a função que verifica se há cartas na pilha de empate e coloca no baralho do player
            } // Caso o jogador tenha uma carta de tipo A
            else
            {
                quantidades_cartas[0]++;
                quantidades_cartas[1]--;
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));
                (*cartas_bot)[quantidades_cartas[0] - 1] = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));

                temporaria = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot)[quantidades_cartas[0] - 1] = temporaria;

                distribuiPilha(cartas_bot, &quantidades_cartas[0], pilha_empate, quantidades_cartas);
            } // Caso contrário
        } // Se supertrunfo pertencer ao bot

        if ((*cartas_jogador)[0].super_trunfo)
        {
            if ((*cartas_bot)[0].hexadecimal[1] == 'A')
            {
                quantidades_cartas[0]++;
                quantidades_cartas[1]--;
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));
                (*cartas_bot)[quantidades_cartas[0] - 1] = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));

                temporaria = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot)[quantidades_cartas[0] - 1] = temporaria;

                distribuiPilha(cartas_bot, &quantidades_cartas[0], pilha_empate, quantidades_cartas);
            } // Caso o bot tenha uma carta de tipo A
            else
            {
                quantidades_cartas[1]++;
                quantidades_cartas[0]--;
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));
                (*cartas_jogador)[quantidades_cartas[1] - 1] = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));

                temporaria = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador)[quantidades_cartas[1] - 1] = temporaria;

                distribuiPilha(cartas_jogador, &quantidades_cartas[1], pilha_empate, quantidades_cartas);
            } // Caso contrário
        } // Se supertrunfo pertencer ao jogador
    }
    else
    {
        //---------------------------------
        // DEMAIS CASOS
        //---------------------------------

        switch (*btn_clicado)
        {
        case 0: // Curiosidade

            if ((*cartas_jogador)[0].curiosidade > (*cartas_bot)[0].curiosidade)
            {
                quantidades_cartas[1]++;
                quantidades_cartas[0]--;
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));
                (*cartas_jogador)[quantidades_cartas[1] - 1] = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));

                temporaria = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador)[quantidades_cartas[1] - 1] = temporaria;

                distribuiPilha(cartas_jogador, &quantidades_cartas[1], pilha_empate, quantidades_cartas);
                break;
            }
            else if ((*cartas_jogador)[0].curiosidade < (*cartas_bot)[0].curiosidade)
            {
                quantidades_cartas[0]++;
                quantidades_cartas[1]--;
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));
                (*cartas_bot)[quantidades_cartas[0] - 1] = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));

                temporaria = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot)[quantidades_cartas[0] - 1] = temporaria;

                distribuiPilha(cartas_bot, &quantidades_cartas[0], pilha_empate, quantidades_cartas);
                break;
            }
            else
            {
                empate(cartas_bot, cartas_jogador, pilha_empate, quantidades_cartas, tipo);
            }
            break;

        case 1: // Criatividade

            if ((*cartas_jogador)[0].criatividade > (*cartas_bot)[0].criatividade)
            {
                quantidades_cartas[1]++;
                quantidades_cartas[0]--;
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));
                (*cartas_jogador)[quantidades_cartas[1] - 1] = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));

                temporaria = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador)[quantidades_cartas[1] - 1] = temporaria;

                distribuiPilha(cartas_jogador, &quantidades_cartas[1], pilha_empate, quantidades_cartas);
                break;
            }
            else if ((*cartas_jogador)[0].criatividade < (*cartas_bot)[0].criatividade)
            {
                quantidades_cartas[0]++;
                quantidades_cartas[1]--;
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));
                (*cartas_bot)[quantidades_cartas[0] - 1] = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));

                temporaria = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot)[quantidades_cartas[0] - 1] = temporaria;
                distribuiPilha(cartas_bot, &quantidades_cartas[0], pilha_empate, quantidades_cartas);
                break;
            }
            else
            {
                empate(cartas_bot, cartas_jogador, pilha_empate, quantidades_cartas, tipo);
            }
            break;

        case 2: // Inovação

            if ((*cartas_jogador)[0].inovacao > (*cartas_bot)[0].inovacao)
            {
                quantidades_cartas[1]++;
                quantidades_cartas[0]--;
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));
                (*cartas_jogador)[quantidades_cartas[1] - 1] = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));

                temporaria = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador)[quantidades_cartas[1] - 1] = temporaria;

                distribuiPilha(cartas_jogador, &quantidades_cartas[1], pilha_empate, quantidades_cartas);
                break;
            }
            else if ((*cartas_jogador)[0].inovacao < (*cartas_bot)[0].inovacao)
            {
                quantidades_cartas[0]++;
                quantidades_cartas[1]--;
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));
                (*cartas_bot)[quantidades_cartas[0] - 1] = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));

                temporaria = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot)[quantidades_cartas[0] - 1] = temporaria;

                distribuiPilha(cartas_bot, &quantidades_cartas[0], pilha_empate, quantidades_cartas);
                break;
            }
            else
            {
                empate(cartas_bot, cartas_jogador, pilha_empate, quantidades_cartas, tipo);
            }
            break;

        case 3: // Idade

            if ((*cartas_jogador)[0].idade > (*cartas_bot)[0].idade)
            {
                quantidades_cartas[1]++;
                quantidades_cartas[0]--;
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));
                (*cartas_jogador)[quantidades_cartas[1] - 1] = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));

                temporaria = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador)[quantidades_cartas[1] - 1] = temporaria;

                distribuiPilha(cartas_jogador, &quantidades_cartas[1], pilha_empate, quantidades_cartas);
                break;
            }
            else if ((*cartas_jogador)[0].idade < (*cartas_bot)[0].idade)
            {
                quantidades_cartas[0]++;
                quantidades_cartas[1]--;
                (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));
                (*cartas_bot)[quantidades_cartas[0] - 1] = (*cartas_jogador)[0];
                for (int u = 0; u < quantidades_cartas[1]; u++)
                {
                    (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
                }
                (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));

                temporaria = (*cartas_bot)[0];
                for (int u = 0; u < quantidades_cartas[0]; u++)
                {
                    (*cartas_bot)[u] = (*cartas_bot)[u + 1];
                }
                (*cartas_bot)[quantidades_cartas[0] - 1] = temporaria;

                distribuiPilha(cartas_bot, &quantidades_cartas[0], pilha_empate, quantidades_cartas);
                break;
            }
            else
            {
                empate(cartas_bot, cartas_jogador, pilha_empate, quantidades_cartas, tipo);
            }
            break;

        default:
            break;
        }
    }

    *btn_clicado = -1; // Reset do botão para a próxima jogada

    printf("\nBARALHO BOT/PLAYER2:\n\n");

    for (int s = 0; s < quantidades_cartas[0]; s++)
    {
        printf("%s\n", (*cartas_bot)[s].nome);
    }

    printf("\nBARALHO PLAYER/PLAYER1:\n\n");

    for (int s = 0; s < quantidades_cartas[1]; s++)
    {
        printf("%s\n", (*cartas_jogador)[s].nome);
    }

    printf("\nBARALHO EMPATE:\n\n");

    for (int s = 0; s < quantidades_cartas[2]; s++)
    {
        printf("%s\n", (*pilha_empate)[s].nome);
    }

    return;
} // Função que trata das condições de ganho de cada rodada

// Função que trata do empate ocorrido
void empate(Carta **cartas_bot, Carta **cartas_jogador, Carta **pilha_empate, int *quantidades_cartas, int tipo)
{
    quantidades_cartas[2]++; // Incrementa o contador de referencia para a alocacao dinamica em casos

    if (*pilha_empate == NULL) // Checa se o vetor ja foi inicializado, se nao, inicializa ele
    {
        (*pilha_empate) = (Carta *)malloc(2 * sizeof(Carta)); // Inicializa com 2 posicoes iniciais, uma pra cada carta;
    }
    else // Se ele ja existe
    {
        // Realoca conforme a quantidade de empates seguidos
        (*pilha_empate) = (Carta *)realloc(*pilha_empate, (2 * quantidades_cartas[2]) * sizeof(Carta));
    }

    if (tipo == 1)
    {
        (*pilha_empate)[(2 * quantidades_cartas[2]) - 1] = (*cartas_jogador)[0]; // Coloca a carta do jogador na penultima posicao disponivel
        (*pilha_empate)[(2 * quantidades_cartas[2]) - 2] = (*cartas_bot)[0];     // Coloca a carta do bot na ultima posicao disponivel
    }
    else
    {
        (*pilha_empate)[(2 * quantidades_cartas[2]) - 1] = (*cartas_bot)[0];     // Coloca a carta do bot na penultima posicao disponivel
        (*pilha_empate)[(2 * quantidades_cartas[2]) - 2] = (*cartas_jogador)[0]; // Coloca a carta do jogador na ultima posicao disponivel
    }

    // Retira as cartas empatadas e ordena as restantes:
    quantidades_cartas[0]--;
    quantidades_cartas[1]--;

    for (int u = 0; u < quantidades_cartas[0]; u++)
    {
        (*cartas_bot)[u] = (*cartas_bot)[u + 1];
    }
    (*cartas_bot) = (Carta *)realloc(*cartas_bot, quantidades_cartas[0] * sizeof(Carta));

    for (int u = 0; u < quantidades_cartas[1]; u++)
    {
        (*cartas_jogador)[u] = (*cartas_jogador)[u + 1];
    }
    (*cartas_jogador) = (Carta *)realloc(*cartas_jogador, quantidades_cartas[1] * sizeof(Carta));

    return;
} // Função que trata dos casos de empate

// Função que coloca as cartas de empate nas cartas do ganhador da rodada de desempate
void distribuiPilha(Carta **cartas_merecedor, int *qtd_cartas_merecedor, Carta **pilha_empate, int *quantidades_cartas)
{

    if ((quantidades_cartas)[2] > 0)
    {
        *qtd_cartas_merecedor += 2 * quantidades_cartas[2];                                                 // Aumenta as cartas do vencedor nas que estão no monte
        (*cartas_merecedor) = (Carta *)realloc(*cartas_merecedor, (*qtd_cartas_merecedor) * sizeof(Carta)); // Realoca o baralho do vencedor

        for (int i = 0; i < (2 * quantidades_cartas[2]); i++)
        {
            (*cartas_merecedor)[(*qtd_cartas_merecedor - i - 1)] = (*pilha_empate)[i]; // Coloca a pilha dentro das cartas de quem ganhou
        }

        quantidades_cartas[2] = 0;
    } // Caso base, onde há cartas no monte de empate

    return;
} // Funcao que distribui as cartas da pilha de empate quando alguem ganhar

// Função que simula uma IA para as escolhas do bot baseado na dificuldade
int iaBot(Carta *cartas_bot, int dificuldade)
{

    // Copia os atributos da carta do bot para esse vetor de escolhas:
    int random_start[4];
    random_start[0] = cartas_bot[0].curiosidade;
    random_start[1] = cartas_bot[0].criatividade;
    random_start[2] = cartas_bot[0].inovacao;
    random_start[3] = cartas_bot[0].idade;

    int candidatos[4], j = 0; // Usadas na escolha

    switch (dificuldade)
    {
    case 0: // FACIL - Remove duas maiores opções

        for (int count = 0; count < 2; count++)
        {

            int maior_valor = random_start[0], maior_indice = 0;

            for (int i = 1; i < 4; i++)
            {
                if (random_start[i] > maior_valor)
                {
                    maior_valor = random_start[i];
                    maior_indice = i;
                }
            }
            random_start[maior_indice] = -1; // Marca o maior valor como removido
        } // Execução duas vezes

        // Adicionar índices restantes ao vetor de candidatos
        for (int i = 0; i < 4; i++)
        {
            if (random_start[i] != -1)
            {
                candidatos[j++] = i;
            }
        } // Criando o vetor de saida
        break;

    case 1: // MEDIO - Remove a maiore opção

        int maior_valor = random_start[0], maior_indice = 0;

        for (int i = 1; i < 4; i++)
        {
            if (random_start[i] > maior_valor)
            {
                maior_valor = random_start[i];
                maior_indice = i;
            }
        }
        random_start[maior_indice] = -1; // Marca o maior valor como removido

        // Adicionar índices restantes ao vetor de candidatos
        for (int i = 0; i < 4; i++)
        {
            if (random_start[i] != -1)
            {
                candidatos[j++] = i;
            }
        } // Criando o vetor de saida
        break;

    case 2: // DIFICIL - Remove as duas menores opções
        for (int count = 0; count < 2; count++)
        {

            int menor_valor = random_start[0], menor_indice = 0;

            for (int i = 1; i < 4; i++)
            {
                if (random_start[i] != -1 && random_start[i] < menor_valor)
                {
                    menor_valor = random_start[i];
                    menor_indice = i;
                }
            }
            random_start[menor_indice] = -1; // Marca o menor valor como removido
        }

        // Adicionar índices restantes ao vetor de candidatos
        for (int i = 0; i < 4; i++)
        {
            if (random_start[i] != -1)
            {
                candidatos[j++] = i;
            }
        } // Criando o vetor de saida
        break;

    default:
        return -1; // Retorna -1 para dificuldade inválida
    }

    // Randomizar entre os valores restantes:
    int escolha_aleatoria = rand() % j; // Randomiza entre 0 e j-1

    return candidatos[escolha_aleatoria];

} // Função que simula uma ia de escolhas do bot baseado na dificuldade

// Função que verifica se alguem ganhou o jogo, se sim ativa os triggers do submenu para isso
void checaVitoria(int *quantidades_cartas, int *submenu_tela)
{
    if (quantidades_cartas[0] == 0)
    {
        *submenu_tela = 5;
    }

    if (quantidades_cartas[1] == 0)
    {
        *submenu_tela = 6;
    }
    return;
} // Função que verifica se alguem ganhou o jogo, se sim sinaliza para os desenhos

#ifdef _WIN32

// Função que é chamada no inicio de cada jogo, preparando para jogar, apenas para o multiplayer:
void criarNovaSala(Carta **cartas_jogador1, Carta **cartas_jogador2, int quantidades_cartas[2], int cartas_escolhidas[32])
{

    // Preencher o array com valores possiveis de cartas, ids possiveis de acesso ao vetor de cartas:
    for (int i = 0; i < 32; i++)
    {
        cartas_escolhidas[i] = i;
    }

    // Embaralhar o array, usando random:
    for (int i = 31; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = cartas_escolhidas[i];
        cartas_escolhidas[i] = cartas_escolhidas[j];
        cartas_escolhidas[j] = temp;
    }

    for (int k = 0; k < 32; k++)
    {
        if (k % 2 == 0)
        {
            // Copia vetor cartas para o jogador1:
            quantidades_cartas[0]++;
            *cartas_jogador1 = (Carta *)realloc(*cartas_jogador1, quantidades_cartas[0] * sizeof(Carta));
            (*cartas_jogador1)[quantidades_cartas[0] - 1] = cartas_multiplayer[cartas_escolhidas[k]];
        }
        else
        {
            // Copia vetor cartas para o jogador2:
            quantidades_cartas[1]++;
            *cartas_jogador2 = (Carta *)realloc(*cartas_jogador2, quantidades_cartas[1] * sizeof(Carta));
            (*cartas_jogador2)[quantidades_cartas[1] - 1] = cartas_multiplayer[cartas_escolhidas[k]];
        }
    } // For que copia as informações das cartas aleatorias geradas para cada baralho, atualizando tambem a quantidade de cartas

    return;
} // Fim função preparadora da sala do multiplayer

// Função que aleatoriza um id para sala, para inciar um novo jogo:
int aleatorizarSala()
{
    int sala = 0;

    do
    {
        for (int s = 0; s < 8; s++)
        {
            sala += rand() % 10 * pow(10, s);
        }
    } while (sala < 10000000 || verificarSalaVazia(sala));

    snprintf(buffer, sizeof(buffer), "Sala multiplayer criada, id: %d\n", sala);
    escreverLog(buffer);

    return sala;
}

// Função que é chamada após o jogador 2 conectar a sala, ele recebe e cria os vetores de carta, e ec..
void EntrarSala(Carta **cartas_jogador1, Carta **cartas_jogador2, int quantidades_cartas[2], int cartas_escolhidas[32])
{
    for (int k = 0; k < 32; k++)
    {
        if (k % 2 != 0)
        {
            // Copia vetor cartas para o jogador1:
            quantidades_cartas[0]++;
            *cartas_jogador1 = (Carta *)realloc(*cartas_jogador1, quantidades_cartas[0] * sizeof(Carta));
            (*cartas_jogador1)[quantidades_cartas[0] - 1] = cartas_multiplayer[cartas_escolhidas[k]];
        }
        else
        {
            // Copia vetor cartas para o jogador2:
            quantidades_cartas[1]++;
            *cartas_jogador2 = (Carta *)realloc(*cartas_jogador2, quantidades_cartas[1] * sizeof(Carta));
            (*cartas_jogador2)[quantidades_cartas[1] - 1] = cartas_multiplayer[cartas_escolhidas[k]];
        }
    } // For que copia as informações das cartas aleatorias geradas para cada baralho, atualizando tambem a quantidade de cartas

    return;
}

#endif