#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

typedef struct _BUFFER {
    char szBuffer[11];
    FILE *f;
    sem_t semNewTask;
    sem_t semTaskCompleted;
    int iExitProgram;
} BUFFER;

void *workerThread(void *buffer) {
    
    BUFFER *pBuf = (BUFFER*) buffer;
    while(pBuf->iExitProgram == 0) {

        sem_wait(&pBuf->semNewTask);

        if(pBuf->iExitProgram != 0) {
            break;
        }

        fprintf(pBuf->f, "%s", pBuf->szBuffer);
        //fflush(pBuf->f);

        sem_post(&pBuf->semTaskCompleted);
    }
    
    printf("Worker finished \n");

    return NULL;
}

int main(int argc, char *argv[]) {


    char szUserInput[255] = "";

    FILE *f = NULL;

    f = fopen("text.txt", "a");

    pthread_t tWorker;

    // Create buffer
    BUFFER *pBuf = malloc(sizeof(BUFFER));
    pBuf->f = f;
    pBuf->iExitProgram = 0;

    // Init semaphore
    sem_init(&pBuf->semNewTask, 0, 0);
    sem_init(&pBuf->semTaskCompleted, 0, 0);


    // Start thread
    pthread_create(&tWorker, NULL, workerThread, (void *) pBuf);

    while(pBuf->iExitProgram == 0) {
        printf("Skriv en tekststreng (tast 'quit' for å avlsutte programmet) \n");
        fgets(szUserInput, 255, stdin);
        if(strlen(szUserInput) > 1) {
            szUserInput[strlen(szUserInput) - 1] = 0;

            if (strcmp(szUserInput, "quit") != 0) {

                int iStart = 0;

                while(iStart <= (strlen(szUserInput) - 1)) {
                    strncpy(pBuf->szBuffer, &szUserInput[iStart], 10);
                    pBuf->szBuffer[10] = 0;
                    
                    sem_post(&pBuf->semNewTask);
                    sem_wait(&pBuf->semTaskCompleted);
                    
                    iStart += 10;
                    
                }

                strcpy(pBuf->szBuffer, "\n");

                sem_post(&pBuf->semNewTask);
                sem_wait(&pBuf->semTaskCompleted);

            } else {
                pBuf->iExitProgram = 1;

                sem_post(&pBuf->semNewTask);
            } 
        }

    }

    // Terminate thread and close file
    pthread_join(tWorker, NULL);
    fclose(f);

    // Destroy semaphores and free allocated buffer
    sem_destroy(&pBuf->semNewTask);
    sem_destroy(&pBuf->semTaskCompleted);
    free(pBuf);

    return 0;
}