#include "processitem.h"

#include <QDebug>

//---------------------------------------------------------
ProcessItem::ProcessItem(const pid_t process_id, ProcessItem* parent) :
  m_process_id(process_id),
  m_parent(parent)
{
}
//---------------------------------------------------------
void ProcessItem::append_child(ProcessItem *item)
{
  if(item)
  {
    m_children.push_back(item);
  }
  else
  {
    qWarning() << "Wrong parameter!";
  }
}
//---------------------------------------------------------
ProcessItem* ProcessItem::child(const int row)
{
  if((row < 0) || (row >= m_children.size()))
  {
    qWarning() << "Wrong parameter!";
  }

  return m_children[row];
}
//---------------------------------------------------------
int ProcessItem::child_count() const
{
  return m_children.size();
}
//---------------------------------------------------------
int ProcessItem::column_count()
{
  return m_data.size()
}
//---------------------------------------------------------
int ProcessItem::row()
{
  if(m_parent)
  {
    return m_parent->m_children
  }
}

