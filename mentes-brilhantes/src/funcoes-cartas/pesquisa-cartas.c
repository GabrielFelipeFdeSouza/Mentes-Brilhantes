// FUNÇÕES DE BUSCAS NO VETOR DE CARTAS:

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>

int pesquisarCarta(Carta *cartas, TextBox *caixas_texto, int super_trunfo, RadioButton *botoes_radio, Carta **cartas_desenho)
{

    int total_cartas = 0;
    int caixas_vazias = 0;

    *cartas_desenho = NULL;

    // Aplicando o filtro:
    for (int i = 0; i < 5; i++) // qtd caixas texto
    {
        if (strcmp(caixas_texto[i].texto, "") == 0 && super_trunfo == 0)
            caixas_vazias++;
    }
    if (caixas_vazias == 5)
    {
        return -1;
    }
    else
    {
        if (super_trunfo)
        {
            for (int p = 0; p < quantidade_cartas; p++)
            {
                if (cartas[p].super_trunfo == super_trunfo)
                {
                    total_cartas++;
                    (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                    (*cartas_desenho)[total_cartas - 1] = cartas[p];
                }
            }
            return total_cartas;
        }

        if (botoes_radio[0].estado)
        {
            for (int p = 0; p < quantidade_cartas; p++)
            {
                if (strstr(cartas[p].nome, caixas_texto[0].texto) != NULL)
                {
                    total_cartas++;
                    (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                    (*cartas_desenho)[total_cartas - 1] = cartas[p];
                }
            }
            return total_cartas;
        }

        if (botoes_radio[1].estado)
        {
            for (int p = 0; p < quantidade_cartas; p++)
            {
                if ((int)cartas[p].curiosidade >= atoi(caixas_texto[1].texto) && (int)cartas[p].curiosidade <= atoi(caixas_texto[2].texto))
                {
                    total_cartas++;
                    (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                    (*cartas_desenho)[total_cartas - 1] = cartas[p];
                }
            }
            return total_cartas;
        }

        if (botoes_radio[2].estado)
        {
            for (int p = 0; p < quantidade_cartas; p++)
            {
                if ((int)cartas[p].criatividade >= atoi(caixas_texto[1].texto) && (int)cartas[p].criatividade <= atoi(caixas_texto[2].texto))
                {
                    total_cartas++;
                    (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                    (*cartas_desenho)[total_cartas - 1] = cartas[p];
                }
            }
            return total_cartas;
        }

        if (botoes_radio[4].estado)
        {
            for (int p = 0; p < quantidade_cartas; p++)
            {
                if ((int)cartas[p].idade >= atoi(caixas_texto[1].texto) && (int)cartas[p].idade <= atoi(caixas_texto[2].texto))
                {
                    total_cartas++;
                    (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                    (*cartas_desenho)[total_cartas - 1] = cartas[p];
                }
            }
            return total_cartas;
        }

        if (botoes_radio[3].estado)
        {
            for (int p = 0; p < quantidade_cartas; p++)
            {
                if ((int)cartas[p].inovacao >= atoi(caixas_texto[1].texto) && (int)cartas[p].inovacao <= atoi(caixas_texto[2].texto))
                {
                    total_cartas++;
                    (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                    (*cartas_desenho)[total_cartas - 1] = cartas[p];
                }
            }
            return total_cartas;
        }

        if (botoes_radio[4].estado)
        {
            for (int p = 0; p < quantidade_cartas; p++)
            {
                if ((int)cartas[p].idade >= atoi(caixas_texto[1].texto) && (int)cartas[p].idade <= atoi(caixas_texto[2].texto))
                {
                    total_cartas++;
                    (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                    (*cartas_desenho)[total_cartas - 1] = cartas[p];
                }
            }
            return total_cartas;
        }

        if (botoes_radio[5].estado)
        {
            if (strcmp(caixas_texto[3].texto, "") != 0 && strcmp(caixas_texto[4].texto, "") != 0)
            {
                for (int p = 0; p < quantidade_cartas; p++)
                {
                    if (atoi(cartas[p].hexadecimal) == atoi(caixas_texto[3].texto) && (char)cartas[p].hexadecimal[1] == (char)caixas_texto[4].texto[0])
                    {
                        total_cartas++;
                        (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                        (*cartas_desenho)[total_cartas - 1] = cartas[p];
                    }
                }
            }
            else if (strcmp(caixas_texto[3].texto, "") != 0)
            {
                for (int p = 0; p < quantidade_cartas; p++)
                {
                    if (atoi(cartas[p].hexadecimal) == atoi(caixas_texto[3].texto))
                    {
                        total_cartas++;
                        (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                        (*cartas_desenho)[total_cartas - 1] = cartas[p];
                    }
                }
            }
            else
            {
                for (int p = 0; p < quantidade_cartas; p++)
                {
                    if ((char)cartas[p].hexadecimal[1] == (char)caixas_texto[4].texto[0])
                    {
                        total_cartas++;
                        (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                        (*cartas_desenho)[total_cartas - 1] = cartas[p];
                    }
                }
            }
            return total_cartas;
        }

        return 0;
    }
}