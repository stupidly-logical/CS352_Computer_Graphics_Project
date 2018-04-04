#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

float angle_tip = 0.0f, angle_view = 0.0f, angle_tilt = 0.0f;


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
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 0.90f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 0.90f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 1.0f, 3.0f);

	//Left Stair Set
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 0.25f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 0.60f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 0.60f, 2.05f);


	//Left Stair Set
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.40f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.05f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -0.05f, 2.05f);


	//Left Stair Set
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 0.25f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 0.25f, 3.0f);

	//Left Stair Set
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.05f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 0.25f, 2.65f);
}

void drawRightStairSet(){

	//Right Stair Set
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 0.90f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.90f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 1.0f, 3.0f);

	//Right Stair Set
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.25f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.60f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 0.60f, 2.05f);


	//Right Stair Set
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.25f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 0.25f, 3.0f);


	//Right Stair Set
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.60f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 0.25f, 2.65f);


	//Right Stair Set
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -0.40f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -0.40f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -1.0f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -1.0f, 3.0f);


	//Right Stair Set
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -0.40f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -0.70f, 1.75f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -1.0f, 1.75f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -1.0f, 2.65f);


	//Right Stair Set
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -0.70f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -0.70f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -1.0f, 2.65f);

}

void drawBottomSet(){
	
	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.5f);

	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -1.0f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -1.0f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -1.0f, -1.5f);


	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, -0.40f, 2.05f);


	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -0.05f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -0.05f, 2.65f);

	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -0.05f, 2.65f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 0.25f, 2.05f);

	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 0.25f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.25f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 0.25f, 1.5f);

	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, -0.40f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -0.40f, 2.05f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, -0.40f, 1.5f);

}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
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
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	//Front Stair Wall
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -1.0f, 3.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, -1.0f, 3.0f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 1.0f, 3.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 1.0f, 3.0f);
	
	drawLeftStairSet();

	drawRightStairSet();	

	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	
	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	
	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	
	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.5f);

	drawBottomSet();

	glEnd();
	
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

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Project");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKeypress);
	glutReshapeFunc(handleResize);
	
	//glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}








