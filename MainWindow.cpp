#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createSignalSlotConnections();
    addBlankStateRow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createSignalSlotConnections()
{
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->pushButtonEmergencyStop, SIGNAL(pressed()), &monitor, SLOT(emergencyStop()));
    connect(ui->pushButtonSynchronise, SIGNAL(pressed()), &monitor, SLOT(sync()));
}

void MainWindow::addBlankStateRow()
{
    QHBoxLayout *layout = new QHBoxLayout;
    QComboBox *combobox = new QComboBox;
    QLineEdit *lineEdit = new QLineEdit;
    QPushButton *pushButton = new QPushButton(tr("Send"));

    layout->addWidget(combobox);
    layout->addWidget(lineEdit);
    layout->addWidget(pushButton);

    int numLayouts = ui->verticalLayoutStates->count();
    ui->verticalLayoutStates->insertLayout(numLayouts - 1, layout);

}
