//
//  room.c
//  COMP206_A4
//
//  Created by Mathew Plouffe on 2017-04-10.
//  Copyright © 2017 Mathew Plouffe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
typedef struct player{
    char* username;
    int manna;
    int gold;
    int isAlive;
} player;

void updatePage(player* aPlayer);
char* getPlayerUsername(player*);
void setPlayerUsername(player*, char*);

int getPlayerManna(player*);
void setPlayerManna(player*, int);

int getPlayerGold(struct player*);
void setPlayerGold(player*, int);

struct player constructNewPlayer(char*, int, int);
void removePlayer(player*);

typedef struct room{
    char* name;
    int manna;
    int gold;
    int isOccupied;
}room;

void playGame();
char* getRoomName(room*);

void setRoomManna(room*, int);
int getRoomManna(room*);

void setRoomGold(room*, int);
int getRoomGold(room*);

void setRoomOccupancy(room*, int);
int getRoomOccupancy(room*);

room initialiseRoom(void);
room createNewRoom(void);

int saveToFile(room*);
int readRoomFromFile(room*);

typedef struct node{
    struct node* previous;
    int value;
    
} node;

typedef struct stack{
    node* top;
    int size;
    
} stack;

int play (char*, int, int);

stack newStack(void);

node pop(stack*);
node peek(stack*);
void push(int, stack*);
node getPrevious(node*);
int isEmpty(stack*);

int initialiseGame(stack*);

stack* readFromFile(void);
int writeToFile(stack[]);

int movePiece(stack*, stack*);

int hasWon(stack*);

int drop (player*, room*, int);

int parseError(int);

char* addToArray(char*);

