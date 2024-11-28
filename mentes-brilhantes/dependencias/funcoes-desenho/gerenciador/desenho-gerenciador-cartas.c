//FUNÇÕES DE DESENHO PARA A TELA DE GERENCIAMENTO DE CARTAS

#ifdef _WIN32 //Testa se o SO é Windows
    #include "../dependencias.h"
    #else
    #include "dependencias.h"
    #endif //Inclui relaativamente os arquivos de dependencia

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

void desenhoGerenciador(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, Texture2D fundo, int submenu_tela)
{
    
    BeginTextureMode(*target); //Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(RAYWHITE); //Fundo da tela

    DrawTexture(fundo, 0, 0, WHITE); //Desenha o fundo
    DrawRectangleLinesEx((Rectangle){0, 275, 311, 325}, 3, BLACK); //Desenha um retangulo preto vazado para controles

    switch (submenu_tela)
    {
    case 5:
        incluir_listar();
        break;
    
    default:
        break;
    }

    for(int t = 0; t < quantidade_botoes; t++){
    desenharBotaoTxt(botoes[t]);
    } //Desenha todos os botões

    DrawText(TextFormat("Posição do mouse: (%.2f,%.2f)", posicao_mouse.x, posicao_mouse.y), 500, 300, 20, BLUE);
    
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

void incluir_listar(){
    DrawRectangleLinesEx((Rectangle){4, 295, 302, 107}, 4, NOSSO_AMARELO);
    DrawText("QUANTIDADE DE", 8, 300, 35, NOSSO_CIANO);
    DrawText("QUANTIDADE DE", 10, 302, 35, NOSSO_AZUL);
    DrawText("CARTAS:", 79, 332, 35, NOSSO_CIANO);
    DrawText("CARTAS:", 81, 334, 35, NOSSO_AZUL);
    DrawText(TextFormat("%d", quantidade_cartas), 142, 366, 35, NOSSO_AZUL);
    DrawText(TextFormat("%d", quantidade_cartas), 140, 364, 35, NOSSO_AMARELO);
    return;
} //Função que desenha a listagem de cartas

