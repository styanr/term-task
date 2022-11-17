#include "add_item.h"
#include "qmessagebox.h"
#include "ui_add_item.h"
#include <QValidator>
#include "transport.h"

add_item::add_item(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_item)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    QIntValidator *validator = new QIntValidator(0, 999);
    ui->le_axles->setValidator(validator);
    ui->le_passengers->setValidator(validator);
    ui->le_seats->setValidator(validator);
    validator = new QIntValidator(0, 99);
    ui->le_doors->setValidator(validator);
    validator = new QIntValidator(200, 1000);
    ui->le_horsepower->setValidator(validator);
    errors = {
           {"Brand", "Property \"Brand\" has not been filled.\n"},
           {"Engine Type", "Property \"Engine\" has not been filled.\n"},
           {"Axles", "Property \"Axles\" has not been filled.\n"},
           {"Passengers", "Property \"Passengers\" has not been filled.\n"},
           {"Seats", "Property \"Seats\" has not been filled.\n"},
           {"Doors", "Property \"Doors\" has not been filled.\n"},
           {"Horsepower", "Property \"Horsepower\" has not been filled.\n"},
           {"Low Floor", "Property \"Low Floor\" has not been filled.\n"},
    };
    result = "";
}

add_item::~add_item()
{
    if(result.isEmpty())
        valid = false;
    delete ui;
}

void add_item::on_le_brand_textEdited(const QString &arg1)
{
    QString border = "";
    if(!arg1.isEmpty()) {
        border = "border : 2px solid green;";
        errors["Brand"] = "";
        for(const QChar character : arg1) {
            if(!(character.isLetter() || character.isSpace() || character == ','
                 || character == '.' || character == '-')) {
                border = "border : 2px solid red;";
                errors["Brand"] = "Text in property \"Brand\" contains not supported characters.\n";
                break;
            }
        }
    }
    else
        errors["Brand"] = "Property \"Brand\" has not been filled.\n";
    ui->le_brand->setStyleSheet(border);
}

void add_item::on_le_engine_textEdited(const QString &arg1)
{
    QString border = "";
    if(!arg1.isEmpty()) {
        if(arg1 == "Electric" || arg1 == "Hybrid" || arg1 == "Petrol" || arg1 == "Diesel") {
            border = "border : 2px solid green;";
            errors["Engine Type"] = "";
        }
        else {
            errors["Engine Type"] = "Text in property \"Engine Type\" does not match any supported values.\n";
            border = "border : 2px solid red;";
        }
    }
    else
        errors["Engine Type"] = "Property \"Engine\" has not been filled.\n";
    ui->le_engine->setStyleSheet(border);
}


void add_item::on_le_axles_textEdited(const QString &arg1)
{
    QString border = "";
    if(!arg1.isEmpty()) {
        if(arg1.toInt() < 2) {
            border = "border : 2px solid red;";
            errors["Axles"] = "Value in property \"Axles\" cannot be smaller than 2.\n";
        }
        else {
            border = "border : 2px solid green;";
            errors["Axles"] = "";
        }
    }
    else
        errors["Axles"] = "Property \"Axles\" has not been filled.\n";
    ui->le_axles->setStyleSheet(border);
}


void add_item::on_le_passengers_textEdited(const QString &arg1)
{
    QString border = "";
    if(!arg1.isEmpty()) {
        border = "border : 2px solid green;";
        errors["Passengers"] = "";
    }
    else
        errors["Passengers"] = "Property \"Passengers\" has not been filled.\n";
    ui->le_passengers->setStyleSheet(border);
}


void add_item::on_le_seats_textEdited(const QString &arg1)
{
    QString border = "";
    if(!arg1.isEmpty()) {
        if(arg1.toInt() > ui->le_passengers->text().toInt()) {
            border = "border : 2px solid red;";
            errors["Seats"] = "Value in property \"Seats\" is bigger than value in property \"Passengers\".\n";
        }
        else {
            border = "border : 2px solid green;";
            errors["Seats"] = "";
        }
    }
    else
        errors["Seats"] = "Property \"Seats\" has not been filled.\n";
    ui->le_seats->setStyleSheet(border);
}


void add_item::on_le_doors_textEdited(const QString &arg1)
{
    QString border = "";
    if(!arg1.isEmpty()) {
        if(arg1.toInt() <= 1) {
            border = "border : 2px solid red;";
            errors["Doors"] = "Value in property \"Doors\" cannot be smaller than 2.\n";
        }
        else {
            border = "border : 2px solid green;";
            errors["Doors"] = "";
        }
    }
    else
        errors["Doors"] = "Property \"Doors\" has not been filled.\n";
    ui->le_doors->setStyleSheet(border);
}


void add_item::on_le_horsepower_textEdited(const QString &arg1)
{
    QString border = "";
    if(!arg1.isEmpty()) {
        if(arg1.toInt() < 200) {
            border = "border : 2px solid red;";
            errors["Horsepower"] = "Value in property \"Horsepower\" cannot be smaller than 200.\n";
        }
        else {
            border = "border : 2px solid green;";
            errors["Horsepower"] = "";
        }
    }
    else
        errors["Horsepower"] = "Property \"Horsepower\" has not been filled.\n";
    ui->le_horsepower->setStyleSheet(border);
}


void add_item::on_le_lowfloor_textEdited(const QString &arg1)
{
    QString border = "";
    errors["Low Floor"] = "Property \"Low Floor\" has not been filled.\n";
    if(!arg1.isEmpty()) {
        if(arg1 == "Yes" || arg1 == "No") {
            border = "border : 2px solid green;";
            errors["Low Floor"] = "";
        }
        else {
            errors["Low Floor"] = "Text in property \"Low Floor\" does not match any supported values.\n";
            border = "border : 2px solid red;";
        }
    }
    ui->le_lowfloor->setStyleSheet(border);
}


void add_item::on_b_OK_clicked()
{
    auto a = errors;
    if(std::find_if_not(errors.begin(), errors.end(), [](const auto& a){
                return a.second.isEmpty();
        }) != errors.end()) {
        valid = false;
        QString errors_str = "";
        for(const auto &val : errors)
            errors_str += val.second;
        QMessageBox::critical(this, "Error adding a new transport.", "There are some errors in your input:\n" + errors_str);
    }
    else {
        valid = true;
        QStringList res_list;
        res_list.append(ui->le_brand->text());
        res_list.append(QString::number(string_to_engine_type[ui->le_engine->text()]));
        res_list.append(ui->le_axles->text());
        res_list.append(ui->le_passengers->text());
        res_list.append(ui->le_seats->text());
        res_list.append(ui->le_doors->text());
        res_list.append(ui->le_horsepower->text());
        res_list.append(ui->le_lowfloor->text() == "Yes" ? "1" : "0");
        result = res_list.join(',');
        close();
    }
}

std::pair<bool, QString> add_item::get_result() const {
    return std::pair<bool, QString>(valid, result);
};


void add_item::on_pushButton_clicked()
{
    valid = false;
    close();
}

