#ifndef INICONFIG_H
#define INICONFIG_H

#include <QSettings>

class IniConfig : public QSettings
{
public:
    IniConfig(QString szIniPath);

    void SetValue(QString section, QString key, QVariant value);
    QVariant GetValue(QString section, QString key, QVariant defaultValue);
};

#endif // INICONFIG_H
