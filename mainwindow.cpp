#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
//#include <bits/stdc++.h>
#include <regex>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <QGridLayout>

using namespace std;
// look at console.tcl - decoding

/*TODO Pick a widget and change it's values through STDIN("Can be done in python or any other languages")
 done--*TODO Include Get and Set
 done--*TODO Set values using hex frames (ex."0x01234F") <- every byte is one seven segment
 done--*NEXT Parameterize the seven segments (account for ".") <Important>
 done--*NEXT Make header with number sizes for each parameter for readablity
 *TODO Make Github with a readme.md (Document Header file)
 *NOTE 0 on 1 off (Active Low)
 done--*TODO Run initialize method/loop
 *NOTE Reusablity and Flexability is key <Important>
 *NOTE Look into resizing Window for different resolutions. (Look into relative locations as opposed to pixel based ones) *** <Important>
 *EXTRA Look into TLC and Vending Machine applications.
*/

bool segmentHasDecimalPoint =false;
bool sevensegment[NUMSEVENSEGMENT][NUMSEVENSEGPARTS] = {0};
bool sevensegmentDec[NUMSEVENSEGMENT][NUMSEVENSEGPARTSDEC] = {};
bool switchStates[NUMSWITCHES] = {};
bool ledStates[NUMLEDS] = {};



void initControls(){



    qDebug() << "\n" << "hello" << "\n";
      int nb;
      qDebug() << "Enter a number " << "\n";
      cin>>nb;
      qDebug() << "Your number is "<< nb<< "\n";

    for (int i =0;i<NUMSWITCHES-1;i++) {
        switchStates[i]=true;
    }

    for (int i =0;i<NUMLEDS-1;i++) {
        ledStates[i]=true;
    }

    for (int i = 0;i<NUMSEVENSEGMENT;i++) {
        for (int j = 0;j<NUMSEVENSEGPARTSDEC;j++) {
            sevensegment[NUMSEVENSEGMENT][NUMSEVENSEGPARTSDEC] = true;
            //qDebug() << "" << sevensegment[NUMSEVENSEGMENT][NUMSEVENSEGPARTS];
        }
    }





}

//Methods that get the values of all stored states
bool* getSwitchStates(){
    return switchStates;
}

bool* getLEDStates(){
    return ledStates;
}

bool* getSevenSegmentStates(){
    if(segmentHasDecimalPoint){
        return *sevensegmentDec;
    }
    else{
        return *sevensegment;
    }
}
//Method that updates all of the switches with a series of booleans to determine on/off state
void updateSwitches(bool newSwitchStates[]){
    int switchLength = sizeof(switchStates)/sizeof(switchStates[0]);
    int newSwitchLength = sizeof(newSwitchStates)/sizeof(newSwitchStates[0]);
    if(switchLength == newSwitchLength){
        for (int i= 0;i<NUMSWITCHES;i++ ) {
            switchStates[i] = newSwitchStates[i];
        }
    }
}
//Method that updates all of the LEDs with a series of booleans to determine on/off state
void updateLEDs(bool newLEDStates[]){
    int ledLength = sizeof(ledStates)/sizeof(ledStates[0]);
    int newLEDLength = sizeof(newLEDStates)/sizeof(newLEDStates[0]);
    if(ledLength == newLEDLength){
        for (int i= 0;i<NUMLEDS;i++ ) {
            ledStates[i] = newLEDStates[i];
        }
    }
}

