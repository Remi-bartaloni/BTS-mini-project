#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "mesures.h"
#include <QMetaType>

class MyThread : public QThread
{
    Q_OBJECT

    bool is_running;

public:
    explicit MyThread(QObject *parent = 0);
    void stop();
    void run();

    void automatique();

    //bool get_eta() const { return (is_running);}

signals:
    void acquerir();
    void acquerir(Mesures);

};

#endif // MYTHREAD_H
