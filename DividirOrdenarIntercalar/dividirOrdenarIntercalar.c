#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 8

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

void intercalar();
void remover(char n []);

int main(int argc, char**argv)
{
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, parte;
    char nome [20]; //o tamanho definido no array precisa ser igual ou maior que o tamanho do nome dos arquivos que serão guardados nessa variável

	f = fopen("cep.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	parte = qtd/TAMANHO;
    rewind(f);

    //Divide e ordena
    int i;
    for(i=0;i<TAMANHO-1;i++)
    {
        e = (Endereco*) malloc(parte*sizeof(Endereco));
        fread(e,sizeof(Endereco),parte,f);
        //printf("Lido = OK\n");
        qsort(e,parte,sizeof(Endereco),compara);
        //printf("Ordenado = OK\n");
        sprintf(nome,"cep%d.dat",i+1);
        saida = fopen(nome,"wb");
        fwrite(e,sizeof(Endereco),parte,saida);
        fclose(saida);
        //printf("Escrito = OK\n");
        free(e);
    }

    //O resultado da divisão pode não ser exato.
    //Então é necessário fazer um caso expecífico para que os elementos que seriam deixados de fora no caso da divisão ter "resto"
    //sejam inseridos no último arquivo.

    e = (Endereco*) malloc((qtd-(parte*(TAMANHO-1)))*sizeof(Endereco));
	fread(e,sizeof(Endereco),qtd-(parte*(TAMANHO-1)),f) == qtd-(parte*(TAMANHO-1));
    //printf("Lido = OK\n");
	qsort(e,qtd-(parte*(TAMANHO-1)),sizeof(Endereco),compara);
	//printf("Ordenado = OK\n");
	sprintf(nome,"cep%d.dat",TAMANHO);
    saida = fopen(nome,"wb");
	fwrite(e,sizeof(Endereco),qtd-(parte*(TAMANHO-1)),saida);
	fclose(saida);
	//printf("Escrito = OK\n");
	free(e);
	fclose(f);

    intercalar();

    remover(nome);

    return 0;
}

void intercalar()
{
	FILE *a, *b, *saida;
	Endereco ea, eb;
    int arq1 = 1; //indice do primeiro arquivo que será intercalado
    int arq2 = 2; //indice do segundo arquivo que será intercalado
    int arqNovo = TAMANHO+1; //indice do arquivo que será criado, resultado da intercalação
    char nome [20];

    while(arqNovo<(TAMANHO*2))
    {
        sprintf(nome,"cep%d.dat",arq1);
        a = fopen(nome,"rb");
        sprintf(nome,"cep%d.dat",arq2);
        b = fopen(nome,"rb");
        sprintf(nome,"cep%d.dat",arqNovo);
        saida = fopen(nome,"wb");

        fread(&ea,sizeof(Endereco),1,a);
        fread(&eb,sizeof(Endereco),1,b);

        while(!feof(a) && !feof(b))
        {
            if(compara(&ea,&eb)<0)
            {
                fwrite(&ea,sizeof(Endereco),1,saida);
                fread(&ea,sizeof(Endereco),1,a);
            }
            else
            {
                fwrite(&eb,sizeof(Endereco),1,saida);
                fread(&eb,sizeof(Endereco),1,b);
            }
        }

        while(!feof(a))
        {
            fwrite(&ea,sizeof(Endereco),1,saida);
            fread(&ea,sizeof(Endereco),1,a);		
        }
        while(!feof(b))
        {
            fwrite(&eb,sizeof(Endereco),1,saida);
            fread(&eb,sizeof(Endereco),1,b);		
        }

        arq1 = arq1 + 2;
        arq2 = arq2 + 2;
        arqNovo++;
        fclose(a);
        fclose(b);
        fclose(saida);
    }
}

void remover (char nome[])
{
    int i;
    for(i = 1;i<=(TAMANHO*2)-2;i++)
    {
        sprintf(nome,"cep%d.dat",i);
        if(remove(nome)==0)
        {
            printf("%s removido\n",nome);
        }
    }
}