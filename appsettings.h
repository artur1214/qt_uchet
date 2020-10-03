#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QList>
#include <qstring.h>



class AppSettings
{
public:
    struct RequestStatus{
        QString id;
        QString desc;
        QString color;
        RequestStatus(QString id, QString desc, QString color);
    };
    enum DisplayWorksTypes{
        Block = 1,
        String = 2
    };
    static QList<RequestStatus> statuses;
    //AppSettings();
    static QString curUser;
    QList<AppSettings::RequestStatus> getStatuses();
private:
    AppSettings();
};

#endif // APPSETTINGS_H
