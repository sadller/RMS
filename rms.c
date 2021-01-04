//user_detail (binary)
//job_detail (binary)
//admin_msg_box (text)

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>

void gotoxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int option(int x,int y,int n,int wid=1)
{
    char ch,optn=1;
    gotoxy(x,y);
    printf("%c",16);
    while(1)
    {
	ch=getch();
	if(ch==NULL)
	    ch=getch();
	gotoxy(x,y);
	printf(" ");
	switch(ch)
	{
	    case 72:
		    if(optn>1)
		    {
			optn--;
			y-=wid;
		    }
		    break;
	    case 80:
		    if(optn<n)
		    {
			optn++;
			y+=wid;
		    }
		    break;
	    case 13:
		    return optn;
	    case 27:
		    return -1;
        case 8:
            return 0;
	}
	gotoxy(x,y);
	printf("%c",16);
    }
}

char* val_check(char* value,char* type)
{
    int i;
    gotoxy(1,20);   printf("                                                      ");
    gotoxy(1,20);
    if(strcmp(type,"name")==0)
    {
        if(strlen(value)>18)
            return "too long";
        else if(strlen(value)==0)
            return "can't null";
        for(i=0;value[i]!='\0';i++)
        {
            if(value[i]==' ')
                return "space not allowed";
            else if(!isalpha(value[i]))
                return "only alphabet allowed";
        }
        return " ";
    }

    if(strcmp(type,"pass")==0)
    {
        if(strlen(value)>10)
            return "too long (Max 10 chars)";
        else if(strlen(value)<6)
            return "should be more than 6 chars";
        for(i=0;value[i]!='\0';i++)
        {
            if(value[i]==' ')
                return "space not allowed";
        }
        return " ";
    }

    if(strcmp(type,"mob")==0)
    {
        if(strlen(value)!=10)
            return "Mob. no. should have 10 digits";
        for(i=0;value[i]!='\0';i++)
        {
            if(value[i]==' ')
                return "space not allowed";
            else if(!isdigit(value[i]))
                return "only digits allowed";
        }
        return " ";
    }

    if(strcmp(type,"mail")==0)
    {
        int found=0;
        for(i=0;value[i]!='\0';i++)
        {
            if(value[i]=='@')
                found++;
        }
        if(found!=1)
            return "inappropriate format";
        return " ";
    }

    if(strcmp(type,"add")==0)
    {
        if(strlen(value)==0)
            return "can't null";
        for(i=0;value[i]!='\0';i++)
        {
            if(!isalpha(value[i]) && !isdigit(value[i]) && value[i]!=' ' && value[i]!=',' && value[i]!='.' && value[i]!='/' && value[i]!='-')
                return "special symbol not allowed";
        }
        return " ";
    }
}


void start_page();
void home_page();
void admin_login();
void admin_home();
void post_jobs();
void show_jobs();
void show_user_details();
void show_all_user();
void show_id_user();
void a_notification();
void shortlist();
void profile_cmp(char*);

void user_page();
void user_signup();
int  assign_id();
void save_user(struct user*);
void user_login();
void user_home(struct user*);
void view_profile(struct user*);
void updt_profile(struct user*);
void updt_record(struct user*);
int  if_updated(struct user*);
void apply_job(struct user*);
void u_notification(struct user*);
void profile_print(struct user*);

void autobackup();

struct date
{
    int day,month,year;
};
struct job
 {
   char name[20];
   int vacancy;
   float salary;
   char desc[200];
 };
struct user
{
    char f_name[20];
    char l_name[20];
    int id ;
    char sex;
    char add[100];
    char mob[11];
    char mail[30];
    char pass[10];
    char msg[200];
    char app_job[3][20];
    struct date dob;
    int  notify;
    struct academic
    {
        float per_10,per_12,per_gd;
        char  clg_10[40],clg_12[40],clg_gd[40];
        char  degree[10];
    }a;
};


int main()
{
 start_page();
 autobackup();
 system("cls");
 home_page();
 system("cls");
 return 0;
}

