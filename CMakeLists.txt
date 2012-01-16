 #
 #  Copyright (C) 2011, BMW AG 
 # 
 # AudioManagerDeamon
 #
 # @file CMakeLists.txt
 #
 # @date: 20.05.2011
 # @author: Christian Müller (christian.ei.mueller@bmw.de)
 #

cmake_minimum_required(VERSION 2.6)

execute_process(COMMAND git describe --tags WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                OUTPUT_VARIABLE DAEMONVERSION 
                OUTPUT_STRIP_TRAILING_WHITESPACE)

IF (DAEMON_ERROR)
	SET( DAEMONVERSION "homebrew-${CMAKE_SOURCE_DIR}" )
ENDIF(DAEMON_ERROR)

message(STATUS "Build Version ${DAEMONVERSION}")

execute_process(COMMAND git log --pretty=short WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG)

PROJECT(AudioManagerDeamon)

OPTION( WITH_DBUS_WRAPPER 
	"Enable Dbus Wrapper Support" ON )

OPTION( WITH_SOCKETHANDLER_LOOP 
	"Enable SocketHandler Support (cannot work with SimpleDBusLoop)" ON )

OPTION( WITH_SIMPLEDBUS_LOOP 
	"Enable SimpleDBusLoop (requires DBus_Wrapper,cannot work with SocketHandler)" OFF )

OPTION( WITH_TESTS
	"Build together with all available unitTest" ON )

OPTION( WITH_DOCUMENTATION
	"Build together with Doxygen Documentation" OFF )

OPTION( WITH_PLUGIN_COMMAND
	"Build command pluings" ON)

OPTION( WITH_PLUGIN_CONTROL
	"Build control pluing" ON)

OPTION( WITH_PLUGIN_ROUTING
	"Build routing pluings" ON)

OPTION( USE_BUILD_LIBS
	"Sets the default path to the libs that are compiled with the AudioManager together. If turned off, the default location will be the one of the install path" OFF) 

OPTION( WITH_MAIN
	"Build with daemon" ON)

OPTION( WITH_PPOLL
	"libc supports ppoll" ON)

OPTION( WITH_TELNET
	"build with Telnetserver" OFF)

#Can be changed via passing -DDBUS_SERVICE_PREFIX="XXX" to cmake
IF(NOT DEFINED DBUS_SERVICE_PREFIX)
	SET( DBUS_SERVICE_PREFIX "org.genivi.audiomanager\0" )
ENDIF(NOT DEFINED DBUS_SERVICE_PREFIX)

#Can be changed via passing -DDBUS_SERVICE_OBJECT_PATH="XXX" to cmake
IF(NOT DEFINED DBUS_SERVICE_OBJECT_PATH)
	SET( DBUS_SERVICE_OBJECT_PATH "/org/genivi/audiomanager\0" )
ENDIF(NOT DEFINED DBUS_SERVICE_OBJECT_PATH)

#Can be changed via passing -DDEFAULT_TELNETPORT="XXX" to cmake
IF(NOT DEFINED DEFAULT_TELNETPORT)
	SET( DEFAULT_TELNETPORT 6060 )
ENDIF(NOT DEFINED DEFAULT_TELNETPORT)

#Can be changed via passing -DMAX_TELNETCONNECTIONS="XXX" to cmake
IF(NOT DEFINED MAX_TELNETCONNECTIONS)
	SET( MAX_TELNETCONNECTIONS 3 )
ENDIF(NOT DEFINED MAX_TELNETCONNECTIONS)

SET(DLT_CONTEXT AudioManager)
SET(PLUGINS_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/plugins)
SET(LIB_INSTALL_SUFFIX "audioManager")

if(USE_BUILD_LIBS)
	SET(DEFAULT_PLUGIN_COMMAND_DIR "${PLUGINS_OUTPUT_PATH}/command")
	SET(DEFAULT_PLUGIN_ROUTING_DIR "${PLUGINS_OUTPUT_PATH}/routing")
	SET(CONTROLLER_PLUGIN "${PLUGINS_OUTPUT_PATH}/control/libPluginControlInterface.so")
