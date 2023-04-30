#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>

#include "tokenizer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void textShow(std::string str);
    void codeShow(std::string str);
    void treeShow(std::string str);
    void errorShow(const char* str);
private slots:
    void on_cmdLineEdit_editingFinished();
    void clr();
    void run();
    void load();
private:
    int strToInt(std::string str);
    Ui::MainWindow *ui;
    std::map<int,std::vector<std::string>> statements;
};

#include "program.h"
#endif // MAINWINDOW_H
