#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=exampleProgram

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=exampleProgram

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

ACLOCAL_AMFLAGS=-I ../m4

# Sources for the a.out 
exampleProgram_SOURCES = exampleProgram.cxx

# Libraries for a.out
exampleProgram_LDADD = $(top_srcdir)/libmlmathtest/libmlmathtest.la \
	$(top_srcdir)/../libmlmath/libmlmath/libmlmath.la \
	/usr/local/lib/libgtest.a

# Linker options for a.out
exampleProgram_LDFLAGS = \
	-rpath `cd $(top_srcdir);pwd`/libmlmathtest/.libs -pthread

# Compiler options for a.out
exampleProgram_CPPFLAGS = \
	-DML_MATH_DEBUG=0 \
	-DML_FIXED_POINT=0 \
	-DMLMATH_EXPORTS \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/../../common/include \
	-I$(MLE_ROOT)/include \
	-I/usr/local/include \
	-std=c++17

