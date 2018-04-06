# -*- Makefile -*-
#
#  Copyright (C) 2000-2007  Wizzer Works
#
#  Wizzer Works makes available all content in this file ("Content").
#  Unless otherwise indicated below, the Content is provided to you
#  under the terms and conditions of the Common Public License Version 1.0
#  ("CPL"). A copy of the CPL is available at
#
#      http://opensource.org/licenses/cpl1.0.php
#
#  For purposes of the CPL, "Program" will mean the Content.
#
#  For information concerning this Makefile, contact Mark S. Millard,
#  of Wizzer Works at msm@wizzerworks.com.
#
#*************************************************************************
#
# Makefile for installing header files.
#
# $Id$
#
###########################################################################

ISM_DEPTH = ..
include $(ISM_DEPTH)/ismdefs

VPATH = $(ISM_DEPTH)/../common/include/math

HEADERS = \
	3dmath.h \
	angle.h \
	anglebr.h \
	asine.h \
	atan.h \
	mlmath.h \
	recip.h \
	rotation.h \
	scalar.h \
	sine.h \
	sqrt.h \
	transfrm.h \
	trig.h \
	vector.h \
	$(NULL)

SOURCE = \
	asine.cxx \
	atan.cxx \
	fixed.cxx \
	recip.cxx \
	rotation.cxx \
	scalar.cxx \
	sine.cxx \
	sqrt.cxx \
	transfrm.cxx \
	vector.cxx \
	$(NULL)

DOC1 = \
	MleDoxyfile \
	wzFooter.html \
	wzHeader.html \
	$(NULL)

DOC2 = \
	pkmn_pgbg.gif \
	WwLogo.gif \
	$(NULL)

install: $(HEADERS)
	$(INSTALL) -d $(MLE_ROOT)/include/math
	$(INSTALL) $^ $(MLE_ROOT)/include/math

export: $(_FORCE)

include $(ISMRULES)

collect:
	$(IBCOLLECT) -baseDir $(ISM_DEPTH)/.. \
                     -log ../build/collect.raw \
                     -srcDir $(ISM_DEPTH)/../common/include/math \
                     -destDir "include/math" \
                     -tags "INCLUDE" \
                     $(HEADERS)
	$(IBCOLLECT) -baseDir $(ISM_DEPTH)/.. \
                     -log ../build/collect.raw \
                     -srcDir $(ISM_DEPTH)/../common/include/math \
                     -destDir "Core/math/linux/include/math" \
                     -tags "SOURCE" \
                     $(HEADERS)
	$(IBCOLLECT) -baseDir $(ISM_DEPTH)/.. \
                     -log ../build/collect.raw \
                     -srcDir $(ISM_DEPTH)/../common/src \
                     -destDir "Core/math/common/src" \
                     -tags "SOURCE" \
                     $(SOURCE)
	$(IBCOLLECT) -baseDir $(ISM_DEPTH)/.. \
                     -log ../build/collect.raw \
                     -srcDir $(ISM_DEPTH)/../common/doc \
                     -destDir "Core/math/common/doc" \
                     -tags "DOC" \
                     $(DOC1)
	$(IBCOLLECT) -baseDir $(ISM_DEPTH)/.. \
                     -log ../build/collect.raw \
                     -srcDir $(ISM_DEPTH)/../common/doc/images \
                     -destDir "Core/math/common/doc/images" \
                     -tags "DOC" \
                     $(DOC2)
