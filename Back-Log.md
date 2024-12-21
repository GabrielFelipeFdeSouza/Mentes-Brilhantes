#Arquivo de Backlog de construção e programação do jogo - MENTES BRILHANTES:

**14/11/24 - 20:50 - 23:00, Gabriel:**
Ajustei os arquivos em questão de dependencia, *deixando parte de imagens para teste posterior, além da função*
*de escala do game*;


**15/11/24 - 07:30 - 09:28, Gabriel:**
Fiz um teste bem sucedido com carregamento, redimensionamento e exibição de imagens. Ajustei o arquivo makefile
para pegar todos os arquivos e subpastas dentro de "mentes-brilhantes", e por fim, começei a organização das
funções nos seus arquivos especificos.;


**15/11/24 - 10:00 - 12:00, Thiago:**
Mudei o nome e todas as referencias da ex funcao-menu para funcao-controle-geral, pois estava sendo usada apenas
para pegar as informacoes basicas. Criei um struct para botoes do menu e outros, na pasta desenho-menu.c. Criei
uma funcao para achar as dimensoes exatas do botao dado um ponto inicial, um texto e uma fonte.
criei uma funcao para desenhar o retangulo e o texto do botao dado uma variavel struct botao qualquer.;


**15/11/24- 12:20 - 13:25 - Gabriel:**
Juntei as funções de ciar botão que retorna a caixa de colisao dela, coloquei o strict botao, num arquivo c para 
todas as structs, e agora as funções de criarbotao e desenharbotao, recebem o struct Botao, *ficou para o próximo,*
*desenhar o txt relativo ao botao na função de desenho do botao e dar uma organizadinha*;


**15/11/24 - 13:40 - 14:05 - Gustavo e Thiago:**
Desenhar o txt relativo ao botao na função de desenho do botao.;


**15/11/24 - 14:30 - 15:20 - Gustavo e Thiago:**
Conseguimos colocar o efeito sonoro ao clicar no botao e precisa arrumar a musica.;


**15/11/24 -  19:20 - 20:00- Gabriel:**
Coloquei a musica para funcionar e tocar infinitamente dentro do while, quem precisar das funções de audio,
é só dar uma olahada na lista de comandos da raylib. Também, coloquei a flag para a tela não congelar mesmo se 
não estiver focada, mas descobri que isso não funciona  se voce minimizar pelo botão, se isso ocorrer o jogo, 
semre congelará. *Próximos passos, começar a organizar a estrutura de telas do jogo e variaveis de controle geral*;


**16/11/24 - 15:00 - 17:32 - Gabriel:**
Fiz com que em cada arquivo, apenas um include seja dado, ele é o include de dependencias.h que oinclui já todos,
os arquivos do jogo, mais as bibliotecas padrões para execução. Ainda também reorganizei a main.c e desloquei
alguns de seus conteudos para a função de controle do menu, afinal na main.c só ficará o switch com o caso base.
Ainda organizei mais alguns arquivos .h e .c para que estejam reultilizaveis perante todo o código, ex:
repassei as funções de botao para desenho-geral, para ser reultilizado, entre outras  alterações nessa parte.
Criei por fim o sistema de controle de audio facilitado que é apenas a função controleSons(), que gerencia *todos*
*os sons, agora sim creio que seja a hora de colocar a mão realmente na massa e fazer o contudo do game!*;


**19/11/24 - 20:40 - 22:00 - Thiago:**
Criei os botões do menu, com a paleta de cor do jogo, arrumei as funções do botão, para colocar bordas.
*Fica para tras colocar background na tela!*


**19/11/24 - 22:02 - 22:40 - Gabriel:**
Criei as funções que realçam botões (ambos os tipos), também adicioneis os botões Nulos que terão imagens,
sem txt, botei também o fundo para preto.;


**20/11/24 - 07:40 - 08:55 - Gabriel:**
Coloquei sons se o usuário passar em cima do botão com o mouse, e um som para quando os botões forem clicados,
sem que altere o fluxo do programa, o som é executado e então é chamado a função especifica. 
*Fica para depois colocar as funções de som em um arquivo só*;


**21/11/24 - 21:00 - 23:00 - Gabriel, Thiago e Gustavo:**
Fizemos as imagens do menu, ficando uma para depois, colcoamos a tela para redimensionar, deixando para,
redimensionar os botões depois, e colocamos o estado_tela para controle da animação do botão (COLOCAR NUMA FUNÇÃO).;


**22/11/24 - 06:50 - 07:25 - Gabriel:**
Fiz as caixas de colisão do botão redimensionarem com a tela, fiz também o F11 funcionar.;


**22/11/24 - 21:20 - 23:35 - Gabriel:**
Arrumei algumas funções gerais de lugar para serem reultilizadas, coloquei o sistema de saida forçada do usuario,
no switch da main, além de dar uma arrumada nessa parte para problemas que estava dando de loops infinitos devido,
a chamamento de telas na função de menu. Coloquei para funcionar também o botão de mute do menu e sua respectiva
textura com animações.;


