## What is Always Available Actions (AAA)?

AAA is a simple utility program which lives in your system tray and provides quick access to scripts, directories, programs, and shortcuts by reducing the number of clicks and keystrokes between you and your automated task.

## How do I use Always Available Actions?

AAA appears in the system tray as an unmistakably bright green square icon and can be "torn-off" into a floating context menu. From the menu you may run items with left click or open them for editing with middle click. Actions will be opened in a text editor while everything else will be opened in a file explorer.

Keeping the icon ever-present in the system tray varies between Windows versions and Linux window managers. Consult your favourite search engine for how to do this.

### Platform configuration files

AAA's main configuration files are `windows.cfg` and `linux.cfg` and live in the same directory as the program. They have the format of keyvalue pairs, one per line, where everything before the first space is the key and everything after is the value. Both files support the same keyvalues which are as follows:

```
# In both cases, <program> is invoked with the directory or action file as the only argument
fileBrowser <program>
textEditor <program>
```

### Action files

AAA will load actions from all `*.aaa` files within the `actions` directory in the same directory as the application. These files are simply text files with a special extension to distinguish them from anything else that may reside within the `actions` directory. The action files use the same keyvalue format as the platform configuration files. Their keyvalues are as follows:

```
# <string> appears as the title of the action in the menu.
name <string>

# A space-separated list of platforms for which this action should appear.
# Only two platforms are currently supported: "windows" and "linux".
platforms <string>

# <string> may be an absolute path, a relative path starting from the location
# of the action file, or the name of any executable in your PATH.
# Escaping and quoting is generally unnecessary. The value is used as-is.
# An action may run multiple programs one after another.
program <string>

# Any argument following a program will be added for that program.
arg <string>

# Programs run synchronously will have their exit code checked upon completion.
# The action will terminate and report the first non-zero exit code unless silent.
# <boolean> is assumed to be truthy if omitted.
silent <boolean>

# This key will cause the action to not wait for the program
# to complete before moving on. The exit code will be ignored.
# The last program in an action is automatically run asynchronously.
# <boolean> is assumed to be truthy if omitted.
async <boolean>
```

### Shortcuts and symlinks

On Windows, shortcuts will run the application or open the target directory depending on what the shortcut points to. On Linux, only symlinks which point to directories will be action-ized but work in the same way.

### Command line options

AAA will react to the following set of command line arguments by producing a platform-appropriate alert.

```
--show-message <title> <message>
--show-information <title> <message>
--show-warning <title> <message>
--show-critical <title> <message>
```

These arguments will not start AAA if it is not already running.

## Other notes

- AAA is a single instance application and is not designed for a multi-user environment.
- Observant users will notice Qt's network module in the download. This is core to the single application instance.
- The included "ClipboardFX" actions require the "win32clipboard" Python module on Windows to function.

## Legal stuff

Always Available Actions is made with Qt and is licensed under [LGPL 3.0](LICENCE.md) accordingly.
