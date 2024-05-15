#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define P sem_wait
#define V sem_post
#define rw &rw_
#define reader_mutex &reader_mutex_
#define writer_mutex &writer_mutex_
#define read &read_


const int READER_NUM = 20;
const int WRITER_NUM = 2;
const double SLEEP_TIME = 1;

sem_t rw_;
sem_t reader_mutex_;
sem_t writer_mutex_;
sem_t read_;

static int readercount = 0;
static int writercount = 0;

void *reader(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        P(read); // 申请读取权限

        // 互斥操作访问readercount 
        P(reader_mutex); 
        if (readercount == 0)
            P(rw);
        readercount++;

        V(reader_mutex);
        printf("%d号读者读取\n", id);
        sleep(SLEEP_TIME);
        P(reader_mutex);
        
        // 互斥操作访问readercount 
        readercount--;
        if (readercount == 0)
            V(rw);
        V(reader_mutex);
    }
}

void *writer(void *arg)
{
    int id = *((int *)arg);

    while (1)
    {
        // 写进程互斥访问writercount 写队列中有写进程则不给read权限
        P(writer_mutex);
        if(writercount != 0)
            P(read);
        writercount++;
        V(writer_mutex);


        P(rw);
        printf("%d号写者修改\n", id);
        V(rw);

        // 写进程互斥访问writercount
        P(writer_mutex);
        writercount--;
        if(writercount != 0)
            V(read);
        V(writer_mutex);
    }
}

int main()
{
    // 初始化信号量
    sem_init(rw, 0, 1);
    sem_init(reader_mutex, 0, 1);
    sem_init(writer_mutex, 0, 1);
    sem_init(read, 0, 1);

    // 初始化读者、写者
    pthread_t readers[READER_NUM];
    pthread_t writers[WRITER_NUM];

    for (int i = 0; i < READER_NUM; i++)
    {
        pthread_create(&readers[i], NULL, reader, &i);
    }
    
    for (int i = 0; i < WRITER_NUM; i++)
    {
        pthread_create(&writers[i], NULL, writer, &i);
    }

    pthread_exit(0);

    return 0;
}
