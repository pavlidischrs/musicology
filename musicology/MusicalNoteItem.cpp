#include "musicalNoteItem.h"

#include <QDebug>

#include "mainwindow.h"


using namespace Music;

MusicalNoteItem::MusicalNoteItem(int itemID):QGraphicsPixmapItem()
{

    itemID_ = itemID;
}

void MusicalNoteItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

//        qDebug() << "Click event grapped from item with ID: "<< itemID_;

        emit updatePentagramSignal(itemID_);
    }
}

