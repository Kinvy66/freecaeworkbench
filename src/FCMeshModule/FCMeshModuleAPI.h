#ifndef FCMESHMODULEAPI_H
#define FCMESHMODULEAPI_H

#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCMESHMODULE_BUILDLIB)
#define FCMESHMODULE_API Q_DECL_EXPORT
#else
#define FCMESHMODULE_API Q_DECL_IMPORT
#endif

#endif // FCMESHMODULEAPI_H
