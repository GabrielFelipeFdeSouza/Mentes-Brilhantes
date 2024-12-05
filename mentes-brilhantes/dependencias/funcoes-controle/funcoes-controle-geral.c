// FUNÇÕES PARA AS FUNÇÕES DE CONTROLE - SEM SER PARTE DE DESENHO:

#include "../../dependencias.h"

extern Vector2 posicao_mouse; // Chamada da variavel global posicao_mouse

bool coresIguais(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
} //Função que verifica se duas cores são iguais

void leMouse()
{
    // Obtemos as posições brutas do mouse na janela
    posicao_mouse.x = GetMouseX();
    posicao_mouse.y = GetMouseY();

    // Ajustamos a posição X do mouse para o sistema de coordenadas do jogo
    posicao_mouse.x = (posicao_mouse.x - (GetScreenWidth() - (COMPRIMENTO_TELA * scale)) * 0.5f) / scale;

    // Ajustamos a posição Y do mouse para o sistema de coordenadas do jogo
    posicao_mouse.y = (posicao_mouse.y - (GetScreenHeight() - (ALTURA_TELA * scale)) * 0.5f) / scale;

    return;
} //Função de leitura da posição do cursor em relação à janela aberta

void checarSaida(){

    if(WindowShouldClose()){
        tela = 10;
    } //Se a tela for fechada pelo usuário ou funções de sair, seta tela = 10 para uso na main

    return;
} //Função que verifica se o usuário quer sair

bool checarClique(Rectangle *botao)
{
    if (IsMouseButtonPressed(0) && CheckCollisionPointRec(posicao_mouse, *botao))
    {
        return true;
    }
    else
    {
        return false;
    }
} //Função que checa clique do mouse em um botão, além da colisão

void controleSons(int controle, Music musica, Sound som){
    switch (controle)
    {
    case 1:
        if(esta_mudo == false){
            PlaySound(som); // Toca apenas uma vez o som do input
        }
        break;

    case 2:
        SetMusicVolume(musica, 0); //Tira o som da musica
        break;

    case 3:
        SetMusicVolume(musica, 1); //Recoloca o som do jogo com som 1
        break;
    
    default:
        UpdateMusicStream(musica); // Mantem a musica tocando
        break;
    }
    return;
} //Função que controla as musicas e sons ao ser chamada

void checarTelaCheia(){
    if (IsKeyPressed(KEY_F11))
    {
        int display = GetCurrentMonitor(); // mostra em qual monitor estamos, caso tenha mais de 1

        //if (IsWindowFullscreen())
        if(GetScreenWidth() > 1000)
        {
            // Se estiver já em tela cheia:
            //ToggleFullscreen();                                // Tira de telacheia
            SetWindowSize(COMPRIMENTO_TELA, ALTURA_TELA);      // Seta o tamanho da tela para o original
            SetWindowPosition(posicao_tela.x, posicao_tela.y); // Seta a posição para o meio
        }
        else
        {
            posicao_tela = GetWindowPosition();                                 // Obtem a posição de tela antes de redimensionar para mudar depois
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display)); // Seta para o tamanho max do monitor
            SetWindowPosition(0, 0); // Seta a posição para o 0,0 do monitor
            //ToggleFullscreen();                                                 // Coloca em telacheia
        }

    } // Fim if muda estado pelo F11
} //Função que checa estados de tela cheia e tecla F11 para togle disso


void abrePdf() {
    printf("\nAbrindo PDF inicial...\n");
    #ifdef _WIN32
        system("start ./data/instrucoes.pdf");
    #elif __linux__
        system("xdg-open ./data/instrucoes.pdf");
    #else
        printf("Sistema operacional não suportado.\n");
    #endif
}