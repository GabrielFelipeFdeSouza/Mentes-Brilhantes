/*
-->ADICIONAR CARTAS<--
Arquivo responsavel por gerenciar a lógica de adicionar cartas, sempre que for
chamado pelo gerenciador ele faz as verificações, se tiver tudo certo adiciona a carta
ao final do vetor de structs.
*/

//---------------------------------
// INCLUDES
//---------------------------------

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>
#include "funcoes-deck.h"
#include "funcoes-controle-geral.h"
#include "cores.h"
#include "adicionar-cartas.h"
#include <math.h>
#include <stdbool.h>

//Função que adiciona uma carta apartir dos dados recebidos do gerenciador:
int adicionarCarta(TextBox *caixas_texto, int super_trunfo)
{

    for (int s = 0; s < 6; s++)
    {
        if (strcmp(caixas_texto[s].texto, "") == 0)
        {
            return 1;
        }
    } // Verifica se há texto, se não retorna erro 1

    if (atoi(caixas_texto[1].texto) > 100 || atoi(caixas_texto[2].texto) > 100 || atoi(caixas_texto[3].texto) > 100 || atoi(caixas_texto[4].texto) > 999)
    {
        return 1;
    }
    // Se o texto nas caixas de numero for maior que 3 digitos e fora do range permitido, retorna erro 1

    if ((strlen(caixas_texto[5].texto) != 2) || (caixas_texto[5].texto[1] > 68) || (caixas_texto[5].texto[0] > 56) || (caixas_texto[5].texto[0] < 49))
    {
        return 2;
    } // Verifica se o hexadecimal esta nos conformes

    for (int j = 0; j < quantidade_cartas; j++)
    {
        if (cartas[j].super_trunfo == 1 && super_trunfo == 1)
        {
            return 3;
        }
    } //Checa se já há um supertrunfo no deck, e retorna erro no gerenciador se tiver

    // Copiando os parametros para a nova carta:
    cartas[quantidade_cartas].id = quantidade_cartas + 1;
    strcpy(cartas[quantidade_cartas].nome, caixas_texto[0].texto);
    cartas[quantidade_cartas].curiosidade = atoi(caixas_texto[1].texto);
    cartas[quantidade_cartas].criatividade = atoi(caixas_texto[2].texto);
    cartas[quantidade_cartas].inovacao = atoi(caixas_texto[3].texto);
    cartas[quantidade_cartas].idade = atoi(caixas_texto[4].texto);
    strcpy(cartas[quantidade_cartas].hexadecimal, caixas_texto[5].texto);
    cartas[quantidade_cartas].super_trunfo = super_trunfo;
    strcpy(cartas[quantidade_cartas].imagem, "./img/rostos/padrao.png");

    for (int s = 0; s < 6; s++)
    {
        strcpy(caixas_texto[s].texto, "");
        caixas_texto[s].tamanho = 0;
    } // Limpa as caixas de texto ao serem usadas

    quantidade_cartas++; // Incrementa para o programa enxergar essa nova carta

    return 0; //Retorno sem erros
} //fim adicionarCarta