#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct livro{   //dados do Livro livro
    char autor [20];
    char titulo [40];
    int ano;
    int id;
    struct livro *proximo;
}Livro;


typedef struct pilha{   //atributos de pilha
    Livro *topo;
    int qtd;
    int max_qtd;
}Pilha;

Pilha* criaPilha(){
    //cria estrutura para pilha
    Pilha *p  = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->qtd = 0;
    return p;
}

Livro* criaLivroPilha(int id, int ano, char at [] , char tit [] ){
    //cria um Livro de pilha
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    novoLivro->proximo = NULL;
    novoLivro->ano = ano;
    strcpy(novoLivro->autor,at);
    strcpy(novoLivro->titulo,tit);
    novoLivro->id = id;
    return novoLivro;
}


void push(Pilha *p, Livro *lv){
    //empura um Livro na pilha
    lv->proximo = p->topo;
    p->topo = lv;
    p->qtd++;
}

Livro* pop(Pilha *p){
    //salta um Livro da pilha
    Livro *aux = p->topo;
    if(aux != NULL){
        p->topo = p->topo->proximo;
        p->qtd--;
        aux->proximo = NULL;
    }
    return aux;
}

void mostraLivroPilha(Livro lv){
    printf("\n\t %d - Titulo: %s \n\t Autor: %s \n\t Ano: %d \n",lv.id,lv.titulo,lv.autor,lv.ano);
}

void mostraTopo(Pilha *p){
    if(p->topo != NULL){
        printf("\n Mostra TOPO - Pilha");
        mostraLivroPilha(*p->topo);
    }else{
        printf("\n TOPO NULO - Pilha Vazia \n");
    }
}


void apagaPilha(Pilha *p){
    //apaga os Livros da pilha
    while(p->topo !=NULL){
        free(pop(p));
    }
    mostraTopo(p);
}


void mostraPilha(Pilha p){
    Livro *aux = p.topo;
    if(aux == NULL)
        printf("\n  -- Pilha Vazia!!\n");
    else
        while(aux !=NULL){
            mostraLivroPilha(*aux);
            aux = aux->proximo;
        }
}

Pilha* invertePilhaNova(Pilha *p1){
    //Inverte pilha p1 e retorna a nova pilha
    Pilha *nova = criaPilha();

    Livro *aux = pop(p1);

    while(p1->topo != NULL) {
        aux = pop(p1);
        push(nova, aux);
    }

    return nova;
   

}


void invertePropriaPilha(Pilha *p1){
    //Inverte A PROPRIA pilha p1 

    /* inverte, mas altera memory adress
        Pilha *temp = invertePilhaNova(p1);

        *p1 = *temp;
        free(temp);
    */

   if(p1->topo == NULL || p1->topo->proximo == NULL)
    return; // valida se nao ha nada para inverter

   Livro *prev = NULL;
   Livro *current = p1->topo;
   Livro *next = NULL;

   while(current != NULL){
    next = current->proximo; // salva prox nó
    current->proximo = prev; // inverte pointeiro do nó atual
    prev = current; // avança o ponteiro 'prev'
    current = next; // avança o ponteiro 'current'
   }

   p1->topo = prev;
}

Pilha* copiaPilha(Pilha *p1){
    Pilha *copia = criaPilha();
    Livro *aux = p1->topo;
    Livro *livrosTemp[p1->qtd];

    int i = 0;

    while (aux != NULL){
        livrosTemp[i++] = criaLivroPilha(aux->id, aux->ano, aux->autor, aux->titulo);

        aux = aux->proximo;
    }

    for(int j = i -1; j >= 0; j--){
        push(copia, livrosTemp[j]);
    }

    return copia;

}

// Pilha* copiaPilha(Pilha *p1);
    //Copia a pilha 1 para uma nova e mantem a ordem de p1

    

void menu(Pilha *p1, Pilha *p2, int ct){
    int op, posicao;
    Pilha *nova;
    Livro *lv;
    char ch;
    int ano;
    char titulo[20], autor[20];
    do{
        printf("\n\nInforme uma Opção:");
        printf("\n -- 1 - PUSH:");
        printf("\n -- 2 - POP:");
        printf("\n -- 3 - Mostra TOPO:");   
        printf("\n -- 4 - Mostrar Pilha:");
        printf("\n -- 5 - Apagar Pilha:");
        printf("\n -- 6 - Inverte Pilha:");
        printf("\n -- 7 - Inverte Propria Pilha");
        printf("\n -- 8 - Copia Pilha");
        printf("\n -- 0 - Sair do Programa:\n");
        printf("\nInforme sua Opçao:");
        scanf("%d",&op);
        fflush(stdin);
        
        switch(op){
            case 1:                
                printf("\n Função PUSH. \n");
                printf("Informe o Titulo do Livro:");
                scanf("%s",titulo);
                printf("Informe o Autor:");
                scanf("%s",autor);
                printf("Informe o Ano:");
                scanf("%d",&ano);
                push(p1,criaLivroPilha(ct++,ano,autor,titulo));
                printf("\n Inserção Realizada com Sucesso");
             
            break;
            case 2:
                printf("\n Função POP. \n");
                lv = pop(p1);
                if(lv!=NULL){
                    mostraLivroPilha(*lv);
                    printf("\n --- Remoção Realizada com Sucesso!!");
                }else{
                    printf("\n --- ERRO - Remoção inválida!!");
                }               
            break;
            case 3:                
                printf("Mostra TOPO Pilha:");
                mostraTopo(p1);
            break;
            case 4:
                printf("\nMostra Pilha:");
                mostraPilha(*p1);
            break;
            case 5:
                printf("\n Apagar a Pilha !! \n");
                apagaPilha(p1);
            break;
            case 6:
                printf("Inverte Pilha");
                printf("\n Pilha 1 :");
                mostraPilha(*p1);
                printf("\n Pilha P1 - Invertida :");
                invertePilhaNova(p1);                
                mostraPilha(*p1);
            break;

            case 7:
                printf("Inverte NOVA Pilha");
                printf("\n Pilha 1 :");
                mostraPilha(*p1);
                printf("\n Pilha P2 - Invertida :");
                invertePropriaPilha(p1);               
                mostraPilha(*p1);
            break;

            case 8: 
                printf("Copia Pilha");
                printf("\n Pilha 1:");
                mostraPilha(*p1);
                printf("\n Pilha P2 - Copiada");
                copiaPilha(p1);
                mostraPilha(*p1);
            break;

            default:
                printf("\nFim do programa!!\n");
        }
       
    
    }while(op>0);
}

int main(){

    Pilha *p1,*p2;
    Livro *l1, *l2, *l3, *l4;

    p1 = criaPilha(); //pilha end X
    p2 = criaPilha();

    int ct =1;
    
    time_t inicio, fim;


    l1 = criaLivroPilha(ct++,2016,"Paul Deitel and  Harvey Deitel","Java: Como Programar");
    l2 = criaLivroPilha(ct++,2006,"H. M. Deitel","C++: Como Programar 5°Ed.");
    l3 = criaLivroPilha(ct++,2016,"Allen B. Downey","Pense em Python:");   
    l4 = criaLivroPilha(ct++,2010,"Josh Lockhart","PHP Moderno: Novos Recursos e Boas Práticas");   

    push(p1,l1);
    push(p1,l2);
    push(p1,l3);
    push(p1,l4);

    time(&inicio);
    menu(p1,p2,ct);
    
    time(&fim);

    double tempo = difftime(fim,inicio);

    printf("\n Tempo de Uso foi %lf\n",tempo);
    exit(0);
}


