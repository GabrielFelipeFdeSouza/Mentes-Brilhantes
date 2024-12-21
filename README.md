# 🎮 **Projeto Mentes Brilhantes**  

### Projeto para a disciplina de *Fundamentos de Programação 2*  
#### Professor Orientador: Muriel de Souza Godoi  
#### Universidade Tecnológica Federal do Paraná (UTFPR) - Campus Apucarana  

# 🧰 **AVISO**  

### Por conta da incompatibilidade da raylib, problemas podem surgir no linux, para mais detalhes olhar o arquivo *details.md*  

---

## 👨‍🎓 **Alunos:**  
- **Gabriel Felipe Ferdinandi de Souza;**  
- **Gustavo Ferreira da Fonseca;**  
- **Thiago André Mattos Málaga;**  

---

## 📋 Informações:  
**Mentes Brilhantes** é um jogo do estilo de *Super Trunfo* desenvolvido como projeto acadêmico, requesito parcial de avaliação da disciplina. Seu tema remete foco em personagens que envolvem mentes brilhantes de diferentes áreas do conhecimento.  

---

## 🔧 Compilação:  
Instruções detalhadas de como compilar o jogo estão nesta seção!

### Ambiente Windows:
Para esse abiente de execução siga os passos abaixo:
1. Baixe o repositório Mentes Brilhantes, [git clone https://github.com/usuario/projeto.git](https://github.com/GabrielFelipeFdeSouza/super-trunfo);

2. Baixe o compilador (se ainda não possuir) *MINGW-64*, pelo link: https://github.com/skeeto/w64devkit/releases/download/v2.0.0/w64devkit-x64-2.0.0.exe, e execute o arquivo;

3. Coloque o patch Bin do compilador nas variaveis de ambiente do seu Windows, se achar dificuldades o video https://www.youtube.com/watch?v=aducc6-ra90, pode ser útil;

4. Pelo terminal navegue até a pasta do jogo usando "CD" e "DIR", a pasta principal é a que contem o arquvio MAKEFILE, dentro dela siga os próximos passos:

5. Execute o comando
    ```
    make clean 
    ```
    Para limpar os arquivos de compilação e binários do jogo;

6. Execute o comando
    ```
    make
    ```
    Para compilar os arquivos

### Ambiente Linux: 
Para esse abiente de execução siga os passos abaixo:
Por padrão o ambiente *linux* ja vem com o compilador correto instalado, mas há passos a serem seguidos:
1. Baixe o repositório Mentes Brilhantes, [git clone https://github.com/usuario/projeto.git](https://github.com/GabrielFelipeFdeSouza/super-trunfo);

2. Instale as dependencias para as bibliotecas de video e audio, execute o seguinte comando como administrador no terminal:
    ```
    sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
    ```

3. Pelo terminal navegue até a pasta do jogo usando "CD" e "LS", a pasta principal é a que contem o arquvio MAKEFILE, dentro dela siga os próximos passos:

4. Execute o comando
    ```
    make clean 
    ```
    Para limpar os arquivos de compilação e binários do jogo;

5. Execute o comando
    ```
    make
    ```
    Para compilar os arquivos
---

## 🛠️ Requisitos:  
Listagem de dependências e ferramentas necessárias para rodar o jogo:

### Ambiente Windows:
Os requesitos de execução nesse ambiente giram em torno dos próprios requesitos da raylib (Biblioteca gráfica usada):

1. OPEN-GL: Esse é um dos requesitos que a raylib possui, em geral, placas de video mais novas, ou atualizadas já possuem versão compativel para a raylib!

2. DirectX: Para esse ambiente, o directX é nescessário  já que são uma série de api's multitarefas pensadas para jogos!

3. Permissão de Administração para jogar em modo "Multiplayer", pois esse recurso nescessita de acesso a rede e passagem por firewalls. *Pode ocorrer de funcionar sem permisão em alguns casos*.


### Ambiente Linux:
Nesse ambiente os requesitos são parecidos com os do windows, mas há um detalhe adicional:

1. Bibliotecas e api gráfica atualizadas: Em geral, para evitar imcompatibilidade com a raylib, manter esses dois itens sempre atualizados evita esses problemas.

2. Bibliotecas de audio e vídeo: Durante a compilação no *passo 2*, mostramos bibliotecas adicionais nescessárias para compilação do jogo.
---

## 🎮 Como Jogar:  
Explicações e regras do jogo, incluindo dicas e estratégias.

//FUTURO
