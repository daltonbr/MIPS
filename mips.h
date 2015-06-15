// Header that defines registers, functions and constants for a MIPS processor
//mips.h
#ifndef MIPS
#define MIPS

//Global Variables
extern char inputLine[129];
extern char outputLine[129];

extern char opcodeBinary[7];        // G Var for Binary
extern char rsBinary[6];
extern char rtBinary[6];
extern char rdBinary[6];
extern char shamtBinary[6];
extern char functBinary[7];

extern char immediateBinary[17];   // exclusive type I
extern char addressBinary[27]; 	// exclusive type J

extern char functionAssembly[6];     // G Var for Assembly
extern char rsAssembly[4];
extern char rtAssembly[4];
extern char rdAssembly[4];
extern char shamtAssembly[3];      // 2^5 = 32 (max) - 2 caracteres
//extern char functAssembly[6];

extern char immediateAssembly[6];   // 2^16 = 65538 (max) - 5 caracteres
extern char addressAssembly[26]; 	// definimos address com 

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
void ripBinaryLabel();
void ripBinaryR();
void ripBinaryI();
void ripBinaryJ();

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

void concatenateR(char *outputLine)  //generates R type line
{
	strcpy (opcodeBinary,"000000");	 	// fixo para R
	strcpy (shamtBinary,"00000"); 		// fixo para R
	
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, rsBinary);
	strcat (outputLine, rtBinary);
	strcat (outputLine, rdBinary);
	strcat (outputLine, shamtBinary);
	strcat (outputLine, functBinary);
}

void concatenateI(char *outputLine)	//generates I type line
{
	charTo16Bits (immediateAssembly, immediateBinary );
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, rtBinary);  //rs na verdade
	strcat (outputLine, rdBinary);  //rt na verdade
	strcat (outputLine, immediateBinary);
}

void concatenateIU(char *outputLine)	//generates I type line
{
	charTo16BitsU (immediateAssembly, immediateBinary );
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, rtBinary);  //rs na verdade
	strcat (outputLine, rdBinary);  //rt na verdade
	strcat (outputLine, immediateBinary);
}

void concatenateJ(char *outputLine)	//generates J type line
{
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, addressBinary);
}

void addToBinary() // R
{
	strcpy (functBinary,"100000");	 	// fixo para o add
	concatenateR(outputLine);   // "empacota" a linha
}

void addiToBinary()  // I
{
	strcpy (opcodeBinary,"001000");
	concatenateI(outputLine);   // "empacota" a linha
}

void addiuToBinary()  // IU
{
	strcpy (opcodeBinary,"001001");
	concatenateIU(outputLine);   // "empacota" a linha
}

void adduToBinary() // R   -- revisar
{
	strcpy (functBinary,"100001");	// fixo para o addu
	concatenateR(outputLine);   // "empacota" a linha
}

void andToBinary() //  R
{
	strcpy (functBinary,"100100");
	concatenateR(outputLine);   // "empacota" a linha
}

void andiToBinary() // I
{
	strcpy (opcodeBinary,"001100");
	concatenateI(outputLine);   // "empacota" a linha
}
		
void beqToBinary() // I
{
	strcpy (opcodeBinary,"000100");
	concatenateI(outputLine);   // "empacota" a linha
}

void bneToBinary() // I
{
	strcpy (opcodeBinary,"000101");
	concatenateI(outputLine);   // "empacota" a linha
}

void jToBinary()  // J  -atencao
{
	strcpy (opcodeBinary,"000010");
	concatenateJ(outputLine);   // "empacota" a linha
}

void jalToBinary()  // J   -atencao
{
	strcpy (opcodeBinary,"000011");
	concatenateJ(outputLine);   // "empacota" a linha
}

