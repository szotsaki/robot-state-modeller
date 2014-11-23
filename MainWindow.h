#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <functional>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalMapper>
#include <QStringList>
#include <QDebug>

#include "Monitor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSignalMapper signalMapper;
    Ui::MainWindow *ui;
    Monitor monitor;

    void createSignalSlotConnections();
    void addBlankStateRow();
    void deleteStateRow(QHBoxLayout *row);
    void disableValueRefreshing(QLineEdit *lineEdit);
    void enableValueRefreshing(QLineEdit *lineEdit);
    void enableValueColor(QLineEdit *lineEdit);
    void disableValueColor(QLineEdit *lineEdit);
    QStringList getStates() const;

private slots:
    void stateCbIndexChanged(int index);

};

#endif // MAIN_WINDOW_H_
