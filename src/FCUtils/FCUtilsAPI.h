#ifndef FCUTILSAPI_H
#define FCUTILSAPI_H
#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCUTILS_BUILD)
#define FCUTILS_API Q_DECL_EXPORT
#else
#define FCUTILS_API Q_DECL_IMPORT
#endif

// Q_DECL_IMPORT.

#endif // FCUTILSAPI_H
