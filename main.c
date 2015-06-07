/*
Este eh um programa que simula um processador MIPS em C
Primeiro faremos um PARSE

autores:
Dalton Lima - sacinopatinete@gmail.com
Stephany ?
Victor ?
Tadeu ?
Lucas Pinheiro - pinheiro.lucasaugusto@gmail.com

*/

#include <stdio.h>
#include <string.h>  //strcpy()
#include "mips.h"
#include "filemanager.h"
#define BUFFER_SIZE 129   //line buffer max size


int main () 
{
	unsigned long totalLines = 0;
	FILE *file;
	
	printf("MIPS Parser!\n" );

instructionR addFunction; //instanciando um struct do tipo R

strcpy (addFunction.opcode,"123456");	
strcpy (addFunction.rs,"54321");
strcpy (addFunction.rt,"12345");
strcpy (addFunction.rd,"99999");
strcpy (addFunction.shamt,"00000");
strcpy (addFunction.funct,"666666");
strcpy (addFunction.end, "\0");

//imprime o struct do primeiro elemento, ate encontrar o 'terminator'
printf("\n\nTeste de impressao do Struct addFunction:\n");
printf("%s", addFunction.opcode);

//conta linha do binary1.txt
totalLines = countLine ();
printf("\nNumero de linhas em binary1.txt : %lu \n", totalLines);


char instructionName[6];  // guarda um nome de instrucao. Ex: "add", "sltu". Os casos maiores sao "addiu" + terminator = 6 espacos

file = fopen(".\\teste\\assembly1.txt", "r");
	if (!file)
	{
		printf("\nerro ao abrir arquivo!\n");
	}
	else
	{
		printf("\narquivo aberto com sucesso!\n");
		while (fgets (inputLine, 129, file) ) 
		{	
			puts (inputLine);				// inputLine contem a linha a ser trabalhada"
			strcpy (instructionName, getNameAssembly(inputLine) );  //extrai a primeira palavra e copia em instructionName
			//puts (instructionName);
			
			ripDataAssembly(inputLine);
			puts(outputLine);			// imprime na tela a saida					
		}
	}
	
//	addToBinary(inputLine);
	
	
fclose(file);

/*
file = fopen(".\\teste\\binary1.txt", "r");
	if (!file)
	{
		printf("\nerro ao abrir arquivo!\n");
	}
	else
	{
		printf("\narquivo aberto com sucesso!\n");
		while (fgets (inputLine, 129, file) ) 
		{
			puts (inputLine);
		}
	}
	
fclose(file);
*/

// teste da nova funcao isNumeric - apagarei no proximo commit
	
	int teste;
	char alf1 = 'a';
	char alf2 = '0' ;
	teste = isNumeric (alf1);
	printf("%d", teste); // esperamos 0
	teste = isNumeric (alf2);
	printf("%d", teste); // esperamos 1

return 0;
}