dosseg
.MODEL tiny

.CODE
public _inportb
public _outportb

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
