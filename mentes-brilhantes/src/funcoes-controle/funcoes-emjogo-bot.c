// FUNÇÕES PARA A TELA DE EM JOGO COM BOT - SEM SER PARTE DE DESENHO

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
#include "desenho-game-bot.h"
#include <time.h>

//---------------------------------
// FUNÇAO PRINCIPAL
//---------------------------------

void jogarSingleplayer(RenderTexture2D *target, Music *musica, Sound sons[])
{

    //---------------------------------
    // VARIAVEIS LOCAIS
    //---------------------------------

    int submenu_tela = 0; // Variavel do submenus do jogo - ajuda para correta lógica das telas - começa em configurações da partida
    Botao botoes[2];
    int dificuldade;                               // Variavel usada para fazer o sistema de gameplay do jogo
    int quantidades_cartas[2] = {0, 0};            // Quantidade de cartas do bot e jogador nessa ordem
    long int contador_tempo[4] = {179, 0, 0, 211}; // Contadores de tempo baseado em FPS
    int id_imagem = -1;                            // Usado para carregar a imagem da carta
    int id_imagem_bot = -1;                        // Usado para carregar a imagem da carta
    Texture2D img_carta;
    Texture2D img_carta_bot;
    int vezJogar = 1;     // Começa jogando o player
    int btn_clicado = -1; // Botao clicado por ultimo do jogador
    bool clicado_btn = false;

    //---------------------------------
    // INICIALIZANDO OS VETORES E AS IMAGENS
    //---------------------------------

    // Incializando os vetores de cartas do bot e do jogador:
    Carta *cartas_bot = NULL;
    Carta *cartas_jogador = NULL;
    cartas_jogador = (Carta *)malloc(sizeof(Carta));
    cartas_bot = (Carta *)malloc(sizeof(Carta));
    Carta carta;     // Carta usada para ser desenhada na tela
    Carta carta_bot; // Carta usada para ser desenhada na tela

    botoes[0].colisao = criarBotao(&botoes[0], 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);
    botoes[1].colisao = criarBotao(&botoes[1], 65, 265, NOSSO_AZUL, "INICIAR JOGO", 26, NOSSO_CINZA);

    RadioButton botoes_radio[3];
    botoes_radio[0] = (RadioButton){0, "Fácil", {75, 160}, 12, NOSSO_BEGE, true, 1};
    botoes_radio[1] = (RadioButton){1, "Médio", {75, 195}, 12, NOSSO_BEGE, false, 1};
    botoes_radio[2] = (RadioButton){2, "Difícil", {75, 230}, 12, NOSSO_BEGE, false, 1};

    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-jogo.png");          // Carrega a imagem do fundo desse menu
    Texture2D fundo_carta = LoadTexture("img/fundo-carta.png");   // Carrega a imagem do fundo desse menu
    Texture2D frente_carta = LoadTexture("img/frente_carta.png"); // Carrega a imagem do frame frontal da carta

    //---------------------------------
    // LOOP GERAL
    //---------------------------------

    while (tela == 3)
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
        desenhaJogoSingleplayer(target, &botoes[0], fundo, botoes_radio, submenu_tela, contador_tempo, &img_carta, &carta, &frente_carta, quantidades_cartas, vezJogar, &img_carta_bot, &carta_bot, fundo_carta, btn_clicado);

        //---------------------------------
        // CONTROLES DO JOGO
        //---------------------------------

        if (submenu_tela == 0)
        {
            if (checarClique(&botoes[1].colisao) && estado_tela != 2)
            {
                controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
                botoes[1].cor_botao = GREEN;

                for (int u = 0; u < 3; u++)
                {
                    if (botoes_radio[u].estado)
                    {
                        dificuldade = u;
                        break;
                    }
                }

                submenu_tela = 1;
                iniciar_jogo(&cartas_bot, &cartas_jogador, dificuldade, quantidades_cartas);

            } // Iniciar Jogo
        }

        if (submenu_tela == 1)
        {
            contador_tempo[0]--;
            if (contador_tempo[0] <= 0)
            {
                submenu_tela = 2;
            }
        } // Contador para incio do jogo

        if (submenu_tela == 2)
        {
            contador_tempo[1]++; // Cronometro global

            // Alteração das cartas e imagens desenhadas:
            carta = cartas_jogador[0];
            if (id_imagem != carta.id)
            {
                id_imagem = carta.id;
                UnloadTexture(img_carta);
                img_carta = LoadTexture(carta.imagem);
            } // Usado para carregar a textura de uma carta apenas na troca de carta

            carta_bot = cartas_bot[0];
            if (id_imagem_bot != carta_bot.id)
            {
                id_imagem_bot = carta_bot.id;
                UnloadTexture(img_carta_bot);
                img_carta_bot = LoadTexture(carta_bot.imagem);
            } // Usado para carregar a textura de uma carta apenas na troca de carta

            // Cliques do jogador e do bot ao jogar:

            if (vezJogar == 1 && btn_clicado == -1 && contador_tempo[3] > 210)
            {
                btn_clicado = btnsCartasClicados(15, 130);
                if (btn_clicado != -1)
                {
                    clicado_btn = true;
                    contador_tempo[3] = 0;
                }
            } // Vez do jogador de jogar

            if (vezJogar == 0 && btn_clicado == -1 && contador_tempo[3] > 410)
            {
                btn_clicado = iaBot(cartas_bot, dificuldade);
                if (btn_clicado != -1)
                {
                    clicado_btn = true;
                    contador_tempo[3] = 0;
                }

            } // Vez do bot de jogar

            // Interpretador de cliques e ia do bot:

            if (vezJogar == 1 && clicado_btn == true && contador_tempo[3] > 209)
            {
                clicado(&btn_clicado, &cartas_bot, &cartas_jogador, quantidades_cartas);
                clicado_btn = false;
                contador_tempo[2] = 0;
                checaVitoria(quantidades_cartas, &submenu_tela);
                vezJogar = 0;
            }

            if (vezJogar == 0 && clicado_btn == true && contador_tempo[3] > 209)
            {
                clicado(&btn_clicado, &cartas_bot, &cartas_jogador, quantidades_cartas);
                clicado_btn = false;
                contador_tempo[2] = 0;
                checaVitoria(quantidades_cartas, &submenu_tela);
                vezJogar = 1;
            }

            // Contador de tempo secundário das ações:

            if (contador_tempo[3] < 420)
            {
                contador_tempo[3]++;
            }

        } // Em jogo

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
                free(cartas_bot);
                free(cartas_jogador);
                tela = 2;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }
    }

    return;
}

