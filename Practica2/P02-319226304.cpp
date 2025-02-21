//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderRojo = "shaders/shader_rojo.vert";
static const char* fShaderRojo = "shaders/shader_rojo.frag";
static const char* vShaderVerde = "shaders/shader_verde.vert";
static const char* fShaderVerde = "shaders/shader_verde.frag";
static const char* vShaderAzul = "shaders/shader_azul.vert";
static const char* fShaderAzul = "shaders/shader_azul.frag";
static const char* vShaderCafe = "shaders/shader_cafe.vert";
static const char* fShaderCafe = "shaders/shader_cafe.frag";
static const char* vShaderVerdeOscuro = "shaders/shader_verdeOscuro.vert";
static const char* fShaderVerdeOscuro= "shaders/shader_verdeOscuro.frag";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	//Letra J
	GLfloat vertices_letra_J[] = {
		//triangulo 1
		//X			Y			Z			R		G		B
		-0.8f,	 0.5f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.8f,	 0.37f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.4f,	 0.5f,		0.5f,			0.0f,	0.3f,	0.0f,

		//triangulo 2
		//X			Y			Z			R		G		B
		-0.8f,	 0.37f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.4f,	 0.5f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.4f,	 0.37f,		0.5f,			0.0f,	0.3f,	0.0f,
		
		//triangulo 3
		//X			Y			Z			R		G		B
		-0.67f,	 0.37f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.53f,  0.37f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.67f,  0.0f,		0.5f,			0.0f,	0.3f,	0.0f,
		
		//triangulo 4
		//X			Y			Z			R		G		B
		-0.53f,  0.37f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.53f,  0.0f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.67f,  -0.0f,		0.5f,			0.0f,	0.3f,	0.0f,

		//triangulo 5
		//X			Y			Z			R		G		B
		-0.67f,  0.1f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.67f,  0.0f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.85f,  0.0f,		0.5f,			0.0f,	0.3f,	0.0f,

		//triangulo 6
		//X			Y			Z			R		G		B
		-0.67f,  0.1f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.85f,  0.1f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.85f,  0.0f,		0.5f,			0.0f,	0.3f,	0.0f,

		//triangulo 7
		//X			Y			Z			R		G		B
		-0.75f,  0.1f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.85f,  0.1f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.85f,  0.15f,		0.5f,			0.0f,	0.3f,	0.0f,

		//triangulo 8
		//X			Y			Z			R		G		B
		-0.75f,  0.1f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.85f,  0.15f,		0.5f,			0.0f,	0.3f,	0.0f,
		-0.75f,  0.15f,		0.5f,			0.0f,	0.3f,	0.0f,

	};
	MeshColor* letra_J = new MeshColor();
	letra_J->CreateMeshColor(vertices_letra_J, 144);	// 8*3*6=144
	meshColorList.push_back(letra_J);
	
	//Letra C
	GLfloat vertices_letra_C[] = {
		//triangulo 1
		//X			Y			Z			R		G		B
		0.1f,	 0.33f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.0f,	 0.33f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.1f,	 0.5f,		0.5f,			0.502f, 0.0f, 0.502f,
		
		//triangulo 2
		//X			Y			Z			R		G		B
		0.0f,	 0.33f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.1f,	 0.5f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.0f,	 0.5f,		0.5f,			0.502f, 0.0f, 0.502f,

		//triangulo 3
		//X			Y			Z			R		G		B
		0.0f,	 0.5f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.0f,	 0.4f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.2f,	 0.4f,		0.5f,			0.502f, 0.0f, 0.502f,

		//triangulo 4
		//X			Y			Z			R		G		B
		0.0f,	 0.5f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.2f,	 0.4f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.2f,	 0.5f,		0.5f,			0.502f, 0.0f, 0.502f,
		
		//triangulo 5
		//X			Y			Z			R		G		B
		-0.2f,	 0.4f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.09f,	 0.4f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.2f,	 0.0f,		0.5f,			0.502f, 0.0f, 0.502f,

		//triangulo 6
		//X			Y			Z			R		G		B
		-0.09f,  0.4f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.2f,	 0.0f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.09f,  0.0f,		0.5f,			0.502f, 0.0f, 0.502f,

		//triangulo 7
		//X			Y			Z			R		G		B
		-0.09f,  0.0f,		0.5f,			0.502f, 0.0f, 0.502f,
		-0.09f,  0.1f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.1f,	 0.1f,		0.5f,			0.502f, 0.0f, 0.502f,

		//triangulo 8
		//X			Y			Z			R		G		B
		-0.09f,  0.0f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.1f,	 0.1f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.1f,	 0.0f,		0.5f,			0.502f, 0.0f, 0.502f,
		
		//triangulo 9
		//X			Y			Z			R		G		B
		0.1f,	 0.1f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.0f,	 0.1f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.1f,	 0.17f,		0.5f,			0.502f, 0.0f, 0.502f,

		//triangulo 10
		//X			Y			Z			R		G		B
		0.0f,	 0.1f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.1f,	 0.17f,		0.5f,			0.502f, 0.0f, 0.502f,
		0.0f,	 0.17f,		0.5f,			0.502f, 0.0f, 0.502f
		

	};
	MeshColor* letra_C = new MeshColor();
	letra_C->CreateMeshColor(vertices_letra_C, 180);	// 10*3*6=180 
	meshColorList.push_back(letra_C);

	//Letra G
	GLfloat vertices_letra_G[] = {
		
		//triangulo 1
		//X			Y			Z			R		G		B
		0.3f,	 0.5f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.7f,	 0.5f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.7f,	 0.4f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 2
		//X			Y			Z			R		G		B
		0.7f,	 0.4f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.3f,	 0.5f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.3f,	 0.4f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 3
		//X			Y			Z			R		G		B
		0.3f,	 0.4f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.4f,	 0.4f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.3f,	 0.0f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 4
		//X			Y			Z			R		G		B
		0.4f,	 0.4f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.3f,	 0.0f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.4f,	 0.0f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 5
		//X			Y			Z			R		G		B
		0.4f,	 0.0f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.4f,	 0.1f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.7f,	 0.1f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 6
		//X			Y			Z			R		G		B
		0.4f,	 0.0f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.7f,	 0.0f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.7f,	 0.1f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 7
		//X			Y			Z			R		G		B
		0.7f,	 0.1f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.6f,	 0.1f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.7f,	 0.25f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 8
		//X			Y			Z			R		G		B
		0.6f,	 0.1f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.6f,	 0.25f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.7f,	 0.25f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 9
		//X			Y			Z			R		G		B
		0.6f,	 0.25f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.6f,	 0.19f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.5f,	 0.19f,		0.5f,			0.2f,	0.2f,	0.2f,

		//triangulo 10
		//X			Y			Z			R		G		B
		0.6f,	 0.25f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.5f,	 0.25f,		0.5f,			0.2f,	0.2f,	0.2f,
		0.5f,	 0.19f,		0.5f,			0.2f,	0.2f,	0.2f

	};
	MeshColor* letra_G = new MeshColor();
	letra_G->CreateMeshColor(vertices_letra_G, 180);	// 10*3*6=180 
	meshColorList.push_back(letra_G);



	/*GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
			-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,18);
	meshColorList.push_back(letras);

	//Triangulo azul
	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};
	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);//0
 
	//Triangulo verde
	GLfloat vertices_trianguloverde[] = {
		//X            Y            Z            R        G        B
		-1.0f,      -0.5f,      0.5f,         0.0f,    0.5f,    0.0f,
		1.0f,       -0.5f,      0.5f,         0.0f,    0.5f,    0.0f,
		0.0f,       1.5f,       0.5f,         0.0f,    0.5f,    0.0f,
	};
	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);//1
	
	//Cuadrado rojo
	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);//2

	//Cuadrado verde
	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};
	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);//3

	//Cuadrado café
	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,

	};
	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);//4
	*/
}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	// Shader Cubo Rojo (2)
	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vShaderRojo, fShaderRojo);
	shaderList.push_back(*shaderRojo);

	// Shader Cubo Verde (3)
	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vShaderVerde, fShaderVerde);
	shaderList.push_back(*shaderVerde);

	// Shader Piramide Azul (4)
	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vShaderAzul, fShaderAzul);
	shaderList.push_back(*shaderAzul);

	// Shader Cubo Cafe (5)
	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vShaderCafe, fShaderCafe);
	shaderList.push_back(*shaderCafe);

	// Shader Piramide Verde Oscuro (6)
	Shader* shaderVerdeOscuro = new Shader();
	shaderVerdeOscuro->CreateFromFiles(vShaderVerdeOscuro, fShaderVerdeOscuro);
	shaderList.push_back(*shaderVerdeOscuro);

}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		//Renderización de la casa (Cubo Rojo)
		shaderList[2].useShader(); // shader_rojo
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -15.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Usar cubo para la casa

		// Renderización del Techo (Piramide Azul)
		shaderList[4].useShader(); // shader_azul
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.8f, -15.0f));
		model = glm::scale(model, glm::vec3(6.0f, 3.0f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // Usar pirámide para el techo
		
		// Renderización de la Ventana Izquierda (Cubo Verde)
		shaderList[3].useShader(); // shader_verde
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, 0.7f, -10.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Usar cubo para ventanas

		// Renderización de la Ventana Derecha (Cubo Verde)
		shaderList[3].useShader(); // shader_verde
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, 0.7f, -10.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Usar cubo para ventanas

		// Renderización de la Puerta (Cubo Verde)
		shaderList[3].useShader(); // shader_verde
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.03f, -10.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Usar cubo para puerta

		// Renderización del tronco Izquierdo (Cubo Café)
		shaderList[5].useShader(); // shader_cafe
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -1.7f, -15.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Usar cubo para el tronco izquierdo

		// Renderización del tronco Derecho (Cubo Café)
		shaderList[5].useShader(); // shader_cafe
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, -1.7f, -15.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Usar cubo para el tronco derecho

		// Renderización de la Copa de árbol Izquierdo (Pirámide Verde Oscuro)
		shaderList[6].useShader();	// shader_verdeOscuro
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, -0.1f, -15.0f));
		model = glm::scale(model, glm::vec3(2.3f, 2.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // Usar pirámide para la copa del árbol

		// Renderización de la Copa de árbol Derecho (Pirámide Verde Oscuro)
		shaderList[6].useShader();	// shader_verdeOscuro
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, -0.1f, -15.0f));
		model = glm::scale(model, glm::vec3(2.3f, 2.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // Usar pirámide para la copa del árbol



		
/**/
		/*
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		

		//Renderizar letra J
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -4.0f));   
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 1.0f));  
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//Renderizar letra C
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();

		//Renderizar letra G
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -4.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();
		*/ 
		/*
		// Renderizar triángulo azul
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, 0.0f, -4.0f));  // Más separado en X
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		
		// Renderizar triángulo verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -4.0f));  // Nueva posición
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[1]->RenderMeshColor();

		// Renderizar cuadrado verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[2]->RenderMeshColor();

		// Renderizar cuadrado rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, -4.0f));   // Centro
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[3]->RenderMeshColor();

		// Renderizar cuadrado café
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, 0.0f, -4.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[4]->RenderMeshColor();
			
		

		//Renderizado Estructura Casa -> Cuadro Rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));   // Centro
		model = glm::scale(model, glm::vec3(6.0f, 7.5f, 1.5f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		//Renderizado Techo -> Triangulo azul
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 6.0f, -3.0f));   // Centro
		model = glm::scale(model, glm::vec3(4.0f, 2.5f, 1.5f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//Renderizado Puerta -> Cuadro verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, -3.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(2.0f, 2.5f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor();

		//Renderizado Ventana Izquierda -> Cuadro verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.35f, 1.8f, -3.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(2.0f, 2.5f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor();

		//Renderizado Ventana Derecha -> Cuadro verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.35f, 1.8f, -3.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(2.0f, 2.5f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor();

		//Renderizado Tronco Izquierdo -> Cuadro café
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -3.2f, -2.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(1.0f, 1.4f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();

		//Renderizado Tronco Derecho -> Cuadro café
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -3.2f, -2.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(1.0f, 1.4f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();

		//Renderizado Copa Arbol Izquierdo -> Triangulo verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.5f, -2.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(1.2f, 2.0f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();

		//Renderizado Copa Arbol Derecho -> Triangulo verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.5f, -2.0f));   // Nueva posición
		model = glm::scale(model, glm::vec3(1.2f, 2.0f, 1.0f));  // Hacerlo más grande
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();
		
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[0].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		*/
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/

