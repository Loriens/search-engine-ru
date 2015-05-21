#include "paint.h"
#include "ui_paint.h"

Paint::Paint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);
    setWindowTitle("Graph");
}

Paint::~Paint()
{
    delete ui;
}

void Paint::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QRect rec(250, 10, 250, 50);
    painter.drawRect(rec);
    painter.drawText(rec, Qt::AlignCenter, "Folder path: " + Path);

    int x = 10;
    int y = 100;
    for (int i = 0; i < allFiles.size(); i++)
    {
        QRect rec(x, y, 250, 25);
        painter.drawRect(rec);
        painter.drawText(rec, Qt::AlignCenter, allFiles[i].value("Path").toString() + " (size: " + allFiles[i].value("Size").toString() + ")");

        if ((i + 1) % 4 == 0)
        {
            x = 10;
            y += 75;
        } else {
            x += 300;
        }
    }
}
