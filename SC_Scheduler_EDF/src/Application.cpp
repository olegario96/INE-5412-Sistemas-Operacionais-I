/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Application.cpp
 * Author: cancian
 * 
 * Created on 31 de Agosto de 2016, 14:18
 */

#include <list>

#include "Application.h"

Application::Application() {
}

Application::Application(const Application& orig) {
}

Application::~Application() {
}

void Application::addCode(Application::Information instruction) {
    _code.insert(_code.end(), instruction);
}

void Application::addData(Application::Information data) {
    _data.insert(_data.end(), data);
}

std::list<Application::Information> Application::getCode() {
    return _code;
}

std::list<Application::Information> Application::getData() {
    return _data;
}