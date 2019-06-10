#ifndef QWFLOATSPINDELEGATE_H
#define QWFLOATSPINDELEGATE_H

#include <QStyledItemDelegate>

class QWFloatSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWFloatSpinDelegate();
    //自定义代理组件必须以下4个函数
    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget * editor, const QModelIndex & index)const Q_DECL_OVERRIDE;
    void setModelData(QWidget * editor, QAbstractItemModel *model, const QModelIndex & index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
};

#endif // QWFLOATSPINDELEGATE_H
