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
    void addBlankStateRow();
    void deleteStateRow(QHBoxLayout *row);
    void disableValueRefreshing(QLineEdit *valueEdit);
    void enableValueRefreshing(QLineEdit *valueEdit);
    void enableValueColor(QLineEdit *valueEdit);
    void disableValueColor(QLineEdit *valueEdit);
    void activateValueEdit(QLineEdit *valueEdit, QPushButton *pushButton, QLabel *label);
    void deactivateValueEdit(QLineEdit *valueEdit, QPushButton *pushButton, QLabel *label);
    void newValueReceived(dataId_t receivedDataId, QComboBox *comboBox, QLineEdit *lineEdit);
    void sendNewValue(QComboBox *comboBox, QLineEdit *lineEdit);

private slots:
    void addBlankStateRowByCb(int index);
    void comboBoxIndexChanged(QComboBox *comboBox, QLineEdit *lineEdit);
    void eraseLog();

};

#endif // MAIN_WINDOW_H_