void jrToBinary()   // R   --- provavelmente? zerar todo o resto!
{					//  usar rs, rt ou rd ???
	strcpy (functBinary,"001000");	
	strcpy (opcodeBinary,"000000");	 	// fixo para R
	strcpy (shamtBinary,"00000"); 		// fixo para R
	
	strcpy (outputLine, opcodeBinary);
	strcat (outputLine, rsBinary);  //primeiro que extrai
	strcat (outputLine, "00000");   //rt
	strcat (outputLine, "00000");   //rd
	strcat (outputLine, shamtBinary);
	strcat (outputLine, functBinary);
	
	concatenateR(outputLine);   // "empacota" a linha
}

void lbuToBinary() // I
{
	strcpy (opcodeBinary,"100100");
	concatenateIU(outputLine);   // "empacota" a linha	
}

void lhuToBinary() // I  Unsigned
{
	strcpy (opcodeBinary,"100101");
	concatenateIU(outputLine);   // "empacota" a linha	
}

void llToBinary() // I
{
	strcpy (opcodeBinary,"110000");
	concatenateI(outputLine);   // "empacota" a linha	
}

void luiToBinary() // I  C2?  Load Upper Immed  - nao eh Unsigned
{
	strcpy (opcodeBinary,"001111");
	concatenateI(outputLine);   // "empacota" a linha	
}

void lwToBinary() // I
{
	strcpy (opcodeBinary,"100011");
	concatenateI(outputLine);   // "empacota" a linha	
}

void norToBinary()   // R
{
	strcpy (functBinary,"100111");	
	concatenateR(outputLine);   // "empacota" a linha
}	

void orToBinary()   // R
{
	strcpy (functBinary,"100101");	
	concatenateR(outputLine);   // "empacota" a linha
}	

void oriToBinary() // I
{
	strcpy (opcodeBinary,"001101");
	concatenateI(outputLine);   // "empacota" a linha	
}		

void sltToBinary() // R
{
	strcpy (functBinary,"101010");	
	concatenateR(outputLine);   // "empacota" a linha
}

void sltiToBinary() // I
{
	strcpy (opcodeBinary,"001010");	
	concatenateI(outputLine);   // "empacota" a linha
}

void sltiuToBinary() // I
{
	strcpy (opcodeBinary,"001011");	
	concatenateIU(outputLine);   // "empacota" a linha
}

void sltuToBinary() // R   e U how???
{
	strcpy (functBinary,"101011");	
	concatenateR(outputLine);   // "empacota" a linha
}

void sllToBinary() // R    -- atencao tem shamt
{
	strcpy (opcodeBinary,"000000");
	strcpy (functBinary,"000000");	
	charTo5BitsU (immediateAssembly, shamtBinary ); //escreve no shamt
	
	strcpy (outputLine, opcodeBinary);  // concatena avulso por causa do shamt
	strcat (outputLine, rsBinary);
	strcat (outputLine, rtBinary);
	strcat (outputLine, rdBinary);
	strcat (outputLine, shamtBinary);
	strcat (outputLine, functBinary);
}

void srlToBinary() // R   -- atencao tem shamt
{
	strcpy (opcodeBinary,"000000");
	strcpy (functBinary,"000010");	
	charTo5BitsU (immediateAssembly, shamtBinary ); //escreve no shamt
	
	strcpy (outputLine, opcodeBinary);  // concatena avulso por causa do shamt
	strcat (outputLine, rsBinary);
	strcat (outputLine, rtBinary);
	strcat (outputLine, rdBinary);
	strcat (outputLine, shamtBinary);
	strcat (outputLine, functBinary);
}

void sbToBinary() // I
{
	strcpy (opcodeBinary,"101000");	
	concatenateI(outputLine);   // "empacota" a linha
}		

void scToBinary() // I
{
	strcpy (opcodeBinary,"111000");	
	concatenateI(outputLine);   // "empacota" a linha
}		

void shToBinary() // I
{
	strcpy (opcodeBinary,"101001");	
	concatenateI(outputLine);   // "empacota" a linha
}			

void swToBinary() // I
{
	strcpy (opcodeBinary,"101011");	
	concatenateI(outputLine);   // "empacota" a linha
}	

void subToBinary() // R
{
	strcpy (functBinary,"100010");	
	concatenateR(outputLine);   // "empacota" a linha
}

