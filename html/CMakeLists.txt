cmake_minimum_required (VERSION 3.8)

project ("html")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC_EXECUTABLE ON)

set(SOURCES html.cpp)

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.12.12\\msvc2017_64\\lib\\cmake")

find_package(Qt5 COMPONENTS
		Core
		Gui
		Widgets
		WebEngineWidgets
		REQUIRED
		)

add_executable(html "html.cpp") 

target_link_libraries(html
		Qt5::Widgets
		Qt5::Gui
		Qt5::Core
		Qt5::WebEngineCore
		Qt5::WebEngineWidgets
		)


foreach (QT_LIB Qt5Widgets Qt5Gui Qt5Core libGLESv2 Qt5WebEngineCore Qt5WebEngineWidgets Qt5Quick Qt5PrintSupport Qt5Network Qt5QuickWidgets Qt5WebChannel Qt5Positioning Qt5Qml)
	add_custom_command(TARGET html POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			"D:\\Qt\\5.12.12\\msvc2017_64\\bin\\${QT_LIB}d.dll"
			"$<TARGET_FILE_DIR:html>")
endforeach (QT_LIB)