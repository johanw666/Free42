###############################################################################
# Free42 -- an HP-42S calculator simulator
# Copyright (C) 2004-2026  Thomas Okken
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2,
# as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see http://www.gnu.org/licenses/.
###############################################################################

PKG_CONFIG ?= pkg-config
CXX_FOR_BUILD ?= $(CXX)

CFLAGS += -MMD \
	 -Wall \
	 -Wno-parentheses \
	 -Wno-sign-compare \
	 -Wno-format-truncation \
	 -Wno-unknown-warning-option \
	 -Wno-unknown-pragmas \
	 -g \
	 $(shell $(PKG_CONFIG) --cflags gtk+-3.0) \
	 -DGDK_DISABLE_DEPRECATION_WARNINGS -DGTK_DISABLE_SINGLE_INCLUDES -DGSEAL_ENABLE \
	 -DVERSION="\"$(shell cat VERSION)\"" \
	 -DVERSION_PLATFORM="\"$(shell uname -s)\"" \
	 -DHAVE_SINCOS=1

CXXFLAGS = $(CFLAGS) \
	 -fno-exceptions \
	 -fno-rtti

LIBS = $(shell $(PKG_CONFIG) --libs gtk+-3.0)

ifdef AUDIO_ALSA
LIBS += -lpthread -ldl
endif

ifneq "$(findstring 6162,$(shell echo ab | od -x))" ""
CFLAGS += -DF42_BIG_ENDIAN -DBID_BIG_ENDIAN
endif

SRCS = shell_main.cc shell_skin.cc shell_state.cc skins.cc keymap.cc \
	shell_loadimage.cc shell_spool.cc core_main.cc core_commands1.cc \
	core_commands2.cc core_commands3.cc core_commands4.cc \
	core_commands5.cc core_commands6.cc core_commands7.cc core_display.cc \
	core_globals.cc core_helpers.cc core_keydown.cc core_linalg1.cc \
	core_linalg2.cc core_math1.cc core_math2.cc core_phloat.cc \
	core_sto_rcl.cc core_tables.cc core_variables.cc
CORE_OBJS = shell_spool.o core_main.o core_commands1.o core_commands2.o \
	core_commands3.o core_commands4.o core_commands5.o \
	core_commands6.o core_commands7.o core_display.o core_globals.o \
	core_helpers.o core_keydown.o core_linalg1.o core_linalg2.o \
	core_math1.o core_math2.o core_phloat.o core_sto_rcl.o \
	core_tables.o core_variables.o
OBJS = shell_main.o shell_skin.o shell_state.o skins.o keymap.o \
	shell_loadimage.o \
	$(CORE_OBJS)

ifndef FP_INTEL
ifndef FP_DECNUM
ifndef FP_BINARY_INTEL
ifndef FP_BINARY
ifdef BCD_MATH
FP_INTEL = 1
else
FP_BINARY_INTEL = 1
endif
endif
endif
endif
endif

ifdef FP_INTEL
CXXFLAGS += -DFP_INTEL
INTEL = 1
EXE = free42dec
else
ifdef FP_BINARY_INTEL
CXXFLAGS += -DFP_BINARY_INTEL
INTEL = 1
EXE = free42bin
else
ifdef FP_DECNUM
CXXFLAGS += -DFP_DECNUM
SRCS += core_decimal.cc
OBJS += core_decimal.o
DECNUM_SRCS = decQuad.c decimal128.c decNumber.c decContext.c decimal64.c
OBJS += decQuad.o decimal128.o decNumber.o decContext.o decimal64.o
EXE = free42dec-decnum
else
ifdef FP_BINARY
CXXFLAGS += -DFP_BINARY
EXE = free42bin-pure
endif
endif
endif
endif

ifdef INTEL
OTHER_DEPS = gcc111libbid.a
LIBS += gcc111libbid.a
CFLAGS += -DDECIMAL_CALL_BY_REFERENCE=1 \
	  -DDECIMAL_GLOBAL_ROUNDING=1 \
	  -DDECIMAL_GLOBAL_ROUNDING_ACCESS_FUNCTIONS=1 \
	  -DDECIMAL_GLOBAL_EXCEPTION_FLAGS=1 \
	  -DDECIMAL_GLOBAL_EXCEPTION_FLAGS_ACCESS_FUNCTIONS=1
