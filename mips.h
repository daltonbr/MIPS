#ifndef MIPS
#define MIPS

// Header that defines registers, functions and constants for a MIPS processor
//mips.h

// Instruction R
typedef struct {
	char opcode[6];
	char rs[5];
	char rt[5];
	char rd[5];
	char shamt[5];
	char funct[6];
	char end[1];
} instructionR;

// Instruction I
typedef struct {
	char opcode[6];
	char rs[5];
	char rt[5];
	char immediate[16];
	char end[1];
} instructionI;

// Instruction J
typedef struct {
	char opcode[6];
	char immediate[26];
	char end[1];
} instructionJ;

#define Szero 00000   // em 5 bits
#define Ss0 10000  // 16
#define Ss1 10001  // 17
#define Ss2 10010  // 18
#define Ss3 10011  // 19
#define Ss4 10100  // 20
#define Ss5 10101  // 21


// opcode + funct em binary
#define add 000000100000 // 0/20[hex] - criar um struct com 2 pedacos de 6 bits?
#define sub 000000100010 // 0/22

//soma binaria - desconsidera carry - nao verifica inputs
int xor(int a, int b)
{
	if ( a==b )
	{
		return 0;
	}
	else
	{
		return a + b;
	}
}


//Core Instruction Set (tipo + 6bits)

/*
// R Format Instructions - 12 types (Tipo + 6 bits Funct) (opcode fixo 000000)
add = R100000 	// 0/20
addu = R100001 	// 0/21
and = R100100 	// 0/24
jr = R001000	// 0/08
nor = R100111 	// 0/27
or  = R100101 	// 0/25
slt = R101010 	// 0/2a
sltu = R101011	// 0/2b
sll  = R000000	// 0/00
srl  = R000010	// 0/02
sub = R100010 	// 0/22
subu = R100011  // 0/23

// I Format Instructions - 17 types (Tipo + 6 bits opcode)
addi = I001000 		// 8
addiu = I001001		// 9
andi = I001100		// c
beq = I000100 		// 4
bne = I000101		// 5
lbu = I00100100 	// 24 
lhu = I100101 		// 25
ll = I110000		// 30
lui = I001111		// f
lw = I100011 		// 23
ori = I001101 		// d
slti = I001010 		// a
sltiu = I001011 	// b  
sb = I101000		// 28
sc = I111000		// 38
sh = I101001		// 29
sw = I101011		// 2b

// J Format Instructions - 2 types (tipo + 6 bits opcode) 
j = J000010 		// 2
jal = J000011 		// 3

*/

 // registrador Assembly => Binário
 // dado o assembly do registrador, retorna o binário;
 char getRegisterAB(char reg[4]) 
{
	char regR[4];

	switch(reg)
	{
		//Constante '0'
		case "$zero": regR="00000";
		//Temporário do Assembler
		case "$at": regR="00001"; break;
		//Resultados de Funções
		case "$v0": regR="00010"; break;
		case "$v1": regR="00011"; break;
		//Argumentos
		case "$a0": regR="00100"; break;
		case "$a1": regR="00101"; break;
		case "$a2": regR="00110"; break;
		case "$a3": regR="00111"; break;
		//Temporários
		case "$t0": regR="01000"; break;
		case "$t1": regR="01001"; break;
		case "$t2": regR="01010"; break;
		case "$t3": regR="01011"; break;
		case "$t4": regR="01100"; break;
		case "$t5": regR="01101"; break;
		case "$t6": regR="01110"; break;
		case "$t7": regR="01111"; break;
		//Temporários Salvos
		case "$s0": regR="10000"; break;
		case "$s1": regR="10001"; break;
		case "$s2": regR="10010"; break;
		case "$s3": regR="10011"; break;
		case "$s4": regR="10100"; break;
		case "$s5": regR="10101"; break;
		case "$s6": regR="10110"; break;
		case "$s7": regR="10111"; break;
		//Temporários
		case "$t8": regR="11000"; break;
		case "$t9": regR="11001"; break;
		//Reservado para Kernel
		case "$k0": regR="11010"; break;
		case "$k1": regR="11011"; break;
		//Ponteiro Global
		case "$gp": regR="11100"; break;
		//Ponteiro "Pilha"
		case "$sp": regR="11101"; break;
		//Frame Pointer
		case "$fp": regR="11110"; break;
		//Endereço de retorno
		case "$ra": regR="11111"; break;

		default: /*ERRO:registrador não encontrado,programa abortado*/ break;
	}
	return regR;
}

/* versao do Dalton
// 32 registers (5 bits)
//name	number	use
$zero = 00000 	// 0	constant 0
$at	  = 00001	// 1 	Assemble temporary

$v0 = 00010	// 2 	Function Results and Expression Evaluation
$v1	= 00011	// 3

$a0 = 00100	// 4	Arguments
$a1	= 00101	// 5
$a2 = 00110	// 6
$a3 = 00111	// 7

$t0 = 01000	// 8	Temporaries
$t1	= 01001	// 9
$t2	= 01010	// 10
$t3	= 01011	// 11
$t4	= 01100	// 12
$t5	= 01101	// 13	
$t6	= 01110	// 14
$t7	= 01111	// 15

$s0	= 10000	// 16	Saved Temporaries
$s1	= 10001	// 17
$s2	= 10010	// 18
$s3	= 10011	// 19
$s4	= 10100	// 20
$s5	= 10101	// 21
$s6	= 10110	// 22
$s7	= 10111	// 23

$t8	= 11000	// 24	Temporaries
$t9	= 11001	// 25

$k0	= 11010	// 26	Reserved for OS Kernel
$k1	= 11011	// 27

$gp	= 11100	// 28	Global Pointer
$sp	= 11101	// 29	Stack Pointer
$fp	= 11110	// 30	Frame Pointer

$ra	= 11111	// 31	Return Adress

*/

#endif