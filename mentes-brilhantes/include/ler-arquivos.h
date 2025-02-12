#ifndef LER_ARQUIVOS_H

#define LER_ARQUIVOS_H

int carregarDadosCSV(const char *nomeArquivo);
bool verificaOuCriaArquivoBinario(const char *nomeArquivo);
int carregarDadosBIN(const char *nomeArquivo);
void lerCartasMultiplayer();
#endif //LER_ARQUIVOS_H