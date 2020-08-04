#pragma once

#include <QTextStream>

class TextStream : public QTextStream
{
public:
    TextStream();
    using QTextStream::QTextStream;
    using QTextStream::operator<<;
    QTextStream &operator<<(const std::string &string);
};

