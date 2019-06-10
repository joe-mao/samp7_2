#include "qwcomboboxdelegate.h"
#include <QComboBox>


QWComboBoxDelegate::QWComboBoxDelegate()
{

}

QWidget *QWComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //设置要使用的代理组件
    QComboBox * editor = new QComboBox(parent);
    editor->setFrame(false);//设置为无边框
    return editor;
}

void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //从数据模型获取数据，显示到代理组件中
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox * comBox = static_cast<QComboBox *>(editor);
    comBox->addItem(text);
}

void QWComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //将代理组件的数据保存到数据模型中
    QComboBox * comBox = static_cast<QComboBox *>(editor);
    QString text = comBox->currentText();
    model->setData(index, text, Qt::EditRole);
}

void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //设置代理组件大小
    editor->setGeometry(option.rect);
}
