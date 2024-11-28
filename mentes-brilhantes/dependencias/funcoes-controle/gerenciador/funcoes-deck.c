// FUNÇÕES PARA A TELA DE MENU - SEM SER PARTE DE DESENHO

#ifdef _WIN32 //Testa se o SO é Windows
    #include "../dependencias.h"
    #else
    #include "dependencias.h"
    #endif //Inclui relaativamente os arquivos de dependencia

// Função de declaração do menu:
void gerenciarCartas(RenderTexture2D *target, Music *musica, Sound sons[])
{

    // Variaveis:
    int submenu_tela = 5; //Variavel do submenus do gerenciador

    // Definindo os botões do gerenciador:
    Botao botoes_gerenciador[7]; // Declara todos os botões da tela de menu;
    botoes_gerenciador[0].colisao = criarBotao(&botoes_gerenciador[0], 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);
    botoes_gerenciador[1].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[1], 4, 3, 303, 53, NOSSO_AZUL, "ADICIONAR CARTA", NOSSO_CINZA);
    botoes_gerenciador[2].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[2], 4, 58, 303, 53, NOSSO_AZUL, "EXCLUIR CARTA", NOSSO_CINZA);
    botoes_gerenciador[3].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[3], 4, 111, 303, 53, NOSSO_AZUL, "EDITAR CARTA", NOSSO_CINZA);
    botoes_gerenciador[4].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[4], 4, 164, 303, 53, NOSSO_AZUL, "PESQUISAR CARTAS", NOSSO_CINZA);
    botoes_gerenciador[5].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[5], 4, 217, 151, 53, NOSSO_AZUL, "LISTAR", NOSSO_CINZA);
    botoes_gerenciador[6].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[6], 156, 217, 151, 53, NOSSO_AZUL, "EXPORT", NOSSO_CINZA);

    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-gerenciador.png"); // Carrega a imagem btn com som

    // Condição de tela:
    while (!WindowShouldClose() && tela == 1)
    {

        scaleX = (float)GetScreenWidth() / COMPRIMENTO_TELA;
        scaleY = (float)GetScreenHeight() / ALTURA_TELA;
        scale = (scaleX < scaleY) ? scaleX : scaleY;

        checarTelaCheia();                                        // Chama função que verifica as condições de tela cheia
        leMouse();                                                // Chama a função global de leitura de mouse
        desenhoGerenciador(target, botoes_gerenciador, 7, fundo, submenu_tela); // Chama a função de desenho objetos do gerenciador
        controleSons(0, *musica, sons[0]);                        // Função de controle geral sons - mantem musica tocando
        resaltaBotoes(botoes_gerenciador, 7, *musica, sons[0]);   // Função que checa se o usuário esta sob um btn
        // resaltaBotoesNulo(botao_menu_som, 1); //Função que checa se o usuário esta sob um btn

        // CHECAGEM DE CLIQUE DOS BOTÕES:

        if (checarClique(&botoes_gerenciador[0].colisao) && estado_tela != 2)
        {
            estado_tela = 2;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[0].cor_botao = GREEN;
            trocar_tela = true;
        } // Voltar Mnenu

        

        if (checarClique(&botoes_gerenciador[5].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[5].cor_botao = GREEN;
            submenu_tela = 5;
        } //Submenu - LISTAR

        // CONTROLE DAS TELAS:

        switch (estado_tela)
        {
        case 2:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(fundo);
                tela = 2;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }

        if(!IsSoundPlaying(sons[1])){
            for(int u = 0; u < 7; u++){
                if(coresIguais(botoes_gerenciador[u].cor_botao, GREEN))
                    botoes_gerenciador[u].cor_botao = NOSSO_AZUL;
            }
        } //Muda apos clique a cor de fundo do botão

    }

    return;
}