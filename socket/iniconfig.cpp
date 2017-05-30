#include "iniconfig.h"

IniConfig::IniConfig(QString szIniPath)
    : QSettings(szIniPath, QSettings::IniFormat)
{

}

void IniConfig::SetValue(QString section, QString key, QVariant value)
{
    beginGroup(section);
    setValue(key, value);
    endGroup();
}


QVariant IniConfig::GetValue(QString section, QString key, QVariant defaultValue)
{
    beginGroup(section);
    QVariant val = value(key, defaultValue);
    endGroup();
    SetValue(section, key, val);
    return val;
}
