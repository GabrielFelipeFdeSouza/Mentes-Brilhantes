//FUNÇÕES DE EXCLUSÃO DE CARTAS:

#ifdef _WIN32 //Testa se o SO é Windows
      #include "../dependencias.h"   
#else
    #include "./dependencias.h"
#endif
void excluirCarta(int id_excluir, Carta **cartas){

    (*cartas)[id_excluir].id = -1; //Usado para mapear onde precisa redimensionar o vetor

    ajustarPosicoes(*cartas);

    *cartas = (Carta*) realloc(*cartas, (quantidade_cartas-1) * sizeof(Carta));

    return;
}

void ajustarPosicoes(Carta *cartas){
    bool ajustar = false; //Usado para saber quando reajustar a posição

    for(int l = 0; l < quantidade_cartas; l++){
        if(cartas[l].id == -1){
            ajustar = true;
        }

        if(ajustar){
            cartas[l] = cartas[l+1]; //Copiando o vetor com contudo para a posição do vetor zerado
            cartas[l].id = l+1; //Reajuste do id
        }
    }

    return;
}