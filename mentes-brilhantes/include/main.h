#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"
#include "structs-gerais.h"

// Constantes
extern const int COMPRIMENTO_TELA;
extern const int ALTURA_TELA;

// Variáveis globais
extern float scale, scaleX, scaleY;
extern int tela; // Sinalizador de tela que o usuário se encontra
extern int estado_tela; // Sinalizador de tela que o usuário se encontra - controle para funções
extern bool sair; //Sinalizador de saida do usuário
extern Vector2 posicao_mouse; // Posição do mouse
extern Vector2 posicao_tela; // Posição da tela
extern bool esta_mudo; //Controle geral de sons
extern bool trocar_tela; //Controle geral se usuário quer mudar de tela, evitar congelamentos
extern int quantidade_cartas; //Inteiro que salva a quantidade total de cartas na abertura dos arquivos
extern Color *cor_aleatoria; //Usada nas cores aleatorias do game
extern Carta *cartas; // Cria o ponteiro do vetor de cartas para uso no singlePlayer e gerenciador
extern Carta *cartas_multiplayer; // Cria o ponteiro do vetor de cartas para uso no multiplayer
extern int botoes_resaltar; // Variavel usada para incicar para as funções de desenho, quantos botões precisam ser resaltados
extern int id_master_saida; //USado para fechar seções em jogos multiplayers
extern char buffer[512]; //Usado para as funções do log

// Funções
Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight);

#endif //MAIN_H
