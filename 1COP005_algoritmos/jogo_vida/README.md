# 🇺🇸 game-of-life:

rules taken from the website "en.wikipedia.org/wiki/Conway%27s_Game_of_Life":

- any live cell with fewer than two live neighbours dies, as if by underpopulation.

- any live cell with two or three live neighbours lives on to the next generation.

- any live cell with more than three live neighbours dies, as if by overpopulation.

- any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

*note: to execute, pass the parameters: ./main quadro.txt "number of generations"

# 🇧🇷 jogo-da-vida:

regras retiradas do site "pt.wikipedia.org/wiki/Jogo_da_vida":

- toda célula morta com exatamente três vizinhos vivos torna-se viva (nascimento).

- toda célula viva com menos de dois vizinhos vivos morre por isolamento.

- toda célula viva com mais de três vizinhos vivos morre por superpopulação.

- toda célula viva com dois ou três vizinhos vivos permanece viva.

*obs: para executar passe os parâmetros: ./main quadro.txt "número de gerações"