//update sevensegment display with binary string, has if statements to account for decimal point usage
void MainWindow::updateSevenSeg(string binaryStr){
    int k = 0;
    qDebug() << "uss";
    qDebug() << binaryStr.c_str();
    if (segmentHasDecimalPoint) {
        qDebug() << "Decimal Point found, 48 bits expected (all used) \n";
         k = 0;
        for (int i = 0;i<NUMSEVENSEGMENT;i++) {
            for (int j = 0;j<NUMSEVENSEGPARTSDEC;j++) {
                int bit = (int)binaryStr[k] -48;
                sevensegment[NUMSEVENSEGMENT][NUMSEVENSEGPARTS] = bit;
              //  qDebug()<< "" << sevensegment[NUMSEVENSEGMENT][NUMSEVENSEGPARTSDEC];
                k++;
            }
            qDebug() << "\n";
        }
    }
    else if (!segmentHasDecimalPoint){
        qDebug()  << "No decimal point found, 44 bits expected (42 used) \n";
         k = 0;
        for (int i = 0;i<NUMSEVENSEGMENT;i++) {
            for (int j = 0;j<NUMSEVENSEGPARTS;j++) {
                int bit = (int)binaryStr[k++] - '0';
                sevensegment[i][j] = bit;
            //    qDebug() << "" << sevensegment[i][j];


            }//k++;

          // int bit = (int)binaryStr[k] - '0';
          //  sevensegment[NUMSEVENSEGMENT][NUMSEVENSEGPARTS] = bit;
            //qDebug() <<"\n";
        }
    }
  //  qDebug() << k;

    string debug;


    for (int i = 0;i<NUMSEVENSEGMENT;i++)
        for (int j = 0;j<NUMSEVENSEGPARTS;j++)
            debug.push_back(sevensegment[i][j] == true ? '1' : '0');

       // qDebug() << debug.c_str();
   // qDebug() << "\n\n\n\n";

    segChange();
}

QString getSegName(int num, int let ) {
    QString ret;

    char numc = '0'+(num); //int to ascii
    ret = "seg";
    ret.push_back(numc);
    ret.push_back(SEGLETTERS[let]);

    return ret;
}

QString getSegLetter(QString name){
    QString ret = "image: url(:/de10rs/de10 resource/";
    ret.push_back(name.at(4));
    ret.push_back(".png)");
  //  qDebug() << ret;
    return ret;
}


//image: url(:/de10 resource/A.png)

void MainWindow::segChange(){

    QLabel* seg;
    string debug;
    for(int i = 0 ; i < NUMSEVENSEGMENT; ++i)
        for(int j = 0 ; j < NUMSEVENSEGPARTS; ++j) {

          QString name = getSegName(i+1,j);
          seg  = this->findChild<QLabel*>(name);
     //     qDebug() <<  seg;

         debug.push_back(sevensegment[i][j] == true ? '1' : '0');

     //    qDebug() << seg;

          if(sevensegment[i][j] == true)
            seg->setStyleSheet("");
         else seg->setStyleSheet(getSegLetter(name)) ;
      // else seg->setStyleSheet("image: url(:/de10rs/de10 resource/A.png)") ;



    //     qDebug() << getSegLetter(name);

        }

    int index = 0;
    qDebug() << "begin";

    for(int i = 0; i < 8; ++i){
       debug.push_back(sevensegment[0][index] == true ? '1' : '0');

    }

   qDebug() << debug.c_str();
 ;
}


//converts hex string into binary
string hexToBin(string hexdec)
{
    qDebug() << hexdec.c_str();
    short int i = 0;
    string hexString = "";

    while (hexdec[i]) {

        switch (hexdec[i]) {
        case '0':
            hexString += "0000";
            break;
        case '1':
            hexString += "0001";
            break;
        case '2':
            hexString += "0010";
            break;
        case '3':
            hexString += "0011";
            break;
        case '4':
            hexString += "0100";
            break;
        case '5':
            hexString += "0101";
            break;
        case '6':
            hexString += "0110";
            break;
        case '7':
            hexString += "0111";
            break;
        case '8':
            hexString += "1000";
            break;
        case '9':
            hexString += "1001";
            break;
        case 'A':
        case 'a':
            hexString += "1010";
            break;
        case 'B':
        case 'b':
            hexString += "1011";
            break;
        case 'C':
        case 'c':
            hexString += "1100";
            break;
        case 'D':
        case 'd':
            hexString += "1101";
            break;
        case 'E':
        case 'e':
            hexString += "1110";
            break;
        case 'F':
        case 'f':
            hexString += "1111";
            break;
        default:
            qDebug() << "\nInvalid hexadecimal digit "
                 << hexdec[i];
        }
        i++;
    }
    qDebug() << "hex";
    qDebug() << hexString.c_str();
    return hexString;
}
/*
 * This method takes the hex value given and checks if it has a decimal value or not. After that it sets the flag
 * segmentHasDecimalPoint, it sets the binarystring to give the seven segment display by converting the hex to binary.
 * Finally the updateSevenSeg method will be called and change the seven segment display state.
*/