int main (void){
    //the log is going to be appended to the bottom of the html file upon room update
    //Initialise the room. It grabs the room from the file and make sure that it was loaded correctly
    //get the room from file
    room theRoom=initialiseRoom();
    
    //parse to ensure the room was correctly loaded
    if (parseError(theRoom.isOccupied)==FALSE){
        return FALSE;
    }
    //check for the room occupancy (false is the occupied state
    if (theRoom.isOccupied==TRUE){
        return FALSE;
    }
    
    //assumes that player data is appended to the end of the command
    //parse the data passed to the room by the post command
    
    char* queryString=malloc(1000);
    queryString=getenv("QUERY_STRING");
    
    char* command=malloc(100);
    char* gamecommand=malloc(100);
    char* manna=malloc(4);
    char* gold=malloc(4);
    char* value=malloc(4);
    int i=0;
    int k=0;;
    //the string should be in the following form inventory=10%2C10&input=drop+5&homepage=true
    char c;
    
    while (c!='\0') {
        if (queryString[i]=='%' && queryString[i+1]=='2' && queryString[i+2]=='C'){
            i+=3;
        }
        c=queryString[i++];
    }
    
    i=0;
    if (strstr(queryString, "inventory")){
        while (c!='&'){
            c=queryString[i++];
            
            if (c=='='){
                manna[k++]=queryString[i++];
                manna[k++]=queryString[i++];
                k=0;
                i+=3;
                gold[k++]=queryString[i++];
                gold[k++]=queryString[i++];
                break;
            }
        }
    }
    
    if (strstr(queryString,"play")){
        command="play";
        gamecommand="start";
    }
    else if (strstr(queryString,"drop")){
        k=0;
        i=0;
        command="drop";
        
        while (c!='\0'){
            if (queryString[i]=='%' && queryString[i+1]=='2' && queryString[i+2]=='C'){
                i+=3;
            }
            c=queryString[i++];
            
            if (c=='+'){
                c=queryString[i++];
                value[k++]=c;
            }
        }
    }
    else if (strstr(queryString,"exit")){
        command="exit";
    }
    else {
        command="null";
    }
		
    player thePlayer=constructNewPlayer("thePlayer", atoi(manna), atoi(gold));
    int cmd=0;
    
    if ( strcmp ("drop",command)==0 ){
        cmd=1;
    }
    else if (strcmp("play", command)==0){
        cmd=2;
    }
    else if (strcmp("exit", command)==0){
        cmd=4;
    }
    else{
        ;
    }
    int ret;
    switch (cmd){
        case 1:
            ret=drop(&thePlayer, &theRoom, atoi(value) );
            fflush(stdout);
            break;
        case 2:
            ret=play("start", 0, 0);
            playGame(&thePlayer);
            break;
        case 3:
            ret=saveToFile(&theRoom);
            break;
        case 4:
            setRoomGold(&theRoom, getRoomGold(&theRoom)+thePlayer.gold);
            thePlayer.gold=0;
            setRoomManna(&theRoom, getRoomManna(&theRoom)+thePlayer.manna);
            thePlayer.manna=0;
            break;
            
        default:
            ret=FALSE;
            break;
    }
    if (ret==-1 || ret>0)
    {
        //the command was executed properly
	saveToFile(&theRoom);
        //<<<<<<<<<TODO>>>>>>>>>>>>>>>>
        // write the room information to a file before exiting
        //pass the player information back to the webpage
	updatePage(&thePlayer);
        return ret;
    }
    else
        //the command did not get executed properly
    {
	updatePage(&thePlayer);       	
	return FALSE;
    }
}
void updatePage(player* aPlayer){
	printf("Content-Type: text/html\n\n");
	char* page="<!doctype html><html><title>Tower of Hanoi</title><head><center><h1> Tower of Hanoi </h1></center></head><body><center><img src=\"https://i.ytimg.com/vi/KhWJSpGApOA/maxresdefault.jpg\"><link rel=\"stylesheet\" href=\"./main.css\"/></link></center><br><br><center> Your Mana:%d   Your gold: %d <p><center><form action=\"./room.cgi\" method=\"get\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"text\" placeholder=\"play, drop, refresh, exit\" name=\"input\"/><input type=\"submit\" value=\"Submit\"/></form><br> <br><form action=\"http://cs.mcgill.ca/~ychen286/cgi-bin/transporter.py\" class=\"button\"><input type=\"hidden\" name=\"inventory\"value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"https://cs.mcgill.ca/~cbelis3/\"><input type=\"submit\" value=\"North\"/></form><form action=\"http://cs.mcgill.ca/~bcumin1/cgi-bin/transporter.py\" class=\"button\"><input type=\"hidden\" name=\"inventory\"value\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"https://cs.mcgill.ca/~cbelis3/\"><input type=\"submit\" value=\"West\"/></form><form action=\"http://cs.mcgill.ca/~ychen286/cgi-bin/transporter.py\" class=\"button\"><input type=\"hidden\" name=\"inventory\"value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"https://cs.mcgill.ca/~cbelis3/\"><input type=\"submit\" value=\"East\"/></form><form action=\"http://cs.mcgill.ca/~bcumin1/cgi-bin/transporter.py\" class=\"button\"><input type=\"hidden\" name=\"inventory\"value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"https://cs.mcgill.ca/~cbelis3/\"><input type=\"submit\" value=\"South\"/> </form></p></center></body></html>"; 
printf(page,aPlayer->manna,aPlayer->gold, aPlayer->manna,aPlayer->gold, aPlayer->manna,aPlayer->gold, aPlayer->manna, aPlayer->gold, aPlayer->manna, aPlayer->gold, aPlayer->manna,aPlayer->gold);
        return;
    
    
}
void playGame(player* aPlayer){
	printf("Content-Type:text/html\n\n");

	const char* pagetwo="<!doctype html><html><title>Tower of Hanoi</title><head><center><h1> Tower of Hanoi </h1></center></head><body><center><canvas id=\"TowerOfHanoi\" width=\"700\" height=\"300\" style=\"border:1px solid #000000;\"></canvas></center><script type=\"text/javascript\" src=\"./main.js\"></script><link rel=\"stylesheet\" href=\"./main.css\"/></link><center><input type=\"submit\" class=\"button\" value=\"Middle\" onclick=\"buttonOne()\"/><input type=\"submit\" class=\"button\" value=\"Right\" onclick=\"buttonTwo()\"/><input type=\"submit\" class=\"button\" value=\"Left\" onclick=\"buttonThree()\"/><input type=\"submit\" class=\"button\" value=\"Right\" onclick=\"buttonFour()\"/><input type=\"submit\" class=\"button\" value=\"Left\" onclick=\"buttonFive()\"/><input type=\"submit\" class=\"button\" value=\"Middle\" onclick=\"buttonSix()\"<br><br>";	
printf(pagetwo);
    return;
}


