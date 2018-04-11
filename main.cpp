#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

float angle_tip = 0.0f, angle_view = 0.0f, angle_tilt = 0.0f;
GLuint _textureGrass, _textureWindow, _textureSky, _textureWall, _textureGlass, _textureLogo;
const int SKY_FRONT=0,SKY_RIGHT=1,SKY_LEFT=2,SKY_BACK=3,SKY_UP=4,SKY_DOWN=5;
GLuint skybox[6];
GLuint grass;
// float pass[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

GLuint LoadBMP(const char *fileName)
{
	FILE *file;
	unsigned char header[54],*data;
	unsigned int dataPos,size,width, height;
	file = fopen(fileName, "rb");
	fread(header, 1, 54, file);
	dataPos		= *(int*)&(header[0x0A]);
	size		= *(int*)&(header[0x22]);
	width		= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);
	if (size == NULL)
		size = width * height * 3;
	if (dataPos == NULL)
		dataPos = 54;
	data = new unsigned char[size];
	fread(data, 1, size, file);
	fclose(file);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); 
	return texture;
}

void initSky()
{
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);														
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
		skybox[SKY_DOWN] = LoadBMP("BMP11/down.bmp");
		skybox[SKY_FRONT] = LoadBMP("BMP11/front.bmp");
		skybox[SKY_BACK] = LoadBMP("BMP11/back.bmp");
		skybox[SKY_RIGHT] = LoadBMP("BMP11/right.bmp");
		skybox[SKY_LEFT] = LoadBMP("BMP11/left.bmp");
		skybox[SKY_UP] = LoadBMP("BMP11/up.bmp");
		grass=LoadBMP("BMP11/grass_1.bmp");
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length){

	//glDisable(GL_DEPTH_TEST);
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_UP]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z); 
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();
 
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_DOWN]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
	glEnd();
 	glDisable(GL_TEXTURE_2D);

}


void draw_ground()
{		
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,grass);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10,0,10);
	glTexCoord2f(800.0f, 0.0f); glVertex3f(10,0,-10);
	glTexCoord2f(800.0f, 800.0f); glVertex3f(-10,0,-10);
	glTexCoord2f(0.0f, 800.0f); glVertex3f(-10,0,10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
		case 'z':
			angle_tilt -= 5;
			break;
		case 'x':
			angle_tilt += 5;
			break;
	}

	glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y){
	switch(key){
       case GLUT_KEY_LEFT :
       angle_tip -= 5;  break;
       case GLUT_KEY_RIGHT:  
       angle_tip += 5;  break;
       case GLUT_KEY_UP   :  
       angle_view -= 5;  break;
       case GLUT_KEY_DOWN :  
       angle_view += 5;  break;
	}

	glutPostRedisplay();
}

//Loading image data for texturing



//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawLeftStairSet(){

	//Left Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, 0.90f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, 0.90f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.25f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.25f, 1.0f, 3.0f);
	glEnd();

	//Left Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, 0.25f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.25f, 0.60f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.25f, 0.60f, 2.05f);
	glEnd();

	//Left Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -0.40f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.25f, -0.05f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.25f, -0.05f, 2.05f);
	glEnd();

	//Left Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.25f, 0.25f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.25f, 0.25f, 3.0f);
	glEnd();

	//Left Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.25f, -0.05f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.25f, 0.25f, 2.65f);
	glEnd();
}

void drawRightStairSet(){

	//Right Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.25f, 0.90f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, 0.90f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, 1.0f, 3.0f);
	glEnd();

	//Right Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, 0.25f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, 0.60f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, 0.60f, 2.05f);
	glEnd();


	//Right Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, 0.25f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, 0.25f, 3.0f);
	glEnd();


	//Right Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, 0.60f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, 0.25f, 2.65f);
	glEnd();


	//Right Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.25f, -0.40f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, -0.40f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, -1.0f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, -1.0f, 3.0f);
	glEnd();

	//Right Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.25f, -0.40f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, -0.70f, 1.75f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, -1.0f, 1.75f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, -1.0f, 2.65f);
	glEnd();

	//Right Stair Set
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.25f, -0.70f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, -0.70f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, -1.0f, 2.65f);
	glEnd();

}

void drawBottomSet(){

	//Bottom
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -1.0f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, -1.0f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, -1.0f, -1.5f);
	glEnd();

	//Bottom
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.0f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.0f, -0.40f, 2.05f);
	glEnd();

	//Bottom
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, -0.05f, 2.65f);
	glEnd();

	//Bottom
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.0f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.0f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, 0.25f, 2.05f);
	glEnd();

	//Bottom
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, 0.25f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, 0.25f, 1.5f);
	glEnd();

	//Bottom
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -0.40f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.25f, -0.40f, 1.5f);
	glEnd();

}

