
TARGET = glex

HEADERS +=  glex.h \
    size.h \
    point.h \
    project.h \
    angle.h

SOURCES +=  main.cpp\
            glex.cpp \
    size.cpp \
    project.cpp \
    angle.cpp

LIBS    +=  -L/usr/lib -lglut \
            -L/usr/lib -lGL \
            -L/usr/lib -lGLU \
            -L/usr/lib -lGLEW
