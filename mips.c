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

// fim da declaracao de Global Variables

// simples funcao pra limpar a tela
void clearScreen()
{
	system("cls");
}

int main () 
{
	char opcao = ' ';
	instruction instructionMemory[6] = {
		{0,"10001101000010100000000000000100"}, //lw $t0,4($t2)
		{1,"00100001010010110000000000000100"}, //addi $t2, $t3, 4
		{2,"00000001010010000100100000100000"}, //add $t0, $t1, $t2
		{3,"00010001000010011111111111111011"}, //beq $t0, $t1, loop (+1 linha)
		{4,"00100001010010110000000000000100"}, //addi $t2, $t3, 4
		{5,"10101101000010010000000000001000"}  //loop: sw $t0, 8($t1)
    };
	
	data dataMemory[5] = {
		{0,"00000000111111110000000011111111"},
		{1,"22222222333333332222222233333333"},
		{2,"44444444555555554444444455555555"},
		{3,"66666666777777776666666677777777"},
		{4,"88888888999999998888888899999999"}
	};

	registers registerFile[5] = {  //32 registradores, por enquanto 5 pra testar
		{"00000","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}, //0
		{"00001","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"}, //1
		{"00010","cccccccccccccccccccccccccccccccc"}, //2
		{"00011","dddddddddddddddddddddddddddddddd"}, //3
		{"00100","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"}  //4
	};

	clearScreen();
	printf("MIPS!\n" );

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
	
		printf("\nDigite qualquer tecla pra continuar...");
		getch();
		clearScreen();
		//scanf(" %c", &opcao);
	}

return 0;
}
