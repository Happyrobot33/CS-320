#include <GL/glut.h>

float x = 0;
float y = 0;
const float stepSize = 0.01f;

// Display callback function
void display()
{
    // set the clear color to blue
    glClearColor(0, 0, 1, 0);
    // clear the screen itself
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Translate based on the position
    glTranslatef(x, y, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); // red
    glVertex3f(0, 0.5, 0);
    glVertex3f(-0.5, -0.5, 0);
    glVertex3f(0.5, -0.5, 0);
    glEnd();

    glutSwapBuffers();
}

// keyboard callback function
void handleInput(int key, int xin, int yin)
{
    //switch on the key
    switch (key)
    {
        case GLUT_KEY_UP:
            if (y < 0.5f)
                y = y + stepSize;
            break;
        case GLUT_KEY_DOWN:
            if (y > -0.5f)
                y = y - stepSize;
            break;
        case GLUT_KEY_RIGHT:
            if (x < 0.5f)
                x = x + stepSize;
            break;
        case GLUT_KEY_LEFT:
            if (x > -0.5f)
                x = x - stepSize;
            break;
        default:
            break;
    }

    //redisplay
    glutPostRedisplay();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Assignment 1");

    glutSpecialFunc(handleInput);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
