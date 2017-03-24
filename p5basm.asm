dosseg
.MODEL tiny

.CODE
public _inportb
public _outportb
public _putchar
public _puts

_outportb PROC 
	push bp
	mov bp,sp

	push ax
	push dx


	mov dx, [bp+4]
	mov al, [bp+6]
	out dx, al

	pop ax
	pop dx 
	pop bp
	ret
_outportb ENDP

_inportb PROC 
	push ax
	push dx

	push bp
	mov bp,sp
	
	mov dx, [bp+4]
	in al,dx

	pop bp
	pop dx
	pop ax
	ret
_inportb ENDP

_putchar PROC 
	
	push ax
	push dx

	push bp
	mov bp,sp
	
	mov dl, [bp+4]
	mov ah,02h
	int 21h

	pop bp
	pop dx 
	pop ax
	ret
_putchar ENDP

_puts PROC
	push ax
	push dx 

	push bp
	mov bp,sp 

	mov ah,09h
	mov dx,[bp+4]
	int 21h

	pop bp 
	pop dx
	pop ax
	ret 
_puts ENDP

END

 ; Tabla para retornar valores
 ; ==============================================================
 ; Tipo de Valor Lacalidad para el Valor
 ; --------------------------------------------------------------
 ; unsigned char, char, enum 								AX
 ; unsigned short, short 									AX
 ; unsigned int, int 										AX
 ; unsigned long, long 									 DX:AX
 ; float, double, long double 				  Dirección offset
 ; struct y union 							  Dirección offset
 ; near * 												    AX
 ; far * 												 DX:AX
 ; ============================================================== 
