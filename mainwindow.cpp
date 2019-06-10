#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(this->ui->tableView);
    theModel = new QStandardItemModel(2, FixedColumnCount, this);//数据模型定义和初始化
    theSelection = new QItemSelectionModel(theModel);//选择模型定义和初始化
    this->ui->tableView->setModel(theModel);//设置数据模型
    this->ui->tableView->setSelectionModel(theSelection);//设置选择模型
    this->ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    LabCellPos = new QLabel(this);
    LabCellText = new QLabel(this);
    this->ui->statusBar->addWidget(LabCellPos);
    this->ui->statusBar->addWidget(LabCellText);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actSaveStm_triggered()
{
    //以Qt预定义编码保存文件
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this, "保存选择文件", curPath, "Qt预定义编码数据文件(*.stm)");
    if(aFileName.isEmpty()){
        return;   
    }
    if(saveDataAsStream(aFileName)){
        QMessageBox::information(this, "消息提示", "文件已经成功保存!");
    }
}

void MainWindow::resetTable(int aRowCount, QStringList & headerList)
{
    //表格复位
    theModel->removeRows(0, theModel->rowCount());
    theModel->setRowCount(aRowCount);
    theModel->setHorizontalHeaderLabels(headerList);
    QString str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    for(int i = 0; i < theModel->rowCount(); ++i){
        //设置最后一列
        QModelIndex index = theModel->index(i, FixedColumnCount - 1);
        QStandardItem * aItem = theModel->itemFromIndex(index);
        aItem->setCheckable(true);
        aItem->setData(str, Qt::DisplayRole);
        aItem->setEditable(false);
    }


}

bool MainWindow::saveDataAsStream(QString &aFileName)
{
    //将模型数据保存为Qt预定义编码的数据文件
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::WriteOnly | QIODevice::Truncate))){
        return false;
    }
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_9);//流版本号，写入和读取版本要兼容
    qint32 rowCount = theModel->rowCount();
    qint32 colCount = theModel->columnCount();
    aStream<<rowCount;//写入文件流，行数
    aStream<<colCount;//写入文件流，列数
    //获取表头文字
    for(int i = 0; i < theModel->columnCount(); ++i){
        QString str = theModel->horizontalHeaderItem(i)->text();//获取表头文字
        aStream<<str;//字符串写入文件流
    }
    //获取数据区的数据
    for(int i = 0; i < theModel->rowCount(); ++i){
        
        QStandardItem * aItem = theModel->item(i, 0);//测深
        qint32 ceShen = aItem->data(Qt::DisplayRole).toInt();
        aStream<<ceShen;//写入文件流，qint32
        
        aItem= theModel->item(i, 1);//垂深
        qreal chuiShen = aItem->data(Qt::DisplayRole).toDouble();
        aStream<<chuiShen;//写入文件流，qreal
        
        aItem = theModel->item(i, 2);//方位
        qreal fangwei = aItem->data(Qt::DisplayRole).toDouble();
        aStream<<fangwei;//写入文件流，qreal
        
        aItem = theModel->item(i, 3);//位移
        qreal weiYi = aItem->data(Qt::DisplayRole).toDouble();
        aStream<<weiYi;//写入文件流，qreal
        
        aItem = theModel->item(i, 4);//固井质量
        QString zhiLiang = aItem->data(Qt::DisplayRole).toString();
        aStream<<zhiLiang;//写入文件流，QString
        
        aItem = theModel->item(i, 5);//测井取样
        bool quYang = (aItem->checkState() == Qt::Checked);
        aStream<<quYang;//写入文件流 bool
    }
    aFile.close();
    return true;
}

bool MainWindow::openDataAsStream(QString &aFileName)
{
    //从stm文件读取数据
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadOnly))){
        return false;
    }
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_9);//设置流文件版本号
    qint32 rowCount, colCount;
    aStream>>rowCount;//读取行数
    aStream>>colCount;//读取列数
    //获取表头文字，但并不使用
    QStringList headerList;
    QString str;
    for(int i = 0; i < colCount; ++i){
        aStream>>str;//读取表头字符串
        headerList<<str;
    }

    this->resetTable(rowCount, headerList);//表格复位，设定行数


    //读取数据区
    qint32 ceShen;
    qreal chuiShen, fangWei, weiYi;
    QString zhiLiang;
    bool quYang;
    QStandardItem * aItem;
    QModelIndex index;
    for(int i = 0; i < rowCount; ++i){
        aStream >> ceShen;//读取测深， qint32
        index = theModel->index(i, 0);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(ceShen, Qt::DisplayRole);
        
        aStream >> chuiShen;//读取垂深, qreal
        index = theModel->index(i, 1);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(chuiShen, Qt::DisplayRole);
        
        aStream >> fangWei;//读取方位, qreal
        index = theModel->index(i, 2);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(fangWei, Qt::DisplayRole);
        
        aStream >> weiYi;//位移, qreal
        index = theModel->index(i, 3);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(weiYi, Qt::DisplayRole);
        
        aStream >> zhiLiang;//固井质量, QString
        index = theModel->index(i, 4);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(zhiLiang, Qt::DisplayRole);
        
        aStream >> quYang;//测井取样
        index = theModel->index(i, 5);
        aItem = theModel->itemFromIndex(index);
        if(quYang){
            aItem->setCheckState(Qt::Checked);
        }else{
            aItem->setCheckState(Qt::Unchecked);
        }

    }
     aFile.close();
    return true;
}

void MainWindow::iniModelFromStringList(QStringList & aFileContent)
{
    int rowCnt = aFileContent.count();//文本行数
    theModel->setRowCount(rowCnt - 1);
    QString header = aFileContent.at(0);
    QStringList headerList = header.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList);//设置表头文字
    //设置表格数据
    QStandardItem * aItem;
    QStringList tmpList;
    int j;
    for(int i = 1; i < rowCnt; ++i){
        QString aLineText = aFileContent.at(i);
        tmpList = aLineText.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        for(j = 0; j < FixedColumnCount-1; j ++){
            //不包含最后一列
            aItem = new QStandardItem(tmpList.at(j));
            theModel->setItem(i - 1, j, aItem);//为模型的某行列位置设置Item
        }
        aItem = new QStandardItem(headerList.at(j));//最后一列
        aItem->setCheckable(true);//使单元格编程CheckBox状态
        if(tmpList.at(j) == "0"){
            aItem->setCheckState(Qt::Unchecked);
        }else{
            aItem->setCheckState(Qt::Checked);
        }
        theModel->setItem(i - 1, j, aItem);
    }
}

void MainWindow::on_actOpenStm_triggered()
{
    //打开stm文件
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "Qt预定义编码数据文件(*.stm)");
    if(aFileName.isEmpty()){
        return;
    }
    if(openDataAsStream(aFileName)){
        QMessageBox::information(this, "提示消息", "文件已经打开!");
    }
}

void MainWindow::on_actIniDataArea_triggered()
{
    //使用文本文件先初始化表格数据
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "井数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty()){
        return;
    }
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        //打开文件
        QTextStream aStream(&aFile);
        while(!aStream.atEnd()){
            QString str = aStream.readLine();
            fFileContent.append(str);
        }
    }
    aFile.close();
    iniModelFromStringList(fFileContent);

}

void MainWindow::on_actSaveDat_triggered()
{
    //保存dat文件

}

void MainWindow::on_actIni_triggered()
{

}
