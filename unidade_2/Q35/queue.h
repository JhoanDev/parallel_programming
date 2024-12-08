#ifndef QUEUE_H
#define QUEUE_H

typedef struct node Node;
typedef struct queue Queue;

//cria fila
Queue *queue_cria(void);

// insere valor
void queue_insere(Queue *f, char *line);

// retira valor
char *queue_retira(Queue *f);

// verifica se a queue esta vazia
int queue_vazia(Queue *f);

// imprime a queue
void queue_imprime(Queue *f);

// libera a memoria
void queue_libera(Queue *f);

#endif //QUEUE_H