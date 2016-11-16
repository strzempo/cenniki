#ifndef MAINTREEMODEL_H
#define MAINTREEMODEL_H

#include <QAbstractItemModel>
class TreeComponent;

class MainTreeModel : public QAbstractItemModel
{
    Q_OBJECT
  //  Q_PROPERTY(QModelIndex index READ index)

public:
    explicit MainTreeModel(QObject *parent = 0);
    ~MainTreeModel();

    // Header:
    QVariant headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role = Qt::DisplayRole*/) const override;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //serialization
    void save();
    void load();

    void generateSampleTree();

    //for qml
    enum ItemRoles
    {
        nodeNameRole = Qt::UserRole + 1
    };
    QHash<int, QByteArray> roleNames() const override;

private:
    TreeComponent* m_rootComponent;
};

#endif // MAINTREEMODEL_H
