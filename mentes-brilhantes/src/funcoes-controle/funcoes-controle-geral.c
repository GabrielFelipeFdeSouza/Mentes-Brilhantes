// FUNÇÕES PARA AS FUNÇÕES DE CONTROLE - SEM SER PARTE DE DESENHO:

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "cores.h"
#include "desenho-geral.h"
#include "funcoes-controle-geral.h"

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

bool coresIguais(Color c1, Color c2)
{
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
} // Função que verifica se duas cores são iguais

void leMouse()
{
    // Obtemos as posições brutas do mouse na janela
    posicao_mouse.x = GetMouseX();
    posicao_mouse.y = GetMouseY();

    // Ajustamos a posição X do mouse para o sistema de coordenadas do jogo
    posicao_mouse.x = (posicao_mouse.x - (GetScreenWidth() - (COMPRIMENTO_TELA * scale)) * 0.5f) / scale;

    // Ajustamos a posição Y do mouse para o sistema de coordenadas do jogo
    posicao_mouse.y = (posicao_mouse.y - (GetScreenHeight() - (ALTURA_TELA * scale)) * 0.5f) / scale;

    return;
} // Função de leitura da posição do cursor em relação à janela aberta

void checarSaida()
{

    if (WindowShouldClose())
    {
        tela = 10;
    } // Se a tela for fechada pelo usuário ou funções de sair, seta tela = 10 para uso na main

    return;
} // Função que verifica se o usuário quer sair

bool checarClique(Rectangle *botao)
{
    if (IsMouseButtonPressed(0) && CheckCollisionPointRec(posicao_mouse, *botao))
    {
        return true;
    }
    else
    {
        return false;
    }
} // Função que checa clique do mouse em um botão, além da colisão

void controleSons(int controle, Music musica, Sound som)
{
    switch (controle)
    {
    case 1:
        if (esta_mudo == false)
        {
            PlaySound(som); // Toca apenas uma vez o som do input
        }
        break;

    case 2:
        SetMusicVolume(musica, 0); // Tira o som da musica
        break;

    case 3:
        SetMusicVolume(musica, 1); // Recoloca o som do jogo com som 1
        break;

    default:
        UpdateMusicStream(musica); // Mantem a musica tocando
        break;
    }

    return;
} // Função que controla as musicas e sons ao ser chamada

void checarTelaCheia()
{
    if (IsKeyPressed(KEY_F11))
    {
        int display = GetCurrentMonitor(); // mostra em qual monitor estamos, caso tenha mais de 1

        // if (IsWindowFullscreen())
        if (GetScreenWidth() > 1000)
        {
            // Se estiver já em tela cheia:
            // ToggleFullscreen();                                // Tira de telacheia
            SetWindowSize(COMPRIMENTO_TELA, ALTURA_TELA);      // Seta o tamanho da tela para o original
            SetWindowPosition(posicao_tela.x, posicao_tela.y); // Seta a posição para o meio
        }
        else
        {
            posicao_tela = GetWindowPosition();                                 // Obtem a posição de tela antes de redimensionar para mudar depois
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display)); // Seta para o tamanho max do monitor
            SetWindowPosition(0, 0);                                            // Seta a posição para o 0,0 do monitor
            // ToggleFullscreen();                                                 // Coloca em telacheia
        }

    } // Fim if muda estado pelo F11

    return;
} // Função que checa estados de tela cheia e tecla F11 para togle disso