void start_page()
{
    system("cls");
    system("color 0A");
    int i;
    char temp,line[]="  RAJAT AGRAWAL 69   MCA   SUMIT PANDEY 70    RECRUITMENT MANAGEMENT SYSTEM  PROJECT  ";
    gotoxy(1,1);   printf("______________________________________________________________________________");
    gotoxy(35,5);   printf("R M S");
    gotoxy(22,7);   printf("Recruitment Management System");
    gotoxy(1,20);   printf("______________________________________________________________________________");
    gotoxy(1,22);   printf("______________________________________________________________________________");

    while(!kbhit())
    {
        i=0;
        temp=line[0];
        while(i<strlen(line)-1)
        {
            line[i]=line[i+1];
            i++;
        }
        line[i]=temp;
        gotoxy(3,21);   printf("%.75s",line);
        for(int j=0;j<30000;j++)
            for(int k=0;k<1000;k++);
    }

    getch();
}

//FIRST PAGE ON PROGRAM STARTUP
void home_page()
{
 system("cls");
 system("color 1B");
 gotoxy(30,5);		printf("ADMIN");
 gotoxy(30,6);		printf("USER");
 gotoxy(30,7);      printf("EXIT");
 do{
    switch(option(28,5,3))               //option() is defined in utility.c
    {
        case 1:
            admin_login();
            home_page();
            return;
        case 2:
            user_page();
            home_page();
            break;
        case 3:
            system("cls");
            exit(0);
    }
 }while(1);
}

//ASKS ADMINISTRATOR PASSWORD
void admin_login()
{
 char pin[5]="0297",str[5],ch;
 int i=0;
 system("cls");
 system("color E1");
 gotoxy(35,10);		printf("P I N");
 gotoxy(34,12);		printf("_ _ _ _");
 gotoxy(32,15);		printf("<ESC> BACK");
 while(i<4)
 {
   gotoxy(34+2*i,12);
   ch=getche();
   if(isdigit(ch))                 //ONLY DIGITS ALLOWED IN PIN
     str[i++]=ch;
   else if(ch==27)
     return;
 }
  str[i]='\0';
 if(strcmp(str,pin)==0)
   {
     system("cls");
     system("color BC");
     gotoxy(30,8); printf("Successfull Login");
     admin_home();
     return;
   }
   gotoxy(25,15);   printf("PASSWORD MISMATCH...EXITING");
   getch();
}

//OPTIONS FOR ADMIN
void admin_home()
{
  system("cls");
  system("color BC");
  gotoxy(30,10);	printf("POST JOBS");
  gotoxy(30,11);	printf("SHOW JOBS");
  gotoxy(30,12);	printf("USER DETAILS");
  gotoxy(30,13);    printf("MESSAGE BOX");
  gotoxy(30,14);    printf("SHORTLIST");
  gotoxy(30,15);    printf("LOGOUT");
 do{
     switch(option(28,10,6))
    {
        case 1:
            post_jobs();
            admin_home();
            return;
        case 2:
            show_jobs();
            admin_home();
            return ;
        case 3:
            show_user_details();
            admin_home();
            return;
        case 4:
            a_notification();
            admin_home();
            return;
        case 5:
            shortlist();
            admin_home();
            return;
        case 6:
            return;
    }
 }while(1);
}

//POST JOB DESCRIPTION FOR USER
void post_jobs()
{
 struct job post,p;
 system("cls");
 system("color 70");
 printf("POST NAME : ");
 gets(post.name);
 printf("VACANCY   : ");
 scanf("%d",&post.vacancy);
 printf("SALARY    : ");
 scanf("%f",&post.salary);
 fflush(stdin);
 printf("DESCRIPTION : ");
 gets(post.desc);
 printf("PRESS ENTER TO POST THIS JOB");
 char ch=getch();
 if(ch!=13)
    return;
 FILE *fp;
 fp=fopen("job_detail","rb");
 while(fread(&p,sizeof(p),1,fp)==1)
     if(strcmp(p.name,post.name)==0)
     {
         printf("\nPOST ALREADY EXITS WITH THIS NAME...");
         getch();
         fclose(fp);
         return;
     }
 fclose(fp);
 fp=fopen("job_detail","ab");
 fwrite(&post,sizeof(post),1,fp);
 fclose(fp);
}