else(USE_BUILD_LIBS)
	SET(DEFAULT_PLUGIN_COMMAND_DIR "${CMAKE_INSTALL_PREFIX}/lib/${LIB_INSTALL_SUFFIX}/command")
	SET(DEFAULT_PLUGIN_ROUTING_DIR "${CMAKE_INSTALL_PREFIX}/lib/${LIB_INSTALL_SUFFIX}/routing")
	SET(CONTROLLER_PLUGIN "${CMAKE_INSTALL_PREFIX}/lib/${LIB_INSTALL_SUFFIX}/control/libPluginControlInterface.so")
endif(USE_BUILD_LIBS)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
SET(AUDIO_INCLUDES_FOLDER ${CMAKE_SOURCE_DIR}/includes)
SET(DOC_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/doc)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(TEST_EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/test)
SET(DOXY_FILE ${CMAKE_SOURCE_DIR}/cmake/DoxyFile.in)
SET(INTROSPECTION_COMMAND_XML_FILE "${AUDIO_INCLUDES_FOLDER}/dbus/CommandInterface.xml")

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/cmake/config.cmake ${CMAKE_SOURCE_DIR}/includes/config.h )

FIND_PACKAGE(PkgConfig)
pkg_check_modules(DLT REQUIRED automotive-dlt)

IF(WITH_DOCUMENTATION)
	find_package(Doxygen)
	file(MAKE_DIRECTORY ${DOC_OUTPUT_PATH}/Interfaces)
	configure_file(${DOXY_FILE}  ${DOC_OUTPUT_PATH}/Interfaces/Doxyfile  @ONLY IMMEDIATE)
  	add_custom_target (Interfaces ALL 
  		COMMAND ${DOXYGEN_EXECUTABLE} ${DOC_OUTPUT_PATH}/Interfaces/Doxyfile WORKING_DIRECTORY ${DOC_OUTPUT_PATH}/Interfaces
  		SOURCES ${AUDIO_INCLUDES_FOLDER} ${DOC_OUTPUT_PATH}/Interfaces/Doxyfile
	)
ENDIF(WITH_DOCUMENTATION)

##global build flags set(CPACK_RPM_COMPONENT_INSTALL ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -std=c++98 -D_GNU_SOURCE")

if(WITH_PLUGIN_COMMAND)
	add_subdirectory (PluginCommandInterfaceDbus)
endif(WITH_PLUGIN_COMMAND)

if(WITH_PLUGIN_ROUTING)
	add_subdirectory (PluginRoutingInterfaceDbus)
	add_subdirectory (PluginRoutingInterfaceAsync)
endif(WITH_PLUGIN_ROUTING)

if(WITH_PLUGIN_CONTROL)
	add_subdirectory (PluginControlInterface)
endif(WITH_PLUGIN_CONTROL)

if(WITH_MAIN)
	add_subdirectory (AudioManagerDaemon)
endif(WITH_MAIN)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# Here starts package creation
SET(CPACK_SET_DESTDIR ON)
SET(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_SOURCE_DIR}/packages)
SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_NAME "AudioManager")
SET(CPACK_PACKAGE_VENDOR "GENIVI")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "AudioManager: This component manages audio in the GENIVI context")
SET(CPACK_PACKAGE_VERSION "${DAEMONVERSION}")
SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENCE)
SET(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README)
SET(CPACK_PACKAGE_CONTACT "Christian Mueller (BMW) christian.ei.mueller@bmw.de")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "genivi")
SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "*")
SET(CPACK_STRIP_FILES TRUE)
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README)
SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_IGNORE_FILES ".settings*" ".cproject" ".project" "/\\\\.metadata" "\\\\.#" "/#" ".*~" "/\\\\.git" "${CMAKE_CURRENT_BINARY_DIR}" "bin/" "packages/" "config.h") 

#evaluate the properties
if(WITH_MAIN)
get_property(ADD_DEPEND GLOBAL PROPERTY bin_prop)
list(REMOVE_DUPLICATES ADD_DEPEND)
set(ALL_DEPEND ${ADD_DEPEND})
FOREACH (dep ${ADD_DEPEND})
	SET(bin_DEPENDENCIES "${dep} ,${bin_DEPENDENCIES}")
