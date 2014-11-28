#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <functional>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
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

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    QSignalMapper signalMapper;
    Ui::MainWindow *ui;
    Monitor monitor;

    void createSignalSlotConnections();
    void addBlankStateRow();
    void deleteStateRow(QHBoxLayout *row);
    void disableValueRefreshing(QLineEdit *valueEdit);
    void enableValueRefreshing(QLineEdit *valueEdit);
    void enableValueColor(QLineEdit *valueEdit);
    void disableValueColor(QLineEdit *valueEdit);
    void activateValueEdit(QLineEdit *valueEdit);
    void deactivateValueEdit(QLineEdit *valueEdit);
    QPushButton *getPushButtonInRow(QLineEdit *valueEdit) const;
    QLabel *getLabelInRow(QLineEdit *valueEdit) const;
    QLineEdit *getLineEditInRow(QComboBox *comboBox) const;

private slots:
    void addBlankStateRowByCb(int index);
    void comboBoxIndexChanged(QComboBox *comboBox);
    void eraseLog();

};

#endif // MAIN_WINDOW_H_
