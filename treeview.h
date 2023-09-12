#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class TreeView : public QWidget
{
    Q_OBJECT

public:
    TreeView(QWidget* parent = 0);
};

#endif  // WIDGET_H
