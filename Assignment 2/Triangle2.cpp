#include <GL/glut.h>

// Display callback function
void display()
{
    // set the clear color to blue
    glClearColor(0, 0, 1, 0);
    // clear the screen itself
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //scale by 1.5 in both directions
    glScalef(1.5f, 1.5f ,1);

    //rotate by 30 degrees
    glRotatef(30, 0, 0, 1);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); // red
    glVertex3f(0, 0, 0);
    glVertex3f(0.5, 0, 0);
    glVertex3f(0.25, 0.5, 0);
    glEnd();

    glutSwapBuffers();
}

// Main function
int main(int argc, char **argv)
{
    //init glut
    glutInit(&argc, argv);
    //setup display information
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Assignment 2");

    //register our callback for rendering
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
