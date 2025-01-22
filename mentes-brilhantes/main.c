/*
-->MAIN<--
Arquivo base do jogo, responsavel polr inicializar as coisas importantes e
também por fecha-las*/

#include "main.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs-gerais.h"
#include "ler-arquivos.h"
#include "escrever-arquivos.h"
#include "desenho-geral.h"
#include "funcoes-controle-geral.h"
#include "funcoes-menu.h"
#include "funcoes-deck.h"
#include "funcoes-emjogo-bot.h"
#include "funcoes-emjogo-multiplayer.h"
#include <time.h>
#include "funcoes-creditos.h"
#include <math.h>
#include "funcoes-rede.h"

//---------------------------------
// CONSTANTES
//---------------------------------
const int COMPRIMENTO_TELA = 1000;
const int ALTURA_TELA = 600;

float scale, scaleX, scaleY;

bool esta_mudo = true;    // Controle geral de sons
bool trocar_tela = false; // Controle geral se usuário quer mudar de tela, evitar congelamentos

//---------------------------------
// VARIAVEIS GLOBAIS
//---------------------------------

// TELAS: 0 e 2 - Menu, 1 - Gerenciador, 3 - Jogo Single-player, 11 - Erros
int tela = 0;                // Sinalizador de tela que o usuário se encontra, iniciando no menu
int estado_tela = 0;         // Sinalizador de intenção de troca de tela, usado para animações
Vector2 posicao_mouse;       // Posição do mouse
Vector2 posicao_tela;        // Posição da tela
int quantidade_cartas = 0;   // Representa a quantidade de cartas no vetor basico
Color *cor_aleatoria = NULL; // Usada para a função de super trunfo e do creditos
Image icon;                  // Para uso do icone de canto na janela
Carta *cartas;               // Cria o ponteiro do vetor de cartas para uso no singlePlayer e gerenciador
Carta *cartas_multiplayer;   // Cria o ponteiro do vetor de cartas para uso no multiplayer
int botoes_resaltar = 0;     // Variavel usada para controla os botoes à serem resaltados
char buffer[512];            // Usado para as funções do log

