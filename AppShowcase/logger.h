#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

namespace logger {

enum LogType {
    LOG_TRACE = 0,
    LOG_DEBUG = 1,
    LOG_INFO  = 2,
    LOG_WARN  = 3,
    LOG_ERROR = 4
};


class Logger : QObject
{
    Q_OBJECT

public:
    Logger(QObject *parent = 0);
    ~Logger();

    bool init(QString config);
    bool openLogFile();
    void close();

    void setLogLevel(LogType type);

    QString getTimestamp();

    void trace(QString nMsg);
    void debug(QString nMsg);
    void info(QString nMsg);
    void warn(QString nMsg);
    void err(QString nMsg);

    QString getLogString();

    QString     log;
    QString     logFilename;
    QFile       logFile;
    QTextStream logStream;

    LogType     logLevel;

    bool        overrideName_flag;

    QString     configFilename;

    bool error_flag;
};

}

#endif // LOGGER_H
