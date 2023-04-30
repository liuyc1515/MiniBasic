#include "tokenizer.h"

void tokenizer(const std::string &str,std::vector<std::string> &tokens)
{
    int pos=0;
    std::string token="";
    while (str[pos]!='\0')
    {
        if (str[pos]!=' ')
        {
            token+=str[pos];
        }
        else
        {
            tokens.push_back(token);
            token="";
        }
        pos+=1;
    }
    tokens.push_back(token);
}
