#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#define maxx 800
#define maxy 600
#define toolbar_height maxy-80
#define actionbar_width maxx-90

#define PENCIL 0
#define TWOPOINTLINE 1
#define RECTANGLE 2
#define POLYGON 3
#define CIRCLE 4
#define TEXT 5
#define MESH 6

int r=0,b=0,g=0;
int toolflag;   //to select tool
int colorflag=0;//to select color
int clear = 0;
int leftrotateflag=0;
float color[200][3]={{1,0,0},{1,1,0},{1,0,1},{0,1,0},{0,1,1},{0,0,1}};
int meshcount=0;

int linepoints[200][3];
int pencilpoints[5000][3];
int squarepoints[200][3];
int polypoints[200][3];
int circlepoints[200][3];
int textpospoint[200][4];
int textcount=0;
int pencilpointcount=0;
int linepointcount=-1;
int squarepointcount=0;
int polypointcount=-1;
int circlepointcount=0;
int x1,y1,x2,y2,dist;


void rotateobject()
{
    float res[3][2],rot[3][3],ver[3][2];
    float m,n;
    float h=(float)linepoints[linepointcount-1][0]/1.0;
    float k=(float)linepoints[linepointcount-1][1]/1.0;
    float theta;
    printf("%f %f\n",h,k);
    if(leftrotateflag)
    {
     theta=-1*3.14/180;
    leftrotateflag=0;
    }
    else
    {

        theta=2*3.14/180;
    }


    m=h-h*(cos(theta)) + k*(sin(theta));
    n=k-h*(sin(theta)) - k*(cos(theta));
    rot[0][0]=cos(theta);
    rot[0][1]=-sin(theta);
    //rot[0][2]=m;
    rot[1][0]=sin(theta);
    rot[1][1]=cos(theta);
    //rot[1][2]=n;
    //rot[2][0]=0;
   // rot[2][1]=0;
   // rot[2][2]=1;
    int i,j,p;
   // printf("%d %d \n",m,n);
   //ver[0][0]=linepoints[linepointcount-1][0];
   //ver[1][0]=linepoints[linepointcount-1][1];
   //ver[2][0]=0;
   ver[0][0]=linepoints[linepointcount][0];
   ver[1][0]=linepoints[linepointcount][1];
   //ver[2][0]=0;

    for(i=0;i<2;i++)
    {
        for(j=0;j<1;j++)
        {
            res[i][j]=0;
            for(p=0;p<2;p++)
            {
                res[i][j]+=rot[i][p]*ver[p][j];
            }
        }
    }


    printf("\n");
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            printf("%f ",res[i][j]);
        }
        printf("\n");
    }

    linepoints[linepointcount][0]=res[0][0];
    linepoints[linepointcount][1]=res[1][0];


  /*  int x=linepoints[linepointcount][0];
    int y=linepoints[linepointcount][1];
    int r = sqrt((x-linepoints[linepointcount-1][0])*(x-linepoints[linepointcount-1][0]) + (y-linepoints[linepointcount-1][1])*(y-linepoints[linepointcount-1][1]));
    printf("r : %d\n",r);
    linepoints[linepointcount][0]=x+100*cos(10*3.14/180);
    linepoints[linepointcount][1]=y+100*sin(10*3.14/180);*/
    glutPostRedisplay();

}
void motion(int x,int y)
{
    if(x<actionbar_width && y<toolbar_height)
    {
    if(toolflag == PENCIL)
    {
    printf("hello\n");
    addpencilpoint(x,maxy-y);
    glutPostRedisplay();
    }
    else if(toolflag == TWOPOINTLINE)
    {
    addlinepoint(x,maxy-y);
    glutPostRedisplay();
    }
    else if(toolflag == RECTANGLE)
    {
        addsquarepoint(x,maxy-y);
        glutPostRedisplay();
    }
    else if(toolflag == POLYGON)
    {
        addpolypoint(x,maxy-y);
        glutPostRedisplay();
    }
    else if(toolflag == CIRCLE)
    {
        addcirclepoint(x,maxy-y);
        glutPostRedisplay();
    }
    }
}

