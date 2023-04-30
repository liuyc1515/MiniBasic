#ifndef EVALSTATE_H
#define EVALSTATE_H

#include <string>
#include <map>

class EvaluationContext
{
public:
    void setValue(std::string var, int value);
    int getValue(std::string var);
    bool isDefined(std::string var);
private:
    std::map<std::string,int> symbolTable;
};

#endif // EVALSTATE_H
