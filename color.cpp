#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<string.h>
#include<math.h>

//FUNTION DEFINTIONS

void mouse1(int btn, int state, int x, int y);
void cursor(int x,int y);
void cursordraw();
void pause();
void circle(GLfloat c1,GLfloat c2,GLfloat c3);
void Polygon1(GLfloat s[][3],int tno);
void print(GLfloat x, GLfloat y, char *string);
void intprint(GLfloat x, GLfloat y,int val);
void scorefn();
void mouse3(int btn,int state,int x,int y);
void gameplay(int face);
void Roll();
void Playmenu();
void keyboard(unsigned char btn, int x, int y);
void cursor1(int,int);
void Polygon(int a, int b, int c, int d, int i, GLfloat s[][3]);
void healthbar();
void pause();
void menu();
void Dice();
void rs(int w,int h);
void display(void);
void idle();
void mouse(int, int, int, int);
void mouse1(int, int, int, int);
void mouse2(int, int, int, int);
GLuint LoadTextureRAW( const char * filename);
void healthbar1();

static GLfloat theta[] = { 0.0,0.0,0.0,0.0 },smallx=45.0,smally=45.0,smallz=45.0,bigx=0.0,bigy=0.0,gof =0;
static int rando=0;
static GLuint texture[31];

GLfloat v[][3] = { { -3.5,-3.5,-3.5 },{ 3.5,-3.5,-3.5 },{ 3.5,3.5,-3.5 },{ -3.5,3.5,-3.5 },{ -3.5,-3.5,3.5 },{ 3.5,-3.5,3.5 },{ 3.5,3.5,3.5 },{ -3.5,3.5,3.5 } };

const GLfloat color[8][3]={{1.0,1.0,1.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},{0.0,1.0,1.0},{0.0,0.0,1.0},{1.0,0.0,1.0},{0.0,0.0,0.0}};

GLfloat s1[][3] = {{0.0,0.0,3.6}};
GLfloat s2[][3] = {{-2.0,3.6,-2.0},{2.0,3.6,2.0}};
GLfloat s3[][3] = {{-3.6,2.0,-2.0},{-3.6,0.0,0.0},{-3.6,-2.0,2.0}};
GLfloat s4[][3] = {{3.6,2.0,2.0},{3.6,2.0,-2.0},{3.6,-2.0,2.0},{3.6,-2.0,-2.0}};
GLfloat s5[][3] = {{2.0,-3.6,2.0},{2.0,-3.6,-2.0},{-2.0,-3.6,2.0},{-2.0,-3.6,-2.0},{0.0,-3.6,0.0}};
GLfloat s6[][3] = {{-2.0,-2.0,-3.6},{-2.0,2.0,-3.6},{0.0,2.0,-3.6},{0.0,-2.0,-3.6},{2.0,-2.0,-3.6},{2.0,2.0,-3.6}};

GLfloat v0[][3] = {{ -3.0,5.0,-4 },{ 3.0,5.0,-4 },{ -3.0,3.0,-4 },{ 3.0,3.0,-4 }};
GLfloat v1[][3] = {{ -1.5,2.5,-4 },{ 1.5,2.5,-4 },{ -1.5,1.5,-4 },{ 1.5,1.5,-4 }};
GLfloat v2[][3] = {{ -1.5,0.5,-4 },{ 1.5,0.5,-4 },{ -1.5,-0.5,-4 },{ 1.5,-0.5,-4 }};
GLfloat v3[][3] = {{ -1.5,-1.5,-4 },{ 1.5,-1.5,-4 },{ -1.5,-2.5,-4 },{ 1.5,-2.5,-4 }};