**23/11/24 - 06:50 - 08:22 - Gabriel:**
Reorganizei as pastas de funções e desenhos por menus, ou seja cada tela tem sua pasta para organizar,
coloquei a tela do gerenciador para rodar já, e fiz o link do menu para ela e dela para o menu. Atualizei a
função leMouse(), que agora só le de fato o mouse, quem coloca o cursor clicavel é as funções de resaltar.
*Fica para o próximo terminar de desenhar o menu (Fundo, textos, etc...);

**23/11/24 - 09:30 - 11:00 - Thiago:**
Criei uma pasta pras funcoes do csv para nao misturar com as de criar o gerenciador, criei o arquivo banco.csv
em um lugar solto dentro da mentes-brilhantes mas fora de qualquer outra pasta, da pra mudar dps sla.


**23/11/24 - 12:00 - 16:40 - Gabriel, Thiago e Gustavo:**
Colocamos as pastas para trabalhar com os structs e arquivos, ajustes das funções de botão, criação do arquivo,
colocamos o backgrounddo menu.
*Proximas etapas, mexer com os arquivos csv e binario, além de fazer o gerenciador*;


**23/11/24 - 17:30 - 19:20 - Gabriel:**
Começei a fazer as sub_telas do gerenciador, cada parte de controle tera uma função de desenho que complementa essa
tela, além disso fiz os testes com arquivo CSV deixandoa função de leitura e alocação desses dados no struct cartas
já pronto começar tudo, *A struct cartas e o tamanho dele serão passados via ref. para o gerenciador pois são declarados na main* .;


**24/11/24 - 07:00 - 09:12 - Gabriel:**
Coloquei na main para checar se o arquivo binario exite na pasta, se existir, carrega os conteudos dele, se não, cria
ele e carrega os conteudos pelo CSV, se nao tiver nenhum o prorgama fecha, além disso, se o usuario sair ou
fechar a tela, os dados de cartas são salvos no arquivo binario para serem usados nas proximas vezes que o usuario
abrir o jogo. Ademais conclui a parte do botoa listar n o gerenciador, os botoes dessa seção agora estao todos ok.
*Para o proximo fica começar a desenhar essa tela, botoes de passar as cartas, o contador de carta, passar a struct*
*cartas para a função de comando do gerenciado, e tambem fazer a arte da frente da carta, além de fazer esses*
*sistemas funcionarem com as interações do usuario*.;


**25/11/24  - 22:30 - 23:20 - Gabriel:**
Identifiquei os problemas ocorridos no linux, botão invisivel do menu deve ser passsado por referencia para o desenho
já a parte de não compilar, são bibliotecas nescessárias que estão faltando, é só baixar antes de compilar.;


**26/11/24 - 21:00 - 23:21 - Gabriel, Thiago e Gustavo:**
Fizemos o desenho das setas do gerenciador, também o design da frente da carta e começamos os testes com o sanduiche
de desenhos, além de um teste preliminar de memória RAM. Além disso, teste de comportamentos e debate sobre o, 
ambiente linux.;


**28/11/24 - 01:00 - 04:33 - Gabriel:**
Adicionei o README ao projeto, além de colocar no github a primeira leva de arquivos. No jogo coloquei as funções
que desenham cartas, no desenho geral para usar em outros escopos, além disso, colquei as setas e o sistema de
contagem das cartas para funcionar, adicionei ainda as diretivas de proteção das cartas, principalmente compilar
o vetor de cartas para um vetor cartas_exibicao pois essas que serão realmente exibidas, dado que há ainda
a função de pesquisa que restringe o total_cartas. Além de colocar uam função de cor especial para super trunfo.;


**03/12/24 - 20:20 - 22:10 - Gabriel:**
Centralizei as funções de saida em uma só, checarSaida(), ela já faz o fluxo de saida, colocando o menu em 10 funcionar,
além disso, fiz uma alteração no redimensionador, colocando em uma função geral, afinal ela é usada em todas as partes
também, coloquei ainda o exportar csv para funcionar, ele exporta as cartas para o arquivo Cartas.csv na raiz do jogo
*Quanto antes fica a parte de excluir e a respectiva função que ajusatará as posições no vetor de cartas, além disso*
*Colocar para rodar o sistema de primeira entrada do game, com um pdf explicativo, e tambem otimizar partes das funções*.;


**04/12/24 - 07:40 - 08:35 - Gabriel:**
Coloquei a função que abre o pdf na primeira abertura do jogo, ainda coloquei uam tela secundária, que é aberta em 
casos de erros, ela exibe os erros para o usuário e finaliza o programa, ela esta na funções de desenho geral.;


**07/12/24 - 14:30 - 18:30 - Thiago:**
Criei um struct para os RadioButtons(botoes circulares que apenas um esta selecionado por vez).
Criei uma funcao pra desenhar os radiobuttons e para deixar eles realçados e para checar qual foi clicado e desativar os outros.
Baixei a Raygui para saber como e o jeito certo de fazer as coisas mais pra frente e nao foi tao legal assim.
comecei a fazer as textboxes pra comecar ja criei o struct. Precisando criar uma funcao para ler o teclado e retornar,
uma string alocada diinamicamente. Dei uma olhada e a o codigo pra text box deles tem 300 linhas.;


