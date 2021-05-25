app:    application.o       KVS-lib.o       app_func.o
        cc      -o      app     application.o   KVS-lib.o       app_func.o
KVS-lib.o:      KVS-lib.c
        cc      -c      KVS-lib.c
app_func.o:     app_func.c      KVS-lib.h
        cc      -c      app_func.c
application.o:  application.c   KVS-lib.h       app_func.h
        cc      -c      application.
clean:
        rm      app     application.o   KVS-lib.o       app_func.o