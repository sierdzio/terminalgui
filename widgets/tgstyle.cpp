#include "tgstyle.h"

// TODO: rethink and refactor. This approach is pretty dumb!
void Tg::Style::setBorderStyleValues(const Tg::BorderStyle &borderStyle)
{
    border->width = borderStyle.width;
    border->topLeft = borderStyle.topLeft;
    border->topRight = borderStyle.topRight;
    border->bottomLeft = borderStyle.bottomLeft;
    border->bottomRight = borderStyle.bottomRight;
    border->horizontal = borderStyle.horizontal;
    border->vertical = borderStyle.vertical;
    border->textColor = borderStyle.textColor;
    border->backgroundColor = borderStyle.backgroundColor;
}
