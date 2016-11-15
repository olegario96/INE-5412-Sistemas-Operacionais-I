#include <iostream>
#include <pthread.h>
//nome do aluno: Gustavo Olegário

/**
 * @brief   pthread_mutex_init: shall initialize the mutex referenced by mutex
 *          with attributes specified by attr. If attr is NULL, the default 
 *          attributes are used. the effect shall be the same as passing the 
 *          addres of a default mutex attribues object.
 * 
 * @param   pthread_mutex_t *mutex: variable that will be initialized.
 * 
 * @return  If successful, shall return zero; otherwise, an error number shall
 *          be returned to indicate the error.
 * 
 */
 
 /**
 * @brief   pthread_mutex_lock: the mutex object referencd by mutex shall be 
 *          locked by calling pthread_mutex_lock(). If the mutex is already 
 *          locked, the calling thread shall block until the mutex becomes 
 *          available.This operation shall return with the mutex object 
 *          referenced by mutex in the locked state with the calling thread as 
 *          its owner.
 * 
 * @param   pthread_mutex_t *mutex: mutex that the thread will try to lock.
 * 
 * @return  If successful, the pthread_mutex_lock() shall return zero; otherwise, 
 *          an error number is returned to indicate the error.
 * 
 */
 
 /**
 * @brief    pthread_mutex_unlock: function shall release the mutex object 
 *           referenced by mutex. The manner in which a mutex is released is 
 *           dependent upon the mutex's type attribute. If there are threads 
 *           blocked on the mutex object referenced by mutex when pthread_mutex_
 *           unlock is called, resulting inn the mutex becoming available, the 
 *           scheduling policy immediately return sucess.
 * 
 * @param   pthread_mutex_t *mutex: mutex that the thread will try to unlock.
 * 
 * @return  If successful, the pthread_mutex_unlock() shall return zero; otherwise, 
 *          an error number is returned to indicate the error.
 *  
 */
 
 /**
 * @brief   pthread_mutex_destroy: function shall destroy the mutex object  
 *          referenced by mutex. The mutex object becomes, in effect, 
 *          unintialized. An implementation may cause pthread_mutex_destroy() to 
 *          set the object referenced by mutex to an invalide value. A destroyed
 *          mutex object can be reinitialized using pthread_mutex_init
 * 
 * @param   pthread_mutex_t *mutex: variable that will be destroyed.
 * 
 * @return  If successful, shall return zero; otherwise, an error number shall
 *          be returned to indicate the error.
 * 
 */
 
 /**
 * @brief    pthread_create: the pthread_create function starts a new thread in 
 *           the process. the new thread stars execution by invoking 
 *           start_routine(); arg is passed as the sole argumente of
 *           start_rountine()
 * 
 * @param    pthread_t *thread: thread that will execute the routine
 * 
 * @param    const pthread_attr_t *attr: used to set up attributes from the 
 *           thread. If not used, set as NULL
 * 
 * @param    void *(*start_routine) (void *): rountine that the thread will 
 *           will execute
 * 
 * @param    void *arg: arguments used on the start_routine
 * 
 * @return   on success, pthread_create returns 0; on error, it returns an error
 *           number, and the contents of *thread are undefined.
 */
 
 /**
 * @brief   pthread_join: supsends execution of the calling thread until the 
 *          target thread terminates, unless the target thread has already 
 *          terminated. On return from a successful pthread_join call with a 
 *          non_NULL value_ptr argument, the value passed to pthread_exit by 
 *          the terminating thread is made available in the location referenced
 *          value_ptr.
 * 
 * @param   pthread_t thread: thread that the thread calling pthread_join will
 *          wait. 
 * 
 * @param   void **value_ptr: variable that will store the value returned by 
 *          the function pthread_exit. Normally, NULL is used if dont wanna store
 *          the value.
 * 
 * @return  if successful, the pthread_join funciont returns zero. Otherwise, an 
 *          error number is returned to indicate the error.
 * 
 */
 
 


using namespace std;

/* declare a mutex */
pthread_mutex_t mymutex;



void *inc_(void *void_ptr)
{
  /* increment x to 100 */
  pthread_mutex_lock(&mymutex);
  int *ptr = (int *)void_ptr;
  for (int i = 0; i < 100; ++i) 
  {
    /* enter critical region */
    ++(*ptr);
    /* leave critical region */
  }
  pthread_mutex_unlock(&mymutex);
  cout << "increment finished" << endl;
  return NULL;
}

void *dec_(void *void_ptr)
{
    /* decrement x to 100 */
    pthread_mutex_lock(&mymutex);
    int *ptr = (int *)void_ptr;
  for (int i = 0; i < 100; ++i)
  {
    /* enter critical region */
    --(*ptr);
    /* leave critical region */
  }
  pthread_mutex_unlock(&mymutex);
    cout << "decrement finished" << endl;
    return NULL;
}


int main()
{
  int x = 0;
  cout << "x: " << x << endl;
  /* declare threads */ 
  pthread_t inc_thread, dec_thread;
  /* init mutexex */
  pthread_mutex_init(&mymutex, NULL);
    /* create a first thread which executes inc_(&x) */
    pthread_create(&inc_thread, NULL, inc_, (void *)& x);
  /* create a second thread which executes dec_(&x) */
    pthread_create(&dec_thread, NULL, dec_, (void *)& x);
    /* wait for the first thread to finish */
    pthread_join(inc_thread, NULL);
  /* wait for the second thread to finish */
    pthread_join(dec_thread, NULL);
  /* destroy miutex */
  pthread_mutex_destroy(&mymutex);

  cout << "x: " << x << endl;
  return 0;
}

/* Respostas do "Para pensar e responder junto ao código:"
   1) Na implementação computacional da Unidade 1, o que acontecia com a variá-
   vel global count quando ela era incrementada pelos diferentes processos?
   
   Naquela implementação de, como se tratavam de processos e não de threads, 
   cada um tinha a sua cópia privada de count. Dessa maneira, não tínhamos que
   nos preocupar com a condição de corrida. Cada processo fazia seu incremento e
   no final o processo pai fazia a soma final.
   
   2) O mesmo vai acontecer agora quando a variável global x for incrementada
   e decrementada pelas diferentes threads?
   
   Não, pois como threads utilizam memória compartilhada, temos que nos 
   preocupar com regiões críticas e condições de corrida. Dessa forma, 
   utilizando o mutex, nós temos que garantir que uma única thread faça um 
   acesso controlado a váriavel x, uma vez que uma mudança nessa variável sem 
   controle pode afetar o objetivo do nosso programa.
   
   3) Qual é o valor esperado para a variável x após o término do aplicativo?
   Se não houver mutex, qual será o valor final da variável global x (ou sua
   distribuição de probabilidade)?
   
   0. No caso em que há a condição de corrida, sem proteção de mutex ou 
   semáforo, nada se pode afirmar sobre o valor de x. Pois uma thread pode ler
   o valor 0, então a outra ser escalonada ler o mesmo valor e decrementar. 
   Com o escalonamento da thread inicial, ela incrementará, em relação ao valor
   lido inicialmente, e o valor final de x nesse caso será 1.
*/