#include <stdio.h>
#include <pthread.h>

#define TAR_VET 100000
#define QTD_THREADS 4

int id[QTD_THREADS];
int vetor[TAR_VET];
int resultado = 0;

void * funcao(void * args)
{
    int id = *((int *)args);
    int intervalo = TAR_VET/QTD_THREADS;
    int soma = 0;
    for(int i = id*intervalo; i < (id+1)*intervalo; i++)
    {
        soma += vetor[i];
    }
    resultado += soma;
}

int main()
{
    for(int i = 0; i< TAR_VET; i++)
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
    
    printf("Resultado: %d\n", resultado);
    
    return 0;
}