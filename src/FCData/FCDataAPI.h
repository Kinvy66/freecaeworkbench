#ifndef FCDATAAPI_H
#define FCDATAAPI_H
#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCDATA_BUILDLIB)
#define FCDATA_API Q_DECL_EXPORT
#else
#define FCDATA_API Q_DECL_IMPORT
#endif

#endif // FCDATAAPI_H
