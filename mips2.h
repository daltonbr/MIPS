// Header that defines registers, functions and constants for a MIPS processor
//mips2.h
#ifndef MIPS2
#define MIPS2

//Global Variables
extern char inputLine[33];

extern char opcodeBinary[7];        // G Var for Binary
extern char rsBinary[6];
extern char rtBinary[6];
extern char rdBinary[6];
extern char shamtBinary[6];
extern char functBinary[7];

extern char immediateBinary[17];   // exclusive type I
extern char addressBinary[27]; 	// exclusive type J

// buffers de saida
extern char signExtend[33];
extern char reg1Out[33];   // saidas dos banco de registradores
extern char reg2Out[33];
extern char aluOut[33];    // saida da ALU principal
extern char memOut[33];	// saida da memoria


// sinais de controle
extern char regWrite;
extern char regDst;
extern char AluSrc;
extern char AluOp;
extern char AluZero;
extern char memRead;
extern char memWrite;
extern char memToReg;
extern char branch;

extern char instructionAssembly[6];     // G Var for Assembly
extern int PC;         // Program Counter

// fim da declaracao de Global Variables

//Core Instruction Set (tipo + 6bits)
/*
// R Format Instructions - 12 types (Tipo + 6 bits Funct) (opcode fixo 000000)
add = R100000 	// 0/20 *
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
//declaracao de funcoes
void charTo16Bits (char *charInput, char *charOutput);
void charTo16BitsU (char *charInput, char *charOutput);
void charTo5BitsU (char *charInput, char *charOutput);
void charTo26BitsU (char *charInput, char *charOutput); // usada nas funcoes J  //ou nao?
void charTo32Bits(char *charInput, char *charOutput);
void ripBinaryLabel();
void binary16ToChar(char *charInput, char *charOutput);
void binary5ToCharU(char *charInput, char *charOutput);  // converte binarios em decimal char C2
void binary16ToCharU(char *charInput, char *charOutput); // converte binarios em decimal char Unsigned
int binary32ToChar(char *charInput, char *charOutput);
void not (char *string); // inverte 0 pra 1 e vice-versa

// # funcoes Assembly -> Binary
void registerToAssembly(char *registerBinary, char *registerAssembly);
void instructionR ();
void instructionI ();
void instructionJ ();


// cabecalho das funcoes individuais binary -> Assembly
void addToAssembly(); // R
void adduToAssembly(); // R
void andToAssembly(); // R
void jrToAssembly(); // R
void norToAssembly(); // R
void orToAssembly(); // R
void sltToAssembly(); // R
void sltuToAssembly(); // R
void sllToAssembly(); // R
void srlToAssembly(); // R
void subToAssembly(); // R
void subuToAssembly(); // R
void addiToAssembly();  // I
void andiToAssembly();  // I
void beqToAssembly();  // I parenteses
void bneToAssembly();  // I parenteses
void lbuToAssembly();  // I parenteses
void lhuToAssembly();  // I parenteses
void llToAssembly();  // I parenteses - rever
void luiToAssembly();    // I
void lwToAssembly();    // I
void oriToAssembly();    // I
void sltiToAssembly();    // I
void sltiuToAssembly();    // IU
void sbToAssembly();  // I parenteses
void scToAssembly();  // I parenteses
void shToAssembly();  // I parenteses
void swToAssembly();  // I parenteses
void jToAssembly();  // J
void jalToAssembly();  // J

//recebe duas strings por referencia, sendo a primeiro uma string em binário 32bits
//segunda("a saída") em uma string representando inteiro
int binary32ToChar(char *charInput, char *charOutput)
{
	int aux = 0;
	char tempInput[33];

	if (charInput[0] == '0') // o ultimo bit, em complemento de 2, é reservado para a representação de sinal, entao se ele for '0' significa que o numero é positivo
	{
		strcpy(tempInput, charInput);
		aux = strtol(tempInput, &charOutput, 2); // função que converte binary, em uma string, para um decimal em outra string
		itoa(aux, charOutput, 10);
		//printf("Debug valor conversao: %ld\n", aux);
	}
	else // tratamento para numeros negativo
	{
		strcpy(tempInput, charInput);
		not(tempInput);
		aux = strtol(tempInput, &charOutput, 2);
		aux = (aux + 1) * -1;
		itoa(aux, charOutput, 10);
	}
	return aux;
}

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

void not (char *string)
{
	int i=0;
	do
	{
		if (string[i] == '0') 
		{
			string[i] = '1';    				
		}
		else
		{
			string[i]='0';
    	}
		i++;
	} while (string[i] != '\0');
}

void padZero(char *string, int length)
{
	int i=0, originalLength;
	originalLength = strlen(string);  //tamanho antes do preenchimento
	char stringTemp[17] = {0};        // array temporario
	strncpy (stringTemp, string, originalLength);  //guarda a string original
	stringTemp[originalLength] = '\0';
	
	int padLength = length - strlen(string);  // diferenca que preencheremos com '0'
	if (padLength < 0) padLength = 0;    // Evitamos tamanhos negativos - nunca deveria ser
	
	for (i=0; i < padLength; i++)
	{
		string[i] = '0';		
	}
	strncpy ( (string + padLength) ,stringTemp, originalLength);   // concatena de volta na string (agora com zeros) o conteudo original
}

// retorna 1 se o caracter eh numerico, incluindo o hifen para caso de negativos
// retorna 0 se qualquer outro.
int isNumeric (char ch)
{
	int output;
	switch (ch){
		case '0': output = 1;
		case '1': output = 1;
		case '2': output = 1;
		case '3': output = 1;
		case '4': output = 1;
		case '5': output = 1;
		case '6': output = 1;
		case '7': output = 1;
		case '8': output = 1;
		case '9': output = 1;
		case '-': output = 1;   // podemos argumentar que pra outros usos esta nao eh uma escolha sabia =)
		break;
	default:
		output = 0;
	}
	return output;
}

// similar a funcao isNumeric() 
int isBinary (char ch)
{
	int output;
	switch (ch){
		case '0': output = 1;
		case '1': output = 1;
		break;
	default:
		output = 0;
	}
	return output;
}
/*
void addToBinary() // R
{
	strcpy (functBinary,"100000");	 	// fixo para o add
}

void addiToBinary()  // I
{
	strcpy (opcodeBinary,"001000");
}

void addiuToBinary()  // IU
{
	strcpy (opcodeBinary,"001001");
}

void adduToBinary() // R   -- revisar
{
	strcpy (functBinary,"100001");	// fixo para o addu
}

void andToBinary() //  R
{
	strcpy (functBinary,"100100");
}

void andiToBinary() // I
{
	strcpy (opcodeBinary,"001100");
}
		
void beqToBinary() // I
{
	strcpy (opcodeBinary,"000100");
}

void bneToBinary() // I
{
	strcpy (opcodeBinary,"000101");
}

void jToBinary()  // J  -atencao
{
	int i = 2; //  recorta o label
	do {
		addressAssembly[i-2] = inputLine[i];
		i++;
	} while (inputLine[i] != '\n');
	
	int label;
	label = searchLabel(addressAssembly);
	itoa(label,addressAssembly,10);
	
	charTo26BitsU(addressAssembly, addressBinary);
	strcpy (opcodeBinary,"000010");
}

void jalToBinary()  // J   -atencao
{
	strcpy (opcodeBinary,"000011");
	int i = 4; //  recorta o label
	do {
		addressAssembly[i-4] = inputLine[i];
		i++;
	} while (inputLine[i] != '\n');
	
	int label;
	label = searchLabel(addressAssembly);
	itoa(label,addressAssembly,10);
	
	charTo26BitsU(addressAssembly, addressBinary);
}

void jrToBinary()   // R -  usar rs 
{					
	strcpy (functBinary,"001000");	
	strcpy (opcodeBinary,"000000");	 	// fixo para R
	strcpy (shamtBinary,"00000"); 	
	strcpy (rsBinary,"00000"); 
	strcpy (rdBinary,"00000"); 	// fixo para R
}

void lbuToBinary() // I
{
	strcpy (opcodeBinary,"100100");
}

void lhuToBinary() // I  Unsigned
{
	strcpy (opcodeBinary,"100101");
}

void llToBinary() // I
{
	strcpy (opcodeBinary,"110000");
}

void luiToBinary() // I  C2?  Load Upper Immed  - nao eh Unsigned
{
	strcpy (opcodeBinary,"001111");
}

void lwToBinary() // I
{
	strcpy (opcodeBinary,"100011");
}

void norToBinary()   // R
{
	strcpy (functBinary,"100111");	
}	

void orToBinary()   // R
{
	strcpy (functBinary,"100101");	
}	

void oriToBinary() // I
{
	strcpy (opcodeBinary,"001101");
}		

void sltToBinary() // R
{
	strcpy (functBinary,"101010");	
}

void sltiToBinary() // I
{
	strcpy (opcodeBinary,"001010");	
}

void sltiuToBinary() // I
{
	strcpy (opcodeBinary,"001011");	
}

void sltuToBinary() // R   e U how???
{
	strcpy (functBinary,"101011");	
}

void sllToBinary() // R    -- atencao tem shamt
{
	strcpy (opcodeBinary,"000000");
	strcpy (functBinary,"000000");
	strcpy (rsBinary ,"00000");
	charTo5BitsU (immediateAssembly, shamtBinary ); //escreve no shamt
}

void srlToBinary() // R   -- atencao tem shamt
{
	strcpy (opcodeBinary,"000000");
	strcpy (functBinary,"000010");	
	strcpy (rsBinary ,"00000");
	charTo5BitsU (immediateAssembly, shamtBinary ); //escreve no shamt
}

void sbToBinary() // I
{
	strcpy (opcodeBinary,"101000");	
}		

void scToBinary() // I
{
	strcpy (opcodeBinary,"111000");	
}		

void shToBinary() // I
{
	strcpy (opcodeBinary,"101001");	
}			

void swToBinary() // I
{
	strcpy (opcodeBinary,"101011");	
}	

void subToBinary() // R
{
	strcpy (functBinary,"100010");	
}

void subuToBinary() // R  --- atencao funcao R! mas eh U?
{
	strcpy (functBinary,"100011");	
}
*/

