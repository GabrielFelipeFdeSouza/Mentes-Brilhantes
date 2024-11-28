# 🎮 **Projeto Mentes Brilhantes**  

### Projeto para a disciplina de *Fundamentos de Programação 2*  
#### Professor Orientador: Muriel de Souza Godoi  
#### Universidade Tecnológica Federal do Paraná (UTFPR) - Campus Apucarana  

---

## 👨‍🎓 **Alunos:**  
- **Gabriel Felipe Ferdinandi de Souza;**  
- **Gustavo Ferreira da Fonsceca;**  
- **Thiago André Mattos Málaga;**  

---

## 📋 Informações:  
**Mentes Brilhantes** é um jogo do estilo de *Super Trunfo* desenvolvido como projeto acadêmico, requesito parcial de avaliação da disciplina. Seu tema remete foco em personagens que envolvem mentes brilhantes de diferentes áreas do conhecimento.  

---

## 🔧 Compilação:  
Instruções detalhadas de como compilar o jogo estão nesta seção!

##Ambiente Windows:
Para esse abiente de execução siga os passos abaixo:
1. Baixe o repositório Mentes Brilhantes, [git clone https://github.com/usuario/projeto.git](https://github.com/GabrielFelipeFdeSouza/super-trunfo);

2. Baixe o compilador (se ainda não possuir) *MINGW-64*, pelo link: https://github.com/skeeto/w64devkit/releases/download/v2.0.0/w64devkit-x64-2.0.0.exe, e execute o arquivo;

3. Coloque o patch Bin do compilador nas variaveis de ambiente do seu Windows, se achar dificuldades o video https://www.youtube.com/watch?v=aducc6-ra90, pode ser útil;

4. Navegue até a pasta do jogo usando "CD" e "DIR", a pasta principal é a que contem o arquvio MAKEFILE, dentro dela siga os próximos passos:

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

##Ambiente Linux: 
Para esse abiente de execução siga os passos abaixo:
Por padrão o ambiente *linux* ja vem com o compilador correto instalado, mas há passos a serem seguidos:
1. Baixe o repositório Mentes Brilhantes, [git clone https://github.com/usuario/projeto.git](https://github.com/GabrielFelipeFdeSouza/super-trunfo);

2. Instale as dependencias para as bibliotecas de video e audio, execute o sefuinte comando como administrador no terminal:
```
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

3. Navegue até a pasta do jogo usando "CD" e "LS", a pasta principal é a que contem o arquvio MAKEFILE, dentro dela siga os próximos passos:

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

---

## 🎮 Como Jogar:  
Explicações e regras do jogo, incluindo dicas e estratégias.
