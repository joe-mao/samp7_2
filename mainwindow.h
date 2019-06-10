#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "qwcomboboxdelegate.h"
#include "qwfloatspindelegate.h"
#include "qwintspindelegate.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>

#define FixedColumnCount 6

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actSaveStm_triggered();
    
    void on_actOpenStm_triggered();
    
private:
    Ui::MainWindow *ui;
    QLabel * LabCellPos;//当前单元格的行列号
    QLabel * LabCellText;//当前单元格的内容

    QWFloatSpinDelegate floatSpinDelegate;//浮点数代理组件
    QWIntSpinDelegate intSpinDelegate;//整数型代理组件
    QWComboBoxDelegate comboBoxDelegate;//列表选择，代理组件
    QStandardItemModel * theModel;//数据模型
    QItemSelectionModel * theSelection;//选择模型
    void resetTable(int aRowCount);//表格复位，设定行数
    bool saveDataAsStream(QString & aFileName);//保存为stm文件
    bool openDataAsStream(QString & aFileName);//打开stm文件
    bool saveBinaryFile(QString & aFileName);//保存为dat文件
    bool openBinaryFile(QString & aFileName);//打开dat文件




};

#endif // MAINWINDOW_H
