# Developer guide

## Quick start

Let's start with something simple and easy:

```
#include <QCoreApplication>
#include <tgterminal.h>
#include <tgscreen.h>
#include <widgets/tglabel.h>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  Tg::RawTerminalLocker locker;
  Tg::Screen screen;
  Tg::Label label("Hello world!", &screen);
  label.show();

  return app.exec();
}
```

Terminal GUI uses Qt, so we need a QCoreApplication instance, and we run its
event loop using `app.exec()`.

Then we need 2 objects which are not so obvious: terminal locker and screen.

`RawTerminalLocker` is a simple RAII object which ensures that terminal runs in
proper echo mode, and that original echo mode is restored when application
quits.

`Screen` is a space (within the terminal) to draw widgets on. By default, it
fills whole terminal window, but can be manually adjusted.

Then, we start with some actual GUI: `Label` is a `Widget` which can be used to
draw text easily.

When you run this example, you will notice that `Label` has a border - that's
the default behavior when a `Widget` is *not a child of another widget*. If you
don't want the border, you can easily turn it off using
`Label::setBorderVisible(false)`.
