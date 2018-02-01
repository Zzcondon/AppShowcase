#include "logger.h"

#include <QFile>
#include <QDebug>
#include <QDir>

#include "time.h"

using namespace logger;


Logger::Logger(QObject* parent): QObject(parent),
log(),
logFilename(""),
logLevel(LogType::LOG_INFO),
overrideName_flag(false),
configFilename(),
error_flag(false)
{

}

Logger::~Logger() {
    close();
}

bool Logger::init(QString config) {
    bool initSuccess_flag = true;

    //Look For config Options
    configFilename = config;
    QFile configFile(configFilename);

    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
         // Read in overriding filename

        configFile.close();

        initSuccess_flag &= openLogFile();
    }
    else {
        initSuccess_flag = false;
    }

    return initSuccess_flag;
}

void Logger::close() {
    bool renameLog_flag = true;

    if (logFile.isOpen()) {
        if (!overrideName_flag) {
            QFile oldLog("log.txt");
            if (oldLog.exists()) {
                if (!oldLog.remove()) {
                    err("Unable to Remove Old log file \"log.txt\"");
                    renameLog_flag = false;
                }
            }

            if (renameLog_flag) {
                if (!logFile.rename("log.txt")) {
                    err("Unable to Rename log file to \"log.txt\"");
                }
            }
        }

        logFile.close();
    }

}

void Logger::setLogLevel(LogType type) {
    logLevel = type;
}

bool Logger::openLogFile() {
    bool openSuccess_flag = true;

    if (logFilename.isEmpty()) {
        logFilename = QString("log_%1.txt").arg(getTimestamp());
    }

    logFile.setFileName(logFilename);

    if (logFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        logStream.setDevice(&logFile);
        logStream << "Initialized Logger " << getTimestamp() << endl;
    }
    else {
        openSuccess_flag = false;
    }

    return openSuccess_flag;
}

QString Logger::getTimestamp() {
    QString timestamp;
    time_t timer = time(NULL);
    struct tm *time = gmtime(&timer);
    if ((time->tm_year + 1900) >= 2015) {
        timestamp = QString("%1%2%3-%4%5%6").arg(time->tm_year + 1900).arg(time->tm_mon + 1, 2, 10, QChar('0')).arg(time->tm_mday, 2, 10, QChar('0'))
                                            .arg(time->tm_hour, 2, 10, QChar('0')).arg(time->tm_min, 2, 10, QChar('0')).arg(time->tm_sec, 2, 10, QChar('0'));
    }

    return timestamp;
}

void Logger::trace(QString nMsg) {

    if (logLevel <= LogType::LOG_TRACE) {
        if (!error_flag) {
            QString logMsg("TRACE - " + nMsg);
            qDebug().noquote() << logMsg;

            logMsg.append("\n");

            log.append(logMsg);
            logStream << logMsg;
        }
    }
}

void Logger::debug(QString nMsg) {

    if (logLevel <= LogType::LOG_DEBUG) {
        if (!error_flag) {
            QString logMsg("DEBUG - " + nMsg);
            qDebug().noquote() << logMsg;

            logMsg.append("\n");

            log.append(logMsg);
            logStream << logMsg;
            logStream.flush();
        }
    }
}

void Logger::info(QString nMsg) {

    if (logLevel <= LogType::LOG_INFO) {
        if (!error_flag) {
            QString logMsg("INFO - " + nMsg);
            qDebug().noquote() << logMsg;

            logMsg.append("\n");

            log.append(logMsg);
            logStream << logMsg;
            logStream.flush();
        }
    }
}

void Logger::warn(QString nMsg) {

    if (logLevel <= LogType::LOG_WARN) {
        if (!error_flag) {
            QString logMsg("WARN - " + nMsg);
            qDebug().noquote() << logMsg;

            logMsg.append("\n");

            log.append(logMsg);
            logStream << logMsg;
            logStream.flush();
        }
    }
}

void Logger::err(QString nMsg) {

    if (logLevel <= LogType::LOG_ERROR) {
        if (!error_flag) {
            QString logMsg("ERROR - " + nMsg);
            qDebug().noquote() << logMsg;

            logMsg.append("\n");

            log.append(logMsg);
            logStream << logMsg;
            logStream.flush();
        }
    }
}

QString Logger::getLogString() {
    return log;
}
