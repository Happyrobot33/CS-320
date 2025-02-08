#include <GL/glut.h>

// Rotation angles for the cube man
float angleX = 0.0f;
float angleY = 0.0f;

// Function to draw a cube
void drawCube(float x, float y, float z, float width, float height, float depth) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(width, height, depth);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Function to draw the cube man
void drawCubeMan() {
    // Body
    drawCube(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f);

    // Head
    drawCube(0.0f, 1.2f, 0.0f, 0.6f, 0.6f, 0.5f);

    // Arms
    drawCube(-0.8f, 0.3f, 0.0f, 1.2f, 0.3f, 0.3f);
    drawCube(0.8f, 0.3f, 0.0f, 1.2f, 0.3f, 0.3f);

    // Legs
    drawCube(-0.3f, -1.2f, 0.0f, 0.3f, 1.2f, 0.3f);
    drawCube(0.3f, -1.2f, 0.0f, 0.3f, 1.2f, 0.3f);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Move back to view the object
    glTranslatef(0.0f, 0.0f, -6.0f);

    // Apply rotation
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Draw the cube man
    drawCubeMan();

    glutSwapBuffers();
}

// Timer callback for animation
void timer(int value) {
    angleX += 1.0f;
    angleY += 1.0f;

    if (angleX > 360.0f) angleX -= 360.0f;
    if (angleY > 360.0f) angleY -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// Reshape callback
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Cube Man");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}