//---------------------------------
// FUNÇOES ADICIONAIS
//---------------------------------

void iniciar_jogo(Carta **cartas_bot, Carta **cartas_jogador, int dificuldade, int quantidades_cartas[2])
{
    int cartas_escolhidas[quantidade_cartas]; // Usado para determinar os indices das cartas de cada jogador

    (void)dificuldade;

    // Preencher o array com valores possiveis de cartas:
    for (int i = 0; i < quantidade_cartas; i++)
    {
        cartas_escolhidas[i] = i;
    }

    // Embaralhar o array:
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

void clicado(int *btn_clicado, Carta **cartas_bot, Carta **cartas_jogador, int *quantidades_cartas)
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
            }
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
            }
        }

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
            }
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
            }
        }
    }
    else
    {
        //---------------------------------
        // DEMAIS CASOS
        //---------------------------------

        switch (*btn_clicado)
        {
        case 0:

            if ((*cartas_jogador)[0].curiosidade >= (*cartas_bot)[0].curiosidade)
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
                break;
            }

            if ((*cartas_jogador)[0].curiosidade < (*cartas_bot)[0].curiosidade)
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
                break;
            }
            break;
        case 1:

            if ((*cartas_jogador)[0].criatividade >= (*cartas_bot)[0].criatividade)
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
                break;
            }

            if ((*cartas_jogador)[0].criatividade < (*cartas_bot)[0].criatividade)
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
                break;
            }
            break;
        case 2:

            if ((*cartas_jogador)[0].inovacao >= (*cartas_bot)[0].inovacao)
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
                break;
            }

            if ((*cartas_jogador)[0].inovacao < (*cartas_bot)[0].inovacao)
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
                break;
            }
            break;
        case 3:

            if ((*cartas_jogador)[0].idade >= (*cartas_bot)[0].idade)
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
                break;
            }

            if ((*cartas_jogador)[0].idade < (*cartas_bot)[0].idade)
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
                break;
            }
            break;
        default:
            break;
        }
    }

    *btn_clicado = -1; // Reset do botão para a próxima jogada

    // Exibição do baralho atual de cada:

    printf("\nBaralho Player:\n");

    for (int t = 0; t < quantidades_cartas[1]; t++)
    {
        printf("%s\n", (*cartas_jogador)[t].nome);
    }

    printf("\nBaralho Bot:\n");

    for (int t = 0; t < quantidades_cartas[0]; t++)
    {
        printf("%s\n", (*cartas_bot)[t].nome);
    }

    return;
} // Função que trata das condições de ganho de cada rodada

void empate()
{

    return;
} // Função que trata dos casos de empate

int iaBot(Carta *cartas_bot, int dificuldade)
{
    int random_start[4];
    random_start[0] = cartas_bot[0].curiosidade;
    random_start[1] = cartas_bot[0].criatividade;
    random_start[2] = cartas_bot[0].inovacao;
    random_start[3] = cartas_bot[0].idade;

    int candidatos[4], j = 0;

    switch (dificuldade)
    {
    case 0:
    { // Remover os dois maiores valores
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
    }
    case 1:
    { // Remover o maior valor

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
    }
    case 2:
    { // Remover os dois menores valores
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
    }
    default:
        return -1; // Retorna -1 para dificuldade inválida
    }

    // Randomizar entre os valores restantes

    int escolha_aleatoria = rand() % j; // Randomiza entre 0 e j-1

    return candidatos[escolha_aleatoria];

} // Função que simula uma ia de escolhas do bot baseado na dificuldade

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