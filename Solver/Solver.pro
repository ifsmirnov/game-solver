HEADERS += \
    solver.hpp \
    app_headers/app_action.hpp \
    app_headers/app_externalstate.hpp \
    app_headers/app_interactor.hpp \
    app_headers/app_state.hpp \
    app_headers/app_actionexecutor.hpp \
    sys/emulator.hpp \
    app_headers/app_factory.hpp \
    app_headers/app_recognizer.hpp \
    sys/clicker.hpp \
    sys/cclicker.h \
    sys/x_clickemulator.h

SOURCES += \
    solver.cpp \
    main.cpp \
    sys/clicker.cpp \
    sys/cclicker.c \
    sys/x_clickemulator.cpp

QMAKE_CXXFLAGS += -std=c++0x
