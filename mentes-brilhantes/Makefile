# Verifica o sistema operacional:
ifdef OS
  OS := $(strip $(OS))
else
  OS := $(strip $(shell uname))
endif

# Configuração para Windows ou Unix:
ifeq ($(OS),Windows_NT)
  INCLUDE = -I./include/ -L./libwin
  EXTRA_FLAGS = -Wall -Werror -Wextra -std=c99 -Wno-missing-braces -lraylib -lm -lopengl32 -lgdi32 -lwinmm -lws2_32
  BIN = ./mentes-brilhantes.exe
else
  INCLUDE = -I./
  EXTRA_FLAGS = -Wall -Werror -Wextra -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  BIN = ./mentes-brilhantes
endif

# Encontrar todos os arquivos .c recursivamente:
SRC = $(shell find . -name "*.c")

# Função principal:
all: $(BIN)

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
	@if [ $$? -eq 0 ]; then \
		echo "Compilação concluída com sucesso! Executável: $(BIN)"; \
	else \
		echo "Erro na compilação! Verifique o código e tente novamente."; \
		exit 1; \
	fi

# Comando para rodar o jogo:
run: all
	@echo "------- INICIANDO JOGO --------"
	$(BIN)

# Limpeza de arquivos binários e executáveis:
clean:
	@echo "Removendo arquivos executáveis e binários antigos!"
	$(RM) $(BIN)
	$(RM) -f ./data/cartas.bin
	@echo "Limpeza concluída!"

# Função para depurar:
debug: all
	@echo "Iniciando em modo de depuração..."
	gdb $(BIN)

.PHONY: all run clean debug
