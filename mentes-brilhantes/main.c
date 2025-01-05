/*ARQUIVO MAIN - INICIALIZAÇÕES DAS DEPENDENCIAS RAYLIB, AUDIO, IMAGENS E ETC,
MAIS AS DIRETIVAS BASES DE SAIDA E ENTRADA*/

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
#include <time.h>
#include "funcoes-creditos.h"

// Constantes
const int COMPRIMENTO_TELA = 1000;
const int ALTURA_TELA = 600;

float scale, scaleX, scaleY;

bool esta_mudo = true;    // Controle geral de sons
bool trocar_tela = false; // Controle geral se usuário quer mudar de tela, evitar congelamentos

// TELAS: 0 e 2 - Menu, 1 - Gerenciador, 3 - Jogo Single-player, 11 - Erros

// Variáveis globais:
int tela = 0;          // Sinalizador de tela que o usuário se encontra
int estado_tela = 0;   // Sinalizador de intenção de troca de tela, usado para animações
Vector2 posicao_mouse; // Posição do mouse
Vector2 posicao_tela;  // Posição da tela
int quantidade_cartas = 0;
Color *cor_aleatoria = NULL; // Usada para a função de super trunfo
Image icon;                  // Para uso do icone
Carta *cartas;               // Cria o ponteiro do vetor de cartas para uso no singlePlayer e gerenciador
int botoes_resaltar = 0;

int main(void)
{

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    if (verificaOuCriaArquivoBinario("./data/cartas.bin"))
    {
        // LE ARQ BINARIO:
        quantidade_cartas = carregarDadosBIN("./data/cartas.bin"); // Chama a função de leitura dos dados binarios e salva em cartas

        if (quantidade_cartas <= 0)
        {
            printf("GAME: Erro ao carregar os dados.\n");
            telaErro("Erro ao ler dados do arquivo BIN na abertura!");
            tela = 11;
        }
    }
    else
    {
        // Salvando do CSV para o vetor struct cartas, se for a primeira vez:
        quantidade_cartas = carregarDadosCSV("./data/banco.csv"); // Chama a função de abertura do CSV e salva em cartas

        if (quantidade_cartas <= 0)
        {
            printf("GAME: Erro ao carregar os dados.\n");
            telaErro("Erro ao ler dados do arquivo CSV na primeira abertura!");
            tela = 11;
        }
        else
        {
            abrePdf(); // Abre o pdf de boas vindas se for a primeira vez - Instruções e regras
        }
    } // If que verifica se há o arquivo bin de cartas para começar

    printf("\nGAME: QUANTIDADE DE CARTAS LIDAS: %d\n\n", quantidade_cartas); // TESTE PARA VER SE OS ARQUIVOS FUNCIONARAM, TANTO BIN QUANTO CSV

    do
    {

        switch (tela)
        {
        case 0: // MENU
            // Configuração de janela e audio - apenas uma vez:
            InitWindow(COMPRIMENTO_TELA, ALTURA_TELA, "Mentes Brilhantes");            // Inicialização da tela inicial
            SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);             // Seta a tela para rodar, mesmo se não focada, mas se minimizada pelo botão, congela
            RenderTexture2D target = LoadRenderTexture(COMPRIMENTO_TELA, ALTURA_TELA); // Cria a textura de renderização
            SetTargetFPS(60);                                                          // Setando o framerate da raylib para 60
            icon = LoadImage("./img/icon.png");                                        // Carega a img de icone para usar
            SetWindowIcon(icon);                                                       // Desenha o icone
            ShowCursor();                                                              // Habilita a raylib para desenhar o cursor do S.O
            InitAudioDevice();                                                         // Inicia o dispositivo padrão de audio

            // Configurações das musicas:
            Music musica;
            musica = LoadMusicStream("./sounds/musica.mp3");
            PlayMusicStream(musica);
            Sound sons[2];
            sons[0] = LoadSound("./sounds/sobbtn.mp3");
            sons[1] = LoadSound("./sounds/clicou.mp3");
            controleSons(2, musica, sons[1]); // Tira o som da musica - PADRAO

            menu(&target, &musica, sons); // Chama a tela de menu com a textura base de desenho redimensionavel
            break;

        case 2:                           // MENU SE JA ESTIVER ABERTO:
            menu(&target, &musica, sons); // Chama a tela de menu com a textura base de desenho redimensionavel
            break;

        case 1:                                      // GERENCIADOR DE CARTAS
            gerenciarCartas(&target, &musica, sons); // Chama a tela de gerenciar cartas com a textura base de desenho redimensionavel
            break;

        case 3:                                        // SINGLEPLAYER GAME
            jogarSingleplayer(&target, &musica, sons); // Chama a tela de jogo singleplayer com a textura base de desenho redimensionavel
            break;

        case 4:                         //CREDITOS
            creditos(&target, &musica, sons); // Chama a tela de creditos com a textura base de desenho redimensionavel
            break;

        case 11:      // ERROS
            return 0; // Sai do código principal se tiver erro, após a tela de erro
            break;

        default:
            break;

        } // Switch relaciona qual tela o usuário se encontra
    } while (tela < 8); // Checa se a tela é invalida ou se o usuário a fechou

    CloseWindow();
    UnloadImage(icon);
    printf("\nGAME: SAINDO DO GAME...\n");
    salvarDados("./data/cartas.bin"); // Salva os dados no arq.bin antes de sair
    free(cartas);
    free(cor_aleatoria); // Libera a memoria das cores
    CloseAudioDevice();
    printf("GAME: Saiu na tela: %d | Estado de tela estava em: %d\n", tela, estado_tela);                                                                    // Depuração
    printf("GAME: Quantidade de cartas salvas: %d, tamanho do arquivo binario em bytes: %d\n\n", quantidade_cartas, (int)sizeof(Carta) * quantidade_cartas); // Depuração
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
