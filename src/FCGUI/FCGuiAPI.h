#ifndef FCGUIAPI_H
#define FCGUIAPI_H
#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCGUI_BUILDLIB)
#define FCGUI_API Q_DECL_EXPORT
#else
#ifdef Q_CC_MSVC
#define FCGUI_API Q_DECL_IMPORT
#else
#define FCGUI_API Q_DECL_IMPORT
#endif
#endif

#endif // FCGUIAPI_H
