#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void welcome_message(void){// This function will handle Welcome Message
    char m[]= "$$$$$$$$$$  Welcome To The Bank Management System  $$$$$$$$$$";
    int l=0;
    while(m[l] != '\0'){
        l++;
    }
    for(int i=0;i<l;i++){
        printf("%c",m[i]);
        Sleep(40);
    }
}
void new_line(int x){ // This function will handle New lines
    for(int i=0;i<x;i++){
        printf("\n");
    }
}
int main(){
    welcome_message();
    new_line(1);
    return 0;


}
