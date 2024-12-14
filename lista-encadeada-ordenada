#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CARROS 1000
#define TAM_HASH 11

// @author {Gabriel Soares}

// Estrutura do carro
typedef struct Carro {
    char placa[8];
    char modelo[20];
    float valor;
    struct Carro *proximo;
} Carro;

// Estrutura para armazenar os tempos de ordenação
typedef struct {
    char metodo[30];
    double tempo;
} ResultadoOrdenacao;

// Protótipos
Carro* criarLista();
Carro* inserirCarro(Carro* lista, const char* placa, const char* modelo, float valor);
void mostrarLista(Carro* lista);
void liberarLista(Carro* lista);
Carro* copiarLista(Carro* lista);
void gerarDadosAleatorios(char* placa, char* modelo, float* valor);

// Ordenações
void selectionSort(Carro* lista);
void insertionSort(Carro* lista);
void bubbleSort(Carro* lista);
void shellSort(Carro* lista);
Carro* quickSort(Carro* lista);
double medirTempo(void (*func)(Carro*), Carro* lista);

// Buscas
Carro* buscarNaLista(Carro* lista, const char* modelo);
Carro* buscarNaTabelaHash(Carro* tabelaHash[], const char* modelo);

// Tabela Hash
void criarTabelaHash(Carro* lista, Carro* tabelaHash[]);
int hash(const char* modelo);

