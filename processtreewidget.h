#ifndef PROCESSTREEWIDGET_H
#define PROCESSTREEWIDGET_H

#include <QWidget>
#include <QTreeView>

class ProcessTreeWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ProcessTreeWidget(QWidget *parent = 0);

signals:

public slots:
private:
  QTreeView* m_tree_view;
};

#endif // PROCESSTREEWIDGET_H
