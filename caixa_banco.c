#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cliente {
    char nome[50];
    int operacao; // 1: Saque, 2: Depósito, 0: Atendimento com gerente
    float valor;
    struct Cliente* proximo;
} Cliente;

typedef struct Fila {
    Cliente* inicio;
    Cliente* fim;
} Fila;

// Inicializa a fila
void inicializar_fila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Enfileira um cliente
void enfileirar(Fila* f, Cliente* cl) {
    cl->proximo = NULL;
    if (f->fim == NULL) {
        f->inicio = cl;
    } else {
        f->fim->proximo = cl;
    }
    f->fim = cl;
}

// Desenfileira um cliente
Cliente* desenfileirar(Fila* f) {
    if (f->inicio == NULL) {
        return NULL;
    }
    Cliente* temp = f->inicio;
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    return temp;
}

// Verifica se a fila está vazia
int fila_vazia(Fila* f) {
    return f->inicio == NULL;
}

// Mostra todos os clientes na fila
void mostrar_fila(Fila* f) {
    Cliente* atual = f->inicio;
    while (atual != NULL) {
        printf("Nome: %s, Operacao: %d, Valor: %.2f\n", atual->nome, atual->operacao, atual->valor);
        atual = atual->proximo;
    }
}

// Exercício 1: Distribuir fichas para atendimento de clientes no caixa
void atender_caixa(Fila* fila_prioritaria, Fila* fila_geral, const char* nome, int operacao, float valor, int prioritario) {
    Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
    strcpy(novo_cliente->nome, nome);
    novo_cliente->operacao = operacao;
    novo_cliente->valor = valor;
    if (prioritario) {
        enfileirar(fila_prioritaria, novo_cliente);
    } else {
        enfileirar(fila_geral, novo_cliente);
    }
}

// Exercício 2: Atendimento com o gerente
void atender_gerente(Fila* fila_prioritaria_gerente, Fila* fila_geral_gerente, const char* nome, int prioritario) {
    Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
    strcpy(novo_cliente->nome, nome);
    novo_cliente->operacao = 0;
    novo_cliente->valor = 0.0;
    if (prioritario) {
        enfileirar(fila_prioritaria_gerente, novo_cliente);
    } else {
        enfileirar(fila_geral_gerente, novo_cliente);
    }
}

// Exercício 3: Exibir quadro com números dos últimos atendidos
void exibir_quadro(Fila* fila_prioritaria_caixa, Fila* fila_geral_caixa, Fila* fila_prioritaria_gerente, Fila* fila_geral_gerente) {
    printf("Atendimento Caixa:\n");
    if (!fila_vazia(fila_prioritaria_caixa)) {
        printf("Prioritário Caixa Nº: %s\n", fila_prioritaria_caixa->inicio->nome);
    }
    if (!fila_vazia(fila_geral_caixa)) {
        printf("Geral Caixa Nº: %s\n", fila_geral_caixa->inicio->nome);
    }
    printf("Atendimento Gerente:\n");
    if (!fila_vazia(fila_prioritaria_gerente)) {
        printf("Prioritário Gerente Nº: %s\n", fila_prioritaria_gerente->inicio->nome);
    }
    if (!fila_vazia(fila_geral_gerente)) {
        printf("Geral Gerente Nº: %s\n", fila_geral_gerente->inicio->nome);
    }
}

// Exercício 4: Chamar clientes conforme as regras
void chamar_clientes(Fila* fila_prioritaria, Fila* fila_geral) {
    static int cont_prioritario = 0;
    Cliente* cliente_chamado;
    if (cont_prioritario < 2 && !fila_vazia(fila_prioritaria)) {
        cliente_chamado = desenfileirar(fila_prioritaria);
        cont_prioritario++;
    } else if (!fila_vazia(fila_geral)) {
        cliente_chamado = desenfileirar(fila_geral);
        cont_prioritario = 0;
    } else if (!fila_vazia(fila_prioritaria)) {
        cliente_chamado = desenfileirar(fila_prioritaria);
        cont_prioritario = 1;
    } else {
        printf("Nenhum cliente na fila.\n");
        return;
    }
    printf("Chamado: %s\n", cliente_chamado->nome);
    free(cliente_chamado);
}

// Exercício 5: Registro de log de atendimento e operações de caixa
void registrar_log(Fila* fila_log, Cliente* cliente) {
    Cliente* log_entry = (Cliente*)malloc(sizeof(Cliente));
    strcpy(log_entry->nome, cliente->nome);
    log_entry->operacao = cliente->operacao;
    log_entry->valor = cliente->valor;
    enfileirar(fila_log, log_entry);
}

void processar_caixa(Fila* fila_caixa, float* saldo) {
    Cliente* cliente = desenfileirar(fila_caixa);
    if (cliente == NULL) return;
    
    if (cliente->operacao == 1) { // Saque
        *saldo -= cliente->valor;
    } else if (cliente->operacao == 2) { // Depósito
        *saldo += cliente->valor;
    }
    printf("Novo saldo do caixa: %.2f\n", *saldo);
    free(cliente);
}

int main() {
    Fila fila_prioritaria_caixa, fila_geral_caixa;
    Fila fila_prioritaria_gerente, fila_geral_gerente;
    Fila log_caixa, log_gerente;
    inicializar_fila(&fila_prioritaria_caixa);
    inicializar_fila(&fila_geral_caixa);
    inicializar_fila(&fila_prioritaria_gerente);
    inicializar_fila(&fila_geral_gerente);
    inicializar_fila(&log_caixa);
    inicializar_fila(&log_gerente);

    float saldo_caixa = 1000.0;
    // Aqui você pode adicionar chamadas de exemplo para os exercícios, simulando os atendimentos.

    return 0;
}
