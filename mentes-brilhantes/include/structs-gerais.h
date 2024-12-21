#ifndef STRUCTS_GERAIS_H
#define STRUCTS_GERAIS_H

typedef struct
{
    // retangulo
    Rectangle colisao;
    Color cor_botao;
    // texto
    char texto[100];
    int tamanho_fonte_texto;
    Color cor_texto;
} Botao;

typedef struct
{
    // retangulo
    Rectangle colisao;
    Color cor_botao;
} BotaoNulo;

typedef struct
{
    int id;         //numero da carta pq o gabriel pediu   
    bool super_trunfo;      //checa pra ver se e super
    char hexadecimal[5];    //numeros e letras que ficam no canto da carta kk
    char imagem[256];       //Char para endereço relativo das imagens da carta
    char nome[51];
    unsigned int curiosidade;
    unsigned int criatividade;
    unsigned int inovacao;
    unsigned int idade;
}Carta;

typedef struct
{
    int index;                  //pra saber qual
    char texto[20];
    Vector2 centro;             //centro do circulo do botao de radio
    float raio;                 //raio do botao;
    Color cor;
    bool estado;                 //caso o botao esteja ativado
    int grupo;
    

}RadioButton;

typedef struct
{
    Rectangle caixa;
    Color cor_caixa;
    char texto[128];
    char texto_placeholder[128];
    Color cor_texto;
    bool placeholder;
    bool habilitado;
    int tamanho;
    int subgrupo;
    int subcaixa;
}TextBox;

typedef struct
{
    int index;                  //pra saber qual
    char texto[20];
    Rectangle quadrado;
    Color cor;
    bool estado;                 //caso o botao esteja ativado
    int grupo;
    
}Seletor;


#endif // STRUCTS_GERAIS_H
