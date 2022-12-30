#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "file_names.h"
#include "checkos.h"

typedef struct Bank
{
    char name[31];
    char password[9];
    char email[33];
    char address[30];
    char phone[12];
    int acount_no;
    float balance;
} acc;
typedef struct Statement
{
    char type[20];
    int account;
    char name[31];
    float amt;
    char password[9];
    char date_time[100];
} stmt;
int attempt=0;
void welcome_message();
void line_start();
void line_end();
void show_msg(char tmp[],int to_time);
void new_line(int x);
int isName(char tmp[],int len);
int isEmail(char tmp[], int len);
int isPwd(char tmp[],int len);
int isPhn(char tmp[],int len);
int email_exs(char tmp[]);
void generate_acc(int *tmp);
void create_account();
void show_accounts();
void update_account();
void withdraw_money();
void deposit_money();
void show_statement();
void delete_account();
void menu();
void option_select();
void goto_menu();
void check_file();
void exit_func();
void main()
{
    check_file();
    new_line(1);
    menu();
    option_select();
}
void welcome_message()	// This function will handle Welcome Message
{
    char m[] = "$$$$$$$$$$ Welcome To The Bank Management System $$$$$$$$$$";
    for(int i=0; i<strlen(m); i++)
    {
        printf("%c",m[i]);
        wait(120);
    }
}
void line_start()
{
    printf("\t\t=======================================================================================\n");
}
void line_end()
{
    printf("\t\t=======================================================================================\n\n");
}
void show_msg(char tmp[],int to_time)
{
    printf("\t\t\t\t\t");
    for(int i=0; i<strlen(tmp); i++)
    {
        printf("%c",tmp[i]);
        wait(to_time);
    }
}
void new_line(int x)	// This function will handle New lines
{
    for (int i = 0; i < x; i++)
    {
        printf("\n");
    }
}

