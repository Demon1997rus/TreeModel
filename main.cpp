#include "widget.h"
#include <QApplication>
//  TreeModel
// Иерархическая модель Qt в паре с делегатом

//void removeItemWithChildren(QAbstractItemModel* model, const QModelIndex& index)
// {
//     int rowCount = model->rowCount(index);
//     for (int row = rowCount - 1; row >= 0; --row) {
//         QModelIndex childIndex = model->index(row, 0, index);
//         removeItemWithChildren(model, childIndex);
//     }

//     // Дополнительные действия перед удалением элемента, если необходимо

//     model->removeRows(index.row(), 1, index.parent());
// }

// Пример использования
// QModelIndex rootIndex = model->index(0, 0, QModelIndex());
// removeItemWithChildren(model, rootIndex);


//////////////////////////////////////////
// void deleteItemWithChildren(QObject* item)
// {
//     QList<QObject*> children = item->children();
//     for (int i = 0; i < children.size(); ++i) {
//         QObject* child = children.at(i);
//         deleteItemWithChildren(child);
//     }

//     delete item;
// }

// Пример использования
// QObject* rootItem = ...; // ваш корневой элемент
// deleteItemWithChildren(rootItem);

//////////////////////////////////////////
// void removeItemWithChildren(QAbstractItemModel* model, const QModelIndex& index)
// {
//     int rowCount = model->rowCount(index);
//     for (int row = rowCount - 1; row >= 0; --row) {
//         QModelIndex childIndex = model->index(row, 0, index);
//         removeItemWithChildren(model, childIndex);
//     }

//     model->beginRemoveRows(index.parent(), index.row(), index.row());
//     model->removeRows(index.row(), 1, index.parent());
//     model->endRemoveRows();
// }

// // Пример использования
// QModelIndex rootIndex = model->index(0, 0, QModelIndex());
// removeItemWithChildren(model, rootIndex);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
