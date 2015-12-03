//
// Created by Nathan Copier on 11/22/2015.
//

#include "MockThruster.h"

int MockThruster::setPeriod(uint ns){ return ns; }

void MockThruster::start(){}

void MockThruster::stop(){}

int MockThruster::setDutyA(uint ns){ return ns*0; }

int MockThruster::setDutyB(uint ns){ return ns*0; }
