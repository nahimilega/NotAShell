#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


void introScreen() {
    /*
    This displays the initial message on the screen
    */
    printf("Welcome To the Terminal \n");
    printf("Made by: Archit Agrawal");
    char* username = getenv("USER");
    printf("\033[0;32m");
    printf("\n\n\nUSER is: %s \n", username);
    printf("\033[0m");
}

char *prDir(){
    /*
    Return the current directory
    */
    static char cwd[1000];
    getcwd(cwd, sizeof(cwd));
    return cwd;
}

void concatenate_string(char *original, char *add)
{
   while(*original)
      original++;

   while(*add)
   {
      *original = *add;
      add++;
      original++;
   }
   *original = '\0';
}

void forkVale( char *command, char **parm ){
    // char command[], char options[], char parms[]
    // Forking a child
    pid_t pid = fork();
    char binaryAddress[] = "/bin/";
    if (pid == -1) {
        printf("Error While Forking");
        return ;
    }
    else if (pid == 0) {



        concatenate_string(binaryAddress,command);

        execv(binaryAddress, parm) ;


        exit(0);
    }

    else {
        wait(NULL);
        return;
    }
}

void cd(char parm[]){
    /*
    Testing needed
    */

  if (chdir(parm) != 0)
    perror("cd: no such file or directory b: \n" );
}

void echo(char *allParm[40]){
    /*
    Done
    Args:
        A total of all the parameters
    */

   for (int i = 1; allParm[i] != NULL; i++)
   {
       printf("%s \n",allParm[i]);
   }
}

void History(char *history[], int historyCounter){
    // FIX ME in loop condition

    for (int i = 0; i< historyCounter; i++){
      printf("%d: %s \n",i+1,history[i]);
    }
}

void pwd(){
    /*
        Done
    */
    char cwd[1000];
    getcwd(cwd, sizeof(cwd));
    printf("%s \n", cwd );
}

void eexit(){
    /*
        Done
    */
    exit(0);
}


void leftPanel(){
    printf("\033[0;32m");
    char *username = getenv("USER");

    char *cwd = prDir();

    printf("%s@work-pc:", username);


    printf("\033[0m");
    printf("\033[1;34m");
    printf("%s",cwd);

    printf("\033[0m");
    printf("$ ");
}


//and split into the words, seprated by spaces

int getWords(char *base, char target[30][40])
{
    /*
    Only break the words by spaces
    */

   int last_value;
   for(last_value=0; base[last_value]!='\0' ;last_value++){
   }


    for (int i = last_value-1; base[i] == ' '; i--) {
        base[i] = '\0';
    }


	int n=0,i,j=0;

	for(i=0; base[i]!='\0' ;i++)
	{
		if(base[i] != ' '){
			target[n][j++] = base[i];
		}


		else{
			target[n][j] = '\0';//insert NULL
			n++;
			j=0;
		}

	}

    target[n][j] = '\0';
	return n;
}



void printString(char* inputString)
{
    for (int i = 0; inputString[i] != '\0'; i++) {
    printf("%c",inputString[i]);
    }

}


int sanatizeWords(char arr[30][40], int n, char newArr[30][40]){
    /*
    Remove all the extra white spaces and you are only left with words
    */
    int newCtr = 0;
    for (int i = 0; i < n; i++) {
        if(*arr[i] != '\0'){
            for(int loop = 0; loop < 40; loop++) {
                newArr[newCtr][loop] = arr[i][loop];
            }
            newCtr++;
            /*
            arr[i][0] = 'm';
            arr[i][1] = '\0';
            */
        }

    }
    return newCtr;
}





int main(){

introScreen();

int historyCounter=0;
char* history[500];
char *bin_address = prDir();

concatenate_string(bin_address,"/bin/");


while(1){


    // Take input
    char inputString[6000] = "";
    leftPanel();
    // scanf("%[^\n]%*c", );
    gets(inputString);
    //fgets(inputString, 600, stdin);

    // To protect from enter
    if(strcmp(inputString, "")==0)
        continue;




    history[historyCounter++] = strdup(inputString);

    char arr[30][40];

    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 40; j++)
            arr[i][j] = 'a';




    int n = getWords(inputString,arr);
    n++;

    //sanatizeWords(arr,n);
    char new[30][40];
    n = sanatizeWords(arr,n, new);

    char *parms[n];


    for (int i = 0; i < n; i++)
    {
        parms[i] = new[i];
    }

    parms[n] = NULL;


    char *command = new[0];


    if(strcmp(command ,"cd") == 0){

        cd(new[1]);

    }

    else if( strcmp(command ,"echo")== 0){

        echo(parms);
    }

    else if(strcmp(command ,"history") == 0 ){
        History(history, historyCounter);
    }

    else if( strcmp(command ,"pwd") == 0 ){
        pwd();
    }

    else if( strcmp(command ,"exit") == 0){
        eexit();
    }
    else if(strcmp(command ,"ls") == 0 || strcmp(command ,"mkdir") == 0 || strcmp(command ,"cat") == 0 || strcmp(command ,"date") == 0 || strcmp(command ,"rm") == 0 ){
        forkVale(command,parms);
    }
    else
    {
        printf("NOTaSHELL: command not found: %s \n",command );
    }

}

//leftPanel();
return 0;
}