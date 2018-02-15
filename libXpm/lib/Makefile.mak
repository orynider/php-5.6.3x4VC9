################################################################
# MSVC Makefile
#
# Author: Jan Wielemaker
# Date:   Feb 17, 2001
################################################################

# Destinations.  Please edit
prefix=C:\Documents and Settings\jan
LIBDIR=$(prefix)\lib64
INCDIR=$(prefix)\include

# On CFLAGS, /MD means to use multi-threaded mvcrt.dll.  This must be the
# same on all parts of the system you compile!.  Check the MSVC documentation

CC=cl.exe
AR=lib.exe
CFLAGS=/MD /W3 /O2 /EHsc /DNDEBUG /DWIN32 /DFOR_MSW /nologo /c

XPMLIB=xpm.lib

OBJ=	Attrib.obj CrBufFrI.obj CrDatFrI.obj CrIFrBuf.obj CrIFrDat.obj \
	Image.obj Info.obj RdFToBuf.obj RdFToDat.obj RdFToI.obj \
	WrFFrBuf.obj WrFFrDat.obj WrFFrI.obj create.obj \
	data.obj hashtab.obj misc.obj parse.obj rgb.obj scan.obj \
	simx.obj

.c.obj:
	@$(CC) $(CFLAGS) /Fo$@ $<

$(XPMLIB):	$(OBJ)
		del $@
		$(AR) /out:$@ /nologo $(OBJ)

install:	$(XPMLIB)
		copy $(XPMLIB) "$(LIBDIR)"
		copy xpm.h "$(INCDIR)"

clean::
		del *~ *.obj

distclean:	clean
		del xpm.lib
