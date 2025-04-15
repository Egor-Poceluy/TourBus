#ifndef EVENTTYPES_H
#define EVENTTYPES_H

#include <QString>

enum class EventType {
    DatabaseConnectedSuccess,
    DatabaseConnectedError,
    QuerySuccess,
    QueryError,
    LoginSuccess,
    LoginError,
    Logout
};


struct Event {
    EventType type;
    QString data;
};

#endif // EVENTTYPES_H
