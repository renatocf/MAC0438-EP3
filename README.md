# MAC0438-EP3
Third exercise of the disicpline MAC0458 (Programação Concorrente) 

MAC0438-EP3
============

Relatório
-----------
O arquivo em .pdf contendo o relatório encontra-se no diretório doc/

Monitores
--------

Terceiro exercício-programa da disciplina de MAC0438 (Programação
Concorrente).

Neste programa, resolvemos o problema dos filósofos famintos utilizando
monitores. Os monitores foram implementados na classe Fork e eles gerenciam
o acesso dos filósofos aos garfos (recurso compartilhado). O código se 
organiza de maneira simples : Será feito um jantar. Para servir um jantar,
organizam-se os filosofos e os garfos em uma mesa. Tudo que os filósofos fazem
é pensar e comer. Cada filósofo pensa por um instante e, depois, tenta comer. 
Para comer, tenta pegar os garfos (se for destro, pega primeiro o garfo à sua 
direita, e se for canhoto, pega primeiro o garfo à esquerda). Caso o 
filósofo consiga pegar os 2 garfos, ele então come. Ao terminar de comer, o
filósofo solta seus garfos e, então, repete tudo (volta para o passo de pensar).

Os arquivos do código fonte encontram-se nos diretórios 'include' (*.hpp) e 
'src' (*.cpp). Os arquivos de teste encontram-se na pasta 'test'. Os exemplos
de entrada utilizados para produção do relatório estão localizados no 
diretório 'example'.


Compilação
-----------
Para compilar, basta rodar o comando `make`

Para rodar os testes de unidade, coloque `make check`
