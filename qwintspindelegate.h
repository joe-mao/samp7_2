#ifndef QWINTSPINDELEGATE_H
#define QWINTSPINDELEGATE_H
#include <QStyledItemDelegate>
#include <QWidget>
#include <QModelIndex>
class QWIntSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWIntSpinDelegate();
    //自定义代理组件必须继承以下4个类
    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget * editor, const QModelIndex & index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
};

#endif // QWINTSPINDELEGATE_H
