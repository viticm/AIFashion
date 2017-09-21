# Makefile for building Ain
# See ../doc/readme.html for installation and customization instructions.

# == CHANGE THE SETTINGS BELOW TO SUIT YOUR ENVIRONMENT =======================

# Your platform. See PLATS for possible values.
PLAT= none

CC= gcc -std=gnu99
CFLAGS= -O2 -Wall -Wextra -DAIN_COMPAT_5_2 $(SYSCFLAGS) $(MYCFLAGS)
LDFLAGS= $(SYSLDFLAGS) $(MYLDFLAGS)
LIBS= -lm $(SYSLIBS) $(MYLIBS)

AR= ar rcu
RANLIB= ranlib
RM= rm -f

SYSCFLAGS=
SYSLDFLAGS=
SYSLIBS=

MYCFLAGS=
MYLDFLAGS=
MYLIBS=
MYOBJS=

# == END OF USER SETTINGS -- NO NEED TO CHANGE ANYTHING BELOW THIS LINE =======

PLATS= aix bsd c89 freebsd generic linux macosx mingw posix solaris

AIN_A=	libain.a
CORE_O=	aaction.o aevent.o ame.o amind.o
LIB_O=	aaction.o aevent.o ame.o amind.o
BASE_O= $(CORE_O) $(LIB_O) $(MYOBJS)

AIN_T=	ain
AIN_O=	ain.o

AINC_T=	ainc
AINC_O=	ainc.o

ALL_O= $(BASE_O) $(AIN_O) $(AINC_O)
ALL_T= $(AIN_A) $(AIN_T) #$(AINC_T)
ALL_A= $(AIN_A)

# Targets start here.
default: $(PLAT)

all:	$(ALL_T)

o:	$(ALL_O)

a:	$(ALL_A)

$(AIN_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

$(AIN_T): $(AIN_O) $(AIN_A)
	$(CC) -o $@ $(LDFLAGS) $(AIN_O) $(AIN_A) $(LIBS)

$(AINC_T): $(AINC_O) $(AIN_A)
	$(CC) -o $@ $(LDFLAGS) $(AINC_O) $(AIN_A) $(LIBS)

clean:
	$(RM) $(ALL_T) $(ALL_O)

depend:
	@$(CC) $(CFLAGS) -MM l*.c

echo:
	@echo "PLAT= $(PLAT)"
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(SYSLDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

# Convenience targets for popular platforms
ALL= all

none:
	@echo "Please do 'make PLATFORM' where PLATFORM is one of these:"
	@echo "   $(PLATS)"

aix:
	$(MAKE) $(ALL) CC="xlc" CFLAGS="-O2 -DAIN_USE_POSIX -DAIN_USE_DLOPEN" SYSLIBS="-ldl" SYSLDFLAGS="-brtl -bexpall"

bsd:
	$(MAKE) $(ALL) SYSCFLAGS="-DAIN_USE_POSIX -DAIN_USE_DLOPEN" SYSLIBS="-Wl,-E"

c89:
	$(MAKE) $(ALL) SYSCFLAGS="-DAIN_USE_C89" CC="gcc -std=c89"
	@echo ''
	@echo '*** C89 does not guarantee 64-bit integers for Ain.'
	@echo ''


freebsd:
	$(MAKE) $(ALL) SYSCFLAGS="-DAIN_USE_LINUX" SYSLIBS="-Wl,-E -lreadline"

generic: $(ALL)

linux:
	$(MAKE) $(ALL) SYSCFLAGS="-DAIN_USE_LINUX" SYSLIBS="-Wl,-E -ldl -lreadline"

macosx:
	$(MAKE) $(ALL) SYSCFLAGS="-DAIN_USE_MACOSX" SYSLIBS="-lreadline" CC=cc

mingw:
	$(MAKE) "AIN_A=ain53.dll" "AIN_T=ain.exe" \
	"AR=$(CC) -shared -o" "RANLIB=strip --strip-unneeded" \
	"SYSCFLAGS=-DAIN_BUILD_AS_DLL" "SYSLIBS=" "SYSLDFLAGS=-s" ain.exe
	$(MAKE) "AINC_T=ainc.exe" ainc.exe

posix:
	$(MAKE) $(ALL) SYSCFLAGS="-DAIN_USE_POSIX"

solaris:
	$(MAKE) $(ALL) SYSCFLAGS="-DAIN_USE_POSIX -DAIN_USE_DLOPEN -D_REENTRANT" SYSLIBS="-ldl"

# list targets that do not create files (but not all makes understand .PHONY)
.PHONY: all $(PLATS) default o a clean depend echo none

# DO NOT DELETE

aaction.o: aaction.h ainconf.h
aevent.o: aevent.h ainconf.h
ame.o: ame.h ainconf.h
amind.o: amind.h ainconf.h aevent.h

# (end of Makefile)
