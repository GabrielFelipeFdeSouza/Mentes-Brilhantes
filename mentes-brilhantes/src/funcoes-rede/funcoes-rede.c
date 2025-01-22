#ifdef _WIN32

#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes-rede.h"

int conectar_server()
{
    const wchar_t *host = L"gg128.ddnsfree.com"; // Endereço do seu servidor
    const wchar_t *path = L"/";                  // Caminho para o script PHP

    // Inicializa o handle para a sessão HTTP
    HINTERNET hSession = WinHttpOpen(L"ConexaoTester/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, NULL, NULL, 0);
    if (!hSession)
    {
        return 0; // Falha ao inicializar a sessão
    }

    // Configura os timeouts
    DWORD timeout = 750; // 750ms para timeout maximo
    WinHttpSetTimeouts(hSession, timeout, timeout, timeout, timeout);

    // Conecta ao servidor
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect)
    {
        WinHttpCloseHandle(hSession);
        return 0; // Falha ao conectar ao servidor
    }

    // Cria uma requisição HEAD (teste de conexão, sem baixar conteúdo)
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"HEAD", path, NULL, NULL, NULL, 0);
    if (!hRequest)
    {
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 0; // Falha ao criar a requisição
    }

    // Envia a requisição e verifica a resposta
    BOOL bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) && WinHttpReceiveResponse(hRequest, NULL);

    // Fecha os handles
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    // Retorna o resultado da conexão
    return bResults ? 1 : 0;
}

