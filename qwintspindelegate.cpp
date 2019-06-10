#include "qwintspindelegate.h"
#include <QSpinBox>

QWIntSpinDelegate::QWIntSpinDelegate()
{

}

QWidget *QWIntSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    //创建希望的代理编辑组建
    QSpinBox * editor = new QSpinBox(parent);
    editor->setFrame(false);//设置为无边框
    editor->setMinimum(0);
    editor->setMaximum(10000);
    return editor;//返回此编辑器
}

void QWIntSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //从数据模型获取数值。设置位编辑器的显示值
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox * spinBox = static_cast<QSpinBox *>(editor);
    spinBox->setValue(value);
}

void QWIntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //将代理组件的数据保存到数据模型中
    QSpinBox * spinBox = static_cast<QSpinBox *>(editor);
    spinBox->interpretText();
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWIntSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    //设置在组件大小
    editor->setGeometry(option.rect);
}


