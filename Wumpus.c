/*

AUTHOR: Sai Tarun Yellamraju
Description: This is my Wumpus World Solver.
Each of the the numbers from 1 to 12 are different inferences for the Agent who 
will try to collect the Gold in the Maze and Come back. The array a1[][] denotes 
the original grid which is not visble to the Agent. The Array a[][] denotes the 
grid which is percieved by the Agent till that point. The Program in short words 
basically tries to avoid the Pits and Wumpus; and collects the Gold comes back to
the start position. To change the maze, you can change the a1[][] matrix.

0  ==  SAFE
1  ==  WALL
2  ==  WUMPUS
3  ==  STENCH
4  ==  PIT
5  ==  BREEZE
6  ==  GOLD
7  ==  GLITTER
8  ==  PLAYER
9  ==  VISITED
10 ==  BREEZE AND STENCH
11 ==  BREEZE AND GLITTER
12 ==  STENCH AND GLITTER

*/
#include<stdio.h>
#include<stdlib.h>
int a1[6][6]={
               {1,1, 1,1,1,1},
               {1,3, 0,7,6,1},
               {1,2, 10,0,7,1},
               {1,10,4,5,0,1},
               {1,8, 5,0,0,1},
               {1,1, 1,1,1,1}
            };
/*int a1[6][6]={
               {1,1,1,1,1,1},
               {1,2,0,0,7,1},
               {1,2,3,7,6,1},
               {1,3,0,0,7,1},
               {1,8,0,0,0,1},
               {1,1,1,1,1,1}
            };*/
int a[6][6]={
               {1,1,1,1,1,1},
               {1,0,0,0,0,1},
               {1,0,0,0,0,1},
               {1,0,0,0,0,1},
               {1,8,0,0,0,1},
               {1,1,1,1,1,1}
            };            
