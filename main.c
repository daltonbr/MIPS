/*
Este eh um programa que simula um processador MIPS em C
Primeiro faremos um PARSE

autores:
Dalton Lima - sacinopatinete@gmail.com
Stefany - stefanylacroux@hotmail.com
Victor - victor_ribeiro.pira@hotmail.com
Tadeu - tadeumartines@yahoo.com.br
Lucas Pinheiro - pinheiro.lucasaugusto@gmail.com

*/

#include <stdio.h>
#include <stdlib.h>
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
struct JumpTable JumpAdressTable[20];

char immediateBinary[17];   // exclusive type I
char addressBinary[27]; 	// exclusive type J

char instructionAssembly[6];     // G Var for Assembly
char rsAssembly[6];
char rtAssembly[6];
char rdAssembly[6];
char shamtAssembly[3];      // 2^5 = 32 (max) - 2 caracteres
//char functAssembly[6];

char immediateAssembly[6];   // 2^16 = 65538 (max) - 5 caracteres
char addressAssembly[27]; 	// we define address with
char labelAssembly[20];    // label for bne and beq functions
int pcAssembly = 0;         // Program Counter Assembly (line number read)

// end of Global Variables declaration
void printPointer(char *string, int length);

int main () 
{
	fillJumpAdressTable();   // scans the input file for Labels and creates a table
		
	unsigned long totalLines = 0;
	FILE *inputFile, *outputFile;
		
	printf("MIPS Parser!\n" );

//conta linha do binary1.txt
totalLines = countLine ();
printf("\nNumber of lines in binary1.txt : %lu \n", totalLines);

char instructionName[6];  // stores an instruction name. Ex: "add", "sltu". The largest cases are "addiu" + terminator = 6 spaces

inputFile = fopen("./assembly.txt", "r");
outputFile = fopen("./outputBinary.txt", "w");
			// "r"	Opens a file for reading. The file must exist.
			// "w"	Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
			// "a"	Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
			// "r+"	Opens a file to update both reading and writing. The file must exist.
			// "w+"	Creates an empty file for both reading and writing.
			// "a+"	Opens a file for reading and appending.
	if (!outputFile)
	{
		printf("\nerror opening writing file!\n");
	}
	else  // write file opened correctly
	{
		if (!inputFile)
		{
			printf("\nerror opening reading file!\n");
		}
		else   // read file opened correctly
		{
			printf("\nAssembly file opened successfully!\n");				
			while (fgets (inputLine, 129, inputFile) ) 
			{	
				printf("\nInput Assembly: ");
				puts (inputLine);				// inputLine contains the line to be worked on
				pcAssembly++;    //global var that counts the Program Counter (Assembly)
				printf("\nLine (pc) = %d \n", pcAssembly);  //prints current line
				
				if ( !isLabel(inputLine) ) // if the line is a NO, the label executes the line, otherwise it increments the PC and goes to the next line		
				{
					strcpy (instructionName, getNameAssembly(inputLine) );  //extract the first word and copy it into instructionName
					ripDataAssembly(inputLine);   // extracts some elements from the line (records and immediates) and puts them in global variables
							
					strcpy (rsBinary, registerToBinary(rsAssembly)); //converting assembly to binary (still in global variables)
					strcpy (rtBinary, registerToBinary(rtAssembly));
					strcpy (rdBinary, registerToBinary(rdAssembly));
											
					filterInstruction(instructionName);   //filters according to each instruction (forwards to another subfunction)			
					printf("\nOutput Binary: ");
					puts(outputLine);			// prints the output on the screen
					fputs(outputLine, outputFile);  // print the line in the output file
					fputs("\n", outputFile);  //    \n
				}
			}
		}	
	}
	
fclose(inputFile);
fclose(outputFile);

//### here the conversation ends Assembly -> Binary and the opposite begins

inputLine[0] = '\0';  // eliminates previous dirt
outputLine[0] = '\0';

inputFile = fopen("./binary.txt", "r");
outputFile = fopen("./outputAssembly.txt", "w");
			
	if (!outputFile)
	{
		printf("\nerror opening writing file!\n");	
	}
	else  // write file opened correctly
	{
		if (!inputFile)
		{
			zf("\nerror opening reading file!\n");
		}
		else   // read file opened correctly
		{
			printf("\nBinary file opened successfully!\n");
			while (fgets (inputLine, 129, inputFile) ) 
			{
				printf("\nBinary Line:");
				puts (inputLine);			// inputLine contains the line to be worked on
				
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
				printf("Instruction:");
				puts(instructionAssembly);
				
				puts(outputLine);			// prints the output on the screen
				fputs(outputLine, outputFile);  // print the line in the output file
				fputs("\n", outputFile);  //    \n  
				
			}
		}
	}
	
fclose(inputFile);
fclose(outputFile);

return 0;
}
