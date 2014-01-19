#----------------------------------------------
#   Natural GM (c) 2013 Daniel Hrabovcak
#----------------------------------------------
#   Qt specific options.
#----------------------------------------------
#TEMPLATE	 =	app
QT			+=	core gui network
CONFIG		+=	c++11
#LIBS		+=	-L$$[QT_INSTALL_LIBS]

CONFIG(debug, release|debug) {
#	LIBS	+=	-lqscintilla2d
	TARGET	=	"Natural GM Debug"
#	CONFIG	+=	debug
#	CONFIG	-=	release
#	message("Debug mode set.")
} else {
#	LIBS	+=	-lqscintilla2
	TARGET	=	"Natural GM"
#	CONFIG	+=	release
#	message("Release mode set.")
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES		+=	QSCINTILLA_DLL
#----------------------------------------------
#   Include locations.
#----------------------------------------------
INCLUDEPATH	+=	$$PWD/ \
	Windows \
	Classes/ErrorLogger \
	Classes/RapidXML \
	Classes/Delegates \
	Classes/RapidJSON \
	Managers \
	Models \
	Dialogs \
	Widgets \
	Resources \
	Containers \
	Models/ResourceItemModel \
	Models/Proxy-Models \
	Models/ProjectItemModel \
	Resources/Serializers \
	Resources/Base \
	Resources/Editors \
	Resources/Types \
	Resources/Plugins \
	Widgets/Windows \
	Widgets/Dock-Widgets \
	Widgets/Widgets \
	Widgets/Dialogs
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
	Managers/PluginManager.hpp \
	Widgets/Dock Widgets/PropertyDockWidget.hpp \
	Widgets/Dock Widgets/PropertyDockWidget.hpp \
	Widgets/Dock-Widgets/PropertyDockWidget.hpp \
	Widgets/Dock-Widgets/DockWidget.hpp \
	Managers/PropertyManager.hpp \
	Resources/Plugins/SerialPlugin.hpp \
	Resources/Plugins/Plugin.hpp \
	Resources/Plugins/ToolPlugin.hpp \
	Widgets/Dock-Widgets/HierarchyDockWidget.hpp \
	Resources/Base/Variant.hpp \
	Managers/IconManager.hpp \
	Widgets/Windows/ResourceWindow.hpp \
    Models/Proxy-Models/SortGroupProxyModel.hpp \
    Managers/AppManager.hpp \
    Widgets/Dialogs/ProjectDialog2.hpp \
    Widgets/Widgets/ProjectWidget.hpp \
    Models/Proxy-Models/SortRootProxyModel.hpp \
    Resources/Base/FileDetails.hpp \
    Models/ProjectItemModel/ProjectFilterProxyModel.hpp \
    Models/ProjectItemModel/ProjectSetItemModel.hpp \
    Models/ProjectItemModel/ProjectSetModelItem.hpp \
    Models/ProjectItemModel/ProjectItemModel.hpp \
    Classes/Delegates/SizableItemDelegate.hpp
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
	Resources/Base/Base.cpp \
	Resources/Editors/TextEditor.cpp \
	Widgets/ResourceSplitterHandle.cpp \
	Widgets/HighlightWidget.cpp \
	Widgets/ResourceTabBar.cpp \
	Resources/Serializers/GMXSerializer.cpp \
	Models/ResourceItemModel/ResourceProxyModel.cpp \
	Managers/PluginManager.cpp \
	Widgets/Dock-Widgets/DockWidget.cpp \
	Managers/PropertyManager.cpp \
	Widgets/Dock-Widgets/HierarchyDockWidget.cpp \
	Managers/IconManager.cpp \
    Models/Proxy-Models/SortGroupProxyModel.cpp \
    Widgets/Windows/ResourceWindow.cpp \
    Managers/AppManager.cpp \
    Managers/AppManagerA.cpp \
    Managers/AppManagerB.cpp \
    Widgets/Dialogs/ProjectDialog2.cpp \
    Widgets/Widgets/ProjectWidget.cpp \
    Models/Proxy-Models/SortRootProxyModel.cpp \
    Models/ProjectItemModel/ProjectFilterProxyModel.cpp \
    Models/ProjectItemModel/ProjectSetModelItem.cpp \
    Models/ProjectItemModel/ProjectItemModel.cpp \
    Models/ProjectItemModel/ProjectSetItemModel.cpp \
    Resources/Base/FileDetails.cpp \
    Classes/Delegates/SizableItemDelegate.cpp \
    Managers/SettingManager.cpp
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
