#ifndef PROCESSTREEMODEL_H
#define PROCESSTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ProcessItem;

class ProcessTreeModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  /*!
   * \brief ProcessTreeModel
   * \param parent
   */
  explicit ProcessTreeModel(QObject* parent = 0);
  /*!
   * \brief ~ProcessTreeModel
   */
  ~ProcessTreeModel();
private:
  /*!
   * \brief data
   * \param index
   * \param role
   * \return
   */
  QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
  /*!
   * \brief flags
   * \param index
   * \return
   */
  Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
  /*!
   * \brief headerData
   * \param section
   * \param orientation
   * \param role
   * \return
   */
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  /*!
   * \brief index
   * \param row
   * \param column
   * \param parent
   * \return
   */
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  /*!
   * \brief parent
   * \param index
   * \return
   */
  QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
  /*!
   * \brief rowCount
   * \param parent
   * \return
   */
  int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  /*!
   * \brief columnCount
   * \param parent
   * \return
   */
  int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
private:
  /*!
   * \brief m_root_item
   */
  ProcessItem* m_root_item;
};

#endif // PROCESSTREEMODEL_H