// recebe duas strings por referencia, a primeira eh a entrada ("numeros")
//  a segunda devolve a string de binário UNSIGNED de 5 bits
void charTo5BitsU (char *charInput, char *charOutput)   
{
	int num = 33; // gambiarra pra cair fora do segundo if
	if ( charInput[0] != '-' ) //procura numeros negativos, eles nem deveriam ser chamados
		num=atoi(charInput);   //num receberá o char passado para int
	
	if( num<32 ) // limite do range de 16bits
	{
        //itoa(int ,char* ,base int);
        itoa(num,charOutput,2);  // converte o numero intero 'num' em um binário de base 2 e coloca na string 'charBinary'
		padZero(charOutput, 5);
		charOutput[5] = '\0';
	}else
	{
	    strcpy(charOutput,"XXXXX");  // saida de erro
		charOutput[5] = '\0';
	}
}
 // recebe duas strings por referencia, a primeira eh a entrada ("numeros")
 //  a segunda devolve a string de binário UNSIGNED de 16 bits
void charTo16BitsU (char *charInput, char *charOutput)
{
	int num = 65537; // gambiarra pra cair fora do segundo if
	if ( charInput[0] != '-' ) //procura numeros negativos, eles nem deveriam ser chamados
		num=atoi(charInput);   //num receberá o char passado para int
	
	if( num<65536 ) // limite do range de 16bits
	{
        //itoa(int ,char* ,base int);
        itoa(num,charOutput,2);  // converte o numero intero 'num' em um binário de base 2 e coloca na string 'charBinary'
		padZero(charOutput, 16);
	}else
	{
	    strcpy(charOutput,"XXXXXXXXXXXXXXXX");  // saida de erro
		charOutput[16] = '\0';
	}
}
// recebe duas strings por referencia, a primeira eh a entrada ("numeros")
//  a segunda devolve a string de binário em Complemento de 2 em 16 bits
void charTo16Bits (char *charInput, char *charOutput)
{

	int num=atoi(charInput);   //num receberá o char passado para int	
	
	if (-32768 <= num < 32768)
	{
		if (num>=0) // se o numero é maior que 0, é passado pra binário normalmente
		{
	        //itoa(int ,char* ,base int);
	        itoa(num,charOutput,2); // converte o numero intero 'num' em um binário de base 2 e coloca na string 'charBinary'
			padZero(charOutput, 16);  //completa com zeros
		}
		else
		{
		    itoa ( (num*(-1)) -1 , charOutput,2 ); // se o numero é negativo, ele é passado pra positivo (e subtraimos 1)
		    padZero(charOutput, 16);  //completa com zeros
			not (charOutput);   	// complemento do array
		}
	}else
	{
		strcpy(charOutput,"XXXXXXXXXXXXXXXX");  // saida de erro
	}
}

