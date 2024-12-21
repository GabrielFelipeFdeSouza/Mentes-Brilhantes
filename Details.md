#Arquivo de detalhes de construção e programação do jogo - MENTES BRILHANTES:

**DETALHES GERAIS**

Ainda estamos construindo/identando o jogo, funções estão quase todas funcionando, mas devido aos erros com raylib
nos computadores da faculdade pode estar causando erros no mesmo que serão corrigidos para a entrega final.
Campo adicionar ainda com um erro de memória!

**DETALHES ESPECIFICOS DAS FUNÇÕES**

    *Escreve-arquivos.c*
        Arquivo de escrita em arquivos do jogo, tanto em CSV quanto em BIN.
        Responsável por receber as ordens da main/controle do gerenciador e o vetor de cartas, além da quantidade
        que é global e escrever nos arquivos, binário para uso do próprio jogo e csv para export do usuário.
        No caso do arquivo de escrita binária ele coloca na primeira posição a quantidade de cartas para ser lida na próxima
        abertura do game, como primeiro fator, afim de saber quantas cartas esse deck tem. 

    *Ler-arquivos.c*
        Arquivo de leitura em arquivos do jogo, tanto em CSV quanto em BIN.
        Responsável por receber as ordens da main para checar se há o arquivo binário presente na pasta
        de dados, e processar na main, também le os arquivos em ambos os tipos de arquivos de acordo com
        os comandos da main. Usamos na função de ler o arquivo csv uma engenharia que não é nescessária, iremos nas futuras
        atualizações colocar diretamente o fscanf para leitura. Essa função ainda realoca o tamanho de cartas se tiver muitas
        cartas e a alocação inicial não der conta. Ambas as funções de leitura, funcionam bem similar, elas leem os arquivos
        e retornam via referencia.

    *Adicionar-cartas.c*
        Arquivo responsavel por gerenciar a lógica de adicionar cartas, sempre que for
        chamado pelo gerenciador ele faz as verificações, se tiver tudo certo adiciona a carta
        ao final do vetor de structs.
        Bem simples, essa função pega as informações mandadas pelo gerenciador e adiciona no final do cartas
        porém, antes ele checa se há alguns requesitos para fazer tal adição.