void show_jobs()
{
    struct job post;
    system("cls");
    system("color 1A");
    FILE *fp;
    fp=fopen("job_detail","rb");
    while(fread(&post,sizeof(post),1,fp)==1)
    {
        printf("\n________________________________________________________________________");
        printf("\nPOST NAME : %s",post.name);
        printf("\nVACANCY : %d\t\tSALARY : %.2f",post.vacancy,post.salary);
        printf("\nDESCRIPTION : %s",post.desc);
    }
    fclose(fp);
    getch();
}

//DISPLAY USER DETAILS
void show_user_details()
{
    system("cls");
    system("color 60");
    gotoxy(10,5);   printf("SHOW ALL");
    gotoxy(10,6);   printf("SHOW USER BY ID");
    switch(option(8,5,2))
    {
        case 1:
            show_all_user();
            return;
        case 2:
            show_id_user();
            return;
        case 0:
            return;
    }
}

void show_all_user()
{
    system("cls");
    system("color 1C");
    gotoxy(30,1);   printf("ALL USER DETAILS");
    struct user u;
    FILE *fp;
    fp=fopen("user_detail","rb");
    while(fread(&u,sizeof(u),1,fp)==1)
    {
        view_profile(&u);
    }
    fclose(fp);
    getch();
}

void show_id_user()
{
    system("cls");
    system("color 1C");
    int id,found=0;
    gotoxy(5,5);    printf("ENTER USER ID : ");
    scanf("%d",&id);

    struct user u;
    FILE *fp;
    fp=fopen("user_detail","rb");
    while(fread(&u,sizeof(u),1,fp)==1)
    {
        if(id==u.id)
        {
            view_profile(&u);
            found=1;
        }
    }
    fclose(fp);
    if(!found)
    {gotoxy(5,7); printf("NO USER FOUND WITH THIS ID");}
    getch();
}

//FOR COMMUNICATION B/W ADMIN AND USER
void a_notification()
{
    FILE *fp;
    char str[100];
    system("cls");
    system("color 1A");
    if((fp=fopen("admin_msg_box","r"))==NULL)
    {
        printf("NO MESSAGES HERE...");
        getch();
        return;
    }
    while(fgets(str,99,fp)!=NULL)
    {
        printf("%s",str);
    }
    fclose(fp);
    getch();
}

void shortlist()
{
    system("cls");
    system("color 1C");
    int col=5,tot_job=0,choice;
    struct job post;
    struct user u;
    FILE *fp;
    fp=fopen("job_detail","rb");
    while(fread(&post,sizeof(post),1,fp)==1)
    {
         gotoxy(5,col++);    printf("%s",post.name);
         tot_job++;
    }
    choice=option(3,5,tot_job);
    if(choice>0)
    {
        rewind(fp);
        fseek(fp,sizeof(post)*(choice-1),0);
        fread(&post,sizeof(post),1,fp);
        profile_cmp(post.name);
    }
    fclose(fp);
}

void profile_cmp(char *post_name)
{
    system("cls");
    int tot=0,i;
    struct user u;
    FILE *fp;
    fp=fopen("user_detail","rb");
    while(fread(&u,sizeof(u),1,fp)==1)
    {
        for(i=0;i<3;i++)
            if(strcmp(u.app_job[i],post_name)==0)
            {
                view_profile(&u);
                tot++;
                break;
            }
    }
    fclose(fp);
    if(tot==0)
        {printf("NO USER APPLIED FOR THIS JOB"); getch(); return;}
    int choice=option(1,1,tot,16),ch=0;
    fp=fopen("user_detail","rb");
    gotoxy(3,2);
    while(fread(&u,sizeof(u),1,fp)==1)
    {
        for(i=0;i<3;i++)
            if(strcmp(u.app_job[i],post_name)==0)
            {
                ch++;
                break;
            }
        if(ch==choice)
        {
            fclose(fp);
            u.notify++;
            strcat(u.msg,"\nYou are selected for interview for the post ");
            strcat(u.msg,post_name);
            strcpy(u.app_job[i],"selected");
            updt_record(&u);
            break;
        }
    }
    fclose(fp);
}


