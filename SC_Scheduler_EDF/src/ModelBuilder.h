/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModelBuilder.h
 * Author: cancian
 *
 * Created on 11 de Abril de 2016, 17:13
 */

#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "Model.h"

class ModelBuilder {
public:
    ModelBuilder();
    ModelBuilder(const ModelBuilder& orig);
    virtual ~ModelBuilder();
    virtual Model * buildModel();
private:

};

#endif /* MODELBUILDER_H */

