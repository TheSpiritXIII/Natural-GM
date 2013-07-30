#----------------------------------------------
#   Natural GM (c) 2013 Daniel Hrabovcak
#----------------------------------------------
#   Qt specific options.
#----------------------------------------------
greaterThan(QT_MAJOR_VERSION, 5)
QT			+=	widgets network
TEMPLATE	=	app
TARGET		=	"Natural-GM"
CONFIG		+=	c++11
#----------------------------------------------
#   Include locations.
#----------------------------------------------
DEPENDPATH	+=	Windows \
	Classes/ErrorLogger \
	Managers \
	Models \
	Dialogs \
	Widgets \
	Resources \
	Models/ResourceItemModel \
	Resources/Serializers
INCLUDEPATH	+=	Windows \
	Classes/ErrorLogger \
	Managers \
	Models \
	Dialogs \
	Widgets \
	Resources \
	Models/ResourceItemModel \
	Resources\Serializers
#----------------------------------------------
#   Header files.
#----------------------------------------------
HEADERS		+=	Windows/MainWindow.hpp \
	Classes/ErrorLogger/ErrorLogger.hpp \
	Managers/WindowManager.hpp \
	Managers/ResourceManager.hpp \
	Managers/IconManager.hpp \
	Managers/ActionManager.hpp \
	Models/BasicItem.hpp \
	Models/ColumnItem.hpp \
	Models/BasicModel.hpp \
	Models/ColumnModel.hpp \
	Resources/Resource.hpp \
	Dialogs/ProjectDialog.hpp \
	Global.hpp \
	Managers/ProjectManager.hpp \
	Resources/Project.hpp \
	Resources/Serializer.hpp \
	Resources/Serializers/TextSerializer.hpp \
	Resources/Widget.hpp \
	Resources/Type.hpp \
	Widgets/ResourceTab.hpp \
	Widgets/ResourceSplitter.hpp \
	Resources/Widgets/TextWidget.hpp \
	Resources/Types/TextType.hpp \
	Models/ResourceItemModel/ResourceBaseItem.hpp \
	Models/ResourceItemModel/ResourceContentItem.hpp \
	Models/ResourceItemModel/ResourceGroupItem.hpp \
	Models/ResourceItemModel/ResourceProjectItem.hpp \
	Models/ResourceItemModel/ResourceItemModel.hpp \
	Classes/RapidXML/RapidXML.hpp
#----------------------------------------------
#   Source files.
#----------------------------------------------
SOURCES		+= \
	Main.cpp \
	Classes/ErrorLogger/ErrorLogger.cpp \
	Windows/MainWindow.cpp \
	Managers/WindowManager.cpp \
	Managers/IconManager.cpp \
	Models/BasicItem.cpp \
	Models/BasicModel.cpp \
	Dialogs/ProjectDialog.cpp \
	Managers/ActionManager.cpp \
	Managers/ProjectManager.cpp \
	Widgets/ResourceSplitter.cpp \
	Widgets/ResourceTab.cpp \
	Resources/Serializers/TextSerializer.cpp \
	Resources/Widgets/TextWidget.cpp \
	Models/ResourceItemModel/ResourceBaseItem.cpp \
	Models/ResourceItemModel/ResourceGroupItem.cpp \
	Models/ResourceItemModel/ResourceItemModel.cpp
#----------------------------------------------
#   Application Icons.
#----------------------------------------------
#win32:RC_FILE = resource.rc
TRANSLATIONS	=	untranslated.ts
#----------------------------------------------
#   Static building.
#----------------------------------------------
#CONFIG += static