void enviarDados(int id_sala, int cartas_escolhidas[32], char *nome_jogador1, int comandos[2])
{
    // Configurações do servidor e arquivo PHP
    const wchar_t *host = L"gg128.ddnsfree.com";                                  // Endereço do seu servidor
    const wchar_t *path = L"/projetos/super-trunfo/SERVER/processar_arquivo.php"; // Caminho para o script PHP

    // Buffer para armazenar os dados formatados
    char dados[1024]; // Ajuste o tamanho conforme necessário

    // Adicionar comandos ao JSON
    char comandos_str[32];
    sprintf(comandos_str, "%d,%d", comandos[0], comandos[1]);

    // Adicionar cartas escolhidas ao JSON
    char cartas_str[256] = {0};
    for (int i = 0; i < 32; i++)
    {
        char buffer[8];
        sprintf(buffer, "%d,", cartas_escolhidas[i]);
        strcat(cartas_str, buffer);
    }
    // Remover a última vírgula
    cartas_str[strlen(cartas_str) - 1] = '\0';

    // Formatar os dados do JSON
    sprintf(dados,
            "{\"arquivo\":\"%d.txt\",\"dados\":\"%s\\n%s\\n%s\"}",
            id_sala,
            comandos_str,
            cartas_str,
            nome_jogador1);

    // Abre sessão e conecta ao servidor
    HINTERNET hSession = WinHttpOpen(L"HTTP Writer/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     NULL, NULL, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, 0);

    // Cria a requisição HTTP POST
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", path, NULL, NULL, NULL, 0);

    // Adiciona cabeçalhos da requisição
    WinHttpAddRequestHeaders(hRequest, L"Content-Type: application/json\r\n",
                             -1, WINHTTP_ADDREQ_FLAG_ADD);

    // Envia a requisição POST com os dados JSON
    BOOL enviado = WinHttpSendRequest(hRequest,
                                      NULL, 0,
                                      (LPVOID)dados, strlen(dados),
                                      strlen(dados), 0);

    // Verifica se a requisição foi enviada
    if (!enviado)
    {
        printf("GAME: Erro ao enviar requisição: %lu\n", GetLastError());
        return;
    }

    // Recebe a resposta do servidor
    WinHttpReceiveResponse(hRequest, NULL);

    // Lê a resposta do servidor
    // DWORD tamanho;
    char buffer[2048] = {0};
    DWORD lido;
    if (WinHttpReadData(hRequest, buffer, sizeof(buffer) - 1, &lido))
    {
        buffer[lido] = '\0'; // Garantir que o buffer seja uma string válida
        printf("Resposta do servidor: %s\n", buffer);
    }
    else
    {
        printf("Erro ao ler a resposta: %lu\n", GetLastError());
    }

    // Fecha as conexões
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}

void encerrar_secao(int id_sala, int cartas_escolhidas[32], char *nome_jogador1, int comandos[2])
{
    // Configurações do servidor e arquivo PHP
    const wchar_t *host = L"gg128.ddnsfree.com";                              // Endereço do seu servidor
    const wchar_t *path = L"/projetos/super-trunfo/SERVER/destruir_jogo.php"; // Caminho para o script PHP

    // Buffer para armazenar os dados formatados
    char dados[1024]; // Ajuste o tamanho conforme necessário

    // Adicionar comandos ao JSON
    char comandos_str[32];
    sprintf(comandos_str, "%d,%d", comandos[0], comandos[1]);

    // Adicionar cartas escolhidas ao JSON
    char cartas_str[256] = {0};
    for (int i = 0; i < 32; i++)
    {
        char buffer[8];
        sprintf(buffer, "%d,", cartas_escolhidas[i]);
        strcat(cartas_str, buffer);
    }
    // Remover a última vírgula
    cartas_str[strlen(cartas_str) - 1] = '\0';

    // Formatar os dados do JSON
    sprintf(dados,
            "{\"arquivo\":\"%d.txt\",\"dados\":\"%s\\n%s\\n%s\"}",
            id_sala,
            comandos_str,
            cartas_str,
            nome_jogador1);

    // Abre sessão e conecta ao servidor
    HINTERNET hSession = WinHttpOpen(L"HTTP Writer/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     NULL, NULL, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, 0);

    // Cria a requisição HTTP POST
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", path, NULL, NULL, NULL, 0);

    // Adiciona cabeçalhos da requisição
    WinHttpAddRequestHeaders(hRequest, L"Content-Type: application/json\r\n",
                             -1, WINHTTP_ADDREQ_FLAG_ADD);

    // Envia a requisição POST com os dados JSON
    BOOL enviado = WinHttpSendRequest(hRequest,
                                      NULL, 0,
                                      (LPVOID)dados, strlen(dados),
                                      strlen(dados), 0);

    // Verifica se a requisição foi enviada
    if (!enviado)
    {
        printf("GAME: Erro ao enviar requisição para o servidor durante o encerrar da sala: %lu\n", GetLastError());
        return;
    }

    // Recebe a resposta do servidor
    WinHttpReceiveResponse(hRequest, NULL);

    // Lê a resposta do servidor
    // DWORD tamanho;
    char buffer[2048] = {0};
    DWORD lido;
    if (WinHttpReadData(hRequest, buffer, sizeof(buffer) - 1, &lido))
    {
        buffer[lido] = '\0'; // Garantir que o buffer seja uma string válida
        printf("GAME: Resposta do servidor: %s\n", buffer);
    }
    else
    {
        printf("GAME: Erro ao ler a resposta: %lu\n", GetLastError());
    }

    // Fecha as conexões
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}

void lerServidor1(int id_sala, int comandos[2], char *nome_jogador2)
{
    // Configurações do servidor e arquivo
    const wchar_t *host = L"gg128.ddnsfree.com"; // Servidor
    wchar_t path[100];
    swprintf(path, sizeof(path) / sizeof(wchar_t), L"./projetos/super-trunfo/SERVER/%d.txt", id_sala);
    // Vetores para armazenar os dados
    int vetor1[2] = {0};  // Vetor para os dois primeiros números
    int vetor2[32] = {0}; // Vetor para os 32 números seguintes
    char nome[51] = {0};  // Nome com até 50 caracteres

    // Abre sessão e conecta ao servidor
    HINTERNET hSession = WinHttpOpen(L"HTTP Reader/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     NULL, NULL, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, 0);

    // Faz a solicitação do arquivo
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path, NULL, NULL, NULL, 0);
    WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, 0, 0);
    WinHttpReceiveResponse(hRequest, NULL);

    // Lê o conteúdo do arquivo
    // DWORD tamanho;
    char buffer[2048] = {0};
    DWORD lido;
    if (WinHttpReadData(hRequest, buffer, sizeof(buffer) - 1, &lido))
    {
        buffer[lido] = '\0'; // Garantir que o buffer seja uma string válida

        // Processar o conteúdo do arquivo
        char *linha1 = strtok(buffer, "\n"); // Primeira linha
        char *linha2 = strtok(NULL, "\n");   // Segunda linha
        char *linha3 = strtok(NULL, "\n");   // Terceira linha (nome)

        // Processar vetor1
        char *token = strtok(linha1, ",");
        for (int i = 0; i < 2 && token != NULL; i++)
        {
            vetor1[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        // Processar vetor2
        token = strtok(linha2, ",");
        for (int i = 0; i < 32 && token != NULL; i++)
        {
            vetor2[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        (void)vetor2;

        // Processar o nome
        if (linha3 != NULL)
        {
            strncpy(nome, linha3, 50);
            nome[50] = '\0'; // Garantir terminador nulo
        }
    }

    // Fechar conexões
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    for (int i = 0; i < 2; i++)
    {
        comandos[i] = vetor1[i];
    }

    strcpy(nome_jogador2, nome);
}

void lerServidor2(int id_sala, int *submenu_tela)
{
    // Configurações do servidor e arquivo
    const wchar_t *host = L"gg128.ddnsfree.com"; // Servidor
    wchar_t path[100];
    swprintf(path, sizeof(path) / sizeof(wchar_t), L"./projetos/super-trunfo/SERVER/%d.txt", id_sala);
    // Vetores para armazenar os dados
    int vetor1[2] = {0};  // Vetor para os dois primeiros números
    int vetor2[32] = {0}; // Vetor para os 32 números seguintes
    char nome[51] = {0};  // Nome com até 50 caracteres

    // Abre sessão e conecta ao servidor
    HINTERNET hSession = WinHttpOpen(L"HTTP Reader/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     NULL, NULL, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, 0);

    // Faz a solicitação do arquivo
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path, NULL, NULL, NULL, 0);
    WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, 0, 0);
    WinHttpReceiveResponse(hRequest, NULL);

    // Lê o conteúdo do arquivo
    // DWORD tamanho;
    char buffer[2048] = {0};
    DWORD lido;
    if (WinHttpReadData(hRequest, buffer, sizeof(buffer) - 1, &lido))
    {
        buffer[lido] = '\0'; // Garantir que o buffer seja uma string válida

        // Processar o conteúdo do arquivo
        char *linha1 = strtok(buffer, "\n"); // Primeira linha
        char *linha2 = strtok(NULL, "\n");   // Segunda linha
        char *linha3 = strtok(NULL, "\n");   // Terceira linha (nome)

        // Processar vetor1
        char *token = strtok(linha1, ",");
        for (int i = 0; i < 2 && token != NULL; i++)
        {
            vetor1[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        if (vetor1[1] == 0)
        {
            *submenu_tela = 8;
        }

        // Processar vetor2
        token = strtok(linha2, ",");
        for (int i = 0; i < 32 && token != NULL; i++)
        {
            vetor2[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        (void)vetor2;

        // Processar o nome
        if (linha3 != NULL)
        {
            strncpy(nome, linha3, 50);
            nome[50] = '\0'; // Garantir terminador nulo
        }
    }

    (void)nome;

    // Fechar conexões
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}

void ReceberDadosIniciais(char *nome_jogador1, int *cartas_escolhidas, int id_sala)
{

    // Configurações do servidor e arquivo
    const wchar_t *host = L"gg128.ddnsfree.com"; // Servidor
    wchar_t path[100];
    swprintf(path, sizeof(path) / sizeof(wchar_t), L"./projetos/super-trunfo/SERVER/%d.txt", id_sala);
    // Vetores para armazenar os dados
    int vetor1[2] = {0};  // Vetor para os dois primeiros números
    int vetor2[32] = {0}; // Vetor para os 32 números seguintes

    // Abre sessão e conecta ao servidor
    HINTERNET hSession = WinHttpOpen(L"HTTP Reader/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     NULL, NULL, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, 0);

    // Faz a solicitação do arquivo
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path, NULL, NULL, NULL, 0);
    WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, 0, 0);
    WinHttpReceiveResponse(hRequest, NULL);

    // Lê o conteúdo do arquivo
    // DWORD tamanho;
    char buffer[2048] = {0};
    DWORD lido;
    if (WinHttpReadData(hRequest, buffer, sizeof(buffer) - 1, &lido))
    {
        buffer[lido] = '\0'; // Garantir que o buffer seja uma string válida

        // Processar o conteúdo do arquivo
        char *linha1 = strtok(buffer, "\n"); // Primeira linha
        char *linha2 = strtok(NULL, "\n");   // Segunda linha
        char *linha3 = strtok(NULL, "\n");   // Terceira linha (nome)

        // Processar vetor1
        char *token = strtok(linha1, ",");
        for (int i = 0; i < 2 && token != NULL; i++)
        {
            vetor1[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        (void)vetor1;

        // Processar vetor2
        token = strtok(linha2, ",");
        for (int i = 0; i < 32 && token != NULL; i++)
        {
            vetor2[i] = atoi(token);
            token = strtok(NULL, ",");
            cartas_escolhidas[i] = vetor2[i];
        }

        // Processar o nome
        if (linha3 != NULL)
        {
            strncpy(nome_jogador1, linha3, 50);
            nome_jogador1[50] = '\0'; // Garantir terminador nulo
        }
    }

    // Fechar conexões
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}

int verificarSalaVazia(int id_sala)
{
    int saida = 0;
    // Configurações do servidor e arquivo
    const wchar_t *host = L"gg128.ddnsfree.com"; // Servidor
    wchar_t path[100];
    swprintf(path, sizeof(path) / sizeof(wchar_t), L"./projetos/super-trunfo/SERVER/%d.txt", id_sala);
    // Vetores para armazenar os dados
    int vetor1[2] = {0};  // Vetor para os dois primeiros números
    int vetor2[32] = {0}; // Vetor para os 32 números seguintes
    char nome[51] = {0};  // Nome com até 50 caracteres

    // Abre sessão e conecta ao servidor
    HINTERNET hSession = WinHttpOpen(L"HTTP Reader/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     NULL, NULL, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, 0);

    // Faz a solicitação do arquivo
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path, NULL, NULL, NULL, 0);
    WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, 0, 0);
    WinHttpReceiveResponse(hRequest, NULL);

    // Lê o conteúdo do arquivo
    // DWORD tamanho;
    char buffer[2048] = {0};
    DWORD lido;
    if (WinHttpReadData(hRequest, buffer, sizeof(buffer) - 1, &lido))
    {
        buffer[lido] = '\0'; // Garantir que o buffer seja uma string válida

        // Processar o conteúdo do arquivo
        char *linha1 = strtok(buffer, "\n"); // Primeira linha
        char *linha2 = strtok(NULL, "\n");   // Segunda linha
        char *linha3 = strtok(NULL, "\n");   // Terceira linha (nome)

        // Processar vetor1
        char *token = strtok(linha1, ",");
        for (int i = 0; i < 2 && token != NULL; i++)
        {
            vetor1[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        if (vetor1[1] == 16)
        {
            saida = 1;
        }

        // Processar vetor2
        token = strtok(linha2, ",");
        for (int i = 0; i < 32 && token != NULL; i++)
        {
            vetor2[i] = atoi(token);
            token = strtok(NULL, ",");
        }

        (void)vetor2;

        // Processar o nome
        if (linha3 != NULL)
        {
            strncpy(nome, linha3, 50);
            nome[50] = '\0'; // Garantir terminador nulo
        }
    }

    (void)nome;

    // Fechar conexões
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return saida;
}

#endif