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

	mov ax,0

	mov dx, [bp+4]
	mov al, [bp+6]
	out dx, al

	pop dx 
	pop ax
	pop bp
	ret
_outportb ENDP

_inportb PROC 
	push bp
	mov bp,sp

	push dx

	mov ah,0

	mov dx, [bp+4]
	in al,dx

	pop dx
	pop bp
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
