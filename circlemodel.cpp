
#include <QDebug>
#include <QColor>
#include <QTimer>

#include "circlemodel.h"
#include "circlemanager.h"

CircleModel::CircleModel(QObject *parent) : QAbstractListModel(parent)
{
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]() {
        if (mCircleManager) {
            mCircleManager->simulate();
        }

        for (int i = 0; i < mCircleManager->circleListSize(); ++i) {
            emit dataChanged(createIndex(i, 0), createIndex(i, 0));
        }
    });

    timer->start(100);
}

int CircleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mCircleManager->circleListSize();
}

QVariant CircleModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case CirclePosX:
        return mCircleManager->position(index.row()).x();
        break;
    case CirclePosY:
        return mCircleManager->position(index.row()).y();
        break;
    case CircleColor:
        return mCircleManager->color(index.row()).name();
        break;
    case ReadyToDie:
        return mCircleManager->isReadyToDie(index.row());
        break;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> CircleModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[CirclePosX] = "circlePosX";
    roleNames[CirclePosY] = "circlePosY";
    roleNames[CircleColor] = "circleColor";
    roleNames[ReadyToDie] = "isReadyToDie";

    return roleNames;
}

void CircleModel::changeColor(int index)
{
    if (index < 0 || index >= mCircleManager->circleListSize()) {
        return;
    }

    mCircleManager->changeColor(index);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

void CircleModel::removeCircle(int index)
{
    if (index < 0 || index >= mCircleManager->circleListSize()) {
        return;
    }

    emit beginRemoveRows(QModelIndex(), index, index);
    mCircleManager->removeCircle(index);
    emit endRemoveRows();
}
