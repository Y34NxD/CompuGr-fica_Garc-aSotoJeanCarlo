#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	GLfloat getmuevex() { return muevex; }
	GLfloat getrotaLlantas() { return rotaLlantas; }
	GLfloat getrotaCofre() { return rotaCofre; }
	GLfloat getTransladaCarro() { return TransladaCarro; }
	GLfloat getEstadoLampara() { return EstadoLampara;  }
	GLfloat getEstadoFantasma() { return EstadoFantasma; }
	GLfloat getBanderaLuzFaro() { return BanderaLuzFaro; }


	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex, rotax, rotay, rotaz;
	GLfloat rotaLlantas, rotaCofre, TransladaCarro;
	GLfloat EstadoLampara, EstadoFantasma;
	GLfloat BanderaLuzFaro;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