void MainWindow::setSegment(int segment, string value) {
    string debug ="";
    int index = 0 ;
    qDebug() << value.c_str();
    value = hexToBin(value);



    for(int i = 0; i < value.length(); ++i){
       sevensegment[segment][index++] = (value[i]-48) == 0 ? false : true;
       debug.push_back(sevensegment[segment][index] == true ? '1' : '0');

    }

    debug.push_back(0x20);
    index = 0;

    for(int i = 0; i < value.length(); ++i){
       debug.push_back(sevensegment[0][index] == true ? '1' : '0');

    }

    qDebug() << debug.c_str();
    segChange();

    }




void MainWindow::hexToSegment(string hexVal){

    string binaryStr;
    regex noDecTemplate("(0x|0X)[a-fA-F0-9]{0,12}$");
    regex decTemplate("(0x|0X)[a-fA-F0-9]{0,11}$");
    if(regex_match(hexVal,noDecTemplate)){
        segmentHasDecimalPoint = false;
        binaryStr = hexToBin(hexVal.erase(0,2));
        updateSevenSeg(binaryStr);
    }
    else if(regex_match(hexVal,decTemplate)){
        segmentHasDecimalPoint = true;
        binaryStr = hexToBin(hexVal.erase(0,2));
        updateSevenSeg(binaryStr);
    }
    else{
        qDebug() << "hex string is invalid";
    }
}


//Finds which switch was flipped and changes its switch state and updates the array of switch states.
void MainWindow::switchFlipped(){
    QPushButton* button = (QPushButton*)sender();//sender finds the button pressed and sets it to a new QPushButton pointer
    short switchNumber = (short)button->objectName()[2].unicode() - 48; //temp

  //  qDebug() << button->objectName();
    bool buttonState = switchStates[switchNumber];
    if (buttonState == true) {
        button->setStyleSheet("background-image: url(:/de10 resource/InverseSW.png);");
        qDebug()<<"first clause"<<"\n";
     //   qDebug() << sizeof(switchStates)/sizeof(switchStates[0]);

        switchStates[switchNumber] = false;

    }
    else if(buttonState == false){
        button->setStyleSheet("background-image: url(:/de10rs/de10 resource/SW.png);");
        qDebug()<<"second clause"<<"\n";
        switchStates[switchNumber] = true;

    }

    ledChange(!switchStates[switchNumber], switchNumber);
    qDebug() << switchNumber;

}

void MainWindow::buttonReleased(){
}

