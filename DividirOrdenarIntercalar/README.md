# Dividir Ordenar Intercalar

dividirOrdenarIntercalar.c --> código em C  
divOrdInt.exe --> código compilado com gcc

Objetivo:  
Tendo um arquivo com centenas de milhares de registros de endereços (cep.dat), deve-se dividir esse <br/>
arquivo em [TAMANHO] aquivos diferentes, ordenar por CEP cada uma dessas arquivos individualmente e <br/>
depois ir intercalando de dois em dois esses arquivos até gerar um arquivo com todos os endereços do <br/>
arquivo original ordenados por CEP. No final do processo todos os arquivos anteriores gerados pela <br/>
intercalação serão excluídos, deixando apenas o último arquivo.

No código o TAMANHO está definido como 8 e o arquivo ordenado se chamará "cep15.dat". <br/>
Mas o valor do TAMANHO pode ser alterado que o código funcionará normalmente. <br/>
E o nome do arquivo ordenado segue o padrão "cep[(TAMANHO*2)-1].dat".


Como usar:  
1- baixar o arquivo "cep.dat" localizado em https://www.dropbox.com/sh/8i46wy3q0rmasu7/AACxLU8MxYm-_IV9UvuagxzIa/aula03?dl=0&preview=cep.dat&subfolder_nav_tracking=1  
2- baixar os arquivos do projeto ("dividirOrdenarIntercalar.c" e "divOrdInt.exe") e coloca-los em uma pasta junto com o "cep.dat"  
3- digitar no terminal os seguintes comandos:  
cd [local dos arquivos]  
./divOrdInt 
