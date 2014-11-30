#include "MainWindow.h"
#include "ui_MainWindow.h"

Q_DECLARE_METATYPE(QHBoxLayout *)
Q_DECLARE_METATYPE(dataId_t)

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

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn && object->isWidgetType()) {
        QLineEdit *valueEdit = qobject_cast<QLineEdit *>(object);
        const QHBoxLayout *layout = valueEdit->property("managingLayout").value<QHBoxLayout *>();
        QPushButton *pushButton = static_cast<QPushButton *>(layout->itemAt(2)->widget());
        QLabel *label = static_cast<QLabel *>(layout->itemAt(3)->widget());

        activateValueEdit(valueEdit, pushButton, label);
        return true;
    }

    return QObject::eventFilter(object, event);
}

void MainWindow::createSignalSlotConnections()
{
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->pushButtonEmergencyStop, &QPushButton::pressed, &monitor, &Monitor::emergencyStop);
    connect(ui->pushButtonSynchronise, &QPushButton::pressed, &monitor, &Monitor::sync);
    connect(ui->pushButtonEraseLog, &QPushButton::pressed, this, &MainWindow::eraseLog);
}

void MainWindow::addBlankStateRow()
{
    // Creating a new QComboBox - QLineEdit - QPushButton row
    QHBoxLayout *layout = new QHBoxLayout;

    // Adding QComboBox
    QComboBox *combobox = new QComboBox;
    combobox->addItem("");
    for (const auto &dataId : monitor.getAllDataIds()) {
        const QString name = QString::fromStdString(monitor.getDataIdText(dataId));
        combobox->addItem(name, QVariant::fromValue(dataId));
    }

    // Adding QLineEdit
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setMinimumWidth(110);
    lineEdit->setProperty("managingLayout", QVariant::fromValue(layout));

    // Adding QPushButton
    QPushButton *pushButton = new QPushButton(tr("Send"));
    pushButton->setVisible(false);

    // Adding label
    QLabel *label = new QLabel;
    label->setMinimumWidth(80);
    label->setVisible(false);

    layout->addWidget(combobox);
    layout->addWidget(lineEdit);
    layout->addWidget(pushButton);
    layout->addWidget(label);
    lineEdit->installEventFilter(this);

    // Disconnect all the comboboxes "addBlankStateRow()" calls because only the last one should emit this signal
    const auto currentIndexChanged = static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged);
    const QList<QComboBox *> comboBoxes = ui->groupBoxScrollArea->findChildren<QComboBox *>();
    for (const QComboBox *disconnectCombobox : comboBoxes) {
        disconnect(disconnectCombobox, currentIndexChanged, this, &MainWindow::addBlankStateRowByCb);
    }

    // Inserting the new line right before the spring
    const int numLayouts = ui->verticalLayoutStates->count();
    ui->verticalLayoutStates->insertLayout(numLayouts - 1, layout);


    // Connect signals of the row
    connect(combobox, currentIndexChanged, this, &MainWindow::addBlankStateRowByCb);

    const auto comboBoxIndexChanged = [=] {this->comboBoxIndexChanged(combobox, lineEdit);};
    connect(combobox, currentIndexChanged, this, comboBoxIndexChanged);

    const auto deleteRow = [this, layout] (int index) {if (index == 0) {this->deleteStateRow(layout);}};
    connect(combobox, currentIndexChanged, this, deleteRow);

    const auto newValueReceived = [=] (dataId_t receivedId) {this->newValueReceived(receivedId, combobox, lineEdit);};
    connect(&monitor, &Monitor::newValueReceived, this, newValueReceived);

    const auto deactivateValueEdit = [=] {this->deactivateValueEdit(lineEdit, pushButton, label);};
    connect(pushButton, &QPushButton::pressed, this, deactivateValueEdit);

    const auto sendNewValue = [=] {this->sendNewValue(combobox, lineEdit);};
    connect(pushButton, &QPushButton::pressed, this, sendNewValue);
}

void MainWindow::deleteStateRow(QHBoxLayout *row)
{
    for (int i = 0, count = row->count(); i < count; ++i) {
        auto item = row->takeAt(0)->widget();
        item->deleteLater();
    }
    row->deleteLater();
}

void MainWindow::enableValueColor(QLineEdit *valueEdit)
{
    valueEdit->setStyleSheet("border: blue");
}

void MainWindow::disableValueColor(QLineEdit *valueEdit)
{
    valueEdit->setStyleSheet("");
}

void MainWindow::activateValueEdit(QLineEdit *valueEdit, QPushButton *pushButton, QLabel *label)
{
    if (valueEdit->isReadOnly()) {
        return;
    }

    disableValueRefreshing(valueEdit);
    pushButton->setVisible(true);
    label->setText("[" + valueEdit->text() + "]");
    label->setVisible(true);
}

void MainWindow::deactivateValueEdit(QLineEdit *valueEdit, QPushButton *pushButton, QLabel *label)
{
    if (valueEdit->isReadOnly()) {
        return;
    }

    enableValueRefreshing(valueEdit);
    pushButton->setVisible(false);
    label->setVisible(false);
}

void MainWindow::newValueReceived(dataId_t receivedDataId, QComboBox *comboBox, QLineEdit *lineEdit)
{
    const dataId_t currentDataId = comboBox->currentData().value<dataId_t>();
    if (receivedDataId == currentDataId) {
        const QString newValue = QString::fromStdString(monitor.getDataValueText(currentDataId));
        lineEdit->setText(newValue);
    }
}

void MainWindow::sendNewValue(QComboBox *comboBox, QLineEdit *lineEdit)
{
    const ValueWrapperFactory wrapperFactory;
    const dataId_t dataID = comboBox->currentData().value<dataId_t>();
    const QString value = lineEdit->text();
    const ValueWrapper *wrapper = wrapperFactory.create(dataID, value.toStdString());
    monitor.send(dataID, *wrapper);
    delete wrapper;
}

void MainWindow::disableValueRefreshing(QLineEdit *valueEdit)
{
    valueEdit->blockSignals(true);
}

void MainWindow::enableValueRefreshing(QLineEdit *valueEdit)
{
    valueEdit->blockSignals(false);
}

void MainWindow::addBlankStateRowByCb(int index)
{
    // The first one is always empty
    if (index == 0) {
        return;
    }

    addBlankStateRow();
}

void MainWindow::comboBoxIndexChanged(QComboBox *comboBox, QLineEdit *lineEdit)
{
    // The first one is always empty
    const int index = comboBox->currentIndex();
    if (index == 0) {
        return;
    }

    lineEdit->setReadOnly(false);
}

void MainWindow::eraseLog()
{
    ui->textBrowserLogging->setText(QString::null);
}