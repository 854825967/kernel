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
include Kernel-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/HeartBeatManage/HeartBeatManage.o \
	${OBJECTDIR}/_ext/1885453440/tinyxmlparser.o \
	${OBJECTDIR}/_ext/1809219144/Buff.o \
	${OBJECTDIR}/LogicManage/LogicManage.o \
	${OBJECTDIR}/NetSystem/NetSystem.o \
	${OBJECTDIR}/Kernel.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/HeartBeatManage/HeartBeat.o \
	${OBJECTDIR}/ObjectManage/ObjectManage.o \
	${OBJECTDIR}/_ext/1809219144/CXmlConfig.o \
	${OBJECTDIR}/_ext/768003749/snippets.o \
	${OBJECTDIR}/_ext/1809219144/CIniConfig.o \
	${OBJECTDIR}/_ext/768003749/ConvertUTF.o \
	${OBJECTDIR}/_ext/1885453440/tinyxmlerror.o \
	${OBJECTDIR}/_ext/1809219144/Archive.o \
	${OBJECTDIR}/CallBackSystem/CallBackSystem.o \
	${OBJECTDIR}/_ext/1809219144/Stream.o \
	${OBJECTDIR}/_ext/1809219144/VarList.o \
	${OBJECTDIR}/LogSystem/LogSystem.o \
	${OBJECTDIR}/_ext/1885453440/tinyxml.o \
	${OBJECTDIR}/Config/ConfigManage.o \
	${OBJECTDIR}/Console/Console.o \
	${OBJECTDIR}/NetSystem/LinkManage.o \
	${OBJECTDIR}/_ext/1885453440/tinystr.o


# C Compiler Flags
CFLAGS=-ldl -lpthread

# CC Compiler Flags
CCFLAGS=-ldl -lpthread
CXXFLAGS=-ldl -lpthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-ldl -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/../../Kernel_R

${CND_DISTDIR}/../../Kernel_R: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/../..
	${LINK.cc} -lpthread -ldl -o ${CND_DISTDIR}/../../Kernel_R ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/HeartBeatManage/HeartBeatManage.o: HeartBeatManage/HeartBeatManage.cpp 
	${MKDIR} -p ${OBJECTDIR}/HeartBeatManage
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HeartBeatManage/HeartBeatManage.o HeartBeatManage/HeartBeatManage.cpp

${OBJECTDIR}/_ext/1885453440/tinyxmlparser.o: ../Public/TinyXml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1885453440
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1885453440/tinyxmlparser.o ../Public/TinyXml/tinyxmlparser.cpp

${OBJECTDIR}/_ext/1809219144/Buff.o: ../Public/Buff.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1809219144
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1809219144/Buff.o ../Public/Buff.cpp

${OBJECTDIR}/LogicManage/LogicManage.o: LogicManage/LogicManage.cpp 
	${MKDIR} -p ${OBJECTDIR}/LogicManage
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/LogicManage/LogicManage.o LogicManage/LogicManage.cpp

${OBJECTDIR}/NetSystem/NetSystem.o: NetSystem/NetSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/NetSystem
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/NetSystem/NetSystem.o NetSystem/NetSystem.cpp

${OBJECTDIR}/Kernel.o: Kernel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Kernel.o Kernel.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/HeartBeatManage/HeartBeat.o: HeartBeatManage/HeartBeat.cpp 
	${MKDIR} -p ${OBJECTDIR}/HeartBeatManage
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HeartBeatManage/HeartBeat.o HeartBeatManage/HeartBeat.cpp

${OBJECTDIR}/ObjectManage/ObjectManage.o: ObjectManage/ObjectManage.cpp 
	${MKDIR} -p ${OBJECTDIR}/ObjectManage
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ObjectManage/ObjectManage.o ObjectManage/ObjectManage.cpp

${OBJECTDIR}/_ext/1809219144/CXmlConfig.o: ../Public/CXmlConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1809219144
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1809219144/CXmlConfig.o ../Public/CXmlConfig.cpp

${OBJECTDIR}/_ext/768003749/snippets.o: ../Public/simpleini/snippets.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/768003749
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/768003749/snippets.o ../Public/simpleini/snippets.cpp

${OBJECTDIR}/_ext/1809219144/CIniConfig.o: ../Public/CIniConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1809219144
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1809219144/CIniConfig.o ../Public/CIniConfig.cpp

${OBJECTDIR}/_ext/768003749/ConvertUTF.o: ../Public/simpleini/ConvertUTF.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/768003749
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/768003749/ConvertUTF.o ../Public/simpleini/ConvertUTF.c

${OBJECTDIR}/_ext/1885453440/tinyxmlerror.o: ../Public/TinyXml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1885453440
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1885453440/tinyxmlerror.o ../Public/TinyXml/tinyxmlerror.cpp

${OBJECTDIR}/_ext/1809219144/Archive.o: ../Public/Archive.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1809219144
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1809219144/Archive.o ../Public/Archive.cpp

${OBJECTDIR}/CallBackSystem/CallBackSystem.o: CallBackSystem/CallBackSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/CallBackSystem
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CallBackSystem/CallBackSystem.o CallBackSystem/CallBackSystem.cpp

${OBJECTDIR}/_ext/1809219144/Stream.o: ../Public/Stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1809219144
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1809219144/Stream.o ../Public/Stream.cpp

${OBJECTDIR}/_ext/1809219144/VarList.o: ../Public/VarList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1809219144
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1809219144/VarList.o ../Public/VarList.cpp

${OBJECTDIR}/LogSystem/LogSystem.o: LogSystem/LogSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/LogSystem
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/LogSystem/LogSystem.o LogSystem/LogSystem.cpp

${OBJECTDIR}/_ext/1885453440/tinyxml.o: ../Public/TinyXml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1885453440
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1885453440/tinyxml.o ../Public/TinyXml/tinyxml.cpp

${OBJECTDIR}/Config/ConfigManage.o: Config/ConfigManage.cpp 
	${MKDIR} -p ${OBJECTDIR}/Config
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Config/ConfigManage.o Config/ConfigManage.cpp

${OBJECTDIR}/Console/Console.o: Console/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/Console
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Console/Console.o Console/Console.cpp

${OBJECTDIR}/NetSystem/LinkManage.o: NetSystem/LinkManage.cpp 
	${MKDIR} -p ${OBJECTDIR}/NetSystem
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/NetSystem/LinkManage.o NetSystem/LinkManage.cpp

${OBJECTDIR}/_ext/1885453440/tinystr.o: ../Public/TinyXml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1885453440
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1885453440/tinystr.o ../Public/TinyXml/tinystr.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/../../Kernel_R

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
