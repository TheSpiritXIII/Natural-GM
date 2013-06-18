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
	Managers/WindowManager \
	Managers/ResourceManager \
	Managers/ActionManager \
	Models
INCLUDEPATH	+=	Windows \
	Classes/ErrorLogger \
	Managers/WindowManager \
	Managers/ActionManager \
	Models
#----------------------------------------------
#   Header files.
#----------------------------------------------
HEADERS		+=	Windows/MainWindow.hpp \
	Classes/ErrorLogger/ErrorLogger.hpp \
	Managers/WindowManager/WindowManager.hpp \
	Managers/ResourceManager/ResourceManager.hpp \
	Managers/IconManager/IconManager.hpp \
	Managers/ActionManager/ActionManager.hpp \
	Models/BasicItem.hpp \
	Models/ColumnItem.hpp \
	Models/BasicModel.hpp \
	Models/ColumnModel.hpp \
	Classes/TinyXML-2/TinyXML-2.hpp \
	Models/ResourceItem.hpp \
	Models/ResourceModel.hpp \
	Resources/Resource.hpp \
	Dialogs/ProjectDialog.hpp \
    Global.hpp \
    Managers/ProjectManager/ProjectManager.hpp \
    Resources/Project.hpp
#----------------------------------------------
#   Source files.
#----------------------------------------------
SOURCES		+= \
	Main.cpp \
	Classes/ErrorLogger/ErrorLogger.cpp \
	Windows/MainWindow.cpp \
	Managers/WindowManager/WindowManager.cpp \
	Managers/IconManager/IconManager.cpp \
	Models/BasicItem.cpp \
	Classes/TinyXML-2/TinyXML-2.cpp \
	Models/ResourceItem.cpp \
	Models/BasicModel.cpp \
	Dialogs/ProjectDialog.cpp
#----------------------------------------------
#   Application Icons.
#----------------------------------------------
#win32:RC_FILE = resource.rc
#----------------------------------------------
#   Static building.
#----------------------------------------------
CONFIG += static
