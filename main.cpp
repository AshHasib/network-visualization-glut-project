#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

struct point
{
	double x,y,z;
};


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);

                glVertex3f(0, i*10, -90);
				glVertex3f(0, i*10, 90);



			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}
void drawCube(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,a);
		glVertex3f( a,-a,a);
		glVertex3f(-a,-a,a);
		glVertex3f(-a, a,a);

		glVertex3f(a,a,-a);
		glVertex3f(a,-a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a,a,-a);

		glVertex3f(a,-a,a);
		glVertex3f(a,a,a);
		glVertex3f(a,a,-a);
		glVertex3f(a,-a,-a);


		glVertex3f(-a, -a,a);
		glVertex3f(-a,a,a);
		glVertex3f(-a,a,-a);
		glVertex3f(-a,-a,-a);


		glVertex3f( a,a,a);
		glVertex3f( a,a,-a);
		glVertex3f(-a,a,-a);
		glVertex3f(-a,a,a);

		glVertex3f(a,-a,a);
		glVertex3f(a,-a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a,-a,a);
	}glEnd();
}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

double tx=0;
double ty=0;
double rx=0;

int width = 720;
int height = 640;


bool routerFlag = false;
bool serverFlag = false;
bool hackerFlag= false;

char *hackerMessage = "HACKER INTERRUPTION!!";
char *routerMessage = "ROUTER TO COMPUTER INTERACTION";
char *serverMessage = "SERVER TO ROUTER TO COMPUTER INTERACTION";




float c1 = 1.0;
float c2 = 0.6;
float c3 = 0.1;


float b1 = 0;
float b2 = 0;
float b3 = 1;

float r1 = 1;
float r2 = 0;
float r3 = 0;



float rToCColor1= c1;
float rToCColor2 = c2;
float rToCColor3 = c3;

float sToRColor1 = c1;
float sToRColor2 = c2;
float sToRColor3 = c3;

float hToSColor1 = c1;
float hToSColor2 = c2;
float hToSColor3 = c3;


float temp=0;

