#ifndef PROCESSITEM_H
#define PROCESSITEM_H

#include <unistd.h>
#include <vector>

#include <QVariant>

class ProcessItem
{
public:
  /*!
   * \brief ProcessItem
   * \param process_id
   * \param parent
   */
  ProcessItem(const pid_t process_id, ProcessItem* parent = 0);
  /*!
   * \brief append_child
   * \param item
   */
  void append_child(ProcessItem* item);
  /*!
   * \brief child
   * \param row
   * \return
   */
  ProcessItem* child(const int row);
  /*!
   * \brief child_count
   * \return
   */
  int child_count() const;
  /*!
   * \brief column_count
   * \return
   */
  int column_count() const;
  /*!
   * \brief row
   * \return
   */
  int row() const;
  /*!
   * \brief parent
   * \return
   */
  ProcessItem* parent();
private:
  /*!
   * \brief m_process_id
   */
  pid_t m_process_id;
  /*!
   * \brief m_parent
   */
  ProcessItem* m_parent;
  /*!
   * \brief m_children
   */
  std::vector<ProcessItem*> m_children;
  /*!
   * \brief m_data
   */
  std::vector<QVariant> m_data;
};

#endif // PROCESSITEM_H