**08/12/24 - 17:50 - 18:00 - Thiago:**
Arrumei o programa que tinha corrompido na troca pelo servidor.;


**08/12/24 - 17:50 - 20:35 - Thiago:**
Mechi com o radio button e fiz ele funcionar, agora é integrar com a caixa de texto.;


**11/12/24 - 00:00 - 01:00 - Gabriel:**
Fiz o sistema de textos funcionar junto com os radios buttons, além disso, dei uma reorganizada nessa parte de extrutura
Mas percebi que precisamos extruturar e mecher no fluxograma principal afim de deixar o mais leve e organizado possivel.;


**12/12/24 - 22:00 - 00:32 - Gabriel:**
Fiz os checks e saidas de erros do adicionar, funções de verificação sanatização e cópia.;


**13/12/24 - 15:30 - 20:00 - Gabriel, Gustavo e Thiago:**
Achamos os erros de passagem que corompião o vetor de structs, além de colocar para funcionar 100% o adicionar e remover,
começamos também a definir como fazer o editar e pesquisar, que são as ultimas para a primeira entrega.;


**14/12/24 - 4:00 - 18:00 - Gabriel:**
Fiz o editar, nos mesmos moldes do adicionar, usando até, os mesmos campos, logo, podemos remover o sistema de grupos
que não será usado.;


**14/12/24 - 20:30 - 23:00 - Gustavo e Thiago:**
Fizemos um tipo de botão checkbox para usar se é supertrunfo.;


**15/12/24 - 07:40 - 08:20 - Gabriel:**
Fiz a interligação entre o checkbox do supertrunfo para as funções que salvam o conteudo, agora por fim isso esta
funcionando, *proximos passos é fazer os alertas da editar, inverter o hexadecimal e pensar nas regras*.;


**15/12/24 - 18:10 - 19:18 - Gabreil:**
Realizei aluns ajustes no editar, ele agora tem os alertas de erro, podendo-se editar campo por campo, separadamente,
sem a nescessidade de todos estarem preenchidos, e também inverti para o correto de letras e numeros.
*Agora o importante seria começar o pesquisar e colocar algumas regras para o adicionar, como excluir a possibilidade*
*do usuario colocar 2 supertrunfos no mesmo deck, ou outros detalhes*.;


**16/12/24 - 22:40 -  23:38 - Gabriel:**
Regras de filtragem no editar e adicionar colocadas, o usuário nos 3 campos de "poder" só pode colocar valores <100,
e na idade <999, além disso, ele checa se há um supertrunfo no baralho, não deixando ter dois! Juntei as funções de 
resaltar botoes, nulos e invisieis em uma só. Começei a tambem a mecher no pesquisar, colocando para renderizar
uma base parecida com a od adicionar.; *O quanto antes começar a fazer a parte de controle do pesquisar*.;


**17/12/24 - 22:40 - 23:58 - Gabriel:**
Começei a colocar as coisas do pesquisar em ordem, as caixas multiplas e seus controles juntos, além de uma 
logica de subcaixas para saber qual das duas esta ativada no momento, além de ter dado uma ajeitada nuns
detalhes para preparar terreno para a função de controle do pesquisar.;


**18/12/24 - 15:15 - 16:35 - Gabriel, Thiago e Gustavo:**
Tentamos sem muito sucesso fazer funcionar no linux, segundo o professor, o problema é conflito com a raylib
4.2 dos computadores da faculdade, e portanto, funcionará apenas em windows até essa correção, além do mais o
professor deu algumas dicas *Colocar uma pasta de src para os .c e na include os .h, além de remover o*
*dependencias.h, e em cada trecho incluir o nescessário*.;


**18/12/24 - 23:30 - 01:00 - Gabriel:**
Fiz a parte inicial da função que processa os dados da pesquisar, agora ela manda o vetor e quantidade
para o dedenho relacionado à essa pesquisa, e se não houver correspondencias, manda uma pseudo carta 
que tem um txt falando isso para o usuário. Agora é colocar o resto da checagem nessa função e otimiza-la.;


**19/12/24 - 21:00 - 23:30 - Gabriel, Gustavo e Thiago:**
Arrumamos o banco de dados, as imagens, removemos os guard de include e colocamos o include direto normal
Adicionei o return; onde falatava nas funções void, dimunui tamnho de vetores que estavam maiores que o necessario
Começei a padronizar o modo de indentação e uma leve começada no PDF de instruções.;


**20/12/24 - 13:00 - 14:40 - Gabriel e Thiago:**
Terminamos o pesquisar, adicionando todos os campos, as regras de saida e o super-trunfo, ficou de 
ótima sugestão do professor usar strstr() para checar o txt de entrada, assim buscando partes de 
trechos no pesquisando.;


**20/12/2024 - 21:00 - 23:42 - Gabriel, Thiago e Gustavo:**
Passamos esses ultimos momentos, otimizando, organizando e tentando corrigir todos os problemas.
Erros ainda permanecem no realoc do adicionar cartas. *Todos os problemas serão sanados o quanto*
*antes para o iniciar as outras partes*.;