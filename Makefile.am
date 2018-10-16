lib_LTLIBRARIES = libSimpleNodeStateMachine.la

libSimpleNodeStateMachine_la_CFLAGS = -I../NodeStateManager \
                                    $(GIO_CFLAGS)         \
                                    $(GIO_UNIX_CFLAGS)    \
                                    $(GLIB_CFLAGS)        \
                                    $(GOBJECT_CFLAGS)
libSimpleNodeStateMachine_la_SOURCES = NodeStateMachine.c

nodist_libSimpleNodeStateMachine_la_SOURCES = SimpleNodeStateMachineApi.c

libSimpleNodeStateMachine_la_LDFLAGS = -avoid-version

BUILT_SOURCES = SimpleNodeStateMachineApi.h

CLEANFILES    = SimpleNodeStateMachineApi.c \
                SimpleNodeStateMachineApi.h

SimpleNodeStateMachineApi.c SimpleNodeStateMachineApi.h: org.genivi.SimpleNodeStateMachine.xml
	gdbus-codegen --interface-prefix org.genivi.SimpleNodeStateMachine. --c-namespace NodeState --generate-c-code SimpleNodeStateMachineApi --annotate "org.genivi.SimpleNodeStateMachine.Shutdown()" org.gtk.GDBus.C.ForceGVariant true $<

dbuspolicy_DATA = org.genivi.SimpleNodeStateMachine.conf

EXTRA_DIST = $(dbuspolicy_DATA)