void subuToBinary() // R  --- atencao funcao R! mas eh U?
{
	strcpy (functBinary,"100011");	
	concatenateR(outputLine);   // "empacota" a linha
}

// ##################


void ripDataAssembly (char *myLine)    	// primeira versao - soh extrai registros
										// precisaremos caso especial pra J e JAL ?
{
	char rs[4], rt[4], rd[4];
	char immediate[6];  //soh armazena ate 65536 = 2^16 = 65536 unsigned - maior numero que um immediate U de 16bits pode ter. + 1 terminator
	char address[26]; 	// *tamanho aberto a revisao
	char ch, chProx;
	int offset = 0, isNum = 0, tamanho = 0;

	//	essa primeira parte procura registradores - basicamente procurando por "$"
	do
	{
		offset++;
		ch = myLine[offset]; 
	} while (ch != '$' && ch != '\0');
	
	if ( ch == '$' )
	{
		strncpy(rt,(myLine + offset),3);		//achou o primeiro registro e poe no RT - copia os 3 chars seguintes
		rt[3] = '\0';
	}
	
	if ( ch != '\0' ) //ainda nao acabou ?
	{
		do
		{
			offset++;
			ch = myLine[offset];
		} while (ch != '$' && ch != '\0');
		
		if ( ch == '$' ) {
			strncpy(rd,(myLine + offset),3);  //achou o segundo registro e poe no RD
			rd[3] = '\0';
		}
		
		if ( ch != '\0' ) //ainda nao acabou  ?
		{
			do
			{
				offset++;
				ch = myLine[offset];
			} while (ch != '$' && ch != '\0');
			
			if ( ch == '$' ){
				strncpy(rs,(myLine + offset),3);   //achou o terceiro registro e poe no RS			
				rs[3] = '\0';
			}
		}
	}
		
	// essa parte procura o immediate (inteiro), caso exista
	// a tecnica consiste em pegar um elemento depois da virgula que nao tenha "$"asicamente ele fica depois de uma virgula
	// assumimos que nao temos espacos depois da virgula, e que eventualmente tenhamos um immediate entre parenteses.
	
	offset = 0;  //importante zerar o offset pois varreremos novamente a linha
	do
	{
		offset++;
		ch = myLine[offset];
		if ( ch == ',' ) {    // se o char atual eh virgula, checa se o proximo eh numerico
			offset++;
			chProx = myLine[offset];
			isNum = isNumeric(chProx);	
		}
	} while ( !isNum && ch != '\0' );  // soh sai desse loop qdo \0 ou encontrar uma virgula seguida de um numerico
	
	if ( ch != '\0' )  //pra entrar nesse if, somente se offset esta parado em nosso immediate 
	{
		tamanho = offset;   //offset guarda a posicao do primeiro caracter do immediate
			do {			//verifica onde termina o imediate   
				tamanho++;
				chProx = myLine[tamanho];
				isNum = isNumeric(chProx);
			} while (isNum);    //sai do loop qdo encontra um "nao numerico"
			tamanho = tamanho - offset;		 // faz a diferenca pra saber o tamanho do immediate
			strncpy(immediate,(myLine + offset),tamanho);		//copia do immediate
			immediate[tamanho] = '\0';
	}
	// os registros ja estao extraidos, e serao passados em forma de binario 
	strcpy ( rsAssembly, rs); //copiando variavel local pra global
	strcpy ( rtAssembly, rt);
	strcpy ( rdAssembly, rd);
	strcpy ( immediateAssembly, immediate);
	
}

// funcao que retorna os binarios de cada Registro - em caso de erro retorna xxxxx
char *registerToBinary(char *registerAssembly)
{
	static char *registerBinary;
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
	registerAssembly=registerBinary;
	return (char *)registerBinary;   //(char *)registerBinary;
}

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


