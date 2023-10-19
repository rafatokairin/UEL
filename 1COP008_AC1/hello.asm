.data
msg: .asciiz "Hello, World!"

.text
main:
	# inicializando registradores
	li $v0, 4		# instrucao imprimir String
	la $a0, msg		# carregar endereco msg para $a0
	syscall
	
	li $v0, 10		# encerrar programa
	syscall
