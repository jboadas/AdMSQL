HEADERS       = window.h
SOURCES       = main.cpp \
                window.cpp
RESOURCES     = iconos.qrc
QT           += svg \
                script

OTHER_FILES += \
    mensajes.js \
    AdMySQL.rc

RC_FILE = AdMySQL.rc