//**************************************************************************

//USER SIGNUP AND LOGIN
void user_page()
{
  system("cls");
  system("color 1B");
  gotoxy(34,5);		printf("SIGNUP");
  gotoxy(34,6);		printf("LOGIN");
  gotoxy(34,7);     printf("BACK");
  switch(option(32,5,3))
  {
   case 1:
	  user_signup();
	  user_page();
	  return;
   case 2:
	  user_login();
	  user_page();
	  return;
   case 3:
        return;
  }
}








void user_signup()
{
    system("cls");
    system("color 79");
    user u;
    char err_msg[30];
    gotoxy(30,2);   printf("USER SIGNUP");
    u.id=assign_id()+1000;
    gotoxy(5,4);    printf("USER ID : %d\t[PLEASE REMEMBER THE USER ID]",u.id);
    gotoxy(5,6);    printf("FIRST NAME : ");
    do{
        gotoxy(18,6);   printf("                                          ");
        gotoxy(18,6);   gets(u.f_name);
        strupr(u.f_name);
        if(printf("%s",val_check(u.f_name,"name"))==1)   break;
    }while(1);

    gotoxy(5,7);    printf("LAST  NAME : ");
    do{
        gotoxy(18,7);   printf("                                          ");
        gotoxy(18,7);   gets(u.l_name);
        strupr(u.l_name);
        if(printf("%s",val_check(u.l_name,"name"))==1)   break;
    }while(1);

    gotoxy(5,8);    printf("GENDER(M/F): ");
    do{
       u.sex=getche();
       if(u.sex=='m'||u.sex=='M'||u.sex=='f'||u.sex=='F')
        break;
       printf("\b \b");
    }while(1);
    u.sex=toupper(u.sex);

    gotoxy(5,9);    printf("E-MAIL     : ");
    do{
        gotoxy(18,9);   printf("                                          ");
        gotoxy(18,9);   gets(u.mail);
        if(printf("%s",val_check(u.mail,"mail"))==1)   break;
    }while(1);

    gotoxy(5,10);    printf("MOBILE NO. : ");
    do{
        gotoxy(18,10);   printf("                                          ");
        gotoxy(18,10);   gets(u.mob);
        strupr(u.mob);
        if(printf("%s",val_check(u.mob,"mob"))==1)   break;
    }while(1);

    strcpy(u.app_job[0],"\0");
    strcpy(u.app_job[1],"\0");
    strcpy(u.app_job[2],"\0");
    u.a.per_10=u.a.per_12=u.a.per_gd=0.0L;
    u.dob.day=u.dob.month=u.dob.year=0;
    strcpy(u.add,"\0");
    strcpy(u.a.clg_10,"\0");
    strcpy(u.a.clg_12,"\0");
    strcpy(u.a.clg_gd,"\0");
    strcpy(u.a.degree,"\0");
    strcpy(u.msg,"\0");
    u.notify=0;

    gotoxy(5,12);   printf("PASSWORD         : ");
    do{
        gotoxy(24,12);   printf("                                          ");
        gotoxy(24,12);   gets(u.pass);
        if(printf("%s",val_check(u.pass,"pass"))==1)   break;
    }while(1);

    gotoxy(5,13);   printf("CONFIRM PASSWORD : ");
    do{
        char con_pass[20];
        do{
            gotoxy(24,13);   printf("                                          ");
            gotoxy(24,13);   gets(con_pass);
            if(printf("%s",val_check(con_pass,"pass"))==1)   break;
        }while(1);

        if(strcmp(con_pass,u.pass)==0)
            break;
        gotoxy(1,20);   printf("                                                      ");
        gotoxy(1,20);   printf("Password mismatch");
    }while(1);

    save_user(&u);
    system("cls");
    gotoxy(25,5);
    printf("USER SUCCESSFULLY REGISTERED");
    gotoxy(25,7);
    printf("Press any key to continue...");
    getch();
}

