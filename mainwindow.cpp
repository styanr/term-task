#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customexception.h"
#include <QDir>
#include <vector>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <functional>
#include "add_item.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changed_list = false;
    ui->gridLayout->setContentsMargins(10, 0, 10, 0);
    ui->verticalLayout->setContentsMargins(10, 0, 0, 0);
    ui->main_table->setAlternatingRowColors(true);
    ui->main_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->main_table->setFocusPolicy(Qt::NoFocus);
    ui->main_table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->main_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->main_table->setShowGrid(false);
    ui->main_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->main_table->verticalHeader()->hide();
    ui->main_table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->pushButton->setCursor(Qt::PointingHandCursor);
    ui->ChooseArgument->setCursor(Qt::PointingHandCursor);
    ui->ChooseOrder->setCursor(Qt::PointingHandCursor);
    ui->menuFile->setCursor(Qt::PointingHandCursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent (QCloseEvent *event) {
    if(ask_to_save())
        event->accept();
    else event->ignore();
}

bool MainWindow::ask_to_save() {
    bool proceed = true;
    if(changed_list) {
        int res = QMessageBox::warning(this, "Warning",
                    "Save changes to file?",
                    QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel, QMessageBox::Save);
        if (res == QMessageBox::Save)
            on_actionSave_triggered();
        else if (res == QMessageBox::Cancel)
            proceed = false;
    }
    return proceed;
}

void MainWindow::setup_table() {
    ui->label_2->setText("Average horsepower: " + QString::number(list.average_horsepower()));
    ui->main_table->horizontalHeader()->show();
    ui->main_table->setRowCount(0);
    QTableWidgetItem *new_item;
    for(int i = 0; i < list.size(); i++) {
        ui->main_table->insertRow(ui->main_table->rowCount());
        ui->main_table->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->main_table->setItem(i, 1, new QTableWidgetItem(QString::fromLatin1(list[i].get_brand())));
        ui->main_table->setItem(i, 2, new QTableWidgetItem(engine_type_to_string[list[i].get_engine_type()]));
        ui->main_table->setItem(i, 3, new QTableWidgetItem(QString::number(list[i].get_axles_count())));
        ui->main_table->setItem(i, 4, new QTableWidgetItem(QString::number(list[i].get_passengers_count())));
        ui->main_table->setItem(i, 5, new QTableWidgetItem(QString::number(list[i].get_seats_count())));
        ui->main_table->setItem(i, 6, new QTableWidgetItem(QString::number(list[i].get_doors_count())));
        ui->main_table->setItem(i, 7, new QTableWidgetItem(QString::number(list[i].get_horsepower())));
        ui->main_table->setItem(i, 8, new QTableWidgetItem(list[i].has_low_floor() ? "Yes" : "No"));
    }
}

void MainWindow::update_table() {
    for(int i = 0; i < list.size(); i++) {
        ui->main_table->item(i, 1)->setText(QString::fromLatin1(list[i].get_brand()));
        ui->main_table->item(i, 2)->setText(engine_type_to_string[list[i].get_engine_type()]);
        ui->main_table->item(i, 3)->setText(QString::number(list[i].get_axles_count()));
        ui->main_table->item(i, 4)->setText(QString::number(list[i].get_passengers_count()));
        ui->main_table->item(i, 5)->setText(QString::number(list[i].get_seats_count()));
        ui->main_table->item(i, 6)->setText(QString::number(list[i].get_doors_count()));
        ui->main_table->item(i, 7)->setText(QString::number(list[i].get_horsepower()));
        ui->main_table->item(i, 8)->setText((list[i].has_low_floor() ? "Yes" : "No"));
    }
}

void MainWindow::highlight_table(std::vector<std::size_t> indices) {
    on_b_clr_clicked();
    for(std::size_t index : indices) {
        for(int i = 0; i < ui->main_table->columnCount(); i++)
        ui->main_table->item(index, i)->setBackground(QColor((index % 2 ? 215 : 180), 0, 55, 255));
    }
}

void MainWindow::on_actionRead_from_triggered()
{
    if (!ask_to_save())
        return;
    QString filepath = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(), "Text file (*.txt)");
    if(!filepath.isEmpty()) {
        input_file.setFileName(filepath);
        input_file.open(QIODevice::ReadOnly);
        if(input_file.size()) {
            QTextStream input_stream(&input_file);
            try {
                list.clear();
                input_stream >> list;
                setup_table();
            }
            catch(CustomException &e) {
                QMessageBox::critical(this, "Error reading from file", QString::fromUtf8(e.what()));
            }
        }
        else QMessageBox::critical(this, "Error reading file", "The file that you have chosen is empty. Please try again");
        input_file.close();
    }
    else
        QMessageBox::critical(this, "Error opening file", "You have not chosen a file. Please try again.");
}