void addpencilpoint(int x,int y)
{
    pencilpoints[pencilpointcount][0]=x;
    pencilpoints[pencilpointcount][1]=y;
    pencilpoints[pencilpointcount][2]=colorflag;
    pencilpointcount++;
}
void addlinepoint(int x,int y)
{
    linepoints[linepointcount][0]=x;
    linepoints[linepointcount][1]=y;
    linepoints[linepointcount][2]=colorflag;
}

void addsquarepoint(int x,int y)
{
    squarepoints[squarepointcount][0]=x1;
    squarepoints[squarepointcount][1]=y1;
    squarepoints[squarepointcount][2]=colorflag;

    squarepoints[squarepointcount+1][0]=x;
    squarepoints[squarepointcount+1][1]=y1;
    squarepoints[squarepointcount+1][2]=colorflag;

    squarepoints[squarepointcount+2][0]=x;
    squarepoints[squarepointcount+2][1]=y1;
    squarepoints[squarepointcount+2][2]=colorflag;

    squarepoints[squarepointcount+3][0]=x;
    squarepoints[squarepointcount+3][1]=y;
    squarepoints[squarepointcount+3][2]=colorflag;

    squarepoints[squarepointcount+4][0]=x;
    squarepoints[squarepointcount+4][1]=y;
    squarepoints[squarepointcount+4][2]=colorflag;

    squarepoints[squarepointcount+5][0]=x1;
    squarepoints[squarepointcount+5][1]=y;
    squarepoints[squarepointcount+5][2]=colorflag;

    squarepoints[squarepointcount+6][0]=x1;
    squarepoints[squarepointcount+6][1]=y;
    squarepoints[squarepointcount+6][2]=colorflag;

    squarepoints[squarepointcount+7][0]=x1;
    squarepoints[squarepointcount+7][1]=y1;
    squarepoints[squarepointcount+7][2]=colorflag;

}

void addpolypoint(int x,int y)
{
    polypoints[polypointcount][0]=x;
    polypoints[polypointcount][1]=y;
    polypoints[polypointcount][2]=colorflag;
}

void addcirclepoint(int x,int y)
{
    circlepoints[circlepointcount][0]=x;
    circlepoints[circlepointcount][1]=y;
    circlepoints[circlepointcount][2]=colorflag;
}

