#include "circlemanager.h"

CircleManager::CircleManager(QObject *parent) : QObject(parent)
{
    mCircles.reserve(maxModelSize);
    for (int i = 0; i < maxModelSize; ++i) {
        mCircles << Circle{ mFieldWidth, mFieldHeight };
    }
}

QPoint CircleManager::position(int index) const
{
    if (index >= 0 && index < maxModelSize) {
        return mCircles.at(index).mPoint;
    }
    return QPoint();
}

QColor CircleManager::color(int index) const
{
    if (index >= 0 && index < maxModelSize) {
        return mCircles.at(index).mColor;
    }
    return QColor();
}

void CircleManager::update(int &position, int &velocity, int maxPosition)
{
    position += velocity;
    if (position <= 0 || position >= maxPosition) {
        velocity *= -1;
    }
}

void CircleManager::simulate()
{
    for (auto &circle : mCircles) {
        update(circle.mPoint.rx(), circle.mVelocity.rx(), mFieldWidth);
        update(circle.mPoint.ry(), circle.mVelocity.ry(), mFieldHeight);
    }
}
