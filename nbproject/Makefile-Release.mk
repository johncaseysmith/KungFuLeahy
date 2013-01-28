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
CND_PLATFORM=Cygwin-Windows
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/663814019/tiles.o \
	${OBJECTDIR}/_ext/663814019/game.o \
	${OBJECTDIR}/_ext/663814019/myLib.o \
	${OBJECTDIR}/_ext/663814019/sound.o \
	${OBJECTDIR}/_ext/663814019/freddie.o \
	${OBJECTDIR}/_ext/663814019/exit.o \
	${OBJECTDIR}/_ext/663814019/photon.o \
	${OBJECTDIR}/_ext/663814019/instructions.o \
	${OBJECTDIR}/_ext/663814019/win.o \
	${OBJECTDIR}/_ext/663814019/gba_wrapper.o \
	${OBJECTDIR}/_ext/663814019/start.o \
	${OBJECTDIR}/_ext/663814019/main.o \
	${OBJECTDIR}/_ext/663814019/level1.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk cs1372.exe

cs1372.exe: ${OBJECTFILES}
	${LINK.c} -o cs1372 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/663814019/tiles.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/tiles.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/tiles.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/tiles.c

${OBJECTDIR}/_ext/663814019/game.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/game.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/game.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/game.c

${OBJECTDIR}/_ext/663814019/myLib.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/myLib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/myLib.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/myLib.c

${OBJECTDIR}/_ext/663814019/sound.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/sound.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/sound.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/sound.c

${OBJECTDIR}/_ext/663814019/freddie.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/freddie.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/freddie.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/freddie.c

${OBJECTDIR}/_ext/663814019/exit.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/exit.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/exit.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/exit.c

${OBJECTDIR}/_ext/663814019/photon.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/photon.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/photon.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/photon.c

${OBJECTDIR}/_ext/663814019/instructions.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/instructions.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/instructions.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/instructions.c

${OBJECTDIR}/_ext/663814019/win.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/win.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/win.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/win.c

${OBJECTDIR}/_ext/663814019/gba_wrapper.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/gba_wrapper.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/gba_wrapper.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/gba_wrapper.c

${OBJECTDIR}/_ext/663814019/start.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/start.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/start.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/start.c

${OBJECTDIR}/_ext/663814019/main.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/main.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/main.c

${OBJECTDIR}/_ext/663814019/level1.o: /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/level1.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/663814019
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/663814019/level1.o /cygdrive/C/Users/Casey/Documents/NetBeansProjects/JohnSmith_FinalProject/level1.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} cs1372.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