void keyboard(unsigned int key,int x,int y)
{
    textpospoint[textcount][2]=key;
    textpospoint[textcount][3]=colorflag;
    textcount++;
    textpospoint[textcount][0]=textpospoint[textcount-1][0]+11;
    textpospoint[textcount][1]=textpospoint[textcount-1][1];

    glutPostRedisplay();
}
void mouse(int button,int action,int x,int y)
{
    int i;
    y=maxy-y;
    if(button==GLUT_LEFT_BUTTON)
    {
        if(action == GLUT_DOWN)
        {
            //setting toolflag
            if(y<maxy-20 && y>maxy-60)
            {
                if(x > 200 && x < 240)
                    toolflag=PENCIL;
                if(x > 240 && x < 280)
                    toolflag=TWOPOINTLINE;
                if(x > 280 && x < 320)
                    toolflag=RECTANGLE;
                if(x > 320 && x < 360)
                    toolflag=POLYGON;
                if(x > 360 && x < 400)
                    toolflag=CIRCLE;
                if(x > 400 && x < 440)
                    toolflag=TEXT;
                if(x > 440 && x < 480)
                {
                    meshcount=(++meshcount)%2;
                   // printf("%d\n",meshcount);
                    glutPostRedisplay();
                }
                if(x>500 && x<570)
                {
                    clear=1;
                }

                return 0;
            }

            //setting colorflag
            if(x<maxx-20 && x>maxx-60)
            {
                if(y<480 && y>440)
                {
                    colorflag=0;
                    r=255;
                    g=0;
                    b=0;
                }
                if(y<440 && y>400)
                {
                    colorflag=1;
                    r=255;
                    g=255;
                    b=0;
                }
                if(y<400 && y>360)
                {
                    colorflag=2;
                    r=255;
                    g=0;
                    b=255;
                }
                if(y<360 && y>320)
                {
                    colorflag=3;
                    r=0;
                    g=255;
                    b=0;
                }
                if(y<320 && y>280)
                {
                    colorflag=4;
                    r=0;
                    g=255;
                    b=255;
                }
                if(y<280 && y>240)
                {
                    colorflag=5;
                    r=0;
                    g=0;
                    b=255;
                }
                if(y<maxy-380-2*40 && y>maxy-380-3*40)
                {
                    printf("rotate\n");
                    rotateobject();
                }
                if(y<maxy-380-3*40 && y>maxy-380-4*40)
                {
                    printf("rotate\n");
                    leftrotateflag=-1;
                    rotateobject();

                }
            }
            //printf("%d : ",toolflag);
            //printf("%d\n",colorflag);
        }

    }
    //for text
    if(x<actionbar_width && y<toolbar_height)
    {
    if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN && toolflag == TEXT)
    {
        textpospoint[textcount][0]=x;
        textpospoint[textcount][1]=y;
        glutKeyboardFunc(keyboard);
    }

    //for line
    if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN && toolflag == TWOPOINTLINE)
    {

        linepointcount++;
        addlinepoint(x,y);
        //printf("%d %d\n",linepoints[pointcount][0],linepoints[pointcount][1]);
        glutPostRedisplay();
    }

    //for rectangle
    if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN && toolflag == RECTANGLE)
    {
        x1=x;
        y1=y;
        addsquarepoint(x,y);
      //  printf("%d %d : %d\n",squarepoints[pointcount][0],squarepoints[pointcount][1],pointcount);

    }
    else if(button==GLUT_LEFT_BUTTON && action==GLUT_UP && toolflag == RECTANGLE)
    {
        squarepointcount+=8;
       // printf("%d %d : %d\n",squarepoints[7][0],squarepoints[7][1],pointcount);
    }

    //for polygon
    if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN && toolflag == POLYGON)
    {
        polypointcount++;
        addpolypoint(x,y);

       // printf("%d %d : %d\n",polypoints[pointcount][0],polypoints[pointcount][1],pointcount);
    }
    if(button==GLUT_RIGHT_BUTTON && action==GLUT_DOWN && toolflag == POLYGON)
    {
        if(polypointcount>=0)
        polypointcount--;
    }

    //for circle
    if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN && toolflag == CIRCLE)
    {
        x1=x;
        y1=y;
        addcirclepoint(x,y);
        printf("%d %d : %d\n",circlepoints[circlepointcount][0],circlepoints[circlepointcount][1],circlepointcount);
        circlepointcount++;

    }
    else if(button==GLUT_LEFT_BUTTON && action==GLUT_UP && toolflag == CIRCLE)
    {
        circlepointcount++;
    }
    }
}

void pencil()
{
    //box at x=200, y=maxy-20;
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
    glVertex2i(216,maxy-25);
    glVertex2i(224,maxy-25);
    glVertex2i(224,maxy-45);
    glVertex2i(216,maxy-45);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(224,maxy-45);
    glVertex2i(220,maxy-55);
    glVertex2i(216,maxy-45);
    glEnd();
}
void twopointline()
{
    //box at x=240, y=maxy-20
    glLineWidth(1.5);
    glBegin(GL_LINES);
    glVertex2i(250,maxy-50);
    glVertex2i(270,maxy-30);
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2i(250,maxy-50);
    glVertex2i(270,maxy-30);
    glEnd();
}

void rectangle()
{
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
    glVertex2i(290,maxy-30);
    glVertex2i(310,maxy-30);
    glVertex2i(310,toolbar_height+30);
    glVertex2i(290,toolbar_height+30);
    glEnd();
}
void polygon()
{
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
    glVertex2i(325,maxy-40);
    glVertex2i(335,maxy-30);
    glVertex2i(345,maxy-30);
    glVertex2i(355,maxy-40);
    glVertex2i(345,maxy-50);
    glVertex2i(335,maxy-50);
    glEnd();
}
void circle(int r,int x,int y)
{
    int i;
    glPointSize(1.5);
    glBegin(GL_POINTS);
    for(i=0;i<360;i+=5)
    {
    glVertex2i(x+r*cos(i),y+r*sin(i));
    }
    glEnd();
}
void text()
{
    glRasterPos2i(410,toolbar_height/2-9);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'T');
}
void mesh()
{
int j,i;
    glLineWidth(1.5);
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
        glBegin(GL_LINE_LOOP);
        glVertex2i(450+i*5,maxy-30-j*5);
        glVertex2i(450+i*5+5,maxy-30-j*5);
        glVertex2i(450+i*5+5,maxy-30-j*5-5);
        glVertex2i(450+i*5,maxy-30-j*5-5);
        glEnd();
        }
    }
}

