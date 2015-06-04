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


//funcao que le o arquivo binario
void readBinary ()
{
	FILE *binaryFile;
	// open a file
	binaryFile = fopen(".\\teste\\binary1.txt", "r");
		
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
	assemblyFile = fopen(".\\teste\\assembly1.txt", "r");
		
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
