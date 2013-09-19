#pragma once

//! \brief The PseudoRandomGenerator class
//! interface for different random generators
class PseudoRandomGenerator
{
public:
    PseudoRandomGenerator(){}
    virtual ~PseudoRandomGenerator(){}
    virtual int rand() = 0;
};