int assign_id()
{
    struct user u;
    int i=0;
    FILE *fp;
    if((fp=fopen("user_detail","rb+"))==NULL)
    {
        fp=fopen("user_detail","wb");
        fclose(fp);
        fp=fopen("user_detail","rb+");
    }
    while(fread(&u,sizeof(u),1,fp)==1)
        i++;
    fclose(fp);
    return i;
}

void save_user(struct user *u)
{
    FILE *fp;
    system("cls");

    if((fp=fopen("user_detail","ab+"))==NULL)
    {
        fp=fopen("user_detail","wb");
    }
    fwrite(u,sizeof(*u),1,fp);
    fclose(fp);
}

void user_login()
{
    struct user u;
    int id,found=0;
    char pass[15];
    FILE *fp;
    if((fp=fopen("user_detail","rb+"))==NULL)
    {
        system("cls");
        gotoxy(30,5);
        printf("#FILE MISSING...");
        getch();
        return;
    }
    system("cls");
    system("color 1A");
    gotoxy(34,5);   printf("ID : ");
    gotoxy(30,6);   printf("PASSWORD : ");
    gotoxy(39,5);   scanf("%d",&id);
    fflush(stdin);
    gotoxy(40,6);   gets(pass);

    while(fread(&u,sizeof(u),1,fp)==1)
    {
        if(id==u.id && strcmp(pass,u.pass)==0)
            {
                fclose(fp);
                user_home(&u);
                return;
            }
    }
    fclose(fp);
    gotoxy(30,10);      printf("NO USER FOUND...");
    getch();
}

void user_home(struct user *u)
{
    system("cls");
    system("color BC");
    gotoxy(34,5);   printf("VIEW PROFILE");
    gotoxy(34,6);   printf("UPDATE PROFILE");
    gotoxy(34,7);   printf("PRINT PROFILE");
    if(u->notify>0)
        {gotoxy(34,8);   printf("NOTIFICATION (%d)",u->notify);}
    else
        {gotoxy(34,8);   printf("NOTIFICATION");}
    gotoxy(34,9);   printf("APPLY JOB");
    gotoxy(34,10);   printf("LOGOUT");

    do{
        switch(option(32,5,6))
        {
            case 1:
                system("cls");
                system("color 1E");
                view_profile(u);
                getch();
                user_home(u);
                return ;
            case 2:
                updt_profile(u);
                user_home(u);
                return;
            case 3:
                profile_print(u);
                user_home(u);
                return;
            case 4:
                u_notification(u);
                user_home(u);
                return;
            case 5:
                apply_job(u);
                user_home(u);
                return;
            case 6:
                return;
        }
    }while(1);
}

void view_profile(struct user *u)
{
    //printf("\n______________________________________________________________________________");
    printf("\n\t   USER ID    : %d",u->id);
    printf("\n\t   FIRST NAME : %s",u->f_name);
    printf("\n\t   LAST  NAME : %s",u->l_name);
    printf("\n\t   GENDER     : %c",u->sex);
    printf("\n\t   MOBILE     : %s",u->mob);
    printf("\n\t   E-MAIL     : %s",u->mail);
    if(u->dob.day>0)
        printf("\n\t   BIRTH DATE : %d/%d/%d",u->dob.day,u->dob.month,u->dob.year);
    if(strlen(u->add)>0)
        printf("\n\t   ADDRESS    : %.50s",u->add);
    if(u->a.per_10>0)
    {
        printf("\n\t   HIGHSCHOOL % : %.2f",u->a.per_10);
        if(strlen(u->a.clg_10)>0)
            printf("\n\t   FROM : %.50s",u->a.clg_10);
    }
    if(u->a.per_12>0)
    {
        printf("\n\t   INTERMEDIATE% : %.2f",u->a.per_12);
        if(strlen(u->a.clg_12)>0)
            printf("\n\t   FROM : %.50s",u->a.clg_12);
    }
    if(u->a.per_gd>0)
    {
        printf("\n\t   GRADUATION %  : %.2f",u->a.per_gd);
        if(strlen(u->a.clg_gd)>0)
            printf("\n\t   FROM : %.50s",u->a.clg_gd);
    }

    if(strlen(u->a.degree)>0)
        printf("\n\t   DEGREE : %s",u->a.degree);
    printf("\n ");
   int i;
   for(i=1;i<78;i++)
        printf("%c",220);
}

