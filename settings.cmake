# Путь к заголовочным файлам
message(Settings " CMAKE_SOURCE_DIR")

set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

# Путь к искодным текстам программ
set(SOURCE_PATH ${CMAKE_SOURCE_DIR}/source)

# Путь к собранным исполняемым модулям
set(BIN_PATH ${CMAKE_SOURCE_DIR}/bin)

# Путь к собранным статическим библиотекам
set(LIB_PATH ${CMAKE_SOURCE_DIR}/libs)

set(RESOURCE_PATH ${CMAKE_SOURCE_DIR}/resource)
# Путь к библиотеке boost
set(BOOST_PATH D:/boost_1_82_0)

# Путь к библиотеке Qt
#set(QT_PATH "C:/Qt/Qt5.14.2/5.14.2/msvc2017_64")
set(QT_PATH "D:\\QT\\5.14.2\\msvc2017_64")
set(QT_RES "D:\\Projects\\LIDPacker\\resource\\RIm.qrc")
set(SCIENCE_PATH ${CMAKE_SOURCE_DIR}/libs/science)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})