void charTo26BitsU (char *charInput, char *charOutput)
{
	int num = 67108865; // gambiarra pra cair fora do segundo if
	if ( charInput[0] != '-' ) //procura numeros negativos, eles nem deveriam ser chamados
		num=atoi(charInput);   //num receberá o char passado para int
	
	if( num<67108864 ) // limite do range de 26bits
	{
        //itoa(int ,char* ,base int);
        itoa(num,charOutput,2);  // converte o numero intero 'num' em um binário de base 2 e coloca na string 'charBinary'
		padZero(charOutput, 26);
	}else
	{
	    strcpy(charOutput,"XXXXXXXXXXXXXXXXXXXXXXXXXX");  // saida de erro
		charOutput[26] = '\0';
	}
}

// recebe duas strings por referencia, a primeira eh a entrada ("numeros")
//  a segunda devolve a string de binário em Complemento de 2 em 32 bits
void charTo32Bits(char *charInput, char *charOutput)
{

	int num = atoi(charInput);   //num receberá o char passado para int	

	if (-32768 <= num < 32768)
	{
		if (num >= 0) // se o numero é maior que 0, é passado pra binário normalmente
		{
			//itoa(int ,char* ,base int);
			itoa(num, charOutput, 2); // converte o numero intero 'num' em um binário de base 2 e coloca na string 'charBinary'
			padZero(charOutput, 32);  //completa com zeros
		}
		else
		{
			itoa((num*(-1)) - 1, charOutput, 2); // se o numero é negativo, ele é passado pra positivo (e subtraimos 1)
			padZero(charOutput, 32);  //completa com zeros
			not (charOutput);   	// complemento do array
		}
	}
	else
	{
		printf("Debug: Erro na funcao charTo32Bits!");
		strcpy(charOutput, "XXXXXXXXXXXXXXXX");  // saida de erro
	}
}


