#ifndef LCDTOOL_CROPTOOLITEM_H
#define LCDTOOL_CROPTOOLITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class CropToolItem : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit CropToolItem(QObject *parent = nullptr);
    ~CropToolItem() override;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif //LCDTOOL_CROPTOOLITEM_H
