#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

float angle_tip = 0.0f, angle_view = 0.0f, angle_tilt = 0.0f;
GLuint _textureGrass, _textureWindow, _textureSky, _textureWall, _textureGlass, _textureLogo, _texturePillar, _textureTile, _textureDoor, _textureFrame;
const int SKY_FRONT=0,SKY_RIGHT=1,SKY_LEFT=2,SKY_BACK=3,SKY_UP=4,SKY_DOWN=5;
GLuint skybox[6];
GLuint grass;
GLfloat d[3] = {0,0,-10.8};
GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
GLfloat lightColor1[] = {0.0f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)

GLuint LoadBMP(const char *fileName) {
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

void initSky() {
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);														
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
		skybox[SKY_DOWN] = LoadBMP("Sky/down.bmp");
		skybox[SKY_FRONT] = LoadBMP("Sky/front.bmp");
		skybox[SKY_BACK] = LoadBMP("Sky/back.bmp");
		skybox[SKY_RIGHT] = LoadBMP("Sky/right.bmp");
		skybox[SKY_LEFT] = LoadBMP("Sky/left.bmp");
		skybox[SKY_UP] = LoadBMP("Sky/up.bmp");
		grass=LoadBMP("Sky/grass_1.bmp");
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

void draw_ground() {
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

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
		exit(0); break;
		case 'q':
		angle_tilt -= 1.5; break;
		case 'w':
		angle_tilt += 1.5; break;
		case 'a' :
		angle_tip -= 1.5;  break;
		case 's':  
		angle_tip += 1.5;  break;
		case 'z':  
		angle_view -= 1.5;  break;
		case 'x':  
		angle_view += 1.5;  break;
        case 'l':
        lightColor0[0] += 1;
        if(lightColor0[0] > 3)
            lightColor0[0] = 1;
        lightColor0[1] += 1;
            if(lightColor0[1] > 3)
                lightColor0[1] = 1;
        lightColor0[2] += 1;
            if(lightColor0[2] > 3)
                lightColor0[2] = 1;
	}

	glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y){
	switch(key){
       case GLUT_KEY_LEFT :
       d[0] -= 0.5;  break;
       case GLUT_KEY_RIGHT:  
       d[0] += 0.5;  break;
       case GLUT_KEY_UP   :  
       d[2] -= 0.5;  break;
       case GLUT_KEY_DOWN :  
       d[2] += 0.5;  break;
	}

	glutPostRedisplay();
}

void handleMouseKeyPress(int button, int state, int x, int y){
}

void handlePassiveMotion(int x, int y){
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawLeftWindow(){
	glBindTexture(GL_TEXTURE_2D, _textureFrame);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.0f, -0.17f, -0.17f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.0f, -0.17f, 0.17f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.0f, 0.17f, 0.17f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.0f, 0.17f, -0.17f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.01f, -0.15f, -0.15f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.01f, -0.15f, 0.15f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.01f, 0.15f, 0.15f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.01f, 0.15f, -0.15f);
	glEnd();
}

void drawRightWindow(){
	glBindTexture(GL_TEXTURE_2D, _textureFrame);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.0f, -0.17f, -0.17f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.0f, -0.17f, 0.17f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.0f, 0.17f, 0.17f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.0f, 0.17f, -0.17f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.01f, -0.15f, -0.15f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.01f, -0.15f, 0.15f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.01f, 0.15f, 0.15f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.01f, 0.15f, -0.15f);
	glEnd();
}

void drawFrontWindow(){
	glBindTexture(GL_TEXTURE_2D, _textureFrame);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.17f, -0.17f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.17f, -0.17f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);z
	glTexCoord2f(1,1);	glVertex3f(0.17f, 0.17f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.17f, 0.17f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.151f, -0.15f, 0.01f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.15f, -0.15f, 0.01f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.15f, 0.15f, 0.01f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.15f, 0.15f, 0.01f);
	glEnd();
}

void drawBackWindow(){
	glBindTexture(GL_TEXTURE_2D, _textureFrame);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.17f, -0.17f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.17f, -0.17f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.17f, 0.17f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.17f, 0.17f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.151f, -0.15f, -0.01f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.15f, -0.15f, -0.01f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.15f, 0.15f, -0.01f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.15f, 0.15f, -0.01f);
	glEnd();
}

