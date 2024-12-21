//Função que desenhe na tela (qualquer) os seguintes itens padrões:

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "desenho-geral.h"
#include "funcoes-controle-geral.h"
#include "cores.h"

int criarBotaoTxtRedimensionavel(Botao *botao, int x, int y, int width, int height, Color cor_fundo, char texto[], Color cor_texto)
{

    // Começa com um tamanho base
    int fontSize = 20;
    
    // Mede o texto com a fonte padrão e o tamanho base
    int textWidth = MeasureText(texto, fontSize);

    // Calcula o fator de escala com base no comprimento do texto e no quadrado
    float scaleFactor = ((float)width / textWidth) - 0.13f;
    
    //Atribui as caracteristicas da criação:
    botao->cor_botao = cor_fundo;
    botao->cor_texto = cor_texto;
    strcpy(botao->texto, texto);
    botao->colisao.width = width;
    botao->colisao.height = height;
    botao->colisao.x = x;
    botao->colisao.y = y;

    return (int) fontSize * scaleFactor; //Retorno do tamanho da fonte ajustado
}

Rectangle criarBotao(Botao *botao, int x, int y, Color cor_fundo, char texto[], int tamanho_fonte, Color cor_texto)
{
    
    //Atribui as caracteristicas da criação:
    botao->cor_botao = cor_fundo;
    botao->cor_texto = cor_texto;
    botao->tamanho_fonte_texto = tamanho_fonte;
    strcpy(botao->texto, texto);

    // declaracao de variaveis
    float largura_fonte = 0.0f;

    // verifica o tamanho do texto
    largura_fonte = MeasureText(botao->texto, (int)botao->tamanho_fonte_texto);

    // define o botao com as proporcoes corretas
    Rectangle colisao_botao = {x, y, (int)largura_fonte + 14, (int)tamanho_fonte + 14};

    // retorna a caixa de colisao para ser checada depois
    return colisao_botao;
}

void desenharBotaoTxt(Botao botao)
{

    DrawRectangle(-4 + botao.colisao.x, -4 + botao.colisao.y, 8 +botao.colisao.width, 8 + botao.colisao.height, NOSSO_AMARELO);
    DrawRectangle(botao.colisao.x, botao.colisao.y, botao.colisao.width, botao.colisao.height, botao.cor_botao);
    DrawText(botao.texto, (2 * botao.colisao.x + botao.colisao.width - MeasureText(botao.texto, botao.tamanho_fonte_texto)) * 0.5, ((2 * botao.colisao.y + botao.colisao.height - botao.tamanho_fonte_texto) * 0.5), botao.tamanho_fonte_texto, botao.cor_texto);

    return;
}

void desenharBotaoNulo(BotaoNulo botao)
{

    DrawRectangle(-4 + botao.colisao.x, -4 + botao.colisao.y, 8 +botao.colisao.width, 8 + botao.colisao.height, NOSSO_AMARELO);
    DrawRectangle(botao.colisao.x, botao.colisao.y, botao.colisao.width, botao.colisao.height, botao.cor_botao);

    return;
}

