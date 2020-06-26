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
    bool operator==(PaintedItem& other);

    Q_INVOKABLE void setImage(QString image, int width, int height);
    Q_INVOKABLE void setPixmap(QPixmap pixmap);
    Q_INVOKABLE void fitToitem(int originalHeight, int originalWidth, int height, int width);
    Q_INVOKABLE void saveImage(QString path, QString quality);

    Q_INVOKABLE void onMouseReleased();

    Q_INVOKABLE void addBackup();
    Q_INVOKABLE void addBackup(QImage newUndo);
    Q_INVOKABLE void loadBackup();
    Q_INVOKABLE void addRedo(QImage newRedo);
    Q_INVOKABLE void loadRedo();

    Q_INVOKABLE void blurImage(int radius);
    Q_INVOKABLE void contrastImage(int contrast, int x, int y, int brushSize);
    Q_INVOKABLE void sharpenImage(int value, int x, int y, int brushSize);

    Q_INVOKABLE int getWidth();
    Q_INVOKABLE void setWidth(int newWidth);
    Q_INVOKABLE int getHeight();
    Q_INVOKABLE void setHeight(int newHeight);

    Q_INVOKABLE int getX();
    Q_INVOKABLE void setX(int newX);
    Q_INVOKABLE int getY();
    Q_INVOKABLE void setY(int newY);

    Q_INVOKABLE QString getPixel(int row, int col);

private:
    QImage originalImage;
    QImage currentImage;
    QPixmap imagePixmap;

    std::list<QImage> backupList;
    std::list<QImage> redoList;

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
