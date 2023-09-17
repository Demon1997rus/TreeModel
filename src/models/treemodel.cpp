#include "treemodel.h"

#include <QDebug>
#include <QFile>

namespace TreeExample
{
TreeModel::TreeModel(const QString& data, QObject* parent)
  : QAbstractItemModel(parent), m_root(new Node({ "Title", "Summary" }))
{
    setupModelData(data.split("\n"), m_root);
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

void TreeModel::setupModelData(const QStringList& lines, Node* parent)
{
    QList<Node*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count())
    {
        int position = 0;
        while (position < lines[number].length())
        {
            if (lines[number].at(position) != ' ')
                break;
            position++;
        }

        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty())
        {
            // Read the column data from the rest of the line.
            const QStringList columnStrings = lineData.split(QLatin1Char('\t'), QString::SkipEmptyParts);
            QList<QVariant> columnData;
            columnData.reserve(columnStrings.count());
            for (const QString& columnString : columnStrings)
                columnData << columnString;

            if (position > indentations.last())
            {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0)
                {
                    parents << parents.last()->child(parents.last()->childCount() - 1);
                    indentations << position;
                }
            }
            else
            {
                while (position < indentations.last() && parents.count() > 0)
                {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new Node(columnData, parents.last()));
        }
        ++number;
    }
}

}  // namespace TreeExample