//Changes the led states of the given LED (ledNum) to the new state (newLEDState)
void MainWindow::ledChange(bool newLEDState,short ledNum){
    QLabel* tempLabel;
    //This switch statement is given which ledNum we are looking for and we set the templabel equal to the proper
    //led on the ui.
    switch(ledNum){
        case 0:
            tempLabel = ui->ledR0;
            break;
        case 1:
            tempLabel = ui->ledR1;
            break;
        case 2:
            tempLabel = ui->ledR2;
            break;
        case 3:
            tempLabel = ui->ledR3;
            break;
        case 4:
            tempLabel = ui->ledR4;
            break;
        case 5:
            tempLabel = ui->ledR5;
            break;
        case 6:
            tempLabel = ui->ledR6;
            break;
        case 7:
            tempLabel = ui->ledR7;
            break;
        case 8:
            tempLabel = ui->ledR8;
            break;
        case 9:
            tempLabel = ui->ledR9;
            break;
    }
    //Replaces the LED state with the picture representing "on"
    if(newLEDState == true){
        ledStates[ledNum] = true;
        tempLabel->setStyleSheet("image: url(:/de10 resource/led.png);");
    }
    //Empty's the LED states picture to represent it being "off"
    else{
        ledStates[ledNum] = false;
        tempLabel->setStyleSheet("");
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::labelScale(QLabel* label) {


    /*1st resize attempt*/

   /*     QSize pixSize(label->width(),label->height());
      pixSize.scale(size(), Qt::KeepAspectRatio);
      label->setFixedSize(pixSize);*/




    /*2nd resize attempt*/


//label->resize(ui->centralwidget->width()-label->width(),ui->centralwidget->height()-label->height());

    //    pixSize.setWidth(label->pixmap().height()-1);


    /*misc. attempt at scaling*/

     //   label->setScaledContents(true);
    //  ui->centralwidget->setFixedSize(pixSize);
      // label->resize(label->width()/2,label->height()/2);

}

QString SStoPixMap(QString txt, QString path) {

    QString ret = path;

   int begin = txt.indexOf("de10 resource/")+14;

   while(txt.size()-begin > 2)
       ret.append(txt.at(begin++));

    qDebug() << ret;



    return ret;
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);


    QList<QLabel*> elements = this->findChildren<QLabel*>();


   for(QLabel* element : elements){

    /*attempt to edit stylesheet in resizeevent*/

   //   char set[100];
    //   char setlen = 100;
     // snprintf(set,setlen,"height: %dpx;",5);
    //  element->setStyleSheet(set);

    labelScale(element);


}






}


QString getParent(QString path, int levels) {

    for(int i = 0 ; i < levels; ++i)
    {
        while(!path.endsWith('/') && !path.endsWith('\\'))
            path.chop(1);
        path.chop(1);
    }

    return path;

}

//Sets up the MainWindow with all of the switches and buttons.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    //A helpful shortcut for the arrow is to just type ui.swX which is to say ui.swX is the same as ui->swX
    ui->setupUi(this);
    connect(ui->sw0,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw1,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw2,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw3,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw4,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw5,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw6,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw7,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw8,SIGNAL(released()),this,SLOT(switchFlipped()));
    connect(ui->sw9,SIGNAL(released()),this,SLOT(switchFlipped()));

    connect(ui->btnkey0,SIGNAL(released()),this,SLOT(buttonReleased()));
    connect(ui->btnkey1,SIGNAL(released()),this,SLOT(buttonReleased()));
    //hexToSegment("0x0F0F0F0F0F03");
  /// hexToSegment("0xffffffffffff");
    // hexToSegment("0x010204081020");
    hexToSegment("0x000000000000");

  //   setSegment(3,"00");
  //   setSegment(1,"ea");



     /*Get all label elements, use their stylesheets to set their QPixmaps as their stylesheet images, then try scaling in resizeEvent()*/


   /*
   QString path = QCoreApplication::applicationDirPath();
   path =  getParent(path,2) + "/DE10-GUI/de10 resource/";


  QList<QLabel*> elements = this->findChildren<QLabel*>();
    for(QLabel* element : elements) {


        qDebug() << element;
       // QPixmap img(SStoPixMap(ui->de10->styleSheet(),path).c_str());

        element->setPixmap(QPixmap(SStoPixMap(element->styleSheet(),path)));
        element->setScaledContents(true);
        element->show();

      //  element->setStyleSheet("width: max-width; height:auto;"); //attempt at resizing via stylesheet
    }

    */




    /*attempt to use QGridLayout to put all (or at least one) widget into a layour for simple scaling*/


      /*  QGridLayout *layout = new QGridLayout(ui->centralwidget);
        QWidget* widget = new QWidget(this);
        layout->setSpacing(6);

        layout->addWidget(ui->centralwidget, 0, 0, 1, 1);
        layout->addWidget(widget, 0, 0, 1, 1); //<--or whatever you need
        setLayout(layout);


        */



}
