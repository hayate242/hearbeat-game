#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>

int divide(char *s,char **argp,int maxn){
  
  int n = 0;
  char prev = ' ';

  while(*s != '\0'){
    if(*s == ' ' || *s == '\t' || *s == '\n'){
      if(prev != ' ')
	*s = '\0';
      prev = ' ';
    }
    else{
      if(prev == ' '){
	*argp++ = s;
	n++;
	if(n == maxn)
	  return (-1);
      }

      prev = *s;
    }
    s++;
  }
  *argp = NULL;
  return (n);

}

int main(void){
  int n = 0;
  char *argv[1024],ln[1024],home[1024];
  int st = 0;
  int i = 0;

  strcpy(home,getpwuid(getuid())->pw_dir);

  while(1){
    printf("%s","Please input something: ");
    
    fgets(ln,1024,stdin);
    if((n=divide(ln,argv,1024))==-1)
      fprintf(stderr,"Too many arguments.\n");
    
    // argv[i] = &ln[i];
    
    if(strcmp(argv[0],"cd")==0){
      printf("cd!\n");
      if(n==2)
	chdir(argv[1]);
      else if(n==1)
	chdir(home);
      else
      fprintf(stderr,"Too many arguments.\n");
    }
    else if(fork() != 0){
      wait(&st);
    }
    else{
      execvp(argv[0],argv);
      printf("%s","error\n");
      exit(1);
    }

     i++;
  }

  
   

  return 0;
}
