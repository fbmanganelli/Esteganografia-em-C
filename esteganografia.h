#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100 //tamanho das entradas de arquivo do usuario
#define TAM 100 //tamanho do texto na pilha

//estrutura de pilha
typedef struct pilha{
    int top;
    char texto[TAM];
}Pilha;

//imprime o menu
void menu();

//limpa a tela
void clear_screen();

//inicia encriptacao
int esconder();

//retorna o tamanho da imagem
int size_of_image(FILE *fimg);

//escreve o texto a ser escondido em um arquivo
void secret_text(FILE *ftxt, Pilha *pilha);

//retorna o tamanho do texto no arquivo
int secret_text_size(FILE *ftxt);

//copia os caracteres de controle da imagem
void copia_inicio(FILE *fimg, FILE *fimg_out);

//inicia a pilha
Pilha cria_pilha();

//insere na pilha
void push(Pilha *pilha, char letra);

//retira da pilha
char pop(Pilha *pilha);

//imprime a pilha
void exibirPilha(Pilha *pilha);

//retorna os bit do arquivo de texto
int get_bit(char byte, int bit);

//insere o texto na imagem
void inserir_texto(FILE *fimg, FILE *ftxt, FILE *fimg_out);

//encripta o tamanho do texto
void num_encriptar(int num,FILE *fimg, FILE *fimg_out);

//inicia desencriptacao
int desencriptar();

//encontra o texto escondido
void achar_texto(int size_txt, FILE *fimg, FILE *ftxt);

//desencripta o tamanho do texto
void num_desencriptar(FILE *fimg, int *size_txt);

//funcao de controle para o usuario
void Continue();

//creditos do programa
void creditos();