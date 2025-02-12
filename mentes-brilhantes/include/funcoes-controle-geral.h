#ifndef FUNCOES_CONTROLE_GERAL_H
#define FUNCOES_CONTROLE_GERAL_H

#include "raylib.h"
#include "structs-gerais.h"

// DeclaraÃ§Ã£o das funÃ§Ãµes
void leMouse();
bool coresIguais(Color c1, Color c2);
bool checarClique(Rectangle *botao);
void controleSons(int controle, Music musica, Sound som);
void checarTelaCheia();
void checarSaida();
void abrePdf();
void checaRadioButton(RadioButton btns_radio[], int qtd_btn_radio, int grupo_selecionado);
void leTeclado(char *string, int *conta_tecla, int subgrupo, int limitador);
void checaSeletor(Seletor caixas[], int qtd__caixas_seletor, int grupo_selecionado);
void resetarCartas();
#endif