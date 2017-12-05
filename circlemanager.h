#ifndef CIRCLEMANAGER_H
#define CIRCLEMANAGER_H

#include <QObject>
#include <QSize>
#include <QPoint>
#include <QColor>

struct Circle {
    Circle(int width = 600, int height = 600)
        : mPoint(randomValue(width), randomValue(height))
        , mColor(QColor::colorNames().at(randomValue(QColor::colorNames().size())))
        , mVelocity(randomDirection() * randomValue(3), randomDirection() * randomValue(3))
        , mIsReadyToDie(false)
    { }

    inline int randomValue(int maxRandom) { return qrand() % maxRandom + 1; }
    inline int randomDirection() { return qrand() % 2 ? 1 : -1; }

    QPoint mPoint;
    QColor mColor;
    QPoint mVelocity;
    bool mIsReadyToDie;
};

class CircleManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int fieldWidth READ fieldWidth WRITE setFieldWidth NOTIFY fieldWidthChanged)
    Q_PROPERTY(int fieldHeight READ fieldHeight WRITE setFieldHeight NOTIFY fieldHeightChanged)

public:
    explicit CircleManager(QObject *parent = 0);

    int fieldWidth() const { return mFieldWidth; }
    void setFieldWidth(int size) {
        mFieldWidth = size;
        emit fieldWidthChanged();
    }

    int fieldHeight() const { return mFieldHeight; }
    void setFieldHeight(int size) {
        mFieldHeight = size;
        emit fieldHeightChanged();
    }

    int circleListSize() const { return mCircles.size(); }
    QPoint position(int index) const;
    QColor color(int index) const;
    bool isReadyToDie(int index) const { return mCircles.at(index).mIsReadyToDie; }

    void removeCircle(int index) { mCircles.removeAt(index); }
    void changeColor(int index) {
        mCircles[index].mColor = mCircles[index].mColor.light();
        mCircles[index].mIsReadyToDie = true;
    }

    void update(int &position, int &velocity, int maxPosition);
    void simulate();

signals:
    void fieldWidthChanged();
    void fieldHeightChanged();

private:
    int mFieldWidth = 600;
    int mFieldHeight = 600;
    QList<Circle> mCircles;

    const int maxModelSize = 10;
};

#endif // CIRCLEMANAGER_H
