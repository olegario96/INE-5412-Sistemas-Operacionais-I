/*
 * File:   Tester.cpp
 * Author: cancian
 *
 * Created on November 7, 2015, 3:44 PM
 */



#include <iostream>

#include "OperatingSystem.h"
#include "Traits.h"

#include "Simulator.h"
#include "SourceModule.h"
#include "Simul_Entity.h"
#include "ModuleCreate.h"
#include "ModuleDispose.h"
#include "ModelBuilder.h"

#include "ProblemTester.h"


ProblemTester::ProblemTester() {
}

ProblemTester::ProblemTester(const ProblemTester& orig) {
}

ProblemTester::~ProblemTester() {
}

void ProblemTester::_clearSystem() {
    /*
    Process::getProcessesList()->clear();
    Thread::getThreadsList()->clear();
    Thread* t;
    while ((t = System::scheduler()->choose()) != nullptr) {
        System::scheduler()->remove(t);
    }
    Thread::_running = nullptr;
     */
}


// test here while there are no subclasses

// VIRTUAL!!
TestInfo ProblemTester::do_real_test(int numTest){
    TestInfo testInfo = TestInfo();
    Traits<Model>::ProblemSolving problem = Traits<Model>::problemChoosen;
    return testInfo;
}


void ProblemTester::test(int numTest) {
    Model* model = _modelBuilder->buildModel();
            
    Simulator* simulator = Simulator::getInstance();
    simulator->setModel(model);
    //simulator->step();

    TestInfo testInfo = TestInfo();
    try {
        testInfo = do_real_test(numTest);
    } catch (int ex) {
        testInfo.SetFailed(true);
        testInfo.SetMessage("Exception raised when executing the test. Tester has failed.");
    }
    
    std::string message = testInfo.GetMessage();
    if (testInfo.IsFailed()) {
        std::cout << "[[TEST_FAILED]]";
        message = "ERROR: " + message;
    } else {
        std::cout << "[[TEST_SUCCESS]]";
        message = "Woohoo.";
    }
    std::cout << " (" << numTest << ") testName='" << testInfo.GetTestName() << "' message='" << message << "'" << std::endl;

}