GLfloat pd1[4][3]= {{ 16.0,0.0,-4 },{18.667,0.0,-4 },{ 16.0,-2.666,-4 },{18.667,-2.666,-4 }};
GLfloat pd2[4][3]= {{ 18.666,0.0,-4 },{21.333,0.0,-4 },{18.666,-2.666,-4 },{21.333,-2.666,-4 }};
GLfloat pd3[4][3]= {{ 21.333,0.0,-4 },{24.0,0.0,-4 },{21.333,-2.666,-4 },{24.0,-2.666,-4 }};
GLfloat pd4[4][3]= {{ 24.0,0.0,-4 },{26.666,0.0,-4 },{24.0,-2.666,-4 },{26.666,-2.666,-4 }};
GLfloat pd5[4][3]= {{ 26.666,0.0,-4 },{29.333,0.0,-4 },{26.666,-2.666,-4 },{29.333,-2.666,-4 }};
GLfloat pd6[4][3]= {{ 29.333,0.0,-4 },{ 31.9,0.0,-4 },{29.333,-2.666,-4 },{31.9,-2.666,-4 }};

GLfloat phl1[4][3]= {{ 16.0,-5.1333,-4 },{ 24.0,-5.1333,-4 },{ 16.0,-8.666,-4 },{ 24.0,-8.666,-4 }};
GLfloat phl2[4][3]= {{ 24.0,-5.1333,-4 },{ 31.9,-5.1333,-4 },{ 24.0,-8.666,-4 },{ 31.9,-8.666,-4 }};

GLfloat pr1[4][3]= {{ 16.0,-10.0,-4 },{ 31.9,-10.0,-4 },{ 16.0,-13.4,-4 },{ 31.9,-13.4,-4 }};

GLfloat w1=1366,h1=786,mx,my;//Should be changed acc. to monitor reso
float i1=10.0;
int selecn = 0,selechl = 0,sf = 0,hlf= 1,roll =0,score = 0, score1=0, health = 10, health1 = 10, counter=0, hs=0, rf=0;

GLuint LoadTextureRAW( const char * filename)
{
    GLuint texture;
    unsigned char* data;
    FILE * file;
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    float width = 512;
    float height = 512;
    data = (unsigned char*)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );
    for( int i = 0; i < width * height; ++i )
    {
        int index = i*3;
        unsigned char B,R;
        B=data[index];
        R=data[index+2];
        data[index]=R;
        data[index+2]=B;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texture);
    glBindTexture( GL_TEXTURE_2D, texture);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB , GL_UNSIGNED_BYTE, data);    // build our texture mipmaps
    free( data );
    return texture;
}

void circle(GLfloat c1,GLfloat c2,GLfloat c3)
{
    glColor3f(1.0,1.0,1.0);                                                                     //color to white
    int i;
    GLfloat a=c1,b=c2,c=c3;
    glBegin(GL_POLYGON);
       for(i=0;i<=360;i++)
       {
            if(c1!=(GLfloat)3.6 && c2!=(GLfloat)3.6 && c1!=(GLfloat)-3.6 && c2!=(GLfloat)-3.6)
            {
               a=0.5*sin(i)+c1;                                                                 //find abc values in terms of rcos0 and rsin0 for xyz
               b=0.5*cos(i)+c2;
            }
            else if(c3!=(GLfloat)3.6 && c2!=(GLfloat)3.6 && c3!=(GLfloat)-3.6 && c2!=(GLfloat)-3.6)
            {
               c=0.5*sin(i)+c3;
               b=0.5*cos(i)+c2;
            }
            else
            {
               c=0.5*sin(i)+c3;
               a=0.5*cos(i)+c1;
            }
           glVertex3f(a,b,c);
       }
    glEnd();
}

