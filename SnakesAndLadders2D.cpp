#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<gl/glut.h>
#include<SOIL.h>
#include<Windows.h>

GLint ww=1000,wh=600,winw=1000,winh=600;
GLuint board,p1,p2,roll,df1,df2,df3,df4,df5,df6,p1w,p2w,retry,quit;
GLint turn=1,DF=1,dface,winner=0;
GLfloat x1=700,x2=770,y1=270,y2=340;
GLint p1x=120,p1y=120;
GLint p2x=125,p2y=120;
GLint b1=1,b2=1;
GLint endgame=0;
void LoadTexture(char *FileName,GLuint *ID)
{
	(*ID) = SOIL_load_OGL_texture(FileName,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);	
	if((*ID)==0)
	   	return;
	   	//printf("Success\n");
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}
void init()
{
	srand(time(NULL));
	glPointSize(12.0);
	glClearColor(0,0,0,0);
	glEnable(GL_TEXTURE_2D);
	char str1[]="snl.jpg";
	LoadTexture(str1,&board);
	char str2[]="p1.png";
	LoadTexture(str2,&p1);
	char str3[]="p2.png";
	LoadTexture(str3,&p2);
	char str4[]="Roll.png";
	LoadTexture(str4,&roll);
	char str5[]="Diceface1.png";
	LoadTexture(str5,&df1);
	char str6[]="Diceface2.png";
	LoadTexture(str6,&df2);
	char str7[]="Diceface3.png";
	LoadTexture(str7,&df3);
	char str8[]="Diceface4.png";
	LoadTexture(str8,&df4);
	char str9[]="Diceface5.png";
	LoadTexture(str9,&df5);
	char str10[]="Diceface6.png";
	LoadTexture(str10,&df6);
	char str11[]="Player1Wins.png";
	LoadTexture(str11,&p1w);
	char str12[]="Player2Wins.png";
	LoadTexture(str12,&p2w);
	char str13[]="retry.png";
	LoadTexture(str13,&retry);
	char str14[]="quit.png";
	LoadTexture(str14,&quit);
}
void createBoard()
{
	//glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D,board);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(100,100);
	glTexCoord2f(0,1);
	glVertex2f(100,500);
	glTexCoord2f(1,1);
	glVertex2f(500,500);
	glTexCoord2f(1,0);
	glVertex2f(500,100);
	glEnd();
//	printf("Hello\n");
}
void createText()
{
	if(turn%2==1)
	glBindTexture(GL_TEXTURE_2D,p1);
	else
	glBindTexture(GL_TEXTURE_2D,p2);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,1.0f);
	glVertex2f(650,480);
	glTexCoord2f(0.0f,0.0f);
	glVertex2f(650,420);
	glTexCoord2f(1.0f,0.0f);
	glVertex2f(850,420);
	glTexCoord2f(1.0f,1.1f);
	glVertex2f(850,480);
	glEnd();
}
void createDice()
{
	glBindTexture(GL_TEXTURE_2D,roll);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,1.0);
	glVertex2f(700,340);
	glTexCoord2f(0.0,0.0);
	glVertex2f(700,270);
	glTexCoord2f(1.0,0.0);
	glVertex2f(770,270);
	glTexCoord2f(1.0,1.0);
	glVertex2f(770,340);
	glEnd();
	switch(DF)
	{
		case 1:	glBindTexture(GL_TEXTURE_2D,df1);
		break;
		case 2:	glBindTexture(GL_TEXTURE_2D,df2);
		break;
		case 3:	glBindTexture(GL_TEXTURE_2D,df3);
		break;
		case 4:	glBindTexture(GL_TEXTURE_2D,df4);
		break;
		case 5:	glBindTexture(GL_TEXTURE_2D,df5);
		break;
		case 0:	glBindTexture(GL_TEXTURE_2D,df6);
		break;
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,1.0);
	glVertex2f(687.5,200);
	glTexCoord2f(1.0,1.0);
	glVertex2f(787.5,200);
	glTexCoord2f(1.0,0.0);
	glVertex2f(787.5,110);
	glTexCoord2f(0.0,0.0);
	glVertex2f(687.5,110);
	glEnd();
}
void createPins()
{
	 glDisable(GL_TEXTURE_2D);
     glBegin(GL_POINTS);
     glColor3f(1.0,0.0,0.0);
     glVertex2i(p1x,p1y);
     glColor3f(0.0,0.0,0.0);
     glVertex2i(p2x,p2y);
     glEnd();
     glEnable(GL_TEXTURE_2D);
}
void end()
{
	endgame=1;
	//printf("%d\n",winner);
	Sleep(2*1000);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	if(winner==1)
	{
		glBindTexture(GL_TEXTURE_2D,p1w);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D,p2w);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex2i(700,500);
	glTexCoord2f(0,1);
	glVertex2i(300,500);
	glTexCoord2f(0,0);
	glVertex2i(300,420);
	glTexCoord2f(1,0);
	glVertex2i(700,420);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,retry);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2i(100,200);
	glTexCoord2f(0,0);
	glVertex2i(100,140);
	glTexCoord2f(1,0);
	glVertex2i(300,140);
	glTexCoord2f(1,1);
	glVertex2i(300,200);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,quit);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2i(700,200);
	glTexCoord2f(0,0);
	glVertex2i(700,140);
	glTexCoord2f(1,0);
	glVertex2i(900,140);
	glTexCoord2f(1,1);
	glVertex2i(900,200);
	glEnd();
	glutSwapBuffers();
	/*glFlush();
	glutSwapBuffers();*/
}
void display()
{
	if(endgame==0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		createBoard();
		createText();
		createDice();
		createPins();
		glutSwapBuffers();
	}
	else
	{
		end();
	}
}
int checkladder(int box)
{
	int res;
	switch(box)
	{
		case 3:res=48;
		break;
		case 6:res=21;
		break;
		case 20:res=50;
		break;
		case 36:res=19;
		break;
		case 63:res=32;
		break;
		case 68:res=30;
		break;
		default:res=0;
	}
	return res;
}
int checksnake(int box)
{
	int res;
	switch(box)
	{
		case 25:res=20;
		break;
		case 34:res=33;
		break;
		case 47:res=28;
		break;
		case 65:res=13;
		break;
		case 87:res=30;
		break;
		case 91:res=30;
		break;
		case 99:res=30;
		break;
		default:res=0;
	}
	return res;
}
void move()
{
	//printf("%d\n",dface);
	if(turn%2==1)
	{
		b1+=dface;
		if(b1>100)
		{
			b1-=dface;
			turn++;
			display();
			return;
		}
		while((dface!=0)&&(p1x+40<500))
		{
			p1x+=40;
			dface--;
		}
		if(dface!=0)
		{
			p1y+=40;
			p1x=120;
			dface--;
		}
		while(dface!=0)
		{
			p1x+=40;
			dface--;
		}
		int x=checkladder(b1);
		if(x!=0)
		{
			dface=x;
			b1+=dface;
			int upw=dface/10;
			dface=dface%10;
			while(upw!=0)
			{
				p1y+=40;
				upw--;
			}
			while((dface!=0)&&(p1x+40<500))
			{
				p1x+=40;
				dface--;
			}
			if(dface!=0)
			{
				p1y+=40;
				p1x=120;
				dface--;
			}
			while(dface!=0)
			{
				p1x+=40;
				dface--;
			}	
		}
		x=checksnake(b1);
		if(x!=0)
		{
			b1-=x;
			dface=x;
			int downw=dface/10;
			dface=dface%10;
			while(downw!=0)
			{
				p1y-=40;
				downw--;
			}
			while((dface!=0)&&(p1x-40>100))
			{
				p1x-=40;
				dface--;
			}
			if(dface!=0)
			{
				p1y-=40;
				p1x=480;
				dface--;
			}
			while(dface!=0)
			{
				p1x-=40;
				dface--;
			}
		}
		turn++;
	}
	else
	{
		b2+=dface;
		if(b2>100)
		{
			b2-=dface;
			turn++;
			display();
			return;
		}
		while((dface!=0)&&(p2x+40<500))
		{
			p2x+=40;
			dface--;
		}
		if(dface!=0)
		{
			p2y+=40;
			p2x=125;
			dface--;
		}
		while(dface!=0)
		{
			p2x+=40;
			dface--;
		}
		int x=checkladder(b2);
		if(x!=0)
		{
			dface=x;
			b2+=dface;
			int upw=dface/10;
			dface=dface%10;
			while(upw!=0)
			{
				p2y+=40;
				upw--;
			}
			while((dface!=0)&&(p2x+40<500))
			{
				p2x+=40;
				dface--;
			}
			if(dface!=0)
			{
				p2y+=40;
				p2x=125;
				dface--;
			}
			while(dface!=0)
			{
				p2x+=40;
				dface--;
			}
		}
		x=checksnake(b2);
		if(x!=0)
		{
			b2-=x;
			dface=x;
			int downw=dface/10;
			dface=dface%10;
			while(downw!=0)
			{
				p2y-=40;
				downw--;
			}
			while((dface!=0)&&(p2x-40>100))
			{
				p2x-=40;
				dface--;
			}
			if(dface!=0)
			{
				p2y-=40;
				p2x=485;
				dface--;
			}
			while(dface!=0)
			{
				p2x-=40;
				dface--;
			}
		}
		turn++;
	}
	display();
	if(b1==100)
	{
		winner=1;
		end();
	}
	if(b2==100)
	{
		winner=2;
		end();
	}
}
void rollDice()
{
	GLint rolltime=1000 + rand()%1000;
	int i;
	for(i=1;i<=rolltime;i++)
	{
		DF=(DF+1)%6;
		createBoard();
		createText();
		createDice();
		//createPins();
		glutSwapBuffers();
	}
	dface=DF;
	if(dface==0)
	dface=6;
	move();
}
void resize(int w,int h)
{
	winw=w,winh=h;
	glViewport(0,0,w,h);
	//glutReshapeWindow(1000,600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,ww,0,wh);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		x=x*1000.0/winw;
		y=y*600.0/winh;
		y=600-y;
		if(x>=x1&&x<=x2&&y>=y1&&y<=y2&&endgame==0)
		{
			//printf("%d %d\n",x,y);
			//bstate=0;
			//glutMouseFunc(NULL);
			rollDice();
			//glutMouseFunc(mouse);
		}
		if(endgame==1)
		{
			if(x>=100&&x<=300&&y>=120&&y<=200)
			{
				endgame=0;
				b1=1,b2=1,DF=1,turn=1,p1x=120,p1y=120,p2x=125,p2y=120,winner=0;
				glClear(GL_COLOR_BUFFER_BIT);
				glutSwapBuffers();
				display();
			}
			if(x>=700&&x<=900&&y>=120&&y<=200)
			{
				exit(0);
			}
		}
	}
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(ww,wh);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Snakes And Ladders");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
}
