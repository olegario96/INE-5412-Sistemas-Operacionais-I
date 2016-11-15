/*
 * File:   TimerMediator.cpp
 * Author: cancian
 *
 * Created on October 9, 2015, 2:55 PM
 */

#include "Mediator_Timer.h"
#include "Simulator.h"
#include "Simul_Debug.h"
#include "OperatingSystem.h"
#include "Traits.h"
#include "Abstr_Thread.h"

Timer::Timer(unsigned int instance) {
    _instance = instance;
}

Timer::Timer(const Timer& orig) {
}

Timer::~Timer() {
}

/**
 * O sistema simulado possui um timer que gera interrupções periodicamente. O timer foi inicialmente configurado
 * para gerar interrupções a cada Traits<Timer>::timer_interrupt_period unidades de tempo. 
 * Sempre que uma interrupção do timer ocorre, automaticamente é
 * invocado o método static void TimerMediator::interrupt_handler(), que precisa ser implementado. Esse método trata uma
 * interrupção do timer, e sua implementação depende do algoritmo de escalonamento. Ele pode ser usado para preemptar
 * uma thread caso seu time slice tenha sido atingido, no caso do algoritmo round-robin, por exemplo.
 */
void Timer::interrupt_handler() {
    Debug::cout(Debug::Level::trace, "TimerMediator::interrupt_handler()");
    // INSERT YOUR CODE HERE
    // ...

}
