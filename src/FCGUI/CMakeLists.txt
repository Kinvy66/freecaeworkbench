cmake_minimum_required(VERSION 3.5)
fcmacro_lib_setting(
    "FCGui"
    "FC GUI | https://github.com/kinvy66"
    0
    0
    3
)

########################################################
# Qt
########################################################
set(FC_MIN_QT_VERSION 5.14)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} ${FC_MIN_QT_VERSION} COMPONENTS
    Core
    Gui
    Widgets
    Xml
    Svg
    REQUIRED
)
