// FUNÇÕES PARA A TELA DE MENU - SEM SER PARTE DE DESENHO

#ifdef _WIN32 //Testa se o SO é Windows
      #include "../dependencias.h"   
#else
    #include "./dependencias.h"
#endif

// Função de declaração do menu:
void gerenciarCartas(RenderTexture2D *target, Music *musica, Sound sons[], Carta cartas[])
{

    // Variaveis:
    int submenu_tela = 5; //Variavel do submenus do gerenciador
    int carta_atual = 1; //Variavel que representa a carta atual do jogador
    Carta carta; //Struct da carta que sera desenhada para o usuario
    int total_cartas = quantidade_cartas; //Variavel que representa o total de cartas por operação
    int id_anterior = -1;
    int exportou; //Usado para export das cartas no csv [0 - Não solicitado, 1 - exportado corretamente, 2 - erro]
    int contador_frames_submenu6 = 0; //Usado para dar o aviso de exportou ao usuário

    Texture2D img_carta; //Usada na imagem do rosto atual

    // Definindo os botões do gerenciador:
    Botao botoes_gerenciador[7]; // Declara todos os botões da tela do gerenciador
    botoes_gerenciador[0].colisao = criarBotao(&botoes_gerenciador[0], 906, 552, NOSSO_AZUL, "MENU", 26, NOSSO_CINZA);
    botoes_gerenciador[1].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[1], 4, 3, 303, 53, NOSSO_AZUL, "ADICIONAR CARTA", NOSSO_CINZA);
    botoes_gerenciador[2].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[2], 4, 58, 303, 53, NOSSO_AZUL, "EXCLUIR CARTA", NOSSO_CINZA);
    botoes_gerenciador[3].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[3], 4, 111, 303, 53, NOSSO_AZUL, "EDITAR CARTA", NOSSO_CINZA);
    botoes_gerenciador[4].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[4], 4, 164, 303, 53, NOSSO_AZUL, "PESQUISAR CARTAS", NOSSO_CINZA);
    botoes_gerenciador[5].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[5], 4, 217, 151, 53, NOSSO_AZUL, "LISTAR", NOSSO_CINZA);
    botoes_gerenciador[6].tamanho_fonte_texto = criarBotaoTxtRedimensionavel(&botoes_gerenciador[6], 156, 217, 151, 53, NOSSO_AZUL, "EXPORT", NOSSO_CINZA);

    BotaoNulo botoes_nulos_gerenciador[2]; //Declara os botões invisiveis do gerenciado
    botoes_nulos_gerenciador[0].colisao = (Rectangle){913, 263, 67, 56};
    botoes_nulos_gerenciador[0].cor_botao = NOSSO_AZUL;
    botoes_nulos_gerenciador[1].colisao = (Rectangle){329, 263, 67, 56};
    botoes_nulos_gerenciador[1].cor_botao = NOSSO_AZUL;
    // Carregando as imagens:
    Texture2D fundo = LoadTexture("img/fundo-gerenciador.png"); //Carrega a imagem btn com som
    Texture2D setass = LoadTexture("img/seta.png"); //Carega a img da seta
    Texture2D seta = ResizeTexture(setass, 72, 72); //Redimensiona a seta 
    Texture2D frente_carta = LoadTexture("img/frente_carta.png");

    // Condição de tela:
    while (tela == 1)
    {

        //ESCALA DA TELA:
        scaleX = (float)GetScreenWidth() / COMPRIMENTO_TELA;
        scaleY = (float)GetScreenHeight() / ALTURA_TELA;
        scale = (scaleX < scaleY) ? scaleX : scaleY;

        //CONTROLES GERAIS:
        checarSaida(); //Chama a função que verifica se o usuário saiu
        checarTelaCheia();                                        // Chama função que verifica as condições de tela cheia
        leMouse();                                                // Chama a função global de leitura de mouse
        desenhoGerenciador(target, botoes_gerenciador, 7, fundo, submenu_tela, seta, frente_carta, carta_atual, total_cartas, carta, &img_carta, exportou); // Chama a função de desenho objetos do gerenciador
        controleSons(0, *musica, sons[0]);                        // Função de controle geral sons - mantem musica tocando
        resaltaBotoes(botoes_gerenciador, 7, *musica, sons[0]);   // Função que checa se o usuário esta sob um btn
        resaltaBotoesNulo(botoes_nulos_gerenciador, 2); //Função que checa se o usuário esta sob um btn

        //CONTROLE DAS CARTAS:

        carta = cartas[carta_atual - 1]; //Copia os dados da carta que será desenhada

        if(id_anterior != cartas[carta_atual - 1].id){
            id_anterior = cartas[carta_atual - 1].id;
            UnloadTexture(img_carta);
            img_carta = LoadTexture(cartas[carta_atual - 1].imagem);
        }

        if(checarClique(&botoes_nulos_gerenciador[0].colisao) && estado_tela != 2){
            carta_atual++;
        } //Clique btn direito

        if(checarClique(&botoes_nulos_gerenciador[1].colisao) && estado_tela != 2){
            carta_atual--;
        } //Clique btn esquerdo

        if(carta_atual > total_cartas){
            carta_atual = 1;
        } //Se maior que ultima volta para a 1

        if(carta_atual < 1){
            carta_atual = total_cartas;
        } //Se menor que 1 volta para a ultima

        // CHECAGEM DE CLIQUE DOS BOTÕES:
        if (checarClique(&botoes_gerenciador[0].colisao) && estado_tela != 2)
        {
            estado_tela = 2;
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[0].cor_botao = GREEN;
            trocar_tela = true;
        } // Voltar Menu  

        if (checarClique(&botoes_gerenciador[5].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[5].cor_botao = GREEN;
            submenu_tela = 5;
            carta_atual = 1;
        } //Submenu - LISTAR

        if (checarClique(&botoes_gerenciador[6].colisao) && estado_tela != 2)
        {
            controleSons(1, *musica, sons[1]); // Função de controle geral sons - tocar som clicou
            botoes_gerenciador[6].cor_botao = GREEN;
            submenu_tela = 6;
            exportou = exportarCsv(cartas);
        } //Submenu - EXPORTAR

        // CONTROLE DAS TELAS:

        if(submenu_tela == 6){
            if(contador_frames_submenu6 > 220){
                submenu_tela = 5;
                contador_frames_submenu6 = 0;
                exportou = 0;
            } else{
                contador_frames_submenu6++;
            } //Dara o aviso de exportou ao usuário por 220 Segundos
        }

        switch (estado_tela)
        {
        case 2:
            if (!IsSoundPlaying(sons[1]) && trocar_tela == true)
            {
                trocar_tela = false;
                UnloadTexture(fundo);
                UnloadTexture(img_carta);
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