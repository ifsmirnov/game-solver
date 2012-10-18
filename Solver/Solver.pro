HEADERS += \
    solver.hpp \
    app_headers/app_action.hpp \
    app_headers/app_externalstate.hpp \
    app_headers/app_interactor.hpp \
    app_headers/app_state.hpp \
    app_headers/app_actionexecutor.hpp \
    sys/emulator.hpp \
    app_headers/app_factory.hpp \
    app_headers/app_recognizer.hpp

SOURCES += \
    solver.cpp \
    main.cpp

QMAKE_CXXFLAGS += -std=c++0x
