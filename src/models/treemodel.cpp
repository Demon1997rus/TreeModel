#include "treemodel.h"

#include <QDebug>
#include <QFile>

namespace TreeExample
{
TreeModel::TreeModel(const QString& pathModelData, QObject* parent)
  : QAbstractItemModel(parent), m_root(new Node({ "Title", "Summary" }))
{
    QFile file(pathModelData);
    QDomDocument doc;
    QString errorMsg;
    if (doc.setContent(&file, &errorMsg))
    {
        qDebug() << "The model accepted the data";
        setupModelData(doc);
    }
    else
    {
        qCritical() << errorMsg;
        qFatal("Error in data.xml file");
    }
}

TreeModel::~TreeModel() { delete m_root; }

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }
    Node* parentNode;
    if (parent.isValid())
    {
        parentNode = reinterpret_cast<Node*>(parent.internalId());
    }
    else
    {
        parentNode = m_root;
    }
    Node* childNode = parentNode->child(row);
    if (childNode)
    {
        return createIndex(row, column, childNode);
    }
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }
    Node* childNode = reinterpret_cast<Node*>(child.internalId());
    Node* parentNode = childNode->parent();
    if (parentNode == m_root)
    {
        return QModelIndex();
    }
    return createIndex(parentNode->row(), 0, parentNode);
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    Node* parentNode;
    if (parent.column() > 0)
    {
        return 0;
    }
    if (parent.isValid())
    {
        parentNode = reinterpret_cast<Node*>(parent.internalId());
    }
    else
    {
        parentNode = m_root;
    }
    return parentNode->childCount();
}

int TreeModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return reinterpret_cast<Node*>(parent.internalId())->columnCount();
    }
    return m_root->columnCount();
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return reinterpret_cast<Node*>(index.internalId())->data(index.column());
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return m_root->data(section);
    }
    return QVariant();
}

void TreeModel::setupModelData(const QDomDocument& data)
{
    QDomElement elem = data.firstChildElement();
    qDebug() << elem.tagName();
}

}  // namespace TreeExample
