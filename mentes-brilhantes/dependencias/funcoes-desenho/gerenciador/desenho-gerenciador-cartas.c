//FUNÇÕES DE DESENHO PARA A TELA DE GERENCIAMENTO DE CARTAS

#ifdef _WIN32 //Testa se o SO é Windows
      #include "../dependencias.h"   
#else
    #include "./dependencias.h"
#endif

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

void desenhoGerenciador(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, Texture2D fundo, int submenu_tela, Texture2D seta, Texture2D frente_carta, int carta_atual, int total_cartas, Carta carta, Texture2D *img_carta, int exportou)
{
    
    BeginTextureMode(*target); //Tudo que for desenhado dessa função até EndTextureMode será automaticamente escalado
    ClearBackground(RAYWHITE); //Fundo da tela

    DrawTexture(fundo, 0, 0, WHITE); //Desenha o fundo

    DrawRectangleLinesEx((Rectangle){0, 275, 311, 325}, 3, BLACK); //Desenha um retangulo preto vazado para controles
    
    DrawTexture(seta, 910, 255, WHITE); //Desenha a seta da direita
    DrawTextureEx(seta, (Vector2){400, 255+72}, 180.0f, 1.0f, WHITE); //Desenha a seta da esquerda (13)

    desenhaCarta(500, 100, &frente_carta, &carta, img_carta); //Chama a função para desenhar a carta na posição x,y
    
    DrawRectangleLinesEx((Rectangle){320, 15, 160, 55}, 5, WHITE); //Desenha um retangulo branco para numero de cartas
    DrawText(TextFormat("%d / %d",carta_atual, total_cartas), 333, 25, 35, WHITE);

    switch (submenu_tela)
    {
    case 5:
        incluir_listar();
        break;
    
    default:
    incluir_exportar(exportou);
        break;
    }

    for(int t = 0; t < quantidade_botoes; t++){
    desenharBotaoTxt(botoes[t]);
    } //Desenha todos os botões - Nulos e normais

    DrawText(TextFormat("Posição do mouse: (%.2f,%.2f)", posicao_mouse.x, posicao_mouse.y), 450, 570, 20, BLUE);
    
    EndTextureMode();

    desenhoRedimensionado(target); //Chama a função que desenha redimensionadamente
}

void incluir_listar(){
    DrawRectangleLinesEx((Rectangle){4, 295, 302, 116}, 4, NOSSO_AMARELO);
    DrawText("QUANTIDADE DE", 8, 300, 35, NOSSO_CIANO);
    DrawText("QUANTIDADE DE", 10, 302, 35, NOSSO_AZUL);
    DrawText("CARTAS:", 79, 337, 35, NOSSO_CIANO);
    DrawText("CARTAS:", 81, 339, 35, NOSSO_AZUL);
    DrawText(TextFormat("%d", quantidade_cartas), 142, 373, 35, NOSSO_AZUL);
    DrawText(TextFormat("%d", quantidade_cartas), 140, 371, 35, NOSSO_AMARELO);
    return;
} //Função que desenha a listagem de cartas

void incluir_exportar(int exportou){
    DrawRectangleLinesEx((Rectangle){4, 280, 302, 182}, 4, NOSSO_AMARELO);

    if(exportou == 1){
    DrawText(TextFormat("Cartas"), 94, 293, 35, NOSSO_AMARELO);
    DrawText(TextFormat("Exportadas"), 63, 331, 35, NOSSO_AMARELO);
    DrawText(TextFormat("Na raiz do game"), 30, 373, 32, NOSSO_AZUL);
    DrawText(TextFormat("-Cartas.csv-"), 42, 411, 35, NOSSO_AZUL);
    } else{
    DrawText(TextFormat("Erro ao"), 100, 300, 35, NOSSO_AMARELO);
    DrawText(TextFormat("Exportar!"), 70, 338, 35, NOSSO_AMARELO);
    }

    return;
} //Função que desenha a listagem de cartas

