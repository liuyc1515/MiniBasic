#include "program.h"

void program(std::vector<std::string> &tokens,MainWindow* window,int &flow)
{
    flow=0;
    if (tokens[1]=="LET")
    {
        try
        {
            let(tokens[2]);
        }
        catch (const char* ch)
        {
            throw ch;
        }
    }
    else if (tokens[1]=="PRINT")
    {
        try
        {
            print(tokens[2],window);
        }
        catch (const char* ch)
        {
            throw ch;
        }
    }
    else if (tokens[1]=="REM")
    {
        rem();
    }
    else if (tokens[1]=="IF")
    {
        if (tokens[3]=="THEN")
        {
            try
            {
                flow=ifThen(tokens[2],tokens[4]);
            }
            catch (const char* ch)
            {
                throw ch;
            }
        }
        else
        {
            throw "error!";
        }
    }
    else if (tokens[1]=="GOTO")
    {
        flow=Goto(tokens[2]);
    }
    else if (tokens[1]=="END")
    {
        flow=-1;
    }
}
