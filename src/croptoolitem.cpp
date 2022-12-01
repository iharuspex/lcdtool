#include "croptoolitem.h"

CropToolItem::CropToolItem(QObject *parent) : QObject(parent) {}

CropToolItem::~CropToolItem() = default;

QRectF CropToolItem::boundingRect() const {
    return {0, 0, 100, 100};
}

void CropToolItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::PenStyle::DashLine);
    painter->drawRect(0, 0, 200, 200);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


