#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include "dialog.h"
#include "paint.h"
#include <QTextStream>
#include <QRegExp>
#include <vector>
#include <QJsonObject>

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

QString MainWindow::readFile(const QString &filePath)
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

void MainWindow::printFile(const QString &folderPath) {
    ui->textBrowser->setText(readFile(folderPath));

    QFile ourFile(folderPath);
    QString buffer;

    if(!ourFile.open(QFile::ReadOnly | QFile::Text))
    {
        // Error
    }
    QTextStream stream(&ourFile);

    QString name_path = stream.readLine();
    stream.readLine();

    while(!stream.atEnd()) {
        QJsonDocument jsdoc = QJsonDocument::fromJson(stream.readLine().toUtf8());
        all_files.push_back(jsdoc.object());
        stream.readLine();
    }

    ourFile.flush();
    ourFile.close();

    // Закрываем файл. Очень важно!

    Paint *window = new Paint(this);
    window->allFiles = this->all_files;
    window->Path = name_path;
    window->show();
}

void MainWindow::on_actionRead_dir_triggered()
{
    Dialog *window = new Dialog(this);
    window->show();

    connect(window, SIGNAL(filePath(QString)), this, SLOT(printFile(QString)));
}
