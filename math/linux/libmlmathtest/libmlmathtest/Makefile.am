#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libmlmathtest.la

#######################################
# Build information for each library

# Sources for libmlmathtest
libmlmathtest_la_SOURCES = libmlmathtest.cxx \
	testMlVector2.cxx testMlVector3.cxx testMlVector4.cxx \
	testMlTransform.cxx

# Linker options libTestProgram
libmlmathtest_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libmlmathtest_la_CPPFLAGS = \
	-DML_MATH_DEBUG=0 \
	-DML_FIXED_POINT=0 \
	-DMLMATH_EXPORTS \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/../../common/include \
	-I$(MLE_HOME)/Core/util/common/include \
	-I$(MLE_HOME)/Core/util/linux/include \
	-I$(GTEST_DIR)/include
