#ifndef LOG_FILEIO_DEFINES_H
#define LOG_FILEIO_DEFINES_H

/*
        This exists to cut down on the visual pollution
        #ifdef <somedebug define>
        ///////stuff////////
        #endif
        Takes up a lot of realestate

*/

#ifndef NDEBUG

#define debug_logfile_create(path)\
do{\
        fprintf(stderr, "\033[92mLogfile creation\033[0m\nLogFile: %s\n", path);\
}while(0);

#define debug_logfile_nocreate(path)\
do{\
        fprintf(stderr, "\033[92mLogfile doesnt exist, create flag 0.\033[0m\nLogFile: %s\n", path);\
}while(0);\


#else
#define debug_logfile_create(path){};
#define debug_logfile_nocreate(path){};
#endif

#endif