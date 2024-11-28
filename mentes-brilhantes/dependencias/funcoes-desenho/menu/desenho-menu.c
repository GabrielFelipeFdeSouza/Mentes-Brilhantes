// FUNÇÕES DE DESENHO PARA A TELA DE MENU GERAL

#ifdef _WIN32 //Testa se o SO é Windows
    #include "../dependencias.h"
    #else
    #include "dependencias.h"
    #endif //Inclui relaativamente os arquivos de dependencia

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

void desenhoMenu(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, BotaoNulo botao, Texture2D img_btn_som, Texture2D fundo)
{
    BeginTextureMode(*target); //Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(RAYWHITE); //Fundo da tela

    DrawTexture(fundo, 0, 0, WHITE);

    for(int t = 0; t < quantidade_botoes; t++){
    desenharBotaoTxt(botoes[t]);
    } //Desenha todos os botões


    DrawText(TextFormat("Posição do mouse: (%.2f,%.2f)", posicao_mouse.x, posicao_mouse.y), 1, 1, 20, RED);
    desenharBotaoNulo(botao); //Desenha os botões nulos, nesse caso o da imagem de som
    DrawTexture(img_btn_som, 916, 525, WHITE);
    EndTextureMode();

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

}