ENDFOREACH(dep)
STRING(REGEX REPLACE ".$" "" bin_DEPENDENCIES ${bin_DEPENDENCIES})
endif(WITH_MAIN)

get_property(ADD_DEPEND GLOBAL PROPERTY sampleplugins_prop)
list(REMOVE_DUPLICATES ADD_DEPEND)
list(APPEND ALL_DEPEND ${ADD_DEPEND})
FOREACH (dep ${ADD_DEPEND})
	SET(sampleplugins_DEPENDENCIES "${dep} ,${sampleplugins_DEPENDENCIES}")
ENDFOREACH(dep)
STRING(REGEX REPLACE ".$" "" sampleplugins_DEPENDENCIES ${sampleplugins_DEPENDENCIES})

if(WITH_TESTS)
get_property(ADD_DEPEND GLOBAL PROPERTY tests_prop)
list(REMOVE_DUPLICATES ADD_DEPEND)
list(APPEND ALL_DEPEND ${ADD_DEPEND})
FOREACH (dep ${ADD_DEPEND})	
	SET(tests_DEPENDENCIES "${dep} ,${tests_DEPENDENCIES}")
ENDFOREACH(dep)
STRING(REGEX REPLACE ".$" "" tests_DEPENDENCIES ${tests_DEPENDENCIES})
endif(WITH_TESTS)

get_property(ADD_DEPEND GLOBAL PROPERTY dev_prop)
list(REMOVE_DUPLICATES ADD_DEPEND)
list(APPEND ALL_DEPEND ${ADD_DEPEND})
FOREACH (dep ${ADD_DEPEND})
	SET(dev_DEPENDENCIES "${dep} ,${dev_DEPENDENCIES}")
ENDFOREACH(dep)
STRING(REGEX REPLACE ".$" "" dev_DEPENDENCIES ${dev_DEPENDENCIES})

list(REMOVE_DUPLICATES ALL_DEPEND)
FOREACH (dep ${ALL_DEPEND})
	SET(all_DEPENDENCIES "${dep} ,${all_DEPENDENCIES}")
ENDFOREACH(dep)
STRING(REGEX REPLACE ".$" "" all_DEPENDENCIES ${all_DEPENDENCIES})
execute_process(COMMAND cp ${CMAKE_MODULE_PATH}/add_package_dependencies.sh ${CMAKE_CURRENT_BINARY_DIR})

#component based dep package generation is only supported above 2.8.5
IF (${CMAKE_VERSION} VERSION_GREATER 2.8.4)

	SET(CPACK_COMPONENTS_ALL bin sampleplugins tests dev)
	SET(CPACK_COMPONENTS_IGNORE_GROUPS 1)
	SET(CPACK_RPM_COMPONENT_INSTALL ON)
	SET(CPACK_DEB_COMPONENT_INSTALL ON)
	ADD_CUSTOM_TARGET(genivi_package 
		COMMAND make package
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/add_package_dependencies.sh ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Linux-bin.deb ${CPACK_OUTPUT_FILE_PREFIX} \"${bin_DEPENDENCIES}\"
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/add_package_dependencies.sh ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Linux-sampleplugins.deb ${CPACK_OUTPUT_FILE_PREFIX} \"${sampleplugins_DEPENDENCIES}\"
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/add_package_dependencies.sh ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Linux-tests.deb ${CPACK_OUTPUT_FILE_PREFIX} \"${tests_DEPENDENCIES}\"
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/add_package_dependencies.sh ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Linux-dev.deb ${CPACK_OUTPUT_FILE_PREFIX} \"${dev_DEPENDENCIES}\"
	) 
ELSE (${CMAKE_VERSION} VERSION_GREATER 2.8.4)
	ADD_CUSTOM_TARGET(genivi_package 
		COMMAND make package
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/add_package_dependencies.sh ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Linux.deb ${CPACK_OUTPUT_FILE_PREFIX} \"${all_DEPENDENCIES}\"
	)
ENDIF (${CMAKE_VERSION} VERSION_GREATER 2.8.4)

INCLUDE(CPack)

