import random
import math

def coprimo(phi):
    e = random.randint(3, phi - 1)
    while math.gcd(e, phi) != 1:
        e = random.randint(3, phi - 1)
    return e

def inversoMod(e, phi):
    for d in range(3, phi):
        if (e * d) % phi == 1:
            return d
    raise ValueError("Inverso modular não existe!")