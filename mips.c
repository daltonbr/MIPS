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

// buffers de saida
char signExtend[33];
char reg1Out[33];   // saidas dos banco de registradores
char reg2Out[33];
char aluOut[33];    // saida da ALU principal
char memOut[33];	// saida da memoria

// sinais de controle
char regWrite = '0';
char regDst = '0';
char AluSrc = '0';
char AluOp = '0';
char AluZero = '0';
char memRead = '0';
char memWrite = '0';
char memToReg = '0';
char branch = '0';

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
	printf("\n ### Registradores ###\n"); //8 a 11
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
	printf("\n ### DataMemory ###\n"); //1 a 3
	int i;
	for (i = 1; i < 4; i++)
	{
		printf("Posicao: %d - Dados: ", (dataMemory[i]).dataAddress);
		puts((dataMemory[i]).DataLine);
	}
}

void printInstruction()
{
	printf("RS:");	puts(rsBinary);
	printf("RT:");	puts(rtBinary);
	printf("RD:"); 	puts(rdBinary);
	printf("Shamt:"); puts(shamtBinary);
	printf("Funct:"); puts(functBinary);
	printf("immed:"); puts(immediateBinary);
	printf("Address:");	puts(addressBinary);
	printf("SignExtended: "); puts(signExtend);
	printf("AluOut: "); puts(aluOut);
	printf("AluZero: %c", AluZero);
}

void signExtender()
{
	strcpy(signExtend, immediateBinary);
	padZero(signExtend, 32);
}

void alu()
{
	char aluSource2[33];
	char temp1[33];
	char temp2[33];
	int int1, int2, soma;
	AluZero = '0';  // soh pra resetar

	if (AluSrc == '0')
	{
		strcpy(aluSource2, reg2Out);
	}
	else
	{
		strcpy(aluSource2, signExtend);
	}

	if (AluOp == '0') //soma
	{
		int1 = binary32ToChar(reg1Out, temp1);  //converte pra inteiro as entradas
		int2 = binary32ToChar(aluSource2, temp2);
		soma = int1 + int2;  // soma os inteiros
		itoa(soma, temp1, 10);  // converte pra texto
		charTo32Bits(temp1, aluOut);  // converte pra texto binario e ja da a saida
	}
	else // beq - compara igualdade entre os operando
	{
		printf("\nALu em modo igualdade\n");
		printf("Alu1: "); puts(reg1Out);
		printf("Alu2: "); puts(aluSource2);
		if (strcmp(reg1Out, aluSource2)) // retorna 0 qdo iguais 
		{
			AluZero = '0';  // valores diferentes
		}
		else
		{
			AluZero = '1';  // valores iguais, sinal de controle asserted
		}
		printf(" %c", AluZero);
		//puts(reg1Out);
		//puts(aluSource2);
	}
}

void registerOut()
{
	int i;
	for (i = 0; i < 32; i++)
	{
		if (! strcmp(opcodeBinary, "000000") )  //se for instrucao tipo R, beq ou bne...
		{
			if (!strcmp(rsBinary, registerFile[i].RegisterNumber))  //pegamos reg1 do RS
			{
				strcpy(reg1Out, registerFile[i].registerData);
				break;
			}
		}
		else  // tipo I ou J, entao pegamos reg1 do RT
		{
			if (!strcmp(rtBinary, registerFile[i].RegisterNumber))
			{
				strcpy(reg1Out, registerFile[i].registerData);
				break;
			}
		}
	}
	for (i = 0; i < 32; i++)
	{
		if ((!strcmp(opcodeBinary, "000100")) || (!strcmp(opcodeBinary, "000101")))
		{
			if (!strcmp(rtBinary, registerFile[i].RegisterNumber))
			{
				strcpy(reg2Out, registerFile[i].registerData);
				break;
			}
		}
		else
		if (!strcmp(rdBinary, registerFile[i].RegisterNumber))
		{
			strcpy(reg2Out, registerFile[i].registerData);
			break;
		}
	}
	
	if (!strcmp(opcodeBinary, "101011")) // especial para o SW
	{
		for (i = 0; i < 32; i++)
		{
			if (!strcmp(rsBinary, registerFile[i].RegisterNumber))
			{
				strcpy(reg2Out, registerFile[i].registerData);
				break;
			}
		}
	}
	printf("\nReg1Out: "); puts(reg1Out);
	printf("Reg2Out: "); puts(reg2Out);
}

int verifyBranch()
{
	int signExtInteger = atoi(signExtend);

	if (branch == '1' && AluZero == '1')
	{
		PC = PC + signExtInteger;
		printf("\nDebug: Tomando o branch incrementando %d instrucoes\n", signExtInteger);
		//printf("\nDebug: %d\n", PC);
		return signExtInteger;
	}
	else
		return 0;
}

