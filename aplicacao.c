#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> 

// Definição da estrutura Aluno
typedef struct {
    int matricula;
    char nome[50];
    char curso[50];
    double coeficiente;
    int periodo;
} Aluno;

// Estrutura para estatísticas
typedef struct {
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
    double tempoExecucao;
} Estatisticas;

// Protótipos das funções de ordenação
Estatisticas selectSort(Aluno vetor[], int tamanho, FILE *arquivo);
Estatisticas insertSort(Aluno vetor[], int tamanho, FILE *arquivo);
Estatisticas quick(Aluno vetor[], int tamanho, FILE *arquivo);
Estatisticas merge(Aluno vetor[], int tamanho, FILE *arquivo);


// Função para gerar nomes aleatórios
char *gerarNomeAleatorio() {
    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    char *nome = (char *)malloc(10 * sizeof(char));
    for (int i = 0; i < 9; ++i) {
        int index = rand() % (strlen(alfabeto) - 1);
        nome[i] = alfabeto[index];
    }
    nome[9] = '\0';
    return nome;
}

char *gerarCursoAleatorio() {
    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    char *curso = (char *)malloc(10 * sizeof(char));
    for (int i = 0; i < 12; ++i) {
        int index = rand() % (strlen(alfabeto) - 1);
        curso[i] = alfabeto[index];
    }
    curso[12] = '\0';
    return curso;
}

// Função para gerar um aluno aleatório
Aluno gerarAlunoAleatorio() {
    Aluno a;
    a.matricula = rand(); // Gera uma matrícula aleatória
    strcpy(a.nome, gerarNomeAleatorio());
    strcpy(a.curso, gerarCursoAleatorio()); 
    a.coeficiente = (double)rand() / RAND_MAX * 10.0; // Gera um coeficiente entre 0 e 10
    a.periodo = rand() % 10 + 1; // Gera um período entre 1 e 10
    return a;
}

// Função para gerar um vetor de alunos aleatórios
void gerarVetorAleatorio(Aluno vetor[], int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = gerarAlunoAleatorio();
    }
}


void gerarVetorOrdenado(Aluno vetor[], int tamanho) {
    gerarVetorAleatorio(vetor, tamanho);
    selectSort(vetor, tamanho, NULL); // Passando NULL como o argumento FILE*
}


void gerarVetorInversamenteOrdenado(Aluno vetor[], int tamanho) {
    gerarVetorOrdenado(vetor, tamanho);
    // Inverte a ordem do vetor
    for (int i = 0; i < tamanho / 2; ++i) {
        Aluno temp = vetor[i];
        vetor[i] = vetor[tamanho - i - 1];
        vetor[tamanho - i - 1] = temp;
    }
}

//-----------------------------SelecSort-----------------------------

Estatisticas selectSort(Aluno vetor[], int tamanho, FILE *arquivo) {
    Estatisticas est;
    est.comparacoes = 0;
    est.movimentacoes = 0;

    clock_t inicio, fim;
    inicio = clock();

    for (int i = 0; i < tamanho - 1; ++i) {
        int indiceMenor = i;
        for (int j = i + 1; j < tamanho; ++j) {
            est.comparacoes++;
            if (vetor[j].matricula < vetor[indiceMenor].matricula) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            Aluno temp = vetor[i];
            vetor[i] = vetor[indiceMenor];
            vetor[indiceMenor] = temp;
            est.movimentacoes += 3;
        }
    }

    fim = clock();
    est.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    

    return est;
}

//-----------------------------InsertSort-----------------------------

Estatisticas insertSort(Aluno vetor[], int tamanho, FILE *arquivo) {
    Estatisticas est;
    est.comparacoes = 0;
    est.movimentacoes = 0;

    clock_t inicio, fim;
    inicio = clock();

    for (int i = 1; i < tamanho; ++i) {
        Aluno chave = vetor[i];
        int j = i - 1;

        while (j >= 0 && vetor[j].matricula > chave.matricula) {
            est.comparacoes++;
            vetor[j + 1] = vetor[j];
            j = j - 1;
            est.movimentacoes++;
        }
        vetor[j + 1] = chave;
        if (i != j + 1) {
            est.movimentacoes++;
        }
    }

    fim = clock();
    est.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    return est;
}


