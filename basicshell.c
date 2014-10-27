#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#include <unistd.h>


#define MAX_LEN 1024
#define DELIMS " \t\r\n"

typedef struct allhis
{
	char nm[100];
	int pid;
}allhis;

int k1=0;int pdp[1000],flag[1000]={0};
int fl1=0,fl2=0,fl3=0,k2=0;
void sig_handler(int signum){

	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
//	signal(SIGCHLD, child_handler);
	signal(SIGQUIT,sig_handler);


//	return;
}
void child_handler(int signum)
{
	int status,x;
	pid_t pid;
	pid=waitpid(WAIT_ANY,&status,WNOHANG);

	for(x=0;x<k1;x++)
	{
		if(pdp[x]==pid)
		{
			printf("%d exited normally\npress enter",pid);
			
				flag[x]=0;
				break;
			}
		
	}
	fflush(stdout);
	signal(SIGCHLD,child_handler);
}



int key=0; 
int main(int argc, char *argv[])
{
	allhis **hs1;
	hs1=(allhis**)malloc(sizeof(allhis*)*1000);
	int hsin=0;
	for(hsin=0;hsin<1000;hsin++)hs1[hsin]=(allhis*)malloc(sizeof(allhis));
	hsin=0;
	
signal(SIGINT,  sig_handler);
signal(SIGTSTP, sig_handler);
//signal(SIGCHLD, child_handler);
//	signal(SIGQUIT,sig_handler);

char h[1000][1000];
char curr[1000][1000];
long pd[1000];int cd[1000];
int x,y,k=0;
for(x=0;x<100;x++)
{
	//pwd2[x]='\0';
	for(y=0;y<100;y++)
	{
		h[x][y]='\0';
		curr[x][y]='\0';
	}
}
char *pwd1;
if((pwd1=getcwd(NULL,64))==NULL)
{
	perror("pwd1");
	exit(0);
}
//printf("%s\n",pwd1);
char p1[1000],p2[1000],p3[1000];
strcpy(p1,pwd1);
strcpy(p2,pwd1);
strcpy(p3,pwd1);
//printf("%s %d\n",p1,strlen(p1));

free(pwd1);
int cle=strlen(pwd1);
//FILE *out=fopen("his","a");
while(1)
{
//	out=fopen("his","a+");
//	printf("-------\n");
	FILE *usrnm=popen("whoami","r");
	char txt[255],hstnm[1024];
	fgets(txt,sizeof(txt),usrnm);
	if(txt[strlen(txt)-1]=='\n')txt[strlen(txt)-1]='\0';
	hstnm[1023]='\0';
	gethostname(hstnm,1023);

	char *pwd;
	if((pwd=getcwd(NULL,64))==NULL)
	{
		perror("pwd");
		exit(0);
	}
	free(pwd);
//	fflush(stdout);
	char pwd2[1000];
	pwd2[0]='~';

	int x1,x2=1;
	for(x1=cle;x1<strlen(pwd);x1++)
	{
		pwd2[x2]=pwd[x1];
		x2++;
	}
	pwd2[x2]='\0';
	//printf("%s %s\n",pwd2,pwd);
	
	printf("<%s@%s:%s>",txt,hstnm,pwd2);
	fflush(stdout);
	char st1[1000];
	
	char ln[MAX_LEN];
	char *cmd;
	if(!fgets(ln,MAX_LEN,stdin))break;
	ln[strlen(ln)-1]='\0';
//	printf("%s",ln);

	strcpy(h[k],ln);
	
	k++;
	strcpy(st1,"command name:");
	strcat(st1,ln);
	strcat(st1," process id: ");
//	fprintf(out,"%s","st1");

	cmd=strtok(ln,DELIMS);
	if(cmd)
	{
	if(strcmp(cmd,"cd")==0)
	{
		char *op=strtok(NULL,DELIMS);
		char *h=getenv("PWD");
	//	printf("%s\n",h);
		char f;
		//if(!op)
		//f=op[0];
	//	printf("%c\n",f);
		if(!op)
		{
//			printf("pid %d\n",(int)getpid());
			//char s1[1000];
			//snprintf(s1,1000,"%d",(int)getpid());
			//printf("%s\n",s1);

			char *hm=getenv("PWD");
		//	printf("%s\n",hm);
			chdir(hm);
			
		}
		else 
		{
			char f=op[0];
			if(f=='~' || (f=='.' & strcmp(op,"..")!=0) )
			{

	char *hm=getenv("PWD");
				chdir(hm);
			}
			else if(strcmp(op,"..")==0 && pwd==pwd1)
			{
			}
			
			else chdir(op);
	}}
	else if(strcmp(cmd,"quit")==0)
	{
	
		break;
	}
	else if(strcmp(cmd,"hist")==0)
	{
		int i;
		for(i=0;i<k-1;i++)printf("%d. %s\n",(i+1),h[i]);
	}
	else if(cmd[0]=='h' && cmd[1]=='i' && cmd[2]=='s' && cmd[3]=='t' && strlen(cmd)>4)
	{
		int ln=0,cv;
		//printf("%s\n",cmd);
		for(cv=4;cv<strlen(cmd);cv++)
		{
			ln=(ln*10)+(int)(cmd[cv]-'0');
		}
		//printf("%d %d\n",k,ln);
		int sp=1;
		for(cv=k-ln+-2;cv<k-2;cv++)
		{
			printf("%d. %s\n",sp,h[cv]);
			sp++;
		}
	}

	else if(strcmp(cmd,"pid")==0)
	{
		char *op=strtok(NULL,DELIMS);
		if(!op)
			                 {
				                         printf("command name: ./a.out process id:%d\n",(int)getpid());
				                 }

		else if(strcmp(op,"all")==0)
		{
		printf("List of all processes spawned from this shell:\n");
		fl1++;
		//qprintf("%d\n",key);
	

		int ii;
		for(ii=0;ii<hsin;ii++)
		{
			printf("command name: %s process id:%d\n",hs1[ii]->nm,hs1[ii]->pid);
		}
		}
		else if(strcmp(op,"current")==0)
		{
			printf("List of currently executing processes spawned from this shell:\n");
			int kl;
			for(kl=0;kl<k2;kl++)
			{
				if(flag[kl]==1)
				printf("command name: %s process id:%d\n",curr[kl],cd[kl]);
			}
		}
	

	}
	

	else
	{
		
		char a[100][100];
		int i,j;
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				a[i][j]='\0';
			}
		}
		strcpy(a[0],cmd);
	//	printf("%s %s\n",a[0],cmd);
		char *s;
	//	strcpy(s,cmd);
		for(i=1;i<100;i++)
		{
			
			s=strtok(NULL,DELIMS);
			if(!s)break;
			strcpy(a[i],s);
		}
		if(a[i-1][strlen(a[i-1])-1]=='&')
{
		a[i-1][strlen(a[i-1])-1]='\0';
		pid_t pid;
		int status;
		char *cm[100];

		for(j=0;j<i;j++)
		{
			//printf("%s\n",a[j]);
			cm[j]=a[j];
			//strcpy(&cm[j],a[j]);
		}
		cm[i]=NULL;
		//strcpy(&cm[i],NULL);
		pid=fork();
		if(pid==0)
		{
		
			int k=execvp(*cm,cm);
			if(k<0)printf("Command not found\n");
			_exit(0);
		
			
		}
		else 
		{

		//	fl2++;
			
			strcpy(hs1[hsin]->nm,cmd);
			hs1[hsin]->pid=pid;
			hsin++;

			key++;
			pdp[k1]=pid;
			k1++;
			 
			 printf("command %s pid %d\n",cmd,pdp[k1-1]);

			strcpy(curr[k2],cmd);
			flag[k2]=1;
			cd[k2]=(int)pid;
			k2++;
			//wait(&status);
//			printf("parent\n");
//			while(wait(&status)!=pid)
			signal(SIGCHLD, child_handler);
		//	sigset_t set;
		//	sigemptyset(&set);
		//	sigaddset(&set, SIGCHLD);
		//	sigprocmask(SIG_BLOCK, &set, NULL);
		//	waitpid(-1, &status, WNOHANG);
			//signal(SIGCHLD,SIG_DFL); /* ignore child */
		//	        signal(SIGTSTP,SIG_IGN);

//				;

		}

	}

	else
	{	pid_t pid;
		int status;
		char *cm[100];

		for(j=0;j<i;j++)
		{
			//printf("%s\n",a[j]);
			cm[j]=a[j];
			//strcpy(&cm[j],a[j]);
		}
		
		cm[i]=NULL;
		//strcpy(&cm[i],NULL);
		pid=fork();
		if(pid==0)
		{
			
			 

			int k=execvp(*cm,cm);
			if(k<0)printf("Command not found\n");
			_exit(0);
		
			
		}
		else 
		{
			strcpy(hs1[hsin]->nm,cmd);
			hs1[hsin]->pid=pid;
			hsin++;
	//		fl2++;
			key++;
//			printf("parent\n");
			pdp[k1]=pid;
			k1++;
			while(wait(&status)!=pid)
				;

		}

	}}
//	printf("<%s@%s:%s>",txt,hstnm,pwd);
//	printf("xxxxxxxxxxxx\n");

	}
/*char *st;
char ne[1000];
scanf(" %[^\n]",ne);
st=strtok(ne,DELIMS);
if(strcmp(st,"quit")==0)exit(1);
else
{
while(st!=NULL)
{
printf("%s\n",st);
st=strtok(NULL,DELIMS);
}
}*/
}
//fclose(out);
return 0;
}

