#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define INCREMENTOS 100000

int contador = 0;                   
pthread_mutex_t mutex;             

// Função executada por cada thread
void* incremento(void* arg){
    int id = *(int*) arg;
    for(int i = 0; i < INCREMENTOS; i++){
        pthread_mutex_lock(&mutex);     // Entra na seção crítica
        contador++;                     // Incrementa o contador com proteção
        pthread_mutex_unlock(&mutex);   // Sai da seção crítica
    }
    printf("Thread %d terminou\n", id);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);   // Inicializa o mutex

    // Cria as threads
    for(int i = 0; i < NUM_THREADS; i++){
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, incremento, &ids[i]);
    }

    // Aguarda o término das threads
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);      // Destrói o mutex

    printf("\nValor final do contador: %d (esperado: %d)\n",contador, NUM_THREADS * INCREMENTOS);

    return 0;
}