void drawTailSet() {

	//Left
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.2f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.2f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, 1.0f, -5.0f);
	glEnd();

	//Right
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(2.2f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(2.2f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.2f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(2.2f, 1.0f, -5.0f);
	glEnd();

	//Back
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.2f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(2.2f, -1.0f, -5.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.2f, 1.0f, -5.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, 1.0f, -5.0f);
	glEnd();

	//Front-Box
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.7f, -0.3f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.2f, -0.3f, -4.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, 1.0f, -4.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.7f, 1.0f, -4.0f);
	glEnd();

	//Left-Box
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.7f, -0.3f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.7f, -0.3f, -4.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.7f, 1.0f, -4.0f);
	//glNormal3f(.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.7f, 1.0f, -5.0f);
	glEnd();

	//Back-Box
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.7f, -0.3f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.2f, -0.3f, -5.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, 1.0f, -5.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.7f, 1.0f, -5.0f);
	glEnd();

}
/*
void drawWindow(){
	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(pass[0][0], pass[0][1], pass[0][2]);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(pass[1][0], pass[1][1], pass[1][2]);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(pass[2][0], pass[2][1], pass[2][2]);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(pass[3][0], pass[3][1], pass[3][2]);
	glEnd();
}
*/

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	 Draw_Skybox(0,0,0,250,250,250);
	
	glTranslatef(0.0f, 0.0f, -8.0f);
	
	//Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {100.0f, 100.0f, 100.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Add directed light
	GLfloat lightColor1[] = {0.0f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	glRotatef(angle_tip, 0.0f, 1.0f, 0.0f);
	glRotatef(angle_view, 1.0f, 0.0f, 0.0f);
	glRotatef(angle_tilt, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);


	//Front Stair Wall
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -1.0f, 3.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, -1.0f, 3.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, 1.0f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.25f, 1.0f, 3.0f);
	glEnd();
	

	//Front Stair Wall Top
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.25f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.25f, 1.0f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.25f, 1.0f, 3.0f);
	glEnd();
	
	drawLeftStairSet();

	drawRightStairSet();	

	//Front-Left
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.5f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.1f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-2.1f, 1.0f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.5f, 1.0f, 1.2f);
	glEnd();

	//Front-Left-Office
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.1f, -1.0f, 1.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -1.0f, 1.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, 1.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.1f, 1.0f, 1.0f);
	glEnd();

	//Front-Left-Office-right wall
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.2f, -1.0f, 1.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.2f, 1.0f, 1.0f);
	glEnd();

	//Front-Left-Office-left wall
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.1f, -1.0f, 1.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.1f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-2.1f, 1.0f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.1f, 1.0f, 1.0f);
	glEnd();

	//Front
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.2f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.8f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.8f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.2f, 1.0f, 1.5f);
	glEnd();
	
	//Front-Right
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.8f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(2.5f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.5f, 1.0f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.8f, 1.0f, 1.2f);
	glEnd();

	//Front-Right-left wall
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.8f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.8f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.8f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.8f, 1.0f, 1.2f);
	glEnd();

	//Right
	// glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureWall);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(2.5f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(2.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.5f, 1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(2.5f, -1.0f, 1.2f);
	glEnd();
	// glDisable(GL_TEXTURE_2D);
	
	//Back
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(2.5f, -1.0f, -1.5f);
	glEnd();
	
	//Left

	// glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.5f, -1.0f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-2.5f, 1.0f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.5f, 1.0f, -1.5f);
	glEnd();
	// glDisable(GL_TEXTURE_2D);

	//Left Window-top-left
	glBindTexture(GL_TEXTURE_2D, _textureWindow);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.51f, -0.7f, -1.1f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.51f, -0.7f, -0.7f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-2.51f, -0.3f, -0.7f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.51f, -0.3f, -1.1f);
	glEnd();

	// pass[4][3]={{-2.5,0.0,0.0},{-2.5,0.0,0.5},{-2.5,0.5,0.0},{-2.5,0.5,0.0}};
	// drawWindow();

	drawTailSet();
/*
	//Top
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 0.9f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 0.9f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 0.9f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 0.9f, 1.5f);
*/
	//Bottom
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.2f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.8f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.8f, -1.0f, -1.5f);
	glEnd();

	drawBottomSet();

	glDisable(GL_TEXTURE_2D);
	
	glutSwapBuffers();
}

void update(int value) {
	angle_tip = value;
	angle_tip += 1.5f;
	if (angle_tip > 360) {
		angle_tip -= 360;
	}
	
	glutPostRedisplay();
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	    _textureSky = LoadBMP("sky.bmp");
	    _textureWindow = LoadBMP("window.bmp");
	    _textureWall = LoadBMP("wall.bmp");
	    _textureGrass = LoadBMP("grass.bmp");
	    _textureGlass = LoadBMP("glass.bmp");
	    _textureLogo = LoadBMP("logo.bmp");
	}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);
	
	//Create the window
	glutCreateWindow("Project");
	initRendering();
	initSky();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKeypress);
	glutReshapeFunc(handleResize);
	
	//glutTimerFunc(25, update, 0); //Add a timer
	Initialize();
	glutMainLoop();
	return 0;
}
