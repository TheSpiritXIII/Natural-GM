Natural GM
==========

__NOTE:__ PLUGINS ARE NOT CURRENTLY FUNCTIONAL.

Plugins are helpful dynamic libraries. Users are allowed to make and
share their own icons to increase their experience. Whether it be
adding new resource types, replacing existing editors or adding a
small convenience script, it is possible.

Installation
------------

Writing plugins will requires the correct headers. To generate all
useful headers, simply run the python script. Python 2.6 or higher is
needed in order to run the script. After running the script, you
must include this directory.


Usage
-----

Plugins are essentially libraries compiled in C++. If you would like
it to interact with Qt, you must include the Qt library. A plugin must
have at least one _getPluginInfo_ implemented or else it will not be
laoded. Plugins are provided access with classes in NGM, to be able to
add custom resource types, widgets, etc. The following are available
functions that the plugin loader searches for:

```c++
namespace NGM
{
	enum class Plugin
	{
		NAME			=	0,
		AUTHOR			=	1,
		DESCRIPTION		=	2
	};
}
bool actionManager(NGM::Manager::ActionManager *manager);
bool windowManager(NGM::Manager::WindowManager *manager);
bool resourceManager(NGM::Manager::ResourceManager *manager);
bool windowCreated(QMainWindow *window);
const char* getPluginInfo(NGM::Plugin type);
```

If you create a new resource or project type, icons will automatically
be loaded based on the respective identifier names.