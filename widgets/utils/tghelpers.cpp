#include "tghelpers.h"

#include <QString>

QString Helpers::toString(const std::string &string)
{
    return QString::fromStdString(string);
}
