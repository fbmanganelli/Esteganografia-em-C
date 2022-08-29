#include "esteganografia.h"

void menu(){
    printf("1 - Esconder mensagem\n");
    printf("2 - Revelar mensagem\n");
    printf("3 - Creditos\n");
    printf("0 - Sair\n");
}

void creditos(){
    printf("Programa feito pelo discente Filipe Brito Manganelli\n");
    Continue();
}

void clear_screen(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}

Pilha cria_pilha(){
    Pilha pi;

    pi.top = 0;
    pi.texto[0] = '\0';

    return pi;
}

void push(Pilha *pilha, char letra){
    pilha->texto[pilha->top] = letra;
    pilha->top++;
    pilha->texto[pilha->top] = '\0';
}

char pop(Pilha *pilha){
    char aux;
    
    pilha->top--;

    aux = pilha->texto[pilha->top];
    
    pilha->texto[pilha->top] = '\0';
    
    return aux;
}

void exibirPilha(Pilha *pilha){
    int i;

    printf("\nMensagem na pilha: ");

    for(i = pilha->top - 1; i >= 0; i--) printf("%c", pilha->texto[i]);

    printf("\n");
}

void Continue(){
    printf("\n\tAperte <Enter> para continuar\n");
    getchar();
}