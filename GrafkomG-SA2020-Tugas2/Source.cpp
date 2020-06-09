#include <iostream> // Opsional
#include <math.h>
#include <GL/freeglut.h>

const double PI = 3.141592653589793;
int i;

double pos = 0;
double satellitePos = 0;
double speed = 0;

bool isMove = true;
bool showOrbit = false;
bool showSatellite = false;
bool showSatelliteOrbit = false;
bool showTrackPlane = false;
bool showTrackSatellite = false;

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

void trackSatellite(int x_pos, int y_pos, float delta, float deltaSatellite, float radiusSatellite) {
	glColor3ub(60, 60, 60);

	glBegin(GL_LINES);
	for (i = 0; i <= 360; i++) {
		float A = (2 * PI) * i / 360;
		float x = cos(A) + (cos(pos * delta) * y_pos + x_pos);
		float y = sin(A) + (sin(pos * delta) * y_pos + x_pos);
		glVertex2f(x, y);
	}
	for (i = 0; i <= 360; i++) {
		float A = (2 * PI) * i / 360;
		float x = cos(A) + (cos(deltaSatellite * satellitePos) * radiusSatellite + (cos(pos * delta) * y_pos + x_pos));
		float y = sin(A) + (sin(deltaSatellite * satellitePos) * radiusSatellite + (sin(pos * delta) * y_pos + x_pos));
		glVertex2f(x, y);
		glColor3ub(20, 20, 20);
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
	if (showOrbit) {
		createOrbit(20);
		createOrbit(40);
		createOrbit(60);
		createOrbit(90);
	}

	if (showTrackPlane) {
		trackPlane(100, 20, 20);
		trackPlane(100, 40, 15);
		trackPlane(100, 60, 10);
		trackPlane(100, 90, 5);
	}

	if (showTrackSatellite) {
		trackSatellite(100, 60, 10, 5, 12);
		trackSatellite(100, 90, 5, 4.5, 5);
		trackSatellite(100, 90, 5, 5, 10);
	}

	if (showSatelliteOrbit) {
		createSatelliteOrbit(12, 100, 60, 10);
		createSatelliteOrbit(5, 100, 90, 5);
		createSatelliteOrbit(10, 100, 90, 5);
	}

	if (showSatellite) {
		createSatellite(2, 100, 60, 10, 5, 12);
		createSatellite(1, 100, 90, 5, 4.5, 5);
		createSatellite(1, 100, 90, 5, 5, 10);
	}

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
	if (isMove) {
		pos += 0.00075f + speed;
		satellitePos += 0.005f + speed;
	}
	else {
		pos += 0.0f;
		satellitePos += 0.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(7, animate, 0);
}

void key(unsigned char key, int x, int y) {
	if (key == 'P' || key == 'p') {
		if (!isMove) {
			isMove = true;
		}
		else {
			isMove = false;
		}
	}

	if (key == '1') {
		if (!showOrbit) {
			showOrbit = true;
		}
		else {
			showOrbit = false;
		}
	}

	if (key == '2') {
		if (!showTrackPlane) {
			showTrackPlane = true;
		}
		else {
			showTrackPlane = false;
		}
	}

	if (key == '3') {
		if (!showSatellite) {
			showSatellite = true;
		}
		else {
			showSatellite = false;
		}
	}

	if (key == '4') {
		if (!showSatelliteOrbit) {
			showSatelliteOrbit = true;
		}
		else {
			showSatelliteOrbit = false;
		}
	}

	if (key == '5') {
		if (!showTrackSatellite) {
			showTrackSatellite = true;
		}
		else {
			showTrackSatellite = false;
		}
	}

	if (key == '+') {
		speed += 0.00025;
	}

	if (key == '_') {
		speed -= 0.00025;
	}
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
	
	std::cout << "--- How To Play --" << std::endl << std::endl;
	std::cout << "- Press P to start/pause" << std::endl;
	std::cout << "- Press 1 to show/hide orbit" << std::endl;
	std::cout << "- Press 2 to enable/disable tracking the plane" << std::endl;
	std::cout << "- Press 3 to show/hide satellite" << std::endl;
	std::cout << "- Press 4 to show/hide satellite orbit" << std::endl;
	std::cout << "- Press 5 to enable/disable tracking the satellite" << std::endl;
	std::cout << "- Press +/- to increase/decrease speed" << std::endl;

	glutMainLoop();

	return 0;
}