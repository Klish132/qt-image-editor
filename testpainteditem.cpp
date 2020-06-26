#include "testpainteditem.h"
#include "painteditem.h"


TestPaintedItem::TestPaintedItem(QObject *parent) : QObject(parent)
{
}

void TestPaintedItem::blurImage()
{
    PaintedItem test_image;
    test_image.setImage("C:\\Users\\Tuha9\\Desktop\\QtProjects\\ImageEditor\\test_image.png", 50, 50);
    test_image.blurImage(30);

    QVERIFY(test_image.getPixel(0, 0) == "104, 201, 244, 255");
    QVERIFY(test_image.getPixel(24, 24) == "188, 165, 214, 255");
    QVERIFY(test_image.getPixel(49, 49) == "218, 139, 170, 255");
}

void TestPaintedItem::contrastImage()
{
    PaintedItem test_image;
    test_image.setImage("C:\\Users\\Tuha9\\Desktop\\QtProjects\\ImageEditor\\test_image.png", 50, 50);
    test_image.contrastImage(255, 24, 24, 25);

    QVERIFY(test_image.getPixel(0, 0) == "65, 210, 253, 255");
    QVERIFY(test_image.getPixel(24, 24) == "255, 255, 255, 255");
    QVERIFY(test_image.getPixel(49, 49) == "244, 152, 124, 255");
}

void TestPaintedItem::sharpenImage()
{
    PaintedItem test_image;
    test_image.setImage("C:\\Users\\Tuha9\\Desktop\\QtProjects\\ImageEditor\\test_image.png", 50, 50);
    test_image.sharpenImage(90, 24, 24, 25);

    QVERIFY(test_image.getPixel(0, 0) == "65, 210, 253, 255");
    QVERIFY(test_image.getPixel(24, 24) == "221, 177, 255, 255");
    QVERIFY(test_image.getPixel(49, 49) == "244, 152, 124, 255");
}
