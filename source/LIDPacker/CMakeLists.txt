cmake_minimum_required(VERSION 3.21)

# Setup project
project(LIDPacker VERSION 1.0)
add_compile_definitions("_CRT_SECURE_NO_WARNINGS")

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH ${QT_PATH}/lib/cmake)
# Set directories for headers search
find_package(Qt5 COMPONENTS Widgets        REQUIRED)
find_package(Qt5 COMPONENTS Core           REQUIRED)
find_package(Qt5 COMPONENTS Charts         REQUIRED)
find_package(Qt5 COMPONENTS Concurrent     REQUIRED)
find_package(Qt5 COMPONENTS PrintSupport   REQUIRED)

qt5_add_resources(RESOURCE_FILE ${QT_RES})

# Set directories for headers search
include_directories(${QT_PATH}/include)

include_directories(${INCLUDE_PATH})

# Making file groups#

file(GLOB_RECURSE   CHEADERSGUI     ${INCLUDE_PATH}/LIDPacker/gui/*.h*)
file(GLOB_RECURSE   CHEADERSMAKER   ${INCLUDE_PATH}/LIDPacker/maker/*.h*)
file(GLOB_RECURSE   CHEADERSSCIENCE ${INCLUDE_PATH}/science/*.h*)

file(GLOB_RECURSE   CSOURCESGUI     ${SOURCE_PATH}/LIDPacker/gui/*.c*)
file(GLOB_RECURSE   CSOURCESMAKER   ${SOURCE_PATH}/LIDPacker/maker/*.c*)

file(GLOB_RECURSE   RESOURCES     ${RESOURCE_PATH}/*.qrc)
file(GLOB_RECURSE   RESOURCESIMG  ${RESOURCE_PATH}/images/*.png)

# Make groups in project file
	
source_group(TREE  ${INCLUDE_PATH}/LIDPacker PREFIX "Header Files" FILES ${CHEADERSGUI})
source_group(TREE  ${INCLUDE_PATH}/LIDPacker PREFIX "Header Files" FILES ${CHEADERSMAKER})
source_group(TREE  ${INCLUDE_PATH} 			 PREFIX "Header Files" FILES ${CHEADERSSCIENCE})

source_group(TREE  ${SOURCE_PATH}/LIDPacker PREFIX "Source Files" FILES ${CSOURCESGUI})
source_group(TREE  ${SOURCE_PATH}/LIDPacker PREFIX "Source Files" FILES ${CSOURCESMAKER})

source_group(TREE  ${RESOURCE_PATH} PREFIX "Resource Files" FILES ${RESOURCES})
source_group(TREE  ${RESOURCE_PATH} PREFIX "Resource Files" FILES ${RESOURCESIMG})

add_executable(LIDPacker ${CHEADERSGUI} ${CHEADERSMAKER} ${CHEADERSSCIENCE} ${CSOURCESGUI} ${CSOURCESMAKER} ${RESOURCES} ${RESOURCESIMG})

add_custom_command(TARGET LIDPacker POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt5::Widgets>
                   $<TARGET_FILE:Qt5::Charts>
                   $<TARGET_FILE:Qt5::Concurrent>
                   $<TARGET_FILE:Qt5::PrintSupport>
                   $<TARGET_FILE:Qt5::Core>
                   $<TARGET_FILE:Qt5::Gui>
                   $<TARGET_FILE_DIR:LIDPacker>
)               
file(COPY ${QT_PATH}/plugins/platforms DESTINATION ${EXECUTABLE_OUTPUT_PATH})
target_link_libraries(LIDPacker PRIVATE Qt5::Widgets)
target_link_libraries(LIDPacker PRIVATE Qt5::Charts)
target_link_libraries(LIDPacker PRIVATE Qt5::Concurrent)
target_link_libraries(LIDPacker PRIVATE Qt5::PrintSupport)
target_link_libraries(LIDPacker PRIVATE Qt5::Core)
target_link_libraries(LIDPacker PRIVATE Qt5::Gui)
target_link_libraries(LIDPacker PRIVATE ${SCIENCE_PATH}/libscience.lib)
# Связывает QT5 dll файлы для проекта.
set_target_properties(LIDPacker PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${QT_PATH}/bin)
#set_target_properties(LIDPacker PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE" LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