void cursordraw()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    GLfloat mx1=0.0;
    GLfloat my1=0.0;
    glTranslatef(mx,my,7.7);
    glRotatef(315.0,0.0,0.0,1.0);
    glRotatef(theta[3],1.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_TRIANGLES);                                                      //cursor is a pyramid and has 4 triangle faces
    glTexCoord2f(0.4, 1.0);glVertex3f(mx1,my1,0.0);                             //triangle 1
    glTexCoord2f(0.0, 0.0);glVertex3f(mx1+.5,my1+.2,0.2);
    glTexCoord2f(1.0, 0.0); glVertex3f(mx1+.5,my1-.2,0.2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_TRIANGLES);                                                      //triangle 2
    glTexCoord2f(0.4, 1.0);glVertex3f(mx1,my1,0.0);
    glTexCoord2f(0.0, 0.0);glVertex3f(mx1+.5,my1+.2,-0.2);
    glTexCoord2f(1.0, 0.0);glVertex3f(mx1+.5,my1-.2,-0.2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_TRIANGLES);                                                      //triangle 3
    glTexCoord2f(0.4, 1.0);glVertex3f(mx1,my1,0.0);
    glTexCoord2f(0.0, 0.0);glVertex3f(mx1+.5,my1+.2,-0.2);
    glTexCoord2f(1.0, 0.0);glVertex3f(mx1+.5,my1+.2,0.2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_TRIANGLES);                                                      //triangle 4
    glTexCoord2f(0.4, 1.0);glVertex3f(mx1,my1,0.0);
    glTexCoord2f(0.0, 0.0);glVertex3f(mx1+.5,my1-.2,-0.2);
    glTexCoord2f(1.0, 0.0);glVertex3f(mx1+.5,my1-.2,0.2);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(mx1,my1,0.0);
    glVertex3f(mx1+.5,my1+.2,0.2);
    glVertex3f(mx1+.5,my1-.2,0.2);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(mx1,my1,0.0);
    glVertex3f(mx1+.5,my1+.2,-0.2);
    glVertex3f(mx1+.5,my1-.2,-0.2);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(mx1,my1,0.0);
    glVertex3f(mx1+.5,my1+.2,-0.2);
    glVertex3f(mx1+.5,my1+.2,0.2);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(mx1,my1,0.0);
    glVertex3f(mx1+.5,my1-.2,-0.2);
    glVertex3f(mx1+.5,my1-.2,0.2);
    glEnd();
    glDisable(GL_TEXTURE_2D);//2
    glPopMatrix();
}

void Polygon1(GLfloat s[][3],int tno)//function used to draw rectangles with textures
{
    glColor3d(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[tno]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.04, 1.0);glVertex3fv(s[0]);
	glTexCoord2f(0.04, 0.0);glVertex3fv(s[2]);
	glTexCoord2f(1.0, 0.0);glVertex3fv(s[3]);
	glTexCoord2f(1.0, 1.0);glVertex3fv(s[1]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Polygon2(GLfloat s[][3],int no,int pick,const GLfloat clr[3],int tno)// function used to draw recangle with textures and add conditions
{
    if(pick == 6)// for the small 6 squares
    {
        glLineWidth(5.0);
        glBegin(GL_LINE_LOOP);
        for(float i=0; i<360.0; i+=6)// for the color changing circle
        {
            glColor3fv(color[rand()%8]);
            glVertex3f((s[0][0]+s[1][0])/2.0+1.25*cos(i*3.14/180.0),(s[0][1]+s[2][1])/2.0+1.333*sin((i*3.14/180.0)),5.0);
        }
        glEnd();
    }
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);//1
    glBindTexture(GL_TEXTURE_2D, texture[tno]);
    if(selechl == 3 && pick == 2)// if 1 or 6 is selected
    {
        glColor3f(0.8,0.5,0.07);
        glBindTexture(GL_TEXTURE_2D, texture[19]);
    }
    if(no == selecn && pick == 6)// if any number from 1 to 6 is selected
    {
        glBindTexture(GL_TEXTURE_2D, texture[20+no]);
    }
    if(no == selechl && pick == 2)// if low or high is selected
    {
        glColor3f(0.0,1.0,0.0);
    }
    glBegin(GL_POLYGON);
	glTexCoord2f(0.04, 1.0);glVertex3fv(s[0]);
    glTexCoord2f(0.04, 0.0);glVertex3fv(s[2]);
	glTexCoord2f(1.0, 0.0);glVertex3fv(s[3]);
	glTexCoord2f(1.0, 1.0);glVertex3fv(s[1]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3b(0,0,0);
}

void print(GLfloat x, GLfloat y, char *g)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int)strlen(g);
	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g[i]);
	}
}

void print1(GLfloat x, GLfloat y, char *g)//used for different font
{
	glRasterPos2f(x, y);
	int len = (int)strlen(g);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, g[i]);
	}
}

