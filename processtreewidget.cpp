#include "processtreewidget.h"

ProcessTreeWidget::ProcessTreeWidget(QWidget *parent) : QWidget(parent), m_tree_view(0)
{
  m_tree_view = new QTreeView(this);
}
