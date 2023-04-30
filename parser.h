#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>
#include <QMessageBox>

#include "exp.h"
#include "evalstate.h"

class parser
{
private:
    Expression* root;
    static EvaluationContext context;
    int calculate(Expression* exp);
    void del(Expression* exp);
public:
    parser(std::string str);
    ~parser();
    int calculate();
    static int getValue(std::string id);
    static int strToInt(std::string str);
};

#endif // PARSER_H
