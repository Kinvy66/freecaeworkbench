#ifndef FCCORE_H
#define FCCORE_H

#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCCORE_BUILDLIB)
#define FCCORE_API Q_DECL_EXPORT
#else
#ifdef Q_CC_MSVC
#define FCCORE_API Q_DECL_IMPORT
#else
#define FCCORE_API Q_DECL_IMPORT
#endif
#endif

#endif // FCCORE_H