bool resaltaBotoes(Botao botoes[], int quantidade_botoes, Music musica, Sound som_clique_btn, BotaoNulo botoes_nulos[], int quantidade_botoes_nulos, BotaoNulo botoes_invisiveis[], int quantidade_botoes_invisiveis)
{

    for(int u = 0; u < quantidade_botoes_nulos; u++)
    {

        if(CheckCollisionPointRec(posicao_mouse, botoes_nulos[u].colisao))
        {
            botoes_nulos[u].cor_botao = NOSSO_CIANO;
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            return true;
        } else{
            botoes_nulos[u].cor_botao = NOSSO_AZUL;
        }
    } //Resalta botoes nulos

    for(int u = 0; u < quantidade_botoes_invisiveis; u++)
    {
        if(CheckCollisionPointRec(posicao_mouse, botoes_invisiveis[u].colisao))
        {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            return true;
        } else{
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    } //Resalta botoes invisiveis

    for(int t = 0; t < quantidade_botoes; t++)
    {
        if(!coresIguais(botoes[t].cor_botao, GREEN)){
        botoes[t].cor_botao = NOSSO_AZUL;
        }
    } //For que evita cores ciano infinitas em botões muito próximos

    for(int u = 0; u < quantidade_botoes; u++)
    {
        if(CheckCollisionPointRec(posicao_mouse, botoes[u].colisao))
        {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

            if(coresIguais(botoes[u].cor_botao, NOSSO_AZUL))
            {
                controleSons(1, musica, som_clique_btn); //Função de controle geral sons - toca o som de mouse sob o btn
            } //If evita varias tocadas do mesmo som

            if(!coresIguais(botoes[u].cor_botao, GREEN))
            {
                botoes[u].cor_botao = NOSSO_CIANO; //Muda cor fundo botão
            } //Evita que mude a cor do botão se for verde
            return true;

        } else{
            
            if(!coresIguais(botoes[u].cor_botao, GREEN))
            {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                botoes[u].cor_botao = NOSSO_AZUL; //Muda cor fundo botão 
            } //Evita que mude a cor do botão se for verde
        }
    }

    return false;
}


void desenhaCarta(int x, int y, Texture2D *frente_carta, Carta *carta, Texture2D *img_carta)
{

    DrawRectangle(x + 15, y + 45, 260 , 175, NOSSO_CREME);

    DrawTextureEx(*img_carta, (Vector2){x+61, y+53}, 0.0f, 1.75f, WHITE);

    DrawTextureEx(*frente_carta, (Vector2){x, y}, 0.0f, 1.75f, WHITE); //Desenha a carta 

    for(int t = 0; t < 4; t++){
        DrawRectangle(x + 21, y + 244 + t * 45, 244, 35, NOSSO_BEGE);
    }

    if(carta->hexadecimal[0] == '9' && carta->hexadecimal[1] == 'Z'){
        DrawText(TextFormat("SEM CARTAS QUE", carta->inovacao), x+25 , y+100 , 26, RED);
        DrawText(TextFormat("CORRESPONDEM!", carta->inovacao), x+30 , y+129 , 26, RED);
    }

    DrawText(TextFormat("CURIOSIDADE: %d", carta->curiosidade), x + 25, y + 251, 25, BLUE);
    DrawText(TextFormat("CRIATIVIDADE: %d", carta->criatividade), x + 25, y + 296, 25, DARKGREEN);
    DrawText(TextFormat("INOVAÇÃO: %d", carta->inovacao), x + 25, y + 341, 25, RED);
    DrawText(TextFormat("IDADE: %d", carta->idade), x + 25, y + 386, 25, DARKPURPLE);

    DrawText(TextFormat("%s", carta->nome), x + 82, y + 25, 27, BLACK);
    DrawCircle(x + 20 + (MeasureText(carta->hexadecimal, 33) / 2), y + 32, 26, BLACK);
    DrawCircle(x + 20 + (MeasureText(carta->hexadecimal, 33) / 2), y + 32, 25, GOLD);
    DrawText(TextFormat("%s", carta->hexadecimal), x + 20, y + 20, 33, DARKBLUE);
    

    if(carta->super_trunfo == true){
        const char *texto = "SUPER TRUNFO";
        DrawRectangle(x + 16, y + 200, MeasureText(texto, 30) + 13, 40, NOSSO_BEGE);

        int espacador = 2; //Espaçador dos chars
        static int contador_velocidade = 0;  // Persistência entre frames

        //Inicializa as cores apenas na primeira execução dessa função:
        if (cor_aleatoria == NULL){

            cor_aleatoria = (Color*) malloc(strlen(texto) * sizeof(Color));
            
            for (int f = 0; f < (int) strlen(texto); f++) {
                cor_aleatoria[f] = (Color){ GetRandomValue(10, 255), GetRandomValue(10, 255), GetRandomValue(10, 255), 255 };
            }
        } //Aloca memória e atribui cores iniciais se não foi inicializado ou se o tamanho do struct é menor que o nescessário

        //Troca as cores a cada 9 frames:
        if (contador_velocidade >= 9) {
            contador_velocidade = 0; //Reseta o contador de frames
            for (int i = 0; i < (int) strlen(texto); i++) {
                cor_aleatoria[i] = (Color){ GetRandomValue(10, 255), GetRandomValue(10, 255), GetRandomValue(10, 255), 255 };
            } //Novas cores aleatorias
        }

        //Desenha o texto com as cores atuais, ja definidas
        for (int w = 0; w < (int) strlen(texto); w++) {
            DrawText(TextFormat("%c", texto[w]), x + 22 + espacador, y + 205, 30, cor_aleatoria[w]);
            espacador += MeasureText(TextFormat("%c", texto[w]), 30) + 2;
        }

        contador_velocidade++;
    } //Se for super trunfo desenha txt especial

    return;
} //Função que desenha a carta na tela, a partir de x,y

void desenhoRedimensionado(RenderTexture2D *target)
{
    
    BeginDrawing(); //COMEÇO DESENHO REDIMENSIONADO

    ClearBackground(BLACK); //BARRAS PRETAS NA PARTE INUTIL DA TELA

    DrawTexturePro(target->texture,
        (Rectangle){ 0.0f, 0.0f, (float)target->texture.width, (float)-target->texture.height },
        (Rectangle){
            (GetScreenWidth() - ((float)COMPRIMENTO_TELA * scale)) * 0.5f,
            (GetScreenHeight() - ((float)ALTURA_TELA * scale)) * 0.5f,
            (float)COMPRIMENTO_TELA * scale,
            (float)ALTURA_TELA * scale
        },
         (Vector2){ 0, 0 },
         0.0f,
         WHITE); 

    EndDrawing(); //FIM DESENHO REDIMENSIONADO

    return;
}

void telaErro(char txt_erro[255])
{

    InitWindow(COMPRIMENTO_TELA, ALTURA_TELA, "Mentes Brilhantes - ERRO"); // Inicialização da tela de erro
    SetWindowState(FLAG_WINDOW_UNFOCUSED);  // Seta a tela para rodar, mesmo se não focada, mas se minimizada pelo botão, congela
    SetTargetFPS(60); // Setando o framerate da raylib para 60

    do{

        BeginDrawing(); //Inicio desenho
        ClearBackground(RAYWHITE); //Fundo da tela

        DrawText(TextFormat("TELA DE ERRO:"), 310, 10, 40, BLACK);
        DrawText(TextFormat("%s", txt_erro), 20, 58, 32, RED);

        EndDrawing(); //Fim desenho

    }while(!WindowShouldClose());

    CloseWindow();

    return;
}

void desenhaRadioButton(RadioButton botoes[], int quantidade_botoesradio, int grupo_selecionado)
{    

    for(int i = 0; i < quantidade_botoesradio; i++)
    {   
        if (botoes[i].grupo == grupo_selecionado)
        {
            DrawCircle(botoes[i].centro.x,botoes[i].centro.y, 1.25 * botoes[i].raio,BLACK);
            DrawCircle(botoes[i].centro.x,botoes[i].centro.y, botoes[i].raio, botoes[i].cor);
            DrawText(botoes[i].texto, botoes[i].centro.x + (3*(int)botoes[i].raio), botoes[i].centro.y - (int)botoes[i].raio,2*(int)botoes[i].raio, BLACK);
            if (botoes[i].estado == true)
            {
                DrawCircle(botoes[i].centro.x,botoes[i].centro.y, 0.85*botoes[i].raio, NOSSO_AZUL);
            }
        }
    }

    return;
}

void resaltaRadioButton(RadioButton botoes[], int quantidade_botoes, int grupo_selecionado)
{

    for(int i = 0; i < quantidade_botoes; i++){

        if (botoes[i].grupo == grupo_selecionado)
        {
            if(CheckCollisionPointCircle(posicao_mouse, botoes[i].centro, botoes[i].raio)){
                botoes[i].cor = NOSSO_CIANO;
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else{
                botoes[i].cor = NOSSO_BEGE;
            }
        }
    }

    return;
}

void desenhaTextBox(TextBox *caixa_texto)
{
    static int contador_frame = 0;

    if(caixa_texto->habilitado){
    DrawRectangle(caixa_texto->caixa.x, caixa_texto->caixa.y, caixa_texto->caixa.width, caixa_texto->caixa.height, caixa_texto->cor_caixa);
        if(caixa_texto->placeholder){
            DrawText(caixa_texto->texto_placeholder, caixa_texto->caixa.x + 7, ((2 * caixa_texto->caixa.y + caixa_texto->caixa.height - 25) * 0.5), 25, GRAY);
            if(contador_frame > 90 && caixa_texto->subcaixa){
            DrawText("|", caixa_texto->caixa.x + 13 + MeasureText(caixa_texto->texto_placeholder, 25), ((2 * caixa_texto->caixa.y + caixa_texto->caixa.height - 25) * 0.5), 25, GRAY);
            } 
        } else{
            DrawText(caixa_texto->texto, caixa_texto->caixa.x + 7, ((2 * caixa_texto->caixa.y + caixa_texto->caixa.height - 25) * 0.5), 25, caixa_texto->cor_texto);
            if(contador_frame > 90 && caixa_texto->subcaixa){
            DrawText("|", caixa_texto->caixa.x + 13 + MeasureText(caixa_texto->texto, 25), ((2 * caixa_texto->caixa.y + caixa_texto->caixa.height - 25) * 0.5), 25, caixa_texto->cor_texto);
            } 
        } 
    }

    if(contador_frame > 180){
        contador_frame = 0;
    }
    
    contador_frame++;
    
    return;
}

void desenhaSeletor(Seletor caixas[], int quantidade_seletor, int grupo_selecionado)
{    

    for(int i = 0; i < quantidade_seletor; i++)
    {   
        if (caixas[i].grupo == grupo_selecionado)
        {
            DrawRectangle(caixas[i].quadrado.x-3, caixas[i].quadrado.y-3,6 + caixas[i].quadrado.width, 6 +caixas[i].quadrado.height, BLACK);
            DrawRectangle(caixas[i].quadrado.x, caixas[i].quadrado.y, caixas[i].quadrado.width, caixas[i].quadrado.height, caixas[i].cor);
            DrawText(caixas[i].texto, caixas[i].quadrado.x + (2 *(int)caixas[i].quadrado.width), caixas[i].quadrado.y , (int)caixas[i].quadrado.width, BLACK);
            if (caixas[i].estado == true)
            {
                DrawRectangle(caixas[i].quadrado.x + 4, caixas[i].quadrado.y +4, caixas[i].quadrado.width -8, caixas[i].quadrado.height -8, NOSSO_AZUL);
            }
            if(CheckCollisionPointRec(posicao_mouse, caixas[i].quadrado)){
                caixas[i].cor = NOSSO_CIANO;
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else{
                caixas[i].cor = NOSSO_BEGE;
            }
        }
        
    }

    return;
}