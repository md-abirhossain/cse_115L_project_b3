#ifdef _WIN32
	    #ifdef _WIN64
	    #include <windows.h>
                     #define os 1
	        void clear_scr(){
	            system("cls");
	        }
	        void wait(float x){
	            Sleep(x/10);
	        }
	    #else
	    #include <windows.h>
                     #define os 1
	        void clear_scr(){
	            system("cls");
	        }
	        void wait(float x){
	            Sleep(x/10);
	        }
	    #endif
	#else
	#include <unistd.h>
                 #define os 0
	    void clear_scr(){
	            fflush(stdout);
	            system("clear");
	        }
	        void wait(float x){
	            fflush(stdout);

	            usleep(x*100);
	        }
#endif

