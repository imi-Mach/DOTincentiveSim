#include <iostream>
#include <unistd.h>

using namespace std;

main(int argc, char **argv) {

    int x_spacing;
    int y_spacing;
    size_t dataPoints;
    pid_t pid;
    pid = fork();

    for (size_t x = 0; x < dataPoints; x++) {
        for (size_t y = 0; y < dataPoints; y++) {
            if((pid = fork()) == 0) {   

                exit(0); 
            }
            else if(pid < 0) {    
                cout << "Error occured: negative PID" << endl;
            }
            else {    
                int returnStatus;    
                waitpid(pid, &returnStatus, 0);

                if (returnStatus == 0) { /* child terminated successfully */
                  
                }

                if (returnStatus == 1) { /* child process terminated with an error */
                printf("The child process terminated with an error!.");    
                }
            }
            
        }
    }
    

}