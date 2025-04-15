#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5

queue<int> buffer;
sem_t emptySlots;
sem_t fullSlots;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item = 0;
    while (true) {
        item++;
        sem_wait(&emptySlots);
        pthread_mutex_lock(&mutex);

        buffer.push(item);
        cout << "Producer produced: " << item << endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&fullSlots);
        sleep(1);
    }
    return nullptr;
}

void* consumer(void* arg) {
    while (true) {
        sem_wait(&fullSlots);
        pthread_mutex_lock(&mutex);

        int item = buffer.front();
        buffer.pop();
        cout << "\tConsumer consumed: " << item << endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&emptySlots);
        sleep(2);
    }
    return nullptr;
}

int main() {
    pthread_t prod, cons;

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&mutex, nullptr);

    pthread_create(&prod, nullptr, producer, nullptr);
    pthread_create(&cons, nullptr, consumer, nullptr);

    pthread_join(prod, nullptr);
    pthread_join(cons, nullptr);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
