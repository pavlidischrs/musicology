#ifndef MYNOTEITEM_H
#define MYNOTEITEM_H


#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include <QObject>



namespace Music {


class MusicalNoteItem: public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

public:

    MusicalNoteItem(int itemID);

signals:

    // We emit this signal every time a user has clicked a Musical Note from the Choices Box
    void updatePentagramSignal(int);

protected:

    // We override the mousePressEvent so as we could click an Musical Note from
    // the Choices Box
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);


    // The ID of the item
    int itemID_;
};


}



#endif // MYNOTEITEM_H
