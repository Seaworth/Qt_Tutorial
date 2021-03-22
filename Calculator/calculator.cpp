#include "calculator.h"
#include "ui_calculator.h"

// Holds current value of calculation
double calcVal  = 0.0;

// Holds memory value
double memVal = 0.0;

// define if this was the last math button clicked
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    // Put 0.0 in display
    ui->Display->setText(QString::number(calcVal));

    // Will hold references to all the number buttons
    QPushButton *numButtons[10];

    // Cycle through locating the buttons
    for (int i = 0; i < 10; ++i) {
        QString butName = "Button" + QString::number(i);

        // Get the buttons by name and add to array
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);

        // When the button is released, call numPressed()
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    // Connect signals and slots for math buttons
    connect(ui->Add, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));

    // Connect equals button
    connect(ui->Equals, SIGNAL(released()),this,
            SLOT(EqualButtonPressed()));

    // Connect changeSign button
    connect(ui->ChangeSign, SIGNAL(released()),this,
            SLOT(ChangeNumberSign()));

    // Connect clear button
    connect(ui->Clear, SIGNAL(released()),this,
            SLOT(ClearButtonPressed()));

    // Connect MemAdd MemSub MemGet button
    connect(ui->MemAdd, SIGNAL(released()),this,
            SLOT(MemAddButtonPressed()));
    connect(ui->MemSub, SIGNAL(released()),this,
            SLOT(MemSubButtonPressed()));
    connect(ui->MemGet, SIGNAL(released()),this,
            SLOT(MemGetButtonPressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // Get number on button
    QString butVal = button->text();

    // Get the value in the display
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else {
        // Put the new number to the right of whats there
        QString newVal = displayVal + butVal;

        double dblNewVal = newVal.toDouble();

        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed()
{
    // Cancel out previous math button clicks
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    // Store current value in the display
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // Get math sysbol on the button
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseSensitive) == 0){
        divTrigger = true;
    }else if (QString::compare(butVal, "*", Qt::CaseSensitive) == 0) {
        multTrigger = true;
    }else if (QString::compare(butVal, "+", Qt::CaseSensitive) == 0) {
        addTrigger = true;
    }else {
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    // Holds new calculation
    double solution = 0.0;

    // Get val in display
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    // Make sure a math button was pressed
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }  else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        }  else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        } else
            solution = calcVal / dblDisplayVal;
    }
    // Put solution in display
    ui->Display->setText((QString::number(solution)));
}

void Calculator::ChangeNumberSign()
{
    // Get val in display
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    // Regular expression checks if it is a number
    QRegExp reg("[-+]?[0-9.]*");

    // If it is a number change the sign
    if(reg.exactMatch(displayVal)){
        dblDisplayVal = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayVal));
    }
}

void Calculator::ClearButtonPressed()
{
    // clear calcVal and memVal
    calcVal  = 0.0;
    memVal = 0.0;

    // clear dispaly
    ui->Display->setText(QString::number(calcVal));

    // clear flag
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
}

void Calculator::MemAddButtonPressed()
{
    // Get val in display
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    memVal += dblDisplayVal;
}

void Calculator::MemSubButtonPressed()
{
    // Get val in display
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    memVal -= dblDisplayVal;
}

void Calculator::MemGetButtonPressed()
{
    ui->Display->setText(QString::number(memVal));
    calcVal = memVal;
}






