#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>

#include "mainwindow.h"
#include "parser.h"

std::string intToStr(int value);
void print(std::string str,MainWindow* window);
void let(std::string str);
void rem();
int ifThen(std::string parse1,std::string parse2);
int Goto(std::string line);

#endif // STATEMENT_H