void zoom()
{
    circle(8,actionbar_width+35,maxy-395);
    glBegin(GL_LINES);
    glVertex2i(actionbar_width+35+7,maxy-395-8);
    glVertex2i(actionbar_width+50,maxy-410);
    glVertex2i(actionbar_width+35,maxy-395+5);
    glVertex2i(actionbar_width+35,maxy-395-5);
    glVertex2i(actionbar_width+30,maxy-395);
    glVertex2i(actionbar_width+35+5,maxy-395);
    glEnd();


    circle(8,actionbar_width+35,maxy-435);
    glBegin(GL_LINES);
    glVertex2i(actionbar_width+35+7,maxy-435-8);
    glVertex2i(actionbar_width+50,maxy-450);
    glVertex2i(actionbar_width+30,maxy-435);
    glVertex2i(actionbar_width+35+5,maxy-435);
    glEnd();
}

void rotate()
{
    //pending...........
    int i;
    glBegin(GL_POINTS);
    for(i=0;i<180;i++)
    {
        glVertex2i(actionbar_width+40+10*cos(90+i*3.14/180),maxy-480+10*sin(90+i*3.14/180));
        glVertex2i(actionbar_width+40+10*cos(90-i*3.14/180),maxy-520+10*sin(90-i*3.14/180));
    }
    glEnd();
    glRasterPos2i(actionbar_width+40,maxy-480-9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'R');
    glRasterPos2i(actionbar_width+30,maxy-520-9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'L');
}
void toolbar()
{
    char string[]="PAINT";
    int i;
    glColor3ub(170,170,170);
    glBegin(GL_QUADS);
    glVertex2i(0,maxy);
    glVertex2i(maxx,maxy);
    glVertex2i(maxx,toolbar_height);
    glVertex2i(0,toolbar_height);
    glEnd();

    // display headin "PAINT"
    glColor3ub(0,0,0);
    for(i=0;string[i]!='\0';i++)
    {
    glRasterPos2i(10+i*14,toolbar_height/2-9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
    }
    // "PAINT text is over at x=80

    //drawing box for tools starting at x=100
    glLineWidth(3.0);
    for(i=0;i<7;i++)
    {
        glColor3ub(0,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(200+i*40,maxy-20);
        glVertex2i(200+i*40+40,maxy-20);
        glVertex2i(200+i*40+40,toolbar_height+20);
        glVertex2i(200+i*40,toolbar_height+20);
        glEnd();
    }
    //dox for toolend at x=480

    // rectangle for clear screen

    // rectangle for point size or line size
    glBegin(GL_LINE_LOOP);
    glVertex2i(500,maxy-20);
    glVertex2i(570,maxy-20);
    glVertex2i(570,toolbar_height+20);
    glVertex2i(500,toolbar_height+20);
    glEnd();

    strcpy(string,"CLEAR");
    glColor3ub(0,0,0);
    for(i=0;string[i]!='\0';i++)
    {
    glRasterPos2i(502+i*12,toolbar_height/2-9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
    }

 /*   glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2i(500+16,toolbar_height+40);
    glEnd();
    glPointSize(6.0);
    glBegin(GL_POINTS);
    glVertex2i(500+32,toolbar_height+40);
    glEnd();
    glPointSize(8.0);
    glBegin(GL_POINTS);
    glVertex2i(500+48,toolbar_height+40);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2i(500+60,toolbar_height+30);
    glVertex2i(500+60,toolbar_height+50);
    glEnd();
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2i(500+70,toolbar_height+30);
    glVertex2i(500+70,toolbar_height+50);
    glEnd();
    glLineWidth(6.0);
    glBegin(GL_LINES);
    glVertex2i(500+82,toolbar_height+30);
    glVertex2i(500+82,toolbar_height+50);
    glEnd();
   */ //point size or line size end at x=600

    // draw rectangle for color shades

    glBegin(GL_QUADS);
    glColor3fv(color[colorflag]);
    glVertex2i(maxx-90,maxy-10);
    glColor3f(1.0,1,1.0);
    glVertex2i(maxx-10,maxy-10);
    glColor3f(.0,0,0);
    glVertex2i(maxx-10,toolbar_height+10);
    glColor3f(0.0,0,0);
    glVertex2i(maxx-90,toolbar_height+10);
    glEnd();

    pencil();
    twopointline();
    rectangle();
    polygon();
    circle(10,380,maxy-40);
    text();
    mesh();

}
void actionbar()
{
    float color[6][3]={{1.0,0.0,0.0},{1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,0.0},{0.0,1.0,1.0,},{0.0,0.0,1.0}};
    int i;
    glColor3ub(170,170,170);
    glBegin(GL_QUADS);
    glVertex2i(actionbar_width,toolbar_height);
    glVertex2i(maxx,toolbar_height);
    glVertex2i(maxx,0);
    glVertex2i(actionbar_width,0);
    glEnd();


    //drawins borderlines
    glColor3ub(0,0,0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2i(0,toolbar_height);
    glVertex2i(actionbar_width,toolbar_height);
    glVertex2i(actionbar_width,toolbar_height);
    glVertex2i(actionbar_width,0);
    glEnd();

    //drawing boxes for colors
    glLineWidth(3.0);

    for(i=0;i<6;i++)
    {
        glColor3ub(0,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(actionbar_width+20,maxy-120-i*40);
        glVertex2i(maxx-20,maxy-120-i*40);
        glVertex2i(maxx-20,maxy-120-i*40-40);
        glVertex2i(actionbar_width+20,maxy-120-i*40-40);
        glEnd();

        glBegin(GL_QUADS);
        glColor3fv(color[i]);
        glVertex2i(actionbar_width+20,maxy-120-i*40);
        glVertex2i(maxx-20,maxy-120-i*40);
        glVertex2i(maxx-20,maxy-120-i*40-38);
        glVertex2i(actionbar_width+20,maxy-120-i*40-38);
        glEnd();
    }

    // boxes for zoom in and zoom out and rotation options
    glColor3ub(0,0,0);
    for(i=0;i<4;i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2i(actionbar_width+20,maxy-380-i*40);
        glVertex2i(maxx-20,maxy-380-i*40);
        glVertex2i(maxx-20,maxy-380-i*40-40);
        glVertex2i(actionbar_width+20,maxy-380-i*40-40);
        glEnd();
    }
    zoom();
    rotate();
}

void statusbar()
{
    glColor3ub(170,170,170);
    glBegin(GL_QUADS);
    glVertex2i(0,30);
    glVertex2i(maxx,30);
    glVertex2i(maxx,0);
    glVertex2i(0,0);
    glEnd();

    glColor3ub(0,0,0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2i(0,30);
    glVertex2i(maxx,30);
    glEnd();

}

void display()
{
    int i,j=0;
    glClear(GL_COLOR_BUFFER_BIT);

    toolbar();
    actionbar();
    statusbar();


    //glColor3ub(100,100,150);
    //draw mesh
    if(meshcount)
    {
        //printf("helo");
        glLineWidth(1.0);
        glBegin(GL_LINES);
        for(i=0;i<actionbar_width;i+=40)
            for(j=30;j<toolbar_height;j+=40)
            {
                glVertex2i(i,30);
                glVertex2i(i,toolbar_height);
                glVertex2i(0,j);
                glVertex2i(actionbar_width,j);
            }
    }
    j=0;
    //glColor3ub(100,200,250);
   // glColor3ub(r,g,b);
    i=0;
    glPointSize(5.0);
    glBegin(GL_POINTS);
        while(i<=pencilpointcount)
        {
        glColor3fv(color[pencilpoints[i][2]]);
        glVertex2i(pencilpoints[i][0],pencilpoints[i][1]);
        i++;
        }
        glEnd();

     //draw lines here
     i=0;
     glPointSize(5.0);
        glBegin(GL_POINTS);
        while(i<=linepointcount)
        {
        glColor3fv(color[linepoints[i][2]]);
        glVertex2i(linepoints[i][0],linepoints[i][1]);
        i++;
        }
        glEnd();

        i=0;
        if(linepointcount!=0)
        {
            glLineWidth(2.0);
            glBegin(GL_LINES);
            while(i<=linepointcount)
            {
                glColor3fv(color[linepoints[i][2]]);
                //printf("hello\n:%d\n",pointcount);
                glVertex2i(linepoints[i][0],linepoints[i][1]);
                ++i;
            }
        }
    glEnd();

    //draw squares here
    i=0;
     glPointSize(5.0);
        glBegin(GL_POINTS);
        while(i<=squarepointcount)
        {
        glColor3fv(color[squarepoints[i][2]]);
        glVertex2iv(squarepoints[i]);
        i++;
        }
        glEnd();

    i=0;
        glLineWidth(2.0);
        glBegin(GL_LINES);
        while(i<=squarepointcount+8)
        {
        glColor3fv(color[squarepoints[i][2]]);
        glVertex2iv(squarepoints[i]);
        i++;
        }
        glEnd();

    i=0;
        glLineWidth(2.0);
        glBegin(GL_LINE_LOOP);
        while(i<=polypointcount)
        {
        glColor3fv(color[polypoints[i][2]]);
        glVertex2i(polypoints[i][0],polypoints[i][1]);
       // printf("%d|||%d",polypoints[i][0],polypoints[i][1]);
        i++;
        }
        glEnd();

    i=0;
    //draw circle here
    glPointSize(3.0);
    while(j<=circlepointcount)
    {
    glColor3fv(color[circlepoints[j][2]]);
    if(circlepointcount!=0)
    {
    glBegin(GL_POINTS);
    dist=sqrt((circlepoints[j+1][0]-circlepoints[j][0])*(circlepoints[j+1][0]-circlepoints[j][0])+(circlepoints[j+1][1]-circlepoints[j][1])*(circlepoints[j+1][1]-circlepoints[j][1]));
    for(i=0;i<360;i+=1)
    {
        glVertex2i(circlepoints[j][0]+dist*cos(i*3.14/180),circlepoints[j][1]+dist*sin(i*3.14/180));
    }
    glEnd();
    }
    j+=2;
    }

    i=0;
    while(i<=textcount)
    {
        glColor3fv(color[textpospoint[i][3]]);
        glRasterPos2i(textpospoint[i][0],textpospoint[i][1]);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,textpospoint[i][2]);
        i++;
    }

    glFlush();
}

void idle()
{
     int i;
    if(clear)
    {
        printf("boom\n");

    for(i=0;i<squarepointcount;i++)
        squarepoints[i][0]=squarepoints[i][1]=squarepoints[i][2]=0;
    squarepointcount=0;

    for(i=0;i<pencilpointcount;i++)
        pencilpoints[i][0]=pencilpoints[i][1]=pencilpoints[i][2]=0;
    pencilpointcount=0;

    for(i=0;i<polypointcount;i++)
        polypoints[i][0]=polypoints[i][1]=polypoints[i][2]=0;
    polypointcount=-1;

    for(i=0;i<circlepointcount;i++)
        circlepoints[i][0]=circlepoints[i][1]=circlepoints[i][2]=0;
    circlepointcount=0;

    for(i=0;i<textcount;i++)
        textpospoint[i][0]=textpospoint[i][1]=linepoints[i][2]=textpospoint[i][3]=0;
    textcount=0;

    for(i=0;i<linepointcount;i++)
        linepoints[i][0]=linepoints[i][1]=linepoints[i][2]=0;
    linepointcount=-1;
    }
    clear=0;
    glutPostRedisplay();

}
void init()
{
    glClearColor(0.85,0.85,0.85,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,maxx,0,maxy);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(maxx,maxy);
    glutCreateWindow("interface");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
}
