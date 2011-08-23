#ifndef QTMSENSORSGLOBAL_H
#define QTMSENSORSGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#  if defined(QT_NODLL)
#    undef QT_MAKEDLL
#    undef QT_DLL
#  elif defined(QT_MAKEDLL)        /* create a Qt DLL library */
#    if defined(QT_DLL)
#      undef QT_DLL
#    endif
#    if defined(QT_BUILD_SENSORS1_LIB)
#      define QTM_SENSORS_EXPORT Q_DECL_EXPORT
#    else
#      define QTM_SENSORS_EXPORT Q_DECL_IMPORT
#    endif
#    define Q_TEMPLATEDLL
#  elif defined(QT_DLL) /* use a Qt DLL library */
#    define QTM_SENSORS_EXPORT Q_DECL_IMPORT
#    define Q_TEMPLATEDLL
#  endif
#  define Q_NO_DECLARED_NOT_DEFINED
#else
#  if defined(Q_OS_LINUX) && defined(Q_CC_BOR)
#    define Q_TEMPLATEDLL
#    define Q_NO_DECLARED_NOT_DEFINED
#  endif
#  undef QT_MAKEDLL /* ignore these for other platforms */
#  undef QT_DLL
#endif

#if !defined(QTM_SENSORS_EXPORT)
#  if defined(QT_SHARED)
#    define QTM_SENSORS_EXPORT Q_DECL_EXPORT
#  else
#    define QTM_SENSORS_EXPORT
#  endif
#endif

#define QTM_BEGIN_NAMESPACE namespace QtMobility {
#define QTM_END_NAMESPACE }
#define QTM_USE_NAMESPACE using namespace QtMobility;
#define QTM_PREPEND_NAMESPACE(x) QtMobility::x

#if QT_PREPEND_NAMESPACE
#define NEW_NAMESPACE(x) QT_PREPEND_NAMESPACE(x)
#else
#define NEW_NAMESPACE(x) ::x
#endif

#endif
