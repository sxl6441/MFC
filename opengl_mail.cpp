#include <GL\freeglut.h>
#include "camera.h"
#include "projection.h"
#include <iostream>
#include <vector>
using namespace std;


#define MAX_CHAR 128
Camera camera;
Projection mProjection;
int lastPos_x = 0;
int lastPos_y = 0;
float outline_[6] = { 0 };//物体包围盒
bool mouseLeftDown = false;
bool mouseRightDown = false;
bool mouseMiddleDown = false;
bool shiftIsDown = false;
bool isPressdown = true;
void paintGL();
void resizeGL(int, int);
void drawStr(void* fontStyle, const char* str);
void drawString(const char* str);
void selectFont(int size, int charset, const char* face);

//glm;;mat4转float数组
const float *mat4ToArray(const glm::mat4 matrix)
{
	float array[16] =
	{
		matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
		matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
		matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
		matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3],
	};
	return &array[0];
}

//键盘事件
void keyBoardEvent(unsigned char key, int mouse_x, int mouse_y)
{
	if (key == 32)//空格键
	{
		camera.SetDirectionView(DEFAULT);
		mProjection.updateSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glutPostRedisplay();
	}
	if (key == 27)//Esc
	{
		exit(0);
	}
}

//鼠标单击事件
void mousePressEvent(int button, int state, int mouse_x, int mouse_y)
{
	int specialKey = glutGetModifiers();//该函数只能在处理按键消息或鼠标消息的函数中调用，检测Shift,Alt,Ctrl状态
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;

			////glDisable(GL_LIGHTING);
			////isPressdown = false;
			//GLint viewport[4];
			//glGetIntegerv(GL_VIEWPORT, viewport);
			//int xx = mouse_x;
			//int yy = viewport[3] - mouse_y;

			////glutPostRedisplay();
			////resizeGL(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			//GLfloat res1[3] = { 1,0,1 };
			//glReadPixels(300, 300, 1, 1, GL_RGB, GL_FLOAT, &res1);

			//renderSelection(camera.GetViewMatrix(), mProjection.GetProjectionMatrix());
			//unsigned char res[3];
			//glReadPixels(xx, yy, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &res);//OpenGL1.1 from microsoft don't support alpha value
			//selectedId = res[0] + res[1] * 255 + res[2] * 255 * 255;
		}
		else if (state == GLUT_UP)
		{
			mouseLeftDown = false;
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseMiddleDown = true;
			if (specialKey == GLUT_ACTIVE_SHIFT)
			{
				shiftIsDown = true;
			}
			else
			{
				shiftIsDown = false;
			}
		}
		else if (state == GLUT_UP)
		{
			mouseMiddleDown = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			std::cout << "右键按下" << std::endl;
		}
		else if (state == GLUT_UP)
		{
			std::cout << "右键释放" << std::endl;
		}
	}
	lastPos_x = mouse_x;
	lastPos_y = mouse_y;
}

//鼠标进入窗口事件
void mouseEntryWindow(int state)
{
	std::cout << state << std::endl;
}

