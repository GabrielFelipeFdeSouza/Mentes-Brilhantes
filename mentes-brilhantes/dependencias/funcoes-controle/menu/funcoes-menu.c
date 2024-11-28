// FUNÇÕES PARA A TELA DE MENU - SEM SER PARTE DE DESENHO

#ifdef _WIN32 //Testa se o SO é Windows
    #include "../dependencias.h"
    #else
    #include "dependencias.h"
    #endif //Inclui relaativamente os arquivos de dependencia


// Função de declaração do menu:
void menu(RenderTexture2D *target, Music *musica, Sound sons[])
{

    // Variaveis:

    // Definindo os botões do menu:
    Botao botoes_menu[5]; // Declara todos os botões da tela de menu
    BotaoNulo botao_menu_som[1];
    botoes_menu[0].colisao = criarBotao(&botoes_menu[0], 42, 525, NOSSO_AZUL, "SAIR", 33, NOSSO_CINZA);
    botoes_menu[1].colisao = criarBotao(&botoes_menu[1], 42, 450, NOSSO_AZUL, "Créditos", 33, NOSSO_CINZA);
    botoes_menu[2].colisao = criarBotao(&botoes_menu[2], 42, 375, NOSSO_AZUL, "Gerenciar cartas", 33, NOSSO_CINZA);
    botoes_menu[3].colisao = criarBotao(&botoes_menu[3], 42, 300, NOSSO_AZUL, "Singleplayer", 33, NOSSO_CINZA);
    botoes_menu[4].colisao = criarBotao(&botoes_menu[4], 42, 225, NOSSO_AZUL, "Multiplayer", 33, NOSSO_CINZA);

    botao_menu_som[0].colisao = (Rectangle){916, 525, 50, 50};
    botao_menu_som[0].cor_botao = NOSSO_AZUL;

    // Carregando as imagens:
    Texture2D fundoss = LoadTexture("img/fundo.png"); //Carrega a imagem btn com som
    Texture2D fundo = ResizeTexture(fundoss, 1000, 600); //Carrega a imagem btn com som
    Texture2D btn_c_som_cru = LoadTexture("img/c-som.png"); //Carrega a imagem btn com som
    Texture2D btn_s_som_cru = LoadTexture("img/s-som.png"); //Carrega a imagem btn sem som
    Texture2D btn_c_som = ResizeTexture(btn_c_som_cru, 50, 50); //Redimensiona a imagem
    Texture2D btn_s_som = ResizeTexture(btn_s_som_cru, 50, 50); //Redimensiona a imagem
    Texture2D img_btn_som = btn_c_som;

    // Condição de tela:
    while (!WindowShouldClose() && (tela == 0 || tela == 2))
    {

        scaleX = (float)GetScreenWidth() / COMPRIMENTO_TELA;
        scaleY = (float)GetScreenHeight() / ALTURA_TELA;
        scale = (scaleX < scaleY) ? scaleX : scaleY;

        checarTelaCheia(); //Chama função que verifica as condições de tela cheia
        leMouse(); // Chama a função global de leitura de mouse
        desenhoMenu(target, botoes_menu, 5, *botao_menu_som, img_btn_som, fundo); // Chama a função de desenho objetos do menu
        controleSons(0, *musica, sons[0]); // Função de controle geral sons - mantem musica tocando
        resaltaBotoes(botoes_menu, 5, *musica, sons[0]); //Função que checa se o usuário esta sob um btn
        resaltaBotoesNulo(botao_menu_som, 1); //Função que checa se o usuário esta sob um btn

        // CHECAGEM DE CLIQUE DOS BOTÕES:

        if (checarClique(&botao_menu_som[0].colisao))
        {
            if (esta_mudo == false)
            {
                esta_mudo = true;
                controleSons(2, *musica, sons[1]); // Tira o som da musica
            }
            else
            {
                esta_mudo = false;
                controleSons(3, *musica, sons[1]);
            }
        } // Controle do som

        if (checarClique(&botoes_menu[0].colisao) && estado_tela != 7)
        {
            estado_tela = 7;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_menu[0].cor_botao = GREEN;
            trocar_tela = true;
        } //Sair

        if (checarClique(&botoes_menu[2].colisao) && estado_tela != 1)
        {
            estado_tela = 1;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_menu[2].cor_botao = GREEN;
            trocar_tela = true;
        } //Gerenciador Cartas

        // CONTROLE DAS TELAS:

        switch (estado_tela)
        {
        case 1:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(btn_c_som);
                UnloadTexture(btn_s_som);
                UnloadTexture(btn_c_som_cru);
                UnloadTexture(btn_s_som_cru);
                UnloadTexture(img_btn_som);
                tela = 1;
            } // Espera tocar para sair se o usuário deseja sair
            break;

        case 7:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(btn_c_som);
                UnloadTexture(btn_s_som);
                UnloadTexture(btn_c_som_cru);
                UnloadTexture(btn_s_som_cru);
                UnloadTexture(img_btn_som);
                UnloadRenderTexture(*target);
                tela = 7;
                CloseWindow();
            } // Espera tocar para sair se o usuário deseja sair
            break;

        default:
            break;
        }

        //Contola IMG do som:

        if(esta_mudo == false){
            img_btn_som = btn_c_som;
        } else{
            img_btn_som = btn_s_som;
        }
        
    } //Fim while da tela de menu

    return;
}