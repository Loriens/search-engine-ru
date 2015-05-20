#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include "dialog.h"
#include "paint.h"
#include <QTextStream>
#include <QRegExp>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textBrowser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::readToFile(const QString &filePath)
{
    QFile ourFile(filePath);

    if(!ourFile.open(QFile::ReadOnly | QFile::Text))
    {
        return "Error";
    }
    QTextStream stream(&ourFile);
    QString buffer = stream.readAll();

    ourFile.flush();
    ourFile.close(); // Закрываем файл. Очень важно!

    return buffer;
}

void MainWindow::readFile(const QString &folderPath) {
    ui->textBrowser->setText(readToFile(folderPath));

    QFile ourFile(folderPath);
    QString buffer;

    if(!ourFile.open(QFile::ReadOnly | QFile::Text))
    {
        // Error
    }
    QTextStream stream(&ourFile);

    while(!stream.atEnd()) {
        all_sites.push_back(stream.readLine());
    }

    ourFile.flush();
    ourFile.close();

    // Закрываем файл. Очень важно!

    Paint *window = new Paint(this);
    window->allSites = this->all_sites;
    window->show();
}

void MainWindow::on_actionRead_dir_triggered()
{
    Dialog *window = new Dialog(this);
    window->show();

    connect(window, SIGNAL(filePath(QString)), this, SLOT(readFile(QString)));
}