//鼠标单击并移动事件
void mouseMoveEvent(int mouse_x, int mouse_y)
{
	int dx = mouse_x - lastPos_x;
	int dy = mouse_y - lastPos_y;
	if (mouseMiddleDown == true)
	{
		if (shiftIsDown == true)
		{
			mProjection.ProcessMouseMove(dx, dy, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
		else
		{
			camera.ProcessMouseRotate(4 * dx, 4 * dy);
		}
		glutPostRedisplay();//放在里面确保模型有时不会消失不见
	}
	lastPos_x = mouse_x;
	lastPos_y = mouse_y;
}

//鼠标滚轮事件
void mouseWheelEvent(int button, int delta, int mouse_x, int mouse_y)
{
	glm::mat4 proj = mProjection.GetProjectionMatrix();
	GLint viewport_[4];
	glGetIntegerv(GL_VIEWPORT, viewport_);
	int xx = mouse_x;
	int yy = viewport_[3] - mouse_y;
	float zz;
	glReadPixels(xx, yy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zz);
	glm::vec3 pivot = glm::unProject(glm::vec3(xx, yy, zz), glm::mat4(1.0f), proj, glm::vec4(viewport_[0], viewport_[1], viewport_[2], viewport_[3]));

	//camera.ProcessMouseScroll(delta);//以模型中心点进行缩放
	mProjection.SetProjection(delta, pivot);//以鼠标位置为焦点进行缩放

	glutPostRedisplay();
}

void initialGL()
{
	outline_[0] = -1;
	outline_[1] = -1;
	outline_[2] = -1;
	outline_[3] = 1;
	outline_[4] = 1;
	outline_[5] = 1;
	float targetX = (outline_[0] + outline_[3]) / 2.0f;
	float targetY = (outline_[1] + outline_[4]) / 2.0f;
	float targetZ = (outline_[2] + outline_[5]) / 2.0f;
	camera = Camera(targetX, targetY, targetZ);
	mProjection = Projection(outline_, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	GLfloat light_ambient[] = { 0.3,0.3,0.3,1.0 };
	GLfloat light_diffuse[] = { 0.4,0.4,0.4,1.0 };
	GLfloat light_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat light_position[] = { 0.0,0.0,1000.0,0.0 };//第4位为0表示方向光，为1表示点光源
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);//启用光源0
	glEnable(GL_LIGHTING);//启用光照
	glEnable(GL_COLOR_MATERIAL);//启用颜色跟踪，所设置的颜色才不会因为光照而失效
	glEnable(GL_DEPTH_TEST);//启用深度测试
}

void resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	mProjection.updateSize(w, h);
}

void paintGL(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	//设置投影矩阵
	glm::mat4 projection_t = mProjection.GetProjectionMatrix();
	const float *projArray = mat4ToArray(projection_t);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(projArray);

	//设置视图矩阵
	glm::mat4 view = camera.GetViewMatrix();
	const float *viewArray = mat4ToArray(view);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(viewArray);

	//绘图
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, 0.0);
	glEnd();

	//绘制文字1
	//glColor3f(1.0f, 1.0f, 0.0f);//设置字体颜色
	//glLineWidth(2.0);//设置笔画粗细
	//glTranslatef(-0.5, -0.3, 0.003);  //设置字符显示的位置
	//glScalef(0.005f, 0.005f, 0.005f);//缩放字体
	//drawStr(GLUT_STROKE_ROMAN, "Hello.123");

	//绘制文字2
	//glRasterPos3f(0, 0, 0);
	//drawString("Hello.123");

	//绘制文字3
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, 1000);
	glListBase(1000);
	glRasterPos3f(-5.0f, 0.0f, 0.0f);
	glCallLists(20, GL_UNSIGNED_BYTE, "Draw with List Text.");

	//绘制文字4
	//GLYPHMETRICSFLOAT agmf[256]; 	// create display lists for glyphs 0 through 255
	//								// with 0.1 extrusion and default deviation. 
	//								//The display list numbering starts at 1000   (it could be any number) 
	//wglUseFontOutlines(wglGetCurrentDC(), 0, 255, 1000, 0.3f, 0.8f, WGL_FONT_LINES, agmf);
	//// Set up transformation to draw the string  
	//glTranslatef(-0.5, -0.3, 0.003);  //设置字符显示的位置
	//glScalef(0.005f, 0.005f, 0.005f);//缩放字体
	//glListBase(1000);		// Indicates the start of display lists for the glyphs// Draw the characters in a string  
	//glCallLists(26, GL_UNSIGNED_BYTE, "Draw outline list 3D text.");

	glutSwapBuffers();//交换缓冲区
}

//显示三维矢量字体
void drawStr(void* fontStyle, const char* str)
{
	// 调用每个字符对应的显示列表，绘制每个字符
	if (fontStyle == GLUT_STROKE_ROMAN || fontStyle == GLUT_STROKE_MONO_ROMAN)
	{
		for (; *str != '\0'; ++str)
		{
			glutStrokeCharacter(fontStyle, *str);//fontStyle可以选GLUT_STROKE_ROMAN和GLUT_STROKE_MONO_ROMAN两种类型，*str为该字符的ASCII码
		}
	}
}

//显示的字体在屏幕上始终是二维的，未采用
void drawString(const char* str)
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) {
		isFirstCall = 0;
		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);
		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
	
}

//设置字体大小，未采用
void selectFont(int size, int charset, const char* face) 
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL工程");
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);
	std::cout << "OpenGL实现的版本号：" << OpenGLVersion << std::endl;
	initialGL();
	glutDisplayFunc(paintGL);
	glutReshapeFunc(resizeGL);
	glutMouseFunc(mousePressEvent);
	glutMotionFunc(mouseMoveEvent);
	//glutPassiveMotionFunc();
	glutKeyboardFunc(keyBoardEvent);
	glutMouseWheelFunc(mouseWheelEvent);
	glutEntryFunc(mouseEntryWindow);
	glutMainLoop();
	return 0;
}