int main(void)
{

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    //---------------------------------
    // CONTROLE VETOR CARTAS
    //---------------------------------

    iniciarArquivoLog(); // Inicia o arquivo de log

    escreverLog("Jogo iniciado com sucesso!");

    if (verificaOuCriaArquivoBinario("./data/cartas.bin"))
    {
        // LE ARQ BINARIO:
        escreverLog("Lendo dados do arquivo binário!");
        quantidade_cartas = carregarDadosBIN("./data/cartas.bin"); // Chama a função de leitura dos dados binarios e salva em cartas

        if (quantidade_cartas <= 0)
        {
            escreverLog("Erro ao abrir/ler os dados do arquivo binário!");
            telaErro("Erro ao ler dados do arquivo BIN na abertura!");
            tela = 11;
        }
    }
    else
    {
        // Salvando do CSV para o vetor struct cartas, se for a primeira vez:
        escreverLog("Lendo dados do arquivo CSV!");
        quantidade_cartas = carregarDadosCSV("./data/banco.csv"); // Chama a função de abertura do CSV e salva em cartas

        if (quantidade_cartas <= 0)
        {
            escreverLog("Erro ao abrir/ler os dados do arquivo CSV!");
            telaErro("Erro ao ler dados do arquivo CSV na primeira abertura!");
            tela = 11;
        }
        else
        {
            escreverLog("Abrindo arquivo pdf...");
            abrePdf(); // Abre o pdf de boas vindas se for a primeira vez - Instruções e regras
        }
    } // If que verifica se há o arquivo bin de cartas para começar

    escreverLog("Lendo cartas para o modo de jogo multiplayer");
    lerCartasMultiplayer(); // Le as cartas para o jogo do multiplayer, mantendo a unicidade de cartas, le do arquivo de banco.csv

    snprintf(buffer, sizeof(buffer), "QUANTIDADE DE CARTAS LIDAS DO VETOR PRINCIPAL: %d", quantidade_cartas);
    escreverLog(buffer);

    //---------------------------------
    //  CONTROLE GERAL DAS TELAS
    //---------------------------------

    do
    {

        switch (tela)
        {
        case 0: // MENU, com inicializações das dependencias
            // Configuração de janela e audio - apenas uma vez:
            escreverLog("Iniciando as configurações padrões de tela, e setando as configurações gerais.");
            InitWindow(COMPRIMENTO_TELA, ALTURA_TELA, "Mentes Brilhantes");            // Inicialização da tela inicial
            SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);             // Seta a tela para rodar, mesmo se não focada, mas se minimizada pelo botão, congela
            RenderTexture2D target = LoadRenderTexture(COMPRIMENTO_TELA, ALTURA_TELA); // Cria a textura de renderização
            SetTargetFPS(60);                                                          // Setando o framerate da raylib para 60
            icon = LoadImage("./img/icon.png");                                        // Carega a img de icone para usar
            SetWindowIcon(icon);                                                       // Desenha o icone
            ShowCursor();                                                              // Habilita a raylib para desenhar o cursor do S.O
            InitAudioDevice();                                                         // Inicia o dispositivo padrão de audio

            // Configurações das musicas:
            escreverLog("Iniciando as configurações de som e musica.");
            Music musica;
            musica = LoadMusicStream("./sounds/musica.mp3");
            PlayMusicStream(musica);
            Sound sons[2];
            sons[0] = LoadSound("./sounds/sobbtn.mp3");
            sons[1] = LoadSound("./sounds/clicou.mp3");
            controleSons(2, musica, sons[1]); // Tira o som da musica - PADRAO

            escreverLog("Abrindo a tela de MENU.");
            menu(&target, &musica, sons); // Chama a tela de menu com a textura base de desenho redimensionavel
            break;

        case 2: // MENU SE JA ESTIVER ABERTO:
            escreverLog("Abrindo a tela de MENU.");
            menu(&target, &musica, sons); // Chama a tela de menu com a textura base de desenho redimensionavel
            break;

        case 1: // GERENCIADOR DE CARTAS
            escreverLog("Abrindo a tela de GERENCIAR CARTAS.");
            gerenciarCartas(&target, &musica, sons); // Chama a tela de gerenciar cartas com a textura base de desenho redimensionavel
            break;

        case 3: // SINGLEPLAYER GAME
            escreverLog("Abrindo a tela de JOGAR SINGLEPLAYER.");
            jogarSingleplayer(&target, &musica, sons); // Chama a tela de jogo singleplayer com a textura base de desenho redimensionavel
            break;

        case 4: // CREDITOS
            escreverLog("Abrindo a tela de CREDITOS.");
            creditos(&target, &musica, sons); // Chama a tela de creditos com a textura base de desenho redimensionavel
            break;

        case 5: // MULTIPLAYER GAME
            escreverLog("Abrindo a tela de MULTIPLAYER.");
            jogarMultiplayer(&target, &musica, sons);
            break;

        case 11: // ERROS
            escreverLog("Abrindo a tela de ERROS.");
            return 0; // Sai do código principal se tiver erro, após a tela de erro
            break;

        default:
            break;

        } // Switch relaciona qual tela o usuário se encontra
    } while (tela < 8); // Checa se a tela é invalida ou se o usuário a fechou

    //---------------------------------
    // FECHAMENTO DO JOGO E ARQUIVOS
    //---------------------------------
    escreverLog("Iniciando SAIDA DO GAME.");
    CloseWindow();
    UnloadImage(icon);
    salvarDados("./data/cartas.bin"); // Salva os dados no arq.bin antes de sair
    escreverLog("Dados salvos no arquivo binário.");
    free(cartas);
    free(cor_aleatoria); // Libera a memoria das cores
    CloseAudioDevice();
    snprintf(buffer, sizeof(buffer), "Saiu na tela: %d | Estado de tela estava em: %d.", tela, estado_tela);
    escreverLog(buffer);
    snprintf(buffer, sizeof(buffer), "Quantidade de cartas salvas: %d, tamanho do arquivo binario em bytes: %d", quantidade_cartas, ((int)sizeof(Carta) * quantidade_cartas) + 4);
    escreverLog(buffer);                                                                     // Depuração
    return 0;
}

// Função para redimensionar a textura (Imagens) - dependencia raylib:
Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight)
{
    Image image = LoadImageFromTexture(texture);        // Obter a imagem da textura
    ImageResize(&image, newWidth, newHeight);           // Redimensionar a imagem
    Texture2D newTexture = LoadTextureFromImage(image); // Criar uma nova textura a partir da imagem redimensionada
    UnloadImage(image);                                 // Liberar a imagem temporária
    return newTexture;
}
