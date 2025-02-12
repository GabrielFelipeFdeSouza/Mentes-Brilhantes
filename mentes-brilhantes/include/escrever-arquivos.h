#ifndef ESCREVER_ARQUIVO_H

#define ESCREVER_ARQUIVO_H

#include "raylib.h"
void salvarDados(const char *nomeArquivo);
int exportarCsv();
void iniciarArquivoLog();
void escreverLog(char *texto);
#endif //ESCREVER_ARQUIVO_H