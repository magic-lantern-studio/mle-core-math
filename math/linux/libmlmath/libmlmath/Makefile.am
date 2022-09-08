#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libmlmath.la

#######################################
# Build information for each library

# Sources for libmlmath
libmlmath_la_SOURCES = libmlmath.c \
	$(top_srcdir)/../../common/src/asine.cxx \
	$(top_srcdir)/../../common/src/atan.cxx \
	$(top_srcdir)/../../common/src/fixed.cxx \
	$(top_srcdir)/../../common/src/recip.cxx \
	$(top_srcdir)/../../common/src/rotation.cxx \
	$(top_srcdir)/../../common/src/scalar.cxx \
	$(top_srcdir)/../../common/src/sine.cxx \
	$(top_srcdir)/../../common/src/sqrt.cxx \
	$(top_srcdir)/../../common/src/transfrm.cxx \
	$(top_srcdir)/../../common/src/vector.cxx

# Linker options for libmlmath
libmlmath_la_LDFLAGS = -version-info 1:0:0

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libmlmath_la_CPPFLAGS = \
	-DML_MATH_DEBUG=0 \
	-DML_FIXED_POINT=0 \
	-DMLMATH_EXPORTS \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/../../common/include \
	-I$(MLE_HOME)/Core/util/common/include \
	-I$(MLE_HOME)/Core/util/linux/include \
	-std=c++11
