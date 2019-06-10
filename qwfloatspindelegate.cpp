#include "qwfloatspindelegate.h"
#include <QDoubleSpinBox>

QWFloatSpinDelegate::QWFloatSpinDelegate()
{

}

QWidget *QWFloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //创建代理编辑组件
   QDoubleSpinBox * editor = new QDoubleSpinBox(parent);
   editor->setFrame(false);//设置为无边框
   editor->setMinimum(0.0);
   editor->setMaximum(10000.0);
   return editor;
}

void QWFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //从数据模型获取数据，显示到代理组件中
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox * doubleSpinBox = static_cast<QDoubleSpinBox *>(editor);
    doubleSpinBox->setValue(value);
}

void QWFloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //将代理组件的数据保存到数据模型中
    QDoubleSpinBox * doubleSpinBox = static_cast<QDoubleSpinBox *>(editor);
    doubleSpinBox->interpretText();
    double value = doubleSpinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWFloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //设置组件大小
    editor->setGeometry(option.rect);
}