void intprint(GLfloat x, GLfloat y,int val)//use to convert numbers into characters before printing onto the screen
{
	char a = val + 48;
	int score1=val,scorerev=0;
	glRasterPos2f( x, y);
    while(score1 > 0)
    {
        scorerev*=10;
        scorerev=scorerev+(score1%10);
        score1/=10;
    }
    score1=scorerev;
	while(score1 > 0)
    {
        a=(score1%10)+48;
        score1/=10;
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a);
    }
    if(val%10==0)
    {a=val%10+48;
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a);}
}

void scorefn()//prints the high score and score after game over
{
    glutMouseFunc(mouse3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.01,0.027,0.0);
	glLoadIdentity();
    glOrtho(-14.0,14.0,-7.875,7.875,-10.0,10.0);
    glColor3d(1,0,1);
    intprint(-0.2,-1.25,score);
    intprint(-0.2,1.0,hs);
    Polygon1(v0,10);
    Polygon1(v1,28);
	Polygon1(v2,29);
	Polygon1(v3,30);
    cursordraw();
	glFlush();
	glutSwapBuffers();
}

void highscore()// checks whether current code is greater than previous high score and writes it to a file
{
FILE *fout,*f;
f=fopen("highscore1.txt","r");
fscanf(f,"%d",&hs);
fclose(f);
    if(score>hs)
        hs=score;
        fout=fopen("highscore1.txt","w");
        fprintf(fout,"%d",hs);
        fclose(fout);
}

void mouse3(int btn,int state,int x,int y)// used to return to main menu
{
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)// && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=1.5 && my<=2.5)
    {
        glutDisplayFunc(menu);
        glutKeyboardFunc(NULL);
        glutMouseFunc(mouse2);
        glutPassiveMotionFunc(cursor);
        glutMotionFunc(cursor);
        glutIdleFunc(idle);
        rf=0;
        roll =0;
        score = 0;
        health = 10;
        health1 = 10;
    }
}

void mouse4(int btn,int state,int x,int y)// used to enter score page after game over
{
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)// && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=1.5 && my<=2.5)
    {
        rf=0;
        glutDisplayFunc(scorefn);
        glutKeyboardFunc(NULL);
        glutMouseFunc(mouse3);
        glutPassiveMotionFunc(cursor);
        glutMotionFunc(cursor);
    }
}