void drawText(const char *text, int length, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0,800,0,600,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);

    for(int i=0;i<length;i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

float hTocSTranslate = -43;
float sToRTranslate = 0;


/**
Method to draw all the components
*/
void drawSS()
{
    int tInit = 580;



    /**
    Initial Text
    */
    glPushMatrix();
    {
        glColor3f(0,1,0);
        drawText("Network Packet Transmission", strlen("Network Packet Transmission"), 0, tInit);
        glColor3f(1,0,0);
        drawText("Author: Hasib", 14, 0, tInit-=20);
        glColor3f(0,0,1);
        drawText("r - router interaction", 10,0, tInit-=20);
        //glColor3f(1,0,0);
        drawText("h - hacker interruption", 23,0,tInit-=20);
        drawText("s - server interaction", 24, 0, tInit-20);


        if (routerFlag && !hackerFlag && !serverFlag) {
            glColor3f(0,0,1);
            drawText(routerMessage, strlen(routerMessage), 0, tInit-40);
        }
        else if (serverFlag && !hackerFlag && !routerFlag) {
            glColor3f(0,0,1);
            drawText(serverMessage, strlen(serverMessage), 0, tInit-40);
        }
        else if (hackerFlag && !routerFlag && !serverFlag) {
            glColor3f(1,0,0);
            drawText(hackerMessage, strlen(hackerMessage), 0, tInit-40);
        }
        else {
            glColor3f(1,1,1);
            drawText("Press any key to see action", strlen("Press any key to see action"), 0, tInit-40);
        }

    }
    glPopMatrix();




    /**
    * Main Server
    */
    glPushMatrix();
    {
        glTranslatef(20,0,0);
        glColor3f(255.0/255.0,128.0/255.0,0);
        glScalef(1,1.5,1);
        drawCube(5);

        //design
        glTranslatef(0,3,4);
        glColor3f(0,0.6,0);
        glScalef(9,1,1);
        drawSquare(.5);

        glTranslatef(0,-3,0);
        //glColor3f(1,0,0);
        drawSquare(.5);

        glTranslatef(0,-3,0);
        //glColor3f(1,0,0);
        drawSquare(.5);
    }
    glPopMatrix();


    /**
    * Connection wire
    */
    glPushMatrix();
    {
        glTranslatef(20,30,0);
        glScalef(1,60,1);
        glColor3f(sToRColor1,sToRColor2,sToRColor3);
        drawSquare(0.4);
    }
    glPopMatrix();


    /**
    * Router
    */
    glPushMatrix();
    {
        glScalef(1,1,1);
        glTranslatef(20,60,0);
        glColor3f(0,0,1);
        drawCube(5);

        //design
        glTranslatef(0,3.5,6.5);
        glColor3f(1,1,1);
        glScalef(9,1.5,1);
        drawSquare(.3);

        glTranslatef(0,-5,0);
        drawSquare(.3);

        glTranslatef(-.3,1.5,0);
        glScalef(.09,6,1);
        drawSquare(.3);
    }
    glPopMatrix();

    /**
    * Computer 1
    */
    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(60,60,0);
        glScalef(1,1.5,1);
        drawCube(3);

        //design
        glTranslatef(0,1.5,1.5);
        glColor3f(1,1,1);
        glScalef(9,1,1);
        drawSquare(.3);


        glTranslatef(0,-3,0);
        //glColor3f(1,0,0);
        drawSquare(.3);

        glTranslatef(-.3,1.5,0);
        glScalef(.09,6,1);
        drawSquare(.3);


    }
    glPopMatrix();

    /**
    * Router - Computer 1
    */
    glPushMatrix();
    {
        glTranslatef(40,60,0);
        glScalef(50,1,1);
        glColor3f(rToCColor1,rToCColor2,rToCColor3);
        drawSquare(0.4);


    }
    glPopMatrix();


    /**
    * Computer 2
    */
    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(-20,60,0);
        glScalef(1,1.5,1);
        drawCube(3);

        //design
        glTranslatef(0,1.5,1.5);
        glColor3f(1,1,1);
        glScalef(9,1,1);
        drawSquare(.3);


        glTranslatef(0,-3,0);
        //glColor3f(1,0,0);
        drawSquare(.3);

        glTranslatef(-.3,1.5,0);
        glScalef(.09,6,1);
        drawSquare(.3);

    }
    glPopMatrix();

    /**
    * Router - Computer 2
    */
    glPushMatrix();
    {
        glTranslatef(0,60,0);
        glScalef(50,1,1);
        glColor3f(rToCColor1,rToCColor2,rToCColor3);
        drawSquare(0.4);
    }
    glPopMatrix();



    /**
    * Computer 3
    */
    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(20,90,0);
        glScalef(1,1.5,1);
        drawCube(3);

        //design
        glTranslatef(0,1.5,1.5);
        glColor3f(1,1,1);
        glScalef(9,1,1);
        drawSquare(.3);


        glTranslatef(0,-3,0);
        //glColor3f(1,0,0);
        drawSquare(.3);

        glTranslatef(-.3,1.5,0);
        glScalef(.09,6,1);
        drawSquare(.3);
    }
    glPopMatrix();

    /**
    * Router - Computer 3
    */
    glPushMatrix();
    {
        glTranslatef(20,70,0);
        glScalef(1,40,1);
        glColor3f(rToCColor1,rToCColor2,rToCColor3);
        drawSquare(0.4);
    }
    glPopMatrix();



    /**
    * Hacker
    */
    glPushMatrix();
    {
        glTranslatef(-40,0,0);
        glColor3f(1,0,0);
        glScalef(1,2,1);
        drawCube(5);

        //design
        glColor3f(1,1,1);
        glTranslatef(-3,0,3.5);
        glScalef(1,5,1);
        drawSquare(.5);

        glTranslatef(6,0,0);
        drawSquare(.5);


        glTranslatef(-3,0.5,0);
        glScalef(5,0.07,1);
        drawSquare(.5);



    }
    glPopMatrix();

    /**
    * Hacker -server
    */

    glPushMatrix();
    {
        glTranslatef(-10,0,0);
        glScalef(80,1,1);
        glColor3f(hToSColor1,hToSColor2,hToSColor3);
        drawSquare(0.4);
    }
    glPopMatrix();


    /**
    * hacker transmitting data
    */
    glPushMatrix();
    {   glTranslatef(hTocSTranslate,0,0);
        glColor3f(1,0,0);
        drawCube(1);
    }glPopMatrix();

    glPushMatrix();
    {   glTranslatef(hTocSTranslate+3,0,0);
        glColor3f(1,0,0);
        drawCube(1);
    }glPopMatrix();

    glPushMatrix();
    {   glTranslatef(hTocSTranslate+6,0,0);
        glColor3f(1,0,0);
        drawCube(1);
    }glPopMatrix();



    /**
    * Server to router data transmission
    */
    glPushMatrix();
    {   glTranslatef(20,sToRTranslate,0);
        glColor3f(0,0,1);
        drawCube(1);
    }glPopMatrix();
    glPushMatrix();
    {   glTranslatef(20,sToRTranslate+3,0);
        glColor3f(0,0,1);
        drawCube(1);
    }glPopMatrix();
    glPushMatrix();
    {   glTranslatef(20,sToRTranslate-3,0);
        glColor3f(0,0,1);
        drawCube(1);
    }glPopMatrix();



}