void drawdoor(){
	glBindTexture(GL_TEXTURE_2D, _textureFrame);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.8f, -0.85f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.4f, -0.85f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.4f, -0.5f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.8f, -0.5f, 1.0f);
	glEnd();
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
	glTexCoord2f(1,0);	glVertex3f(1.2f, -1.0f, -2.8f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, 1.0f, -2.8f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, 1.0f, -5.0f);
	glEnd();

	//Left Window-Top
	glPushMatrix();
	glTranslatef(1.19,0.6,-3.75);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glPopMatrix();

	//Left Window-Middle
	glPushMatrix();
	glTranslatef(1.19,0,-3.75);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glPopMatrix();

	//Left Window-Bottom
	glPushMatrix();
	glTranslatef(1.19,-0.6,-3.75);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glPopMatrix();

	//Left-Connector
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.4f, -1.0f, -2.8f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.8f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.8f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.4f, 1.0f, -2.8f);
	glEnd();

	//Right
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(2.2f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(2.2f, -1.0f, -2.8f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.2f, 1.0f, -2.8f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(2.2f, 1.0f, -5.0f);
	glEnd();

	//Right Window-Top
	glPushMatrix();
	glTranslatef(2.21,0.6,-4.7);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glPopMatrix();

	//Right Window-Middle
	glPushMatrix();
	glTranslatef(2.21,0,-4.7);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glPopMatrix();

	//Right Window-Bottom
	glPushMatrix();
	glTranslatef(2.21,-0.6,-4.7);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glTranslatef(0,0,0.5);
	drawRightWindow();
	glPopMatrix();

	//Right-Connector
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.8f, -1.0f, -2.8f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(2.2f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.2f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.8f, 1.0f, -2.8f);
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

	//Front
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.2f, -1.0f, -2.8f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(2.2f, -1.0f, -2.8f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(2.2f, 1.0f, -2.8f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, 1.0f, -2.8f);
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

	//Left Window-Top
	glPushMatrix();
	glTranslatef(0.69,0.63,-4.75);
	drawLeftWindow();
	glTranslatef(0,0,0.5);
	drawLeftWindow();
	glPopMatrix();

	//Left Window-Middle
	glPushMatrix();
	glTranslatef(0.69,0.03,-4.75);
	drawLeftWindow();
	glTranslatef(0,0,0.5);
	drawLeftWindow();
	glPopMatrix();

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

	//bottom-box
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.7f, -0.3f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.7f, -0.3f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.3f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.3f, -5.0f);
	glEnd();

	//Tail-Door
	glBindTexture(GL_TEXTURE_2D, _textureFrame);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.19f, -0.85f, -4.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.19f, -0.85f, -4.35f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.19f, -0.5f, -4.35f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.19f, -0.5f, -4.65f);
	glEnd();

}

void drawSmallStairs(){
	//Stair 1-bottom
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.7f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.7f, -1.0f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -1.0f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -1.0f, -5.0f);
	glEnd();

	//Stair 1-top
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.75f, -0.95f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.75f, -0.95f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.95f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.95f, -5.0f);
	glEnd();

	//Stair 1-back
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.75f, -0.95f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.75f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.95f, -5.0f);
	glEnd();

	//Stair 1-left
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.75f, -0.95f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.75f, -1.0f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.75f, -1.0f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.75f, -0.95f, -4.0f);
	glEnd();

	//Stair 1-front
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.75f, -0.95f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.75f, -1.0f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -1.0f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.95f, -4.0f);
	glEnd();

	//Stair 2-top
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.8f, -0.9f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.8f, -0.9f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.9f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.9f, -5.0f);
	glEnd();

	//Stair 2-back
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.8f, -0.9f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.8f, -0.95f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.95f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.9f, -5.0f);
	glEnd();

	//Stair 2-left
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.8f, -0.9f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.8f, -0.95f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.8f, -0.95f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.8f, -0.9f, -4.0f);
	glEnd();

	//Stair 2-front
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.8f, -0.9f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.8f, -0.95f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.95f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.9f, -4.0f);
	glEnd();

	//Stair 3-top
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.85f, -0.85f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.85f, -0.85f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.85f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.85f, -5.0f);
	glEnd();

	//Stair 3-back
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.85f, -0.85f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.85f, -0.9f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.9f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.85f, -5.0f);
	glEnd();

	//Stair 3-left
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.85f, -0.85f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.85f, -0.9f, -5.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.85f, -0.9f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.85f, -0.85f, -4.0f);
	glEnd();

	//Stair 3-front
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.85f, -0.85f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.85f, -0.9f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.2f, -0.9f, -4.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.2f, -0.85f, -4.0f);
	glEnd();
}

