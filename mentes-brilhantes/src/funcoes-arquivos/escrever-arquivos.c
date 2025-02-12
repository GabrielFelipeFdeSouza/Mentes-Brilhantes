/*
-->ESCREVE ARQUIVOS<--
Arquivo de escrita em arquivos do jogo, tanto em CSV quanto em BIN.
Responsável por receber as ordens da main/controle do gerenciador e o vetor de cartas, além da quantidade
que é global e escrever nos arquivos, binário para uso do próprio jogo e csv para export do usuário.
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
#include <time.h>
#include "escrever-arquivos.h"

//---------------------------------
// FUNÇÕES DE .CSV:
//---------------------------------

//Função responsavel por exportar um arqivo csv de cartas usando o cartas como parametro:
int exportarCsv()
{

    // Abre o arquivo:
    FILE *arquivo = fopen("./Cartas.csv", "w");
    if (!arquivo)
    {
        perror("Erro ao exportar");
        return 2;
    }

    char super_trunfo[6]; // Usado para escrever se é supertrunfo ou não - afinal no csv fica como txt

    // Escreve todas as linhas no arquivo:
    for (int v = 0; v < quantidade_cartas; v++)
    {
        if (cartas[v].super_trunfo)
        {
            strcpy(super_trunfo, "true");
        }
        else
        {
            strcpy(super_trunfo, "false");
        } // Formata esse dado para ir ao csv

        // Embora tenha usado o fprint, é uma função bem definida, que tem segurança de uso, além de serem poucas cartas, oque não atrasa o fluxo do game!
        fprintf(arquivo, "%d,%s,%s,%s,%s,%d,%d,%d,%d", cartas[v].id, super_trunfo, cartas[v].hexadecimal, cartas[v].imagem, cartas[v].nome, cartas[v].curiosidade, cartas[v].criatividade, cartas[v].inovacao, cartas[v].idade);

        fprintf(arquivo, "\n"); // Espaço entre linhas
    }

    // Fecha o arquivo e retorna ao gerenciador:
    fclose(arquivo);
    escreverLog("Arquivo CSV exportados na pasta raiz do jogo");
    return 1;
} // Fim exportarCsv


//Função responsavel por iniciar o arquivo de log:
void iniciarArquivoLog()
{
    // Tenta abrir o arquivo:
    FILE *arquivo;

    arquivo = fopen("./data/log.txt", "w");
    if (arquivo)
    {
        // Arquivo criado com sucesso:
        fclose(arquivo);
        return;
    }

    // Se não conseguiu criar o arquivo, imprime erro e fecha o programa:
    perror("Erro ao criar o arquivo de log");
    exit(1);
}


//Função responsavel por colocar uma mensagem no arquivo de log, com hora e a informação:
void escreverLog(char *texto)
{
    // Obtem o tempo atual do sistema:
    time_t tempoAtual = time(NULL);

    // Converte para formato entendivel:
    struct tm *horaLocal = localtime(&tempoAtual);

    FILE *arquivo = fopen("./data/log.txt", "a");

    fprintf(arquivo, "[%02d:%02d:%02d]GAME: %s\n", horaLocal->tm_hour, horaLocal->tm_min, horaLocal->tm_sec, texto);
    printf("GAME: %s\n", texto);
    fclose(arquivo);
    return;
}

//---------------------------------
// ARQUIVOS BINÁRIOS:
//---------------------------------


//Função que salva os dados das cartas no bináio ao fechamento do jogo:
void salvarDados(const char *nomeArquivo)
{

    // Abre o arquivo:
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (!arquivo)
    {
        perror("GAME: Erro ao salvar dados");
        escreverLog("Erro ao salvar dados.");
        return;
    }

    // Salva o dado da quantidade de cartas, para próxima carregada:
    if ((int)fwrite(&quantidade_cartas, sizeof(int), 1, arquivo) != 1)
    {
        perror("GAME: Erro ao salvar dados");
        escreverLog("Erro ao salvar dados.");
        fclose(arquivo);
        return;
    }

    // Salva todo o vetor de cartas:
    if ((int)fwrite(cartas, sizeof(Carta), quantidade_cartas, arquivo) != quantidade_cartas)
    {
        perror("GAME: Erro ao salvar dados");
        escreverLog("Erro ao salvar dados.");
        fclose(arquivo);
        return;
    } // Salva os dados de maneira sequencial

    // Fecha o arquivo e volta para a main:
    fclose(arquivo);
    return;
} // Fim salvarDados
