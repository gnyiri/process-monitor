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
  if((row < 0) || (static_cast<unsigned int>(row) >= m_children.size()))
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
int ProcessItem::column_count() const
{
  return m_data.size();
}
//---------------------------------------------------------
int ProcessItem::row() const
{
  int l_row = 0;

  if(m_parent)
  {   
    for(auto it = m_parent->m_children.begin(); it != m_parent->m_children.end(); it++)
    {
      if (*it == this)
      {
        break;
      }
      l_row++;
    }
  }

  return l_row;
}
//---------------------------------------------------------
ProcessItem* ProcessItem::parent()
{
  return m_parent;
}