/*
//recebe duas strings por referencia, sendo a primeiro uma string em binário 16bits
//segunda("a saída") em uma string representando inteiro
void binary16ToChar(char *charInput, char *charOutput)
{
	int i,aux=0;
	char tempInput[17];
	
	if(charInput[0]=='0') // o ultimo bit, em complemento de 2, é reservado para a representação de sinal, entao se ele for '0' significa que o numero é positivo
	{
		strcpy(tempInput,charInput);
		aux = strtol(tempInput, &charOutput, 2); // função que converte binary, em uma string, para um decimal em outra string
		itoa ( aux, charOutput, 10 );
		printf("teste apos: %ld\n", aux);
	}
	else // tratamento para numeros negativos
	{
		strcpy(tempInput,charInput);
		not(tempInput);
		aux = strtol( tempInput, &charOutput, 2);
		aux = (aux+1) * -1 ;
		itoa ( aux, charOutput, 10 );
	}
	strcpy(immediateAssembly,charOutput);
}

void binary5ToCharU(char *charInput, char *charOutput)
{
	int aux=0;
	char tempInput[6];
	strcpy(tempInput,charInput);
	aux = strtol(tempInput, &charOutput, 2); // função que converte binary, em uma string, para um decimal em outra string
	itoa ( aux, charOutput, 10 );
	strcpy(shamtAssembly,charOutput); // corrigir logica
}

void binary16ToCharU(char *charInput, char *charOutput) // funcao crasha para numero grandes
{
	int aux=0;
	char tempInput[17];
	strcpy(tempInput,charInput);
	aux = strtol(tempInput, &charOutput, 2); // função que converte binary, em uma string, para um decimal em outra string
	itoa ( aux, charOutput, 10 );
	strcpy(immediateAssembly,charOutput); // corrigir logica
}

void binary26ToCharU(char *charInput, char *charOutput)
{
	int aux=0;
	char tempInput[27];
	strcpy(tempInput,charInput);
	aux = strtol(tempInput, &charOutput, 2); // função que converte binary, em uma string, para um decimal em outra string
	itoa ( aux, charOutput, 10 );
	strcpy(addressAssembly,charOutput); // corrigir logica
}

*/

