#ifndef STRUCTS_GERAIS_H
#define STRUCTS_GERAIS_H

typedef struct
{
    Rectangle colisao;       // Caixa de colisão
    Color cor_botao;         // Cor
    char texto[100];         // texto
    int tamanho_fonte_texto; // Tamanho de fonte
    Color cor_texto;         // Cor
} Botao;

typedef struct
{
    // retangulo
    Rectangle colisao;
    Color cor_botao;
} BotaoNulo;

typedef struct
{
    int id;              // Id base da carta, usado nos loads das imagens
    bool super_trunfo;   // Sinalizador para Cartas Super-trunfo
    char hexadecimal[5]; // Numeros e letras que ficam no canto da carta
    char imagem[256];    // Char para endereço relativo das imagens da carta
    char nome[51];       // Nome da carta
    unsigned int curiosidade;
    unsigned int criatividade;
    unsigned int inovacao;
    unsigned int idade;
} Carta;

typedef struct
{
    int index;      // pra saber qual
    char texto[20]; // Texto do radio
    Vector2 centro; // centro do circulo do botao de radio
    float raio;     // raio do botao;
    Color cor;      // Cor
    bool estado;    // caso o botao esteja ativado
    int grupo;

} RadioButton;

typedef struct
{
    Rectangle caixa;             // Caixa de colisão
    Color cor_caixa;             // Cor de fundo da caixa
    char texto[128];             // Armazenamento do texto da caixa
    char texto_placeholder[128]; // Placeholder
    Color cor_texto;             // Cor do texto
    bool placeholder;            // Se o placeholder deve ser desenhado
    bool habilitado;             // Se a caixa esta ativa para entradas
    int tamanho;                 // Tamanho do texto da caixa
    int subgrupo;                // Tipo possivel de entrada
    int subcaixa;                // Para ativar a leitura de multiplas caixas de texto
} TextBox;

typedef struct
{
    int index; // pra saber qual
    char texto[20];
    Rectangle quadrado;
    Color cor;
    bool estado; // caso o botao esteja ativado
    int grupo;

} Seletor;

#endif // STRUCTS_GERAIS_H
