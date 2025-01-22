/*
-->EDITAR CARTAS<--
Neste arquivo, quando ele é chamado, as funções são responsáveis pela edição de cartas,
ele verifica quais parametros estão vazios e mantem esses originais, apenas mudando os
que tem algo na caixa de texto relacionado. Ainda ele verifica se há mais de um super-trunfo
no baralho e da um alerta ao usuário.
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

int editarCarta(TextBox *caixas_texto, int posicao, int super_trunfo)
{
    if ((strlen(caixas_texto[5].texto) != 2) && ((caixas_texto[5].texto[1] > 68) || (caixas_texto[5].texto[0] > 56) || (caixas_texto[5].texto[0] < 49)))
    {
        if (strlen(caixas_texto[5].texto) != 0)
        {
            return 2;
        }
    } // Verifica se o hexadecimal esta nos conformes

    if (atoi(caixas_texto[1].texto) > 100 || atoi(caixas_texto[2].texto) > 100 || atoi(caixas_texto[3].texto) > 100 || atoi(caixas_texto[4].texto) > 999)
    {
        return 1;
    } // Se o texto nas caixas de numero for maior que 3 digitos e fora do range permitido, retorna erro 1

    for (int j = 0; j < quantidade_cartas; j++)
    {
        if (cartas[j].super_trunfo == 1 && super_trunfo == 1)
        {
            return 3;
        }
    } // Checa se já existe um super-trunfo no baralho e retorna o erro 3

    // Copiando os parametros para a nova carta - se a caixa for vazia mantem o estado atual:
    if (strcmp(caixas_texto[0].texto, "") != 0)
    {
        strcpy(cartas[posicao].nome, caixas_texto[0].texto);
    }

    if (strcmp(caixas_texto[1].texto, "") != 0)
    {
        cartas[posicao].curiosidade = atoi(caixas_texto[1].texto);
    }

    if (strcmp(caixas_texto[2].texto, "") != 0)
    {
        cartas[posicao].criatividade = atoi(caixas_texto[2].texto);
    }

    if (strcmp(caixas_texto[3].texto, "") != 0)
    {
        cartas[posicao].inovacao = atoi(caixas_texto[3].texto);
    }

    if (strcmp(caixas_texto[4].texto, "") != 0)
    {
        cartas[posicao].idade = atoi(caixas_texto[4].texto);
    }

    if (strcmp(caixas_texto[5].texto, "") != 0)
    {
        strcpy(cartas[posicao].hexadecimal, caixas_texto[5].texto);
    }

    cartas[posicao].super_trunfo = super_trunfo; // Copia o campo super-trunfo

    for (int s = 0; s < 6; s++)
    {
        strcpy(caixas_texto[s].texto, "");
        caixas_texto[s].tamanho = 0;
    } // Limpa as caixas de texto ao serem usadas

    return 0; // Retorno sem erros
} // Fim função editarCarta