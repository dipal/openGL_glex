
TARGET = glex

HEADERS +=  glex.h \
    size.h \
    point.h \
    project.h \
    shape.h \
    solar.h \
    spacecraft.h \
    angle.h \
    position.h

SOURCES +=  main.cpp\
            glex.cpp \
    size.cpp \
    project.cpp \
    shape.cpp \
    solar.cpp \
    spacecraft.cpp \
    angle.cpp \
    position.cpp

LIBS    +=  -L/usr/lib -lglut \
            -L/usr/lib -lGL \
            -L/usr/lib -lGLU \
            -L/usr/lib -lGLEW
