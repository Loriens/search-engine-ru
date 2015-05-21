#ifndef PAINT_H
#define PAINT_H

#include <QDialog>
#include <QtGui>
#include <QDialog>
#include <QtCore>
#include <QJsonObject>

namespace Ui {
class Paint;
}

class Paint : public QDialog
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    std::vector<QJsonObject> allFiles;// Вектор, в котором хранятся все ссылки
    QString Path;
    ~Paint();

private:
    Ui::Paint *ui;
    void paintEvent(QPaintEvent *e);

};

#endif // PAINT_H
