#include "mainwindow.h"
#include <QIcon>
#include <QAction>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include "pcontroller.h"
#include "prep.h"
#include "selectpersonadialog.h"
#include "smanager.h"
#include "prepwidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    PController::get().load();
    this->createActions();
    this->createToolBar();
    this->createCentralWidget();
}

MainWindow::~MainWindow()
{
    PController::get().save();
}

void MainWindow::createActions()
{
    auto debug = new QAction("Debug", this);
    connect(debug, &QAction::triggered, [](){
        qDebug() << PController::get().allPreps().size();
        if (auto p = dynamic_cast<Persona *>(PController::get().allPreps().first())) {
            qDebug() << p->fullname();
        }
    });
    auto import = new QAction("Import preps", this);
    import->setToolTip(tr("Импортировать преподавателей из текстового файла."));
    connect(import, &QAction::triggered, this, &MainWindow::importPersonas);
    _actions << debug << import;
}

void MainWindow::createToolBar()
{
    auto tool_bar = this->addToolBar(tr("Инструменты"));
    tool_bar->addActions(_actions);
}

void MainWindow::createCentralWidget()
{
    auto central_widget = new QTabWidget(this);
    central_widget->addTab(new PrepWidget, tr("Преподаватели"));
    this->setCentralWidget(central_widget);
}

void MainWindow::importPersonas()
{
    auto filename = QFileDialog::getOpenFileName(this, "Open text-file", ".", "From Excel (*.txt *.csv)");
    if (!filename.isEmpty()) {
        auto loaded = PController::get().importPreps(filename);
        QList<Persona *> loaded_persona;
        for (auto p : loaded) {
            loaded_persona << p;
        }
        qDebug() << "Loaded" << loaded.size() << "persons.";
        auto persona_to_import = SelectPersonaDialog::selectPersonaToImport(loaded_persona, this);
        QList<Prep *> prep_to_import;
        for (auto persona : persona_to_import) {
            if (auto p = dynamic_cast<Prep *>(persona)) {
                prep_to_import << p;
            }
        }
        qDebug() << prep_to_import;
    }
}
