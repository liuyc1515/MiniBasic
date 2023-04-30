#include "parser.h"

EvaluationContext parser::context;

parser::parser(std::string str)
{
    int pos=0;
    std::stack<Expression*> operand;
    std::stack<char> operation;
    std::string token="";
    while (true)
    {
        if ((str[pos]>='0'&&str[pos]<='9')||(str[pos]>='a'&&str[pos]<='z')||(str[pos]>='A'&&str[pos]<='Z'))
        {
            token+=str[pos];
            pos+=1;
            continue;
        }
        if (!token.empty()&&token[0]>='0'&&token[0]<='9')
        {
            int num;
            try
            {
                num=strToInt(token);
            }
            catch (const char* ch)
            {
                throw ch;
            }
            Expression* tmp= new ConstantExp(num);
            operand.push(tmp);
            token="";
        }
        if (!token.empty()&&((token[0]>='a'&&token[0]<='z')||(token[0]>='A'&&token[0]<='Z')))
        {
            Expression* tmp= new IdentifierExp(token);
            operand.push(tmp);
            token="";
        }
        if (str[pos]=='=')
        {
            operation.push(str[pos]);
        }
        else if (str[pos]=='<'||str[pos]=='>')
        {
            char op;
            if (!operation.empty())
            {
                op=operation.top();
            }
            while (!operation.empty()&&op!='('&&op!='=')
            {
                operation.pop();
                Expression* rhs=operand.top();
                operand.pop();
                Expression* lhs=operand.top();
                operand.pop();
                std::string tmp="a";
                tmp[0]=op;
                Expression* comp=new CompoundExp(tmp,lhs,rhs);
                operand.push(comp);
                op=operation.top();
            }
            operation.push(str[pos]);
        }
        else if (str[pos]=='+'||str[pos]=='-')
        {
            if (str[pos-1]=='('||str[pos-1]=='=')
            {
                Expression* zero=new ConstantExp(0);
                operand.push(zero);
            }
            char op;
            if (!operation.empty())
            {
                op=operation.top();
            }
            while (!operation.empty()&&op!='('&&op!='='&&op!='<'&&op!='>')
            {
                operation.pop();
                Expression* rhs=operand.top();
                operand.pop();
                Expression* lhs=operand.top();
                operand.pop();
                std::string tmp="a";
                tmp[0]=op;
                Expression* comp=new CompoundExp(tmp,lhs,rhs);
                operand.push(comp);
                op=operation.top();
                }
                operation.push(str[pos]);
        }
        else if (str[pos]=='*'||str[pos]=='/')
        {
            char op;
            if (!operation.empty())
            {
                op=operation.top();
            }
            while (!operation.empty()&&(op=='*'||op=='/'))
            {
                operation.pop();
                Expression* rhs=operand.top();
                operand.pop();
                Expression* lhs=operand.top();
                operand.pop();
                std::string tmp="a";
                tmp[0]=op;
                Expression* comp=new CompoundExp(tmp,lhs,rhs);
                operand.push(comp);
                op=operation.top();
            }
            operation.push(str[pos]);
        }
        else if (str[pos]=='(')
        {
            operation.push(str[pos]);
        }
        else if (str[pos]==')')
        {
            char op;
            if (!operation.empty())
            {
                op=operation.top();
            }
            while (!operation.empty()&&op!='(')
            {
                operation.pop();
                Expression* rhs=operand.top();
                operand.pop();
                Expression* lhs=operand.top();
                operand.pop();
                std::string tmp="a";
                tmp[0]=op;
                Expression* comp=new CompoundExp(tmp,lhs,rhs);
                operand.push(comp);
                op=operation.top();
            }
            operation.pop();
        }
        else if (str[pos]=='\0')
        {
            break;
        }
        else
        {
            throw "error!";
        }
        pos+=1;
    }
    while (!operation.empty())
    {
        char op=operation.top();
        operation.pop();
        Expression* rhs=operand.top();
        operand.pop();
        Expression* lhs=operand.top();
        operand.pop();
        std::string tmp="a";
        tmp[0]=op;
        Expression* comp=new CompoundExp(tmp,lhs,rhs);
        operand.push(comp);
    }
    root=operand.top();
    operand.pop();
    while (!operand.empty())
    {
        delete operand.top();
        operand.pop();
    }
}

int parser::strToInt(std::string str)
{
    bool isNeg=false;
    int num=0;
    int pos=0;
    if (str[0]=='-')
    {
        isNeg=true;
        pos+=1;
    }
    while (str[pos]!='\0')
    {
        num=num*10+str[pos]-'0';
        pos+=1;
    }
    if (isNeg)
    {
        return -num;
    }
    else
    {
        return num;
    }
}

void parser::del(Expression *exp)
{
    if (!exp)
    {
        return;
    }
    del(exp->getLHS());
    del(exp->getRHS());
    delete exp;
}

parser::~parser()
{
    del(root);
}

int parser::calculate(Expression *exp)
{
    if (exp->type()==CONSTANT)
    {
        return exp->getConstantValue();
    }
    if (exp->type()==IDENTIFIER)
    {
        int value;
        try
        {
            value=exp->eval(context);
            return value;
        }
        catch (const char* ch)
        {
            throw ch;
        }
    }
    std::string op=exp->getOperator();
    switch (*(op.c_str()))
    {
    case '+':
        return calculate(exp->getLHS())+calculate(exp->getRHS());
    case '-':
        return calculate(exp->getLHS())-calculate(exp->getRHS());
    case '*':
        return calculate(exp->getLHS())*calculate(exp->getRHS());
    case '/':
        return calculate(exp->getLHS())/calculate(exp->getRHS());
    case '<':
        return calculate(exp->getLHS())<calculate(exp->getRHS());
    case '>':
        return calculate(exp->getLHS())>calculate(exp->getRHS());
    case '=':
    {
        int result=calculate(exp->getRHS());
        context.setValue(exp->getLHS()->getIdentifierName(),result);
        return result;
    }
    default:
        throw "error!";
    }
}

int parser::calculate()
{
    return calculate(root);
}

int parser::getValue(std::string id)
{
    int value;
    try
    {
        value=context.getValue(id);
        return value;
    }
    catch (const char* ch)
    {
        throw ch;
    }
}
