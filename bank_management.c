#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void menu_show(){
       printf("\t\t\t [1] Create Account\n");
       printf("\t\t\t [2] Show Existing Account\n");
       printf("\t\t\t [3] Update Account\n");
       printf("\t\t\t [4] Withdraw Account\n");
       printf("\t\t\t [5] Deposit Account\n");
       printf("\t\t\t [6] Check Balance\n");
       printf("\t\t\t [7] Statement\n");
       printf("\t\t\t [8] Delete account\n");

}
void dynamic_new_line(int n){
       int i=0;
       while(i < n){
              printf("\n");
              i++;
       }
}

void welcome_message(void){
       char message[]="################  Welcome To The Bank Management System  ################";
       printf("%s",message);
       dynamic_new_line(1);
}

void select_menu(){
       int op_select;
       
       printf("\t\t Please Enter any number[1-7] or 0 To Exit: ");
       scanf("%d",&op_select);

       switch (op_select)
       {
              case 0 : 
              printf("0 called");
              break;
              case 1 : 
              printf("1 called");
              break;
              case 2 : 
              printf("2 called");
              break;
              case 3 : 
              printf("3 called");
              break;
              case 4 : 
              printf("4 called");
              break;
              case 5 : 
              printf("5 called");
              break;
              case 6 : 
              printf("6 called");
              break;
              case 7 : 
              printf("7 called");
              break;
       
       default:
              printf("\t\t Please Enter any number[1-7] or 0 To Exit: ");
              scanf("%d",&op_select);
              break;
       }

}


int main(){
   welcome_message();

   menu_show();
   select_menu();

   return 0;
}