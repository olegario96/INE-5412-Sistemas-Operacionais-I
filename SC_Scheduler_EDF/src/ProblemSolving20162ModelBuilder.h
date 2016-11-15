/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProblemSolving20162ModelBuilder.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 08:49
 */

#ifndef PROBLEMSOLVING20162MODELBUILDER_H
#define PROBLEMSOLVING20162MODELBUILDER_H

#include "ModelBuilder.h"

class ProblemSolving20162ModelBuilder: public ModelBuilder {
public:
    ProblemSolving20162ModelBuilder();
    ProblemSolving20162ModelBuilder(const ProblemSolving20162ModelBuilder& orig);
    virtual ~ProblemSolving20162ModelBuilder();
    Model * buildModel();
private:

};

#endif /* PROBLEMSOLVING20162MODELBUILDER_H */

