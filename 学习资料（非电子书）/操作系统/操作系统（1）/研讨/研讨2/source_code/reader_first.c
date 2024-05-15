#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define P sem_wait
#define V sem_post
#define rw &rw_
#define mutex &mutex_

const int READER_NUM = 2;
const int WRITER_NUM = 20;
const double SLEEP_TIME = 1;
sem_t rw_;
sem_t mutex_;

static int readercount = 0;

void *reader(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        P(mutex);
        if (readercount == 0) // 第一个读进程负责加锁
            P(rw);
        readercount++;
        V(mutex);
        
        printf("%d号读者读取\n", id);

        P(mutex);
        readercount--;
        if (readercount == 0)
            V(rw);
        V(mutex);
    }
}
void *writer(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        // sleep(1);
        P(rw);
        // sleep(SLEEP_TIME);
        printf("%d号写者修改\n", id);
        V(rw);
    }
}

int main()
{
    sem_init(rw, 0, 1);
    sem_init(mutex, 0, 1);

    pthread_t readers[READER_NUM];
    pthread_t writers[WRITER_NUM];

    
    
    for (int i = 0; i < WRITER_NUM; i++)
    {
        pthread_create(&writers[i], NULL, writer, &i);
    }

    for (int i = 0; i < READER_NUM; i++)
    {
        pthread_create(&readers[i], NULL, reader, &i);
    }
    pthread_exit(0);

    return 0;
}
