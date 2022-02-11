#include "prepwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>

PrepWidget::PrepWidget(QWidget *parent)
    : QWidget{parent}
{
    auto layout = new QHBoxLayout(this);
    mView = this->createView();
    layout->addWidget(mView);
    layout->addLayout(this->createButtons());
}

QTableView *PrepWidget::createView()
{
    auto result = new QTableView(this);
    return result;
}

QVBoxLayout *PrepWidget::createButtons()
{
    auto result = new QVBoxLayout;
    auto edit = new QPushButton(tr("Edit"));
    result->addWidget(edit);
    return result;
}
