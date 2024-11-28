//FUNCOES PARA ESCREVER NOS ARQUIVOS

#include "../../dependencias.h"


//FUNÇÕES DE .CSV:

//---------------------------------

//ARQUIVOS BINÁRIOS:

void salvarDados(const char *nomeArquivo, Carta *cartas){

    //Abre o arquivo:
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if(!arquivo){
        perror("Erro ao salvar dados");
        return;
    }
    
    if((int) fwrite(&quantidade_cartas, sizeof(int), 1, arquivo) != 1){
        perror("Erro ao salvar dados");
        fclose(arquivo);
        return;
    }
    
    if((int) fwrite(cartas, sizeof(Carta), quantidade_cartas, arquivo) != quantidade_cartas){
        perror("Erro ao salvar dados");
        fclose(arquivo);
        return;
    } //Salva os dados de maneira sequencial 

    fclose(arquivo);
    printf("\nArquivos Salvos!\n");
    return;
}