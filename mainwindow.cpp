#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtCore/QFile>
#include<QtCore/QTextStream>
#include <QProcess>
#include <QPushButton>
#include<QDebug>
#include <QSerialPort>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

        static QProcess p;
        QStringList params;
        QStringList params2;
        QStringList arguments_eventlogPull;
        QStringList arguments_eventlogParse;


        arguments_eventlogPull <<"-b115200 " << "-ccom6 " <<"-r0 " <<"-ftestFile.dat";
        arguments_eventlogParse <<"-ptestFile.dat" <<"-ftestFile.csv";
        QDir::setCurrent("C:\\Users\\Pkalangutkar\\Desktop\\StimZ-QT-GUI");

        QString pythonPath = "C:/Python27/pythonw.exe";
        QString eventlogPull_py = "C:\\Users\\Pkalangutkar\\Desktop\\StimZ-Scripts\\stim-Z-scripts\\python\\eventlog_pull.py";
        QString eventlogParse_py = "C:\\Users\\Pkalangutkar\\Desktop\\StimZ-Scripts\\stim-Z-scripts\\python\\eventlog_parse.py";

        params <<eventlogPull_py;
        params2 <<eventlogParse_py;

        p.start(pythonPath,params<<arguments_eventlogPull);
        p.waitForFinished(-1);
        p.start("python",params2<<arguments_eventlogParse);
        p.waitForFinished(-1);
        QString p_stdout = p.readAll();
        QString p_stderr = p.readAllStandardError();
        qDebug()<<p.readAllStandardOutput();
        if(!p_stderr.isEmpty())
           qDebug()<<"Python error:"<<p_stderr;
        qDebug()<<"Python result="<<p_stdout;
        //ui->lineEdit->setText(p_stdout);

}




