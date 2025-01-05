/*
-->EXCLUIR CARTAS<--
A exclusão embora pareça a mais simples das funções é na realidade bem complexa, pois além de 
"remover" tal carta do vetor, precisa-se ajustar as posições das cartas para ocupar o menor
espaço possivel e os id's também se ajustarem.
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
#include "excluir-cartas.h"
#include <stdbool.h>

void excluirCarta(int id_excluir)
{
    cartas[id_excluir].id = -1; //Usado para mapear onde precisa redimensionar o vetor, usado na função de ajustar as posições

    ajustarPosicoes(); //Chama o ajuste de posições

    cartas = (Carta*) realloc(cartas, (quantidade_cartas-1) * sizeof(Carta)); //Realoca o vetor de cartas para menos um de tamanho

    return;
} //Fim função excluirCarta

void ajustarPosicoes()
{
    bool ajustar = false; //Usado para saber quando reajustar a posição

    for(int l = 0; l < quantidade_cartas; l++)
    {
        if(cartas[l].id == -1)
        {
            ajustar = true;
        } //Quando chegar no id para reajuste começa a reajustar o vetor de cartas

        if(ajustar)
        {
            cartas[l] = cartas[l+1]; //Copiando o vetor com contudo para a posição do vetor zerado
            cartas[l].id = l+1; //Reajuste do id
        }
    } //Le todas as cartas em busca do id -1

    return;
} //Fim função ajustarPosicoes