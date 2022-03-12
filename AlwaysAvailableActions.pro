#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T21:41:14
#
#-------------------------------------------------

CONFIG(debug, debug|release) {
	DESTDIR = ./debug
	OBJECTS_DIR = $$DESTDIR/.obj
	MOC_DIR = $$DESTDIR/.moc
	RCC_DIR = $$DESTDIR/.qrc
	UI_DIR = $$DESTDIR/.ui
}

CONFIG(release, debug|release ) {
	DESTDIR = ./release
	OBJECTS_DIR = $$DESTDIR/.obj
	MOC_DIR = $$DESTDIR/.moc
	RCC_DIR = $$DESTDIR/.qrc
	UI_DIR = $$DESTDIR/.ui
}

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32 {
	# ShellExecute
	LIBS += -lole32
}

TARGET = alwaysAvailableActions
TEMPLATE = app

SOURCES += \
	CAlwaysAction.cpp \
	CProgramActionStep.cpp \
	main.cpp \
	CAlwaysMenu.cpp \
	CBuiltinActionFactory.cpp \
	CProgramSettings.cpp \
	Util.cpp \
	CSqueakyMenu.cpp \
	CSqueakyAction.cpp \
	CSystemTrayIcon.cpp \
	IActionStep.cpp \
	CArgumentProcessor.cpp \
	CSingleApplication.cpp

win32 {
	SOURCES += CShellExecuteActionStep.cpp
}

HEADERS += \
	CAlwaysAction.h \
	CAlwaysMenu.h \
	CBuiltinActionFactory.h \
	CProgramActionStep.h \
	CProgramSettings.h \
	Util.h \
	CSqueakyMenu.h \
	CSqueakyAction.h \
	CSystemTrayIcon.h \
	IActionStep.h \
	CArgumentProcessor.h \
	CSingleApplication.h

win32 {
	HEADERS += CShellExecuteActionStep.h
}

RESOURCES += \
	icons.qrc

DISTFILES += \
	Notes.txt
