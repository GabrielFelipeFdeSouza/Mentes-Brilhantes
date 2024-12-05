//FUNCOES PARA ESCREVER NOS ARQUIVOS

#include "../../dependencias.h"


//FUNÇÕES DE .CSV:

int exportarCsv(Carta cartas[]){
    //Abre o arquivo:
    FILE *arquivo = fopen("./Cartas.csv", "w");
    if(!arquivo){
        perror("Erro ao exportar");
        return 2;
    }

    char super_trunfo[6]; //Usado para escrever se é supertrunfo ou não

    for(int v = 0; v < quantidade_cartas; v++){

        if(cartas[v].super_trunfo){
            strcpy(super_trunfo, "true");
        } else{
            strcpy(super_trunfo, "false");
        } //Formata esse dado para ir ao csv

        //Embora tenha usado o fprint, é uma função bem definida, que tem segurança de uso, além de serem poucas cartas, oque não atrasa o fluxo do game!
        fprintf(arquivo, "%d,%s,%s,%s,%s,%d,%d,%d,%d", cartas[v].id, super_trunfo,cartas[v].hexadecimal, cartas[v].imagem, cartas[v].nome, cartas[v].curiosidade, cartas[v].criatividade, cartas[v].inovacao, cartas[v].idade);
    
        fprintf(arquivo, "\n"); //Espaço entre linhas
    }


    fclose(arquivo);
    printf("\nArquivo Exportado!\n");
    return 1;
}

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


