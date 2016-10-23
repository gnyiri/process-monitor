#include "processitem.h"
#include "processtreemodel.h"

//---------------------------------------------------------------------
ProcessTreeModel::ProcessTreeModel(QObject* parent)
  : QAbstractItemModel(parent)
{
  m_root_item = new ProcessItem(1, 0);
  build_data();
}
//---------------------------------------------------------------------
ProcessTreeModel::~ProcessTreeModel()
{
  delete m_root_item;
}
//---------------------------------------------------------------------
void ProcessTreeModel::build_data()
{
  ProcessItem* m_element_item1 = new ProcessItem(2, m_root_item);
  ProcessItem* m_element_item2 = new ProcessItem(3, m_element_item1);
  ProcessItem* m_element_item3 = new ProcessItem(4, m_element_item1);
}
//---------------------------------------------------------------------
QVariant ProcessTreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  ProcessItem *item = static_cast<ProcessItem*>(index.internalPointer());

  return item->data(index.column());
}
//---------------------------------------------------------------------
Qt::ItemFlags ProcessTreeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return 0;
  }

  return QAbstractItemModel::flags(index);
}
//---------------------------------------------------------------------
QVariant ProcessTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    if(section == 0)
    {
      return QVariant("Name");
    }
    else
    {
      return QVariant("PID");
    }
  }
  return QVariant();
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
