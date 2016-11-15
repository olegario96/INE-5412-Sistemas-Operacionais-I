/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Alarm.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 14:42
 */

#include "Abstr_Alarm.h"
#include <unistd.h>

#define TIMER 1000000

typedef double Microsecond;

Alarm::Alarm() {
	timer = TIMER;
}

Alarm::Alarm(const Alarm& orig) {
}

Alarm::~Alarm() = default;

void Alarm::delay(const Microsecond & time) {
	usleep(time);
}

//Falta implementar ??
void Alarm::init() {

}

Microsecond Alarm::getTimer() {
	return timer;
}