//-----------------------------QuickSort-----------------------------

void trocarAlunos(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}

int encontrarMediana(Aluno vetor[], int esquerda, int direita) {
    int meio = (esquerda + direita) / 2;

    if (vetor[esquerda].matricula > vetor[meio].matricula) {
        trocarAlunos(&vetor[esquerda], &vetor[meio]);
    }
    if (vetor[esquerda].matricula > vetor[direita].matricula) {
        trocarAlunos(&vetor[esquerda], &vetor[direita]);
    }
    if (vetor[meio].matricula > vetor[direita].matricula) {
        trocarAlunos(&vetor[meio], &vetor[direita]);
    }

    trocarAlunos(&vetor[meio], &vetor[direita - 1]);
    return vetor[direita - 1].matricula;
}

void quickSort(Aluno vetor[], int esquerda, int direita, Estatisticas *est) {
    if (esquerda < direita) {
        int pivot = encontrarMediana(vetor, esquerda, direita);
        int i = esquerda;
        int j = direita - 1;

        while (i <= j) {
            while (vetor[i].matricula < pivot) {
                i++;
                est->comparacoes++;
            }
            while (vetor[j].matricula > pivot) {
                j--;
                est->comparacoes++;
            }
            if (i <= j) {
                trocarAlunos(&vetor[i], &vetor[j]);
                i++;
                j--;
                est->movimentacoes++;
            }
        }

        quickSort(vetor, esquerda, j, est);
        quickSort(vetor, i, direita, est);
    }
}
	

Estatisticas quick(Aluno vetor[], int tamanho, FILE *arquivo) {
    Estatisticas est;
    est.comparacoes = 0;
    est.movimentacoes = 0;

    clock_t inicio, fim;
    inicio = clock();

    quickSort(vetor, 0, tamanho - 1, &est);

    fim = clock();
    est.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    return est;
}

//-----------------------------MergeSort-----------------------------

void mergeSort(Aluno vetor[], int esquerda, int direita, Estatisticas *est) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(vetor, esquerda, meio, est);
        mergeSort(vetor, meio + 1, direita, est);

        int tamanhoEsquerda = meio - esquerda + 1;
        int tamanhoDireita = direita - meio;

        Aluno *tempEsquerda = (Aluno *)malloc(tamanhoEsquerda * sizeof(Aluno));
        Aluno *tempDireita = (Aluno *)malloc(tamanhoDireita * sizeof(Aluno));

        for (int i = 0; i < tamanhoEsquerda; i++) {
            tempEsquerda[i] = vetor[esquerda + i];
        }
        for (int j = 0; j < tamanhoDireita; j++) {
            tempDireita[j] = vetor[meio + 1 + j];
        }

        int indiceEsquerda = 0, indiceDireita = 0, indiceMerge = esquerda;
        while (indiceEsquerda < tamanhoEsquerda && indiceDireita < tamanhoDireita) {
            est->comparacoes++;
            if (tempEsquerda[indiceEsquerda].matricula <= tempDireita[indiceDireita].matricula) {
                vetor[indiceMerge] = tempEsquerda[indiceEsquerda++];
            } else {
                vetor[indiceMerge] = tempDireita[indiceDireita++];
            }
            est->movimentacoes++;
            indiceMerge++;
        }

        while (indiceEsquerda < tamanhoEsquerda) {
            vetor[indiceMerge++] = tempEsquerda[indiceEsquerda++];
            est->movimentacoes++;
        }
        while (indiceDireita < tamanhoDireita) {
            vetor[indiceMerge++] = tempDireita[indiceDireita++];
            est->movimentacoes++;
        }

        free(tempEsquerda);
        free(tempDireita);
    }
}

Estatisticas merge(Aluno vetor[], int tamanho, FILE *arquivo) {
    Estatisticas est = {0, 0, 0.0};
    clock_t inicio = clock();
    mergeSort(vetor, 0, tamanho - 1, &est);
    est.tempoExecucao = ((double)(clock() - inicio)) / CLOCKS_PER_SEC;
    return est;
}

