/*
-->LER ARQUIVOS<--
Arquivo de leitura em arquivos do jogo, tanto em CSV quanto em BIN.
Responsável por receber as ordens da main para checar se há o arquivo binário presente na pasta
de dados, e processar na main, também le os arquivos em ambos os tipos de arquivos de acordo com
os comandos da main.
*/

//---------------------------------
//INCLUDES
//---------------------------------

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include <string.h>

//---------------------------------
//--FUNÇÕES DO ARQ .CSV:
//---------------------------------

//Função que abre o arquivo csv e le até o seu fim redimensionando o vetor cartas e salvando as cartas lidas nele, ele retorna o numero de cartas lidas:
int carregarDadosCSV(const char *nomeArquivo, Carta **cartas)
{
    printf("\nLendo do arquivo CSV!\n");

    //Variaveis:
    const int max_linhas = 512; //Maximo de linhas que são lidas do arquivo
    char linha[max_linhas]; //Char para ler e armazenar cada linha e depois processa-la
    int capacidade = 64; // Capacidade inicial do array de
    int tamanho = 0; //Contagem das linhas lidas do arquivo
    char super_trunfo[6]; //Para uso se é supertrunfo durante a leitura

    //Abre o arquivo:
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        return 0;
    } //Verifica se o arquivo existe e abre-o

    //Alocação:
    *cartas = (Carta *)malloc(capacidade * sizeof(Carta));
    if (*cartas == NULL)
    {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return 0;
    } //Aloca o vetor de cartas inicialmente para 32 - se houver mais o realoc trata

    //Le cada linha do arquivo:
    while (fgets(linha, max_linhas, arquivo))
    {
        if (tamanho >= capacidade)
        {
            capacidade  = 2; //Aumenta a capacidade para +2 e realoca
            *cartas = (Carta *)realloc(*cartas, capacidade * sizeof(Carta));
            if (*cartas == NULL)
            {
                perror("Erro ao realocar memória");
                fclose(arquivo);
                return 0;
            }
        } //Se nescessario realocar memoria

        //A cada linha lida quebra o txt em pedaços e salva no c para ser enviado para cartas:
        Carta c;
        sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,],%u,%u,%u,%u", &c.id, super_trunfo, c.hexadecimal, c.imagem, c.nome, &c.curiosidade, &c.criatividade, &c.inovacao, &c.idade);
        
        c.super_trunfo = (strcmp(super_trunfo, "true") == 0); //Verifica se é supertrunfo e manda para p

        (*cartas)[tamanho++] = c; //Cartas na posição do tamnho atual recebe o c
    } //Percorre todo o arquivo

    fclose(arquivo); //Fecha o arquivo
    return tamanho; //Manda a quantidade de cartas do arquivo
} //fim carregarDadosCSV

//---------------------------------
//ARQUIVOS BINÁRIOS:
//---------------------------------

//Função que quando chamada verifica se há o arquivo de dados binários na pasta, se sim só retorna a main se não cria um para uso adiante:
bool verificaOuCriaArquivoBinario(const char *nomeArquivo)
{    
    //Tenta abrir o arquivo em modo de leitura binária:
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo)
    {
        //O arquivo existe, então fecha e retorna true:
        fclose(arquivo);
        return true;
    }

    //O arquivo não existe, tenta criá-lo:
    arquivo = fopen(nomeArquivo, "wb");
    if (arquivo)
    {
        printf("\nArquivo binário não indentificado, criado um novo!\n");
        //Arquivo criado com sucesso, fecha e retorna false:
        fclose(arquivo);
        return false;
    }

    // Se não conseguiu criar o arquivo, imprime erro e fecha o programa:
    perror("Erro ao criar o arquivo");
    exit(1);
} //Fim verificaOuCriaArquivoBinario

//Função de leitura do arquivo BIN, retornando o tamanho do vetor de structs cartas alocado:
int carregarDadosBIN(const char *nomeArquivo, Carta **cartas)
{
    printf("\nLendo do arquivo BIN!\n");

    //Abre o arquivo:
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo binario");
        return 0;
    } //Verifica se o arquivo existe e abre-o

    int quantidade = 0; //Usada para alocar memória apenas para a quantidade de cartas contidas no arquivo binario
    fread(&quantidade, sizeof(int), 1, arquivo); //Le a quantidade de cartas que tem no arquivo, essa info é a primeira do arquivo

    //Aloca memória para o vetor de cartas:
    *cartas = (Carta *)malloc(quantidade * sizeof(Carta));

    //Le todo o contudo do arquivo:
    if((int) fread(*cartas, sizeof(Carta), quantidade, arquivo) != quantidade)
    {
        perror("Erro ao ler arquivo bin");
        fclose(arquivo); //Fecha o arquivo
        return 0;
    }

    fclose(arquivo); //Fecha o arquivo
    return quantidade; //Manda a quantidade de cartas do arquivo
} //Fim carregarDadosBIN