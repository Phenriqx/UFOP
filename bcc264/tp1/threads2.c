#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_ITERACOES 1000000

int contador_global = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* minha_thread(void* arg) {
    for (int i = 0; i < NUM_ITERACOES; i++) {
        pthread_mutex_lock(&mutex);
        contador_global++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* minha_thread2(void* arg) {
    for (int i = 0; i < NUM_ITERACOES; i++) {
        pthread_mutex_lock(&mutex);

        if ((i % 2) == 0 )
            contador_global++;
        
        else 
            contador_global--;

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, minha_thread, NULL) != 0) {
            perror("Erro ao criar a thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor final do contador_global: %d\n", contador_global);

    pthread_mutex_destroy(&mutex);

    return 0;
}

