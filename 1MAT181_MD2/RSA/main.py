import utils

# gera primos para p e q
p, q = utils.geraPrimo(1000, 5000), utils.geraPrimo(1000, 5000)
while p == q:
    q = utils.geraPrimo(1000, 5000)

# calcula n e phi de n
n = p * q
phi_n = (p - 1) * (q - 1)

# escolhe um "e" coprimo de phi de n aleatório (3 <= e <= phi_n - 1)
e = utils.coprimo(phi_n)

# calcula inverso modular: (e * d) % phi_n = 1
d = utils.inversoMod(e, phi_n)

# infos
senha = "RSA1977!"
print(f"Senha original: {senha}")
print(f"p: {p}")
print(f"q: {q}")
print(f"n: {n}")
print(f"phi de n: {phi_n}")
print(f"Chave pública: {e}")
print(f"Chave privada: {d}")

# converte senha original em vetor de códigos ASCII
senha_cript = [ord(caracter) for caracter in senha]

# criptografa: (senha ^ e) mod n = c
senha_cript = [pow(caracter, e, n) for caracter in senha_cript]
print(f"\nSenha criptografada: {senha_cript}")

# descriptografa: (c ^ d) mod n = senha
senha_descript = [pow(caracter, d, n) for caracter in senha_cript]

# desconverte códigos ASCII
senha_descript = "".join(chr(caracter) for caracter in senha_descript)
print(f"\nSenha descriptografada: {senha_descript}")