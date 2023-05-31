cmake_minimum_required (VERSION 3.8)

project ("blur")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC_EXECUTABLE ON)

set(SOURCES blur.cpp)

set(CMAKE_PREFIX_PATH "D:\\RTY\\qt2\\5.12.12\\msvc2017_64\\lib\\cmake")

find_package(Qt5 COMPONENTS
		Core
		Gui
		Widgets
		REQUIRED
		)

QT5_ADD_RESOURCES(SOURCES img.qrc)
add_executable(blur "blur.cpp" 
			qrc_img.cpp)

target_link_libraries(blur
		Qt5::Widgets
		Qt5::Gui
		Qt5::Core
		)


foreach (QT_LIB Qt5Widgets Qt5Gui Qt5Core libGLESv2 )
	add_custom_command(TARGET blur POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			"D:\\RTY\\qt2\\5.12.12\\msvc2017_64\\bin\\${QT_LIB}d.dll"
			"$<TARGET_FILE_DIR:blur>")
endforeach (QT_LIB)