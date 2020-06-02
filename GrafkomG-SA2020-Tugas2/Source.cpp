#include <iostream> // Opsional
#include <math.h>
#include <GL/freeglut.h>

const double PI = 3.141592653589793;
int i;

void createPlanet(int rad, int point, int x_pos, int y_pos) {
	glBegin(GL_POLYGON);
	for (i = 0; i <= 360; i++) {
		float A = i * (2 * PI / point);
		float x = x_pos + rad * cos(A);
		float y = y_pos + rad * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void renderObject() {
	glPointSize(5);

	glColor3f(1, 1, 1);

	// Sun
	glColor3ub(241, 196, 15);
	createPlanet(10, 100, 100, 100);

	// Mercury
	glColor3ub(212, 158, 120);
	createPlanet(2, 50, 100, 80);

	// Venus
	glColor3ub(236, 191, 150);
	createPlanet(3, 100, 100, 60);

	// Earth
	glColor3ub(0, 179, 235);
	createPlanet(5, 100, 100, 35);

	// Mars
	glColor3ub(222, 51, 32);
	createPlanet(2.5, 100, 100, 5);

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Tugas Pertama ~ Kelvin Kurniawan");
	glutDisplayFunc(renderObject);
	gluOrtho2D(0, 200, 0, 200);

	glutMainLoop();

	return 0;
}