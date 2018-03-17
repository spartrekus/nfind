
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif



#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

char searchitem[PATH_MAX];
void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
	{
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf( path, sizeof(path), "%s/%s", name, entry->d_name);

            listdir( path, indent + 2);
        } 
	else 
	{
	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
	    {
              //printf("DIR %s\n", name );
              //printf("%*s- %s\n", indent, "", entry->d_name);
              printf("%s/%s\n", name , entry->d_name );
	    }
        }
    }
    closedir(dir);
}






////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
    ////////////////////////////////////////////////////////
    if ( argc == 2)
     if ( strcmp( argv[1] , "" ) !=  0 ) 
     {
         strncpy( searchitem, argv[ 1 ], PATH_MAX );          
         listdir( ".", 0 ) ;
         return 0;
     }
     return 0;
}



