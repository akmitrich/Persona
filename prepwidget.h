#ifndef PREPWIDGET_H
#define PREPWIDGET_H

#include <QWidget>
class QTableView;
class QVBoxLayout;

class PrepWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PrepWidget(QWidget *parent = nullptr);

private:
    QTableView *createView();
    QVBoxLayout *createButtons();

private:
    QTableView *mView;
};

#endif // PREPWIDGET_H
