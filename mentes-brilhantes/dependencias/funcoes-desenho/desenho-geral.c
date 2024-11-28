//Função que desenhe na tela (qualquer) os seguintes itens padrões:
#include "../../dependencias.h"

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

bool resaltaBotoes(Botao botoes[], int quantidade_botoes, Music musica, Sound som_clique_btn){

    for(int t = 0; t < quantidade_botoes; t++){
        if(!coresIguais(botoes[t].cor_botao, GREEN)){
        botoes[t].cor_botao = NOSSO_AZUL;
        }
    } //For que evita cores ciano infinitas em botões muito próximos

    for(int u = 0; u < quantidade_botoes; u++){
        if(CheckCollisionPointRec(posicao_mouse, botoes[u].colisao)){
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

            if(coresIguais(botoes[u].cor_botao, NOSSO_AZUL)){
                controleSons(1, musica, som_clique_btn); //Função de controle geral sons - toca o som de mouse sob o btn
            } //If evita varias tocadas do mesmo som

            if(!coresIguais(botoes[u].cor_botao, GREEN)){
            botoes[u].cor_botao = NOSSO_CIANO; //Muda cor fundo botão
            } //Evita que mude a cor do botão se for verde
            return true;

        } else{
            
            if(!coresIguais(botoes[u].cor_botao, GREEN)){
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            botoes[u].cor_botao = NOSSO_AZUL; //Muda cor fundo botão 
            } //Evita que mude a cor do botão se for verde
        }
    }
    return false;
}

void resaltaBotoesNulo(Botao botoes[], int quantidade_botoes){
    for(int u = 0; u < quantidade_botoes; u++){
        if(CheckCollisionPointRec(posicao_mouse, botoes[u].colisao)){
            botoes[u].cor_botao = NOSSO_CIANO;
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else{
            botoes[u].cor_botao = NOSSO_AZUL;
        }
    }
}