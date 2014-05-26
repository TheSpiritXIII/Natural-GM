#----------------------------------------------
#   (c) 2014 Daniel Hrabovcak
#----------------------------------------------
#   Qt specific options.
#----------------------------------------------
QT			+= core gui widgets
CONFIG		+= c++11
DEFINES		+= NGM_PORTABLE
#----------------------------------------------
#   Configuration dependent settings.
#----------------------------------------------
CONFIG(release, debug|release):TARGET = "Natural GM"
CONFIG(debug, debug|release):TARGET = "Natural GM (Debug Mode)"
#----------------------------------------------
#   Included Paths
#----------------------------------------------
INCLUDEPATH += \
	API \
	Context \
	Manager \
	Widget
#----------------------------------------------
#   Source Files.
#----------------------------------------------
SOURCES += \
	Main.cpp \
    API/Editor.cpp \
    API/Factory.cpp \
    Widget/PluginDialog.cpp \
    API/SerialData.cpp \
    API/Serializer.cpp \
    Widget/SDIEditorWindow.cpp \
    API/EditorTools.cpp \
    API/Loader.cpp
#----------------------------------------------
#   Header Files.
#----------------------------------------------
HEADERS += \
	API/Editor.hpp \
    API/Factory.hpp \
    API/Plugin.hpp \
    API/SerialData.hpp \
    API/Serializer.hpp \
	Widget/EditorDialog.hpp \
	Widget/SDIEditorWindow.hpp \
	Widget/EditorWindow.hpp \
    Widget/PluginDialog.hpp \
    Manager/GlobalManager.hpp \
    API/EditorTools.hpp \
    API/Loader.hpp \
    API/Variant.hpp
