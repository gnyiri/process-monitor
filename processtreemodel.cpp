#include <fts.h>
#include <sys/stat.h>

#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QByteArray>
#include <fstream>

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
  char* paths[] = { static_cast<const char*>("/proc/"), 0 };
  FTS* file_tree = fts_open(paths, FTS_NOCHDIR, 0);

  if(!file_tree)
  {
    return;
  }

  FTSENT* node = 0;

  while((node = fts_read(file_tree)))
  {
    if(node->fts_level > 0 && node->fts_name[0] == '.')
    {
      fts_set(file_tree, node, FTS_SKIP);
    }
    else if(node->fts_info & FTS_F && node->fts_level == 2)
    {
      std::string file_name(node->fts_accpath);

      if(std::string(node->fts_name) == "status")
      {
        qDebug() << "Found file " << file_name.c_str() << " in " << node->fts_accpath << " at level " << node->fts_level;
        std::fstream process_file(file_name.c_str(), std::fstream::in);
        std::string line;
        while(std::getline(process_file, line))
        {
          if(std::string::npos != line.find("Pid:"))
          {
            qDebug() << line.c_str();
          }
        }
      }
    }
  }

  if(fts_close(file_tree))
  {
    return;
  }
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
