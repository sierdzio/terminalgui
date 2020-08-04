#include "textstream.h"

TextStream::TextStream() : QTextStream()
{
}

QTextStream &TextStream::operator<<(const std::string &string)
{
    QTextStream::operator<<(QString::fromStdString(string));
    return (*this);
}
