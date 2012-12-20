HEADERS += \
    solver.hpp \
    app_headers/app_action.hpp \
    app_headers/app_externalstate.hpp \
    app_headers/app_interactor.hpp \
    app_headers/app_actionexecutor.hpp \
    sys/emulator.hpp \
    app_headers/app_factory.hpp \
    app_headers/app_recognizer.hpp \
    sys/stupidemulator.hpp \
    TriggerImpl/triggeractioneexecutor.hpp \
    TriggerImpl/triggerfactory.hpp \
    app_headers/app_internalstate.hpp \
    app_headers/app_state.hpp \
    sys/clicker.hpp \
    sys/cclicker.h \
    renderarea.hpp \
    TriggerImpl/triggerrecognizer.hpp \
    sys/x_clickemulator.h \
    TriggerImpl/triggerinternalstate.hpp \
    TriggerImpl/triggerexternalstate.hpp \
    TriggerImpl/triggeraction.hpp \
    TriggerImpl/triggerinteractor.hpp \
    MinesImpl/minesrecognizer.hpp \
    MinesImpl/clickcoordreciever.hpp \
    MinesImpl/minesinternalstate.hpp \
    MinesImpl/minesexternalstate.hpp \
    MinesImpl/minesaction.hpp \
    configparser.hpp \
    MinesImpl/minesactionexecutor.hpp \
    MinesImpl/minesinteractor.hpp \
    MinesImpl/minescustomizer.hpp \
    MinesImpl/minesfactory.hpp \
    app_headers/app_recognizer_helper.hpp \
    MinesImpl/minesrecognizerhelper.hpp \
    gui/configdialog.hpp

SOURCES += \
    solver.cpp \
    main.cpp \
    sys/stupidemulator.cpp \
    TriggerImpl/triggeractioneexecutor.cpp \
    TriggerImpl/triggerfactory.cpp \
    sys/clicker.cpp \
    sys/cclicker.c \
    renderarea.cpp \
    TriggerImpl/triggerrecognizer.cpp \
    sys/x_clickemulator.cpp \
    TriggerImpl/triggerinternalstate.cpp \
    TriggerImpl/triggerexternalstate.cpp \
    TriggerImpl/triggeraction.cpp \
    TriggerImpl/triggerinteractor.cpp \
    MinesImpl/minesrecognizer.cpp \
    MinesImpl/clickcoordreciever.cpp \
    MinesImpl/minesinternalstate.cpp \
    MinesImpl/minesexternalstate.cpp \
    MinesImpl/minesaction.cpp \
    configparser.cpp \
    MinesImpl/minesactionexecutor.cpp \
    MinesImpl/minesinteractor.cpp \
    MinesImpl/minescustomizer.cpp \
    MinesImpl/minesfactory.cpp \
    MinesImpl/minesrecognizerhelper.cpp \
    gui/configdialog.cpp

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_LIBS += -lxdo -lX11
QT += xml