// #######  Funcoes de binary -> Assembly

void getOpcodeBinary (char *inputLine)
{
	strncpy (opcodeBinary, inputLine, 6);
	opcodeBinary[6] = '\0';
}

void ripDataBinary(char *opcodeBinary)
{
	strncpy(rsBinary, inputLine + 6, 5);  // faz o split de acordo com a funcao R
	strncpy(rtBinary, inputLine + 11, 5);
	strncpy(rdBinary, inputLine + 16, 5);
	strncpy(shamtBinary, inputLine + 21, 5);
	strncpy(functBinary, inputLine + 26, 6);
	strncpy(addressBinary, inputLine + 6, 26);   // faz o split de acordo com a funcao J
	strncpy(immediateBinary, inputLine + 16, 16);

	if (!(strcmp(opcodeBinary,"000000"))){  // R
		instructionR();
	} else if ( (!(strcmp(opcodeBinary,"000010"))) || (!(strcmp(opcodeBinary,"000011"))) ){  // J
		instructionJ();
	} else {  // I
		instructionI();
	}
}

// funcao que converte um registro binario em assembly
void registerToAssembly(char *registerBinary, char *registerAssembly)
{
	if (!(strcmp(registerBinary,"00000"))){  		  //retorna 0 se iguais, portanto !0 = verdadeiro
		strcpy(registerAssembly,"$zero");
	} else if (!(strcmp(registerBinary,"00001"))) {   	// 1 	Assemble temporary
		strcpy(registerAssembly,"$at");		
	} else if (!(strcmp(registerBinary,"00010"))) {		// 2 	Function Results and Expression Evaluation
		strcpy(registerAssembly,"$v0");				
	} else if (!(strcmp(registerBinary,"00011"))) {
		strcpy(registerAssembly,"$v1");			
	} else if (!(strcmp(registerBinary,"00100"))) {		// 4	Arguments
		strcpy(registerAssembly,"$a0");		
	} else if (!(strcmp(registerBinary,"00101"))) {
		strcpy(registerAssembly,"$a1");		
	} else if (!(strcmp(registerBinary,"00110"))) {
		strcpy(registerAssembly,"$a2");		
	} else if (!(strcmp(registerBinary,"00111"))) {
		strcpy(registerAssembly,"$a3");		
	} else if (!(strcmp(registerBinary,"01000"))) {		// 8	Temporaries
		strcpy(registerAssembly,"$t0");		
	} else if (!(strcmp(registerBinary,"01001"))) {
		strcpy(registerAssembly,"$t1");
	} else if (!(strcmp(registerBinary,"01010"))) {
		strcpy(registerAssembly,"$t2");
	} else if (!(strcmp(registerBinary,"01011"))) {
		strcpy(registerAssembly,"$t3");
	} else if (!(strcmp(registerBinary,"01100"))) {
		strcpy(registerAssembly,"$t4");
	} else if (!(strcmp(registerBinary,"01101"))) {
		strcpy(registerAssembly,"$t5");
	} else if (!(strcmp(registerBinary,"01110"))) {
		strcpy(registerAssembly,"$t6");
	} else if (!(strcmp(registerBinary,"01111"))) {
		strcpy(registerAssembly,"$t7");												
	} else if (!(strcmp(registerBinary,"10000"))) {		// 16	Saved Temporaries
		strcpy(registerAssembly,"$s0");		
	} else if (!(strcmp(registerBinary,"10001"))) {
		strcpy(registerAssembly,"$s1");
	} else if (!(strcmp(registerBinary,"10010"))) {
		strcpy(registerAssembly,"$s2");
	} else if (!(strcmp(registerBinary,"10011"))) {
		strcpy(registerAssembly,"$s3");
	} else if (!(strcmp(registerBinary,"10100"))) {
		strcpy(registerAssembly,"$s4");
	} else if (!(strcmp(registerBinary,"10101"))) {
		strcpy(registerAssembly,"$s5");
	} else if (!(strcmp(registerBinary,"10110"))) {
		strcpy(registerAssembly,"$s6");
	} else if (!(strcmp(registerBinary,"10111"))) {
		strcpy(registerAssembly,"$s7");		
	} else if (!(strcmp(registerBinary,"11000"))) {		// 24	Temporaries
		strcpy(registerAssembly,"$t8");
	} else if (!(strcmp(registerBinary,"11001"))) {
		strcpy(registerAssembly,"$t9");			
	} else if (!(strcmp(registerBinary,"11010"))) {		// 26	Reserved for OS Kernel
		strcpy(registerAssembly,"$k0");
	} else if (!(strcmp(registerBinary,"11011"))) {
		strcpy(registerAssembly,"$k1");
	} else if (!(strcmp(registerBinary,"11100"))) {
		strcpy(registerAssembly,"$gp");
	} else if (!(strcmp(registerBinary,"11101"))) {
		strcpy(registerAssembly,"$sp");
	} else if (!(strcmp(registerBinary,"11110"))) {
		strcpy(registerAssembly,"$fp");
	} else if (!(strcmp(registerBinary,"11111"))) {
		strcpy(registerAssembly,"$ra");					
	} else {
		strcpy(registerAssembly ,"$xx");    //caso de Erro, nenhum registro compativel encontrado
	}
}

