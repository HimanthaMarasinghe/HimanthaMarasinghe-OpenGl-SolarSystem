#include <GL/glut.h>
#include <math.h>

float angle = 32.0;
float angle1 = 171.0;
float angle2 = 93.0;
float angle3 = 0.0;
float angle4 = 0.0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void drawSphere(float angle, float red, float green, float blue, float size, float x) {
    glPushMatrix();
    glColor3f(red, green, blue);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(x, 0, 0);
    glutSolidSphere(size, 30, 30);
    glPopMatrix();
}

void drawCircle(float radius) {
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);

    // Draw circle
    glBegin(GL_LINE_LOOP);
    int num_segments = 100;  // Number of sides (segments) of the polygon
    for(int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments; // Angle in radians
        float x = radius * cosf(theta); // Calculate x coordinate
        float y = radius * sinf(theta); // Calculate y coordinate
        glVertex2f(x, y); // Specify the vertex
    }
    glEnd();

    glPopMatrix();
}

void drawRing(float angle, float x, float outerRadius, float innerRadius) {
    glPushMatrix();

    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(x, 0, 0);

    int num_segments = 100;  // Number of segments to approximate the circle
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments; // Angle in radians

        float xOuter = outerRadius * cosf(theta); // Calculate x coordinate for outer circle
        float yOuter = outerRadius * sinf(theta); // Calculate y coordinate for outer circle

        float xInner = innerRadius * cosf(theta); // Calculate x coordinate for inner circle
        float yInner = innerRadius * sinf(theta); // Calculate y coordinate for inner circle

        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(xOuter, yOuter);  // Outer vertex

        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(xInner, yInner);  // Inner vertex
    }
    glEnd();

    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();
    gluLookAt(0.0, 10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    drawSphere(0.0, 1.0, 1.0, 0.0, 2.0, 0.0); // Yellow sphere

    drawSphere(angle, 0.0, 1.0, 0.0, 0.25, 3.0);  // Green sphere
    drawCircle(3.0);

    drawSphere(angle1, 1.0, 0.0, 0.0, 0.32, 4.5); // Red sphere
    drawCircle(4.5);

    drawSphere(angle2, 1.0, 0.5, 0.0, 0.45, 6.0); // Orange sphere
    drawRing(angle2, 6.0, 0.6, 0.9);
    drawCircle(6.0);

    drawSphere(angle3, 0.0, 0.0, 1.0, 0.3, 7.5); // Blue sphere
    drawCircle(7.5);

    glPushMatrix();
    glRotatef(angle3, 0, 0, 1);
    glTranslatef(7.5, 0, 0);
    drawSphere(angle4, 1, 1, 1, 0.1, 0.6); //moon
    drawCircle(0.6);
    glPopMatrix();

    glFlush();
}

void animate() {
    angle += 0.023;
    angle1 += 0.013;
    angle2 += 0.011;
    angle3 += 0.007;
    angle4 += 0.08;

    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2.0, 2.0, -1.5, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 625);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}
