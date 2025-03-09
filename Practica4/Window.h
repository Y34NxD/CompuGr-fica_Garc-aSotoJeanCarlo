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
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	
	//-----------------------Pata Izquierda trasera
	//Articulaci�n superior
	GLfloat getarticulacion1() { return articulacion1; }
	//Articulaci�n inferior
	GLfloat getarticulacion2() { return articulacion2; }

	//--------------------Pata derecha trasera
	//Articulaci�n superior
	GLfloat getarticulacion3() { return articulacion3; }
	//Articulaci�n inferior
	GLfloat getarticulacion4() { return articulacion4; }

	//-----------------------Pata derecha frontal
	//Articulaci�n superior
	GLfloat getarticulacion5() { return articulacion5; }
	//Articulaci�n inferior
	GLfloat getarticulacion6() { return articulacion6; }

	//-----------------------Pata izquierda frontal
	//Articulaci�n superior
	GLfloat getarticulacion7() { return articulacion7; }
	//Articulaci�n inferior
	GLfloat getarticulacion8() { return articulacion8; }
	
	//Primera articulaci�n de la cola
	GLfloat getarticulacion9() { return articulacion9; }	//Lanta izquierda delantera
	//Segunda articulaci�n de la cola
	GLfloat getarticulacion10() { return articulacion10; }	//Lanta derecha delantera
	//Tercera articulaci�n de la cola
	GLfloat getarticulacion11() { return articulacion11; }	//Lanta derecha trasera
	//Cuarta articulaci�n de la cola
	GLfloat getarticulacion12() { return articulacion12; }	//Lanta izquierda trasera

	//Oreja izquierda
	GLfloat getarticulacion13() { return articulacion13; }
	//Oreja derecha
	GLfloat getarticulacion14() { return articulacion14; }



	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax,rotay,rotaz, articulacion1, articulacion2, articulacion3, articulacion4, articulacion5, articulacion6, articulacion7, articulacion8, articulacion9, articulacion10,
		articulacion11, articulacion12, articulacion13, articulacion14;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