//  ### bloco de cada funcado de binary -> assembly
void addToAssembly() // R
{
	strcpy(instructionAssembly, "add");
	regWrite = '1';
	regDst = '1';
	AluSrc = '0';
	AluOp = '0';
	memRead = '0';
	memWrite = '0';
	memToReg = '0';
	branch = '0';
}

void adduToAssembly() // R
{
	strcpy(instructionAssembly, "addu");
}

void andToAssembly() // R
{
	strcpy(instructionAssembly, "and");
}

void jrToAssembly() // R
{
	strcpy(instructionAssembly, "jr");
}

void norToAssembly() // R
{
	strcpy(instructionAssembly, "nor");
}

void orToAssembly() // R
{
	strcpy(instructionAssembly, "or");
}

void sltToAssembly() // R
{
	strcpy(instructionAssembly, "slt");
}

void sltuToAssembly() // R
{
	strcpy(instructionAssembly, "sltu");
}

void sllToAssembly() // R
{
	strcpy(instructionAssembly, "sll");
}

void srlToAssembly() // R
{
	strcpy(instructionAssembly, "srl");
}

void subToAssembly() // R
{
	strcpy(instructionAssembly, "sub");
}

void subuToAssembly() // R
{
	strcpy(instructionAssembly, "subu");
}
// tipo I
void addiToAssembly()  // I
{
	strcpy(instructionAssembly, "addi");
	regWrite = '1';
	regDst = '0';
	AluSrc = '1';
	AluOp = '0';
	memRead = '0';
	memWrite = '0';
	memToReg = '0';
	branch = '0';
}

void andiToAssembly()  // I
{
	strcpy(instructionAssembly, "andi");
}

void beqToAssembly()  // I
{
	strcpy(instructionAssembly, "beq");
	regWrite = '0';
	regDst = '0';
	AluSrc = '0';
	AluOp = '1';
	memRead = '1';
	memWrite = '0';
	memToReg = '0';
	branch = '1';
}

void bneToAssembly()  // I
{
	strcpy(instructionAssembly, "bne");
}

void lbuToAssembly()  // I parenteses
{
	strcpy(instructionAssembly, "lbu");
}

void lhuToAssembly()  // I parenteses
{
	strcpy(instructionAssembly, "lhu");
}

void llToAssembly()  // I parenteses - rever
{
	strcpy(instructionAssembly, "ll");
}

void luiToAssembly()    // I
{
	strcpy(instructionAssembly, "lui");
}

void lwToAssembly()    // I parenteses
{
	strcpy(instructionAssembly, "lw");
	regWrite = '1';
	regDst = '0';
	AluSrc = '1';
	AluOp = '0';
	memRead = '1';
	memWrite = '0';
	memToReg = '1';
	branch = '0';
}

void oriToAssembly()    // I
{
	strcpy(instructionAssembly, "ori");
}

void sltiToAssembly()    // I
{
	strcpy(instructionAssembly, "slti");
}

void sltiuToAssembly()    // IU
{
	strcpy(instructionAssembly, "sltiu");
}

void sbToAssembly()  // I parenteses
{
	strcpy(instructionAssembly, "sb");
}

void scToAssembly()  // I parenteses
{
	strcpy(instructionAssembly, "sc");
}

void shToAssembly()  // I parenteses
{
	strcpy(instructionAssembly, "sh");
}

