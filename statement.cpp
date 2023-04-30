#include "statement.h"

std::string intToStr(int value)
{
    std::stack<char> num;
    bool isNeg=false;
    if (!value)
    {
        return "0";
    }
    if (value<0)
    {
        value=-value;
        isNeg=true;
    }
    while (value>0)
    {
        num.push(char(value%10+'0'));
        value/=10;
    }
    if (isNeg)
    {
        num.push('-');
    }
    std::string str="";
    while (!num.empty())
    {
        str+=num.top();
        num.pop();
    }
    return str;
}

void print(std::string str,MainWindow* window)
{
    try
    {
        parser tmp(str);
        int num=tmp.calculate();
        window->textShow(intToStr(num));
    }
    catch (const char* ch)
    {
        throw ch;
    }
}

void let(std::string str)
{
    try
    {
        parser exp(str);
        exp.calculate();
    }
    catch (const char* ch)
    {
        throw ch;
    }
}

void rem()
{
    return;
}

int ifThen(std::string parse1,std::string parse2)
{
    try
    {
        parser tmp(parse1);
        if (tmp.calculate())
        {
            return parser::strToInt(parse2);
        }
        else
        {
            return 0;
        }
    }
    catch (const char* ch)
    {
        throw ch;
    }
}

int Goto(std::string line)
{
    return parser::strToInt(line);
}
