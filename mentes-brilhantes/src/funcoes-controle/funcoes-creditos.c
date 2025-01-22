// QUALQUER DEPENDENCIA FORA A DESENHOS DA TELA DE CRÉDITOS

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "funcoes-controle-geral.h"
#include "desenho-geral.h"
#include "cores.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "desenho-creditos.h"

void creditos(RenderTexture2D *target, Music *musica, Sound sons[])
{

    //---------------------------------
    // VARIAVEIS LOCAIS
    //---------------------------------
    Botao botoes[1];
    long int contador_tempo[2] = {0, 0}; // Contadores de tempo baseado em FPS
    char texto[135][512];
    char linha[512]; // Usado de buffer do texto
    int tamanho_texto = 0;
    int *posicoes_desenho_txt;
    int posicoes_desenho_cartas[3];
    int quantidade_cartas_desenhadas = 0;
    int animacoes_ativas[2] = {1,1};

    Carta *cartas_totais;
    Carta cartas_fundo[3];

    Texture2D imagens_cartas[3];

    botoes[0].colisao = criarBotao(&botoes[0], 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);

    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-jogo.png");          // Carrega a imagem do fundo desse menu
    Texture2D frente_carta = LoadTexture("img/frente_carta.png"); // Carrega a imagem do frame frontal da carta

    // Abrindo e carregando o conteudo para ser exibido:
    FILE *arquivo_creditos;

    arquivo_creditos = fopen("./data/creditos.txt", "r");

    if (arquivo_creditos == NULL)
    {
        perror("Erro ao abrir o arquivo de creditos\n");
        exit(1);
    } // Verifica se o arquivo abriu

    while (fgets(linha, 512, arquivo_creditos))
    {
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(texto[tamanho_texto], linha);
        tamanho_texto++;
    } // Percorre todo o arquivo salvando em texto

    fclose(arquivo_creditos); // Fecha o arquivo

    posicoes_desenho_txt = (int *)calloc(tamanho_texto, sizeof(int));

    for (int s = 0; s < tamanho_texto; s++)
    {
        posicoes_desenho_txt[s] = 607 + (34 * s);
    }

    posicoes_desenho_cartas[0] = -457;
    posicoes_desenho_cartas[1] = 607;
    posicoes_desenho_cartas[2] = -457;

    // Abrindo o arquivo de cartas do creditos:
    // Variaveis:
    int capacidade = 64;  // Capacidade inicial do array de
    int tamanho = 0;      // Contagem das linhas lidas do arquivo
    char super_trunfo[6]; // Para uso se é supertrunfo durante a leitura

    // Abre o arquivo:
    FILE *arquivo = fopen("./data/bancoCreditos.csv", "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo de cartas de creditos\n");
        exit(1);
    } // Verifica se o arquivo existe e abre-o

    // Alocação:
    cartas_totais = (Carta *)malloc(capacidade * sizeof(Carta));
    if (cartas_totais == NULL)
    {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return;
    } // Aloca o vetor de cartas inicialmente para 64 - se houver mais o realoc trata

    // Le cada linha do arquivo:
    while (fgets(linha, 512, arquivo))
    {
        if (tamanho >= capacidade)
        {
            capacidade = 2; // Aumenta a capacidade para +2 e realoca
            cartas_totais = (Carta *)realloc(cartas_totais, capacidade * sizeof(Carta));
            if (cartas_totais == NULL)
            {
                perror("Erro ao realocar memória");
                fclose(arquivo);
                return;
            }
        } // Se nescessario realocar memoria

        // A cada linha lida quebra o txt em pedaços e salva no c para ser enviado para cartas:
        Carta c;
        sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,],%u,%u,%u,%u", &c.id, super_trunfo, c.hexadecimal, c.imagem, c.nome, &c.curiosidade, &c.criatividade, &c.inovacao, &c.idade);

        c.super_trunfo = (strcmp(super_trunfo, "true") == 0); // Verifica se é supertrunfo e manda para p

        cartas_totais[tamanho++] = c; // Cartas na posição do tamnho atual recebe o c
    } // Percorre todo o arquivo

    fclose(arquivo); // Fecha o arquivo

    for (int v = 0; v < 3; v++)
    {
        cartas_fundo[v] = cartas_totais[v];
        imagens_cartas[v] = LoadTexture(cartas_fundo[v].imagem);
    }

    //---------------------------------
    // LOOP GERAL
    //---------------------------------

    while (tela == 4)
    {

        //---------------------------------
        // CONTROLES GERAIS
        //---------------------------------

        // ESCALA:
        scaleX = (float)GetScreenWidth() / COMPRIMENTO_TELA;
        scaleY = (float)GetScreenHeight() / ALTURA_TELA;
        scale = (scaleX < scaleY) ? scaleX : scaleY;

        checarSaida();     // Chama a função que verifica se o usuário saiu
        checarTelaCheia(); // Chama função que verifica as condições de tela cheia
        leMouse();
        controleSons(0, *musica, sons[0]);
        desenhaCreditos(target, &botoes[0], fundo, contador_tempo, texto, posicoes_desenho_txt, tamanho_texto, cartas_fundo, imagens_cartas, posicoes_desenho_cartas, frente_carta);

        contador_tempo[0]++;

        //Controle das animações:

        if(IsMouseButtonPressed(0)){
            animacoes_ativas[1] =  !animacoes_ativas[1];
        }

        if(IsMouseButtonPressed(1)){
            animacoes_ativas[0] =  !animacoes_ativas[0];
        }

        if (contador_tempo[0] % 3 != 0 && animacoes_ativas[1])
        {
            for (int p = 0; p < tamanho_texto; p++)
            {
                posicoes_desenho_txt[p]--;
            }
        }

        if (animacoes_ativas[0])
        {
            posicoes_desenho_cartas[0]++;
            posicoes_desenho_cartas[1]--;
            posicoes_desenho_cartas[2]++;
        }

        if (posicoes_desenho_cartas[2] >= 607)
        {
            quantidade_cartas_desenhadas++;
            posicoes_desenho_cartas[0] = -457;
            posicoes_desenho_cartas[1] = 607;
            posicoes_desenho_cartas[2] = -457;
            for (int v = 0; v < 3; v++)
            {
                cartas_fundo[v] = cartas_totais[v + 3 * quantidade_cartas_desenhadas];
                imagens_cartas[v] = LoadTexture(cartas_fundo[v].imagem);
            }
        }

        if (quantidade_cartas_desenhadas == 4)
        {
            quantidade_cartas_desenhadas = -1;
        }

        //---------------------------------
        // CONTROLES BOTOES
        //---------------------------------

        if (checarClique(&botoes[0].colisao) && estado_tela != 2)
        {
            estado_tela = 2;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes[0].cor_botao = GREEN;
            trocar_tela = true;
        } // Voltar Menu

        //---------------------------------
        // CONTROLES TELAS
        //---------------------------------

        switch (estado_tela)
        {
        case 2:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(fundo);
                free(posicoes_desenho_txt);
                free(cartas_totais);
                tela = 2;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }
    }

    return;
}