#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QWIntSpinDelegate;
class QWFloatSpinDelegate;
class QWComboBoxDelegate;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel * LabCellPos;//当前单元格的行列号
    QLabel * LabCellText;//当前单元格的内容

    QWFloatSpinDelegate floatSpinDelegate;//



};

#endif // MAINWINDOW_H
