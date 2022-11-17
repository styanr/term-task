#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "publictransportlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionRead_from_triggered();
    void setup_table();
    void update_table();
    void highlight_table(std::vector<std::size_t> indices);
    void closeEvent(QCloseEvent *event);
    bool ask_to_save();

    void on_actionSave_triggered();

    void on_pushButton_clicked();

    void on_b_el_20_26_clicked();

    void on_b_clr_clicked();

    void on_b_add_clicked();

    void on_actionSave_as_triggered();

    void on_b_lowfloor_clicked();

    void on_b_more_than_avg_clicked();

private:
    PublicTransportList list;
    bool changed_list;
    Ui::MainWindow *ui;
    QFile input_file;
};
#endif // MAINWINDOW_H
