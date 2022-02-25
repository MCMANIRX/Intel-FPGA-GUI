#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchFlipped();
    void buttonReleased();
    void segChange();
    void ledChange(bool newLEDState, short ledNum);
    void updateSevenSeg(std::string binaryStr);
    void hexToSegment(std::string hexVal);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
