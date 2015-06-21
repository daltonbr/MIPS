/*
Este eh um programa que simula um processador MIPS em C
Primeiro faremos um PARSE

autores:
Dalton Lima - sacinopatinete@gmail.com
Stephany ?
Victor ?
Tadeu tadeumartines@yahoo.com.br
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

char instructionAssembly[6];     // G Var for Assembly
char rsAssembly[4];
char rtAssembly[4];
char rdAssembly[4];
char shamtAssembly[3];      // 2^5 = 32 (max) - 2 caracteres
//char functAssembly[6];

char immediateAssembly[6];   // 2^16 = 65538 (max) - 5 caracteres
char addressAssembly[26]; 	// definimos address com 
int pcAssembly = 0;         // Program Counter Assembly (numero da linha lida)

// fim da declaracao de Global Variables

void printPointer(char *string, int length);

int main () 
{
	unsigned long totalLines = 0;
	FILE *inputFile, *outputFile;
	
	printf("MIPS Parser!\n" );

//conta linha do binary1.txt
totalLines = countLine ();
printf("\nNumero de linhas em binary1.txt : %lu \n", totalLines);


char instructionName[6];  // guarda um nome de instrucao. Ex: "add", "sltu". Os casos maiores sao "addiu" + terminator = 6 espacos

inputFile = fopen("./teste/assembly1.txt", "r");
outputFile = fopen("./teste/outputBinary.txt", "w");
			// "r"	Opens a file for reading. The file must exist.
			// "w"	Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
			// "a"	Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
			// "r+"	Opens a file to update both reading and writing. The file must exist.
			// "w+"	Creates an empty file for both reading and writing.
			// "a+"	Opens a file for reading and appending.
	if (!outputFile)
	{
		printf("\nerro ao abrir arquivo de escrita!\n");
	}
	else  // arquivo de escrita aberto corretamente
	{
		if (!inputFile)
		{
			printf("\nerro ao abrir arquivo de leitura!\n");
		}
		else   // arquivo de leitura aberto corretamente
		{
			printf("\narquivo Assembly aberto com sucesso!\n");				
			while (fgets (inputLine, 129, inputFile) ) 
			{	
				printf("\nInput Assembly: ");
				puts (inputLine);				// inputLine contem a linha a ser trabalhada
				pcAssembly++;    //var global que conta o Program Counter (Assembly)
				printf("\nLinha (pc) = %d \n", pcAssembly);  //soh imprime a linha atual
				
				if ( !isLabel(inputLine) ) // se a linha eh um NAO eh label executa a linha, senao incrementa o PC e vai pra proxima linha			
				{
					strcpy (instructionName, getNameAssembly(inputLine) );  //extrai a primeira palavra e copia em instructionName
					ripDataAssembly(inputLine);   // extrai alguns elementos da linha (registros e immediates) e poe em variaveis globais
							
					strcpy (rsBinary, registerToBinary(rsAssembly)); //convertendo assembly to binary (ainda em variaveis globais)
					strcpy (rtBinary, registerToBinary(rtAssembly));
					strcpy (rdBinary, registerToBinary(rdAssembly));
											
					filterInstruction(instructionName);   //filtra de acordo com cada instruction (encaminha para outra subfuncao)					
					printf("\nOutput Binary: ");
					puts(outputLine);			// imprime na tela a saida
					fputs(outputLine, outputFile);  // imprime a linha no arquivo de saida
					fputs("\n", outputFile);  //    \n
				}
				
				
			}
		}	
	}
	
fclose(inputFile);
fclose(outputFile);

// ### aqui termina a conversar Ass -> Bin e comeca a contraria

inputLine[0] = '\0';  // zera a sujeira anterior
outputLine[0] = '\0';

inputFile = fopen("./teste/binary1.txt", "r");
outputFile = fopen("./teste/outputAssembly.txt", "w");
			
	if (!outputFile)
	{
		printf("\nerro ao abrir arquivo de escrita!\n");	
	}
	else  // arquivo de escrita aberto corretamente
	{
		if (!inputFile)
		{
			printf("\nerro ao abrir arquivo de leitura!\n");
		}
		else   // arquivo de leitura aberto corretamente
		{
			printf("\narquivo Binario aberto com sucesso!\n");
			while (fgets (inputLine, 129, inputFile) ) 
			{
				printf("\nLinha Binaria:");
				puts (inputLine);			// inputLine contem a linha a ser trabalhada
				
				getOpcodeBinary(inputLine);
				ripDataBinary(opcodeBinary);
			
				printf("RS:");
				puts(rsBinary);
				puts(rsAssembly);
				printf("RT:");
				puts(rtBinary);
				puts(rtAssembly);
				printf("RD:");
				puts(rdBinary);
				puts(rdAssembly);
				printf("Shamt:");
				puts(shamtBinary);
				printf("Funct:");
				puts(functBinary);
				printf("immed:");
				puts(immediateBinary);
				printf("Address:");
				puts(addressBinary);
				printf("Instruction R:");
				puts(instructionAssembly);
				
				puts(outputLine);			// imprime na tela a saida
				fputs(outputLine, outputFile);  // imprime a linha no arquivo de saida
				fputs("\n", outputFile);  //    \n  pula linha se precisar
				
			}
		}
	}
	
fclose(inputFile);
fclose(outputFile);

return 0;
}
