# 🇺🇸 knapsack-problem:

information taken from the website "en.wikipedia.org/wiki/Knapsack_problem":

- the knapsack problem is the following problem in combinatorial optimization. it derives its name from the problem faced by someone who is constrained by a fixed-size knapsack and must fill it with the most valuable items. the problem often arises in resource allocation where the decision-makers have to choose from a set of non-divisible projects or tasks under a fixed budget or time constraint, respectively.

- images ref:

  > knapwiki: "en.wikipedia.org/wiki/Knapsack_problem".

  > knapggl: "developers.google.com/optimization/pack/knapsack".
  
# heuristics:

- GOW: greedy ordered by weight.

- GOV: greedy ordered by value.

- GOR: greedy ordered by ratio (value / weight).

- BNB: branch and bound.

## knapwiki:

| TESTES: | GOW | GOV | GOR | BNB |
|:------------:|:----------:|:--------:|:---------:|:---------:|
| **SOLUTION**  | 827       | 1088      | 1183      | 1270      |
| **TIME(s)** | 0.000003  | 0.000003  | 0.000003  | 0.000025  |

## knapggl:

| TESTES: | GOW | GOV | GOR | BNB |
|:------------:|:---------:|:---------:|:---------:|:---------:|
| **SOLUTION**  | 2811      | 7339      | 7534      | 7534      |
| **TIME(s)** | 0.000007  | 0.000007  | 0.000009  | 1.627842  |

- test setup:

  > GTX 1050 2GB; i5-3330; 8GB RAM DDR3; 111GB SSD.

# 🇧🇷 problema-mochila:

informações retiradas do site "pt.wikipedia.org/wiki/Problema_da_mochila":

- o problema da mochila (em inglês, knapsack problem) é um problema de otimização combinatória. o nome se dá devido ao modelo de uma situação em que é necessário preencher uma mochila com objetos de diferentes pesos e valores. o objetivo é que se cumpra a mochila com o maior valor possível, não ultrapassando o peso máximo.

- imagens ref:

  > knapwiki: "en.wikipedia.org/wiki/Knapsack_problem".

  > knapggl: "developers.google.com/optimization/pack/knapsack".

# heurísticas:

- GOP: gulosa ordenada pelo peso.

- GOV: gulosa ordenada pelo valor.

- GOR: gulosa ordenada pela razão (valor / peso).

- BNB: branch and bound.

## knapwiki:

| TESTES: | GOP | GOV | GOR | BNB |
|:------------:|:----------:|:--------:|:---------:|:---------:|
| **SOLUÇÃO**  | 827       | 1088      | 1183      | 1270      |
| **TEMPO(s)** | 0.000003  | 0.000003  | 0.000003  | 0.000025  |

## knapggl:

| TESTES: | GOP | GOV | GOR | BNB |
|:------------:|:---------:|:---------:|:---------:|:---------:|
| **SOLUÇÃO**  | 2811      | 7339      | 7534      | 7534      |
| **TEMPO(s)** | 0.000007  | 0.000007  | 0.000009  | 1.627842  |

- setup de testes:

  > GTX 1050 2GB; i5-3330; 8GB RAM DDR3; 111GB SSD.
  
