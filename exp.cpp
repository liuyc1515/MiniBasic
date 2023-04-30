#include "exp.h"

Expression::Expression()
{

}

Expression::~Expression()
{

}

int Expression::getConstantValue()
{
    return 0;
}

std::string Expression::getIdentifierName()
{
    return "";
}

std::string Expression::getOperator()
{
    return "";
}

Expression* Expression::getLHS()
{
    return NULL;
}

Expression* Expression::getRHS()
{
    return NULL;
}

ConstantExp::ConstantExp(int val)
{
    value=val;
}

int ConstantExp::eval(EvaluationContext &context)
{
    return 0;
}

std::string ConstantExp::toString()
{
    std::stack<char> num;
    int tmp=value;
    while (tmp>0)
    {
        num.push(char(tmp%10+'0'));
        tmp/=10;
    }
    std::string str="";
    while (!num.empty())
    {
        str+=num.top();
        num.pop();
    }
    return str;
}

ExpressionType ConstantExp::type()
{
    return CONSTANT;
}

int ConstantExp::getConstantValue()
{
    return value;
}

IdentifierExp::IdentifierExp(std::string name)
{
    IdentifierExp::name=name;
}

int IdentifierExp::eval(EvaluationContext &context)
{
    if (context.isDefined(name))
    {
        return context.getValue(name);
    }
    else
    {
        throw "undefined!";
    }
}

std::string IdentifierExp::toString()
{
    return name;
}

ExpressionType IdentifierExp::type()
{
    return IDENTIFIER;
}

std::string IdentifierExp::getIdentifierName()
{
    return name;
}

CompoundExp::CompoundExp(std::string op,Expression* lhs,Expression* rhs)
{
    CompoundExp::op=op;
    CompoundExp::lhs=lhs;
    CompoundExp::rhs=rhs;
}

CompoundExp::~CompoundExp()
{

}

int CompoundExp::eval(EvaluationContext &context)
{
    return 0;
}

std::string CompoundExp::toString()
{
    return lhs->toString()+op+rhs->toString();
}

ExpressionType CompoundExp::type()
{
    return COMPOUND;
}

std::string CompoundExp::getOperator()
{
    return op;
}

Expression* CompoundExp::getLHS()
{
    return lhs;
}

Expression* CompoundExp::getRHS()
{
    return rhs;
}
