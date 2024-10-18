#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM_VET 100000
#define QTD_THREADS 4

int id[QTD_THREADS];
int vetor[TAM_VET];
int resultado = 0;

pthread_mutex_t mutex;

void * funcao(void * args)
{
    int id = *((int *)args);
    int intervalo = TAM_VET/QTD_THREADS;
    int soma = 0;
    for(int i = id*intervalo; i < (id+1)*intervalo; i++)
    {
        soma += vetor[i];
    }
    pthread_mutex_lock(&mutex);
    resultado += soma;
    pthread_mutex_unlock(&mutex);
}

int main()
{    
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < TAM_VET; i++)
    {
        vetor[i] = i;
    }
    for(int i = 0; i < QTD_THREADS; i++)
    {
        id[i] = i;
    }
    pthread_t threads[QTD_THREADS];
    for(int i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, funcao, &id[i]);
    }
    for(int i = 0; i < QTD_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Resultado: %d\n", resultado);
    
    return 0;
}
