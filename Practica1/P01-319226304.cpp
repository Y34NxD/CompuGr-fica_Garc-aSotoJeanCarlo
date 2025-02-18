//ARCHIVO SEMESTRE 2024-1
#include <stdio.h>
#include <stdlib.h>		//Libreria para usar rand
#include <time.h>		//Libreria para usar time
#include <string.h>
#include <glew.h>
#include <glfw3.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO, shader;
float rojo = 0.0f, verde = 0.0f, azul = 0.0f;
double lastTime = 0.0;		//Inicializar en 0.0
int colorIndice = 3;		// Inicia en 3 u cualquier otro que no sea 0, 1 o 2

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,1.0f,1.0f,1.0f);	 			\n\
}";

void cambiarColor() {		//Función para el cambio de color del fondo
	int nuevoColor;
	do {
		nuevoColor = rand() % 3;			//Genera un número entre 0 y 2
	} while (nuevoColor == colorIndice);	//Asegurando que no sea el mismo color

	colorIndice = nuevoColor;				//Asigna el nuevo indice de color

	//Comparar que indice es, para modifcar las variables de rojo, verde y azul
	if (colorIndice == 0) {
		rojo = 1.0f; verde = 0.0f; azul = 0.0f;		// Rojo
	}
	else if (colorIndice == 1) {
		rojo = 0.0f; verde = 1.0f; azul = 0.0f;		// Verde
	}
	else if (colorIndice == 2) {
		rojo = 0.0f; verde = 0.0f; azul = 1.0f;		// Azul
	}

}

void CrearTriangulo()
{
	GLfloat vertices[] = {
		//Primeras 3 iniciales de mi nombre JCG
		// Letra J
		-0.8f, 0.5f, 0.0f,		//triangulo 1
		-0.8f, 0.37f, 0.0f,
		-0.4f, 0.5f, 0.0f/**/,
		
		-0.8f, 0.37f, 0.0f,		//triangulo 2
		-0.4f, 0.5f, 0.0f,
		-0.4f, 0.37f, 0.0f,

		-0.67f, 0.37f, 0.0f,	//triangulo 3
		-0.53f, 0.37f, 0.0f,
		-0.67f, 0.0f, 0.0f,

		-0.53f, 0.37f, 0.0f,	//triangulo 4
		-0.53f, 0.0f, 0.0f,
		-0.67f, -0.0f, 0.0f,
		
		- 0.67f, 0.1f, 0.0f,	//triangulo 5
		-0.67f, 0.0f, 0.0f,
		-0.85f, 0.0f, 0.0f,

		-0.67f, 0.1f, 0.0f,		//triangulo 6
		-0.85f, 0.1f, 0.0f,
		-0.85f, 0.0f, 0.0f,

		-0.75f, 0.1f, 0.0f,		//triangulo 7
		-0.85f, 0.1f, 0.0f,
		-0.85f, 0.15f, 0.0f,

		-0.75f, 0.1f, 0.0f,		//triangulo 8
		-0.85f, 0.15f, 0.0f,
		-0.75f, 0.15f, 0.0f,

		//letra C
		0.1f, 0.33f, 0.0f,		//triangulo 9
		0.0f, 0.33f, 0.0f,		
		0.1f, 0.5f, 0.0f,

		0.0f, 0.33f, 0.0f,		//triangulo 10
		0.1f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,

		0.0f, 0.5f, 0.0f,		//triangulo 11
		0.0f, 0.4f, 0.0f,
		-0.2f, 0.4f, 0.0f,

		0.0f, 0.5f, 0.0f,		//triangulo 12
		-0.2f, 0.4f, 0.0f,
		-0.2f, 0.5f, 0.0f,

		-0.2f, 0.4f, 0.0f,		//triangulo 13
		-0.09f, 0.4f, 0.0f,
		-0.2f, 0.0f, 0.0f,

		-0.09f, 0.4f, 0.0f,		//triangulo 14
		-0.2f, 0.0f, 0.0f,
		-0.09f, 0.0f, 0.0f,

		-0.09f, 0.0f, 0.0f,		//triangulo 15
		-0.09f, 0.1f, 0.0f,
		0.1f, 0.1f, 0.0f,

		-0.09f, 0.0f, 0.0f,		//triangulo 16
		0.1f, 0.1f, 0.0f,
		0.1f, 0.0f, 0.0f,
		
		0.1f, 0.1f, 0.0f,		//triangulo 17
		0.0f, 0.1f, 0.0f,
		0.1f, 0.17f, 0.0f,

		0.0f, 0.1f, 0.0f,		//triangulo 18
		0.1f, 0.17f, 0.0f,
		0.0f, 0.17f, 0.0f,

		//letra G
		0.3f, 0.5f, 0.0f,		//triangulo 19
		0.7f, 0.5f, 0.0f,
		0.7f, 0.4f, 0.0f,

		0.7f, 0.4f, 0.0f,		//triangulo 20
		0.3f, 0.5f, 0.0f,
		0.3f, 0.4f, 0.0f,

		0.3f, 0.4f, 0.0f,		//triangulo 21
		0.4f, 0.4f, 0.0f,
		0.3f, 0.0f, 0.0f,

		0.4f, 0.4f, 0.0f,		//triangulo 22
		0.3f, 0.0f, 0.0f,
		0.4f, 0.0f, 0.0f,

		0.4f, 0.0f, 0.0f,		//triangulo 23
		0.4f, 0.1f, 0.0f,
		0.7f, 0.1f, 0.0f,

		0.4f, 0.0f, 0.0f,		//triangulo 24
		0.7f, 0.0f, 0.0f,
		0.7f, 0.1f, 0.0f,

		0.7f, 0.1f, 0.0f,		//triangulo 25
		0.6f, 0.1f, 0.0f,
		0.7f, 0.25f, 0.0f,

		0.6f, 0.1f, 0.0f,		//triangulo 26
		0.6f, 0.25f, 0.0f,
		0.7f, 0.25f, 0.0f,

		0.6f, 0.25f, 0.0f,		//triangulo 27
		0.6f, 0.19f, 0.0f,
		0.5f, 0.19f, 0.0f,

		0.6f, 0.25f, 0.0f,		//triangulo 28
		0.5f, 0.25f, 0.0f,
		0.5f, 0.19f, 0.0f


	};
			
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
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
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

	//Crear tríangulo
	CrearTriangulo();
	CompileShaders();
	
	
	srand(time(NULL));			//Inicializar semilla aleatoria
	lastTime = glfwGetTime();	//Obtener el tiempo inicial
	cambiarColor();

	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		//Obtener el tiempo actual
		double tiempoActual = glfwGetTime();

		if (tiempoActual - lastTime >= 2.0) {
			lastTime = tiempoActual;		//Reiniciar el tiempo
			cambiarColor();					//Llama a la funcion para cambiar el color

		}

		//Limpiar la ventana
		glClearColor(rojo,verde,azul,1.0f);	//Asignamos las variables de rojo, verde y azul ya modificadas
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,84); // Cambiar de acuerdo a la cantida de vertices
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);


	}


	return 0;
}