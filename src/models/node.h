#pragma once

#include <QList>

namespace TreeExample
{
class Node
{
public:
    Node(const QList<QVariant>& data, Node* parent = nullptr);
    ~Node();

public:
    Node* parent() const;
    const QList<Node*>& children() const;
    Node* child(int index) const;
    void appendChild(Node* child);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;

private:
    Node* m_parent;
    QList<Node*> m_children;
    QList<QVariant> m_data;
};
}  // namespace TreeExample
