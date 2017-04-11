/**
    cenniki - Menu used in CD with promotion materials for Aliaxis Utilities and Industry.
    Copyright (C) 2016  Kamil 'konserw' Strzempowicz, konserw@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef MAINTREEMODEL_H
#define MAINTREEMODEL_H

#include <QAbstractItemModel>
class TreeComponent;

class MainTreeModel : public QAbstractItemModel
{
    Q_OBJECT

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

    //editing
    Q_INVOKABLE bool insertMenu(const QString &title, const QModelIndex &parent);
    Q_INVOKABLE bool insertItem(const QString &title, const QModelIndex &parent);
    Q_INVOKABLE bool insertLink(const QString &title, const QString &url, const QString& opis, const QModelIndex &parent);
    void removeItem(const QModelIndex& index);
    Q_INVOKABLE void removeItem(const QModelIndex& parentIndex, const QModelIndex& index);
    Q_INVOKABLE bool isMenu(const QModelIndex& item) const;
    void reorder(const QModelIndex& parentIndex, int oldPos, int newPos);
    Q_INVOKABLE void reorder(const QModelIndex& parentIndex, const QModelIndex& index, int newPos);

    //serialization
    Q_INVOKABLE void save();
    void load();

    //for qml
    enum ItemRoles
    {
        nodeNameRole = Qt::UserRole + 1,
        nodeAboutRole,
        nodeSequenceRole
    };
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void invokeAction(const QModelIndex& index) const;
    Q_INVOKABLE QString sectionName(const QModelIndex& index) const;

private:
    TreeComponent* RootComponent;
    TreeComponent* getItem(const QModelIndex& index) const;
};

#endif // MAINTREEMODEL_H
