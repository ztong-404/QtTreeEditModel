#include "widget.h"
#include "ui_widget.h"
#include "personmodel.h"
#include <QTextStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    PersonModel * model = new PersonModel(this);

    ui->treeView->setModel(model);

    ui->treeView->setAlternatingRowColors(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_addRowButton_clicked()
{

    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[Empty Cell]"), Qt::EditRole);
    }
}

void Widget::on_removeRowButton_clicked()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();

    model->removeRows(index.row(),1,index.parent());
}

void Widget::on_addColumnButton_clicked()
{
    QAbstractItemModel *model = ui->treeView->model();
    int column = ui->treeView->selectionModel()->currentIndex().column();

    bool changed = model->insertColumns(column+1,1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal,
                             QVariant("[No header]"), Qt::EditRole);
}

void Widget::on_removeColumnButton_clicked()
{
    QAbstractItemModel *model = ui->treeView->model();
    int column = ui->treeView->selectionModel()->currentIndex().column();
    model->removeColumn(column);
}

void Widget::on_addChildButton_clicked()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {

        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[Empty Cell]"), Qt::EditRole);
    }

    ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                    QItemSelectionModel::ClearAndSelect);
}
