#define BYTE unsigned char
#define WORD unsigned int
#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43
#define PTOs_all_out 0x80

char getch(void);

extern unsigned char inportb(WORD Puerto);
extern void outportb(WORD Puerto, BYTE dato);

void putchar(BYTE dato);

void ClrBitPort(WORD Puerto, BYTE num_bit);
void NotBitPort(WORD Puerto, BYTE num_bit);
void printBin(BYTE dato);
void puts(char *str);
void SetBitPort(WORD Puerto, BYTE num_bit);

unsigned char ReverseBitPort(WORD Puerto);
unsigned char TstBitPort(WORD Puerto, BYTE num_bit);

char dato;

void main( void ){
	char dTemp;

	puts("Practica 5b"); /* imprimir mensaje */
	putchar(10);
	putchar(13);
	dato = 170;

	outportb(RCtr, PTOs_all_out);  /*inicializar 8255 */
	/*outportb(RCtr,0x82);*/
	/*outportb(PA,0x55);  presentar 55h en el Pto A */
	/*while(1){
		putchar(10);
		putchar(13);
		dato = getch();  
		putchar(dato);
		putchar('=');
		printBin(dato);
		outportb(PA,dato); 
	}*/
	while(1)
	{
		outportb(PA,dato);
		printBin(dato);
		getch();
		putchar(' ');
		putchar(' ');
		ReverseBitPort(PA);
		dTemp = inportb(PA);
		printBin(dTemp);
		getch();
		putchar(10);
		putchar(13);
	}
} 

char getch(void)
{
	char dato;

	asm mov ah,8
	asm int 21h
	asm mov dato,al

	return dato;
}

void putchar(BYTE dato)
{

	asm mov dl, dato
	asm mov ah,02h
	asm int 21h
}

void puts(char *str)
{
	while(*str)
	{
		putchar(*str++);
	}
}

/* función simple para desplegar un byte en formato binario */
void printBin( BYTE dato ){
	BYTE msk=0x80;
	
	do{
		putchar( (dato & msk) ? '1' : '0' );
		msk>>=1;
	}while( msk );
}


void SetBitPort(WORD Puerto, BYTE num_bit)
{
	BYTE mask=0x01; /* mascara inicial */
	BYTE temp; /* dato auxiliar */
	temp = inportb( Puerto ); /* leer dato del puerto */
	mask = mask << num_bit; /* ajustar mascara según num_bit */
	temp = temp | mask; /* aplicar mascara con operador OR */
	outportb( Puerto , temp ); /* presentar resultado en el puerto */
}

void ClrBitPort( WORD Puerto, BYTE num_bit)
{
	BYTE mask=0x00; 				/* mascara inicial */
	BYTE temp; 						/* dato auxiliar */
	temp = inportb( Puerto ); 		/* leer dato del puerto */
	mask = mask << num_bit; 		/* ajustar mascara según num_bit */
	temp = temp & mask;
	outportb( Puerto , temp ); 		/* presentar resultado en el puerto */
}

void NotBitPort( WORD Puerto, BYTE num_bit)
{
	BYTE mask=0x01; 				/* mascara inicial */
	BYTE temp; 						/* dato auxiliar */
	temp = inportb( Puerto ); 		/* leer dato del puerto */
	mask = mask << num_bit; 		/* ajustar mascara según num_bit */
	temp = temp ^ mask;
	outportb( Puerto , temp ); 		/* presentar resultado en el puerto */
}

unsigned char TstBitPort( WORD Puerto, BYTE num_bit)
{
	BYTE mask=0x01; 				/* mascara inicial */
	BYTE temp; 						/* dato auxiliar */
	temp = inportb( Puerto ); 		/* leer dato del puerto */
	mask = mask << num_bit; 		/* ajustar mascara según num_bit */

	if((temp&mask) == 0 ){
		return 0;
	}
	return 1;
}

unsigned char ReverseBitPort(WORD Puerto)
{
	int cMSB = 7, cLSB = 0;
	BYTE temp;
	/*BYTE MSBmask = 0x80; 	Iniciando en el bit mas significativo
	BYTE LSBmask = 0x1; 		iniciando la mascara en el bit menos seignificativo*/
	do
	{
		if( (TstBitPort(Puerto,cMSB)&TstBitPort(Puerto,cLSB)) == 0 )
		{
			NotBitPort(PA,cMSB);
			NotBitPort(PA,cLSB);
		}
		cMSB--;
		cLSB++;
		/*MSBmask = MSBmask >> 1;
		LSBmask = LSBmask << 1;*/
	}while(cMSB > cLSB);
}


