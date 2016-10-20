#include "processitem.h"
#include "processtreemodel.h"

//---------------------------------------------------------------------
ProcessTreeModel::ProcessTreeModel(QObject* parent) :
  QAbstractItemModel(parent)
{
  m_root_item = new ProcessItem(1, 0);
}
//---------------------------------------------------------------------
ProcessTreeModel::~ProcessTreeModel()
{
  delete m_root_item;
}
//---------------------------------------------------------------------
QVariant ProcessTreeModel::data(const QModelIndex &index, int role) const
{
  return QVariant();
}
//---------------------------------------------------------------------
Qt::ItemFlags ProcessTreeModel::flags(const QModelIndex &index) const
{

}
//---------------------------------------------------------------------
QVariant ProcessTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}
//---------------------------------------------------------------------
QModelIndex ProcessTreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if(!hasIndex(row, column, parent))
  {
    return QModelIndex();
  }

  ProcessItem* parent_item = 0;

  if(!parent.isValid())
  {
    parent_item = m_root_item;
  }
  else
  {
    parent_item = static_cast<ProcessItem*>(parent.internalPointer());
  }

  ProcessItem* child_item = parent_item->child(row);

  if(child_item)
  {
    return createIndex(row, column, child_item);
  }
  else
  {
    return QModelIndex();
  }
}
//---------------------------------------------------------------------
QModelIndex ProcessTreeModel::parent(const QModelIndex &index) const
{
  if(!index.isValid())
  {
    return QModelIndex();
  }

  ProcessItem* child_item = static_cast<ProcessItem*>(index.internalPointer());
  ProcessItem* parent_item = child_item->parent();

  if(parent_item == m_root_item)
  {
    return QModelIndex();
  }

  return createIndex(parent_item->row(), 0, parent_item);
}
//---------------------------------------------------------------------
int ProcessTreeModel::rowCount(const QModelIndex &parent) const
{
  ProcessItem* parent_item = 0;

  if(parent.column() > 0)
  {
    return 0;
  }

  if(!parent.isValid())
  {
    parent_item = m_root_item;
  }
  else
  {
    parent_item = static_cast<ProcessItem*>(parent.internalPointer());
  }

  return parent_item->child_count();
}
//---------------------------------------------------------------------
int ProcessTreeModel::columnCount(const QModelIndex &parent) const
{
  if(parent.isValid())
  {
    return static_cast<ProcessItem*>(parent.internalPointer())->column_count();
  }
  else
  {
    return m_root_item->column_count();
  }
}
