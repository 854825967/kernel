#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/_ext/1809219144/CXmlConfig.o \
	${OBJECTDIR}/_ext/768003749/snippets.o \
	${OBJECTDIR}/XXAL_login.o \
	${OBJECTDIR}/_ext/1809219144/CIniConfig.o \
	${OBJECTDIR}/_ext/1867965399/CIniConfig.o \
	${OBJECTDIR}/_ext/974707953/tinyxmlerror.o \
	${OBJECTDIR}/_ext/974707953/tinystr.o \
	${OBJECTDIR}/_ext/1867965399/Archive.o \
	${OBJECTDIR}/_ext/931974516/ConvertUTF.o \
	${OBJECTDIR}/_ext/974707953/tinyxml.o \
	${OBJECTDIR}/_ext/1867965399/Buff.o \
	${OBJECTDIR}/_ext/1867965399/CXmlConfig.o \
	${OBJECTDIR}/_ext/1867965399/Stream.o \
	${OBJECTDIR}/_ext/931974516/snippets.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/../../../Modules/XXAL_login.dll

${CND_DISTDIR}/../../../Modules/XXAL_login.dll: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/../../../Modules
	${LINK.cc} -shared -o ${CND_DISTDIR}/../../../Modules/XXAL_login.dll -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/_ext/1867965399/VarList.o: ../../Public/VarList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1867965399
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1867965399/VarList.o ../../Public/VarList.cpp

${OBJECTDIR}/_ext/974707953/tinyxmlparser.o: ../../Public/TinyXml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/974707953
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/974707953/tinyxmlparser.o ../../Public/TinyXml/tinyxmlparser.cpp

${OBJECTDIR}/XXAL_login.o: XXAL_login.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/XXAL_login.o XXAL_login.cpp

${OBJECTDIR}/_ext/1809219144/CIniConfig.o: ../Public/CIniConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1809219144
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1809219144/CIniConfig.o ../Public/CIniConfig.cpp

${OBJECTDIR}/_ext/1867965399/CIniConfig.o: ../../Public/CIniConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1867965399
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1867965399/CIniConfig.o ../../Public/CIniConfig.cpp

${OBJECTDIR}/_ext/974707953/tinyxmlerror.o: ../../Public/TinyXml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/974707953
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/974707953/tinyxmlerror.o ../../Public/TinyXml/tinyxmlerror.cpp

${OBJECTDIR}/_ext/974707953/tinystr.o: ../../Public/TinyXml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/974707953
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/974707953/tinystr.o ../../Public/TinyXml/tinystr.cpp

${OBJECTDIR}/_ext/1867965399/Archive.o: ../../Public/Archive.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1867965399
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1867965399/Archive.o ../../Public/Archive.cpp

${OBJECTDIR}/_ext/931974516/ConvertUTF.o: ../../Public/simpleini/ConvertUTF.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/931974516
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/931974516/ConvertUTF.o ../../Public/simpleini/ConvertUTF.c

${OBJECTDIR}/_ext/974707953/tinyxml.o: ../../Public/TinyXml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/974707953
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/974707953/tinyxml.o ../../Public/TinyXml/tinyxml.cpp

${OBJECTDIR}/_ext/1867965399/Buff.o: ../../Public/Buff.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1867965399
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1867965399/Buff.o ../../Public/Buff.cpp

${OBJECTDIR}/_ext/1867965399/CXmlConfig.o: ../../Public/CXmlConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1867965399
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1867965399/CXmlConfig.o ../../Public/CXmlConfig.cpp

${OBJECTDIR}/_ext/1867965399/Stream.o: ../../Public/Stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1867965399
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1867965399/Stream.o ../../Public/Stream.cpp

${OBJECTDIR}/_ext/931974516/snippets.o: ../../Public/simpleini/snippets.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/931974516
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/931974516/snippets.o ../../Public/simpleini/snippets.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/../../../Modules/XXAL_login.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
