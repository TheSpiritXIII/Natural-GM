#----------------------------------------------
#   Natural GM (c) 2013 Daniel Hrabovcak
#----------------------------------------------
#   Qt specific options.
#----------------------------------------------
TEMPLATE	 =	app
QT			+=	core gui widgets network
CONFIG		+=	c++11
LIBS		+=	-L$$[QT_INSTALL_LIBS]

CONFIG(debug, release|debug) {
	LIBS	+=	-lqscintilla2
	TARGET	=	"Natural GM Debug"
	CONFIG	+=	debug
	CONFIG	-=	release
} else {
	LIBS	+=	-lqscintilla2
	TARGET	=	"Natural GM"
	CONFIG	+=	release
}
DEFINES		+=	QSCINTILLA_DLL
#----------------------------------------------
#   Include locations.
#----------------------------------------------
INCLUDEPATH	+=	$$PWD/ \
	Windows \
	Classes/ErrorLogger \
	Classes/RapidXML \
	Managers \
	Models \
	Dialogs \
	Widgets \
	Resources \
	Containers \
	Models/ResourceItemModel \
	Resources/Serializers \
	Resources/Base \
	Resources/Editors \
	Resources/Types
#----------------------------------------------
#   Header files.
#----------------------------------------------
HEADERS		+=	Windows/MainWindow.hpp \
	Classes/ErrorLogger/ErrorLogger.hpp \
	Managers/WindowManager.hpp \
	Managers/ActionManager.hpp \
	Dialogs/ProjectDialog.hpp \
	Global.hpp \
	Managers/ProjectManager.hpp \
	Resources/Serializers/TextSerializer.hpp \
	Widgets/ResourceTab.hpp \
	Widgets/ResourceSplitter.hpp \
	Models/ResourceItemModel/ResourceBaseItem.hpp \
	Models/ResourceItemModel/ResourceContentItem.hpp \
	Models/ResourceItemModel/ResourceGroupItem.hpp \
	Models/ResourceItemModel/ResourceProjectItem.hpp \
	Models/ResourceItemModel/ResourceItemModel.hpp \
	Classes/RapidXML/RapidXML.hpp \
	Dialogs/AboutDialog.hpp \
	Widgets/ResourceDialog.hpp \
	Resources/Serializers/GMXSerializer.hpp \
	Managers/SettingManager.hpp \
	Managers/ThreadManager.hpp \
	Resources/Base/Serializer.hpp \
	Resources/Base/Type.hpp \
	Resources/Base/Project.hpp \
	Defines.hpp \
	Resources/Base/SerialData.hpp \
	Resources/Base/Resource.hpp \
	Resources/Base/Editor.hpp \
	Resources/Editors/TextEditor.hpp \
	Classes/StatusWidget.hpp \
	Widgets/ResourceSplitterHandle.hpp \
	Widgets/HighlightWidget.hpp \
	Widgets/ResourceTabBar.hpp \
	Models/ResourceItemModel/ResourceProxyModel.hpp \
	Containers/String.hpp \
	Containers/Map.hpp \
	Containers/Vector.hpp \
	Managers/ProgressManager.hpp \
	Containers/List.hpp \
	Containers/Set.hpp \
	Containers/Queue.hpp \
	Resources/Base/Factory.hpp \
	Containers/Deque.hpp \
	Containers/Stack.hpp \
	Managers/Plugin.hpp \
	Managers/PluginManager.hpp \
	Managers/GlobalManager.hpp
#----------------------------------------------
#   Source files.
#----------------------------------------------
SOURCES		+= \
	Main.cpp \
	Classes/ErrorLogger/ErrorLogger.cpp \
	Windows/MainWindow.cpp \
	Managers/WindowManager.cpp \
	Dialogs/ProjectDialog.cpp \
	Managers/ActionManager.cpp \
	Managers/ProjectManager.cpp \
	Widgets/ResourceSplitter.cpp \
	Widgets/ResourceTab.cpp \
	Resources/Serializers/TextSerializer.cpp \
	Models/ResourceItemModel/ResourceBaseItem.cpp \
	Models/ResourceItemModel/ResourceGroupItem.cpp \
	Models/ResourceItemModel/ResourceItemModel.cpp \
	Dialogs/AboutDialog.cpp \
	Widgets/ResourceDialog.cpp \
	Resources/Base/SerialData.cpp \
	Resources/Base/Base.cpp \
	Resources/Editors/TextEditor.cpp \
	Widgets/ResourceSplitterHandle.cpp \
	Widgets/HighlightWidget.cpp \
	Widgets/ResourceTabBar.cpp \
	Resources/Serializers/GMXSerializer.cpp \
	Models/ResourceItemModel/ResourceProxyModel.cpp \
	Managers/PluginManager.cpp \
	Managers/GlobalManager.cpp
#----------------------------------------------
#   Application Icons.
#----------------------------------------------
win32:RC_FILE	=	Platform/Windows.rc
#----------------------------------------------
#	Translations.
#----------------------------------------------
TRANSLATIONS	=	Translations/untranslated.ts
#----------------------------------------------
#   Static building.
#----------------------------------------------
#CONFIG += static
