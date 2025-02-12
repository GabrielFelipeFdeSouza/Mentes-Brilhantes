#ifndef FUNCOES_ADICIONAIS_EMJOGO_H
#define FUNCOES_ADICIONAIS_EMJOGO_H

#include "raylib.h"
#include "structs-gerais.h"

// Declaração das funções
void iniciar_jogo_bot(Carta **cartas_bot, Carta **cartas_jogador, int quantidades_cartas[2]);
void empate(Carta **cartas_bot, Carta **cartas_jogador, Carta **pilha_empate, int *quantidades_cartas, int tipo);
void distribuiPilha(Carta **cartas_merecedor, int *qtd_cartas_merecedor, Carta **pilha_empate, int *quantidades_cartas);
int iaBot(Carta *cartas_bot, int dificuldade);
void checaVitoria(int *quantidades_cartas, int *submenu_tela);
void clicado(int *btn_clicado, Carta **cartas_bot, Carta **cartas_jogador, Carta **pilha_empate, int *quantidades_cartas, int tipo);
void criarNovaSala(Carta **cartas_jogador1, Carta **cartas_jogador2, int quantidades_cartas[2], int cartas_escolhidas[32]);
int aleatorizarSala();
void EntrarSala(Carta **cartas_jogador1, Carta **cartas_jogador2, int quantidades_cartas[2], int cartas_escolhidas[32]);
#endif //FUNCOES_ADICIONAIS_EMJOGO_H