//-----------------------------Comparações e registro de dados-----------------------------

void salvarVetorEmArquivo(Aluno vetor[], int tamanho, FILE *arquivo, const char* descricao) {
    fprintf(arquivo, "%s\n", descricao);
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "Matricula: %d, Nome: %s, Curso: %s, Coeficiente: %.2f, Periodo: %d\n", 
                vetor[i].matricula, vetor[i].nome, vetor[i].curso, vetor[i].coeficiente, vetor[i].periodo);
    }
    fprintf(arquivo, "\n");
}



void aplicarMetodoOrdenacao(Aluno *vetores[12], int tamanho, int metodo, FILE *arquivoResultados, FILE *arquivoAntes, FILE *arquivoDepois) {
    Estatisticas (*funcaoOrdenacao)(Aluno[], int, FILE*) = NULL;
    char *nomeMetodo;

    switch (metodo) {
        case 1:
            funcaoOrdenacao = selectSort;
            nomeMetodo = "SelectSort";
            break;
        case 2:
            funcaoOrdenacao = insertSort;
            nomeMetodo = "InsertSort";
            break;
        case 3:
            funcaoOrdenacao = quick;
            nomeMetodo = "QuickSort";
            break;
        case 4:
            funcaoOrdenacao = merge;
            nomeMetodo = "MergeSort";
            break;
    }

    Estatisticas estatisticas[12];
    for (int i = 0; i < 12; i++) {
        char descricao[50];
        if (i == 0) strcpy(descricao, "Vetor Ordenado");
        else if (i == 1) strcpy(descricao, "Vetor Inversamente Ordenado");
        else sprintf(descricao, "Vetor Aleatorio %d", i-1);

        // Gravação dos vetores antes da ordenação no arquivo correspondente
        salvarVetorEmArquivo(vetores[i], tamanho, arquivoAntes, descricao);
        
        // Aplica a função de ordenação sem gravar os resultados no arquivo
        estatisticas[i] = funcaoOrdenacao(vetores[i], tamanho, NULL); 

        // Gravação dos vetores após a ordenação no arquivo correspondente
        salvarVetorEmArquivo(vetores[i], tamanho, arquivoDepois, descricao);
    }

    // Exibir resultados para o vetor ordenado e inversamente ordenado
    fprintf(arquivoResultados, "Resultados para o vetor ordenado:\n");
    fprintf(arquivoResultados, "Comparacoes: %llu, Movimentacoes: %llu, Tempo de execucao: %.6f segundos\n\n",
           estatisticas[0].comparacoes, estatisticas[0].movimentacoes, estatisticas[0].tempoExecucao);
    printf("Resultados para o vetor ordenado:\n");
    printf("Comparacoes: %llu, Movimentacoes: %llu, Tempo de execucao: %.6f segundos\n\n",
           estatisticas[0].comparacoes, estatisticas[0].movimentacoes, estatisticas[0].tempoExecucao);       
    

    fprintf(arquivoResultados, "Resultados para o vetor inversamente ordenado:\n");
    fprintf(arquivoResultados, "Comparacoes: %llu, Movimentacoes: %llu, Tempo de execucao: %.6f segundos\n\n",
           estatisticas[1].comparacoes, estatisticas[1].movimentacoes, estatisticas[1].tempoExecucao);
    printf("Resultados para o vetor inversamente ordenado:\n");
    printf("Comparacoes: %llu, Movimentacoes: %llu, Tempo de execucao: %.6f segundos\n\n",
           estatisticas[1].comparacoes, estatisticas[1].movimentacoes, estatisticas[1].tempoExecucao);


    // Cálculo da média para os 10 vetores aleatórios
    Estatisticas media = {0, 0, 0.0};
    for (int i = 2; i < 12; i++) {
        media.comparacoes += estatisticas[i].comparacoes;
        media.movimentacoes += estatisticas[i].movimentacoes;
        media.tempoExecucao += estatisticas[i].tempoExecucao;
    }
    media.comparacoes /= 10;
    media.movimentacoes /= 10;
    media.tempoExecucao /= 10;

    fprintf(arquivoResultados, "Média para os 10 vetores aleatórios:\n");
    fprintf(arquivoResultados, "Comparacoes: %llu, Movimentacoes: %llu, Tempo de execucao: %.6f segundos\n\n",
           media.comparacoes, media.movimentacoes, media.tempoExecucao);
    printf("Média para os 10 vetores aleatórios:\n");
    printf("Comparacoes: %llu, Movimentacoes: %llu, Tempo de execucao: %.6f segundos\n\n",
           media.comparacoes, media.movimentacoes, media.tempoExecucao);       
           
}

