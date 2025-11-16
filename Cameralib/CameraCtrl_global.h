#ifndef CAMERACTRL_GLOBAL_H
#define CAMERACTRL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CAMERACTRL_LIBRARY)
#  define CAMERACTRL_EXPORT Q_DECL_EXPORT
#else
#  define CAMERACTRL_EXPORT Q_DECL_IMPORT
#endif

#endif // CAMERACTRL_GLOBAL_H
