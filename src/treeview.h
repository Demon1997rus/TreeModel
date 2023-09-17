#pragma once

#include <QWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QScopedPointer>

#include "models/treemodel.h"

namespace TreeExample
{
class TreeView : public QWidget
{
    Q_OBJECT

public:
    TreeView(const QString& modelData, QWidget* parent = nullptr);

private:
    QVBoxLayout mainLayout;
    QTreeView treeView;
    QScopedPointer<TreeModel> model;
};

}  // namespace TreeExample
