// FUNÇÕES DE BUSCAS NO VETOR DE CARTAS:

#include "../dependencias.h"

int pesquisarCarta(Carta *cartas, TextBox *caixas_texto, int super_trunfo, RadioButton *botoes_radio, Carta **cartas_desenho)
{

    int total_cartas = 0;

    (void)super_trunfo;

    *cartas_desenho = NULL;

    // Aplicando o filtro:

    if (botoes_radio[0].estado)
    {
        for (int p = 0; p < quantidade_cartas; p++)
        {
            if (strcmp(caixas_texto[0].texto, cartas[p].nome) == 0)
            {
                total_cartas++;
                (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
                (*cartas_desenho)[total_cartas - 1] = cartas[p];
            }
        }
    }

    if (total_cartas == 0)
    {
        total_cartas = 1;
        (*cartas_desenho) = realloc(*cartas_desenho, total_cartas * sizeof(Carta));
        (*cartas_desenho)[total_cartas - 1].id = 999;
        (*cartas_desenho)[total_cartas - 1].super_trunfo = false;
        strcpy((*cartas_desenho)[total_cartas - 1].hexadecimal, "9Z");
        strcpy((*cartas_desenho)[total_cartas - 1].imagem, "./img/rostos/erro.png");
        strcpy((*cartas_desenho)[total_cartas - 1].nome, "No-Name");
        (*cartas_desenho)[total_cartas - 1].curiosidade = 0;
        (*cartas_desenho)[total_cartas - 1].criatividade = 0;
        (*cartas_desenho)[total_cartas - 1].inovacao = 0;
        (*cartas_desenho)[total_cartas - 1].idade = 0;
    } //Caso de não haver corespondencias no pesquisar, mostra uma carta base, com a msg relacionada

    return total_cartas;
}