void updt_profile(struct user *u)
{
    int i=1;
    system("cls");
    system("color 1C");
                    printf("\n_______________________________________________________________________________");
    gotoxy(5,3);    printf("USER ID    : %d",u->id);
    gotoxy(5,4);    printf("FIRST NAME : %s",u->f_name);
    gotoxy(5,5);    printf("LAST  NAME : %s",u->l_name);
    gotoxy(5,6);    printf("GENDER     : %c",u->sex);
    gotoxy(5,7);    printf("MOBILE     : %s",u->mob);
    gotoxy(5,8);    printf("E-MAIL     : %s",u->mail);
    gotoxy(5,9);    printf("ADDRESS    : %s",u->add);
    gotoxy(5,10);   printf("BIRTH DATE : %d/%d/%d",u->dob.day,u->dob.month,u->dob.year);
    gotoxy(5,11);   printf("HIGHSCOOL %c   : %.2f",37,u->a.per_10);
    gotoxy(5,12);   printf("FROM : %s",u->a.clg_10);
    gotoxy(5,13);   printf("INTERMEDIATE %c: %.2f",37,u->a.per_12);
    gotoxy(5,14);   printf("FROM : %s",u->a.clg_12);
    gotoxy(5,15);   printf("GRADUATION %c  : %.2f",37,u->a.per_gd);
    gotoxy(5,16);   printf("FROM : %s",u->a.clg_gd);
    gotoxy(5,17);   printf("DEGREE : %s",u->a.degree);
                    printf("\n________________________________________________________________________________");
    while(1)
    {
         switch(option(3,3,15))
         {
            case 1:
            case 2:
            case 3:
            case 4:
                    gotoxy(5,19);   printf("Sorry...this can not be changed!!!");
                    break;
            case 5:
                    do{
                        gotoxy(18,7);   printf("                                          ");
                        gotoxy(18,7);   gets(u->mob);
                        if(printf("%s",val_check(u->mob,"mob"))==1)    break;
                    }while(1);
                    break;
            case 6:
                    do{
                        gotoxy(18,8);   printf("                                          ");
                        gotoxy(18,8);   gets(u->mail);
                        if(printf("%s",val_check(u->mail,"mail"))==1)   break;
                    }while(1);
                    break;
            case 7:
                    do{
                        gotoxy(18,9);   printf("                                                            ");
                        gotoxy(18,9);   gets(u->add);
                        if(printf("%s",val_check(u->add,"add"))==1)    break;
                    }while(1);
                    break;
            case 8:
                    gotoxy(18,10);  printf("                          ");
                    do{
                            gotoxy(18,10);  printf("  ");
                            gotoxy(18,10);  scanf("%d",&u->dob.day);
                            gotoxy(20,10);  printf("/");
                    }while(u->dob.day<1 || u->dob.day>31);
                    do{
                            gotoxy(21,10);  printf("  ");
                            gotoxy(21,10);  scanf("%d",&u->dob.month);
                            gotoxy(23,10);  printf("/");
                            if(u->dob.month<1 || u->dob.month>12)
                                continue;
                            if((u->dob.day==28 || u->dob.day==29)&&(u->dob.month==2))
                                break;
                            else if((u->dob.day==30)&&(u->dob.month==4 || u->dob.month==6 || u->dob.month==9 || u->dob.month==11))
                                    break;
                            else if(u->dob.month==1 || u->dob.month==2 || u->dob.month==3 || u->dob.month==5 || u->dob.month==7||u->dob.month==8||u->dob.month==10||u->dob.month==12)
                                    break;
                    }while(1);
                    gotoxy(24,10);  scanf("%d",&u->dob.year);
                    break;
            case 9:
                    do{
                        gotoxy(21,11);    printf("               ");
                        gotoxy(21,11);    scanf("%f",&u->a.per_10);
                    }while(u->a.per_10<0.0 || u->a.per_10>100.0);
                    break;
            case 10:
                    do{
                        gotoxy(12,12);    printf("                                                    ");
                        gotoxy(12,12);   gets(u->a.clg_10);
                        if((printf("%s",val_check(u->a.clg_10,"add")))==1)           break;
                    }while(1);
                    break;
            case 11:
                    do{
                        gotoxy(21,13);    printf("         ");
                        gotoxy(21,13);    scanf("%f",&u->a.per_12);
                    }while(u->a.per_12<0.0 || u->a.per_12>100.0);
                    break;
            case 12:
                    do{
                        gotoxy(12,14);    printf("                                                    ");
                        gotoxy(12,14);   gets(u->a.clg_12);
                        if((printf("%s",val_check(u->a.clg_12,"add")))==1)           break;
                    }while(1);
                    break;
            case 13:
                    do{
                        gotoxy(21,15);    printf("         ");
                        gotoxy(21,15);    scanf("%f",&u->a.per_gd);
                    }while(u->a.per_gd<0.0 || u->a.per_gd>100.0);
                    break;
            case 14:
                    do{
                        gotoxy(12,16);    printf("                                                    ");
                        gotoxy(12,16);   gets(u->a.clg_gd);
                        if((printf("%s",val_check(u->a.clg_gd,"add")))==1)           break;
                    }while(1);
                    break;
            case 15:
                    do{
                        gotoxy(14,17);    printf("                               ");
                        gotoxy(14,17);    gets(u->a.degree);
                    }while(strlen(u->a.degree)<=0);
                    break;
            case 0:
                    updt_record(u);
                    return;
         }
    }
}


