#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>
#include<iomanip.h>
int size=0,c=0;
char logid[20],logp[20],logg[20];
class game
{
public:
char id[20];
char email[40];
char pass[20];
int tsc,id_ch;
game()
{
strcpy(id,"NIL   ");
tsc=0;
}};
void total();
game gamel(char a[])
{
game g;
ifstream f1;
f1.open("Gamer.dat",ios::binary);
f1.seekg(0);
while(f1.read((char*)&g,sizeof(g)))
{
if(strcmp(g.id,a)==0)
{
return g;
}}
return g;
}
void update(char a[],int sc,int check=0)
{
game g;
fstream f1,f2;
								f1.open("Gamer.dat",ios::binary|ios::in|ios::ate);
f2.open("Temp.dat",ios::binary|ios::in|ios::out);
f2.seekp(0);
f1.seekg(0);
while(f1.read((char*)&g,sizeof(g)))
{
if(strcmp(g.id,a)==0)
{
if(check==0)
{
g.tsc+=sc;
f2.write((char*)&g,sizeof(game));
}
else if(check==1)
{
g.id_ch+=sc;
f2.write((char*)&g,sizeof(game));
}}
else
f2.write((char*)&g,sizeof(game));
}
f1.close();
f2.close();
remove("Gamer.dat");
rename("Temp.dat","Gamer.dat");
}
void updatep(char a[],char p[],int check=0)
{
game g;
fstream f1,f2;
f1.open("Gamer.dat",ios::binary|ios::in|ios::ate);
f2.open("Temp.dat",ios::binary|ios::in|ios::out);
f2.seekp(0);
f1.seekg(0);
while(f1.read((char*)&g,sizeof(g)))
{
if(strcmp(g.id,a)==0)
{
if(check==0)
{
strcpy(g.pass,p);
f2.write((char*)&g,sizeof(game));
}
else if(check==1)
{
strcpy(g.email,p);
f2.write((char*)&g,sizeof(game));
}
else if(check==2)
{
strcpy(g.id,p);
f2.write((char*)&g,sizeof(game));
}}
else
f2.write((char*)&g,sizeof(game));
}
f1.close();
f2.close();
remove("Gamer.dat");
rename("Temp.dat","Gamer.dat");
}
void screen(char a[]);
void waste()
{
cout<<"\nSorry, if thats the case we can't help you.";
getch();
exit(0);
}
int check(char a[])
{
game g;
ifstream f;
f.open("Gamer.dat",ios::binary);
f.seekg(0);
while(f.read((char*)&g,sizeof(g)))
{
if(strcmp(g.id,a)==0)
{f.close();
return 1;
}}
f.close();
return 0;
}
char* checkp(char a[])
{
game g;
ifstream f;
f.open("Gamer.dat",ios::binary);
f.seekg(0);
while(f.read((char*)&g,sizeof(g)))
{
if(strcmp(g.id,a)==0)
{f.close();
return g.pass;
}}
f.close();
return NULL;
}
void fill(char a[])
{
int k=strlen(a);
if(k<10)
{
for(int i=k;i<10;i++)
a[i]=' ';
}
a[10]='\0';
}
void total()
{
ifstream f;
f.open("Gamer.dat",ios::binary);
f.seekg(0,ios::end);
size=f.tellg()/sizeof(game);
}
void login(int);
void create()
{
game g;
int epos,op,opt=0;
cout<<"Enter a gamer id (max 9 characters)\n";
gets(g.id);
if(strlen(g.id)>9)
create();
if(check(g.id)==1)
{
c=1;
login(1);
}
else
{
cout<<"\nNow enter your email address.\n";
ofstream f1;
f1.open("Gamer.dat",ios::binary|ios::app);
gets(g.email);
gwrong:
op=0;
if(opt==0)
opt++;
else
{
cout<<"\nEnter a valid email address.\n";
gets(g.email);
}
for(int i=0;i<strlen(g.email);i++)
{
if(g.email[i]=='@')
{
epos=i;
op++;
}}
if(op!=1||epos<=6)
goto gwrong;
for(i=0;i<strlen(g.email);i++)
{
if(i<epos)
if(!isalnum(g.email[i]))
goto gwrong;
else if(i==strlen(g.email)-4)
if(g.email[i]!='.')
goto gwrong;
}
int len,uc=0,lc=0,chc=0;
char fp[20];
op=0;
pwrong:
cout<<"\nEnter a strong password for your account(6 - 18 character , use uppercase, \nlowercase and special character ):\n";
gets(g.pass);
uc=0,lc=0,chc=0;
for(i=0;i<strlen(g.pass);i++)
{
if(isupper(g.pass[i]))
uc++;
else if(islower(g.pass[i]))
lc++;
else if(!isalpha(g.pass[i]))
chc++;
}
len=strlen(g.pass);
if(len>18||len<6||uc<1||lc<1||chc<1)
goto pwrong;
rep:
cout<<"\nRe enter the password for confirmation\n";
gets(fp);
if(strcmp(fp,g.pass)!=0)
{
cout<<"\nThe password did not match. Do you want to re-try\n";
gets(fp);
if(strcmpi(fp,"yes")==0)
goto rep;
else
{
cout<<"\nDo you want to set a different password\n";
gets(fp);
if(strcmpi(fp,"yes")==0)
goto pwrong;
else
waste();
}}
else
{
cout<<"\n\nRegistration Successful";
g.tsc=0;
g.id_ch=1;
f1.seekp(0,ios::end);
f1.write((char*)&g,sizeof(g));
f1.close();
login(2);
delay(2000);
}}}
void login(int icheck=0)
{
char s[20], ch[20];
int i;
if(icheck==0)
i=1;
else if(icheck==1)
i=3;
else if(icheck==2)
i=2;
game g;
ifstream f1;
f1.open("Gamer.dat",ios::binary);
while(i)
{
clrscr();
cout<<"                         ___  ___         ___   ___        ___                  ";
cout<<"                        |    |   | |\\  | |     |   | |    |                     ";
cout<<"                        |    |   | | \\ | |___  |   | |    |___                  ";
cout<<"                        |    |   | |  \\|     | |   | |    |                     ";
cout<<"                        |___ |___| |   |  ___| |___| |___ |___                  ";
cout<<"                                       _   _                            "<<endl;
cout<<"	                          |   | | | _ | |\\|                           "<<endl;
cout<<"                                  |__ |_| |_| | | |                     "<<endl;
cout<<"________________________________________________________________________________";
cout<<endl;
if(i==1)
{
cout<<"Welcome to PARZIVAL Console";
cout<<endl;
cout<<"\nIn order to access this Console you need a PARZIVAL account";
cout<<endl;
cout<<"\nDo you already have an account ?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
{
cout<<"\nDo you want to login to your account?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
{
i=2;
continue;
}
else
{
cout<<"\nWhy not? Did you forget any of your account password?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
{
i=4;
continue;
}
else
{
waste();
}}}
else
{
cout<<endl;
cout<<"Do you want to register an account?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
{
i=3;
continue;
}
else
waste();
}}
if(i==2)
{
cout<<"Cool. Now lets login to your account\n";
lid:
cout<<"\nEnter your gamer tag:\n";
gets(s);
g=gamel(s);
if(check(s)==0)
{
cout<<"\nIt seems like no such game id exists\n";
cout<<"Do you want to retry:\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
goto lid;
else
{
cout<<"\nSo do you want to register an account?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
{
i=3;
c=0;
continue;
}
else
waste();
}}
else
{
pid:
cout<<"\nEnter your account password:\n";
gets(s);
if(strcmp(s,g.pass)==0)
{
cout<<"\nLogin Successful\n";
getch();
screen(g.id);
i=0;
continue;
}
else
{
cout<<"\nIt seems like that the password is not matching with that gamer id\n";
cout<<"Do you want to re-enter the password?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
goto pid;
else
{
cout<<"\nDid you forget your password?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
{
i=4;
continue;
}
else
waste();
}}}}
if(i==3)
{
if(c==0)
{
cid:
create();
i=2;
}
if(c==1)
{
cout<<"\nSorry, that id is already taken.\n";
goto cid;
}}
if(i==4)
{
flid:
cout<<"\nEnter your gamer tag:\n";
gets(s);
g=gamel(s);
if(check(s)==0)
{
cout<<"\nIt seems like no such game id exists\n";
cout<<"Do you want to retry:\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"yeah")==0)
goto flid;
else
waste();
}
else
{eid:
cout<<"\nEnter your email:\n";
gets(s);
if(strcmp(s,g.email)==0)
{
cout<<"\nEnter the new password\n";
gets(s);
updatep(g.id,s);
i=2;
continue;
}
else
{
cout<<"\nIt seems like that the e-mail is not matching with that gamer id\n";
cout<<"Do you want to re-enter the email?\n";
gets(s);
if(strcmpi(s,"yes")==0||strcmpi(s,"y")==0)
goto eid;
else
waste();
}}}}}
void hang(char a[]);
void reward(char r[])
{
cout<<"\n\n\n\n\n";
cout<<"                    - -    /- -  |    |    |     - -    / -\\        "<<endl;
cout<<"                   |   |   |     |    |   / \\   |   |   |   \\      "<<endl;
cout<<"                   |- -    |---  | /\\ |  |   |  |- -    |   |       "<<endl;
cout<<"                   | \\     |     | /\\ |  |- -|  | \\     |   /     "<<endl;
cout<<"                   |  \\    \\- -  |/  \\|  |   |  |   \\   \\ -/    "<<endl;
cout<<"                   -----------------------------------------      "<<endl;
cout<<"\n                               ";
cout<<r;
getch();
}
void spinsc()
{
clrscr();
cout<<"           |      |   |   /--  |  /  \\   /       /----   - -   +  |\\  |    \n";
cout<<"           |      |   |  |     |/     \\ /        |      |   |  |  |\\  |    \n";
cout<<"           |      |   |  |     |\\      |         \\---+  |---   |  | \\ |    \n";
cout<<"           |      |   |  |     | \\     |             |  |      |  |  \\|    \n";
cout<<"           \\----   \\_/    \\--  |  \\    |         ----/  |      |  |  \\|    \n";
for(int i=0;i<80;i++)
cout<<(char)196;
}
void spin(int tsc)
{
int op=0,idch=0,sc=0;
long ran;
char user[10];
start:
spinsc();
cout<<"\n            In this game you just need to give up some of           "<<endl;
cout<<"             your exp to get something or another in return.                   "<<endl;
cout<<"                   But sometimes you get nothing back.             \n"<<endl;
for(int i=0;i<80;i++)
cout<<(char)196;
cout<<"\n                     Play this game out of your own risk.            "<<endl;
cout<<"              Ofcourse there's a lot of chance to gain more exp.     "<<endl;
cout<<"            But there's also a chance of losing a lot of your exp.   \n"<<endl;
cout<<"                   This game doesn't require any skills.             "<<endl;
cout<<"                         You just need some luck.                    "<<endl;
for(i=0;i<80;i++)
cout<<(char)196;
if(op==0)
{cout<<"\n                      Loading Please wait........";
delay(3500);
op++;
goto start;
}
cout<<"\n                        Press any key to continue";
getch();
check:
game g;
g=gamel(logid);
if(g.tsc<900)
{
spinsc();
cout<<"\n\n\n";
cout<<"                                    "<<(char)286<<endl;
cout<<"                                   / \\                 "<<endl;
cout<<"                                 /  !  \\               "<<endl;
cout<<"                               < _ _ _ _ >              "<<endl;
cout<<"                        + ---------------------- +      "<<endl;
cout<<"                        |     Lvl 10 Required    |      "<<endl;
cout<<"                        |                        |      "<<endl;
cout<<"                        |  You do not meet the   |      "<<endl;
cout<<"                        |  minimum requirements  |      "<<endl;
cout<<"                        |   to play the game.    |      "<<endl;
cout<<"                        + ---------------------- +      "<<endl;
getch();
screen(logid);
}
ran=random(10000)+1;
if(ran<=6000)
ran=1;
else if(ran<=8500)
ran=2;
else if(ran<=9750)
ran=3;
else if(ran<=9999)
ran=4;
else
ran=5;
spinsc();
cout<<"Instruction:                                                            "<<endl;
cout<<"Enter the type of Roulette to spin.Each has its own charges and rewards."<<endl;
cout<<"You can also enter exit to quit.                       Your exp:"<<g.tsc<<endl;
for(i=0;i<80;i++)
cout<<(char)196;
cout<<"         Regular          |          Premium          |          Elite          ";
cout<<"       Fee: 20 Exp        |        Fee: 300 Exp       |       Fee: 900 Exp      ";
cout<<" - - - - - - - - - - - - -+- - - - - - - - - - - - - -+- - - - - - - - - - - - -";
cout<<"     Possible Reward      |      Possible Reward      |      Possible Reward    ";
cout<<"                          |                           |                         ";
cout<<"         Jackpot          |          Jackpot          |          Jackpot        ";
cout<<"         200 Exp          |         1500  Exp         |         6000  Exp       ";
cout<<"                          |                           |                         ";
cout<<"   80  Exp      50 Exp    |   500 Exp     Id changer  |  2000  Exp    1500 Exp  ";
cout<<"  Very Rare      Rare     |  Very Rare       Rare     |  Very Rare      Rare    ";
cout<<"                          |                           |                         ";
cout<<"   20 Exp       Nothing   |   300  Exp      Nothing   | Id changer(3)  Nothing  ";
cout<<"   Common     Very Common |    Common     Very Common |    Common    Very Common";
for(i=0;i<80;i++)
cout<<(char)196;
cout<<"   Player input:  ";
gets(user);
if(strcmpi(user,"Regular")==0)
{
spinsc();
if(ran==1)
{
tsc-=20;
sc=-20;
update(logid,sc);
reward("NOTHING");
}
else if(ran==2)
{
reward("20 EXP");
}
else if(ran==3)
{
tsc+=30;
sc=30;
update(logid,sc);
reward("50 EXP");
}
else if(ran==4)
{
tsc+=60;
sc=60;
update(logid,sc);
reward("80 EXP");
}
else if(ran==5)
{
tsc+=180;
sc=180;
update(logid,sc);
reward("200 EXP");
}}
else if(strcmpi(user,"Premium")==0)
{
spinsc();
if(ran==1)
{
tsc-=300;
sc=-300;
update(logid,sc);
reward("NOTHING");
}
else if(ran==2)
{
reward("300 EXP");
}
else if(ran==3)
{
idch=1;
sc=-300;
update(logid,sc);
update(logid,idch,1);
reward("ID CHANGER");
}
else if(ran==4)
{
tsc+=200;
sc=200;
update(logid,sc);
reward("500 EXP");
}
else if(ran==5)
{
tsc+=1200;
sc=1200;
update(logid,sc);
reward("1500 EXP");
}}
else if(strcmpi(user,"Elite")==0)
{
spinsc();
if(ran==1)
{
tsc-=900;
sc=-900;
update(logid,sc);
reward("NOTHING");
}
else if(ran==2)
{
idch=3;
sc=-900;
update(logid,sc);
update(logid,idch,1);
reward("ID CHANGER(3)");
}
else if(ran==3)
{
tsc+=600;
sc=600;
update(logid,sc);
reward("1500 EXP");
}
else if(ran==4)
{
tsc+=1100;
sc=1100;
update(logid,sc);
reward("2000 EXP");
}
else if(ran==5)
{
tsc+=6100;
sc=6100;
update(logid,sc);
reward("7000 EXP");
}}
else if(strcmpi(user,"Exit")==0)
{
screen(logid);
}
goto check;
}
void settingsc()
{
clrscr();
cout<<"            /----  /---  -----  -----  -----  |\\  |  /---   /----   \n";
cout<<"            |      |       |      |      |    |\\  |  |      |       \n";
cout<<"            \\---   |---    |      |      |    | \\ |  |  --  \\---  \n";
cout<<"                |  |       |      |      |    |  \\|  |   |      |   \n";
cout<<"            ----/  \\---    |      |    -----  |  \\|  \\---/  ----/ \n";
cout<<endl;
for(int i=0;i<80;i++)
cout<<(char)196;
}
void setting(char a[])
{
char user[40],user1[40];
int op=0,epos;
game g;
g=gamel(logid);
strcpy(logp,g.pass);
strcpy(logg,g.email);
int ef;
char pas[20],mail[40];
for(int i=0;i<strlen(g.pass);i++)
pas[i]='*';
pas[i]='\0';
for(i=0;i<strlen(g.email);i++)
{
if(i<3)
mail[i]=g.email[i];
else if(g.email[i]=='@')
{
mail[i]='*';
i++;
mail[i]=g.email[i];
i++;
mail[i]=g.email[i];
i++;
mail[i]=g.email[i];
}
else
mail[i]='*';
}
mail[i]='\0';
settingsc();
cout<<"                               Player profile\n\n";
cout<<"      Gamer Id: "<<g.id;
for(i=1;i<18-strlen(g.id);i++)
cout<<" ";
cout<<"                          Lvl:"<<g.tsc/100+1<<endl;
cout<<"         Email: "<<mail<<endl;
cout<<"      Password: "<<pas;
for(i=1;i<18-strlen(g.pass);i++)
cout<<" ";
cout<<"                   Id changer:"<<g.id_ch<<endl<<endl;
for(i=0;i<80;i++)
cout<<(char)196;
cout<<"                              Available Commands\n\n";
cout<<"    changei - to change the gamer id        changee - to change the email\n";
cout<<"               (requires id changer)\n";
cout<<"    changep - to change the password           back - to go back\n\n";
cout<<"     logout - to log out                       exit - to exit the console\n";
for(i=0;i<80;i++)
cout<<(char)196;
cout<<" Player's input : ";
gets(user);
if(strcmpi(user,"changei")==0)
{
settingsc();
cout<<"\nEnter the current password\n";
gets(user);
if(strcmp(user,g.pass)!=0)
{
cout<<"\nPassword didn't match\n";
delay(3000);
setting(logid);
}
if(g.id_ch>=1)
{
newid:
cout<<"\nEnter the new id(max 9 character):\n";
gets(user);
if(strlen(user)<=9)
{
if(check(user)==1)
{
cout<<"\nId already exists\n";
goto newid;
}
cout<<"\n Are you sure you want to change your id\n";
gets(user1);
if(strcmpi(user1,"yes")!=0)
setting(logid);
update(logid,-1,1);
updatep(logid,user,2);
strcpy(logid,user);
cout<<"\nUpdation Success\n";
delay(2000);
setting(logid);
}
else
goto newid;
}
else
{
cout<<"\n\n\n You do not have any Id changer\n";
setting(logid);
}}
else if(strcmpi(user,"changee")==0)
{
settingsc();
cout<<"\nEnter the current password\n";
gets(user);
if(strcmp(user,g.pass)!=0)
{
cout<<"\nPassword didn't match\n";
delay(3000);
setting(logid);
}
gwrong:
cout<<"\nEnter the new email address.\n";
gets(user);
op=0;
for(i=0;i<strlen(user);i++)
{
if(user[i]=='@')
{
epos=i;
op++;
}}
if(op!=1||epos<=6)
goto gwrong;
for(i=0;i<strlen(user);i++)
{
if(i<epos)
if(!isalnum(user[i]))
goto gwrong;
else if(i==strlen(user)-4)
if(user[i]!='.')
goto gwrong;
}
cout<<"\nAre you sure, you want to change your email?\n";
gets(user1);
if(strcmpi(user1,"yes")!=0)
setting(logid);
updatep(logid,user,1);
updatep(logid,logp);
strcpy(logg,user);
cout<<"\nUpdation Successful\n";
delay(2000);
setting(logid);
}
else if(strcmpi(user,"changep")==0)
{
settingsc();
cout<<"\nEnter the current password\n";
gets(user);
if(strcmp(user,g.pass)!=0)
{
cout<<"\nPassword didn't match\n";
delay(3000);
setting(logid);
}
pwrong:
cout<<"\nEnter the new password\n";
gets(user);
int uc=0,lc=0,chc=0;
for(i=0;i<strlen(user);i++)
{
if(isupper(user[i]))
uc++;
else if(islower(user[i]))
lc++;
else if(!isalpha(user[i]))
chc++;
}
int len=strlen(user);
if(len>18||len<6||uc<1||lc<1||chc<1)
goto pwrong;
cout<<"\nAre you sure, you want to change your password?\n";
gets(user1);
if(strcmpi(user1,"yes")!=0)
setting(logid);
updatep(logid,user);
strcpy(logp,user);
cout<<"\nUpdation Successful\n";
delay(2000);
setting(logid);
}
else if(strcmpi(user,"back")==0)
screen(logid);
else if(strcmpi(user,"logout")==0)
login();
else if(strcmpi(user,"exit")==0)
exit(0);
else
setting(logid);
}
void screen(char a[])
{
game g,t[3],te[100];
g=gamel(a);
strcpy(logid,g.id);
strcpy(logp,g.pass);
int opt,crash=0,fir,sec,th;
char in[10];
scr:
clrscr();
cout<<"________________________________________________________________________________";
cout<<" Id:";
fill(g.id);
cout<<g.id<<"                            Lvl:";
cout<<setw(3)<<(g.tsc/100)+1<<"   ->"<<(char)179<<" ";
int z=g.tsc;
while(z>=100)
{
z=z-100;
}
for(int i=0;i<z;i+=10)
{
cout<<"||";
}
for(i=0;i<100-z;i+=10)
{
cout<<"  ";
}
cout<<" "<<(char)179<<"<-";
for(i=0;i<80;i++)
cout<<(char)196;
total();
ifstream f;
f.open("Gamer.dat",ios::binary);
f.seekg(0);
for(i=0;i<size;i++)
f.read((char*)&te[i],sizeof(game));
if(size==1)
t[0]=g;
else if(size==2)
{
t[0].tsc=-1;
t[1].tsc=-1;
for(i=0;i<size;i++)
{
if(te[i].tsc>=t[0].tsc)
{
t[0]=te[i];
fir=i;
}}
for(i=0;i<size;i++)
{
if(te[i].tsc>=t[1].tsc&&i!=fir)
{
t[1]=te[i];
sec=i;
}
}
}
else
{
t[0].tsc=-1;
t[1].tsc=-1;
t[2].tsc=-1;
for(i=0;i<size;i++)
{
if(te[i].tsc>=t[0].tsc)
{
t[0]=te[i];
fir=i;
}}
for(i=0;i<size;i++)
{
if(te[i].tsc>=t[1].tsc&&i!=fir)
{
t[1]=te[i];
sec=i;
}
}
for(i=0;i<size;i++)
{
if(te[i].tsc>=t[2].tsc&&i!=fir&&i!=sec)
{
t[2]=te[i];
}}
}
cout<<(char)179<<" Rank |   Player   |  Pts  "<<(char)179<<endl;
cout<<(char)179<<"------+------------+-------"<<(char)179<<" 	   Instruction:"<<endl;
cout<<(char)179<<"   1  | "<<setw(9)<<t[0].id<<"  |"<<setw(6)<<t[0].tsc<<" "<<(char)179;
cout<<"      Enter the name of the icon to execute it.\n";
cout<<(char)179<<"   2  | "<<setw(9)<<t[1].id<<"  |"<<setw(6)<<t[1].tsc<<" "<<(char)179;
cout<<"      Enter 'exit' to exit the console\n";
cout<<(char)179<<"   3  | "<<setw(9)<<t[2].id<<"  |"<<setw(6)<<t[2].tsc<<" "<<(char)179<<endl;
for(i=0;i<80;i++)
cout<<(char)196;
cout<<"\n            ___________	           ____________ 	  ___________    "<<endl;
cout<<"           "<<(char)179<<"           "<<(char)179<<"	  "<<(char)179<<"            "<<(char)179<<"	 "<<(char)179<<"           "<<(char)179<<"     "<<endl;
cout<<"           "<<(char)179<<"   |   |   "<<(char)179<<"	  "<<(char)179<<"    |       "<<(char)179<<"	 "<<(char)179<<"   /----   "<<(char)179<<"     "<<endl;
cout<<"           "<<(char)179<<"   |_ _|   "<<(char)179<<"	  "<<(char)179<<"    |       "<<(char)179<<"	 "<<(char)179<<"   |       "<<(char)179<<"     "<<endl;
cout<<"           "<<(char)179<<"   |---|   "<<(char)179<<"	  "<<(char)179<<"    |       "<<(char)179<<"         "<<(char)179<<"   \\---    "<<(char)179<<"      "<<endl;
cout<<"           "<<(char)179<<"   |   |   "<<(char)179<<"	  "<<(char)179<<"    |       "<<(char)179<<"	 "<<(char)179<<"       |   "<<(char)179<<"     "<<endl;
cout<<"           "<<(char)179<<"   |   |   "<<(char)179<<"	  "<<(char)179<<"    \\----   "<<(char)179<<"	 "<<(char)179<<"   ----/   "<<(char)179<<"     "<<endl;
cout<<"           "<<(char)179<<"  Hangman  "<<(char)179<<"	  "<<(char)179<<" Lucky Spin "<<(char)179<<"	 "<<(char)179<<"  Setting  "<<(char)179<<"     "<<endl;
cout<<"           "<<(char)179<<"___________"<<(char)179<<"	  "<<(char)179<<"____________"<<(char)179<<"	 "<<(char)179<<"___________"<<(char)179<<"   "<<endl;
cout<<"                                                                                ";
cout<<"                                                                                ";
for(i=0;i<80;i++)
cout<<(char)196;
cout<<"    Player's Input : ";
gets(in);
if(strcmpi(in,"Hangman")==0||strcmpi(in,"H")==0)
{
hang(g.id);
}
else if(strcmpi(in,"lucky spin")==0||strcmpi(in,"L")==0)
{
spin(g.tsc);
}
else if(strcmpi(in,"exit")==0||strcmpi(in,"e")==0)
exit(0);
else if(strcmpi(in,"setting")==0||strcmpi(in,"s")==0)
{
setting(g.id);
}
else if(crash!=10)
{
crash++;
goto scr;
}
else
{
cout<<"                       Error(404).The Console has crashed.\n";
cout<<"                     We are so sorry for the inconvenience.";
cout<<"\n                          Please restart the console.";
getch();
exit(0);
}}
void hangsc()
{
clrscr();
cout<<endl;
cout<<"             |   |     |     |\\  |    ___    |\\  /|     |     |\\  |  "<<endl;
cout<<"             |_ _|    | |    |\\  |   |       |\\  /|    | |    |\\  |  "<<endl;
cout<<"             |---|   |_ _|   | \\ |   |       | \\/ |   |_ _|   | \\ |  "<<endl;
cout<<"             |   |   |---|   |  \\|   |   |-  |    |   |---|   |  \\|   "<<endl;
cout<<"             |   |   |   |   |  \\|   |___|   |    |   |   |   |  \\|   "<<endl;
cout<<endl;
for(int i=0;i<80;i++)
cout<<(char)196;
}
void abt_hang()
{
cout<<"  About The Game:\n";
cout<<"1.Once the game starts the player will be given 7 lives\n";
cout<<"2.A movie name will be displayed with all the alphabets replaced with a hyphen.";
cout<<"3.The main objective of the player is to guess the movie name.\n";
cout<<"4.The player has to enter a alphabet which he/she think is in the movie name.\n";
cout<<"5.If the entered alphabet is in the movie name, all the dashes present in the     ";
cout<<"places of that alphabet present in the movie name is updated as the alphabet.\n";
cout<<"6.If the entered alphabet is not in the movie name, a life will be reduced.\n";
cout<<"7.The player will keep on entering alphabets\n";
cout<<"8.The game will go on until either the player completes the movie name by\n";
cout<<"  guessing the alphabets correctly or his/her life becomes zero.\n";
for(int i=0;i<80;i++)
cout<<(char)196;
}
void hang_over(int lyf,char a[]);
void hang(char a[]);
void demo()
{
for(int j=1;j<=10;j++)
{
hangsc();
cout<<"Rules to Play:\n";
cout<<"1.If the player enters a single letter, it is taken as a guess.\n";
cout<<"2.If the player enters a word, it is taken as a command.\n";
cout<<"                                Availabe commands:\n";
cout<<"'clue'-reveals an alphabet, but costs two lives      'help'-how to play the game       \n";
cout<<"'exit'-quit the game                                 'reset'-restarts the game\n";
for(int i=0;i<80;i++)
cout<<(char)196;
for(i=0;i<71;i++)
cout<<" ";
cout<<"Life: ";
if(j==4||j==5)
cout<<"6"<<endl;
else if(j>=6)
cout<<"5\n";
else
cout<<"7\n";
if(j!=10)
cout<<"   Movie name: ";
if(j==1)
cout<<"--------"<<endl;
else if(j==2)
cout<<"-o------\n";
else if(j==3||j==4)
cout<<"-o-----a\n";
else if(j==5||j==6)
cout<<"-o--i--a\n";
else if(j==7)
cout<<"-o--illa\n";
else if(j==8)
cout<<"Go--illa\n";
else if(j==9)
cout<<"God-illa\n";
else if(j==9)
cout<<"Godzilla\n";
if(j==10)
{
cout<<"\n           Movie Name : Godzilla"<<endl;
cout<<"\n                                 YOU WON\n";
}
if(j!=10)
cout<<"  Users input: ";
delay(2500);
if(j==1)
cout<<"o";
else if(j==2)
cout<<"a";
else if(j==3)
cout<<"m";
else if(j==4)
cout<<"i";
else if(j==5)
cout<<"s";
else if(j==6)
cout<<"l";
else if(j==7)
cout<<"g";
else if(j==8)
cout<<"d";
else if(j==9)
cout<<"z";
cout<<endl;
if(j==3||j==5)
cout<<"                                InCorrect";
else if(j!=10)
cout<<"                                 Correct";
delay(1500);
if(j==10)
{
cout<<"\n\nPress any key to continue";
getch();
hang(logid);
}}}
void hang(char a[])
{
game g;
g=gamel(a);
char mov[][40]={ "Dhuruvangal 16","Bahubali","Kaala","Aadai","Thani Oruvan",
		"Vada Chennai","Sivaji","Natpe Thunai","Meesaya Murukku",
		"Sarkar","Nerkonda Parvai","Enthiran","Vikram Vedha",
		"Vedhalam","K.O","Naanum Rowdy Thaan","Theri","Kathi",
		"Thuppaki","Viswasam","Vivegam","Thillu Mullu","Vishwaroopam",
		"Pichaikaran","Kalakalapu","Kavan","Anbe Sivam","Comali",
		"Kanchana","Miruthan","Santhosh Subramaniyam",
		"NGK","Velai Illa Patathari","Puli","Billa","Baasha",
		"Mangatha","Alex Pandian","Raatchasi","Ratchasan",
		"Monster","Darling","Pizza","Vetaikaran","Nanban","Thozha",
		"Vanakkam Chennai","Maan Karate","Remo","Velaikaran",
		"Saamy","Kabali","Kaala","Dhuruva Natchathiram",
		"Irumugan","Aambala","Veeram","Aranmanai","Gilli","Goa",
		"Mersal","Jilla","Kaaki Sattai","Junga"};
/*char mov[][40]={"Forrest Gump","The GodFather","Titanic","The Matrix",
		"Fifty Shades of Grey","Troy","Taxi Driver","Avatar","American Pie",
		"Baby Driver","Fast and Furious","Annabelle",
		"Venom","Ready Player One","Rampage","Tomb Raider",
		"The Predator","The Meg","Charlie & The Chocolate Factory ","Zootopia","Moonlight",
		"Deadpool","Don't Breathe","Mirrors",
		"Passengers","Hacksaw Ridge","La La Land","Doctor Strange",
		"Boss Baby","The Jungle Book","Lights Out",
		"Suicide Squad","Silence","GhostBusters","The Conjuring",
		"Harry Potter"," Dunkirk","Wonder Woman","Logan","The Fault In Our Stars",
		"Star Wars","Iron Man","Spider Man:Homecoming",
		"Inside Out","Justice League","Spy kids",
		"Avengers: Infinity War","Black Panther","Mission Impossible",
		"Incredibles","Ant Man","Halloween","Jurassic World","Aquaman",
		"The Nun","Skyscraper","The Dark Knight","Die Hard","Avengers:Endgame",
		"Crazy Stupid Love","The Avengers","The Amazing Spider Man","Gladiator"};
*/
randomize();
int cl,sel,op=0,len,inp,lif,cfound=0,found=0;
char user[10],word[40],cword[40];
hangsc();
if(op==0)
{
abt_hang();
cout<<"Enter: 'play'-start the game. 'demo'-quick auto tutorial. 'exit'-quit the game.\n";
cin>>user;
if(strcmpi(user,"play")==0||strcmpi(user,"p")==0)
op=1;
else if(strcmpi(user,"demo")==0||strcmpi(user,"d")==0)
{
demo();
hang(logid);
}
else if(strcmpi(user,"exit")==0||strcmpi(user,"e")==0)
screen(a);
}
if(op==1)
{
reseth:
sel=random(63);

strcpy(cword,mov[sel]);
strcpy(word,mov[sel]);
len=strlen(cword);
cfound=0;
for(int i=0;i<len;i++)
if(isalpha(cword[i]))
word[i]='-';
lif=7;
while(1)
{
found=0;
hangsc();
cout<<"Rules to Play:\n";
cout<<"1.If the player enters a single letter, it is taken as a guess.\n";
cout<<"2.If the player enters a word, it is taken as a command.\n";
cout<<"                                Availabe commands:\n";
cout<<"'clue'-reveals an alphabet, but costs two lives      'help'-how to play the game       \n";
cout<<"'exit'-quit the game                                 'reset'-restarts the game\n";
for(i=0;i<80;i++)
cout<<(char)196;
for(i=0;i<71;i++)
cout<<" ";
cout<<"Life: "<<lif<<endl;
cout<<"   Movie name: "<<word<<endl;
if(lif<=0)
{
cout<<"\n           Movie Name : "<<cword<<endl;
cout<<"\n                                 GAME OVER\n";
delay(2000);
hang_over(lif,logid);
goto reseth;
}
else if(strcmp(word,cword)==0)
{
cout<<"\n           Movie Name : "<<cword<<endl;
cout<<"\n                                 YOU WON\n";
delay(2000);
hang_over(lif,logid);
goto reseth;
}
else
{
cout<<"  Users input: ";
cin>>user;
cout<<endl;
if(user[1]=='\0')
{
inp=user[0];
guess:
for(i=0;i<len;i++)
{
if(inp==tolower(cword[i])||inp==toupper(cword[i]))
{
found=1;
if(i==0||!(isalpha(cword[i-1])))
word[i]=toupper(inp);
else
word[i]=tolower(inp);
}}
if(found==0)
{
lif--;
cout<<"                                InCorrect";
delay(1000);
}
else if(strcmpi(user,"Clue")!=0&&strcmpi(user,"reset")!=0&&strcmpi(user,"exit")!=0)
{
cout<<"                                 Correct";
delay(500);
}}
else if(strcmpi(user,"clue")==0)
{
if(lif==2)
{cout<<"                    You can't use this when you only have two lives";
delay(500);
}
else if(cfound==1)
{
cout<<"                             You can use this only once a game";
delay(500);
}
else
{
lif=lif-2;
while(1)
{
cl=random(len);
if(word[cl]=='-')
break;
}
inp=cword[cl];
cfound=1;
delay(200);
goto guess;
}}
else if(strcmpi(user,"reset")==0)
{
cout<<"Your progress won't be saved. Are you sure, you want to restart?\n";
gets(user);
if(strcmpi(user,"yes")==0||strcmpi(user,"y")==0)
goto reseth;
else continue;
}
else if(strcmpi(user,"h")==0)
{
hangsc();
abt_hang();
cout<<"Press Enter to continue";
getch();
}
else if(strcmpi(user,"exit")==0)
{
cout<<"Your progress won't be saved. Are you sure, you want to exit?\n";
cin>>user;
if(strcmpi(user,"yes")==0||strcmpi(user,"y")==0)
screen(logid);
else
continue;
}}}}}
void hang_over(int lyf,char a[])
{
game g;
g=gamel(a);
randomize();
int sc=10;
hangsc();
cout<<endl;
char ch[100];
if(lyf!=0)
cout<<"                             !!!CONGRADULATIONS!!!\n\n";
else
cout<<"                      -------BETTER LUCK NEXT TIME-------\n\n";
for(int i=0;i<80;i++)
cout<<(char)196;
delay(1000);
cout<<endl;
cout<<"                  Level Completion points =   10   = 10\n";
delay(1000);
cout<<"                   Level Clearance points =  ";
if(lyf!=0)
{
cout<<" 50   = 50\n";
sc=sc+50;
}
else
cout<<"  0   =  0\n";
delay(1000);
cout<<"                        Bonus Life points = "<<lyf<<" X 10 = ";
if(lyf==0)
cout<<" ";
cout<<lyf*10<<endl;
sc+=lyf*10;
delay(1000);
cout<<"                    Perfect Finish points =";
if(lyf==7)
{
cout<<"   50   = 50\n";
sc+=50;
}
else
cout<<"    0   =  0\n";
delay(1000);
cout<<"                             Lucky points =";
int r=random(1000);
if(r<500)
{
cout<<"   30   = 30\n";
sc+=30;
}
else
cout<<"    0   =  0\n";
delay(1000);
cout<<"                                                   ______\n";
cout<<"                                                      "<<sc<<endl;
update(a,sc);
for(i=0;i<80;i++)
cout<<(char)196;
cout<<"Do you want to play again(Yes/No)?\n";
cin>>ch;
if(strcmpi(ch,"Yes")==0||strcmpi(ch,"y")==0)
{
hang(logid);
}
else
screen(logid);
}
void main()
{
clrscr();
cout<<endl;
cout<<"________________________________________________________________________________";
cout<<"________________________________________________________________________________";
cout<<"                                                                                ";
cout<<"             ___           ___                                           "<<endl;
cout<<"            |   |    |    |   |   -----   |  \\        /    |    |        "<<endl;
cout<<"            |   |   | |   |   |       /   |   |      |    | |   |        "<<endl;
cout<<"            |   |  |   |  |   |      /    |   \\      /   |   |  |        "<<endl;
cout<<"            |___|  |   |  |___|     /     |    |    |    |   |  |        "<<endl;
cout<<"            |      |===|  |\\       /      |    \\    /    |===|  |        "<<endl;
cout<<"            |      |   |  | \\     /       |     |  |     |   |  |        "<<endl;
cout<<"            |      |   |  |   \\   -----   |      \\/      |   |   ------  "<<endl;
cout<<"                                                                         "<<endl;
cout<<"                                                                         "<<endl;
cout<<"                                                                         "<<endl;
cout<<"                         __  __        __   __       __                    "<<endl;
cout<<"                        |   |  | |\\ | |    |  | |   |                      "<<endl;
cout<<"                        |   |  | | \\|  --  |  | |   |--                     "<<endl;
cout<<"                        |__ |__| |  |  __| |__| |__ |__                      "<<endl;
cout<<"                                                                         "<<endl;
cout<<"________________________________________________________________________________";
cout<<"________________________________________________________________________________";
getch();
login();
}

