#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>


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
    void resizeEvent(QResizeEvent* event);
    void switchFlipped();
    void buttonReleased();
    void segChange();
    void setSegment(int segment, std::string value);
    void ledChange(bool newLEDState, short ledNum);
    void updateSevenSeg(std::string binaryStr);
    void hexToSegment(std::string hexVal);
    void labelScale(QLabel* label);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