void gameover(void)// used to show final spin and the game over box after code is completed execution
{
    glutMouseFunc(mouse4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8, 0.5, 0.07, 1.0);
	glLoadIdentity();
	glOrtho(-16.0,32.0,-13.5,13.5,-10.0,10.0);
	glPushMatrix();
    glRotatef(45, 1.0, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 0.0);
    glRotatef(270, 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    Dice();
    glPopMatrix();
	glPushMatrix();
	glTranslatef(24.0,6.5,0.0);
    glScalef(0.5,0.5,0.5);
    glRotatef(smallz, 0.0, 0.0, 1.0);
    glRotatef(smally, 0.0, 1.0, 0.0);
    glRotatef(smallx, 1.0, 0.0, 0.0);
    Dice();
	glPopMatrix();
	Playmenu();
	healthbar1();
	healthbar();
    cursordraw();
    GLfloat go[][3]={{-4.5,13.5,4.0},{20.5,13.5,4.0},{-4.5,6.33,4.0},{20.5,6.33,4.0}};
    if(theta[0] == bigx && theta[1] == bigy)
        rf=2;
	if(health1 == 0 && gof == 1)
    {
        Polygon2(go,0,0,color[0],27);
    }
	print(14,11.0,"SCORE");//warning
	print(-15.75,11.5,"HEALTH");//warning
    intprint(15.0,10.0,score1);
    intprint(-15.0,10.5,health1);
    glFlush();
	glutSwapBuffers();
}

void gameplay()//used to create the working of the game
{
    if(health > 0)
    {
     if(selecn == 1 || selecn ==6)
    {
        if(rando == selecn)
        {
            score+=5;health+=4;
        }
        else
            health--;
    }
    if( selechl == 1 )
    {
            if( rando >= selecn)
            {
                health++;
                score++;
                if( selecn == 5 )
                {
                    health+=2;
                    score++;
                }
            }
            else
            {
                health -= 4;
                if( selecn == 5 )
                {
                    health+=2;
                }
            }
        }
        if(selechl == 2)
        {
            if( rando <= selecn)
            {
                health++;
                score++;
                if( selecn == 2 )
                {
                    health+=2;
                    score++;
                }
            }
            else
            {
                health-=4;
                if( selecn == 2 )
                {
                    health+=2;
                }
            }
        }
        if(health > 10)
        {
            health = 10;
        }
        if(health <= 0)
        {
            health = 0;
            gameplay();
            gof=0;
        }
    }
    else
    {
        health=0;
        rf=0;
        highscore();
        glutKeyboardFunc(NULL);
        glutMouseFunc(mouse4);
        glutDisplayFunc(gameover);
        glutPassiveMotionFunc(cursor1);
        glutMotionFunc(cursor1);
    }
}

void hyperspin()
{
    if(rando == 1)
    {
        bigx=0.0;bigy=0.0;
    }
    if(rando == 2)
    {
        bigx=90.0;bigy=0.0;
    }
    if(rando == 3)
    {
        bigx=0.0;bigy=90.0;
    }
        if(rando == 4)
    {
        bigx=0.0;bigy=270.0;
    }
    if(rando == 5)
    {
        bigx=270.0;bigy=0.0;
    }
    if(rando == 6)
    {
        bigx=180.0;bigy=0.0;
    }
}

void Roll()
{
    rando = rand() % 6 + 1 ;
    gameplay();
    theta[0]++;
    hyperspin();
    sf=0;
    hlf=1;
    selechl=0;
    selecn=0;
}

void Playmenu()
{
    glColor3f(0.0,0.0,0.0);
    Polygon2(pd1,1,6,color[0],11);
    Polygon2(pd2,2,6,color[1],12);
    Polygon2(pd3,3,6,color[2],13);
    Polygon2(pd4,4,6,color[3],14);
    Polygon2(pd5,5,6,color[4],15);
    Polygon2(pd6,6,6,color[5],16);
    Polygon2(phl1,2,2,color[0],18);
    Polygon2(phl2,1,2,color[0],17);
    Polygon2(pr1,1,1,color[0],20);
    glLineWidth(1.0);
}

void Polygon(int a, int b, int c, int d, int i, GLfloat s[][3])
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0,1.0);
	glVertex3fv(v[a]);
	glVertex3fv(v[b]);
	glVertex3fv(v[c]);
	glVertex3fv(v[d]);
	glEnd();
	glPointSize(10.0);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0,1.0);
	glVertex3fv(v[a]);
	glVertex3fv(v[b]);
	glVertex3fv(v[c]);
	glVertex3fv(v[d]);
	glEnd();
	for (int z = 0; z<i; z++)
	{
		circle(s[z][0],s[z][1],s[z][2]);
	}
}

void Dice()
{
    Polygon(4, 5, 6, 7, 1, s1);
	Polygon(2, 3, 7, 6, 2, s2);
	Polygon(0, 4, 7, 3, 3, s3);
	Polygon(1, 2, 6, 5, 4, s4);
	Polygon(0, 1, 5, 4, 5, s5);
	Polygon(0, 3, 2, 1, 6, s6);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8, 0.5, 0.07, 1.0);
	glLoadIdentity();
	glOrtho(-16.0,32.0,-13.5,13.5,-10.0,10.0);
	glPushMatrix();
    glRotatef(45, 1.0, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 0.0);
    glRotatef(270, 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    Dice();
    glPopMatrix();
	glPushMatrix();
	glTranslatef(24.0,6.5,0.0);
    glScalef(0.5,0.5,0.5);
    glRotatef(smallz, 0.0, 0.0, 1.0);
    glRotatef(smally, 0.0, 1.0, 0.0);
    glRotatef(smallx, 1.0, 0.0, 0.0);
    Dice();
	glPopMatrix();
	Playmenu();
	healthbar1();
	healthbar();
    cursordraw();
    if(theta[0] == bigx && theta[1] == bigy)
        rf=1;
	print(14,11.0,"SCORE");//warning
	print(-15.75,11.5,"HEALTH");//warning
    intprint(15.0,10.0,score1);
    intprint(-15.0,10.5,health1);
    glFlush();
	glutSwapBuffers();
}