int play (char* cmd, int fromStack, int toStack)
{
    int ret;
    
    stack towers[3];
    
    for (int i=0; i<3; i++)
    {
        towers[i].size=0;
    }
    
    if (strcmp(cmd,"start")==0)
    {
        ret=initialiseGame(&towers[0]);
        
        if (ret==TRUE)
        {
            //printf("Game successfully initialised\n");
            //fflush(stdout);
            //write the game to file
            
            FILE* fp=fopen("towerInstance.txt","w");
            
            if (fp==NULL)
            {
                //printf("could not save the game to file\n");
                //fflush(stdout);
                return FALSE;
            }
            for (int i=0; i<3; i++)
            {
                node* temp=towers[i].top;
                int counter=towers[i].size;
                
                while (counter>0)
                {
                    //fprintf(fp,"%d ",temp->value);
                    //printf("%d ",temp->value);
                    temp=temp->previous;
                    counter--;
                }
               // fprintf(fp,"\n");
               // printf("\n");
            }
            fclose(fp);
            return TRUE;
        }
        else
        {
           // printf("There was a problem initialising the game\n");
            fflush(stdout);
            return FALSE;
        }
    }
    else if( strcmp(cmd, "exit")==0 )
    {
        ret=remove("towerInstance.txt");
        
        if (ret==0)
        {
           // printf("Game successfully exited\n");
           // fflush(stdout);
            return TRUE;
        }
        else
        {
           // printf("There was a problem deleting the game\n");
           // fflush(stdout);
            return FALSE;
        }
        
    }
    else if( strcmp(cmd, "move")==0 )
    {
        //get the towers from the file
        FILE* fp=fopen("towerInstance.txt","r");
        
        if (fp==NULL)
        {
            //printf("could not read the game from file\n");
            //fflush(stdout);
            return FALSE;
        }
        char c='\0';
        for (int i=0; i<3; i++)
        {
            stack readTo=newStack();
            
            while (c!='\n')
            {
                c=getc(fp);
                
                if (c>=48 && c<=56)
                {
                    push(atoi(&c), &readTo);
                }
            }
            while (readTo.size>0)
            {
                //printf("%d ",readTo.top->value);
                
                if (readTo.top->value<=0)
                {
                    break;
                }
                else
                {
                    int j=pop(&readTo).value;
                    push(j,&towers[i]);
                }
            }
            //printf("\n");
            c='\0';
            
        }
        fclose(fp);
        int ret;
        stack temp1=towers[fromStack];
        stack temp2=towers[toStack];
        ret=movePiece(&temp1, &temp2);
        towers[fromStack]=temp1;
        towers[toStack]=temp2;
        
        if (ret<0)
        {
            //piece was not moved successfully, return an error value
            return ret;
        }
        else
        {
            //check to see if the game has succeeded
            if (hasWon(&towers[2])==TRUE)
            {
                ret=remove("towerInstance.txt");
                
                if (ret==0)
                {
                   // printf("Game won, but game file was not delete\nd");
                    return 9;
                }
                else
                {
                   // printf("Game won and file successfully deleted\n");
                    return 9;
                }
            }
            else
            {
                //save to file, this overwrites any existing game
                //printf("Piece moved successfully\n");
                fflush(stdout);
                
                FILE* fp=fopen("towerInstance.txt","w");
                
                if (fp==NULL)
                {
                    //printf("could not save the game to file\n");
                    //fflush(stdout);
                    return FALSE;
                }
                for (int i=0; i<3; i++)
                {
                    node* temp=towers[i].top;
                    int counter=towers[i].size;
                    
                    while (counter>0)
                    {
                        //printf("%d ",temp->value);
                        //fprintf(fp,"%d ",temp->value);
                        counter--;
                        temp=temp->previous;
                    }
                    //printf("\n");
                    //fprintf(fp,"\n");
                }
                fclose(fp);
                return ((towers[toStack].top->value)*10+towers[toStack].size-1);
            }
        }
    }
    else
    {
        //printf("The command <<%s>> does not exist\n", cmd);
        fflush(stdout);
        return FALSE;
    }
}

