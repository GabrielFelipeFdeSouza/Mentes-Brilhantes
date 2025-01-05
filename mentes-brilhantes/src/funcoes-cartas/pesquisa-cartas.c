/*
-->PESQUISAR CARTAS<--
Essa é a função auxiliar mais complexa do gerenciador, ela é responsavel por todo o submenu de 
pesquisa, é ela que retorna um novo vetor de tamanho dinamico para o gerenciador e ele irá
exibi-lo ao usuário.
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

int pesquisarCarta(TextBox *caixas_texto, int super_trunfo, RadioButton *botoes_radio, Carta **cartas_desenho)
{

    int total_cartas = 0; //Usado para contar quantas cartas ele acha durante a pesquisa
    int caixas_vazias = 0; //Usado para ver se há ao menos uma caixa de texto preenchida para a pesquisa

    *cartas_desenho = NULL; //Vetor de exibição da pesquisa, setado para NULL para iniciar as pesquisas

    // Aplicando o filtro de caixas de texto:
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(caixas_texto[i].texto, "") == 0 && super_trunfo == 0)
            caixas_vazias++;
    } //Verifica se a caixa de texto é vazia, somente se super-trunfo é false, se for true há algo para verificar

    if (caixas_vazias == 5)
    {
        return -1;
    } //Se as caixas forem vazias, retorna erro -1
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
        } //Se for super-trunfo já procura a carta nessa parte e manda a carta para o gerenciador

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
        } //Checa por nome, usando a função strstr para procura por fragmentos de texto

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
        } //Checa por range de curiosidade

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
        } //Checa por range de criatividade

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
        } //Checa por range de inovação

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
        } //Checa por range de idade

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
            } //Caso de ter as duas caixas com texto
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
            } //Caso de ter apenas a caixa de numero com texto
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
            } //Caso de ter apenas a caixa de letra com texto

            return total_cartas;

        } //Checa por hexadecimal

        return 0; //Retorno 0 cartas se não achar nada
    }
} //Fim função pesquisarCarta