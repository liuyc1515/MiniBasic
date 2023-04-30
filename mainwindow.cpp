#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnClearCode,SIGNAL(clicked()),this,SLOT(clr()));
    connect(ui->btnRunCode,SIGNAL(clicked()),this,SLOT(run()));
    connect(ui->btnLoadCode,SIGNAL(clicked()),this,SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    QString cmd = ui->cmdLineEdit->text();
    std::string str=cmd.toStdString();
    if (str=="")
    {
        return;
    }
    ui->CodeDisplay->clear();
    std::vector<std::string> tokens;
    tokenizer(str,tokens);
    int num=strToInt(tokens.front());
    if (num<=0)
    {
        this->errorShow("illegal num!");
    }
    statements[num]=tokens;
    ui->cmdLineEdit->setText("");
    QString output;
    for (std::map<int,std::vector<std::string>>::iterator it=statements.begin();it!=statements.end();++it)
    {
        std::string statement="";
        for (std::vector<std::string>::iterator vecIt=it->second.begin();vecIt!=it->second.end();++vecIt)
        {
            statement+=*vecIt+" ";
        }
        statement.pop_back();
        output.append((statement+"\n").c_str());
    }
    ui->CodeDisplay->append(output);
}

void MainWindow::clr()
{
    statements.clear();
    ui->CodeDisplay->clear();
    ui->treeDisplay->clear();
    ui->textBrowser->clear();
}

void MainWindow::run()
{
    int flow=0;
    std::map<int,std::vector<std::string>>::iterator it=statements.begin();
    while (it!=statements.end())
    {
        program(it->second,this,flow);
        if (flow==0)
        {
            ++it;
        }
        else if (flow==-1)
        {
            break;
        }
        else
        {
            it=statements.find(flow);
        }
    }
}

void MainWindow::load()
{
    QString path=QFileDialog::getOpenFileName(this,"choose your file",".","(*.txt*)");
    std::ifstream input;
    input.open(path.toStdString());
    std::string str;
    QString output;
    while (std::getline(input,str))
    {
        std::vector<std::string> tokens;
        tokenizer(str,tokens);
        int num=strToInt(tokens.front());
        if (num<=0)
        {
            this->errorShow("illegal num!");
            continue;
        }
        statements[num]=tokens;
    }
    for (std::map<int,std::vector<std::string>>::iterator it=statements.begin();it!=statements.end();++it)
    {
        std::string statement="";
        for (std::vector<std::string>::iterator vecIt=it->second.begin();vecIt!=it->second.end();++vecIt)
        {
            statement+=*vecIt+" ";
        }
        statement.pop_back();
        output.append((statement+"\n").c_str());
    }
    ui->CodeDisplay->clear();
    ui->CodeDisplay->append(output);
    input.close();
}

void MainWindow::textShow(std::string str)
{
    QString output;
    output.append(str.c_str());
    ui->textBrowser->append(output);
}

void MainWindow::codeShow(std::string str)
{
    QString output;
    output.append(str.c_str());
    ui->CodeDisplay->append(output);
}

void MainWindow::treeShow(std::string str)
{
    QString output;
    output.append(str.c_str());
    ui->treeDisplay->append(output);
}

void MainWindow::errorShow(const char* ch)
{
    QString output;
    output.append(ch);
    ui->textBrowser->append(output);
}

int MainWindow::strToInt(std::string str)
{
    int num=0;
    int pos=0;
    while (str[pos]!='\0')
    {
        num=num*10+str[pos]-'0';
        pos+=1;
    }
    return num;
}