void swToAssembly()  // I parenteses
{
	strcpy(instructionAssembly, "sw");
	regWrite = '0';
	regDst = '0';
	AluSrc = '1';
	AluOp = '0';
	memRead = '0';
	memWrite = '1';
	memToReg = '0';
	branch = '0';
}

void jToAssembly()  // J
{
	strcpy(instructionAssembly, "j");
}

void jalToAssembly()  // J
{
	strcpy(instructionAssembly, "jal");
}


void instructionR ()
{
	if (!(strcmp(functBinary,"100000"))){  		  //retorna 0 se iguais, portanto !0 = verdadeiro
		addToAssembly(); // R		
	} else if (!(strcmp(functBinary,"100001"))){  		 
		adduToAssembly(); // RU	
	} else if (!(strcmp(functBinary,"100100"))){
		andToAssembly();  //R
	} else if (!(strcmp(functBinary,"001000"))){
		jrToAssembly();  //R
	} else if (!(strcmp(functBinary,"100111"))){
		norToAssembly();  //R			
	} else if (!(strcmp(functBinary,"100101"))){
		orToAssembly();  //R
	} else if (!(strcmp(functBinary,"101010"))){
		sltToAssembly();  //R
	} else if (!(strcmp(functBinary,"101011"))){
		sltuToAssembly();  //R
	} else if (!(strcmp(functBinary,"000000"))){
		sllToAssembly();  //R
	} else if (!(strcmp(functBinary,"000010"))){
		srlToAssembly();  //R
	} else if (!(strcmp(functBinary,"100010"))){
		subToAssembly();  //R
	} else if (!(strcmp(functBinary,"100011"))){
		subuToAssembly();  //RU
	} else {
		printf("ERRO! Funcao instructionR! Instrucao nao Reconhecida");    //caso de Erro, nenhum instruction compativel encontrado
	}	
}

void instructionJ ()
{
	if (!(strcmp(opcodeBinary,"000010"))){  		  //retorna 0 se iguais, portanto !0 = verdadeiro
		jToAssembly(); 
	} else if (!(strcmp(opcodeBinary,"000011"))){
		jalToAssembly();   		 
	} else {
		printf("ERRO! Funcao instructionJ! Instrucao nao Reconhecida");    //caso de Erro, nenhum instruction compativel encontrado

	}		
}

void instructionI ()
{
	if (!(strcmp(opcodeBinary,"001000"))){  		  //retorna 0 se iguais, portanto !0 = verdadeiro
		addiToAssembly();    // I
	} else if (!(strcmp(opcodeBinary,"001100"))){
		andiToAssembly();    // I
	} else if (!(strcmp(opcodeBinary,"000100"))){
		beqToAssembly();     // I
	} else if (!(strcmp(opcodeBinary,"000101"))){
		bneToAssembly(); 	 // I	
	} else if (!(strcmp(opcodeBinary,"100100"))){
		lbuToAssembly(); 	 // I parenteses	
	} else if (!(strcmp(opcodeBinary,"100101"))){
		lhuToAssembly(); 	 // I parenteses
	} else if (!(strcmp(opcodeBinary,"110000"))){
		llToAssembly(); // I parenteses - rever
	} else if (!(strcmp(opcodeBinary,"001111"))){
		luiToAssembly();    // I
	} else if (!(strcmp(opcodeBinary,"100011"))){
		lwToAssembly();    // I
	} else if (!(strcmp(opcodeBinary,"001101"))){
		oriToAssembly();    // I
	} else if (!(strcmp(opcodeBinary,"001010"))){
		sltiToAssembly();    // I
	} else if (!(strcmp(opcodeBinary,"001011"))){
		sltiuToAssembly();    // IU
	} else if (!(strcmp(opcodeBinary,"101000"))){
		sbToAssembly();    // I parenteses
	} else if (!(strcmp(opcodeBinary,"111000"))){
		scToAssembly();    // I ??
	} else if (!(strcmp(opcodeBinary,"101001"))){
		shToAssembly();    // I parenteses
	} else if (!(strcmp(opcodeBinary,"101011"))){
		swToAssembly();    // I ??
	} else {
		printf("ERRO! Funcao instructionI! Instrucao nao Reconhecida");    //caso de Erro, nenhum instruction compativel encontrado

	}	
}

#endif