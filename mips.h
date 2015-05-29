#ifndef MIPS
#define MIPS

// Header that defines registers, functions and constants for a MIPS processor
//mips.h

typedef struct {
	char opcode[6];
	char rs[5];
	char rt[5];
	char rd[5];
	char shamt[5];
	char funct[6];
	char end[1];
} instructionR;

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
/*
// 32 registers
//name	number	use
$zero	// 0	constant 0
$at		// 1 	Assemble temporary

$v0		// 2 	Function Results and Expression Evaluation
$v1		// 3

$a0		// 4	Arguments
$a1		// 5
$a2		// 6
$a3		// 7

$t0		// 8	Temporaries
$t1		// 9
$t2		// 10
$t3		// 11
$t4		// 12
$t5		// 13	
$t6		// 14
$t7		// 15

$s0		// 16	Saved Temporaries
$s1		// 17
$s2		// 18
$s3		// 19
$s4		// 20
$s5		// 21
$s6		// 22
$s7		// 23

$t8		// 24	Temporaries
$t9		// 25

$k0		// 26	Reserved for OS Kernel
$k1		// 27

$gp		// 28	Global Pointer
$sp		// 29	Stack Pointer
$fp		// 30	Frame Pointer

$ra		// 31	Return Adress

*/

#endif