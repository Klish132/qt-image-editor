#include "painteditem.h"
#include <QLabel>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <math.h>

PaintedItem::PaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_itemWidth = 0;
    m_itemHeight = 0;
    m_itemX = 0;
    m_itemY = 0;
}

QRectF PaintedItem::boundingRect() const
{
    return QRectF(m_itemX, m_itemY, m_itemWidth, m_itemHeight);
}

void PaintedItem::paint(QPainter *painter)
{
    painter->drawImage(boundingRect(), currentImage);
    painter->setPen(QPen(Qt::black, 2, Qt::DashLine));
    painter->drawRect(boundingRect());
}

void PaintedItem::setImage(QString image)
{
    QImage tempImage;
    tempImage.load(image);
    setWidth(tempImage.width());
    setHeight(tempImage.height());
    setX(tempImage.rect().x());
    setY(tempImage.rect().y());
    originalImage = tempImage;
    currentImage = tempImage;
    backupList.clear();
    addBackup(currentImage);
    update();
    setPixmap(QPixmap::fromImage(currentImage));
}

void PaintedItem::fitToitem(int height, int width)
{
    if (m_itemWidth > m_itemHeight) {
        float calc = ((width*100)/(float)m_itemWidth)/100;
        setHeight(m_itemHeight* calc);
        setWidth(width);
    } else {
        float calc = ((height*100)/(float)m_itemHeight)/100;
        setWidth(m_itemWidth* calc);
        setHeight(height);
    }
}

void PaintedItem::saveImage(QString path, QString quality)
{
    currentImage.save(path, 0, quality.toInt());
}

void PaintedItem::addBackup(QImage newBackup)
{
    if (backupList.size() == 11)
        backupList.pop_back();
    backupList.push_front(newBackup);
}

void PaintedItem::loadBackup()
{
    if (backupList.size() == 1)
        return;
    else {
        QImage loadedBackup = backupList.front();
        backupList.pop_front();
        currentImage = loadedBackup;
    }
    update();
}

void PaintedItem::setPixmap(QPixmap pixmap)
{
    imagePixmap = pixmap;
}

void PaintedItem::blurImage(int radius)
{
    addBackup(currentImage);
    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
    int alpha = (radius < 1)  ? 16 : (radius > 17) ? 1 : tab[radius-1];

    QImage result = currentImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    int r1 = currentImage.rect().top();
    int r2 = currentImage.rect().bottom();
    int c1 = currentImage.rect().left();
    int c2 = currentImage.rect().right();

    int bpl = result.bytesPerLine();
    int rgba[4];
    unsigned char* p;

    int i1 = 0;
    int i2 = 3;

    //if (alphaOnly)
       //i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

    for (int col = c1; col <= c2; col++) {
       p = result.scanLine(r1) + col * 4;
       for (int i = i1; i <= i2; i++)
           rgba[i] = p[i] << 4;

       p += bpl;
       for (int j = r1; j < r2; j++, p += bpl)
           for (int i = i1; i <= i2; i++)
               p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
       p = result.scanLine(row) + c1 * 4;
       for (int i = i1; i <= i2; i++)
           rgba[i] = p[i] << 4;

       p += 4;
       for (int j = c1; j < c2; j++, p += 4)
           for (int i = i1; i <= i2; i++)
               p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int col = c1; col <= c2; col++) {
       p = result.scanLine(r2) + col * 4;
       for (int i = i1; i <= i2; i++)
           rgba[i] = p[i] << 4;

       p -= bpl;
       for (int j = r1; j < r2; j++, p -= bpl)
           for (int i = i1; i <= i2; i++)
               p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
       p = result.scanLine(row) + c2 * 4;
       for (int i = i1; i <= i2; i++)
           rgba[i] = p[i] << 4;

       p -= 4;
       for (int j = c1; j < c2; j++, p -= 4)
           for (int i = i1; i <= i2; i++)
               p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }
    currentImage = result;
    update();
}

int Truncate(int value) {
    if (value > 255)
        return 255;
    else if (value < 0)
        return 0;
    else
        return value;
}

void PaintedItem::contrastImage(int contrast)
{
    addBackup(currentImage);
    qDebug() << contrast;
    QImage result = currentImage.convertToFormat(QImage::Format_ARGB32);
    int r1 = currentImage.rect().top();
    int r2 = currentImage.rect().bottom();
    int c1 = currentImage.rect().left();
    int c2 = currentImage.rect().right();

    float factor = (259 * (contrast + 255)) / (255 * (259 - contrast));

    for (int row = r1; row <= r2; row++) {
        QRgb *rowData = (QRgb*)result.scanLine(row);
        for (int col = c1; col <= c2; col++) {
            QRgb pixelData = rowData[col];
            int newRed = Truncate(factor * (qRed(pixelData) - 128) + 128);
            int newGreen = Truncate(factor * (qGreen(pixelData) - 128) + 128);
            int newBlue = Truncate(factor * (qBlue(pixelData) - 128) + 128);
            int alpha = qAlpha(pixelData);
            rowData[col] = qRgba(newRed, newGreen, newBlue, alpha);
        }
    }
    qDebug() << "Finished";
    currentImage = result;
    update();
}

int PaintedItem::getWidth()
{
    return m_itemWidth;
}

void PaintedItem::setWidth(int newWidth)
{
    m_itemWidth = newWidth;
    update();
    emit widthChanged();
}

int PaintedItem::getHeight()
{
    return m_itemHeight;
}

void PaintedItem::setHeight(int newHeight)
{
    m_itemHeight = newHeight;
    update();
    emit heightChanged();
}

int PaintedItem::getX()
{
    return m_itemX;
}

void PaintedItem::setX(int newX)
{
    m_itemX = newX;
    update();
    emit xChanged();
}

int PaintedItem::getY()
{
    return m_itemY;
}

void PaintedItem::setY(int newY)
{
    m_itemY = newY;
    update();
    emit yChanged();
}
