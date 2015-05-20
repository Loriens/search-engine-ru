#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
signals:
    void filePath(const QString &str);
    void giveDomen(const QString &str);
private slots:
    void okClicked();
};

#endif // DIALOG_H
