#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include "SNAKEGAME.hpp"

//  array arr(2-dimensional) is used to track the position of the snake coordinates
//  LEN is initial length of the snake
//  x,y is used for present head position
//  xx,yy is used to represent the position of food
//  w,a,s,d(up,left,down,right) respectively are used to play the snake game
//  time is used to represent the delay i.e., how fast it should move after some time
//  ch1,ch2 are used to track the present and previous charactars used by the player to play game
//  graphics is used to remove cursor from the screen

int game()
{
    //  to clear the screen
    clrscr();
    int gd = DETECT,gm;
    //detectgraph(&gd,&gm);
    //initgraph(&gd,&gm,"C:\TC\BGI");

    //  initialization of position of food and snake , length of snake initially
    int i=0, j=0, x=8, y=5, arr[MAAX][2], xx=50, yy=15, flag=0, len=LEN, time=0;
    char ch1 = 'd', ch2 = 'd';

    //  used to display boundary on left and right of a screen
    for(i=1;i<=MAXY;i++)
    {
        gotoxy(1,i);
        cout<<"@";
        gotoxy(MAXX,i);
        cout<<"@";
    }
    //  used to display boundary on top and bottom of a screen
    for(i=1;i<=MAXX;i++)
    {
        gotoxy(i,1);
        cout<<"@";
        gotoxy(i,MAXY);
        cout<<"@";
    }
    //  initialization of position of snake in array
    for (i=0; i<len; i++)
    {
        arr[i][0] = x++;
        arr[i][1] = y;
    }
    while(1)
    {
        //  used to check the boundary whether snake hit it or not
        if(x==1 || x==MAXX || y==1 || y==MAXY)
	       break;
	    //  check whether snake is going to hit itself
        for(i=0;i<len-1;i++)
	        if(arr[i-1][0]==x && arr[i-1][1]==y)
	        {
	            j = 1;
	            break;
            }
        if(j==1)
	        break;
	    //  keeping track of previous move
        ch2 = ch1;
        //  removing the tail of snake
        gotoxy(arr[0][0],arr[0][1]);
        cout<<" ";
        //  shifting the position of snake
        for(i=0; i<len-1; i++)
        {
	        arr[i][0] = arr[i+1][0];
	        arr[i][1] = arr[i+1][1];
        }
        arr[i][0] = x;
        arr[i][1] = y;
        //  displaying the head of snake
        gotoxy(arr[len-1][0],arr[len-1][1]);
        cout<<"*";
        //  checking the coordinates of food
        if(xx==arr[len-1][0] && yy==arr[len-1][1])
	        flag = 1;
	    //  if it is on snake change the coordinates of food
        if(flag)
        {
            //  using random number to find coordinates
            xx = rand()%MAXX+1;
            yy = rand()%MAXY+1;
            for(i=0;i<len;i++)
            {
	            if(xx==arr[i][0] && yy==arr[i][1])
	            {
	                //  if again present on the snake reset to check again and change the coordinates
	                xx++;
	                yy++;
	                i=0;
		        }
	            else if(xx==1 || xx==MAXX || yy==1 || yy==MAXY)
		        {
		            //  if present on boundaries change the coordinates
	                xx = rand()%MAXX+1;
		            yy = rand()%MAXY+1;
			    }
	            else
	                break;
            }
            //  increment the length of snake
            len++;
            flag=0;
        }
        //  display food
        gotoxy(xx,yy);
        cout<<"$";
        arr[len][0] = xx;
        arr[len][1] = yy;
        //  according to the length of snake , speed of snake is decided
        delay(time);
        if(len<10)
	        time = 200;
        else if(len<15)
	        time = 100;
        else if(len<20)
	        time = 50;
        else
	        time = 20;
	    //  accept input from player i.e.,keyboard was hit
        if(kbhit())
		    ch1 = (char)getch();
		//  according to the charactar decide the move
        switch(ch1)
        {
            //  up
	        case 'w' : //   check the previous movement of snake and there should not be any backward movement
	                   if(ch2=='s')
			           {
		                    ch1 = 's';
		                    y++;
		                    break;
		               }
		                    y--;
                		    break;
            //  left
	        case 'a' : //   check the previous movement of snake and there should not be any backward movement
	                   if(ch2=='d')
			           {
		                    ch1 = 'd';
		                    x++;
		                    break;
		               }
		                    x--;
		                    break;
		    //  down
	        case 's' : //   check the previous movement of snake and there should not be any backward movement
	                   if(ch2=='w')
			           {
		                    ch1 = 'w';
		                    y--;
		                    break;
		               }
		                    y++;
		                    break;
		    //  right
            case 'd' : //   check the previous movement of snake and there should not be any backward movement
                       if(ch2=='a')
			           {
		                    ch1 = 'a';
		                    x--;
		                    break;
		               }
		                    x++;
		                    break;
	        default: // if valid charactar is not hit, snake should not change its motion
	                 ch1 = ch2;
	                 // according to the previous charactar it should continue its motion
                     switch(ch2)
			         {
			            case 'w' : y--;
				                   break;
                        case 'a' : x--;
				                   break;
			            case 's' : y++;
				                   break;
			            case 'd' : x++;
				                   break;
			            default  : break;
				     }
	    }
   }
   //   clear screen
   clrscr();
   cout<<"Your SCORE is: "<<len-1;
   //   wait for user to press any key and see his score
   getch();
   return 0;
}

int main()
{
    char choice;
    while(1)
    {
        //  clear screen
        clrscr();
        //delay(10);
        //  display menu to player
        cout<<"choose one option:\n\n";
        cout<<"1.Start game\n";
        cout<<"2.Quit\n\n";
        cout<<"Enter choice:";
        cin>>choice;
        switch(choice)
        {
            case '1' : game();
                       break;
            case '2' : return 0;
            default  : gotoxy(8,2);
	                   cout<<"wrong choice\n\n";
	                   break;
        }
    }
    //  wait for player
    getch();
    return 0;
}
