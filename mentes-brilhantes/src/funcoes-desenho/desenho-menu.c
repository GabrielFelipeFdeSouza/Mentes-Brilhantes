// FUNÇÕES DE DESENHO PARA A TELA DE MENU GERAL

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "desenho-menu.h"
#include "desenho-geral.h"
#include "funcoes-controle-geral.h"
#include "cores.h"

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

void desenhoMenu(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, BotaoNulo botao, Texture2D img_btn_som, Texture2D fundo)
{
    BeginTextureMode(*target); //Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(RAYWHITE); //Fundo da tela

    DrawTexture(fundo, 0, 0, WHITE);

    for(int t = 0; t < quantidade_botoes; t++){
    desenharBotaoTxt(botoes[t]);
    } //Desenha todos os botões

    for(int y = 0; y < quantidade_botoes; y++){
        if(CheckCollisionPointRec(posicao_mouse, botoes[y].colisao)){
            break;
        }
        if(y == quantidade_botoes-1){
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    } //For que arruma o tipo de cursor nos botoes normais


    DrawText(TextFormat("Posição do mouse: (%.2f,%.2f) - FPS: %d", posicao_mouse.x, posicao_mouse.y, GetFPS()), 1, 1, 20, RED);
    desenharBotaoNulo(botao); //Desenha os botões nulos, nesse caso o da imagem de som
    DrawTexture(img_btn_som, 916, 525, WHITE);
    EndTextureMode();

    desenhoRedimensionado(target); //Chama a função que desenha redimensionadamente

    return;
}