int xCameraAngle = -50;
int yCameraAngle = 50;
//int zCameraAngle = 0;

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

        case '4': {
            xCameraAngle -=5;
            break;
        }
        case '6': {
            xCameraAngle+=5;
            break;
        }

        case '2': {
            yCameraAngle -=5;
            break;
        }
        case '8': {
            yCameraAngle+=5;
            break;
        }

        case 'h': {
            hackerFlag = true;
            routerFlag = false;
            serverFlag = false;
            printf("Hacker interruption.\n");
            break;
        }

        case 's': {
            hackerFlag = false;
            routerFlag = false;
            serverFlag = true;
            printf("Server Interaction.\n");
            break;
        }

        case 'r': {
            hackerFlag = false;
            routerFlag = true;
            serverFlag = false;
            printf("Router to Computer Interaction.\n");
            break;
        }

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;
  drawSquare(20);
		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y) {	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			  drawSquare(20);break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(xCameraAngle,yCameraAngle, 200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

    glColor3f(1,0,0);
    //drawSquare(10);
    //drawCube(20);

    drawSS();
    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


bool isRed = false;
bool isYellow = true;
bool isBlue = false;

void animate(){




    if(hackerFlag) {
        sToRTranslate=0;
        hTocSTranslate+=0.3;
        if(hTocSTranslate>15) {
            hTocSTranslate=-40;
        }

        temp+=0.13;

        if (temp>3 && isYellow) {
            hToSColor1 = r1;
            hToSColor2 = r2;
            hToSColor3 = r3;
            sToRColor1= r1;
            sToRColor2 = r2;
            sToRColor3 = r3;
            rToCColor1= r1;
            rToCColor2 = r2;
            rToCColor3 = r3;
            isRed = true;
            isYellow = false;
            temp=0;
        }
        else if (temp>3 && isRed || isBlue) {
            hToSColor1= c1;
            hToSColor2 = c2;
            hToSColor3 = c3;
            sToRColor1= c1;
            sToRColor2 = c2;
            sToRColor3 = c3;
            rToCColor1= c1;
            rToCColor2 = c2;
            rToCColor3 = c3;
            isRed = false;
            isBlue = false;
            isYellow = true;
            temp = 0;
        }
    }


    else if (serverFlag) {
        hTocSTranslate=-43;
        sToRTranslate+=0.3;

        if(sToRTranslate>50) {
            sToRTranslate=0;
        }


        temp+=0.13;

        if (temp>3 && isYellow) {
            sToRColor1= b1;
            sToRColor1 = b2;
            sToRColor1 = b3;
            rToCColor1= b1;
            rToCColor1 = b2;
            rToCColor1 = b3;
            isBlue = true;
            isYellow = false;
            temp=0;
        }
        else if (temp>3 && isBlue) {
            sToRColor1= c1;
            sToRColor1 = c2;
            sToRColor1 = c3;
            rToCColor1= c1;
            rToCColor1 = c2;
            rToCColor1 = c3;
            temp = 0;
            isYellow = true;
            isBlue = false;
        }
    }
    else if (routerFlag) {
        temp+=0.13;

        if (temp>3 && isYellow) {
            rToCColor1= b1;
            rToCColor1 = b2;
            rToCColor1 = b3;
            isBlue = true;
            isYellow = false;
            temp=0;
        }
        else if (temp>3 && isBlue) {
            rToCColor1= c1;
            rToCColor1 = c2;
            rToCColor1 = c3;
            temp = 0;
            isYellow = true;
            isBlue = false;
        }
    }

	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=1;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();


	glutReshapeWindow(width, height);
	//give PERSPECTIVE parameters
	//gluPerspective(80,	1,	1,	1000.0);
	gluPerspective(50, (double)width/(double) height, 1, 256);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
