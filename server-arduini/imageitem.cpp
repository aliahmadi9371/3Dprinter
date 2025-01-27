// ImageItem.cpp
#include "imageitem.h"

ImageItem::ImageItem(QQuickItem *parent) : QQuickPaintedItem(parent)
{
  this->current_image = QImage("./black.png");
//    this->current_image = QImage("./image_print1.png");
}

void ImageItem::paint(QPainter *painter)
{
    QRectF bounding_rect = boundingRect();
    QImage scaled = this->current_image.scaledToHeight(bounding_rect.height());
    QPointF center = bounding_rect.center() - scaled.rect().center();

    if(center.x() < 0)
        center.setX(0);
    if(center.y() < 0)
        center.setY(0);
   painter->drawImage(center, scaled);
}

QImage ImageItem::image() const
{
    return this->current_image;
}

void ImageItem::setImage(const QImage &image)
{
//    this->current_image;
//    update();
    this->current_image = image;
//    emit imageChanged();
    update();
//    emit renderTarget();

}
