#include "esteganografia.h"

int esconder(){
    char img[MAX], img_out[MAX], txt[MAX];
	FILE *fimg, *ftxt, *fimg_out;
    int size_img, size_txt, i;
    char ch;

    printf("Digite o nome da imagem que voce deseja esconder o texto (.bmp): ");
    scanf("%[^\n]%*c", img);

	if((fimg = fopen(img, "r+")) == NULL){
		printf("\n\tImagem %s nao encontrada.\nCancelando operacao\n", img);
        Continue();
		return 0;
	}

	size_img = size_of_image(fimg);

    printf("\nDigite o nome da sua imagem final com o texto escondido (.bmp): ");
    scanf("%[^\n]%*c", img_out);

	fimg_out = fopen(img_out, "w+");
	if ((fimg_out = fopen(img_out, "w+")) == NULL){
		printf("\n\tNao foi possivel criar a imagem %s.\nCancelando operacao\n", img_out);
        Continue();
		return 0;
	}

    printf("\nDigite o nome do arquivo de texto para armazenar sua mensagem (.txt): ");
    scanf("%[^\n]%*c", txt);

	if((ftxt = fopen(txt, "w+")) == NULL){
        printf("\n\tNao foi possivel criar o arquivo %s.\nCancelando operacao\n", txt);
        Continue();
        return 0;
    }

    clear_screen();

    Pilha pilha = cria_pilha();

	printf("Insira o texto que deseja esconder: ");

    while((ch = getchar()) != '\n'){
        push(&pilha, ch);
    }

    exibirPilha(&pilha); //imprime pilha

	secret_text(ftxt, &pilha);

	size_txt = secret_text_size(ftxt);

	if(size_img < size_txt){
		printf("\n\tO tamanho do texto é muito grande para essa imagem!\n");
        Continue();
		return 0;
	}

	rewind(fimg);
    copia_inicio(fimg, fimg_out);

	num_encriptar(size_txt,fimg,fimg_out);
	inserir_texto(fimg,ftxt,fimg_out);

	fclose(fimg);	
	fclose(ftxt);
	fclose(fimg_out);

	return 0;
}

int size_of_image(FILE *fimg){
	int width, height, size;

	fseek(fimg, 0x12, SEEK_SET);	
	fread(&width, sizeof(int), 1, fimg);
	fread(&height, sizeof(int), 1, fimg);
	fseek(fimg, 0L, SEEK_SET);

    size = (width * height * 3) / 8;

	return size;
}

void secret_text(FILE *ftxt, Pilha *pilha){
	
    Pilha aux = cria_pilha();
    char ch;

    fputs(pilha->texto, ftxt);	
}

int secret_text_size(FILE *ftxt){
	int size_txt;
	fseek(ftxt, 0L, SEEK_END);
	size_txt = ftell(ftxt);
	fseek(ftxt, 0L, SEEK_SET);
	return size_txt;
}

void copia_inicio(FILE *fimg, FILE *fimg_out){
    int i;
	char tmp;
	
    for(i = 0; i < 54; i++){
		tmp = fgetc(fimg);
		fputc(tmp,fimg_out);
	}
}

void num_encriptar(int num,FILE *fimg, FILE *fimg_out){

	char arq_buff;	
	int i, j = 0;
	int bit_msg;

	for(i = 1; i <= 8; i++){
		
        arq_buff = fgetc(fimg);

		int file_byte_lsb = (arq_buff & 1);

		bit_msg = get_bit(num, i);

		if(file_byte_lsb == bit_msg)
			fputc(arq_buff, fimg_out);
		else{
			if(file_byte_lsb == 0)
				arq_buff = (arq_buff | 1);
			else
				arq_buff = (arq_buff ^ 1);

			fputc(arq_buff, fimg_out);
		}
	}
}

void inserir_texto(FILE *fimg, FILE *ftxt, FILE *fimg_out){
	char arq_buff = 0, txt_buff = 0, ch;
	int i;
	int bit_msg;
	
    while((txt_buff = fgetc(ftxt)) != EOF){
		for(i = 1; i <= 8; i++)
		{
			arq_buff = fgetc(fimg);

			int file_byte_lsb = (arq_buff & 1);

			bit_msg = get_bit(txt_buff, i);

			if(file_byte_lsb == bit_msg)
			{
				fputc(arq_buff, fimg_out);
			}
			else
			{
				if(file_byte_lsb == 0)
					arq_buff = (arq_buff | 1);
				else
					arq_buff = (arq_buff ^ 1);

				fputc(arq_buff, fimg_out);
			}
		}
	}

	while(!feof(fimg)){
		char tmp_cpy = fgetc(fimg);
		fputc(tmp_cpy,fimg_out);
	}

	if(txt_buff == EOF){
		printf("\n\tMensagem inserida com sucesso!\n");
        Continue();
    }else{
        printf("\n\tFalha ao inserir mensagem!\n");
        Continue();
    }
}

int get_bit(char byte, int bit)
{
	return ((byte >> 8 - bit) & 1);
}


