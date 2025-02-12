#Verifica o sistema operacional:
ifdef OS
    OS := $(strip $(OS))
else
    OS := $(strip $(shell uname))
endif

#Configuração para Windows ou Unix:
ifeq ($(OS),Windows_NT)
    INCLUDE = -I./include/ -L./libwin
    EXTRA_FLAGS = -Wall -Werror -Wextra -std=c99 -Wno-missing-braces -lraylib -lm -lopengl32 -lgdi32 -lwinmm -lws2_32 -lwinhttp
    BIN = ./mentes-brilhantes.exe
    RC_FILE = ./resources.rc
    RES_OBJ = resources.o
else
    INCLUDE = -I./include/ -L./lib
    EXTRA_FLAGS = -Wall -Werror -Wextra -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    BIN = ./mentes-brilhantes
endif

#Encontrar todos os arquivos .c recursivamente:
SRC = $(shell find . -name "*.c")

#Função principal:
all: $(BIN)

#Regra principal para criar o executável:
ifeq ($(OS),Windows_NT)
$(BIN): $(SRC) $(RES_OBJ)
	@echo "Compilando o jogo com as seguintes configurações:"
	@echo ""
	@echo "Sistema Operacional: $(OS)"
	@echo ""
	@echo "Arquivos fontes: $(SRC)"
	@echo ""
	@echo "Incluindo: $(INCLUDE)"
	@echo ""
	@echo "Flags: $(EXTRA_FLAGS)"
	@echo ""
	@gcc $(SRC) $(RES_OBJ) -g $(EXTRA_FLAGS) $(INCLUDE) -o $(BIN)
else
$(BIN): $(SRC)
	@echo "Compilando o jogo com as seguintes configurações:"
	@echo ""
	@echo "Sistema Operacional: $(OS)"
	@echo ""
	@echo "Arquivos fontes: $(SRC)"
	@echo ""
	@echo "Incluindo: $(INCLUDE)"
	@echo ""
	@echo "Flags: $(EXTRA_FLAGS)"
	@echo ""
	@gcc $(SRC) -g $(EXTRA_FLAGS) $(INCLUDE) -o $(BIN)
endif

#Regra para compilar o arquivo de recursos no Windows para imagem do exec:
ifeq ($(OS),Windows_NT)
$(RES_OBJ): $(RC_FILE)
	windres $(RC_FILE) -o $(RES_OBJ)
endif

#Comando para rodar o jogo:
run: all
	@echo ""	
	@echo "------- INICIANDO JOGO --------"
	@echo ""
	$(BIN)

#Limpeza de arquivos binarios e executaveis, e objetos do windows:
clean:
	@echo "Removendo arquivos executaveis e binarios antigos!"
	$(RM) $(BIN)
	$(RM) ./data/cartas.bin
	$(RM) ./Cartas.csv
	$(RM) ./data/log.txt
ifeq ($(OS),Windows_NT)
	$(RM) $(RES_OBJ)
endif
	@echo "Limpeza concluida!"

#Função para depurar:
debug: all
	@echo ""
	@echo "Iniciando em modo de depuracao..."
	@echo ""
	gdb $(BIN)

#Exibe uma ajuda para o usuario:
help:
	@echo ""
	@echo "--> HELP MENTES BRILHANTES <--"
	@echo ""
	@echo "Esse jogo é uma criação para o projeto final da disciplina FDCO2A da UTFPR/AP, ministrado pelo professor Muriel de Souza Godói. O jogo foi desenvolvido e programado pelos alunos: Gabriel Felipe F. de Souza, Gustavo Ferreira da Fonseca e Thiago André M. Malaga. Esse jogo esta sob a licença de uso *GPL*."
	@echo ""
	@echo "O jogo se baseia totalmente na linguagem C e para sua execução é ultilizado um arquivo MakeFile que gerencia as criações/limpezas e modificações do jogo. Para compilar o jogo Há alguns requesitos básicos:"
	@echo ""
	@echo "Windows -> Compilador GCC de arquiquetura 64 bits e com ele será instalado os pacotes do MakeFile. Linux -> Por padrão ele já vem com o compilador correto, mas atualizar as bibliotecas graficas é nescessário e não ter conflitos da raylib presente nesse jogo, com uma préviamente baixada."
	@echo ""
	@echo "OPCOES do Make:"
	@echo ""
	@echo "make -> Apenas compila o jogo"
	@echo ""
	@echo "make run -> Compila o jogo para o SO do windows ou linux (AUTOMATICO) e executa o jogo"
	@echo ""
	@echo "make clean -> Remove arquivos executaveis antigos e BINs temporarios"
	@echo ""
	@echo "make exec -> Executa a limpeza do clean, a compilacao do make e o comando run"
	@echo ""
	@echo "make debug -> Compila o jopo para modo de depuracao, ou seja, iniciando o GDB"
	@echo ""


exec:
	make clean;
	make run;

.PHONY: all run clean debug exec help