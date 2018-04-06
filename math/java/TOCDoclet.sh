#!/bin/sh

javadoc -doclet com.ibm.malup.doclet.config.TOCDoclet -docletpath "M:\JavaTOC\bin\TOCNavDoclet.jar" -sourcepath com.wizzer.mle.math/src -d com.wizzer.mle.math.doc -overview com.wizzer.mle.math/src/overview-summary.html -version "1.0.0.0" -provider "Wizzer Works" com.wizzer.mle.math -pluginid www.wizzer.mle.math.doc -plugintitle "Magic Lantern Math Library"