void drawPillar(){
	//box-pillar-back
	glBindTexture(GL_TEXTURE_2D, _texturePillar);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.9f, -0.95f, -4.9f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.9f, -0.3f, -4.9f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.95f, -0.3f, -4.9f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.95f, -0.95f, -4.9f);
	glEnd();

	//box-pillar-left
	glBindTexture(GL_TEXTURE_2D, _texturePillar);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.9f, -0.95f, -4.9f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.9f, -0.3f, -4.9f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.9f, -0.3f, -4.85f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.9f, -0.95f, -4.85f);
	glEnd();

	//box-pillar-front
	glBindTexture(GL_TEXTURE_2D, _texturePillar);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.9f, -0.95f, -4.85f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.9f, -0.3f, -4.85f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.95f, -0.3f, -4.85f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.95f, -0.95f, -4.85f);
	glEnd();

	//box-pillar-right
	glBindTexture(GL_TEXTURE_2D, _texturePillar);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.95f, -0.95f, -4.9f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.95f, -0.3f, -4.9f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.95f, -0.3f, -4.85f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.95f, -0.95f, -4.85f);
	glEnd();
}

void drawArch(){
	// top
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.2f, -0.35f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -0.35f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, -0.35f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.2f, -0.35f, 1.0f);
	glEnd();

	//bottom
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.2f, -0.4f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -0.4f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, -0.4f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.2f, -0.4f, 1.0f);
	glEnd();

	//left
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.2f, -0.4f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.2f, -0.4f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-2.2f, -0.35f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.2f, -0.35f, 1.0f);
	glEnd();

	//front
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.2f, -0.4f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -0.4f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, -0.35f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.2f, -0.35f, 1.8f);
	glEnd();

	//right
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.2f, -0.4f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -0.4f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, -0.35f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.2f, -0.35f, 1.0f);
	glEnd();

	glTranslatef(-2.2,-0.05,6.6);
	drawPillar();
	glTranslatef(2.2,0.05,-6.6);

	glTranslatef(-3.0,-0.05,6.6);
	drawPillar();
	glTranslatef(3.0,0.05,-6.6);

	//bottom of stairs under arch
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.2f, -0.99f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -0.99f, 1.8f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, -0.99f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.2f, -0.99f, 1.0f);
	glEnd();

	//Stairs continuation
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.1f, -0.85f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.2f, -0.85f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.2f, -0.85f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-2.1f, -0.85f, 1.0f);
	glEnd();

	//Stairs on office
	glPushMatrix();
	glRotatef(90,0.0,1,0);
	glTranslatef(-2.4,0,2.8);
	drawSmallStairs();
	glPopMatrix();

	//Stairs on stair set
	glPushMatrix();
	glTranslatef(-0.95,0,4.5);
	glScalef(1,1,1.49);
	glTranslatef(-0.3,0,2.99);
	drawSmallStairs();
	glPopMatrix();
}

void drawSlideStairs(){
	//Slide Stairs
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.71f, -1.0f, -3.4f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.3f, -1.0f, -3.4f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.3f, -0.69f, -3.4f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.71f, -0.69f, -3.4f);
	glEnd();
}

