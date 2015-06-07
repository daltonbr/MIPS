#ifndef MIPS
#define MIPS

//Global Variables
char inputLine[129];
char outputLine[129];

char opcodeBinary[6];
char rsBinary[5];
char rtBinary[5];
char rdBinary[5];
char shamtBinary[5];
char functBinary[6];

char immediateBinary[16];   // exclusive type I
char addressBinary[26]; 	// exclusive type J

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

void concatenateR(char *outputLine)  //generates R type line
{
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, rsBinary);
	strcat (outputLine, rtBinary);
	strcat (outputLine, rdBinary);
	strcat (outputLine, shamtBinary);
	strcat (outputLine, functBinary);
}

void concatenateI(char *outputLine)	//generates I type line
{
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, rsBinary);
	strcat (outputLine, rtBinary);
	strcat (outputLine, immediateBinary);
}

void concatenateJ(char *outputLine)	//generates J type line
{
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, addressBinary);
}

void ripDataAssembly (char *myLine)    //primeira versao - soh extrai registros
{
	char rs[4], rt[4], rd[4];
	char immediate[5];  //soh armazena ate 65536 = 2^16 = 65536 unsigned - maior numero que um immediate U de 16bits pode ter.
	char address[26]; 	// *tamanho aberto a revisao
	char ch;
	int offset = 0;

		do
		{
			offset++;
			ch = myLine[offset]; 
		} while (ch != '$' && ch != '\0');
		
		if ( ch == '$' )
		{
			strncpy(rd,(myLine + offset),3);		//achou o primeiro registro e poe no RD
		}
		
		if ( ch != '\0' ) //ainda nao acabou ?
		{
			do
			{
				offset++;
				ch = myLine[offset];
			} while (ch != '$' && ch != '\0');
			
			if ( ch == '$' ) {
				strncpy(rs,(myLine + offset),3);  //achou o segundo registro e poe no RS
			}
			
			if ( ch != '\0' ) //ainda nao acabou  ?
			{
				do
				{
					offset++;
					ch = myLine[offset];
				} while (ch != '$' && ch != '\0');
				
				if ( ch == '$' ){
					strncpy(rt,(myLine + offset),3);   //achou o terceiro registro e poe no RT			
				}
			}
		}
	
	puts(rs);
	puts(rt);
	puts(rd);
//	strcpy ( rsBinary, registerToBinary(&rs));  // os registros ja estao extraidos, e serao passados em forma de binario 
//	strcpy ( rtBinary, registerToBinary(&rt));  // para as variaveis globais 
//	strcpy ( rdBinary, registerToBinary(&rd));

}

void addToBinary (char *inputLine) //output nas variaveis globais - input precisa ser por referencia?
{
	// extrairemos os registros:
	// ripDataAssembly (inputLine);   // escreve os registros nas globais
	
	//escrevemos nas globais
	strcpy (opcodeBinary,"000000");	 	// fixo para o add
	strcpy (shamtBinary,"00000"); 		// fixo para o add
	strcpy (functBinary,"100000");	 	// fixo para o add
	
	concatenateR(outputLine);   // "empacota" a linha
}

// funcao que retorna os binarios de cada Registro - em caso de erro retorna xxxxx
char *registerToBinary(char *registerAssembly)
{
	char *registerBinary;
	registerBinary = (char *)malloc(6); // tamanho maximo do nome das funcoes, incluindo terminator
	
	if (!(strcmp(registerAssembly,"$zero"))){  		  //retorna 0 se iguais, portanto !0 = verdadeiro
		strcpy(registerBinary,"00000");
	} else if (!(strcmp(registerAssembly,"$at"))) {   	// 1 	Assemble temporary
		strcpy(registerBinary,"00001");		
	} else if (!(strcmp(registerAssembly,"$v0"))) {		// 2 	Function Results and Expression Evaluation
		strcpy(registerBinary,"00010");				
	} else if (!(strcmp(registerAssembly,"$v1"))) {
		strcpy(registerBinary,"00011");			
	} else if (!(strcmp(registerAssembly,"$a0"))) {		// 4	Arguments
		strcpy(registerBinary,"00100");		
	} else if (!(strcmp(registerAssembly,"$a1"))) {
		strcpy(registerBinary,"00101");		
	} else if (!(strcmp(registerAssembly,"$a2"))) {
		strcpy(registerBinary,"00110");		
	} else if (!(strcmp(registerAssembly,"$a3"))) {
		strcpy(registerBinary,"00111");		
	} else if (!(strcmp(registerAssembly,"$t0"))) {		// 8	Temporaries
		strcpy(registerBinary,"01000");		
	} else if (!(strcmp(registerAssembly,"$t1"))) {
		strcpy(registerBinary,"01001");
	} else if (!(strcmp(registerAssembly,"$t2"))) {
		strcpy(registerBinary,"01010");
	} else if (!(strcmp(registerAssembly,"$t3"))) {
		strcpy(registerBinary,"01011");
	} else if (!(strcmp(registerAssembly,"$t4"))) {
		strcpy(registerBinary,"01100");
	} else if (!(strcmp(registerAssembly,"$t5"))) {
		strcpy(registerBinary,"01101");
	} else if (!(strcmp(registerAssembly,"$t6"))) {
		strcpy(registerBinary,"01110");
	} else if (!(strcmp(registerAssembly,"$t7"))) {
		strcpy(registerBinary,"01111");												
	} else if (!(strcmp(registerAssembly,"$s0"))) {		// 16	Saved Temporaries
		strcpy(registerBinary,"10000");		
	} else if (!(strcmp(registerAssembly,"$s1"))) {
		strcpy(registerBinary,"10001");
	} else if (!(strcmp(registerAssembly,"$s2"))) {
		strcpy(registerBinary,"10010");
	} else if (!(strcmp(registerAssembly,"$s3"))) {
		strcpy(registerBinary,"10011");
	} else if (!(strcmp(registerAssembly,"$s4"))) {
		strcpy(registerBinary,"10100");
	} else if (!(strcmp(registerAssembly,"$s5"))) {
		strcpy(registerBinary,"10101");
	} else if (!(strcmp(registerAssembly,"$s6"))) {
		strcpy(registerBinary,"10110");
	} else if (!(strcmp(registerAssembly,"$s7"))) {
		strcpy(registerBinary,"10111");		
	} else if (!(strcmp(registerAssembly,"$t8"))) {		// 24	Temporaries
		strcpy(registerBinary,"11000");
	} else if (!(strcmp(registerAssembly,"$t9"))) {
		strcpy(registerBinary,"11001");			
	} else if (!(strcmp(registerAssembly,"$k0"))) {		// 26	Reserved for OS Kernel
		strcpy(registerBinary,"11010");
	} else if (!(strcmp(registerAssembly,"$k1"))) {
		strcpy(registerBinary,"11011");
	} else if (!(strcmp(registerAssembly,"$gp"))) {
		strcpy(registerBinary,"11100");
	} else if (!(strcmp(registerAssembly,"$sp"))) {
		strcpy(registerBinary,"11101");
	} else if (!(strcmp(registerAssembly,"$fp"))) {
		strcpy(registerBinary,"11110");
	} else if (!(strcmp(registerAssembly,"$ra"))) {
		strcpy(registerBinary,"11111");					
	}
	else {
		strcpy(registerBinary,"xxxxx");    //caso de Erro, nenhum registro compativel encontrado
	}
	
	return (char *)registerBinary;
}

#endif