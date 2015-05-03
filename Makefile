#
# Created by gmakemake (Ubuntu Sep  7 2011) on Fri Nov  2 19:29:03 2012
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb
CFLAGS =	-ggdb
CLIBFLAGS =	-lm
CCLIBFLAGS =	
########## End of default flags


CPP_FILES =	Connect3Game.cpp CrossoutGame.cpp Game.cpp KaylesGame.cpp TakeawayGame.cpp connect3.cpp crossout.cpp kayles.cpp takeaway.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	Connect3Game.h CrossoutGame.h Game.h KaylesGame.h TakeawayGame.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Connect3Game.o CrossoutGame.o Game.o KaylesGame.o TakeawayGame.o 

#
# Main targets
#

all:	connect3 crossout kayles takeaway 

connect3:	connect3.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o connect3 connect3.o $(OBJFILES) $(CCLIBFLAGS)

crossout:	crossout.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o crossout crossout.o $(OBJFILES) $(CCLIBFLAGS)

kayles:	kayles.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o kayles kayles.o $(OBJFILES) $(CCLIBFLAGS)

takeaway:	takeaway.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o takeaway takeaway.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Connect3Game.o:	Connect3Game.h Game.h
CrossoutGame.o:	CrossoutGame.h Game.h
Game.o:	Game.h
KaylesGame.o:	Game.h KaylesGame.h
TakeawayGame.o:	Game.h TakeawayGame.h
connect3.o:	Connect3Game.h Game.h
crossout.o:	CrossoutGame.h Game.h
kayles.o:	Game.h KaylesGame.h
takeaway.o:	Game.h TakeawayGame.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) connect3.o crossout.o kayles.o takeaway.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf connect3 crossout kayles takeaway 
