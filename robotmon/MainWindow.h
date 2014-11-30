#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <functional>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QTime>
#include <QDebug>

#include "Monitor.h"
#include "ValueWrapperFactory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::MainWindow *ui;
    Monitor monitor;

    void createSignalSlotConnections();
    void fillDataComboBox(QComboBox *comboBox);
    void addBlankStateRow();
    void deleteStateRow(QHBoxLayout *row);
    void enableValueColor(QLineEdit *valueEdit);
    void disableValueColor(QLineEdit *valueEdit);
    void activateValueEdit(QLineEdit *valueEdit, QPushButton *pushButton, QLabel *label);
    void deactivateValueEdit(QLineEdit *valueEdit, QPushButton *pushButton, QLabel *label);
    void newValueReceived(const dataId_t receivedDataId, const QComboBox *comboBox, QLineEdit *lineEdit, QLabel *label);
    void newValueReceived(const dataId_t receivedDataId, const QComboBox *comboBox, QCustomPlot *plot);
    void sendNewValue(QComboBox *comboBox, QLineEdit *lineEdit);

private slots:
    void addBlankStateRowByCb(int index);
    void comboBoxIndexChanged(QComboBox *comboBox, QLineEdit *lineEdit);
    void newValueReceived(const dataId_t receivedDataId);
    void emergencyStopPressed();
    void syncPressed();
    void eraseLog();
    void writeLogLine(const QString& string);

};

#endif // MAIN_WINDOW_H_
