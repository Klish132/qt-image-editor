#ifndef PAINTEDITEM_H
#define PAINTEDITEM_H
#include <QQuickPaintedItem>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <list>

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int itemWidth READ getWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int itemHeight READ getHeight WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int itemX READ getX WRITE setX NOTIFY xChanged);
    Q_PROPERTY(int itemY READ getY WRITE setY NOTIFY yChanged);
public:
    PaintedItem(QQuickItem *parent = 0);
    void paint(QPainter *painter) override;
    QRectF boundingRect() const override;

    Q_INVOKABLE void setImage(QString image);
    Q_INVOKABLE void setPixmap(QPixmap pixmap);
    Q_INVOKABLE void fitToitem(int height, int width);
    Q_INVOKABLE void saveImage(QString path, QString quality);
    Q_INVOKABLE void addBackup(QImage newBackup);
    Q_INVOKABLE void loadBackup();
    Q_INVOKABLE void blurImage(int radius);
    Q_INVOKABLE void contrastImage(int contrast);

    Q_INVOKABLE int getWidth();
    Q_INVOKABLE void setWidth(int newWidth);
    Q_INVOKABLE int getHeight();
    Q_INVOKABLE void setHeight(int newHeight);

    Q_INVOKABLE int getX();
    Q_INVOKABLE void setX(int newX);
    Q_INVOKABLE int getY();
    Q_INVOKABLE void setY(int newY);
private:
    QImage originalImage;
    QImage currentImage;
    QPixmap imagePixmap;

    std::list<QImage> backupList;

    int m_itemWidth;
    int m_itemHeight;

    int m_itemX;
    int m_itemY;
signals:
    void widthChanged();
    void heightChanged();

    void xChanged();
    void yChanged();
};

#endif // PAINTEDITEM_H
