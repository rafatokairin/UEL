def inversoMod(e, phi):
    for d in range(3, phi):
        if (e * d) % phi == 1:
            return d
    raise ValueError("Inverso modular não existe!")