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
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->pushButtonEmergencyStop, &QPushButton::pressed, &monitor, &Monitor::emergencyStop);
    connect(ui->pushButtonSynchronise, &QPushButton::pressed, &monitor, &Monitor::sync);
}

void MainWindow::addBlankStateRow()
{
    // Creating a new QComboBox - QLineEdit - QPushButton row
    QHBoxLayout *layout = new QHBoxLayout;
    QComboBox *combobox = new QComboBox;
    combobox->addItems(getStates());

    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setMinimumWidth(100);

    QPushButton *pushButton = new QPushButton(tr("Send"));

    layout->addWidget(combobox);
    layout->addWidget(lineEdit);
    layout->addWidget(pushButton);

    // Disconnect all the comboboxes "addBlankStateRow()" calls because only the last one should emit this signal
    const auto currentIndexChanged = static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged);
    const QList<QComboBox *> comboBoxes = ui->groupBoxScrollArea->findChildren<QComboBox *>();
    for (const QComboBox *disconnectCombobox : comboBoxes) {
        disconnect(disconnectCombobox, currentIndexChanged, this, &MainWindow::stateCbIndexChanged);
    }

    // Inserting the new line right before the spring
    const int numLayouts = ui->verticalLayoutStates->count();
    ui->verticalLayoutStates->insertLayout(numLayouts - 1, layout);


    // Connect signals of the row
    connect(combobox, currentIndexChanged, this, &MainWindow::stateCbIndexChanged);
    const auto deleteRow = [this, layout](int index){if (index == 0) {this->deleteStateRow(layout);}};
    connect(combobox, currentIndexChanged, this, deleteRow);
}

void MainWindow::deleteStateRow(QHBoxLayout *row)
{
    for (int i = 0, count = row->count(); i < count; ++i) {
        auto item = row->takeAt(0)->widget();
        item->deleteLater();
    }
    row->deleteLater();
}

void MainWindow::enableValueColor(QLineEdit *lineEdit)
{
    lineEdit->setStyleSheet("border: blue");
}

void MainWindow::disableValueColor(QLineEdit *lineEdit)
{
    lineEdit->setStyleSheet("");
}

void MainWindow::disableValueRefreshing(QLineEdit *lineEdit)
{
    lineEdit->blockSignals(true);
}

void MainWindow::enableValueRefreshing(QLineEdit *lineEdit)
{
    lineEdit->blockSignals(false);
}

QStringList MainWindow::getStates() const
{
    QStringList list;
    list << "";
    list << "State 1";
    list << "State 2";
    list << "State 3";
    list << "State 4";

    return list;
}

void MainWindow::stateCbIndexChanged(int index)
{
    // The first one is always empty
    if (index == 0) {
        return;
    }

    addBlankStateRow();
}