void idle()
{
    counter=smallz;
	theta[3]+= 6;
	smallz+= 6;
	if (theta[1]>360.0)
		theta[1] = 0;
    if (theta[0]>360.0)
		theta[0] = 0;
	if (theta[3]>360.0)
		theta[3] -= 360;
    if(theta[0] != bigx)
    {
        theta[0]+=10;
        glutMouseFunc(NULL);
        if(theta[0] == bigx)
            theta[1]+=10;
    }
    else if(theta[1] != bigy)
    {
        theta[1]+=10;
        if(theta[1] == bigy)
            rf=1;
    }
    if(health1 == 0 && theta[1] == bigy && theta[0] == bigx)
        gof=1;
    else if(rf == 1)
    {
        glutMouseFunc(mouse);
        score1=score;
        health1=health;
    }
    if(rf == 2)
    {
        glutMouseFunc(mouse4);
        score1=score;
        health1=health;
    }
    glutPostRedisplay();
}

void diced(GLfloat s, GLfloat tra1, GLfloat tra2)
{
    glPushMatrix();
	glScalef(s,s,s);
	glTranslatef(tra1,tra2,0.0);
	glRotatef(45.0,1.0,0.0,0.0);
	glRotatef(45.0,0.0,1.0,0.0);
	glRotatef(theta[3],0.0,0.0,1.0);
	Dice();
	glPopMatrix();
}

void dice1(GLfloat htp,GLfloat htp1)
{
   glPushMatrix();
    glTranslatef(htp,htp1,0);
	glScalef(0.1,0.1,0.1);
	glRotatef(smallz,1.0,1.0,1.0);
	glRotatef(smallz,1.0,1.0,1.0);
	glRotatef(smallz,1.0,1.0,1.0);
	Dice();
	glPopMatrix();
}

void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLoadIdentity();
	glOrtho(-16.0,32.0,-13.5,13.5,-10.0,10.0);
	dice1(-12,7.2);
	dice1(-12,5.2);
	dice1(-12,3.2);
	dice1(-12,1.2);
	dice1(-12,-.8);
	dice1(-12,-2.8);
	dice1(-12,-4.8);
	dice1(-12,-6.8);
	dice1(-12,-8.8);
	glColor3f(0,0,205);
    print(5,10,"HOW TO PLAY");
	glColor3f(1,0,1);
	print1(-11,7,"Choose a no between 1-6,then guess whether the no on the dice will be higher or lower then the chosen no,then roll the dice!!");
	print1(-11,5,"if the guess is right you get points if not you loose your health,you can also refill your health on every right guess.");
	print1(-11,3,"At the start you will have a health of 10,the amount of health you loose and gain ,and also the points you gain depends upon the no you choose.");
	print1(-11,1,"on choosing 1 or 6 for every right guess you get 5 points and gain 4 health,on every wrong guess you loose 1 health." );
	print1(-11,-1,"on choosing 2 or 5 for every right guess you get 3 points and gain 3 health,on every wrong guess you loose 2 health." );
    print1(-11,-3,"on choosing 3 or 4 for every right guess you get 1 point and gain 1 health,on every wrong guess you loose 4 health." );
	print1(-11,-5,"Also if u choose 1 or 6 the high and low buttons are disabled.");
	print1(-11,-7,"on choosing 2 or 5 the high and low buttons are automatically selected , for 2 low and for 5 high is selected");
	print1(-11,-9,"BEST OF LUCK ,because luck is the only thing you need in this game!! XD");
    glColor3f(1,1,1);
    print(1,-12,"press any key to return to main menu");
	glFlush();
	glutSwapBuffers();
}

