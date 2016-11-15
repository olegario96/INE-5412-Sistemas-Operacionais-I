#include <iostream>
#include <stdio.h>
#include <stdlib.h>
/* ... other includes ... */
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
// Nome do aluno: Gustavo Olegário

#define N_CHILDS 7
#define BASKET 3

using namespace std;

/**
 * @brief pthread_create: see "Linux System Calls and API based on unit 'Processes and 
 *        Threads'" for more info.
 * /

/**
 * @brief pthread_join: see "Linux System Calls and API based on unit 'Processes and 
 *        Threads'" for more info.
 * /

/**
 * @brief sem_init:   this function is used to initialize the unnamed semaphore 
 *                    referred to by sem. The value of the initialized semaphore
 *                    is value. Following a successful call to sem_init, the 
 *                    semaphore may be used in subsequent calls to sem_wait 
 *                    sem_post and sem_destroy.
 * 
 * @param sem_t *sem: semaphore that will be initialized
 * 
 * @param int pshared: flag to indicate if must be shared with processes child 
 *                     or not.
 * 
 * @param value:     number of threads that can acess the critical region.
 * 
 * @return:          returns 0 on success; on error, -1 is returned and errno is 
 *                   set to indicate the error.
 * /

/**
 * @brief sem_destroy: destroys the unnamed semaphore at the address pointed by 
 *                     sem.
 * 
 * @param sem_t *sem: semaphore that will be destroyed.
 * 
 * @return:           returns 0 on success; on error, -1 is returned, and errno
 *                    is set to indicate the error.
 * /

/**
 * @brief sem_wait: decrements (locks) the semaphore pointed to by sem. The 
 *                  semaphore's value is greater than zero, then the decrement
 *                  proceeds, and the function returns, immediately. If the 
 *                  semaphore currently has the value zero, then the call blocks
 *                  until either becomes possible to perform the decrement, or 
 *                  a signal handler interrupts the call.
 * 
 * @param sem_t *sem: semaphore that will be decremented
 * 
 * @return:        Return 0 on success; on error, the value of the semaphore is 
 *                 left unchanged, -1 is returned, and errno is set to tindicate
 *                 the error.
 * /

/**
 * @brief sem_post: increments the semaphore pointed to by sem. If the semaphore 's
 *                  value consequently becomes greater than zero, then another
 *                  process or thread blocked in a sem_wait call will be up
 *                  and proceed to lock the semaphore.
 * 
 * @param sem_t *sem: semaphore that will be decremented
 * 
 * @return:        Return 0 on success; on error, the value of the semaphore is 
 *                 left unchanged, -1 is returned, and errno is set to tindicate
 *                 the error.
 * /

/* declare whenever global variables you need to synchronize pthreads using posix semaphores */
sem_t semaphore;

void *child(void *void_ptr)
{
  unsigned short *childNum = (unsigned short *)void_ptr;
  for (unsigned short i=1; i<=5; i++) {
    cout << "Child " << *childNum << " wants to play with the ball for the " << i << "th time" << endl;
    /* if the child has no ball, need to take one from the basket if there is one, or will wait until there is a ball in the basket */

    cout << " Child " << *childNum << " wants to take a ball from the basket" << endl;
    /* once the child has a ball, he/she starts to play */
    sem_wait(&semaphore);
    cout << "  Child " << *childNum << " is playing with the ball" << endl;
    /* play with the ball for 1 second */
    sleep(1);
    cout << "  Child " << *childNum << " wants to leave the ball in the basket" << endl;
    /* when the child is tired of playing, he/she has to drop the ball into the basket, if there is room for it (basket holds only 3 balls), or will wait until another hild to take a ball */
    sem_post(&semaphore);
    cout << " Child " << *childNum << " has droped the ball in the basket" << endl;
  }
  cout << "Child " << *childNum << " will no longer play" << endl;  
  /* exit the thread*/
  
}

int main()
{
    cout << "The kindengarten is open" << endl;
    /* declare local variable, such as threads */
    pthread_t threads[N_CHILDS];
    int my_vector[7];
    
    for (int i = 0; i < N_CHILDS; ++i) {
        my_vector[i] = i;
    }
    /* init semaphores to synchronize the threads */
    sem_init(&semaphore, 0, BASKET);
    /* create 7 threads for the children, passing to each one a different number (child 0 to 6) */
    for (int i = 0; i < N_CHILDS; ++i) {
        pthread_create(&threads[i], NULL, child, (void *)& my_vector[i]);
    }
    /* wait for all children to finish */
    for (int i = 0; i < N_CHILDS; ++i) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore);
    cout << "The kindengarten is closed" << endl;
    return 0;
    
    /* Respostas das perguntas "para pensar":
       1) Os semáforos podem ser variáveis locais? Todas as threads "child" 
          terminam? Justifique
          
          Não, os semáforos não podem ser variáveis locais, pois se forem, cada
          thread estará fazendo comunicação com um semaforo diferente e assim 
          não podemos fazer o controle correto. Sim todas terminam, visto que a 
          thread principal espera por todas as outras e só quando todas estão 
          juntas é que a mensagem "The kindengarten is closed" é exibida 
          finalizando o programa.
          
          2) E se no cesto couber uma única bola, como na versão original do 
          problema? Há algum erro de programação para que as threads não 
          terminem? O que poderia ser feito para detectar que um evento nunca 
          ocorrerá e fazer com que o programa finalize com sucesso, encerrando
          todas as suas threads?
          
          Sim acontecerá um problema. Pois no final quando souber três 
          crianças brincando com as três bolas, uma delas guardará a bola no 
          cesto. Quando as outras duas quiserem guardar suas bolas, elas 
          ficarão esperando eternamente por uma criança que nunca aparecerá 
          para retirar a bola do cesto e elas poderem colocar as suas. Para 
          detectar um DeadLock basta que seja criado um grafo referente ao 
          estado do programa e verificar se existe um ciclo no grafo.
          
        
    */
}
