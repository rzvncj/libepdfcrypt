AM_CPPFLAGS = $(GMIME_CFLAGS)
AM_LDFLAGS = -no-install

noinst_PROGRAMS = buildpdf unpack

buildpdf_SOURCES = buildpdf.cpp
unpack_SOURCES = unpack.cpp

LDADD = ../lib/libepdfcrypt.la
