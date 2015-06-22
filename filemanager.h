#ifndef FILEMANAGER
#define FILEMANAGER

/*
Header that defines functions to work with files in Windows OS 7+

FILE *fopen(const char *filename, const char *mode);
r  - open for reading
w  - open for writing (file need not exist)
a  - open for appending (file need not exist)
r+ - open for reading and writing, start at beginning
w+ - open for reading and writing (overwrite file)
a+ - open for reading and writing (append if file exists)
*/

//cabecalho de funcoes
int isLabel (char *inputline);

//imprime um pointeiro na tela de char, dado o tamanho - usado para Debug
void printPointer(char *string, int length)
{
	int i;
	for (i=0; i < length; i++){
		printf("%c", string[i]);
	}
}

//verifica se a linha eh um label em Assembly - retorna 0 se não eh
int isLabel (char *inputline)
{
	char ch;
	int i=0;
	do
	{
		ch = inputline[i];
		if (ch == ':')      // procuramos por ':'
			return 1;  //eh label
		i++; 
	} while (ch != '\0');
	return 0;  //nao eh label
}

//entrando uma linha, esta funcao retorna a primeira palavra antes do espaco
char *getNameAssembly(char *fullLine)
{
	int i = 0;
	char *name;
	name = (char *)malloc(6); // tamanho maximo do nome das funcoes, incluindo terminator
	
	do
	{
		name[i] = fullLine[i];
		i++;
	} while ( fullLine[i] != ' ' );    //transcreve a primeira parte da linha ate encontrar um espaco em branco
	name[i] = '\0';

	return (char *)name;
}

// funcao que conta as linhas de um arquivo - no momento o binary1.txt
unsigned long countLine ()
{
	unsigned long lineCount = 0;
	FILE *file;
	file = fopen("./binary.txt", "r");
	
	if ( file == NULL )
	{
		printf( "\nNao pode abrir o arquivo!\n" );
		return -1; //erro
	}
	else //let's count!
	{
		char ch;
		while ( (ch = fgetc(file)) != EOF ) 
		{
			if (ch == '\n')
			lineCount++;
		}	
	}
	lineCount++; // conta a ultima linha EOF - teoricamente precisa verificar se a ultima linha é vazia. Mas assumimos que nao!
	fclose (file);
	return lineCount;
	
}

//funcao que le o arquivo binario
void readBinary ()
{
	FILE *binaryFile;
	// open a file
	binaryFile = fopen("./binary.txt", "r");
		
	/* fopen returns 0, the NULL pointer, on failure */
	if ( binaryFile == NULL )
	{
		printf( "\nNao pode abrir o arquivo!\n" );
	}
	else // aqui que realmente le! 
	{
		char ch;  // read one character at a time from file
		while  ( (( ch = fgetc( binaryFile )) != EOF ) && ( ch != '\n' ) )   // compares with endline "\n" or EOF
		{
		   	 printf( "%c", ch );
		}
	
	fclose( binaryFile );
	}
}

void readAssembly ()
{
	FILE *assemblyFile;
	// open a file
	assemblyFile = fopen("./assembly.txt", "r");
		
	/* fopen returns 0, the NULL pointer, on failure */
	if ( assemblyFile == NULL )
	{
		printf( "\nNao pode abrir o arquivo!\n" );
	}
	else // aqui que realmente le! 
	{
		char ch;  // read one character at a time from file
		
		while  ( ( (ch = fgetc( assemblyFile )) != EOF ) && ( ch != '\n' ) )   // compares with endline "\n" or EOF
		{
		   	 printf( "%c", ch );
		}
	
	fclose( assemblyFile );
	}
}
#endif