int isName(char tmp[],int len)
{
    int i;
    int letter=1;
    for(i=0; i<len; i++)
    {
        if(isspace(tmp[i]) || tmp[i]=='.')
        {
            continue;
        }
        else if(!isalpha(tmp[i]))
        {
            letter = 0;
            break;
        }

    }
    if(letter && (len <= 30) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
int isEmail(char tmp[], int len)
{
    int sp = 0, dot = 0;
    for (int i = 0; i < len; i++)
    {
        if (tmp[i] == '@')
        {
            sp++;
        }
        else if (tmp[i] == '.')
        {
            dot++;
        }
    }

    if ((sp == 1) && (dot >= 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}
int isPwd(char tmp[],int len)
{
    int upper=0,lower=0,s_c=0,digit=0,white_space=0;
    int i;
    for(i=0; i<len; i++)
    {
        if(islower(tmp[i]))
        {
            lower = 1;
        }
        else if(isupper(tmp[i]))
        {
            upper=1;
        }
        else if(isdigit(tmp[i]))
        {
            digit=1;
        }
        else if(isspace(tmp[i]))
        {
            white_space=1;
        }
        else
        {
            s_c=1;
        }
    }
    if(upper && lower && digit && !white_space && s_c && len==8)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int isPhn(char tmp[],int len)
{
    int i;
    if(!(len==11))
    {
        return false;
    }
    for(i=0; i<len; i++)
    {
        if(!isdigit(tmp[i]))
        {
            return false;
        }
    }
}
int email_exs(char tmp[])
{
    acc tmp_data;
    FILE *file_email_check;
    file_email_check=fopen(main_file,main_file_mode_read);
    int isFound=1;
    while(fscanf(file_email_check,"%d\t%[^\t]%*c\t%s\t%s\t%s\t%[^\t]%*c\t%f\n",&tmp_data.acount_no,tmp_data.name,tmp_data.email,tmp_data.phone,tmp_data.password,tmp_data.address,&tmp_data.balance) != EOF)
    {
        if(strcmp(tmp,tmp_data.email)==0)
        {
            isFound=0;
            break;
        }
    }
    fclose(file_email_check);
    if(isFound)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void generate_acc(int *tmp)
{
    acc info;
    int tmp_act,count=0;
    FILE *file_gnr_acc;
    file_gnr_acc=fopen(main_file,main_file_mode_read);
    if(file_gnr_acc == NULL)
    {
        tmp_act=223;
        fclose(file_gnr_acc);
        *tmp=tmp_act;
    }
    else
    {
        while(fscanf(file_gnr_acc,"%d\t%[^\t]%*c\t%s\t%s\t%s\t%[^\t]%*c\t%f\n",&info.acount_no,info.name,info.email,info.phone,info.password,info.address,&info.balance)!= EOF)
        {
            tmp_act=info.acount_no;
            count++;
        }
    }
    fclose(file_gnr_acc);
    if(count==0)
    {
        *tmp=223;
    }
    else
    {
        *tmp=tmp_act + 1;
    }

}
void create_account()
{
    clear_scr();
    line_start();
    show_msg("Create New Account",100);
    new_line(1);
    line_end();
    new_line(2);

    acc info;
    printf("\t\t\t\tEnter Name: ");
goback_name:
    scanf(" %[^\n]%*c", info.name);
    if (!isName(info.name,strlen(info.name)))
    {
        new_line(1);
        printf("\t\t\t\tPlease Enter A Valid Name: ");
        goto goback_name;
    }

    printf("\t\t\t\tEnter Email: ");
goback_email:
    scanf(" %[^\n]%*c", info.email);
    if(!email_exs(info.email))
    {
        new_line(1);
        printf("\t\t\t\tEmail Already Exists!!!\n\n\t\t\t\tEnter Again: ");
        goto goback_email;
    }
    if (!isEmail(info.email, strlen(info.email)))
    {
        new_line(1);
        printf("\t\t\t\tPlease Enter Valid Email Address: ");
        goto goback_email;
    }
    printf("\t\t\t\tPlease enter your password (8 Characters): ");
goback_password:
    scanf(" %s", info.password);
    if (!isPwd(info.password, strlen(info.password)))
    {
        new_line(1);
        printf("\tPlease Enter a password which have special character, digit, Upper case , Lower Case letter: ");
        goto goback_password;
    }
    printf("\t\t\t\tEnter phone Number: ");
goback_phone:
    scanf(" %s", info.phone);
    if (!isPhn(info.phone, strlen(info.phone)))
    {
        new_line(1);
        printf("\t\t\t\tPlease Enter a valid phone number (11 Digits): ");
        goto goback_phone;
    }

    printf("\t\t\t\tEnter address : ");
goback_address:

    scanf(" %[^\n]%*c", info.address);
    if (strlen(info.address) > 30)
    {
        new_line(1);
        printf("\t\t\t\t Please Enter address less than 30 characters: ");
        goto goback_address;
    }
    info.balance=0.00;
    generate_acc(&info.acount_no);
    FILE *file_cr_account;
    file_cr_account=fopen(main_file,main_file_mode_append);
    fprintf(file_cr_account,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
    fclose(file_cr_account);
    new_line(1);
    printf("\t\t\t\t\tAccount Created!");
    new_line(2);
    printf("\t\t\t\t\tYour account number is : %d",info.acount_no);
    new_line(2);
    goto_menu();
}
void show_accounts()
{
    clear_scr();
    char manager_pwd[20];
    printf("\t\t\t\tWelcome, Sir!");
    new_line(2);
    printf("\t\t\t\tEnter password: ");
    scanf(" %[^\n]%*c",manager_pwd);
    if(strcmp(manager_pwd,"B3") !=0 )
    {
        printf("\t\t\t\tSorry, Sir! You have entered wrong password!");
        new_line(2);
        goto_menu();

    }
    clear_scr();
    line_start();
    show_msg("!!!List Of Accounts!!!!",100);
    new_line(1);
    line_end();
    new_line(2);
    FILE *file_shw_account;
    file_shw_account=fopen(main_file,main_file_mode_read);
    if(file_shw_account == NULL)
    {
        printf("\t\t||                                No Accounts Found!!!                                  ||\n");
        fclose(file_shw_account);
    }
    else
    {
        acc info;
        int count=0;
        while(fscanf(file_shw_account,"%d\t%[^\t]%*c\t%s\t%s\t%s\t%[^\t]%*c\t%f\n",&info.acount_no,info.name,info.email,info.phone,info.password,info.address,&info.balance)!= EOF)
        {
            printf("\t\t\tAccount No: %d\n",info.acount_no);
            printf("\t\t\tName: %s\n",info.name);
            printf("\t\t\tEmail: %s\n",info.email);
            printf("\t\t\tPhone: %s\n",info.phone);
            printf("\t\t\tAddress: %s\n",info.address);
            printf("\t\t\tBalance: %.2f\n",info.balance);
            new_line(2);
            count++;
        }
        fclose(file_shw_account);
        if(count==0)
        {
            printf("\t\t||                                No Accounts Found!!!                                  ||\n");
            new_line(2);
        }
    }
    goto_menu();
}
void update_account()
{
    clear_scr();
    line_start();
    show_msg("!!!Update your information!!!",100);
    new_line(1);
    line_end();
    new_line(2);
    acc info;
    FILE *filer_up;
    FILE *filew_up;
    int state;
    int tmp_acc,op;
    char tmp_pwd[9];
    char tmp_up[50];
    state=0;
    filer_up=fopen(main_file,main_file_mode_read);
    filew_up=fopen(tmp_file,tmp_file_append);
    printf("\t\t\t\t Please enter your account no: ");
    scanf("%d",&tmp_acc);
    printf("\t\t\t\t Please enter your password: ");
    scanf(" %[^\n]%*c",tmp_pwd);
    while(fscanf(filer_up,"%d\t%[^\t]%*c\t%s\t%s\t%s\t%[^\t]%*c\t%f\n",&info.acount_no,info.name,info.email,info.phone,info.password,info.address,&info.balance)!= EOF)
    {
        if((info.acount_no == tmp_acc) && (strcmp(info.password,tmp_pwd)==0))
        {
            clear_scr();
            new_line(2);
            printf("\t\t\t Welcome %s !!!",info.name);
            new_line(3);
            printf("\t\t\tPlease Select what you want to edit ==>\n\n");
            printf("\t\t\t[1]Name\n\n");
            printf("\t\t\t[2]Email\n\n");
            printf("\t\t\t[3]Password\n\n");
            printf("\t\t\t[4]Phone");
            new_line(3);
            printf("\t\t\t Please Enter your choice [1-4]: ");
check_op:
            scanf("%d",&op);
            switch (op)
            {
            case 1:
                printf("\t\t\tEnter your new name: ");
goback_name:
                scanf(" %[^\n]%*c",tmp_up);
                if(!isName(tmp_up,strlen(tmp_up)))
                {
                    printf("\t\t\tPlease Enter a valid name: ");
                    goto goback_name;
                }
                else
                {
                    strcpy(info.name,tmp_up);
                    fprintf(filew_up,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
                    printf("\t\t\t\t Name Updated!!!!!");
                    new_line(2);
                    state=1;
                    attempt=0;
                }
                break;
            case 2:
                printf("\t\t\tYour Current Email Address is : %s",info.email);
                new_line(2);
                printf("\t\t\tEnter your new email: ");
goback_email:
                scanf(" %s",tmp_up);
                if(!isEmail(tmp_up,strlen(tmp_up)))
                {
                    printf("\t\t\t\t Please Enter a valid name: ");
                    goto goback_email;
                }
                else
                {
                    strcpy(info.email,tmp_up);
                    fprintf(filew_up,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
                    printf("\t\t\t\t Email Updated!!!!!");
                    new_line(2);
                    state=1;
                    attempt=0;
                }
                break;
            case 3:
                printf("Enter your new password: ");
goback_pwd:
                scanf(" %s",tmp_up);
                if(!isPwd(tmp_up,strlen(tmp_up)))
                {
                    printf("Please Enter a valid password: ");
                    goto goback_pwd;
                }
                else
                {
                    strcpy(info.password,tmp_up);
                    fprintf(filew_up,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
                    printf("\t\t\t\t Password Updated!!!!!");
                    new_line(2);
                    state=1;
                    attempt=0;
                }
                break;
            case 4:
                printf("\t\t\tYour Current Phone number is : %s",info.phone);
                new_line(2);
                printf("\t\t\tEnter your new Phone Number: ");
goback_phone:
                scanf(" %s",tmp_up);
                if(!isPhn(tmp_up,strlen(tmp_up)))
                {
                    printf("\t\t\tPlease Enter a valid Phone Number: ");
                    goto goback_phone;
                }
                else
                {
                    strcpy(info.phone,tmp_up);
                    fprintf(filew_up,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
                    printf("\t\t\t\t Phone number Updated!!!!!");
                    new_line(2);
                    state=1;
                    attempt=0;
                }
                break;
            default:
                printf("\t\t\tPlease Enter in the range [0-4]:");
                goto check_op;
                break;
            }
        }
        else
        {
            fprintf(filew_up,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
        }
    }
    if(state)
    {
        fclose(filer_up);
        fclose(filew_up);
        remove(main_file);
        rename(tmp_file,main_file);
        new_line(1);
        attempt=0;
        goto_menu();
    }
    else if(attempt < 2)
    {
        printf("\t\t\t\tYou have entered wrong info!!!!!");
        fclose(filer_up);
        fclose(filew_up);
        remove(tmp_file);
        new_line(1);
        attempt++;
        new_line(2);
        wait(2000);
        show_msg("Reloading section..........",550);
        new_line(1);
        update_account();
    }
    else
    {
        printf("\t\t\t\tYou have entered maximum amount of time!!!!!");
        fclose(filer_up);
        fclose(filew_up);
        remove(tmp_file);
        new_line(2);
        attempt=0;
        goto_menu();
    }


}
void withdraw_money()
{
    clear_scr();
    new_line(1);
    line_start();
    show_msg("Withdraw Money !!!",100);
    new_line(2);
    line_end();
    new_line(1);
    acc info;
    FILE *filer_wtr;
    FILE *filew_wtr;
    FILE *filew_1_wtr;
    int state;
    int tmp_acc;
    float amt;
    char tmp_pwd[100];
    state=0;
    filer_wtr=fopen(main_file,main_file_mode_read);
    filew_1_wtr=fopen(tmp_file,tmp_file_append);
    printf("\t\t\t\t Please enter your account no: ");
    scanf("%d",&tmp_acc);
    printf("\t\t\t\t Please enter your password: ");
    scanf(" %s",tmp_pwd);
    while(fscanf(filer_wtr,"%d\t%[^\t]%*c\t%s\t%s\t%s\t%[^\t]%*c\t%f\n",&info.acount_no,info.name,info.email,info.phone,info.password,info.address,&info.balance)!= EOF)
    {
        if((info.acount_no == tmp_acc) && (strcmp(info.password,tmp_pwd)==0))
        {
            time_t t;
            time(&t);
            clear_scr();
            new_line(2);
            printf("\t\t\t Welcome %s !!!",info.name);
            new_line(1);
            printf("\t\t\t Your current account balance = %.2f",info.balance);
            new_line(3);
            printf("\t\t\t\t Enter Amount: ");
            scanf("%f",&amt);
            if(amt > info.balance)
            {
                fclose(filew_1_wtr);
                fclose(filer_wtr);
                printf("\t\t\tYou don't have enough balance!!!!!");
                new_line(1);
                remove(tmp_file);
                attempt=0;
                goto_menu();
            }
            else
            {
                filew_wtr=fopen(txn_file,txn_file_mode_append);
                state=1;
                attempt=0;
                info.balance=info.balance-amt;
                fprintf(filew_1_wtr,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
                fprintf(filew_wtr,"Withdraw       %d\t%s\t%.2f\t%s\t%s",info.acount_no,info.name,amt,info.password,ctime(&t));
                new_line(2);
                printf("\t\t\t\t%.2f Has been withdrawn from Account No: %d",amt,info.acount_no);
                new_line(2);
                fclose(filew_wtr);
            }
        }
        else
        {
            fprintf(filew_1_wtr,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
        }
    }
    if(state)
    {
        fclose(filer_wtr);
        fclose(filew_1_wtr);
        remove(main_file);
        rename(tmp_file,main_file);
        new_line(1);
        attempt=0;
        goto_menu();
    }
    else if(attempt < 2)
    {
        printf("\t\t\t\tYou have entered wrong info!!!!!");
        fclose(filer_wtr);
        fclose(filew_1_wtr);
        remove(tmp_file);
        new_line(1);
        attempt++;
        new_line(2);
        wait(2000);
        show_msg("Reloading section..........",550);
        new_line(2);
        withdraw_money();
    }
    else
    {
        printf("\t\t\t\tYou have entered maximum amount of time!!!!!");
        fclose(filer_wtr);
        fclose(filew_1_wtr);
        remove(tmp_file);
        new_line(1);
        attempt=0;
        goto_menu();
    }


}
void deposit_money()
{
    clear_scr();
    new_line(1);
    line_start();
    show_msg("Deposit Money !!!",100);
    new_line(2);
    line_end();
    new_line(1);
    acc info;
    FILE *filer_dpr;
    FILE *filew_dpr;
    FILE *filew_1_dpr;
    int state=0;
    int tmp_acc;
    float amt;
    char tmp_pwd[100];
    state=0;
    filer_dpr=fopen(main_file,main_file_mode_read);
    filew_1_dpr=fopen(tmp_file,tmp_file_append);
    printf("\t\t\t\t Please enter your account no: ");
    scanf("%d",&tmp_acc);
    printf("\t\t\t\t Please enter your password: ");
    scanf(" %s",tmp_pwd);
    while(fscanf(filer_dpr,"%d\t%[^\t]%*c\t%s\t%s\t%s\t%[^\t]%*c\t%f\n",&info.acount_no,info.name,info.email,info.phone,info.password,info.address,&info.balance)!= EOF)
    {
        if((info.acount_no == tmp_acc) && (strcmp(info.password,tmp_pwd)==0))
        {
            time_t t;
            time(&t);
            clear_scr();
            new_line(2);
            printf("\t\t\t Welcome %s !!!",info.name);
            new_line(1);
            printf("\t\t\t Your current account balance = %.2f",info.balance);
            new_line(3);
            printf("\t\t\t\t Enter Amount: ");
            scanf("%f",&amt);
            if(amt < 0 )
            {
                fclose(filew_1_dpr);
                fclose(filer_dpr);
                printf("\t\t\tYou Have entered negative number!!!!!");
                new_line(1);
                remove(tmp_file);
                attempt=0;
                goto_menu();
            }
            else
            {
                filew_dpr=fopen(txn_file,txn_file_mode_append);
                state=1;
                info.balance=info.balance + amt;
                fprintf(filew_1_dpr,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
                fprintf(filew_dpr,"Deposit        %d\t%s\t%.2f\t%s\t%s",info.acount_no,info.name,amt,info.password,ctime(&t));
                new_line(2);
                printf("\t\t\t%.2f Has been deposited to Account No: %d",amt,info.acount_no);
                new_line(2);
                fclose(filew_dpr);
                attempt=0;
            }

        }
        else
        {
            fprintf(filew_1_dpr,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
        }
    }
    if(state)
    {
        fclose(filer_dpr);
        fclose(filew_1_dpr);
        remove(main_file);
        rename(tmp_file,main_file);
        new_line(1);
        attempt=0;
        goto_menu();
    }
    else if(attempt < 2)
    {
        printf("\t\t\t\tYou have entered wrong info!!!!!");
        fclose(filer_dpr);
        fclose(filew_1_dpr);
        remove(tmp_file);
        new_line(1);
        attempt++;
        new_line(2);
        wait(2000);
        show_msg("Reloading section..........",550);
        new_line(2);
        deposit_money();
    }
    else
    {
        printf("\t\t\t\tYou have entered maximum amount of time!!!!!");
        fclose(filer_dpr);
        fclose(filew_1_dpr);
        remove(tmp_file);
        new_line(1);
        attempt=0;
        goto_menu();
    }
}
void show_statement()
{
    clear_scr();
    new_line(1);
    line_start();
    show_msg("!!!Statement!!!",100);
    new_line(2);
    line_end();
    new_line(1);
    stmt txn;
    FILE *filer_stmt;
    int state=0,count=0;
    int tmp_acc;
    char tmp_pwd[100];
goback_account:
    filer_stmt=fopen(txn_file,txn_file_mode_read);
    printf("\t\t\t\t Please enter your account no: ");
    scanf("%d",&tmp_acc);
    printf("\t\t\t\t Please enter your password: ");
    scanf(" %s",tmp_pwd);
    while(fscanf(filer_stmt,"%s        %d\t%[^\t]%*c\t%f\t%s\t%[^\n]%*c\n",txn.type,&txn.account,txn.name,&txn.amt,txn.password,txn.date_time)!= EOF)
    {
        if((txn.account == tmp_acc) && (strcmp(txn.password,tmp_pwd)==0))
        {
            state=1;

            //line_start();
            new_line(1);
            printf("\t\t\t\t Type: %s",txn.type);
            new_line(1);
            printf("\t\t\t\t Account No: %d",txn.account);
            new_line(1);
            printf("\t\t\t\t Amount: %.2f",txn.amt);
            new_line(1);
            printf("\t\t\t\t Date & Time: %s",txn.date_time);
            new_line(2);

        }
    }
    count++;
    if(!state)
    {
        fclose(filer_stmt);
        if(count > 2)
        {
            printf("\t\t\t\t You have tried maximum amount of times!!");
            new_line(2);
            goto_menu();
        }
        else
        {
            new_line(2);
            printf("\t\t\t\t You have entered wrong info!!!!");
            new_line(2);
            goto goback_account;
        }

    }
    else
    {
        fclose(filer_stmt);
        new_line(2);
        goto_menu();
    }
}
void delete_account()
{
    clear_scr();
    line_start();
    show_msg("!!!Delete Your Account!!!",100);
    new_line(1);
    line_end();
    new_line(2);
    acc info;
    FILE *filer_dlt;
    FILE *filew_dlt;
    int state;
    int tmp_acc,op;
    char tmp_pwd[9];
    state=0;
    filer_dlt=fopen(main_file,main_file_mode_read);
    filew_dlt=fopen(tmp_file,tmp_file_append);
    printf("\t\t\t\t Please enter your account no: ");
    scanf("%d",&tmp_acc);
    printf("\t\t\t\t Please enter your password: ");
    scanf(" %[^\n]%*c",tmp_pwd);
    while(fscanf(filer_dlt,"%d\t%[^\t]%*c\t%s\t%s\t%s\t%[^\t]%*c\t%f\n",&info.acount_no,info.name,info.email,info.phone,info.password,info.address,&info.balance)!= EOF)
    {
        if((info.acount_no == tmp_acc) && (strcmp(info.password,tmp_pwd)==0))
        {
            clear_scr();
            new_line(2);
            printf("\t\t\t Welcome %s !!!",info.name);
            new_line(3);
            printf("\t\t\tAre you sure you want to delete your account ==>\n\n");
            printf("\t\t\t[1]YES\n\n");
            printf("\t\t\t[2]NO\n\n");
            printf("\t\t\tPlease Enter your choice [1/2]: ");
check_op:
            scanf("%d",&op);
            switch (op)
            {
            case 1:
                new_line(2);
                printf("\t\t\t\t Account deleted!!!!!");
                new_line(2);
                state=1;
                attempt=0;
                break;
            case 2:
                new_line(2);
                printf("\t\t\t\t Ok ! Will be happy to see you again!!!!!");
                new_line(2);
                fprintf(filew_dlt,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
                state=1;
                attempt=0;
                break;
            default:
                printf("\t\t\tPlease Enter in the range [1-2]:");
                goto check_op;
                break;
            }
        }
        else
        {
            fprintf(filew_dlt,"%d\t%s\t%s\t%s\t%s\t%s\t%.2f\n",info.acount_no,info.name,info.email,info.phone,info.password,info.address,info.balance);
        }
    }
    if(state)
    {
        fclose(filer_dlt);
        fclose(filew_dlt);
        remove(main_file);
        rename(tmp_file,main_file);
        new_line(1);
        attempt=0;
        goto_menu();
    }
    else if(attempt < 2)
    {
        printf("\t\t\t\tYou have entered wrong info!!!!!");
        fclose(filer_dlt);
        fclose(filew_dlt);
        remove(tmp_file);
        new_line(1);
        attempt++;
        new_line(2);
        wait(2000);
        show_msg("Reloading section..........",550);
        new_line(2);
        delete_account();
    }
    else
    {
        printf("\t\t\t\tYou have entered maximum amount of time!!!!!");
        fclose(filer_dlt);
        fclose(filew_dlt);
        remove(tmp_file);
        new_line(1);
        attempt=0;
        goto_menu();
    }


}
void menu()
{
    clear_scr();
    welcome_message();
    new_line(2);
    printf("\t\t[1] Create Account\n\n");
    printf("\t\t[2] Show Existing Account (For Manager)\n\n");
    printf("\t\t[3] Update Existing Account\n\n");
    printf("\t\t[4] Deposit Money\n\n");
    printf("\t\t[5] Withdraw Money\n\n");
    printf("\t\t[6] Show Statement\n\n");
    printf("\t\t[7] Delete Account\n\n");
}
void option_select()
{
    int op;
    printf("\tEnter number[1-7] to get started or enter 0 to exit ");
check_op_again:
    scanf("%d", &op);
    {
        switch (op)
        {
        case 1:
            create_account();
            break;
        case 2:
            show_accounts();
            break;
        case 3:
            update_account();
            break;
        case 4:
            deposit_money();
            break;
        case 5:

            withdraw_money();
            break;
        case 6:
            show_statement();
            break;
        case 7:
            delete_account();
            break;
        case 0:
            exit_func();
            break;
        default:
            printf("\t\t\t\tPlease Enter any digit from 0 to 7:");
            goto check_op_again;
        }
    }
}
void goto_menu()
{
    int op;
    printf("\t\t\t\t Enter 1 to go to or main menu or  0 to exit ");
check_op_again:
    scanf("%d", &op);
    {
        switch (op)
        {
        case 1:
            menu();
            option_select();
            break;
        case 0:
            exit_func();
            break;
        default:
            printf("\t\t\t\tPlease Enter 1 or 0:");
            goto check_op_again;
        }
    }
}
void check_file()
{
    if(!os)
    {
        FILE *filecheck;
        filecheck=fopen(main_file,main_file_mode_read);
        if(filecheck==NULL)
        {
            filecheck=fopen(main_file,main_file_mode_write);
            fclose(filecheck);
        }
        else
        {
            fclose(filecheck);
        }
    }
}
void exit_func()
{
    clear_scr();
    show_msg("Good Bye Form Bank management system!!!!",250);
    new_line(2);
    printf("\t\t\t\t Team members =>");
    new_line(1);
    printf("\t\t\t\t MD. ABIR HOSSAIN (2233233642)");
    new_line(1);
    printf("\t\t\t\t MD. SOFWAN ISLAM (2231769642)");
    new_line(1);
    printf("\t\t\t\t MD. MEHEDI HASAN (2233674642)");
    new_line(2);
    exit(1);
}
