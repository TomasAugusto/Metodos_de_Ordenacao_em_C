# Metodos_de_Ordenacao_em_C
 Trabalho voltado a testar os metodos de ordenação em C

Trabalho foi desenvolvido utilizando o DevC++

Enunciado do Trabalho


O objetivo deste trabalho é comparar o desempenho dos algoritmos de
ordenação vistos em sala. Você deverá implementar os algoritmos SelectSort,
InsertSort, QuickSort e MergeSort e testá-los com diversos vetores de entrada
(vetores do tipo aluno), contabilizando o número de comparações de chaves,
o número de movimentações de registros e o tempo de execução. Para isso
você deverá colocar contadores em seu código e instrumentá-lo de forma a obter
o tempo de execução (use a biblioteca: #include <time.h>; Veja sobre a função:
clock();).
Os vetores deverão ser do tipo Aluno, ou seja, vão precisar criar uma struct
Aluno, que vai conter os seguintes membros: matrícula (int), nome (string), curso
matriculado (string), coeficiente de rendimento (double), período atual (int).
No caso do Quicksort, você deverá implementar a variação “mediana de três”,
em que o pivô é escolhido usando a mediana entre a chave mais à esquerda, a
chave mais à direita, e a chave central (como no algoritmo original). Você deverá
fazer tabelas comparando a performance de cada algoritmo. Mais
especificamente, você deverá realizar testes com vetores de tamanhos 1000,
10000, 100000 e 200000 elementos. Três diferentes tipos de vetores devem ser
utilizados: aleatórios, ordenados e inversamente ordenados.
Para os vetores aleatórios, repita os testes 10 vezes, de forma a obter médias
do tempo de execução e dos contadores. O próprio programa deve gerar os
vetores dos quatro tipos de entradas.
O seu programa deverá imprimir gerar um registro (arquivo de texto), contendo
as seguintes informações: o método de ordenação utilizado, tamanho do vetor,
o tempo de execução e o número de comparações e movimentações efetuado.
Deverá haver também uma opção no programa para imprimir os vetores antes e
depois da execução. Estas informações deverão ser impressas também na tela.
Utilize o srand para gerar um número aleatório, assim, conseguirá preencher os
campos inteiros. Crie uma função para conseguir gerar strings aleatórias para o
nome do estudante e o curso (não precisam fazer sentido os nomes). Sugestão,
crie uma string alfabeto, e gere um número aleatório, e use o número aleatório
para acessar o índice dessa string. Faça isso sucessivamente, para formar o
nome.