/*
 * File:   main.cpp
 * Author: cancian
 *
 * Created on August 31, 2015, 7:42 AM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sys/poll.h>
// general
#include "Simulator.h"
#include "Model.h"

// application-specific
#include "OperatingSystem.h"
//#include "ProblemSolving5Tester.h"
//#include "ProblemSolving5ModelBuilder.h"

//#include "ProblemSolving2Tester.h"
//#include "ProblemSolving2ModelBuilder.h"

//#include "ProblemSolving20162Tester.h"
#include "ProblemTester.h"
#include "ProblemSolving20162ModelBuilder.h"


using namespace std;

int main(int argc, char** argv) {
    int test = -1;

    struct pollfd fds;
    int ret;
    fds.fd = 0; /* this is STDIN */
    fds.events = POLLIN;
    ret = poll(&fds, 1, 0);
    if (ret == 1) {
        std::cin >> test;
        //    std::cout << "Test " << test << " selected\n";
        //} else {
        //    std::cout << "Normal execution selected\n";
    }

    ModelBuilder* builder = new ProblemSolving20162ModelBuilder(); //ProblemSolving5ModelBuilder(); 

    //test = 1;
    if (test == -1) {
        std::cout << "Normal execution selected\n";
        Simulator* simulator = Simulator::getInstance();
        Model* model = builder->buildModel();
        simulator->setModel(model);

        // not the best place to be, but for short...
        OperatingSystem::Init();

        simulator->run();
    } else {
        std::cout << "Test " << test << " selected\n";
        ProblemTester* tester = new ProblemTester(); //ProblemSolving20162Tester(); //ProblemSolving5Tester();
        tester->setBuilder(builder);
        tester->test(test);
    }
    return 0;
}


