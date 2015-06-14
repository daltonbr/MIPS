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

//Global Variables
char inputLine[129];
char outputLine[129];

char opcodeBinary[7];        // G Var for Binary
char rsBinary[6];
char rtBinary[6];
char rdBinary[6];
char shamtBinary[6];
char functBinary[7];

char immediateBinary[17];   // exclusive type I
char addressBinary[27]; 	// exclusive type J

char functionAssembly[6];     // G Var for Assembly
char rsAssembly[4];
char rtAssembly[4];
char rdAssembly[4];
char shamtAssembly[3];      // 2^5 = 32 (max) - 2 caracteres
//char functAssembly[6];

char immediateAssembly[6];   // 2^16 = 65538 (max) - 5 caracteres
char addressAssembly[26]; 	// definimos address com 

// fim da declaracao de Global Variables

void printPointer(char *string, int length);

int main () 
{
	unsigned long totalLines = 0;
	FILE *file;
	
	printf("MIPS Parser!\n" );

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
			puts (inputLine);				// inputLine contem a linha a ser trabalhada
			strcpy (instructionName, getNameAssembly(inputLine) );  //extrai a primeira palavra e copia em instructionName
						
			ripDataAssembly(inputLine);   // extrai alguns elementos da linha (registros e immediates) e poe em variaveis globais
					
			strcpy (rsBinary, registerToBinary(rsAssembly)); //convertendo assembly to binary (ainda em variaveis globais)
			strcpy (rtBinary, registerToBinary(rtAssembly));
			strcpy (rdBinary, registerToBinary(rdAssembly));
									
			filterInstruction(instructionName);   //filtra de acordo com cada instruction (encaminha para outra subfuncao)					
			puts(outputLine);			// imprime na tela a saida
		}
	}	
	
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

return 0;
}