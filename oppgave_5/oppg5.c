#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct _BUFFER {
    char szBuffer[11];
    FILE *f;
} BUFFER;


pthread_mutex_t pmMux1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pmMux2 = PTHREAD_MUTEX_INITIALIZER;

void *workerThread(void *buffer) {
    
    BUFFER *pBuf = (BUFFER*) buffer;
    int i = 0;
    while(1) {
        pthread_mutex_lock(&pmMux2);
        pthread_mutex_lock(&pmMux1);

        // fprintf(pBuf->f, "%s", pBuf->szBuffer);
        printf("worker thread unlocked #%d\n", i);

        pthread_mutex_unlock(&pmMux1);
        pthread_mutex_unlock(&pmMux2);
        i++;
    }
    
    return NULL;
}

int main(int argc, char *argv[]) {

    char szUserInput[255] = "";

    size_t nRead;

    FILE *f = NULL;

    f = fopen("text.txt", "w");

    pthread_t tWorker;

    // Create buffer
    BUFFER *pBuf = malloc(sizeof(BUFFER));
    pBuf->f = f;

    pthread_mutex_lock(&pmMux1);

    // Start thread
    pthread_create(&tWorker, NULL, workerThread, (void *) pBuf);

    while(1) {
        fgets(szUserInput, 255, stdin);

        int iStart = 0;

        while(iStart <= (strlen(szUserInput) - 1)) {
            strncpy(pBuf->szBuffer, &szUserInput[iStart], 10);
            pBuf->szBuffer[10] = 0;
            
            pthread_mutex_unlock(&pmMux1);
            
            iStart += 10;

            pthread_mutex_lock(&pmMux2);
            pthread_mutex_lock(&pmMux1);
            pthread_mutex_unlock(&pmMux2);
        }
    }

    // Terminate thread and close file
    pthread_join(tWorker, NULL);
    fclose(f);

    return 0;
}