#include "node.h"

namespace TreeExample
{
Node::Node(const QList<QVariant>& data, Node* parent) : m_parent(parent), m_data(data) {}

Node::~Node() { qDeleteAll(m_children); }

Node* Node::parent() const { return m_parent; }

const QList<Node*>& Node::children() const { return m_children; }

Node* Node::child(int index) const
{
    if (index < 0 || index >= m_children.size())
    {
        return nullptr;
    }
    return m_children.at(index);
}

void Node::appendChild(Node* child) { m_children.append(child); }

int Node::childCount() const { return m_children.size(); }

int Node::columnCount() const { return m_data.size(); }

QVariant Node::data(int column) const
{
    if (column < 0 || column >= m_data.size())
    {
        return QVariant();
    }
    return m_data.at(column);
}

int Node::row() const
{
    if (m_parent)
    {
        return m_parent->m_children.indexOf(const_cast<Node*>(this));
    }
    return 0;
}

}  // namespace TreeExample