void menu()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glLoadIdentity();
    glOrtho(-14.0,14.0,-7.875,7.875,-10.0,10.0);
    glColor3f(0.0,0.0,1.0);//Adjust the Color Values
    Polygon1(v0,10);
    Polygon1(v1,4);
    Polygon1(v2,5);
    Polygon1(v3,6);
    glColor3f(1.0, 0.0, 1.0);
	cursordraw();
    diced(0.15,20,12);
    diced(0.15,-20,12);
    diced(0.15,-20,-12);
    diced(0.15,20,-12);
    glFlush();
    glutSwapBuffers();
}
//health bar
void healthbar()
{
    float sep=.0;
    float barheight=1.0;
    glBegin(GL_QUADS);
    glColor3f(0,1,0);
    for(float i=0;i<(float)health1;i+=(sep+barheight))
    {
        if(health1<5)
            glColor3f(1,0,0);

        glVertex2f(-14.10,i);
        glVertex2f(-15.10,i);
        glVertex2f(-15.10,i+barheight);
        glVertex2f(-14.10,i+barheight);
    }

    glEnd();
    }

void healthbar1()
{
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex2f(-14.10,0);
    glVertex2f(-15.10,0);
    glVertex2f(-15.10,10);
    glVertex2f(-14.10,10);
    glEnd();
    glLineWidth(1);
}

void pause()
{
    glutMouseFunc(mouse1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();
	glOrtho(-14.0,14.0,-7.875,7.875,-10.0,10.0);
	glColor3f(1.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    Polygon1(v0,10);
    Polygon1(v1,7);
	Polygon1(v2,8);
	Polygon1(v3,9);
	cursordraw();
	glFlush();
	glutSwapBuffers();
}

void cursor1(int x,int y)
{
    mx=x*48.0/w1- 16;
    my=-(y*27.0/h1 -13.5);
}

void cursor(int x,int y)
{
    mx=x*28.0/w1-14.0;
    my=-(y*15.75/h1 - 7.875);
}

void keyboard(unsigned char btn, int x, int y)
{
	if (btn == 27)//ESc ASCII=27
	{
	    rf=0;
	    glutKeyboardFunc(NULL);
	    glutDisplayFunc(pause);
	    glutIdleFunc(idle);
	    glutPassiveMotionFunc(cursor);
	    glutMotionFunc(cursor);
	}
}

void mouse(int btn, int state, int x, int y)//to check if dice sides are accurate....  to be removed
{
    if ( sf == 0 )
    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)16.0 && mx<=(GLfloat)18.66 && my>=-2.66 && my<=0.0)
            {selecn=1;selechl=3;hlf=1;smallx=0.0;smally=0.0;}
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)18.66 && mx<=(GLfloat)21.33 && my>=-2.66 && my<=0.0)
            {selecn=2;selechl=2;hlf=1;smallx=90.0;smally=0.0;}
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)21.33 && mx<=(GLfloat)24.0 && my>=-2.66 && my<=0.0)
            {selecn=3;selechl=0;hlf=0;smallx=0.0;smally=90.0;}
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)24.0 && mx<=(GLfloat)26.66 && my>=-2.66 && my<=0.0)
            {selecn=4;selechl=0;hlf=0;smallx=0.0;smally=270.0;}
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)26.66 && mx<=(GLfloat)29.33 && my>=-2.66 && my<=0.0)
            {selecn=5;selechl=1;hlf=1;smallx=270.0;smally=0.0;}
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)29.33 && mx<=(GLfloat)32.0 && my>=-2.66 && my<=0.0)
            {selecn=6;selechl=3;hlf=1;smallx=180.0;smally=0.0;}
    }
    if ( hlf == 0)
    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)16.0 && mx<=(GLfloat)24.0 && my>=-8.66 && my<=-5.133)
            {selechl=2;sf=1;}
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)24.0 && mx<=(GLfloat)32.0 && my>=-8.66 && my<=-5.133)
            {selechl=1;sf=1;}
        //printf("%d\n",selechl);
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)16.0 && mx<=(GLfloat)32.0 && my>=-13.5 && my<=-10.0 && selecn !=0 && selechl != 0)
        {hlf=1;sf=1;rf=0;score1=score;Roll();}
}