// Função principal
int main() {
    Carro* listaOriginal = criarLista();
    Carro* tabelaHash[TAM_HASH] = {NULL};
    criarTabelaHash(listaOriginal, tabelaHash);
    ResultadoOrdenacao resultados[5] = {0};
    int resultadoIndex = 0;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Mostrar Lista Original\n");
        printf("2. Ordenar com Selection Sort\n");
        printf("3. Ordenar com Insertion Sort\n");
        printf("4. Ordenar com Bubble Sort\n");
        printf("5. Ordenar com Shell Sort\n");
        printf("6. Ordenar com Quick Sort\n");
        printf("7. Buscar Modelo\n");
        printf("8. Listar Métodos de Ordenação e Tempos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarLista(listaOriginal);
                break;
            case 2: {
                Carro* copia = copiarLista(listaOriginal);
                double tempo = medirTempo(selectionSort, copia);
                strcpy(resultados[resultadoIndex].metodo, "Selection Sort");
                resultados[resultadoIndex++].tempo = tempo;
                printf("Ordenação por Selection Sort completada em %.3lf ms.\n", tempo);
                liberarLista(copia);
                break;
            }
            case 3: {
                Carro* copia = copiarLista(listaOriginal);
                double tempo = medirTempo(insertionSort, copia);
                strcpy(resultados[resultadoIndex].metodo, "Insertion Sort");
                resultados[resultadoIndex++].tempo = tempo;
                printf("Ordenação por Insertion Sort completada em %.3lf ms.\n", tempo);
                liberarLista(copia);
                break;
            }
            case 4: {
                Carro* copia = copiarLista(listaOriginal);
                double tempo = medirTempo(bubbleSort, copia);
                strcpy(resultados[resultadoIndex].metodo, "Bubble Sort");
                resultados[resultadoIndex++].tempo = tempo;
                printf("Ordenação por Bubble Sort completada em %.3lf ms.\n", tempo);
                liberarLista(copia);
                break;
            }
            case 5: {
                Carro* copia = copiarLista(listaOriginal);
                double tempo = medirTempo(shellSort, copia);
                strcpy(resultados[resultadoIndex].metodo, "Shell Sort");
                resultados[resultadoIndex++].tempo = tempo;
                printf("Ordenação por Shell Sort completada em %.3lf ms.\n", tempo);
                liberarLista(copia);
                break;
            }
            case 6: {
                Carro* copia = copiarLista(listaOriginal);
                clock_t inicio = clock();
                copia = quickSort(copia);
                clock_t fim = clock();
                double tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
                strcpy(resultados[resultadoIndex].metodo, "Quick Sort");
                resultados[resultadoIndex++].tempo = tempo;
                printf("Ordenação por Quick Sort completada em %.3lf ms.\n", tempo);
                liberarLista(copia);
                break;
            }
            case 7: {
                char modeloBusca[20];
                printf("Digite o modelo do carro que deseja buscar: ");
                scanf("%s", modeloBusca);

                printf("\nMétodo de Busca:\n");
                printf("1. Buscar na Lista Original\n");
                printf("2. Buscar na Tabela Hash\n");
                int metodo;
                printf("Escolha uma opcao: ");
                scanf("%d", &metodo);

                if (metodo == 1) {
                    clock_t inicio = clock();
                    Carro* resultado = buscarNaLista(listaOriginal, modeloBusca);
                    clock_t fim = clock();
                    if (resultado) {
                        printf("Modelo encontrado: %s, Placa: %s, Valor: %.2f\n",
                               resultado->modelo, resultado->placa, resultado->valor);
                    } else {
                        printf("Modelo não encontrado.\n");
                    }
                    printf("Tempo de busca: %.3lf ms\n",
                           ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0);
                } else if (metodo == 2) {
                    clock_t inicio = clock();
                    Carro* resultado = buscarNaTabelaHash(tabelaHash, modeloBusca);
                    clock_t fim = clock();
                    if (resultado) {
                        printf("Modelo encontrado: %s, Placa: %s, Valor: %.2f\n",
                               resultado->modelo, resultado->placa, resultado->valor);
                    } else {
                        printf("Modelo não encontrado.\n");
                    }
                    printf("Tempo de busca: %.3lf ms\n",
                           ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0);
                } else {
                    printf("Método de busca inválido!\n");
                }
                break;
            }
            case 8:
                printf("\nResumo dos Métodos de Ordenação e Tempos:\n");
                for (int i = 0; i < resultadoIndex; i++) {
                    printf("%s: %.3lf ms\n", resultados[i].metodo, resultados[i].tempo);
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    liberarLista(listaOriginal);
    return 0;
}

// Função para criar a lista original com dados aleatórios
Carro* criarLista() {
    Carro* lista = NULL;
    for (int i = 0; i < NUM_CARROS; i++) {
        char placa[8], modelo[20];
        float valor;
        gerarDadosAleatorios(placa, modelo, &valor);
        lista = inserirCarro(lista, placa, modelo, valor);
    }
    return lista;
}

// Inserir um carro na lista
Carro* inserirCarro(Carro* lista, const char* placa, const char* modelo, float valor) {
    Carro* novo = (Carro*)malloc(sizeof(Carro));
    strcpy(novo->placa, placa);
    strcpy(novo->modelo, modelo);
    novo->valor = valor;
    novo->proximo = lista;
    return novo;
}

// Mostrar todos os elementos da lista
void mostrarLista(Carro* lista) {
    Carro* atual = lista;
    while (atual) {
        printf("Modelo: %s, Placa: %s, Valor: %.2f\n", atual->modelo, atual->placa, atual->valor);
        atual = atual->proximo;
    }
}

// Liberar memória da lista
void liberarLista(Carro* lista) {
    Carro* atual = lista;
    while (atual) {
        Carro* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

// Copiar lista
Carro* copiarLista(Carro* lista) {
    if (!lista) return NULL;
    Carro* copia = NULL;
    Carro* atual = lista;
    while (atual) {
        copia = inserirCarro(copia, atual->placa, atual->modelo, atual->valor);
        atual = atual->proximo;
    }
    return copia;
}

// Ordenação por Selection Sort
void selectionSort(Carro* lista) {
    for (Carro* i = lista; i != NULL; i = i->proximo) {
        Carro* menor = i;
        for (Carro* j = i->proximo; j != NULL; j = j->proximo) {
            if (strcmp(j->modelo, menor->modelo) < 0) {
                menor = j;
            }
        }
        if (menor != i) {
            // Trocar os dados
            char tempPlaca[8], tempModelo[20];
            float tempValor;

            strcpy(tempPlaca, i->placa);
            strcpy(tempModelo, i->modelo);
            tempValor = i->valor;

            strcpy(i->placa, menor->placa);
            strcpy(i->modelo, menor->modelo);
            i->valor = menor->valor;

            strcpy(menor->placa, tempPlaca);
            strcpy(menor->modelo, tempModelo);
            menor->valor = tempValor;
        }
    }
}

// Ordenação por Insertion Sort
void insertionSort(Carro* lista) {
    if (!lista) return;

    Carro* sorted = NULL;

    while (lista) {
        Carro* atual = lista;
        lista = lista->proximo;

        if (!sorted || strcmp(atual->modelo, sorted->modelo) < 0) {
            atual->proximo = sorted;
            sorted = atual;
        } else {
            Carro* temp = sorted;
            while (temp->proximo && strcmp(temp->proximo->modelo, atual->modelo) < 0) {
                temp = temp->proximo;
            }
            atual->proximo = temp->proximo;
            temp->proximo = atual;
        }
    }
    lista = sorted;
}

// Ordenação por Bubble Sort
void bubbleSort(Carro* lista) {
    if (!lista) return;

    int trocado;
    do {
        trocado = 0;
        Carro* atual = lista;
        while (atual->proximo) {
            if (strcmp(atual->modelo, atual->proximo->modelo) > 0) {
                // Trocar os dados
                char tempPlaca[8], tempModelo[20];
                float tempValor;

                strcpy(tempPlaca, atual->placa);
                strcpy(tempModelo, atual->modelo);
                tempValor = atual->valor;

                strcpy(atual->placa, atual->proximo->placa);
                strcpy(atual->modelo, atual->proximo->modelo);
                atual->valor = atual->proximo->valor;

                strcpy(atual->proximo->placa, tempPlaca);
                strcpy(atual->proximo->modelo, tempModelo);
                atual->proximo->valor = tempValor;

                trocado = 1;
            }
            atual = atual->proximo;
        }
    } while (trocado);
}

// Ordenação por Shell Sort
void shellSort(Carro* lista) {
    if (!lista) return;

    int tamanho = 0;
    Carro* atual = lista;

    // Contar o tamanho da lista
    while (atual) {
        tamanho++;
        atual = atual->proximo;
    }

    int gap = tamanho / 2;

    while (gap > 0) {
        for (int i = 0; i + gap < tamanho; i++) {
            Carro* elem1 = lista;
            Carro* elem2 = lista;

            for (int j = 0; j < i; j++) elem1 = elem1->proximo;
            for (int j = 0; j < i + gap; j++) elem2 = elem2->proximo;

            if (strcmp(elem1->modelo, elem2->modelo) > 0) {
                // Trocar os dados
                char tempPlaca[8], tempModelo[20];
                float tempValor;

                strcpy(tempPlaca, elem1->placa);
                strcpy(tempModelo, elem1->modelo);
                tempValor = elem1->valor;

                strcpy(elem1->placa, elem2->placa);
                strcpy(elem1->modelo, elem2->modelo);
                elem1->valor = elem2->valor;

                strcpy(elem2->placa, tempPlaca);
                strcpy(elem2->modelo, tempModelo);
                elem2->valor = tempValor;
            }
        }
        gap /= 2;
    }
}

// Ordenação por Quick Sort
Carro* quickSort(Carro* lista) {
    if (!lista || !lista->proximo) return lista;

    Carro* menor = NULL;
    Carro* maior = NULL;
    Carro* pivo = lista;
    lista = lista->proximo;
    pivo->proximo = NULL;

    while (lista) {
        Carro* atual = lista;
        lista = lista->proximo;

        if (strcmp(atual->modelo, pivo->modelo) < 0) {
            atual->proximo = menor;
            menor = atual;
        } else {
            atual->proximo = maior;
            maior = atual;
        }
    }

    menor = quickSort(menor);
    maior = quickSort(maior);

    // Conectar as listas menor, pivo, maior
    Carro* resultado = menor;
    if (resultado) {
        while (resultado->proximo) resultado = resultado->proximo;
        resultado->proximo = pivo;
    } else {
        menor = pivo;
    }
    pivo->proximo = maior;
    return menor;
}

// Função gerar dados aleatórios

void gerarDadosAleatorios(char* placa, char* modelo, float* valor) {
    // Gera uma placa no formato AAA-1234
    sprintf(placa, "AAA%d%d%d", rand() % 10, rand() % 10, rand() % 10);
    
    // Gera um modelo aleatório no formato "ModeloX", onde X é um número
    sprintf(modelo, "Modelo%d", rand() % 100);
    
    // Gera um valor de locação mensal aleatório entre 100.00 e 999.99
    *valor = (float)(rand() % 90000 + 10000) / 100.0;
}

// Busca um modelo na lista encadeada
Carro* buscarNaLista(Carro* lista, const char* modelo) {
    Carro* atual = lista;
    while (atual) {
        if (strcmp(atual->modelo, modelo) == 0)
            return atual; // Encontrado
        atual = atual->proximo;
    }
    return NULL; // Não encontrado
}

// Busca um modelo na tabela hash
Carro* buscarNaTabelaHash(Carro* tabelaHash[], const char* modelo) {
    int indice = hash(modelo);
    Carro* atual = tabelaHash[indice];
    while (atual) {
        if (strcmp(atual->modelo, modelo) == 0)
            return atual; // Encontrado
        atual = atual->proximo;
    }
    return NULL; // Não encontrado
}

// Cria a tabela hash a partir da lista de carros
void criarTabelaHash(Carro* lista, Carro* tabelaHash[]) {
    Carro* atual = lista;
    while (atual) {
        int indice = hash(atual->modelo); // Calcula o índice para o modelo
        tabelaHash[indice] = inserirCarro(tabelaHash[indice], atual->placa, atual->modelo, atual->valor);
        atual = atual->proximo;
    }
}

// Função hash para calcular o índice na tabela hash
int hash(const char* modelo) {
    int soma = 0;
    while (*modelo) {
        soma += *modelo; // Soma dos valores ASCII
        modelo++;
    }
    return soma % TAM_HASH; // Índice na tabela hash
}

// Função para medir o tempo de ordenação
double medirTempo(void (*func)(Carro*), Carro* lista) {
    clock_t inicio = clock();
    func(lista);
    clock_t fim = clock();
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
}
