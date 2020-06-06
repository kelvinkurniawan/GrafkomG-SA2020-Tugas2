#include <iostream> // Opsional
#include <math.h>
#include <GL/freeglut.h>

const double PI = 3.141592653589793;
int i;

double pos = 0;

void createPlanet(int rad, int point, int x_pos, int y_pos, float delta) {
	glBegin(GL_POLYGON);
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

	// Sun
	glColor3ub(241, 196, 15);
	createPlanet(10, 100, 100, 0, 0);

	// Mercury
	glColor3ub(212, 158, 120);
	createPlanet(2, 50, 100, 20, 20);

	// Venus
	glColor3ub(236, 191, 150);
	createPlanet(3, 100, 100, 40, 15);

	// Earth
	glColor3ub(0, 179, 235);
	createPlanet(5, 100, 100, 60, 10);

	// Mars
	glColor3ub(222, 51, 32);
	createPlanet(2.5, 100, 100, 90, 5);

	glFlush();
}

void animate(int) {
	pos += 0.001f;

	glutPostRedisplay();
	glutTimerFunc(7, animate, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Tugas Pertama ~ Kelvin Kurniawan");

	glutTimerFunc(7, animate, 0);
	glEnable(GL_POINT_SMOOTH);
	glutDisplayFunc(renderObject);
	gluOrtho2D(0, 200, 0, 200);

	glutMainLoop();

	return 0;
}