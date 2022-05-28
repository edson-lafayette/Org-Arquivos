#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
    int leitor;
    int c = 0; //contador
    int inicio;
    int fim;
    int meio;
    int bits;
    int registros;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
		return 1;
	}

	//printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep_ordenado.dat","r");
    fseek(f, 0, SEEK_END);
    bits = ftell(f);
    registros = bits/sizeof(Endereco);
    inicio = 0;
    fim = registros - 1;

	while(inicio <= fim)
	{
        c++;
        meio = (inicio+fim)/2;
        fseek(f,(meio*sizeof(Endereco)), SEEK_SET);
        leitor = fread(&e,sizeof(Endereco),1,f);
        
        if(strncmp(argv[1],e.cep,8) < 0)
		{
            fim = meio - 1;
		}
        
        else if(strncmp(argv[1],e.cep,8)> 0)
		{
            inicio = meio + 1;
		}

        else if(strncmp(argv[1],e.cep,8)==0)
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
        
	}
	printf("Total Lido: %d\n", c);
	fclose(f);
}