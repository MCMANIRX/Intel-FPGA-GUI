#include "mainwindow.h"
#include <iostream>

#include <QApplication>


int main(int argc, char *argv[])
{
    std::string text;
    std::cin >> text;
    std::cout << text;


    QApplication a(argc, argv);
    MainWindow w;


    w.show();
    return a.exec();
}
