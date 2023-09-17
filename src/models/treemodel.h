#pragma once

#include <QAbstractItemModel>
#include <QDomDocument>

#include "node.h"

namespace TreeExample
{
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(const QString& pathModelData, QObject* parent = nullptr);
    virtual ~TreeModel();

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected:
    virtual void setupModelData(const QDomDocument& data);
    Node* m_root;
};

}  // namespace TreeExample
