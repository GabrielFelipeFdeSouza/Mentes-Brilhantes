#ifndef DESENHO_GERENCIADOR_H
#define DESENHO_GERENCIADOR_H

#include "raylib.h"
#include "structs-gerais.h"

// Declaração da função
void desenhoGerenciador(RenderTexture2D *target, Botao botoes[], int quantidade_botoes, Texture2D *fundo, int *submenu_tela, Texture2D *seta, Texture2D *frente_carta, int *carta_atual, int *total_cartas, Carta *carta, Texture2D *img_carta, int *exportou, int *retornos_funcoes, RadioButton botoes_radio[], int quantidade_botoes_radio, TextBox caixa_texto[], Seletor *caixas, TextBox caixa_texto_pesquisar[]);
void incluir_listar();
void incluir_exportar(int *exportou);
void incluir_adicionar(RadioButton botoes_radio[], int quantidade_botoes_radio, int grupo_selecionado, TextBox *caixa_texto, Seletor *caixas);
void incluir_editar(RadioButton botoes_radio[], int quantidade_botoes_radio, int grupo_selecionado, TextBox *caixa_texto, Seletor *caixas);
void incluir_pesquisar(RadioButton botoes_radio[], int quantidade_botoes_radio, int grupo_selecionado, TextBox *caixa_texto_pesquisar, Seletor *caixas);
#endif //DESENHO_GERENCIADOR_H
