#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct node
{
    char *dado;
    Node *prox;
};

struct queue
{
    Node *fim;
    Node *ini;
    int tamanho;
};

Queue *queue_cria(void)
{
    Queue *f = (Queue *)malloc(sizeof(Queue));
    if (f == NULL)
    {
        printf("[Erro] memoria.\n");
        exit(1);
    }
    f->fim = NULL;
    f->ini = NULL;
    f->tamanho = 0;
    return f;
}

void queue_insere(Queue *f, char *line)
{
    Node *novo = (Node *)malloc(sizeof(Node));
    if (novo == NULL)
    {
        printf("[Erro] memoria.\n");
        exit(1);
    }
    novo->dado = line;
    novo->prox = NULL;
    if (f->fim != NULL)
        f->fim->prox = novo;
    else
        f->ini = novo;
    f->fim = novo;
    f->tamanho++;
}

char *queue_retira(Queue *f)
{
    if (queue_vazia(f))
    {
        return NULL;
    }
    Node *l = f->ini;
    char *line = f->ini->dado;
    f->ini = f->ini->prox;
    if (f->ini == NULL)
        f->fim = NULL;
    f->tamanho--;
    free(l);
    return line;
}

void queue_imprime(Queue *f)
{
    Node *l;
    int i = 1;
    for (l = f->ini; l != NULL; l = l->prox)
    {
        printf("\nLinha %d: %s", i, l->dado);
        i++;
    }
}

void queue_libera(Queue *f)
{
    Node *p = f->ini;
    while (p != NULL)
    {
        Node *t = p->prox;
        free(p->dado);
        free(p);
        p = t;
    }
    free(f);
}

int queue_vazia(Queue *f)
{
    if (f->tamanho == 0)
        return 1;
    return 0;
}