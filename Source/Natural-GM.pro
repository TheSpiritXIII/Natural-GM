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
	Core \
	Manager \
	Widget
#----------------------------------------------
#   Source Files.
#----------------------------------------------
SOURCES += \
	Main.cpp \
    API/Factory.cpp \
    Widget/PluginDialog.cpp \
    API/SerialData.cpp \
    API/Serializer.cpp \
    Widget/SDIEditorWindow.cpp \
    Widget/TabDisplayWidget.cpp \
    Manager/PluginManager.cpp \
    Core/Library.cpp \
    Core/Directory.cpp \
    Core/Editor.cpp \
    API/Loader.cpp \
    API/PluginDepr.cpp \
    API/Plugin.cpp \
    Context/ToolContext.cpp
#----------------------------------------------
#   Header Files.
#----------------------------------------------
HEADERS += \
    API/Factory.hpp \
    API/SerialData.hpp \
    API/Serializer.hpp \
	Widget/EditorDialog.hpp \
	Widget/SDIEditorWindow.hpp \
	Widget/EditorWindow.hpp \
    Widget/PluginDialog.hpp \
    Manager/GlobalManager.hpp \
    API/Variant.hpp \
    Widget/TabDisplayWidget.hpp \
    Manager/ApplicationManager.hpp \
    Manager/IconManager.hpp \
    Manager/PluginManager.hpp \
    API/Project.hpp \
    Core/Library.hpp \
    Core/Directory.hpp \
    API/TestPlugin.hpp \
    Core/Editor.hpp \
    API/Version.hpp \
    API/Loader.hpp \
    API/PluginDepr.hpp \
    API/Plugin.hpp \
    Plugins/TextEditorPlugin.hpp \
    Core/Plugin.hpp \
    Context/EditContext.hpp \
    Manager/PluginMan.hpp \
    Context/ToolContext.hpp
