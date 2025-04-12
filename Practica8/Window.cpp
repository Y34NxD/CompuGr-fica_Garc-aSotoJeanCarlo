#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	muevex = 0.0f;
	rotaLlantas = 0.0f;
	rotaCofre = 0.0f;
	TransladaCarro = 0.0f;
	EstadoLampara = 1.0f;		//Variable para prender y apagar la luz (Estado inicial prendido)
	EstadoFantasma = 1.0f;		//Variable para prender y apagar la luz (Estado inicial prendido)
	BanderaLuzFaro = 1.0f;		//La luz delantera estará prendida por defecto y la trasera apagada

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica08:Iluminación 2", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow-> muevex -= 1.0;
	}

	//Rotación del dado
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}

	//Rotación para las llantas
	if (key == GLFW_KEY_Z)
	{
		theWindow->rotaLlantas += 10.0; //rotar sobre el eje z 10 grados

	}
	if (key == GLFW_KEY_X)
	{
		theWindow->rotaLlantas -= 10.0; //rotar sobre el eje z 10 grados

	}
	//Rotación para el cofre
	if (key == GLFW_KEY_V)
	{
		if (theWindow->rotaCofre < -90)
		{
		}
		else
		{
			theWindow->rotaCofre -= 10.0; //rotar sobre el eje z 10 grados
		}

	}
	if (key == GLFW_KEY_B)
	{
		if (theWindow->rotaCofre == 0.0)
		{
		}
		else
		{
			theWindow->rotaCofre += 10.0; //rotar sobre el eje z 10 grados
		}

	}

	//Transladar el carro
	if (key == GLFW_KEY_1)
	{
		theWindow->TransladaCarro -= 0.5; //traslada sobre el eje x 
		theWindow->rotaLlantas += 10.0; //Rota las llantas de acuerdo al sentido al que avanza el carro

		theWindow->BanderaLuzFaro = 1.0f;		//Si avanza se prende la bandera del frente
				
	}
	if (key == GLFW_KEY_2)
	{
		theWindow->TransladaCarro += 0.5; //traslada sobre el eje x 
		theWindow->rotaLlantas -= 10.0; //Rota las llantas de acuerdo al sentido al que avanza el carro

		theWindow->BanderaLuzFaro = 0.0f;		//Si retrocede apaga la bandera del frente

	}

	//Apagar y prender la luz de la lampara
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (theWindow->EstadoLampara == 0.0)	//Prende si el estado anterior estaba apagado
		{
			theWindow->EstadoLampara = 1.0;
		}
		else if (theWindow->EstadoLampara == 1.0)//Apaga si el estado anterior estaba prendido
		{
			theWindow->EstadoLampara = 0.0;
		}
		
	}
	//Apagar y prender la luz del fantasma
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		if (theWindow->EstadoFantasma == 0.0)		//Prende si el estado anterior estaba apagado
		{
			theWindow->EstadoFantasma = 1.0;
		}
		else if (theWindow->EstadoFantasma == 1.0)	//Apaga si el estado anterior estaba prendido
		{
			theWindow->EstadoFantasma = 0.0;
		}

	}


	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
