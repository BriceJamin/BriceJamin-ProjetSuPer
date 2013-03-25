#ifndef G_H
#define G_H

#include <QObject>

class G : public QObject
{
    Q_OBJECT
public slots:
    void slotG_H_started();
    void slotG_H_finished();
public:
    G(QObject*);
    ~G();
};

#endif // G_H
