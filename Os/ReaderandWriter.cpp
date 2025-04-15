#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t rw_mutex;
sem_t mutex;
int read_count = 0;
int shared_data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    while (true) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Reading section
        cout << "Reader " << id << " reads data = " << shared_data << endl;

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        sleep(2);
    }
    return nullptr;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (true) {
        sem_wait(&rw_mutex);

        // Writing section
        shared_data++;
        cout << "\tWriter " << id << " writes data = " << shared_data << endl;

        sem_post(&rw_mutex);
        sleep(3);
    }
    return nullptr;
}

int main() {
    pthread_t r1, r2, w1;

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    int r_id1 = 1, r_id2 = 2, w_id = 1;

    pthread_create(&r1, nullptr, reader, &r_id1);
    pthread_create(&r2, nullptr, reader, &r_id2);
    pthread_create(&w1, nullptr, writer, &w_id);

    pthread_join(r1, nullptr);
    pthread_join(r2, nullptr);
    pthread_join(w1, nullptr);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
