#ifndef DESENHO_GERAL_H
#define DESENHO_GERAL_H

#include "raylib.h"
#include "structs-gerais.h"

// Declaração da função
Rectangle criarBotao(Botao *botao, int x, int y, Color cor_fundo, char texto[], int tamanho_fonte, Color cor_texto);
int criarBotaoTxtRedimensionavel(Botao *botao, int x, int y, int width, int height, Color cor_fundo, char texto[], Color cor_texto);
void desenharBotaoTxt(Botao *botao);
void desenharBotaoNulo(BotaoNulo *botao);
void desenhaCarta(int x, int y, Texture2D *frente_carta, Carta *carta, Texture2D *img_carta);
void desenhoRedimensionado(RenderTexture2D *target);
void telaErro(char txt_erro[]);
void desenhaRadioButton(RadioButton botoes[], int quantidade_botoesradio, int grupo_selecionado);
void resaltaRadioButton(RadioButton botoes[], int quantidade_botoes, int grupo_selecionado);
void desenhaTextBox(TextBox *caixa_texto);
void desenhaSeletor(Seletor caixas[], int quantidade_seletor, int grupo_selecionado);
int btnsCartasClicados(int x, int y);
void resaltaBotoes();
Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight);
#endif
