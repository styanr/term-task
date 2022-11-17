#ifndef ADD_ITEM_H
#define ADD_ITEM_H

#include <QDialog>

namespace Ui {
class add_item;
}

class add_item : public QDialog
{
    Q_OBJECT

public:
    explicit add_item(QWidget *parent = nullptr);
    std::pair<bool, QString> get_result() const;
    ~add_item();

private slots:
    void on_le_brand_textEdited(const QString &arg1);

    void on_le_engine_textEdited(const QString &arg1);

    void on_le_axles_textEdited(const QString &arg1);

    void on_le_passengers_textEdited(const QString &arg1);

    void on_le_seats_textEdited(const QString &arg1);

    void on_le_doors_textEdited(const QString &arg1);

    void on_le_horsepower_textEdited(const QString &arg1);

    void on_le_lowfloor_textEdited(const QString &arg1);

    void on_b_OK_clicked();

    void on_pushButton_clicked();

private:
    std::map<QString, QString> errors;
    QString result;
    bool valid;
    Ui::add_item *ui;
};

#endif // ADD_ITEM_H
