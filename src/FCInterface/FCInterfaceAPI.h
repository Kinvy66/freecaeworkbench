#ifndef FCINTERFACEGLOBAL_H
#define FCINTERFACEGLOBAL_H
#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCINTERFACE_BUILDLIB)
#define FCINTERFACE_API		Q_DECL_EXPORT
#else
#define FCINTERFACE_API		Q_DECL_IMPORT
#endif

#endif // FCINTERFACEGLOBAL_H
