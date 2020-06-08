#include <iostream> // Opsional
#include <math.h>
#include <GL/freeglut.h>

const double PI = 3.141592653589793;
int i;

double pos = 0;
double satellitePos = 0;

void createPlanet(int rad, int x_pos, int y_pos, float delta) {
	glBegin(GL_POLYGON);
	for (i = 0; i <= 360; i++) {
		float A = (2 * PI) * i / 360;
		float x = cos(A) * rad + (cos(pos * delta) * y_pos + x_pos);
		float y = sin(A) * rad + (sin(pos * delta) * y_pos + x_pos);
		glVertex2f(x, y);
		glColor3ub(20, 20, 20);
	}
	glEnd();
}

void trackPlane(int x_pos, int y_pos, float delta) {
	glBegin(GL_LINES);
	glColor3ub(60, 60, 60);
	glVertex2f(100, 100);
	for (i = 0; i <= 360; i++) {
		float A = (2 * PI) * i / 360;
		float x = cos(A) + (cos(pos * delta) * y_pos + x_pos);
		float y = sin(A) + (sin(pos * delta) * y_pos + x_pos);
		glVertex2f(x, y);
	}
	glEnd();
}


void createOrbit(int rad) {
	int center = 100;
	glColor3ub(60, 60, 60);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= 360; i++) {
		float A = (2 * PI) * i / 360;
		float x = cos(A) * rad + center;
		float y = sin(A) * rad + center;
		glVertex2f(x, y);
	}
	glEnd();
}


void createSatellite(int rad, int x_pos, int y_pos, float delta, float deltaSatellite, float radiusSatellite) {
	glBegin(GL_POLYGON);
	glColor4ub(255, 255, 255, 255);
	for (i = 0; i <= 360; i++) {
		float A = (2 * PI) * i / 360;
		float x = cos(A) * rad + (cos(deltaSatellite * satellitePos) * radiusSatellite + (cos(pos * delta) * y_pos + x_pos));
		float y = sin(A) * rad + (sin(deltaSatellite * satellitePos) * radiusSatellite + (sin(pos * delta) * y_pos + x_pos));
		glVertex2f(x, y);
		glColor3ub(20, 20, 20);
	}
	glEnd();
}

void createSatelliteOrbit(int rad, int x_pos, int y_pos, float delta) {
	int center = 100;
	glColor3ub(60, 60, 60);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= 360; i++) {
		float A = (2 * PI) * i / 360;
		float x = cos(A) * rad + (cos(pos * delta) * y_pos + x_pos);
		float y = sin(A) * rad + (sin(pos * delta) * y_pos + x_pos);
		glVertex2f(x, y);
	}
	glEnd();
}


void renderObject() {
	glClear(GL_COLOR_BUFFER_BIT);

	// create orbit
	createOrbit(20);
	createOrbit(40);
	createOrbit(60);
	createOrbit(90);

	trackPlane(100, 20, 20);
	trackPlane(100, 40, 15);
	trackPlane(100, 60, 10);
	trackPlane(100, 90, 5);

	createSatelliteOrbit(12, 100, 60, 10);
	createSatelliteOrbit(5, 100, 90, 5);
	createSatelliteOrbit(10, 100, 90, 5);

	createSatellite(2, 100, 60, 10, 5, 12);
	createSatellite(1, 100, 90, 5, 4.5, 5);
	createSatellite(1, 100, 90, 5, 5, 10);
	// create plane

	// Sun
	glColor3ub(241, 196, 15);
	createPlanet(10, 100, 0, 0);

	// Mercury
	glColor3ub(212, 158, 120);
	createPlanet(2, 100, 20, 20);

	// Venus
	glColor3ub(236, 191, 150);
	createPlanet(4, 100, 40, 15);

	// Earth
	glColor3ub(0, 179, 235);
	createPlanet(6, 100, 60, 10);

	// Mars
	glColor3ub(222, 51, 32);
	createPlanet(3, 100, 90, 5);

	glFlush();
}

void animate(int) {
	pos += 0.00075f;
	satellitePos += 0.005f;

	glutPostRedisplay();
	glutTimerFunc(7, animate, 0);
}

void key(unsigned char key, int x, int y) {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Tugas Pertama ~ Kelvin Kurniawan");

	glutTimerFunc(7, animate, 0);
	glutDisplayFunc(renderObject);
	glutKeyboardFunc(key);
	gluOrtho2D(0, 200, 0, 200);

	glutMainLoop();

	return 0;
}