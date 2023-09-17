#include "treeview.h"

#include <QDebug>

namespace TreeExample
{
TreeView::TreeView(const QString& pathModelData, QWidget* parent)
  : QWidget(parent), mainLayout(this), treeView(this), model(new TreeModel(pathModelData, this))
{
    // setup model
    treeView.setModel(model.data());

    // setup layout
    mainLayout.addWidget(&treeView);
}
}  // namespace TreeExample
