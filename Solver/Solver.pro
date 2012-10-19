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
    app_headers/app_state.hpp

SOURCES += \
    solver.cpp \
    main.cpp \
    sys/stupidemulator.cpp \
    TriggerImpl/triggeractioneexecutor.cpp \
    TriggerImpl/triggerfactory.cpp

QMAKE_CXXFLAGS += -std=c++0x
