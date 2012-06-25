
TARGET = glex

HEADERS +=  glex.h \
    point.h \
    project.h \
    angle.h

SOURCES +=  main.cpp\
            glex.cpp \
    project.cpp \
    angle.cpp

LIBS    +=  -L/usr/lib -lglut \
            -L/usr/lib -lGL \
            -L/usr/lib -lGLU \
            -L/usr/lib -lGLEW
