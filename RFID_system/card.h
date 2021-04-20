#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <linux/input.h>
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include <QtDebug>

#define input_eventx  "/dev/input/event18"		//输入设备号

using namespace std;
class Card:public QObject
{
    Q_OBJECT
public:
    explicit Card(QObject *parent = nullptr);
    int fd;
    int GET_ID(char* ID);
    struct input_event i_event;
    Card(string eventx);
    ~Card();


public slots:

//    void cardslots();
signals:



};

#endif // CARD_H
