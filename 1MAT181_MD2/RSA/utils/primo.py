import random

def ehPrimo(num):
    if num < 2:
        return False
    for i in range(2, num // 2 + 1):
        if num % i == 0:
            return False
    return True

def geraPrimo(valor_min, valor_max):
    primo = random.randint(valor_min, valor_max)
    while not ehPrimo(primo):
        primo = random.randint(valor_min, valor_max)
    return primo