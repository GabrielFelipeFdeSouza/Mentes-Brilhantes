/*ARQUIVO MAIN - INICIALIZAÇÕES DAS DEPENDENCIAS RAYLIB, AUDIO, IMAGENS E ETC,
MAIS AS DIRETIVAS BASES DE SAIDA E ENTRADA*/

#include "dependencias.h"

// Constantes
const int COMPRIMENTO_TELA = 1000;
const int ALTURA_TELA = 600;

float scale, scaleX, scaleY;

bool esta_mudo = false; //Controle geral de sons
bool trocar_tela = false; //Controle geral se usuário quer mudar de tela, evitar congelamentos

// Variáveis globais
int tela = 0; // Sinalizador de tela que o usuário se encontra
int estado_tela = 0; //Sinalizador de intenção de troca de tela, usado para animações
Vector2 posicao_mouse; // Posição do mouse
Vector2 posicao_tela; // Posição da tela
int quantidade_cartas = 0;

int main(void)
{
    Carta *cartas = NULL; //Cria o ponteiro do vetor de cartas para uso no singlePlayer e gerenciador

    if(verificaOuCriaArquivoBinario("./data/cartas.bin")){
        //LE ARQ BINARIO:
        quantidade_cartas = carregarDadosBIN("./data/cartas.bin", &cartas); //Chama a função de leitura dos dados binarios e salva em cartas

        if (quantidade_cartas < 0) {
            printf("Erro ao carregar os dados.\n");
            return 1;
        }
    } else{
        //Salvando do CSV para o vetor struct cartas, se for a primeira vez:
        quantidade_cartas = carregarDadosCSV("./data/banco.csv", &cartas); //Chama a função de abertura do CSV e salva em cartas

        if (quantidade_cartas < 0) {
            printf("Erro ao carregar os dados.\n");
            return 1;
        }
    } //If que verifica se há o arquivo bin de cartas para começar

    printf("\n\n%s\n\n", cartas[5].nome);
    printf("\n\n%s\n\n", cartas[26].nome);
    printf("\n\n%d\n\n", cartas[8].criatividade); 
    printf("\nQUANTIDADE DE CARTAS LIDAS: %d\n\n", quantidade_cartas); //TESTE PARA VER SE OS ARQUIVOS FUNCIONARAM, TANTO BIN QUANTO CSV

    do{

        switch (tela)
        {
        case 0: //MENU
            // Configuração de janela e audio - apenas uma vez:
            InitWindow(COMPRIMENTO_TELA, ALTURA_TELA, "Mentes Brilhantes"); // Inicialização da tela inicial
            SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNFOCUSED);  // Seta a tela para rodar, mesmo se não focada, mas se minimizada pelo botão, congela
            RenderTexture2D target = LoadRenderTexture(COMPRIMENTO_TELA, ALTURA_TELA); //Cria a textura de renderização
            SetTargetFPS(60); // Setando o framerate da raylib para 60
            ShowCursor(); // Habilita a raylib para desenhar o cursor do S.O
            InitAudioDevice(); //Inicia o dispositivo padrão de audio

            // Configurações das musicas:
            Music musica;
            musica = LoadMusicStream("./sounds/musica.mp3");
            PlayMusicStream(musica);
            Sound sons[2];
            sons[0] = LoadSound("./sounds/sobbtn.mp3");
            sons[1] = LoadSound("./sounds/clicou.mp3");

            menu(&target, &musica, sons); //Chama a tela de menu com a textura base de desenho redimensionavel
            break;

        case 2: //MENU SE JA ESTIVER ABERTO:
            menu(&target, &musica, sons); //Chama a tela de menu com a textura base de desenho redimensionavel
            break; 

        case 1: //GERENCIADOR DE CARTAS
            gerenciarCartas(&target, &musica, sons); //Chama a tela de gerenciar cartas com a textura base de desenho redimensionavel
            break;

        default:
            break;
        
        } //Switch relaciona qual tela o usuário se encontra
    }while(tela < 8 && !WindowShouldClose()); //Checa se a tela é invalida ou se o usuário a fechou
    
    salvarDados("./data/cartas.bin", cartas); //Salva os dados no arq.bin antes de sair
    printf("SAINDO\n");
    free(cartas);
    tela = 10;
    CloseAudioDevice();
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
