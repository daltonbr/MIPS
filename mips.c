/*
Esta eh a segunda parte do trabalho parte da discplina Arquitetura 
de Computadores
Este eh um programa que simula um processador MIPS em C
Executaremos algumas instrucoes predefinidas

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
#include "mips2.h"
//#include "filemanager.h"

//#define INSTRUCTION_LENGTH = 6
static const int INSTRUCTION_LENGTH = 6;

//Global Variables
char inputLine[33];

char opcodeBinary[7];        
char rsBinary[6];
char rtBinary[6];
char rdBinary[6];
char shamtBinary[6];
char functBinary[7];
char immediateBinary[17];   // exclusive type I
char addressBinary[27]; 	// exclusive type J

char instructionAssembly[6];     // G Var for Assembly

int PC = 0;         		// Program Counter

struct instruction {
	int instructionAddress;
	char instructionLine[33];
};
typedef struct instruction instruction;

struct registers {
	char RegisterNumber[6]; // identficador de cada um dos 32 registro
	char registerData[33];  // 32 bits de dados contidos em cada registrador
};
typedef struct registers registers;

struct data {
	int dataAddress;   //"linhas" ou endereco dos nossos dados da memoria 
	char DataLine[33]; // dados contidos em uma "linha" ou endereco
};
typedef struct data data;

instruction instructionMemory[6] = {
	{ 0,"10001101000010010000000000000100" }, //lw $t0,4($t1)
	{ 1,"00100001001000000000000000001000" }, //addi $t1,$zero,8
	{ 2,"00000001001010100100000000100000" }, //add $t2,$t0,$t1
	{ 3,"00010001010010110000000000000001" }, //beq $t2,$t3,loop (+0 linhas)
	{ 4,"00100001011000000000000000000000" }, //addi $t3,$zero,0
	{ 5,"10101101011010010000000000000100" }  //loop: sw $t3,4($t1)
};

data dataMemory[5] = {
	{ 0,"00000000000000000000000000000000" },  // 0
	{ 1,"00000000000000000000000000000000" },  // 1
	{ 2,"00000000000000000000000000001010" },  // 2
	{ 3,"00000000000000000000000000000000" },  // 3
	{ 4,"00000000000000000000000000000000" }   // 4
};

registers registerFile[32] = {  //32 registradores, por enquanto 5 pra testar
	{ "00000","00000000000000000000000000000000" }, //0  zero
	{ "00001","00000000000000000000000000000000" }, //1  at
	{ "00010","00000000000000000000000000000000" }, //2  v0
	{ "00011","00000000000000000000000000000000" }, //3  v1
	{ "00100","00000000000000000000000000000000" }, //4  a0
	{ "00101","00000000000000000000000000000000" }, //5  a1
	{ "00110","00000000000000000000000000000000" }, //6  a2
	{ "00111","00000000000000000000000000000000" }, //7  a3
	{ "01000","00000000000000000000000000000000" }, //8  t0 = 0
	{ "01001","00000000000000000000000000000100" }, //9  t1 = 4
	{ "01010","00000000000000000000000000000000" }, //10 t2 = 0 
	{ "01011","00000000000000000000000000010010" }, //11 t3 = 18
	{ "01100","00000000000000000000000000000000" }, //12 t4
	{ "01101","00000000000000000000000000000000" }, //13 t5
	{ "01110","00000000000000000000000000000000" }, //14 t6
	{ "01111","00000000000000000000000000000000" }, //15 t7
	{ "10000","00000000000000000000000000000000" }, //16 s0
	{ "10001","00000000000000000000000000000000" }, //17 s1 
	{ "10010","00000000000000000000000000000000" }, //18 s2 
	{ "10011","00000000000000000000000000000000" }, //19 s3
	{ "10100","00000000000000000000000000000000" }, //20 s4
	{ "10101","00000000000000000000000000000000" }, //21 s5
	{ "10110","00000000000000000000000000000000" }, //22 s6
	{ "10111","00000000000000000000000000000000" }, //23 s7
	{ "11000","00000000000000000000000000000000" }, //24 t8
	{ "11001","00000000000000000000000000000000" }, //25 t9
	{ "11010","00000000000000000000000000000000" }, //26 k0
	{ "11011","00000000000000000000000000000000" }, //27 k1
	{ "11100","00000000000000000000000000000000" }, //28 gp
	{ "11101","00000000000000000000000000000000" }, //29 sp
	{ "11110","00000000000000000000000000000000" }, //30 fp
	{ "11111","00000000000000000000000000000000" }  //31 ra
};


// fim da declaracao de Global Variables

// simples funcao pra limpar a tela
void clearScreen()
{
	system("cls");
}

void printRegisters()
{	
	printf("\nRegistradores:\n"); //8 a 11
	int i;
	for (i = 8; i < 12; i++)
	{
		printf("$t%d : ", i-8);  // bela gambiarra hein! Quando ver sera tarde ehehe!
		puts((registerFile[i]).RegisterNumber);
		printf("Dados: ");puts((registerFile[i]).registerData);
	}
}

void printDataMemory()
{
	printf("\nDataMemory:\n"); //0 a 4
	int i;
	for (i = 0; i < 5; i++)
	{
		printf("Posicao: %d - Dados: ", (dataMemory[i]).dataAddress);
		puts((dataMemory[i]).DataLine);
	}
}


int main () 
{
	char opcao = ' ';

	clearScreen();
	// Trabalharemos somente com binarios

	inputLine[0] = '\0';  // zera a linha de entrada
	int i;
	
	for ( i = 0 ; i < INSTRUCTION_LENGTH; i++ )  //efetua um ciclo, ate o fim das instrucoes
	{
		//printf("\nOpcao: %c", opcao);

		strcpy(inputLine, instructionMemory[i].instructionLine); //copia a instrucao para um buffer temporario

		printf("\nInstrucao %d:\n", instructionMemory[i].instructionAddress);  //imprime o indice da instrucao
		puts (inputLine);			// inputLine contem a instrucao a ser trabalhada
	
		getOpcodeBinary(inputLine);  // ripa o OpCode
		printf("\nOpcode: "); puts(opcodeBinary);
		ripDataBinary(opcodeBinary); // ripa o restante dos dados
					
		printf("RS:");
		puts(rsBinary);
		printf("RT:");
		puts(rtBinary);
		printf("RD:");
		puts(rdBinary);
		printf("Shamt:");
		puts(shamtBinary);
		printf("Funct:");
		puts(functBinary);
		printf("immed:");
		puts(immediateBinary);
		printf("Address:");
		puts(addressBinary);
		
		printDataMemory(); //imprime estado da Memoria
		printRegisters();  //imprime estado dos registradores

		printf("\nDigite qualquer tecla pra continuar...");
		getch();
		clearScreen();


		//scanf(" %c", &opcao);


	}

return 0;
}
