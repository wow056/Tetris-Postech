#ifndef DIALOG_SELECT_H
#define DIALOG_SELECT_H

#include <QDialog>

namespace Ui {
class dialog_select;
}

class dialog_select : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_select(QWidget *parent = nullptr);
    ~dialog_select();

private:
    Ui::dialog_select *ui;
};

#endif // DIALOG_SELECT_H
