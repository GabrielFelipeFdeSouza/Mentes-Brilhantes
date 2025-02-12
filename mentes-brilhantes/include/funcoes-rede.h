#ifndef FUNCOES_REDE_H
#define FUNCOES_REDE_H


// Declaração das funções
int conectar_server();
void enviarDados(int id_sala, int cartas_escolhidas[32], char *nome_jogador1, int comandos[2]);
void encerrar_secao(int id_sala, int cartas_escolhidas[32], char *nome_jogador1, int comandos[2]);
void lerServidor1(int id_sala, int comandos[2], char *nome_jogador2);
void lerServidor2(int id_sala, int *submenu_tela);
void ReceberDadosIniciais(char *nome_jogador1, int *cartas_escolhidas, int id_sala);
int verificarSalaVazia(int id_sala);
#endif //FUNCOES_REDE_H