void updt_record(struct user *u)
{
    struct user u1;
    FILE *fp,*fp1;
    fp=fopen("user_detail","rb");
    fp1=fopen("temp","wb");
    while(fread(&u1,sizeof(u1),1,fp)==1)
    {
        if(u1.id==u->id)
            fwrite(u,sizeof(*u),1,fp1);
        else
            fwrite(&u1,sizeof(u1),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    remove("user_detail");
    rename("temp","user_detail");
}

int if_updated(struct user *u)
{
    int check=0;
    if(strlen(u->add)>0)
        check+=1;
    if(strlen(u->a.clg_10)>0)
        check+=1;
    if(strlen(u->a.clg_12)>0)
        check+=1;
    if(strlen(u->a.clg_gd)>0)
        check+=1;
    if(strlen(u->a.degree)>0)
        check+=1;
    if(u->a.per_10>0)
        check+=1;
    if(u->a.per_12>0)
        check+=1;
    if(u->a.per_gd>0)
        check+=1;
    if(u->dob.day>0)
        check+=1;
    return check;
}

void u_notification(struct user *u)
{
    system("cls");
    system("color 1A");
    puts(u->msg);
    u->notify=0;
    updt_record(u);
    getch();
}

void apply_job(struct user *u)
{
    system("cls");
    system("color 1E");
    int i,can_apply=0;
    if(if_updated(u)<9)
    {
        printf("YOU HAVE TO FIRST UPDATE YOUR PROFILE TO APPLY FOR ANY JOB");
        getch();
        return;
    }

    for(i=0;i<3;i++)
        if(strlen(u->app_job[i])==0)
            {can_apply=1; break;}
     if(!can_apply)
     {
         printf("Sorry..you can not apply for more than three jobs");
         getch();
         return;
     }

    struct job post;
    char str[100];
    int j=4,tot_job=0;
    FILE *fp,*np;
    fp=fopen("job_detail","rb");
    np=fopen("admin_msg_box","a");
    while(fread(&post,sizeof(post),1,fp)==1)
    {
        tot_job++;
        gotoxy(5,j++);    printf("POST NAME   : %s",post.name);
        gotoxy(5,j++);    printf("SALARY      : %.2f",post.salary);
        gotoxy(5,j++);    printf("VACANCY     : %d",post.vacancy);
        gotoxy(5,j++);    printf("DESCRIPTION : %.50s",post.desc);
        gotoxy(3,j++);    printf("________________________________________________________");
    }
    int choice=option(3,4,tot_job,5);

    if(choice>0)
    {
       rewind(fp);
       fseek(fp,sizeof(post)*(choice-1),0);
       fread(&post,sizeof(post),1,fp);

       for(int k=0;k<=i;k++)
       {
            if(strcmp(post.name,u->app_job[k])==0)
            {
                system("cls");
                printf("Sorry...you already applied for this post");
                getch();
                return;
            }
        }
        strcpy(u->app_job[i],post.name);
        fprintf(np,"\nUSER ID : %d\tNAME : %s %s\tapplied for the post %s",u->id,u->f_name,u->l_name,post.name);
    }
    fclose(fp);
    fclose(np);
    updt_record(u);
}

void autobackup()
{
    system("copy user_detail d:\RMS_backup /y");
    system("copy job_detail  d:\RMS_backup /y");
    system("copy admin_msg_box d:\RMS_backup /y");
}

void profile_print(struct user *u)
{
    FILE *fp;
    fp=fopen("profile.txt","w");
    fprintf(fp,"\n   USER ID    : %d",u->id);
    fprintf(fp,"\n   FIRST NAME : %s",u->f_name);
    fprintf(fp,"\n   LAST  NAME : %s",u->l_name);
    fprintf(fp,"\n   GENDER     : %c",u->sex);
    fprintf(fp,"\n   MOBILE     : %s",u->mob);
    fprintf(fp,"\n   E-MAIL     : %s",u->mail);
    if(u->dob.day>0)
        fprintf(fp,"\n   BIRTH DATE : %d/%d/%d",u->dob.day,u->dob.month,u->dob.year);
    if(strlen(u->add)>0)
        fprintf(fp,"\n   ADDRESS    : %.50s",u->add);
    if(u->a.per_10>0)
    {
        fprintf(fp,"\n   HIGHSCHOOL % : %.2f",u->a.per_10);
        if(strlen(u->a.clg_10)>0)
            fprintf(fp,"\n   FROM : %.50s",u->a.clg_10);
    }
    if(u->a.per_12>0)
    {
        fprintf(fp,"\n   INTERMEDIATE% : %.2f",u->a.per_12);
        if(strlen(u->a.clg_12)>0)
            fprintf(fp,"\n   FROM : %.50s",u->a.clg_12);
    }
    if(u->a.per_gd>0)
    {
        fprintf(fp,"\n   GRADUATION %  : %.2f",u->a.per_gd);
        if(strlen(u->a.clg_gd)>0)
            fprintf(fp,"\n   FROM : %.50s",u->a.clg_gd);
    }

    if(strlen(u->a.degree)>0)
        fprintf(fp,"\n   DEGREE : %s",u->a.degree);

    fclose(fp);
    system("cls");
    system("color 1B");
    int i;
    gotoxy(1,6);
    view_profile(u);
    gotoxy(1,5);
     for(i=1;i<78;i++)
        printf("%c",220);
    for(i=6;i<23;i++)
    {
        gotoxy(1,i);    printf("%c",221);
        gotoxy(77,i);   printf("%c",222);
    }

    gotoxy(30,3);   printf("PRESS \"CTRL+P\" TO PRINT");
    char ch;
    ch=getch();
    if(ch==NULL)
        ch=getch();
    gotoxy(26,25);
    if(ch==16)
        {system("print profile.txt"); remove("profile.txt"); getch();}
}
