#Arquivo de detalhes de construção e programação do jogo - MENTES BRILHANTES:

**DETALHES DA EQUIPE**

    -Gabriel Felipe F. de Souza;
    -Gustavo Ferreira da Fonseca;
    -Thiago André M. Málaga;

**DETALHES GERAIS**

Ainda estamos construindo/identando o jogo, funções estão quase todas funcionando, mas devido aos erros com raylib
nos computadores da faculdade pode estar causando erros no mesmo que serão corrigidos para a entrega final.
Problema com a função que ressalta no gerenciador de cartas.

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

    *Editar-cartas.c*
        Neste arquivo, quando ele é chamado, as funções são responsáveis pela edição de cartas,
        ele verifica quais parametros estão vazios e mantem esses originais, apenas mudando os
        que tem algo na caixa de texto relacionado. Ainda ele verifica se há mais de um super-trunfo
        no baralho e da um alerta ao usuário.
        Assim como no adicionar esse setor trabalha recebendo parametros do gerenciador e após o processamento
        retorna erros pelos returns para o gerenciador exibir os erros, ou altera no vetor cartas os 
        respectivos campos alterados.

    *Excluir-cartas.c*
        A exclusão embora pareça a mais simples das funções é na realidade bem complexa, pois além de 
        "remover" tal carta do vetor, precisa-se ajustar as posições das cartas para ocupar o menor
        espaço possivel e os id's também se ajustarem.
        Quando a função é chamada passa-se o id atual da carta que deseja-se excluir, e assim a função
        apenas coloca esse id no vetor de cartas para -1, quando chama a função de ajuste de posições,
        e essa chega nesse id -1, começa a copiar as informações das cartas com id+1 para a nova posição
        e tambem ajusta os id's para uso nas outras fuções, assim perdendo aquelas informações da carta 
        que desejava-se excluir e ajustando todo o vetor. o resto da lógica está no gerenciador de cartas.

    *Pesquisar-cartas.c*
        Essa é a função auxiliar mais complexa do gerenciador, ela é responsavel por todo o submenu de 
        pesquisa, é ela que retorna um novo vetor de tamanho dinamico para o gerenciador e ele irá
        exibi-lo ao usuário. Ela inicialmente recebe as caixas de texto do gerenciador e verifica se 
        há alguma com texto, pois se não houver não há oque pesquisar, assim mandando -1 para o gerenciador
        e por sua vez o gerenciador irá colocar apenas o listar. Se houver campos/super-trunfo para pesquisa
        ele irá verificar com prioridade o super-trunfo, se este estiver desligado, verificará os outros
        campos, relativo a qual esta ativo pelo radio button correspondente. Fora o hexadecimal, os outros
        parametros seguem a mesma lógica: Percorre o vetor de cartas em busca de uma carta com o parametro
        dentro do range buscado, se encontrar, aumenta com realloc o tamanho do vetor que será devolvido ao
        gerenciador para desenho e compia para essa nova posição essa carta encontrada. No caso do hexadecimal
        que é o numero e letra, o usuário pode pesquisa usando apenas uma das duas caixas de texto ou usando
        as duas, assim a função verifica em que caso está e pesquisa por igualdade, seguindo o mesmo principio
        das outras.

    *Funcoes-deck.c*
        Aqui é que o deck é totalmente controlado, desde as funções auxiliares dele
        até seu desenho especifico, entre outros detalhes, esse é o coração do
        gerenciador de cartas. O gerenciador é dividido em vários setores, dede o seu controle, exibição
        até o gerenciamento em si. As funções básicas de botoões e telas garantem um pleno funcionmento do
        gerenciador. O sistema de botoes é baseado na animação que deixa ele verde e após isso, executa
        uma ação, no caso, temos várias ações possiveis de acordo com cada botão:
        -Listar: Nesse, o gerenciador por padrão abre nele, exibe todas as cartas sem filtro;
        -Pesquisar: No caso o usuário terá campos que poderá pesquisar por atributos espeficos, não sendo
        acumulativos, e assim as funções filtrarão e exibirão na tela o resultado, similar ao listar;
        -Excluir: Nesse o usuario excluirá a carta que ele estiver na observação, pelo id da carta;
        -Editar: O usuário pode editar 1 ou mais atributos da carta que estiver em observação;
        -Exportar: Da opção do usuário exportar um arquivo csv com todas as cartas que estiverem no deck;
        -Adicionar: O usuário coloca uma nova carta ao baralho, no caso, em seu fim.
        As funções, fora a pesquisar, quando são terminadas retornam ao estado de listar. Há tambem
        alguns casos em que as funções auxiliares podem retornar erros para exibição ao usuário, nesse caso, há
        um temporizador feito com frames, que mostra a msg para o usuário pelo tempo programado, atravez do vetor
        retorno_funcoes. Extruturalmente falando a tela é baseada num loop, que enquanto o usuário estiver no
        gerenciador as funções de verificação/desenho/auxiliares estaão sendo chamadas de acordo com a 
        logica propria da função, incialmente ela realiza um ciclo basico de funções, que estão contidas em todas
        as outras telas, apó isso vai para o controle das funções auxiliares, checando cada caso, após isso ela
        passa pelo controle e checagem de todos os botões da tela, e no fim realiza o controle das telas para o 
        próximo ciclo de acordo com as escolhas do usuário.