stack newStack(void)
{
    stack ret;
    ret.size=0;
    
    return ret;
}
int isEmpty(stack* s)
{
    if (s->size==0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

node pop(stack* s)
{
    node ret=*s->top;
    if (ret.previous)
    {
        s->top=ret.previous;
    }
    else
    {
        s->top=(node*)malloc(sizeof(node));
    }
    s->size--;
    
    ret.previous=NULL;
    return ret;
    
}
node peek(stack* s)
{
    return *s->top;
}
void push(int val, stack* s)
{
    node* n=(node*)(malloc(sizeof(node)));
    n->value=val;
    
    if (s->top==NULL)
    {
        s->top = n;
        n->previous = NULL;
    }
    else
    {
        n->previous=s->top;
        s->top= n;
    }
    s->size++;
}
int initialiseGame(stack* s)
{
    for (int i=8; i>0; i--)
    {
        push (i, s);
    }
    return TRUE;
}
int movePiece(stack* s1, stack* s2)
{
    if (s1->size==0)
    {
        //printf("There are no pieces on this peg\n");
        //fflush(stdout);
        return -1;
    }
    else if (s2->top && s1->top->value > s2->top->value)
    {
        //printf("Cannot put a larger piece onto a smaller one\n");
        //printf("moving %d onto %d!\n", s1->top->value, s2->top->value);
        //fflush(stdout);
        return -1;
    }
    else
    {
        //this move is valid, pop from stackFrom and push that node to StackTo
        push(pop(s1).value, s2);
        return TRUE;
    }
}
int hasWon(stack* s)
{
    if (!s->top)
    {
        //printf("The victory stack is empty!\n");
        return FALSE;
    }
    node temp=*s->top;
    int counter=0;
    
    while (temp.previous!=NULL)
    {
        if (temp.value!=counter++)
        {
            return FALSE;
        }
        temp=getPrevious(&temp);
    }
    if (counter==7)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
node getPrevious(node* n)
{
    return *n->previous;
}
int drop (player* aPlayer, room* theRoom, int someGold)
{
    //player drops the gold if they have enough
    if (aPlayer->gold-someGold>=0)
    {
        setPlayerGold(aPlayer, aPlayer->gold-someGold);
        setRoomGold(theRoom, theRoom->gold+someGold);
    }
    //player does not have enough gold to perform the action
    else
    {
       // printf("You only have %d gold, you cannot drop %d gold\n",aPlayer->gold, someGold);
        fflush(stdout);
        return FALSE;
    }
    //takes into account that fractional manna cannot be given out, and refunds the player the extra gold
    if (someGold%2!=0)
    {
        //printf("Beware the conversion rate...the rate is 2 gold for 1 manna\n");
        //printf("%d is not a multiple of 2, I am refunding you 1 gold\n", someGold);
        //fflush(stdout);
        setRoomGold(theRoom, theRoom->gold-1);
        setPlayerGold(aPlayer, aPlayer->gold+1);
        someGold--;
    }
    aPlayer->manna=aPlayer->manna+someGold/2;
    return TRUE;
}
int parseError(int errorCode)
{
    switch (errorCode)
    {
        case TRUE:case FALSE:
            //printf("Valid state\n");
            //fflush(stdout);
            return TRUE;
        case -1:
            //printf("The room does not exist, or cannot be opened\n");
            //fflush(stdout);
            return FALSE;
        case -2:
            //printf("The new room could not be saved to file\n");
            //fflush(stdout);
            return FALSE;
        case -3:
            //printf("The room data could not be loaded\n");
            //fflush(stdout);
            return FALSE;
        default:
            //printf("Error not listed\n");
            //fflush(stdout);
            return FALSE;
    }
}
char* addToArray(char* s)
{
    char* temp=malloc(strlen(s));
    strcpy(temp,s);
    return temp;
}
char* getRoomName(room* theRoom)
{
    return theRoom->name;
}

void setRoomManna(room* theRoom, int aManna)
{
    theRoom->manna=aManna;
}
int getRoomManna(room* theRoom)
{
    return theRoom->manna;
}

void setRoomGold(room* theRoom, int aGold)
{
    theRoom->gold=aGold;
}
int getRoomGold(room* theRoom)
{
    return theRoom->gold;
}
void setRoomOccupancy(room* theRoom, int Occupancy)
{
    theRoom->isOccupied=Occupancy;
}
int getRoomOccupancy(room* theRoom)
{
    return theRoom->isOccupied;
}
room initialiseRoom(void)
{
    //initialises a blank room, then passes gives it values from file
    room theRoom;
    
    theRoom.gold=0;
    theRoom.manna=0;
    theRoom.isOccupied=0;
    
    int success=readRoomFromFile(&theRoom);
    
    if (success==TRUE)
        //successfully read from file, do nothing
    {
        ;
    }
    //did not read from file successfully, return a room with no resources and an improper occupied state to signify the error
    else
    {
        theRoom.gold=0;
        theRoom.manna=0;
        theRoom.isOccupied=success;
    }
    return theRoom;
}
room createNewRoom(void)
{
    //run this function only if the room is either deleted, or does not exist, is used on startup only
    room theRoom;
    
    theRoom.gold=10;
    theRoom.manna=10;
    theRoom.isOccupied=0;
    int ret=saveToFile(&theRoom);
    
    if (ret==TRUE)
    {
        return theRoom;
    }
    else
    {
        theRoom.isOccupied=-5;
        return theRoom;
    }
}
int saveToFile(room* theRoom)
{
    FILE *fp;
    fp=fopen("resources.csv", "w");
    if (fp==NULL)
    {
        //printf("There was an error creating the resource.txt file");
        //fflush(stdout);
        return FALSE;
    }
    
    int ret=fprintf(fp, "%d,%d,%d", theRoom->gold, theRoom->manna, theRoom->isOccupied);
    
    if (ret<0)
    {
       // printf("There was an error saving the room to the resource.txt file");
       // fflush(stdout);
        return FALSE;
    }
    fclose(fp);
    return TRUE;
}

int readRoomFromFile(room* theRoom)
{
    //looks for the file in the current directory
    FILE *fp=fopen("resources.csv", "r+");
    
    //if there is an error in opening the file
    if (fp==NULL)
    {
        //printf("The file either does not exist, or cannot be opened.\n");
        //printf("Please ensure that the file is in the same directory as the C executable\n");
        //fflush(stdout);
        theRoom->isOccupied=-1;
        return FALSE;
    }
    //there should only be one scanf needed to pass resources to the room, since there is only one room
    char* temp=malloc(10);
    
    int ret=fscanf(fp, "%s", temp);
    
    //failed to read all the values
    if (ret<0)
    {
      //  printf("Failure to read the correct number of values from file, the room data may be corrupted");
      //  fflush(stdout);
        return FALSE;
    }
    int tempArray[3];
    char* tmp=malloc(10);
    int j=0;
    int k=0;
    
    for (int i=0; i<strlen(temp)+1; i++)
    {
        if (temp[i]!=',' && temp[i]!='\0')
        {
            tmp[k++]=temp[i];
        }
        else
        {
            tempArray[j++]=atoi(tmp);
            memset(tmp,'\0',k);
            k=0;
        }
    }
    
    if( j==3)
    {
        //variables are properly assigned
        theRoom->gold=tempArray[0];
        theRoom->manna=tempArray[1];
        theRoom->isOccupied=tempArray[2];
        return TRUE;
    }
    else
    {
        //there was a problem reading the file
       // printf("The room could not be read");
        return FALSE;
    }
}

//simple getters and setters for a player
char* getPlayerUsername(player* aPlayer)
{
    return aPlayer->username;
}
void setPlayerUsername(player* aPlayer, char* aUsername)
{
    aPlayer->username=aUsername;
}

int getPlayerManna(player* aPlayer)
{
    return aPlayer->manna;
}
void setPlayerManna(player* aPlayer, int aManna)
{
    aPlayer->manna=aManna;
}

int getPlayerGold(player* aPlayer)
{
    return aPlayer->gold;
}
void setPlayerGold(player*aPlayer, int aGold)
{
    aPlayer->gold=aGold;
}

struct player constructNewPlayer(char* aUsername, int aManna, int aGold)
{
    player aPlayer;
    
    aPlayer.username=aUsername;
    aPlayer.manna=aManna;
    aPlayer.gold=aGold;
    
    
    return aPlayer;
}
void removePlayer(player* aPlayer)
{
    aPlayer->username=NULL;
    aPlayer->manna=NULL;
    aPlayer->gold=NULL;
    free(aPlayer);
}