int stack[100],direc=0,z=0,b=0,w=0,flag=9,flag1=0,g=0,p=0;
void analyze();
void print();
void forward();
void right();
void left();
void back();
void Success();
void FindWumpus();
void FindPit();
void game();
void Glitter();
void returntostart();
void action();
void print()
{
	getchar();
	system("clear");
	int i=0,j=0;
	for(i=0;i<6;++i)
	{
		for(j=0;j<6;++j)
		{
			switch(a[i][j])
			{
				case 1: printf("  #  ");
					break;
				case 8: printf("  A  ");
					break;
				case 2:	printf("  W  ");
					break;
				case 3: printf("  S  ");
					break;
				case 4: printf("  P  ");
					break;
				case 5: printf("  B  ");
					break;
				case 6:	printf("  G  ");
					break;
				case 7: printf("  L  ");
					break;
				case 9:	printf("     ");
					break;
				case 10:printf(" S B ");
					break;
				case 11:printf(" L B ");
					break;
				case 12:printf(" L S ");
					break;				
				default:printf("  ?  ");		
			}
		}
		printf("\n\n");
	}
	printf("DIRECTION: ");
	switch(direc)
	{
		case 0: printf("UP\n");
			break;
		case 1:  printf("RIGHT\n");
			break;
		case 2:  printf("DOWN\n");
			break;
		case 3:  printf("LEFT\n");
			break;	
	}
}
void action()
{
	int f,i=stack[z]/6,j=(stack[z]-1)%6;
	int z1=z;
	if(direc==0)
	{
		if(a[i-1][j]!=1 && a[i-1][j]!=4)
		{
			flag=a1[i-1][j];
			a[i-1][j]=8;
			print();
			if(flag==0|| flag==8)
				a[i-1][j]=9;
			else
				a[i-1][j]=flag;
			for(z1=z-1;z1>=0;--z1)
			{
				if(stack[z1]==(i-1)*6+(j+1))
				{
					z=z1;
				}
			}	
			stack[z+1]=(i)*6+(j+1)-6;
			++z;	
		}		
		if(a[i-1][j]==4)
		{
			if(i==2)
			{
				right();
				f=a1[stack[z]/6][(stack[z]-1)%6];
				if(f==3)
					analyze();
				left();
				f=a1[stack[z]/6][(stack[z]-1)%6];
				if(f==3)
					analyze();
				direc=2;	
				b+=2;			
			}
			else if(j==1)
			{
				right();
				f=a1[stack[z]/6][(stack[z]-1)%6];
				if(f==3)
					analyze();
				left();
				f=a1[stack[z]/6][(stack[z]-1)%6];
				if(f==3)
					analyze();
				forward();
				f=a1[stack[z]/6][(stack[z]-1)%6];
				if(f==3)
					analyze();
				left();
				direc=0;	
				
			}
			else
			{
				left();
				right();
				forward();
				right();
				direc=0;
			}
		}		
	}
	else if(direc==1)
	{
		if(a[i][j+1]!=1 && a[i][j+1]!=4)
		{
			flag=a1[i][j+1];
			a[i][j+1]=8;
			print();
			if(flag==0|| flag==8)
				a[i][j+1]=9;
			else
				a[i][j+1]=flag;
			for(z1=z-1;z1>=0;--z1)
			{
				if(stack[z1]==(i)*6+(j+2))
				{
					z=z1;
				}
			}	
			stack[z+1]=(i)*6+(j+1)+1;
			++z;
		}
		if(a[i][j+1]==4)
		{
			direc=0;
			forward();
			right();
			direc=0;
			++b;
			direc=0;
		}
	}
	else if(direc==2)
	{
		if(a[i+1][j]!=1 && a[i+1][j]!=4)
		{
			flag=a1[i+1][j];
			a[i+1][j]=8;
			print();
			if(flag==0 || flag==8)
				a[i+1][j]=9;
			else
				a[i+1][j]=flag;
			for(z1=z-1;z1>=0;--z1)
			{
				if(stack[z1]==(i+1)*6+(j+1))
				{
					z=z1;
				}
			}	
			stack[z+1]=(i)*6+(j+1)+6;
			++z;			
		}
		if(a[i+1][j]==4)
		{
			if(i==4)
			{
				left();
				f=a1[stack[z]/6][(stack[z]-1)%6];
				if(f==3)
					analyze();
				right();
				f=a1[stack[z]/6][(stack[z]-1)%6];
				if(f==3)
					analyze();
				direc=0;
				b+=2;		
			}
			else
			{
				right();
				left();
				forward();
				left();
				direc=2;
			}	
		}
	}
	else if(direc==3)
	{
		if(a[i][j-1]!=1 && a[i][j-1]!=4)
		{
			flag=a1[i][j-1];
			a[i][j-1]=8;
			print();
			if(flag==0|| flag==8)
				a[i][j-1]=9;
			else
				a[i][j-1]=flag;
			for(z1=z-1;z1>=0;--z1)
			{
				if(stack[z1]==(i)*6+(j))
				{
					z=z1;
				}
			}	
			stack[z+1]=(i)*6+(j+1)-1;
			++z;	
		}
	}
}
void forward()
{
	direc%=4;
	action();
}
void right()
{
	direc+=1;
	direc%=4;
	action();
}
void back()
{
	direc+=2;
	direc%=4;
	action();
}
void left()
{	
	direc+=3;
	direc%=4;
	action();
}
void Success(int f)
{
	int i=stack[z]/6,j=(stack[z]-1)%6;
	if(a1[i][j]==3)
	{
		direc=flag1;
		a[i][j]=8;		
		print();
		printf("\nSTENCH \nACTION: SHOOT");
		i=0,j=0;
		for(i=0;i<6;++i)
			for(j=0;j<6;++j)
			{
				if(a1[i][j]==2 || a1[i][j]==3)
				{
					a1[i][j]=9;	
					a[i][j]=9;
				}	
			}
		w=1;	
	} 
	if(a1[i][j]==10 && f==3)
	{
		direc=flag1;
		a[i][j]=8;		
		print();
		printf("\nBREEZE \nSTENCH \nACTION: SHOOT");
		i=0,j=0;
		for(i=0;i<6;++i)
			for(j=0;j<6;++j)
			{
				if(a1[i][j]==2 || a1[i][j]==3)
				{
					a1[i][j]=9;	
					a[i][j]=9;
				}	
			}
		w=1;		
	}
	if(a1[i][j]==5 && f==10)
	{
		for(i=0;i<6;++i)
			for(j=0;j<6;++j)
			{
				if(a1[i][j]==5 || a1[i][j]==4 )
				{	
					a[i][j]=a1[i][j];
				}	
			}
		p=1;	
		back();
		right();
		i=stack[z]/6,j=(stack[z]-1)%6;
		direc=flag1;
		a[i][j]=8;		
		print();
		a[i][j]=9;
		printf("\nSTENCH \nBREEZE \nACTION: SHOOT");
		i=0,j=0;
		for(i=0;i<6;++i)
			for(j=0;j<6;++j)
			{
				if(a1[i][j]==2 || a1[i][j]==3)
				{
					a1[i][j]=9;	
					a[i][j]=9;
				}
				if(a1[i][j]==10)
				{
					a1[i][j]=5;	
					a[i][j]=5;
				}	
			}
		w=1;	
	}
}
void FindWumpus(int f)
{
	flag1=direc;
	back();
	left();	
	Success(f);
	if(w==0)
	{
		back();
		int flag2=stack[z];
		forward();
		if(flag2!=stack[z])
		{
			Success(f);
			right();	
			left();
		}
		else
		{
			right();
			Success(f);	
		}	
	}
	else if(p!=1)
	{
		left();
		right();
	}
}
void returntostart()
{
	int i,j;
	for(i=0;i<6;++i)
	{
		for(j=0;j<6;++j)
		{
			if(a1[i][j]==7 || a1[i][j]==6)
			{
				a[i][j]=9;
				a1[i][j]=9;
			}
			if(a1[i][j]==11)
			{
				a1[i][j]=5;
				a[i][j]=a1[i][j];
			}
			if(a1[i][j]==12)
			{
				a1[i][j]=3;
				a[i][j]=a1[i][j];
			}
		}
	}
	int k=0;
	for(k=z;k>=1 && stack[k-1]!=stack[0];--k)
	{
		if(stack[k]-stack[k-1]==(1))
			direc=3;
		else if(stack[k]-stack[k-1]==(-1))
			direc=1;
		else if(stack[k]-stack[k-1]==6)
			direc=0;
		else
			direc=2;
		action();
	}
	forward();
}
void glitter(int f1)
{
	if(f1==7)
		printf("\nGLITTER");
	else if(f1==12)
		printf("\nGLITTER \nSTENCH");
	else
	{
		printf("\nGLITTER \nBREEEZE");
	}
	int i,j;
	if(f1==7)
	{
		if(b%4<2)
		{
			int flag=stack[z];    
			right();
			int f=a1[stack[z]/6][(stack[z]-1)%6];
			if(f==6)
			{
				g=1;
				for(i=0;i<6;++i)
				{
					for(j=0;j<6;++j)
					{
						if(a1[i][j]==7 )
						{
							a[i][j]=7;
						}
					}
				}	
				print();
				printf("GOLD");
				returntostart();
			}
			else
			{
				back();
				printf("\nGLITTER");
				right();
				g=1;
				printf("GOLD");
				returntostart();
			}
		}
		else if(b%4<4)
		{
			int flag=stack[z];
			left();
			int f=a1[stack[z]/6][(stack[z]-1)%6];
			if(f==6)
			{
				g=1;
				printf("GOLD");
				returntostart();
			}
			else
			{
				back();
				printf("\nGLITTER");
				left();
				g=1;
				printf("GOLD");
				returntostart();
			}
		
		}
	}
	else 
	{
		int i=stack[z]/6,j=(stack[z]-1)%6;
		if(j==1)
		{
			back();
			left();
			int f=a1[stack[z]/6][(stack[z]-1)%6];
			if(f==7)
			{
				left();
				printf("\nGOLD");
				g=1;
				returntostart();			
			}
			else
			{
				back();
				right();
				forward();
				printf("\nGOLD");
				g=1;
				returntostart();
			}
		}
		else
		{
			if(b%4<2)
			{
				right();
				printf("\nGOLD");
				g=1;
				returntostart();
			}
			else
			{
				left();
				printf("\nGOLD");
				g=1;
				returntostart();
			}
		}
	}	
}
void FindPit()
{
	int f,flag1=direc;
	int i,j=(stack[z]-1)%6;
	if(j==0)
	{
		back();
		left();
		f=a1[stack[z]/6][(stack[z]-1)%6];
		if(f==5)
		{
			for(i=0;i<6;++i)
				for(j=0;j<6;++j)
				{
					if(a1[i][j]==5 || a1[i][j]==4)
						a[i][j]=a1[i][j];
				}
				p=1;
				print();
				back();
				right();
				direc=flag1;
		}
		else
		{
			back();
			right();
			direc=flag1;
			for(i=0;i<6;++i)
				for(j=0;j<6;++j)
				{
					if(a1[i][j]==5 || a1[i][j]==4)
						a[i][j]=a1[i][j];
				}
			p=1;
		}			
	}
	else
	{
		if(p==0)
		{
			p=1;	
			for(i=0;i<6;++i)
				for(j=0;j<6;++j)
				{
					if(a1[i][j]==5 || a1[i][j]==4)
						a[i][j]=a1[i][j];
				}
		}	
		print();
	}
}
void analyze()
{
	int f=a1[stack[z]/6][(stack[z]-1)%6];
	if(f==8 || f==0 || f==9 || (f==5 && p==1))
	{
		flag1=stack[z];
		if(b%2==0)
			forward();
		else
		{
			if(b%4==1)
			{
				direc+=1;
				direc%=4;
				forward();
				++b;
			}	
			else
			{
				direc+=3;
				direc%=4;
				forward();
				++b;
			}	
		}	
		if(flag1==stack[z])
		{
			if(b%4<2)
			{
				direc+=1;
				direc%=4;
				forward();
				++b;
			}	
			else
			{
				direc+=3;
				direc%=4;
				forward();
				++b;
			}	
		}
	}
	if(f==6)
	{
		g=1;
		int i,j;
		for(i=0;i<6;++i)
		{
			for(j=0;j<6;++j)
			{
				if(a1[i][j]==7 )
				{
					a[i][j]=7;
				}
			}
		}	
		//print();
		printf("GOLD");
		returntostart();
	}
	if(f==7 || f==12 || f==11)
	{
		glitter(f);
	}
	else if(f==3)
	{
		printf("STENCH");
		FindWumpus(f);	
	}
	else if(f==5 && p==0)
	{
		printf("\nBREEZE");
		FindPit();	
	}
	if(f==2)
	{
		g=-1;
		printf("\nWumpus");
	}
	if(f==4)
	{
		g=2;
		printf("\nStench");
	}
	if(f==10)
	{
		printf("\nSTENCH \nBREEZE");
		FindWumpus(f);
	}
}
void game()
{
	stack[0]=26;
	z=0;
	while(g==0)
	{
		if(z==0)
		{
			a[stack[z]/6][(stack[z]-1)%6]=8;		
			print(); 
			a[stack[z]/6][(stack[z]-1)%6]=9;
		}	
		analyze();
	}
}
int main()
{
	system("clear");
	game();
	if(g==-1)
		printf("\nThe Wumpus Has Eaten You. You Have Lost The Game.\n");
	else if(g==1)
		printf("\nCongratulations! You Have Won The Game!");
	else
		printf("\nYou Have Fallen into The Pit. Game Over.\n");	
	return 0;
}
