#----------------------------------------------
#   Natural GM (c) 2013 Daniel Hrabovcak
#----------------------------------------------
#   Qt specific options.
#----------------------------------------------
greaterThan(QT_MAJOR_VERSION, 5)
QT			+=	widgets network
TEMPLATE	 =	app
TARGET		 =	"Natural-GM"
CONFIG		+=	c++11
LIBS		+=	-L$$[QT_INSTALL_LIBS] -lqscintilla2
DEFINES		+=	QSCINTILLA_DLL
#----------------------------------------------
#   Include locations.
#----------------------------------------------
INCLUDEPATH	+=	$$PWD/ \
	Windows \
	Classes/ErrorLogger \
	Managers \
	Models \
	Dialogs \
	Widgets \
	Resources \
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
	Models/BasicItem.hpp \
	Models/ColumnItem.hpp \
	Models/BasicModel.hpp \
	Models/ColumnModel.hpp \
	Dialogs/ProjectDialog.hpp \
	Global.hpp \
	Managers/ProjectManager.hpp \
	Resources/Serializers/TextSerializer.hpp \
	Widgets/ResourceTab.hpp \
	Widgets/ResourceSplitter.hpp \
	Resources/Types/TextType.hpp \
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
	Resources/Editors/TextEditor.hpp
#----------------------------------------------
#   Source files.
#----------------------------------------------
SOURCES		+= \
	Main.cpp \
	Classes/ErrorLogger/ErrorLogger.cpp \
	Windows/MainWindow.cpp \
	Managers/WindowManager.cpp \
	Models/BasicItem.cpp \
	Models/BasicModel.cpp \
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
	Resources/Types/TextType.cpp \
	Resources/Editors/TextEditor.cpp
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
