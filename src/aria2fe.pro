TEMPLATE = app
LANGUAGE = C++

CONFIG +=		qt warn_on release

SOURCES +=	main.cpp \
						mainwindow.cpp \
						aboutdlg.cpp \
						helpdlg.cpp \
						argsdlg.cpp \
						ftpargsdlg.cpp \
						httpargsdlg.cpp \
						metaargsdlg.cpp \
						torrentargsdlg.cpp

HEADERS +=	mainwindow.h \
						aboutdlg.h \
						helpdlg.h \
						argsdlg.h \
						ftpargsdlg.h \
						httpargsdlg.h \
						metaargsdlg.h \
						torrentargsdlg.h

FORMS +=		forms/mainwindow.ui \
						forms/aboutdlg.ui \
						forms/helpdlg.ui \
						forms/argsdlg.ui \
						forms/ftpargsdlg.ui \
						forms/httpargsdlg.ui \
						forms/metaargsdlg.ui \
						forms/torrentargsdlg.ui

RESOURCES =	resources.qrc

DESTDIR =		../bin

TARGET =		aria2fe

unix {
	UI_DIR = build/ui
	MOC_DIR = build/moc
	OBJECTS_DIR = build/obj
}