void memoryHandler()
{
	int memoryAddress;
	char temp[33];
	if (memWrite == '1')
	{
		memoryAddress = binary32ToChar(aluOut, temp);
		//memoryAddress = atoi(aluOut);  // converte endereco para decimal inteiro
		printf("Debug: MemoryAddress to be Written %d (integer) / 4 = %d ", memoryAddress, memoryAddress / 4); // endereco onde escrevemos na memoria
		strcpy( dataMemory[memoryAddress/4].DataLine, reg2Out ); //copia os dados na memoria
		printf("\nDados do Registrador 2 a serem escritos: "); puts(reg2Out);
	}

	if (memRead == '1')
	{
		memoryAddress = binary32ToChar(aluOut, temp);
		printf("Debug: MemoryAddress to be Read %d (integer) / 4 = %d ", memoryAddress, memoryAddress/4); // endereco onde leremos da memoria
		strcpy(memOut, dataMemory[memoryAddress/4].DataLine); //copia os dados na memoria
		printf("\nDados a serem lidos da memoria: "); puts(memOut);
	}

}

void writeBack() // no banco de registradores
{
	char writeAddress[6];
	char writeData[33];
	int i;
		
	if (regWrite == '1')   //se formos escrever
	{
		if (regDst == '1') // Define em qual registrador sera escrito
		{   // add
			strcpy(writeAddress, rtBinary);
		}
		else
		{   // addi, lw, sw, beq (os dois ultimos nao fazem Write Back)
			strcpy(writeAddress, rsBinary);
		}

		if (memToReg == '1')  // define de onde vem os dados a serem escritos
		{
			strcpy(writeData, memOut);  // dados vem da saida de memoria
		}
		else
		{
			strcpy(writeData, aluOut);  // dados vem diretamente da Alu
		}

		// escrevendo efetivamente os dados
		for (i = 0; i < 32; i++)
		{
			if  (!strcmp(registerFile[i].RegisterNumber, writeAddress) )
			{
				strcpy(registerFile[i].registerData, writeData);
				break;
			}
		}
	}
}

int main () 
{
	clearScreen();

	printf("\n --== Estados iniciais da Memoria e dos Registradores ==--\n\n");
	printDataMemory(); //  imprime estado da Memoria
	printRegisters();  //  imprime estado dos registradores

	printf("\nDigite qualquer tecla pra continuar...");
	getch();
	clearScreen();

	inputLine[0] = '\0';  // zera a linha de entrada
	int PC;  // nosso Program Counter
	
	for ( PC = 0 ; PC < INSTRUCTION_LENGTH; PC++ )  //efetua um ciclo, ate o fim das instrucoes, o numero de instrucoes eh fixo
	{
		// ### (1o estagio) Instruction Fetch
		strcpy(inputLine, instructionMemory[PC].instructionLine); //copia a instrucao para um buffer temporario

		printf("\nInstrucao %d:\n", instructionMemory[PC].instructionAddress);  //imprime o indice da instrucao
		puts (inputLine);			// inputLine contem a instrucao a ser trabalhada
	
		// ### (2o estagio) instuction Decode - Parse
		getOpcodeBinary(inputLine);  // ripa o OpCode
		printf("\nOpcode: "); puts(opcodeBinary);
		ripDataBinary(opcodeBinary); // ripa o restante dos dados - parse
					
		signExtender(); // entende o immediate
		
		registerOut(); // retorna os valores de saida de registradores para buffers (variaveis globais)
		
		// ### (3o estagio) Execution		
		alu();         // operacoes aritmeticas da ALU
		PC = PC + verifyBranch();    // verifica atraves de "AluZero" e "Branch" e em caso necessario, altera o PC para tomarmos o branch

		// ### somente imprimindo dados para conferencia
		printInstruction(); // imprime as instrucoes ja devidamente separadas
		printDataMemory(); //  imprime estado da Memoria
		printRegisters();  //  imprime estado dos registradores

		// ### (4o estagio) Memory 
		memoryHandler();  // gerencia as operacoes na memoria
						  
		// ### (5o estagio) WriteBack
		writeBack();

		

		printf("\nDigite qualquer tecla pra continuar...");
		getch();
		clearScreen();		
	}

	// checagem final das memorias e dos registradores!
	printf("\n --== Resultado Final ==--\n\n");

	printDataMemory(); //  imprime estado da Memoria
	printRegisters();  //  imprime estado dos registradores

	printf("\nDigite qualquer tecla pra finalizar!");
	getch();
	
return 0;
}