void abrePdf()
{

    InitWindow(500, 250, "PDF DE REGRAS");
    SetTargetFPS(60); // Setando o framerate da raylib para 60
    ShowCursor();
    Botao botoes_pdf[2];
    botoes_pdf[0].colisao = criarBotao(&botoes_pdf[0], 125, 120, NOSSO_AZUL, "SIM", 40, GREEN);
    botoes_pdf[1].colisao = criarBotao(&botoes_pdf[1], 280, 120, NOSSO_AZUL, "NÃO", 40, RED);
    while (!WindowShouldClose())
    {
        posicao_mouse.x = GetMouseX();
        posicao_mouse.y = GetMouseY();
        BeginDrawing();
        ClearBackground(NOSSO_BEGE);
        DrawText(TextFormat("DETECTADA PRIMEIRA ENTRADA NO JOGO"), 26, 15, 20, BLACK);
        DrawText(TextFormat("DESEJA ABRIR O PDF DE REGRAS?"), 11, 55, 27, NOSSO_AZUL);
        EndDrawing();
        for (int t = 0; t < 2; t++)
        {
            desenharBotaoTxt(botoes_pdf[t]);
        } // Desenha todos os botões

        for (int u = 0; u < 2; u++)
        {

            if (CheckCollisionPointRec(posicao_mouse, botoes_pdf[u].colisao))
            {
                botoes_pdf[u].cor_botao = NOSSO_CIANO;
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            }
            else
            {
                botoes_pdf[u].cor_botao = NOSSO_AZUL;
            }
        } // Resalta botoes nulos

        if (checarClique(&botoes_pdf[0].colisao))
        {
#ifdef _WIN32
            system("start ./data/instrucoes.pdf");
#elif __linux__
            system("xdg-open ./data/instrucoes.pdf");
#else
            escreverLog("Sistema operacional não suportado. PDF não será aberto!");
#endif
            CloseWindow();
        }

        if (checarClique(&botoes_pdf[1].colisao))
        {
            CloseWindow();
        }
    }
}

void checaRadioButton(RadioButton btns_radio[], int qtd_btn_radio, int grupo_selecionado)
{
    for (int i = 0; i < qtd_btn_radio; i++)
    {
        if (btns_radio[i].grupo == grupo_selecionado)
        {
            if (IsMouseButtonPressed(0) && CheckCollisionPointCircle(posicao_mouse, btns_radio[i].centro, btns_radio[i].raio))
            {
                btns_radio[i].estado = true; // define o clicado como true
                for (int u = 0; u < qtd_btn_radio; u++)
                {
                    if (strcmp(btns_radio[i].texto, btns_radio[u].texto) != 0)
                    {
                        btns_radio[u].estado = false; // desativa todos os que nao sao o ultimo clicado
                    }
                }
            }
        }
    }

    return;
} // Função que checa qual radio button dever ser ligado pelo clique do usuário

void leTeclado(char *string, int *conta_tecla, int subgrupo, int limitador)
{
    int tecla;
    tecla = GetCharPressed();

    switch (subgrupo)
    {
    case 0:
        while (tecla > 0)
        {
            if ((tecla >= 32) && (tecla <= 125) && ((*conta_tecla) < limitador))
            {
                string[*conta_tecla] = (char)tecla;
                string[*conta_tecla + 1] = '\0';
                (*conta_tecla)++;
            }
            tecla = GetCharPressed();
        }
        break;

    case 2:
        while (tecla > 0)
        {
            if ((tecla >= 48) && (tecla <= 57) && ((*conta_tecla) < limitador))
            {
                string[*conta_tecla] = (char)tecla;
                string[*conta_tecla + 1] = '\0';
                (*conta_tecla)++;
            }
            tecla = GetCharPressed();
        }
        break;

    default:
        break;
    }

    if (IsKeyPressed(KEY_BACKSPACE) && (*conta_tecla > 0))
    {
        (*conta_tecla)--;
        string[*conta_tecla] = '\0';
    }

    return;
}

void checaSeletor(Seletor caixas[], int qtd__caixas_seletor, int grupo_selecionado)
{
    for (int i = 0; i < qtd__caixas_seletor; i++)
    {
        if (caixas[i].grupo == grupo_selecionado)
        {
            if (IsMouseButtonPressed(0) && CheckCollisionPointRec(posicao_mouse, caixas[i].quadrado))
            {
                caixas[i].estado = !caixas[i].estado; // define o clicado como true
            }
        }
    }

    return;
} // Função que checa quais seletor estao selecionados pelo clique do usuário


void resetarCartas(){

    quantidade_cartas = 32;

    cartas = realloc(cartas, 32 * sizeof(Carta));

    for(int s = 0; s < 32; s++){
        cartas[s] = cartas_multiplayer[s];
    }

} //Função que reseta cartas para as originais, usando as cartas do multiplayer que são as mesmas do banco original
