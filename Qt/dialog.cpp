#include "dialog.h"
#include "ui_dialog.h"
#include <QPushButton>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(okClicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), SLOT(close()));
    setWindowTitle("Read serialization");
    ui->lineEdit->setText("C:/Users/Asus/Documents/Visual Studio 2013/Projects/Task_SPbGU/Task_SPbGU/for_qt.txt");
}

void Dialog::okClicked()
{
    emit filePath(ui->lineEdit->text());
    close();
}

Dialog::~Dialog()
{
    delete ui;
}
