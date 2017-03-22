#define BYTE unsigned char
#define WORD unsigned int
#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43
#define PTOs_all_out 0x80

void ClrBitPort( WORD Puerto, BYTE num_bit);
void NotBitPort( WORD Puerto, BYTE num_bit);
void outportb( WORD port, BYTE dato);
void printBin( BYTE dato );
unsigned char ReverseBitPort( WORD Puerto, BYTE num_bit);
unsigned char TstBitPort( WORD Puerto, BYTE num_bit);

char dato;

void main( void ){
	puts("Practica 5a\n\r"); /* imprimir mensaje */
	outportb(RCtr, PTOs_all_out); /* inicializar 8255 */
	outportb(PA,0x55); /* presentar 55h en el Pto A */
	while(1){
		dato = getch(); /* leer tecla */
		outportb(PB,dato); /* presentar tecla en PB */
		printBin(dato);
		puts("\n\r");
	}
} 
/* función para lectura de puertos usando ensamblador in-line */
void outportb( WORD port, BYTE dato){
	asm mov dx, port
	asm mov al, dato
	asm out dx, al
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
	BYTE mask=0x01; 				/* mascara inicial */
	BYTE temp; 						/* dato auxiliar */
	temp = inportb( Puerto ); 		/* leer dato del puerto */
	mask = mask << num_bit; 		/* ajustar mascara según num_bit */
	temp = temp | mask; 			/* aplicar mascara con operador OR */
	outportb( Puerto , temp ); 		/* presentar resultado en el puerto */
}

void ClrBitPort( WORD Puerto, BYTE num_bit)
{
	BYTE mask=0x01; 				/* mascara inicial */
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
	temp = temp ~ mask;
	outportb( Puerto , temp ); 		/* presentar resultado en el puerto */
}

unsigned char TstBitPort( WORD Puerto, BYTE num_bit)
{
	BYTE mask=0x01; 				/* mascara inicial */
	BYTE temp; 						/* dato auxiliar */
	temp = inportb( Puerto ); 		/* leer dato del puerto */
	mask = mask << num_bit; 		/* ajustar mascara según num_bit */
	
	if((temp | mask) == 0 ){
		return 0;
	}
	
	return 1;
	
}

unsigned char ReverseBitPort( WORD Puerto, BYTE num_bit)
{
	
	
}


