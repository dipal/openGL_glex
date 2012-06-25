
TARGET = glex

HEADERS +=  glex.h \
    point.h \
    project.h \
    angle.h \
    imageloader.h \
    background.h \
    shapeinterface.h \
    multishape.h

SOURCES +=  main.cpp\
            glex.cpp \
    project.cpp \
    angle.cpp \
    imageloader.cpp \
    background.cpp \
    shapeinterface.cpp \
    multishape.cpp

LIBS    +=  -L/usr/lib -lglut \
            -L/usr/lib -lGL \
            -L/usr/lib -lGLU \
            -L/usr/lib -lGLEW