void filterInstruction(char *instruction)
{
	if (!(strcmp(instruction,"add"))){
		addToBinary();
	} else if (!(strcmp(instruction,"addi"))){
		addiToBinary();
	} else if (!(strcmp(instruction,"addiu"))){
		addiuToBinary();	
	} else if (!(strcmp(instruction,"and"))){
		andToBinary();
	} else if (!(strcmp(instruction,"andi"))){
		andiToBinary();
	} else if (!(strcmp(instruction,"beq"))){  // label?
		beqToBinary();
	} else if (!(strcmp(instruction,"bne"))){  // label?
		bneToBinary();
	} else if (!(strcmp(instruction,"j"))){    // J
		jToBinary();
	} else if (!(strcmp(instruction,"jal"))){   // J
		jalToBinary();
	} else if (!(strcmp(instruction,"jr"))){   // R
		jrToBinary();
	} else if (!(strcmp(instruction,"lbu"))){
		lbuToBinary();
	} else if (!(strcmp(instruction,"lhu"))){
		lhuToBinary();
	} else if (!(strcmp(instruction,"ll"))){
		llToBinary();
	} else if (!(strcmp(instruction,"lui"))){
		luiToBinary();
	} else if (!(strcmp(instruction,"lw"))){
		andToBinary();
	} else if (!(strcmp(instruction,"nor"))){
		norToBinary();
	} else if (!(strcmp(instruction,"or"))){
		orToBinary();
	} else if (!(strcmp(instruction,"ori"))){
		oriToBinary();
	} else if (!(strcmp(instruction,"slt"))){
		sltToBinary();
	} else if (!(strcmp(instruction,"slti"))){
		sltiToBinary();
	} else if (!(strcmp(instruction,"sltiu"))){
		sltiuToBinary();
	} else if (!(strcmp(instruction,"sltu"))){
		sltuToBinary();		
	} else if (!(strcmp(instruction,"sll"))){
		sllToBinary();
	} else if (!(strcmp(instruction,"srl"))){
		srlToBinary();
	} else if (!(strcmp(instruction,"sb"))){
		sbToBinary();
	} else if (!(strcmp(instruction,"sc"))){
		scToBinary();
	} else if (!(strcmp(instruction,"sh"))){
		shToBinary();
	} else if (!(strcmp(instruction,"sw"))){		
		swToBinary();
	} else if (!(strcmp(instruction,"sub"))){
		subToBinary();
	} else if (!(strcmp(instruction,"subu"))){
		subuToBinary();	
	}
	else {
		printf("\nERRO! - Funcao nao existente!\n");  //caso de Erro, funcao nao encontrada
	}		
}


// #######  Funcoes de binary -> Assembly

void getOpcodeBinary (char *inputLine)
{
	strncpy (opcodeBinary, inputLine, 6);
	opcodeBinary[6] = '\0';
}

void ripDataBinary(char *opcodeBinary)
{
	if (!(strcmp(opcodeBinary,"000000"))){  // R
		ripBinaryR();
	} else if ( (!(strcmp(opcodeBinary,"000010"))) || (!(strcmp(opcodeBinary,"000011"))) ){  // J
		ripBinaryJ();
	} else if (!(strcmp(opcodeBinary,"111111"))) { // LABEL ?
		ripBinaryLabel();
	} else {  // I
		ripBinaryI();
	}	
}

void ripBinaryR()
{
	strncpy(rsBinary, inputLine+6, 5);
	strncpy(rtBinary, inputLine+11, 5);
	strncpy(rdBinary, inputLine+16, 5);
	strncpy(shamtBinary, inputLine+21, 5);
	strncpy(functBinary, inputLine+26, 6);
}

void ripBinaryJ()
{
	strncpy(addressBinary, inputLine+6, 26);
}

void ripBinaryI()
{
	strncpy(rsBinary, inputLine+6, 5);
	strncpy(rtBinary, inputLine+11, 5);
	strncpy(immediateBinary, inputLine+16, 16);
}

void ripBinaryLabel()
{
	printf("\nLABEL NOS BINARIOS\n");
	//strncpy(addressBinary, inputLine+6, 26);
}

#endif