#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define N_RESOURCES 3

sem_t resources[N_RESOURCES];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* process(void* arg) {
    int id = *(int*)arg;

    // Request resources in increasing order
    for (int i = 0; i < N_RESOURCES; i++) {
        sem_wait(&resources[i]);
        cout << "Process " << id << " acquired Resource " << i << endl;
        sleep(1);
    }

    cout << "\tProcess " << id << " doing its job...\n";
    sleep(2);

    // Release resources in reverse order
    for (int i = N_RESOURCES - 1; i >= 0; i--) {
        sem_post(&resources[i]);
        cout << "Process " << id << " released Resource " << i << endl;
    }

    return nullptr;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    for (int i = 0; i < N_RESOURCES; i++) {
        sem_init(&resources[i], 0, 1);
    }

    pthread_create(&t1, nullptr, process, &id1);
    pthread_create(&t2, nullptr, process, &id2);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    for (int i = 0; i < N_RESOURCES; i++) {
        sem_destroy(&resources[i]);
    }

    return 0;
}
