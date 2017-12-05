#ifndef CIRCLEMODEL_H
#define CIRCLEMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "circlemanager.h"

class CircleModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CircleModel(QObject *parent = 0);

    enum RoleNames {
        CirclePosX = Qt::UserRole,
        CirclePosY = Qt::UserRole + 1,
        CircleColor = Qt::UserRole + 2,
        ReadyToDie = Qt::UserRole + 3
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void setManager(CircleManager *manager) { mCircleManager = manager; }

    Q_INVOKABLE void changeColor(int index);
    Q_INVOKABLE void removeCircle(int index);

private:
    CircleManager *mCircleManager;
};

#endif // CIRCLEMODEL_H
