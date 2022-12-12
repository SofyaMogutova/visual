#include "stepsviewer.h"
#include "ui_stepsviewer.h"
#include <QtSql>
#include <QDebug>

StepsViewer::StepsViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepsViewer)
{
    ui->setupUi(this);
}

StepsViewer::~StepsViewer()
{
    delete ui;
}

void StepsViewer::setRecipe(int recipe_id)
{
    QSqlQuery query;
    bool ok = query.prepare("SELECT description, number FROM steps WHERE recipe_id = :id");
    if(!ok){
        qDebug()<<query.lastError();
    }
    query.bindValue(":id",recipe_id);
    ok = query.exec();
    if(!ok){
        qDebug()<<query.lastError();
    }
    descriptions.clear();
    numbers.clear();
    while (query.next()) {
        QString desc = query.value(0).toString();
        QString number = query.value(1).toString();
        descriptions.push_back(desc);
        numbers.push_back(number);
    }
    qDebug()<<numbers.size();
    qDebug()<<descriptions.size();
    ui->numberLabel->setText(numbers[0]);
    ui->descLabel->setText(descriptions[0]);
    index = 0;
    ui->prevButton->setEnabled(false);
    ui->nextButton->setEnabled(true);
}

void StepsViewer::on_nextButton_clicked()
{
    index++;
    ui->numberLabel->setText(numbers[index]);
    ui->descLabel->setText(descriptions[index]);
    if(index + 1 == numbers.size()){
        ui->nextButton->setEnabled(false);
    }
    if(index > 0){
        ui->prevButton->setEnabled(true);
    }
}

void StepsViewer::on_prevButton_clicked()
{
    index--;
    ui->numberLabel->setText(numbers[index]);
    ui->descLabel->setText(descriptions[index]);
    if(index == 0){
        ui->prevButton->setEnabled(false);
    }
    if(index + 1 < numbers.size()){
        ui->nextButton->setEnabled(true);
    }
}
