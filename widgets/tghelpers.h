#pragma once

/*!
 * Makes sure `condition` is true, otherwise crashes the application.
 *
 * This is useful when using connect(), QMetaObject::invokeMethod() and other
 * similar pieces of code which should ALWAYS return true, but if developer
 * makes a mistake they only print warnings which are easy to miss.
 *
 \\verbatim
CHECK(connect(object, &Class::someSignal,
              receiver, &OtherClass:someSlot,
              Qt::QueuedConnection));

CHECK(QMetaObject::invokeMethod(
    object, "functionName",
    Qt::QueuedConnection,
    Q_ARG(QVector, something));
 \\endverbatim
 *
 */
#if !defined(CHECK)
#if defined(DEBUG_BUILD)
#define CHECK(condition) if (!condition) qFatal("Check failed!")
#else
#define CHECK(condition) condition
#endif
#endif

