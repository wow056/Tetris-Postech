#ifndef DIALOG_SELECT_H
#define DIALOG_SELECT_H

#include <QDialog>
#include <qfontdatabase.h>

namespace Ui {
class dialog_select;
}

class dialog_select : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_select(QWidget *parent = nullptr);
    ~dialog_select();

private slots:
    void on_normal_btn_clicked();

    void on_speed_btn_clicked();

    void on_item_btn_clicked();

private:
    Ui::dialog_select *ui;
};

#endif // DIALOG_SELECT_H
