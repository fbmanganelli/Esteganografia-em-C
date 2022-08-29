#include "esteganografia.h"

int main(){

    int op = 1;
    clear_screen();

    while(op != 0){
        menu();
        scanf("%d%*c", &op);
        
        switch(op){
            case 1:
                clear_screen();
                esconder();
                clear_screen();
                break;

            case 2:
                clear_screen();
                desencriptar();
                clear_screen();
                break;
            case 3:
                clear_screen();
                creditos();
                clear_screen();
            default:
                if(op < 0 || op > 3)
                    printf("\n\tInsira uma opcao valida!\n\n");
                break;
        }
    }

    clear_screen();

    return 0;
}