void keyboard1(unsigned char btn, int x, int y)
{
	    glutKeyboardFunc(NULL);
        glutDisplayFunc(menu);
        glutPassiveMotionFunc(cursor);
        glutMotionFunc(cursor);
        glutMouseFunc(mouse2);
        glutIdleFunc(idle);
}

void mouse2(int btn,int state,int x,int y)// to be defined
{
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=1.5 && my<=2.5)
    {
        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse);
        glutPassiveMotionFunc(cursor1);
        glutMotionFunc(cursor1);
        glutIdleFunc(idle);
        rf=1;
        gof = 0;
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=-0.5 && my<=0.5)
    {
        glutKeyboardFunc(keyboard1);
        glutDisplayFunc(display1);
        glutMouseFunc(NULL);
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=-2.5 && my<=-1.5)
    {
      exit(0);
    }
}

void mouse1(int btn, int state, int x, int y)// to be defined
{
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=1.5 && my<=2.5)
    {
        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse);
        glutPassiveMotionFunc(cursor1);
        glutMotionFunc(cursor1);
        glutIdleFunc(idle);
        rf=1;
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=-0.5 && my<=0.5)
    {
        glutKeyboardFunc(NULL);
        glutDisplayFunc(menu);
        glutPassiveMotionFunc(cursor);
        glutMotionFunc(cursor);
        glutMouseFunc(mouse2);
        glutIdleFunc(idle);
        roll =0;
        score = 0;
        health = 10;
        sf=0;
        hlf=1;
        selechl=0;
        selecn=0;
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=(GLfloat)-1.5 && mx<=(GLfloat)1.5 && my>=-2.5 && my<=-1.5)
    {
      exit(0);
    }
}

void rs(int w,int h)
{
    w1=w;h1=h;
}

void init(void)
{
    texture[0]= LoadTextureRAW ("7.bmp");
    texture[1]= LoadTextureRAW ("8.bmp");
    texture[2]= LoadTextureRAW ("9.bmp");
    texture[3]= LoadTextureRAW ("10.bmp");
    texture[4]= LoadTextureRAW ("p1.bmp");
    texture[5]= LoadTextureRAW ("p2.bmp");
    texture[6]= LoadTextureRAW ("p3.bmp");
    texture[7]= LoadTextureRAW ("p4.bmp");
    texture[8]= LoadTextureRAW ("p5.bmp");
    texture[9]= LoadTextureRAW ("p3.bmp");
    texture[10]= LoadTextureRAW ("b3.bmp");
    texture[11]= LoadTextureRAW ("1.bmp");
    texture[12]= LoadTextureRAW ("2.bmp");
    texture[13]= LoadTextureRAW ("3.bmp");
    texture[14]= LoadTextureRAW ("4.bmp");
    texture[15]= LoadTextureRAW ("5.bmp");
    texture[16]= LoadTextureRAW ("6.bmp");
    texture[17]= LoadTextureRAW ("high.bmp");
    texture[18]= LoadTextureRAW ("low.bmp");
    texture[20]= LoadTextureRAW ("roll.bmp");
    texture[21]= LoadTextureRAW ("21.bmp");
    texture[22]= LoadTextureRAW ("22.bmp");
    texture[23]= LoadTextureRAW ("23.bmp");
    texture[24]= LoadTextureRAW ("24.bmp");
    texture[25]= LoadTextureRAW ("25.bmp");
    texture[26]= LoadTextureRAW ("26.bmp");
    texture[27]= LoadTextureRAW ("go.bmp");
    texture[28]= LoadTextureRAW ("p7.bmp");
    texture[29]= LoadTextureRAW ("p8.bmp");
    texture[30]= LoadTextureRAW ("p9.bmp");

}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(w1,h1);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Blue Jack");
    init();
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    glutReshapeFunc(rs);
    glutDisplayFunc(menu);
    glutMouseFunc(mouse2);
    glutPassiveMotionFunc(cursor);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
