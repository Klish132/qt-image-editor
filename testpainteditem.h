#ifndef TESTPAINTEDITEM_H
#define TESTPAINTEDITEM_H

#include <QtTest/QtTest>
#include <QObject>

class TestPaintedItem : public QObject
{
    Q_OBJECT

public:
    explicit TestPaintedItem(QObject *parent = 0);

private slots:
    void blurImage();
    void contrastImage();
    void sharpenImage();
};

#endif // TESTPAINTEDITEM_H
