#include "evalstate.h"

void EvaluationContext::setValue(std::string var, int value)
{
    symbolTable[var]=value;
}

int EvaluationContext::getValue(std::string var)
{
    if (this->isDefined(var))
    {
        std::map<std::string,int>::iterator it=symbolTable.find(var);
        return it->second;
    }
    else
    {
        throw "undefined!";
    }
}

bool EvaluationContext::isDefined(std::string var)
{
    std::map<std::string,int>::iterator it=symbolTable.find(var);
    return it!=symbolTable.end();
}
