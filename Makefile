TARGET = rotate
OBJS = main.o \
Giresun/precision.o  Giresun/Vector2D.o   Giresun/particle.o \
Giresun/pfgen.o \
graphics/graphics.o graphics/framebuffer.o graphics/sprites.o \



CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -g
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lc -g -lpspgu -lpng -lz -lm -lpspgum -lstdc++ -lm -lpsppower
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Football

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