void drawBackstage(){

	//Front
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.71f, -1.0f, -3.4f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.3f, -1.0f, -3.4f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.3f, -0.69f, -3.4f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.71f, -0.69f, -3.4f);
	glEnd();

	//Left
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.71f, -1.0f, -4.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.71f, -1.0f, -3.4f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.71f, -0.69f, -3.4f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.71f, -0.69f, -4.2f);
	glEnd();

	//Back
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.71f, -1.0f, -4.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.3f, -1.0f, -4.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.3f, -0.69f, -4.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.71f, -0.69f, -4.2f);
	glEnd();

	//Right
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.3f, -1.0f, -4.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.3f, -1.0f, -3.4f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.3f, -0.69f, -3.4f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.3f, -0.69f, -4.2f);
	glEnd();

	//Top
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.71f, -0.69f, -4.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.71f, -0.69f, -3.4f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.3f, -0.69f, -3.4f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.3f, -0.69f, -4.2f);
	glEnd();

	//Stairs on backstage
	glPushMatrix();
	glRotatef(90,0.0,1,0);
	glTranslatef(-2.4,0,2.8);
	glTranslatef(4.75,0,0.5);
	drawSmallStairs();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,0.0,1,0);
	glTranslatef(-2.4,0,2.8);
	glTranslatef(4.9,0.15,0.5);
	drawSmallStairs();
	glPopMatrix();
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	 Draw_Skybox(0,0,0,250,250,250);
	 draw_ground();
	
	glTranslatef(d[0], d[1], d[2]);
	
	//Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	//Positioned light
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Directed light
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

	//Front-Left Window
	glPushMatrix();
	glScalef(0.85,0.85,1);
	glTranslatef(-2.71,0.7,1.21);
	drawFrontWindow();
	glTranslatef(0,-0.71,0);
	drawFrontWindow();
	glTranslatef(0,-0.71,0);
	drawFrontWindow();
	glPopMatrix();

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

	//Front-Left-Office-right wall Window
	glPushMatrix();
	glScalef(1,0.8,0.8);
	glTranslatef(-1.21,0.7,1.55);
	drawLeftWindow();
	glTranslatef(0,-0.71,0);
	drawLeftWindow();
	glTranslatef(0,-0.71,0);
	drawLeftWindow();
	glPopMatrix();

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

	drawArch();

	//Front
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.2f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.6f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.6f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.2f, 1.0f, 1.5f);
	glEnd();

	//Front Window-Top
	glPushMatrix();
	glTranslatef(-0.75,0.6,1.51);
	drawFrontWindow();
	glTranslatef(1.4,0,0);
	drawFrontWindow();
	glTranslatef(0.6,0,0);
	drawFrontWindow();
	glPopMatrix();

	//Front Window-Middle
	glPushMatrix();
	glTranslatef(-0.75,0,1.51);
	drawFrontWindow();
	glTranslatef(1.4,0,0);
	drawFrontWindow();
	glTranslatef(0.6,0,0);
	drawFrontWindow();
	glPopMatrix();

	//Front Window-Bottom
	glPushMatrix();
	glTranslatef(-0.75,-0.6,1.51);
	drawFrontWindow();
	glTranslatef(1.4,0,0);
	drawFrontWindow();
	glTranslatef(0.6,0,0);
	drawFrontWindow();
	glPopMatrix();

		
	//Front-Right
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.9f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(3.0f, -1.0f, 1.7f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(3.0f, 1.0f, 1.7f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.9f, 1.0f, 1.2f);
	glEnd();

	//Front Window-Top
	glPushMatrix();
	glRotatef(-24.4,0,1,0);
	glTranslatef(2.52,0.6,0.32);
	drawFrontWindow();
	glTranslatef(0.6,0,0);
	drawFrontWindow();
	glPopMatrix();

	//Front Window-Middle
	glPushMatrix();
	glRotatef(-24.4,0,1,0);
	glTranslatef(2.52,0,0.32);
	drawFrontWindow();
	glTranslatef(0.6,0,0);
	drawFrontWindow();
	glPopMatrix();

	//Front Window-Bottom
	glPushMatrix();
	glRotatef(-24.4,0,1,0);
	glTranslatef(2.52,-0.6,0.32);
	drawFrontWindow();
	glTranslatef(0.6,0,0);
	drawFrontWindow();
	glPopMatrix();

	//Front-Right-left wall
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.6f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.6f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.6f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.6f, 1.0f, 1.2f);
	glEnd();

	//Front-Right-back wall
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,0);	glVertex3f(1.6f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(1.9f, -1.0f, 1.2f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(1.9f, 1.0f, 1.2f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(1.6f, 1.0f, 1.2f);
	glEnd();

	//Front-Right-back wall-Window
	glBindTexture(GL_TEXTURE_2D, _textureFrame);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.8f, -0.85f, 1.01f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.5f, -0.85f, 1.01f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(-1.5f, -0.5f, 1.01f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-1.8f, -0.5f, 1.01f);
	glEnd();
	// glPushMatrix();
	// glTranslatef(-1.2,0.6,1.51);
	// drawdoor();
	// glPopMatrix();

	//Right
	// glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureWall);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(3.0f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(3.0f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(3.0f, 1.0f, 1.7f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0,1);	glVertex3f(3.0f, -1.0f, 1.7f);
	glEnd();
	// glDisable(GL_TEXTURE_2D);

	//Right Window-Top
	glPushMatrix();
	glTranslatef(3.01,0.6,-1.1);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glPopMatrix();

	//Right Window-Middle
	glPushMatrix();
	glTranslatef(3.01,-0.0,-1.1);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glPopMatrix();

	//Right Window-Bottom
	glPushMatrix();
	glTranslatef(3.01,-0.6,-1.1);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glTranslatef(0,0,0.6);
	drawRightWindow();
	glPopMatrix();
	
	//Back
	glBindTexture(GL_TEXTURE_2D, _textureWall);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-2.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-2.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(3.0f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(3.0f, -1.0f, -1.5f);
	glEnd();

	//Back-Glass door
	glBindTexture(GL_TEXTURE_2D, _textureWindow);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.25f, -1.0f, -1.51f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.25f, -0.3f, -1.51f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.5f, -0.3f, -1.51f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.5f, -1.0f, -1.51f);
	glEnd();

	//Back-Glass door frame 1
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-1.0f, -1.0f, -1.52f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-1.0f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.97f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.97f, -1.0f, -1.52f);
	glEnd();

	//Back-Glass door frame 2
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.75f, -1.0f, -1.52f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.75f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.72f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.72f, -1.0f, -1.52f);
	glEnd();

	//Back-Glass door frame 3
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.5f, -1.0f, -1.52f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.5f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.47f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.47f, -1.0f, -1.52f);
	glEnd();

	//Back-Glass door frame 4
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.25f, -1.0f, -1.52f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.25f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(-0.22f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-0.22f, -1.0f, -1.52f);
	glEnd();

	//Back-Glass door frame 5
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-0.0f, -1.0f, -1.52f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(-0.0f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.03f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.03f, -1.0f, -1.52f);
	glEnd();

	//Back-Glass door frame 6
	glBindTexture(GL_TEXTURE_2D, _textureTile);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(0.24f, -1.0f, -1.52f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);	glVertex3f(0.24f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,1);	glVertex3f(0.27f, -0.3f, -1.52f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(0.27f, -1.0f, -1.52f);
	glEnd();

	//Back Window-Top
	glPushMatrix();
	glTranslatef(2.62,0.63,-1.51);
	drawBackWindow();
	glTranslatef(-1.2,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glPopMatrix();

	//Back Window-Middle
	glPushMatrix();
	glTranslatef(2.62,0.03,-1.51);
	drawBackWindow();
	glTranslatef(-1.2,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glPopMatrix();

	//Back Window-Middle
	glPushMatrix();
	glTranslatef(2.62,-0.6,-1.51);
	drawBackWindow();
	glTranslatef(-1.2,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	// glTranslatef(-0.6,0,0);
	// drawBackWindow();
	// glTranslatef(-0.6,0,0);
	// drawBackWindow();
	// glTranslatef(-0.6,0,0);
	// drawBackWindow();
	glTranslatef(-2.4,0,0);
	drawBackWindow();
	glTranslatef(-0.6,0,0);
	drawBackWindow();
	glPopMatrix();
	
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

	//Left Window-Top
	glPushMatrix();
	glTranslatef(-2.51,0.6,-1.05);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glPopMatrix();

	//Left Window-Middle
	glPushMatrix();
	glTranslatef(-2.51,-0.0,-1.05);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glPopMatrix();

	//Left Window-Bottom
	glPushMatrix();
	glTranslatef(-2.51,-0.6,-1.05);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glTranslatef(0,0,0.6);
	drawLeftWindow();
	glPopMatrix();

	drawTailSet();
	drawSmallStairs();
	drawPillar();

	glTranslatef(0,0,0.8);
	drawPillar();
	glTranslatef(0,0,-0.8);
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
	glBindTexture(GL_TEXTURE_2D, _textureGrass);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,0);	glVertex3f(-3.0f, -1.01f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,0);	glVertex3f(3.2f, -1.01f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(1,1);	glVertex3f(3.2f, -1.01f, -5.2f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0,1);	glVertex3f(-3.0f, -1.01f, -5.2f);
	glEnd();

	drawBottomSet();

	drawBackstage();

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
	    _texturePillar = LoadBMP("pillar.bmp");
	    _textureTile = LoadBMP("tile.bmp");
	    _textureDoor = LoadBMP("door.bmp");
	    _textureFrame = LoadBMP("frame.bmp");
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
	glutMouseFunc(handleMouseKeyPress);
	glutPassiveMotionFunc(handlePassiveMotion);
	
	//glutTimerFunc(25, update, 0); //Add a timer
	Initialize();
	glutMainLoop();
	return 0;
}