CXXFLAGS += -D_WCHAR_T_DEFINED=1
ifeq "$(shell uname -m)" "arm64"
CFLAGS += -fsigned-char -DBID_SIZE_LONG=8
else ifeq "$(shell uname -m)" "aarch64"
CFLAGS += -fsigned-char -DBID_SIZE_LONG=8
else ifeq "$(shell uname -m | sed 's/^\(...\).*$$/\1/')" "arm"
CFLAGS += -fsigned-char -DBID_SIZE_LONG=4
endif
endif

ifdef FP_INTEL
ifdef FREE42_FPTEST
CFLAGS += -DFREE42_FPTEST
SRCS += readtest.c readtest_lines.cc
OBJS += readtest.o readtest_lines.o
endif
endif

ifdef AUDIO_ALSA
# Note: the name of the libasound shared library that is usually compiled into
# the executable is defined in the corresponding *.la file, in the 'dlname'
# property. I suppose it would be better to grab it from there at build time,
# rather than hard-coding it into the Makefile like this, but as long as the
# build environment doesn't change (currently Ubuntu 18.04), this is fine.
CXXFLAGS += -DAUDIO_ALSA -DALSALIB="\"libasound.so.2\""
SRCS += audio_alsa.cc
OBJS += audio_alsa.o
endif

$(EXE): $(OBJS) icons.o $(OTHER_DEPS)
	$(CXX) -o $(EXE) $(LDFLAGS) $(OBJS) icons.o $(LIBS)

txt2raw: symlinks txt2raw.o $(CORE_OBJS) $(OTHER_DEPS)
	$(CXX) -o txt2raw $(LDFLAGS) txt2raw.o $(CORE_OBJS) $(LIBS)

raw2txt: symlinks raw2txt.o $(CORE_OBJS) $(OTHER_DEPS)
	$(CXX) -o raw2txt $(LDFLAGS) raw2txt.o $(CORE_OBJS) $(LIBS)

rawconv: raw2txt txt2raw
	strip raw2txt
	strip txt2raw
	tar cvfz rawconv-linux.tgz raw2txt txt2raw
	rm raw2txt txt2raw

$(SRCS) skin2cc.cc keymap2cc.cc skin2cc.conf keymap.txt: symlinks $(DECNUM_SRCS)

$(DECNUM_SRCS):
	tar xvfz ../decimal/decNumber.tgz

.cc.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

icons.o: icons.gresource.xml
	glib-compile-resources --generate-source $<
	$(CC) $(CFLAGS) -c -o $@ icons.c
	rm icons.c

readtest.o: readtest.c
	$(CC) $(CFLAGS) -I IntelRDFPMathLib20U1/TESTS -D__intptr_t_defined -DLINUX -c -o $@ $<

skin2cc: skin2cc.cc
	$(CXX_FOR_BUILD) -o skin2cc skin2cc.cc

skins.cc: skin2cc skin2cc.conf
	./skin2cc

keymap2cc: keymap2cc.cc
	$(CXX_FOR_BUILD) -o keymap2cc keymap2cc.cc

keymap.cc: keymap2cc keymap.txt
	./keymap2cc

gcc111libbid.a:
	sh ./build-intel-lib.sh
	ln -s IntelRDFPMathLib20U1/TESTS/readtest.c

symlinks:
	for fn in `cd ../common; /bin/ls`; do ln -s ../common/$$fn; done
	touch symlinks

clean: FORCE
	rm -f `find . -type l ! -name readtest.c` \
		dec* \
		skin2cc skin2cc.exe skins.cc \
		keymap2cc keymap2cc.exe keymap.cc \
		*.o *.d *.i *.ii *.s symlinks core.* \
		raw2txt txt2raw rawconv-linux.tgz

cleaner: FORCE
	rm -f `find . -type l` \
		free42bin* free42dec* dec* \
		skin2cc skin2cc.exe skins.cc \
		keymap2cc keymap2cc.exe keymap.cc \
		readtest_lines.cc \
		gcc111libbid.a \
		*.o *.d *.i *.ii *.s symlinks core.* \
		raw2txt txt2raw rawconv-linux.tgz
	rm -rf IntelRDFPMathLib20U1

FORCE:

-include $(OBJS:.o=.d)
