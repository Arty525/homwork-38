cmake_minimum_required (VERSION 3.8)

project ("button")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC_EXECUTABLE ON)

set(SOURCES button.cpp)

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.12.12\\msvc2017_64\\lib\\cmake")

find_package(Qt5 COMPONENTS
		Core
		Gui
		Widgets
		Multimedia
		MultimediaWidgets
		REQUIRED
		)

QT5_ADD_RESOURCES(SOURCES res.qrc)
add_executable(button "button.cpp" 
			qrc_res.cpp)

target_link_libraries(button
		Qt5::Widgets
		Qt5::Gui
		Qt5::Core
		Qt5::Multimedia
		Qt5::MultimediaWidgets
		)


foreach (QT_LIB Qt5Widgets Qt5Gui Qt5Core libGLESv2 Qt5Multimedia Qt5MultimediaWidgets Qt5Network)
	add_custom_command(TARGET button POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			"D:\\Qt\\5.12.12\\msvc2017_64\\bin\\${QT_LIB}d.dll"
			"$<TARGET_FILE_DIR:button>")
endforeach (QT_LIB)