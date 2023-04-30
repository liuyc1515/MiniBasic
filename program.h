#ifndef PROGRAM_H
#define PROGRAM_H

#include <list>
#include <string>
#include <vector>
#include <QMainWindow>

#include "mainwindow.h"
#include "statement.h"

void program(std::vector<std::string> &tokens,MainWindow* window,int &flow);

#endif // PROGRAM_H
