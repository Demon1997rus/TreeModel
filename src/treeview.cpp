#include "treeview.h"

#include <QDebug>
#include <QHeaderView>

namespace TreeExample
{
TreeView::TreeView(const QString& modelData, QWidget* parent)
  : QWidget(parent), mainLayout(this), treeView(this), model(new TreeModel(modelData, this))
{
    // setup model
    treeView.setModel(model.data());

    // setup layout
    mainLayout.addWidget(&treeView);

    treeView.header()->resizeSections(QHeaderView::ResizeToContents);
    resize(1000, 1000);
}
}  // namespace TreeExample