void MainWindow::on_actionSave_triggered()
{
    if(!input_file.fileName().isEmpty()) {
        input_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QTextStream out(&input_file);
            out << list;
            input_file.close();
            changed_list = false;
    }
    else on_actionSave_as_triggered();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Save as...", QDir::currentPath(), "Text file (*.txt)");
    if(!filepath.isEmpty()) {
        input_file.setFileName(filepath);
        input_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out(&input_file);
        out << list;
        changed_list = false;
        input_file.close();
    }
    else
        QMessageBox::critical(this, "Error opening file", "You have not chosen a file. Please try again.");
}

void MainWindow::on_pushButton_clicked()
{
    on_b_clr_clicked();
    try {
    bool is_ascending = (ui->ChooseOrder->currentText() == "Ascending");
    if(ui->ChooseArgument->currentText() != "Car Brand") {
        std::function<int(PublicTransport &)> func;
        if(ui->ChooseArgument->currentText() == "Engine Type")
            func = &PublicTransport::get_engine_type;
        else if(ui->ChooseArgument->currentText() == "Axles")
            func = &PublicTransport::get_axles_count;
        else if(ui->ChooseArgument->currentText() == "Passengers")
            func = &PublicTransport::get_passengers_count;
        else if(ui->ChooseArgument->currentText() == "Seats")
            func = &PublicTransport::get_seats_count;
        else if(ui->ChooseArgument->currentText() == "Doors")
            func = &PublicTransport::get_doors_count;
        else if(ui->ChooseArgument->currentText() == "Horsepower")
            func = &PublicTransport::get_horsepower;
        else if(ui->ChooseArgument->currentText() == "Low Floor")
            func = &PublicTransport::has_low_floor;
        list.sort([&](PublicTransport &a, PublicTransport &b) {
            return (is_ascending? func(a) < func(b) : func(a) > func(b));
        });
    }
    else list.sort([&](PublicTransport &a, PublicTransport &b) {
        return (is_ascending? a.get_brand() < b.get_brand() : a.get_brand() > b.get_brand());
    });
    changed_list = true;
    update_table();
    }
    catch (CustomException &e) {
        QMessageBox::critical(this, "Error sorting the list.", QString::fromUtf8(e.what()));
    }
}


void MainWindow::on_b_el_20_26_clicked()
{
    try {
    std::size_t idx = list.most_powerful_electric();
    QMessageBox::information(this, "Result",
            "Index of most powerful electric transport with 20-26 seats:\n" + QString::number(idx + 1));
    }
    catch (CustomException &e) {
            QMessageBox::critical(this, "Error finding an element.", QString::fromUtf8(e.what()));
    }
}

void MainWindow::on_b_more_than_avg_clicked()
{
    try {
        auto indices = list.more_powerful_than_avg_more_than_4_axles();
        highlight_table(indices);
        QMessageBox::information(this, "Result", QString::number(indices.size()) + " instances found.");
    }
    catch (CustomException &e){
        QMessageBox::critical(this, "Error finding an element.", QString::fromUtf8(e.what()));
    }
}


void MainWindow::on_b_clr_clicked()
{
    for(int i = 0; i < ui->main_table->rowCount(); i++) {
        if(ui->main_table->item(i, 0)->background() == QBrush(QColor(215, 0, 55, 255)) ||
                ui->main_table->item(i, 0)->background() == QBrush(QColor(180, 0, 55, 255))) {
                for(int j = 0; j < ui->main_table->columnCount(); j++)
                ui->main_table->item(i, j)->setBackground(QBrush());
        }
    }
}

void MainWindow::on_b_lowfloor_clicked()
{
    try {
        auto indices = list.more_than_4_doors_has_low_floor_more_than_40_standing_passengers();
        highlight_table(indices);
        QMessageBox::information(this, "Result", QString::number(indices.size()) + " instances found.");
    }
    catch (CustomException &e){
        QMessageBox::critical(this, "Error finding an element.", QString::fromUtf8(e.what()));
    }
}

void MainWindow::on_b_add_clicked()
{
    add_item new_form;
    new_form.exec();
    const auto &result = new_form.get_result();
    if (result.first) {
        PublicTransport new_transport;
        QString str_new = result.second;
        QTextStream stream(&str_new);
        stream >> new_transport;
        list.append(new_transport);
        changed_list = true;
        setup_table();
    }
}




