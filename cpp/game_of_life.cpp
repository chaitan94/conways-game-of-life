#include <GL/glut.h>
#include "Board.cpp"
#define SCREENSIZE 512
#define GRIDSIZE 128.0f
#define CELLSIZE 2/GRIDSIZE
#define FPS 30

int lastUpdate;
Board front((int)GRIDSIZE), back((int)GRIDSIZE);

void drawSquare(float x, float y, int r, int g, int b) {
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(x, y, 0);
    glVertex3f(x+CELLSIZE, y, 0);
    glVertex3f(x+CELLSIZE, y-CELLSIZE, 0);
    glVertex3f(x, y-CELLSIZE, 0);
    glEnd();
}
void drawCell(int c, int x, int y) {
	if (c) drawSquare(x*CELLSIZE-1.0f,-y*CELLSIZE+1.0f,1,1,1);
	else drawSquare(x*CELLSIZE-1.0f,-y*CELLSIZE+1.0f,0,0,0);
}
void render(){
	for (int x = 0; x < GRIDSIZE; x++){
		for (int y = 0; y < GRIDSIZE; y++){
			if(front[x][y] ^ back[x][y]){
				front[x][y] = back[x][y];
				drawCell(int(front[x][y]), x, y);
			}
		}
	}
}
void gl_renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    render();
    glPopMatrix();
    glutSwapBuffers();
}
bool gameOfLife(int x, int y){
	bool cur = front.getCell(x,y);
	int s = 0;
	s += (int)front.getCell(x+(-1),y+(-1));
	s += (int)front.getCell(x+(-1),y+(0));
	s += (int)front.getCell(x+(-1),y+(1));
	s += (int)front.getCell(x+(0),y+(-1));
	s += (int)front.getCell(x+(0),y+(1));
	s += (int)front.getCell(x+(1),y+(-1));
	s += (int)front.getCell(x+(1),y+(0));
	s += (int)front.getCell(x+(1),y+(1));
	if (s > 3) return false;
	if ((s == 3) && !cur) return true;
	if ((s < 2) && cur) return false;
	return front.getCell(x, y);
}
void update(){
    int currentTime = glutGet( GLUT_ELAPSED_TIME );
    if ((currentTime - lastUpdate) >= 1000.0f/FPS) {
		for (int x = 0; x < GRIDSIZE; x++){
			for (int y = 0; y < GRIDSIZE; y++){
				back[x][y] = (gameOfLife(x,y));
			}
		}
    	gl_renderScene();
        lastUpdate = currentTime;
    }
}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(30,30);
    glutInitWindowSize(SCREENSIZE, SCREENSIZE);
    glutCreateWindow("Game Of Life");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(gl_renderScene);
    glutIdleFunc(update);
    lastUpdate = glutGet( GLUT_ELAPSED_TIME );
    glutMainLoop();
	return 0;
}