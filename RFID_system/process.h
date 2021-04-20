#ifndef PROCESS_H
#define PROCESS_H

#include "card.h"
#include "usart.h"
#include <QThread>
#include <QMutex>

class Process : public QThread
{
      Q_OBJECT
public:
        explicit Process(QObject *parent = 0);

    void run() override;
    Card* IC;


private:
    char ID[50];

signals:
    //给主线程发消息
    void send_rifdID(char *);

};


class Process2 : public QThread
{
      Q_OBJECT
public:
        explicit Process2(QObject *parent = 0);

        void run() override;

        USART  *mlx90614;

private:
    QMutex mutex;
    float Temp;

signals:
    //给主线程发消息
    void send_Temperature(float);

};



#endif

