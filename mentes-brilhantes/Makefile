# Verifica o sistema operacional:
ifdef OS
  OS := $(strip $(OS))
else
  OS := $(strip $(shell uname))
endif

#Diretorio do arquivo binário:
PATCH = ./data/cartas.bin

#Inclui os arquivos e flags para compilação em cada S.O:
ifeq ($(OS),Windows_NT)
	INCLUDE = -I./include/ -L./libwin
	EXTRA_FLAGS = -Wall -Werror -Wextra -std=c99 -Wno-missing-braces -lraylib -lm -lopengl32 -lgdi32 -lwinmm -lws2_32
	BIN = ./mentes-brilhantes.exe
else
	INCLUDE=-I./include/ -L./lib
	EXTRA_FLAGS = -Wall -Werror -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 
	BIN = ./mentes-brilhantes
endif

# Encontrar todos os arquivos .c recursivamente em subpastas, excluindo a pasta raylib (exclusão de arquivos da biblioteca):
SRC = $(shell find . -name "*.c" -not -path "./raylib/*")

#Compilação:
all:
	@echo "Compilando..."
	gcc $(SRC) -g $(EXTRA_FLAGS) $(INCLUDE) -o $(BIN)

#Execução:
run:
	@echo "Executando..."
	$(BIN)

#Limpeza:
clean:
	@echo "Limpando arquivos binários e executavel..."
	$(RM) $(BIN)
	$(RM) $(PATCH)
