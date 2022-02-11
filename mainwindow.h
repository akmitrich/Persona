#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createActions();
    void createToolBar();
    void createCentralWidget();
    void importPersonas();

private:
    QList<QAction *> _actions;
};
#endif // MAINWINDOW_H
