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
# Makefile - make installation images.
#
#*************************************************************************

ISM_DEPTH = ..
include $(ISM_DEPTH)/ismdefs

#
# Pull in some definitions that are specific to making installation
# images
#
include $(INSTALLDEFS)

#
# Define the versions of installation images to make
#
VERSIONS = FloatDebug FloatRelease FixedDebug FixedRelease

include $(ISMRULES)

#
# Pull in some rules that are specific to making installation
# images.  This MUST go AFTER including $(ISMRULES) above.
#
include $(INSTALLRULES)

collect:
	make clobber
	cd ..; make collect
