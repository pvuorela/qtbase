# Qt/Windows only configuration file
# --------------------------------------------------------------------

INCLUDEPATH += ../3rdparty/wintab
!wince* {
    LIBS_PRIVATE *= -lshell32
}
