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
        activateValueEdit(qobject_cast<QLineEdit *>(object));
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
        combobox->addItem(name, dataId);
    }
    combobox->setProperty("managingLayout", QVariant::fromValue(layout));

    // Adding QLineEdit
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setMinimumWidth(100);
    lineEdit->setProperty("managingLayout", QVariant::fromValue(layout));

    // Adding QPushButton
    QPushButton *pushButton = new QPushButton(tr("Send"));
    pushButton->setVisible(false);

    layout->addWidget(combobox);
    layout->addWidget(lineEdit);
    layout->addWidget(pushButton);
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
    const auto comboBoxIndexChanged = [this, combobox] {this->comboBoxIndexChanged(combobox);};
    connect(combobox, currentIndexChanged, this, comboBoxIndexChanged);
    connect(combobox, currentIndexChanged, this, &MainWindow::addBlankStateRowByCb);
    const auto deleteRow = [this, layout] (int index) {if (index == 0) {this->deleteStateRow(layout);}};
    connect(combobox, currentIndexChanged, this, deleteRow);
    const auto deactivateValueEdit = [this, lineEdit] {this->deactivateValueEdit(lineEdit);};
    connect(pushButton, &QPushButton::pressed, this, deactivateValueEdit);
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

void MainWindow::activateValueEdit(QLineEdit *valueEdit)
{
    if (valueEdit->isReadOnly()) {
        return;
    }

    disableValueRefreshing(valueEdit);

    QPushButton *pushButton = getPushButtonInRow(valueEdit);
    pushButton->setVisible(true);
}

void MainWindow::deactivateValueEdit(QLineEdit *valueEdit)
{
    if (valueEdit->isReadOnly()) {
        return;
    }

    enableValueRefreshing(valueEdit);

    QPushButton *pushButton = getPushButtonInRow(valueEdit);
    pushButton->setVisible(false);
}

QPushButton* MainWindow::getPushButtonInRow(QLineEdit *valueEdit) const
{
    const QHBoxLayout *layout = valueEdit->property("managingLayout").value<QHBoxLayout *>();
    return static_cast<QPushButton *>(layout->itemAt(2)->widget());
}

QLineEdit *MainWindow::getLineEditInRow(QComboBox *comboBox) const
{
    const QHBoxLayout *layout = comboBox->property("managingLayout").value<QHBoxLayout *>();
    return static_cast<QLineEdit *>(layout->itemAt(1)->widget());
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

void MainWindow::comboBoxIndexChanged(QComboBox *comboBox)
{
    // The first one is always empty
    const int index = comboBox->currentIndex();
    if (index == 0) {
        return;
    }

    const dataId_t dataID = comboBox->currentData().value<dataId_t>();

    QLineEdit *lineEdit = getLineEditInRow(comboBox);
    lineEdit->setReadOnly(false);
}

void MainWindow::eraseLog()
{
    ui->textBrowserLogging->setText(QString::null);
}
