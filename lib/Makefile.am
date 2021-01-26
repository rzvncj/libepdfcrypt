
lib_LTLIBRARIES = libepdfcrypt.la

libepdfcrypt_la_SOURCES = epdf.cpp mime_stream.cpp memory_mime_stream.cpp \
	file_mime_stream.cpp init.cpp safe_epdf_object.cpp mime_unpacker.cpp \
	mime_message.cpp mime_parser.cpp filtered_mime_stream.cpp \
	mime_stream_filter.cpp base64_mime_stream_filter.cpp \
	charset_detector.cpp

noinst_HEADERS = init.hpp charset_detector.hpp

libepdfcrypt_la_CPPFLAGS = $(GMIME_CFLAGS) $(ICU_CFLAGS) $(BOOST_CPPFLAGS)
libepdfcrypt_la_LDFLAGS = $(GMIME_LIBS) $(ICU_LIBS) $(BOOST_LDFLAGS) $(BOOST_LOCALE_LIB)
libepdfcrypt_la_LIBADD =

