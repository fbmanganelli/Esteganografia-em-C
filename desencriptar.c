#include "esteganografia.h"

int desencriptar(){
    char img[MAX], txt[MAX];
	FILE *fimg, *ftxt;
	
	int size, size1, size_txt;

    printf("Digite o nome da imagem que voce deseja encontrar o texto (.bmp): ");
    scanf("%[^\n]%*c", img);

	if((fimg = fopen(img, "r")) == NULL) {
		printf("\n\tNao foi possivel encontrar a imagem %s\nCancelando operacao\n", img);
        Continue();
		return 0;
	}

	fseek(fimg,54 ,SEEK_SET);
	
    printf("\nDigite o nome do arquivo de texto para armazenar a mensagem (.txt): ");
    scanf("%[^\n]%*c", txt);

	if((ftxt = fopen(txt, "w+")) == NULL) {
		printf("\n\tNao foi possivel abrir o arquivo %s.\nCancelando operacao\n", txt);
        Continue();
		return 0;
	}

    clear_screen();

	num_desencriptar(fimg, &size_txt);
	achar_texto(size_txt, fimg, ftxt);

	printf("\n\tMensagem gravada no arquivo %s\n", txt);
    Continue();

	fclose(fimg);
    fclose(ftxt);
}

void num_desencriptar(FILE *fimg, int *size_txt){
	int file_buff = 0, i;
	int ch, bit_msg;
	
    for (i = 0; i < 8; i++){
		ch = fgetc(fimg);
		bit_msg = (ch & 1);
		
        if(bit_msg)
			file_buff = (file_buff << 1) | 1;
		else
			file_buff = file_buff << 1;
	}

	*size_txt = file_buff;
}

void achar_texto(int size_txt, FILE *fimg, FILE *ftxt){
	int file_buff=0, i, j = 0, k = 0;
	int ch,bit_msg;
	char texto[TAM] = {0};
	
    for (i = 0; i < (size_txt * 8); i++){
		j++;
		ch = fgetc(fimg);
		bit_msg = (ch & 1);
		
        if (bit_msg)
			file_buff = (file_buff << 1) | 1;
		else
			file_buff = file_buff << 1;

		if(j == 8){
			putc(file_buff, ftxt);
			texto[k++] = file_buff;
			j = 0;
			file_buff = 0;
		}
	}
	printf("\n\tA mensagem escondida é: %s\n", texto);
}
