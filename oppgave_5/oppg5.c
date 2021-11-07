#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define USERINPUT_BUFFER 4096

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

        // Wait for signal to execute work
        sem_wait(&pBuf->semNewTask);

        // Exit the while loop if exit variable in struct is not 0
        if(pBuf->iExitProgram != 0) {
            break;
        }

        fprintf(pBuf->f, "%s", pBuf->szBuffer);
        //fflush(pBuf->f);

        sem_post(&pBuf->semTaskCompleted);
    }
    
    return NULL;
}

int main(int argc, char *argv[]) {


    char szUserInput[USERINPUT_BUFFER] = "";

    FILE *f = NULL;
    f = fopen("text.txt", "a"); // Can use "w" to start the file as blank each time you run the program

    // Create buffer
    BUFFER *pBuf = malloc(sizeof(BUFFER));
    pBuf->f = f;
    pBuf->iExitProgram = 0;

    // Init semaphore
    sem_init(&pBuf->semNewTask, 0, 0);
    sem_init(&pBuf->semTaskCompleted, 0, 0);

    // Create thread
    pthread_t tWorker;

    // Start thread
    pthread_create(&tWorker, NULL, workerThread, (void *) pBuf);

    printf("Skriv tekststrenger adskilt med ENTER tast (tast 'quit' for å avlsutte programmet): \n");
    while(pBuf->iExitProgram == 0) {
        char *pszReturn = fgets(szUserInput, USERINPUT_BUFFER, stdin);

        if (strcmp(szUserInput, "quit\n") != 0) {

            int iStart = 0;

            while(iStart <= (strlen(szUserInput) - 1)) {
                strncpy(pBuf->szBuffer, &szUserInput[iStart], 10);
                pBuf->szBuffer[10] = 0;
                
                sem_post(&pBuf->semNewTask);
                sem_wait(&pBuf->semTaskCompleted);
                
                iStart += 10;
                
            }
        } else {
            pBuf->iExitProgram = 1;

            sem_post(&pBuf->semNewTask);
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