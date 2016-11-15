#include <string>
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
// nome do acadêmico: Gustavo Figueira Olegário


using namespace std;

/**
 * @brief      getpid: function return the process identificator of the calling
 *                     process. Also, this function shall always be successful.
 *
 *
 * @return     Return the process ID. None return value is reserved to indicate
 *             erros
 */


/**
 * @brief      fork: this function allwos to create a new process.
 *
 * @return     This function is zero in the child and the process-identificator
 *             number of the child in the parent, or -1 on error. In the latter
 *             case, the variable ERRNO indicates the problem.
 */


/**
 * @brief      getppid: function return the parent process identificator of the
 *                      calling process. Also, this function shall always be
 *                      successful.
 *
 * @return     Return the parent process ID. None return value is reserved to
 *             indicate erros.
 *
 */


/**
 * @brief      sleep: pause the calling process for a few seconds, according to
 *             the parameter.
 *
 * @param      NUMBER: number of seconds that the process will wait.
 *
 * @return     This is a void function. There is no return values.
 */


/**
 * @brief      waitpid: This function allows the parent process wait until the
 *                      child processes terminate.
 *
 * @param      pid: There's 4 options for pid. If pid is < -1, than it will wait
 *                  any child process whose group ID is equal to the absolute
 *                  value of pid. If -1, it will wait for any child process.
 *                  When 0, will wait for any process whose identificator is
 *                  equal to that of the calling process, Otherwise, will wait
 *                  for the child whose process identificator is equal to the
 *                  value of pid.
 *
 * @param      *stat_loc
 *
 * @param      options
 *
 * @return     On success, returns the process identificator of the child whose
 *             state has changed; if WNOHANG was specified and one or more child
 *             specified by pid exist, but have not yet changed state, then 0 is
 *             returned. On error, -1 is returned and ERRNO indicates the
 *             problem.
 *
 */

int main () {
   // include declarations you need
   int count = 0;
   int id_father = getpid();
   pid_t pid;
   /* Repeat 5 times */
   for (int i = 0; i < 5; ++i) {
      cout << "Parent process " << id_father /* PID of parent-process */ <<
            ": Creating child" << endl;
      /* Duplicate this process */
      pid = fork();
      /* If there was an error on duplication then */
      if (pid < 0) {
            cout << "Error on fork()" << endl;
            return -1;
      } else if (getppid() == id_father) {
      /* If child-process is running then */
            cout << "Child process " << getpid()/* PID of child-process */
                 << ": Running" << endl;
            count++;
            /* Sleep for 1 second */
            sleep(1);
            cout << "Child process " << getpid()/* PID of child-process */
                 << ": Exiting with status " << count << endl;
            return count;
      }
   }

   /* if this is the parent-process then */
   if (getpid() == id_father){
      cout << "Parent process " << id_father/* PID of parent-process */
           << ": Waiting children to exit" << endl;
      int errno, status, sum = 0;
      /* Parent-process waits for all children to exit,
       * adding each status to the sum variable */
      for (int i = 0; i < 5; ++i) {
         waitpid(-1, &status, 0);
         if (errno == ECHILD) {
            throw runtime_error("erro");
         } else {
            sum += WEXITSTATUS(status);
          }
      }

      cout << "Parent process " << id_father/* PID of parent-process*/
           << ": Exiting with sum " <<sum << endl;
   }
   /*  */
   return count;

  /* Respostas do "Para pensar e responder junto ao código:"
     1) O valor apresentado será 5, pois estamos trabalhando com processos e não
     com threads. Ou seja, não estamos compartilhando a memória. Dessa forma,
     cada um terá a sua própria variável, fará o incremento e no final faremos
     a soma. Como são 5 processos, então o valor apresentado será 5.

     2) Nâo, pois como foi dito anteriormente, não estamos trabalhando com memó-
     ria compartilhada. Sendo assim, não existe a condição de corrida.

     3) Endereços diferentes, pois sempre que um processo é criado o Sistema
     Operacional se encarrega de arranjar, quando possível, espaço na memória
     e criar uma cópia idêntica do código para este novo processo que foi gerado

  */

}