char* getNomeMetodo(int metodo) {
    switch (metodo) {
        case 1: return "SelectSort";
        case 2: return "InsertSort";
        case 3: return "QuickSort";
        case 4: return "MergeSort";
        default: return "Desconhecido";
    }
}

//-----------------------------Main-----------------------------

int main() {
    setlocale(LC_ALL, "Portuguese");
    FILE *arquivoResultados = fopen("resultados_ordenacao.txt", "w");
    if (arquivoResultados == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
	int tamanhos[] = {1000, 10000, 100000, 200000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int metodos[] = {1, 2, 3, 4}; // 1: SelectSort, 2: InsertSort, 3: QuickSort, 4: MergeSort
    //int numMetodos = sizeof(metodos) / sizeof(metodos[0]);

    for (int t = 0; t < numTamanhos; t++) {
        int tamanho = tamanhos[t];
        printf("\nTestando com tamanho de vetor: %d\n\n", tamanho);
        fprintf(arquivoResultados, "\nTestando com tamanho de vetor: %d\n\n", tamanho);

        for (int m = 0; m < 4; m++) {
            int metodo = metodos[m];
            char *nomeMetodo = getNomeMetodo(metodo);
            printf("Aplicando %s ao vetor de tamanho %d\n", nomeMetodo, tamanho);
            fprintf(arquivoResultados, "Aplicando %s ao vetor de tamanho %d\n", nomeMetodo, tamanho);

            char arquivoAntesNome[64], arquivoDepoisNome[64];
            sprintf(arquivoAntesNome, "metodo_%s_antes_%d.txt", nomeMetodo, tamanho);
            sprintf(arquivoDepoisNome, "metodo_%s_depois_%d.txt", nomeMetodo, tamanho);

            FILE *arquivoAntes = fopen(arquivoAntesNome, "w");
            FILE *arquivoDepois = fopen(arquivoDepoisNome, "w");

            // Criação e inicialização dos vetores
            Aluno *vetorOrdenado = (Aluno *)malloc(tamanho * sizeof(Aluno));
            Aluno *vetorInversamenteOrdenado = (Aluno *)malloc(tamanho * sizeof(Aluno));
            Aluno *vetoresAleatorios[10];

            // Geração dos vetores
            gerarVetorOrdenado(vetorOrdenado, tamanho);
            gerarVetorInversamenteOrdenado(vetorInversamenteOrdenado, tamanho);

            for (int i = 0; i < 10; i++) {
                vetoresAleatorios[i] = (Aluno *)malloc(tamanho * sizeof(Aluno));
                gerarVetorAleatorio(vetoresAleatorios[i], tamanho);
            }

            // Aplicar o método de ordenação
            Aluno *todosOsVetores[12] = {vetorOrdenado, vetorInversamenteOrdenado};
            for (int i = 0; i < 10; i++) {
                todosOsVetores[i + 2] = vetoresAleatorios[i];
            }

             aplicarMetodoOrdenacao(todosOsVetores, tamanho, metodo, arquivoResultados, arquivoAntes, arquivoDepois);

            // Liberação de memória alocada dinamicamente
            free(vetorOrdenado);
            free(vetorInversamenteOrdenado);
            for (int i = 0; i < 10; i++) {
                free(vetoresAleatorios[i]);
            }

            fclose(arquivoAntes);
            fclose(arquivoDepois);
        }
        printf("\n"); 
        fprintf(arquivoResultados, "\n");
    }
    fclose(arquivoResultados);
    return 0;
}
