/*
Práctica 8: Iluminación 2
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture octaedroTexture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;

//Modelos para ejercicio de la practica
Model KitCarro_M;	//ojos y carro
Model LlantaIzqDelantera_M;
Model LlantaDerDelantera_M;
Model LlantaIzqTrasera_M;
Model LlantaDerTrasera_M;
Model Rin_M;
Model Cofre_M;
Model Parrilla_M;

//Modelo de la lámpara
Model Lampara_M;

//Modelo del fantasma
Model Fantasma_M;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];			//3
PointLight pointLights2[MAX_POINT_LIGHTS];			//3
SpotLight spotLights[MAX_SPOT_LIGHTS];				//5
SpotLight spotLights2[MAX_SPOT_LIGHTS];				//5

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CrearOctaedro()
{
	unsigned int octaedro_indices[] = {
		// Parte superior
		0, 1, 2,     // Cara 1
		3, 4, 5,     // Cara 2
		6, 7, 8,     // Cara 3
		9,10,11,     // Cara 4
		// Parte inferior
		12,13,14,    // Cara 5
		15,16,17,    // Cara 6
		18,19,20,    // Cara 7
		21,22,23     // Cara 8

	};

	GLfloat octaedro_vertices[] = {
		// Cara 1: top - left - front   normal: (1, -1, -1)
		//x		y		z		S	 T		NX		NY		NZ
		0.0f,  1.0f,  0.0f,  0.14f,	0.65f,  1.0f,  -1.0f,  -1.0f,	//Punta
		-1.0f, 0.0f,  0.0f,  0.02f,	0.34f,  1.0f,  -1.0f,  -1.0f,	//Izquierda
		0.0f,  0.0f,  1.0f,  0.26f,	0.34f,  1.0f,  -1.0f,  -1.0f,	//Derecha

		// Cara 2: top - front - right   normal: (-1, -1, -1)
		//x		y		z		S	T		NX		NY		NZ
		0.0f,  1.0f,  0.0f,  0.285f,0.35f,   -1.0f,  -1.0f,  -1.0f,
		0.0f,  0.0f,  1.0f,  0.4f,	0.65f,   -1.0f,  -1.0f,  -1.0f,
		1.0f,  0.0f,  0.0f,  0.16f,	0.65f,   -1.0f,  -1.0f,  -1.0f,

		// Cara 3: top - right - back   normal: (-1, -1, 1)
		//x		y		z		S	T		NX		NY		NZ
		0.0f,  1.0f,  0.0f,  0.43f,	0.65f,   -1.0f,  -1.0f, 1.0f,
		1.0f,  0.0f,  0.0f,  0.3f,	0.34f,   -1.0f,  -1.0f, 1.0f,
		0.0f,  0.0f, -1.0f,  0.55f,	0.34f,   -1.0f,  -1.0f, 1.0f,

		// Cara 4: top - back - left   normal: (1, -1, 1)
		//x		y		z		S	T		NX		NY		NZ
		0.0f,  1.0f,  0.0f,  0.573f,0.35f,  1.0f,  -1.0f, 1.0f,
		0.0f,  0.0f, -1.0f,  0.68f,	0.65f,  1.0f,  -1.0f, 1.0f,
		-1.0f, 0.0f,  0.0f,	 0.45f,	0.65f,  1.0f,  -1.0f, 1.0f,

		// Cara 5: bottom - front - left   normal: (1, 1, -1)
		//x		y		z		S	T		NX		NY		NZ
		0.0f, -1.0f,  0.0f,  0.715f,0.64f,  1.0f, 1.0f,  -1.0f,
		0.0f,  0.0f,  1.0f,  0.6f, 0.35f,   1.0f, 1.0f,  -1.0f,
		-1.0f, 0.0f,  0.0f,  0.84f, 0.35f,  1.0f, 1.0f,  -1.0f,

		// Cara 6: bottom - right - front   normal: (-1, 1, -1)
		//x		y		z		S	T		NX		NY		NZ
		0.0f, -1.0f,  0.0f,  0.86f, 0.35f,  -1.0f, 1.0f,  -1.0f,
		1.0f,  0.0f,  0.0f,  0.98f,0.64f,   -1.0f, 1.0f,  -1.0f,
		0.0f,  0.0f,  1.0f,  0.75f,0.64f,   -1.0f, 1.0f,  -1.0f,

		// Cara 7: bottom - back - right   normal: (-1, 1, 1)
		//x		y		z		S	T		NX		NY		NZ
		0.0f, -1.0f,  0.0f,  0.57f, 0.99f,  -1.0f, 1.0f, 1.0f,
		0.0f,  0.0f, -1.0f,  0.45f,	0.68f,  -1.0f, 1.0f, 1.0f,
		1.0f,  0.0f,  0.0f,  0.68f,	0.68f,  -1.0f, 1.0f, 1.0f,

		// Cara 8: bottom - left - back   normal: (1, 1, 1)
		//x		y		z		S	T		NX		NY		NZ
		0.0f, -1.0f,  0.0f,  0.44f, 0.02f,  1.0f, 1.0f, 1.0f,
		-1.0f, 0.0f,  0.0f,  0.55f,	0.3f,   1.0f, 1.0f, 1.0f,
		0.0f,  0.0f, -1.0f,  0.31f,	0.3f,   1.0f, 1.0f, 1.0f

	};
	Mesh* octaedro = new Mesh();
	octaedro->CreateMesh(octaedro_vertices, octaedro_indices, 192, 24);
	meshList.push_back(octaedro);
};


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearOctaedro();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	octaedroTexture = Texture("Textures/octaedro_Mod.png");
	octaedroTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	KitCarro_M = Model();
	KitCarro_M.LoadModel("Models/Carro_Ojos.obj");
	LlantaIzqDelantera_M = Model();
	LlantaIzqDelantera_M.LoadModel("Models/LlantaIzqDelantera.obj");
	LlantaIzqTrasera_M = Model();
	LlantaIzqTrasera_M.LoadModel("Models/LlantaIzqTrasera.obj");
	LlantaDerDelantera_M = Model();
	LlantaDerDelantera_M.LoadModel("Models/LlantaDerDelantera.obj");
	LlantaDerTrasera_M = Model();
	LlantaDerTrasera_M.LoadModel("Models/LlantaDerTrasera.obj");
	Rin_M = Model();
	Rin_M.LoadModel("Models/Rin.obj");
	Cofre_M = Model();
	Cofre_M.LoadModel("Models/Cofre.obj");
	Parrilla_M = Model();
	Parrilla_M.LoadModel("Models/Parrilla.obj");

	Lampara_M = Model();
	Lampara_M.LoadModel("Models/Lampara.obj");

	Fantasma_M = Model();
	Fantasma_M.LoadModel("Models/Fantasma.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,	//color de la luz
		0.03f, 0.03f,			//Radiación (modifica el reflejo de la luz, primer parametro), segundo parametro componente difusa (tonalidad del color con la luz)
		0.0f, -1.0f, 0.0f);	//cambio clase

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(0.4f, 0.6f, 1.0f,	//azul claro para el fantasma
		1.0f, 1.0f,
		20.0f, 5.0f, 5.0f,
		1.0f, 0.09f, 0.03f);	//con, lin, exp
	pointLightCount++;
	//Lampara
	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,	//Blanca
		2.0f, 1.0f,
		12.0f, 10.0f, 20.0,
		1.0f, 0.09f, 0.03f);	//con, lin, exp
	pointLightCount++;

	//Segundo arreglo para apagar la luz de la lámpara
	unsigned int pointLightCount2 = 0;
	pointLights2[0] = pointLights[1];		//Luz puntuntual Lámpara
	pointLightCount2++;
	pointLights2[1] = pointLights[0];		//Luz puntual azul claro
	pointLightCount2++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,	//con, lin, exp
		5.0f);
	spotLightCount++;

	//luz verde para el cofre
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		15.0f, 1.0f,
		-14.0f, 0.5f, -15.0f,		//Posición
		0.0f, -1.0f, 0.0f,			//Vector de dirección
		1.0f, 0.5f, 0.1f,			//Atenuación (No poner en ceros)
		25.0f);
	spotLightCount++;
	
	//Luz del helicoptero
	spotLights[2] = SpotLight(0.7f, 0.7f, 0.0f,
		1.0f, 1.0f,					//Rango, color
		0.0f, 4.0f, 6.0,			//Posición
		0.0f, -1.0f, 0.0f,			//Vector de dirección
		0.0f, 0.4f, 0.0f,			//Atenuación (No poner en ceros)
		20.0f);						//angulo de apertura
	spotLightCount++;

	//se crean mas luces puntuales y spotlight 
	//Luz azul (Parte delantera del coche)
	spotLights[3] = SpotLight(0.0f, 0.0f, 1.0f,
		15.0f, 1.0f,				//Rango, color
		-14.0f, 0.5f, -8.5f,		//Posición
		-5.0f, 0.0f, 0.0f,			//Vector de dirección
		1.0f, 0.0f, 0.01f,			//Atenuación (No poner en ceros)
		25.0f);						//angulo de apertura
	spotLightCount++;

	//Luz roja (Parte trasera del coche)
	spotLights[4] = SpotLight(1.0f, 0.0f, 0.0f,
		15.0f, 1.0f,				//Rango, color
		-5.8f, 0.7f, -8.6f,			//Posición
		1.0f, 0.0f, 0.0f,			//Vector de dirección
		1.0f, 0.0f, 0.01f,			//Atenuación (No poner en ceros)
		25.0f);						//angulo de apertura
	spotLightCount++;

	unsigned int spotLightCount2 = 0;
	spotLights2[0] = spotLights[0];	//Luz linterna
	spotLightCount2++;
	spotLights2[1] = spotLights[1];	//Luz Cofre
	spotLightCount2++;
	spotLights2[2] = spotLights[2];	//Luz helicoptero
	spotLightCount2++;
	spotLights2[3] = spotLights[4];	//Luz roja (parte trasera carro)
	spotLightCount2++;
	spotLights2[4] = spotLights[3];	//Luz azul (parte delantera carro)
	spotLightCount2++;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		spotLights2[0].SetFlash(lowerLight, camera.getCameraDirection());

		//Mueve Luz azul del carro de acuerdo si se mueve el carro o no
		glm::vec3 mueveLuz1 = glm::vec3(-14.0f, 0.5f, -8.5f) + glm::vec3(mainWindow.getTransladaCarro(), 0.0f, 0.0f);
		spotLights[3].SetFlash(mueveLuz1, glm::vec3(-1.0f, 0.0f, 0.0f));

		//Mueve Luz roja del carro de acuerdo si se mueve el carro o no
		glm::vec3 mueveLuz2 = glm::vec3(-5.8f, 0.7f, -8.6f) + glm::vec3(mainWindow.getTransladaCarro(), 0.0f, 0.0f);
		spotLights2[3].SetFlash(mueveLuz2, glm::vec3(1.0f, 0.0f, 0.0f));

		//Mueve Luz amarilla del helicoptero de acuerdo si se mueve el helicoptero o no
		glm::vec3 mueveLuz3 = glm::vec3(0.0f, 4.5f, 6.0) + glm::vec3(mainWindow.getmuevex(), 0.0f, 0.0f);		//Tecla Y y U
		spotLights[2].SetFlash(mueveLuz3, glm::vec3(0.0f, -1.0f, 0.0f));
		spotLights2[2].SetFlash(mueveLuz3, glm::vec3(0.0f, -1.0f, 0.0f));

		//Mueve Luz verde del cofre de acuerdo a como rote el cofre		teclas V y B
		glm::mat4 rotacionLuz = glm::rotate(glm::mat4(1.0f), glm::radians(mainWindow.getrotaCofre()), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 mueveLuz4 = glm::vec3(-13.0, 0.99, -10) + glm::vec3(mainWindow.getTransladaCarro(), 0.0f, 0.0f);		//Tecla 1 y 2
		glm::vec3 direccion = glm::normalize(glm::vec3(rotacionLuz * glm::vec4(0.0f, -0.1f, 0.0f, 0.0f)));		
		spotLights[1].SetFlash(mueveLuz4, direccion);
		spotLights2[1].SetFlash(mueveLuz4, direccion);


		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		//shaderList[0].SetPointLights(pointLights, pointLightCount);
		//shaderList[0].SetSpotLights(spotLights, spotLightCount);
		
		if (mainWindow.getBanderaLuzFaro() == 1.0f) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount-1);
		}
		else{
			shaderList[0].SetSpotLights(spotLights2, spotLightCount2 - 1);
		}

		//Entra al estado 0 por defecto, es decir que está prendido la luz del fantasma 
		//Y también la luz de la lámpara
		//Tecla L --> Luz de la lámpara
		//Tecla K --> Luz del fantasma
		int estado = 0; 		
		if (mainWindow.getEstadoLampara() == 1.0f && mainWindow.getEstadoFantasma() == 1.0f)
			estado = 0;
		else if (mainWindow.getEstadoLampara() == 1.0f && mainWindow.getEstadoFantasma() == 0.0f)
			estado = 1;
		else if (mainWindow.getEstadoLampara() == 0.0f && mainWindow.getEstadoFantasma() == 1.0f)
			estado = 2;
		else if (mainWindow.getEstadoLampara() == 0.0f && mainWindow.getEstadoFantasma() == 0.0f)
			estado = 3;

		switch (estado) {
			case 0:	//Ambos PointLight prendidos 
				shaderList[0].SetPointLights(pointLights, pointLightCount);
				break;
			case 1:	//Solo la lámpara está prendida
				shaderList[0].SetPointLights(pointLights2, pointLightCount - 1);
				break;
			case 2:	//Solo el fantasma está prendido
				shaderList[0].SetPointLights(pointLights, pointLightCount2 - 1);
				break;
			case 3:	//Todos los PointLight están apagados
				shaderList[0].SetPointLights(pointLights2, pointLightCount2 - 2);
				break;
			default:
				break;
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4  modelaux2(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		//Helicoptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::translate(model, glm::vec3(mainWindow.getmuevex(), 0.0f, 0.0f));	// Mover(transladar) con Y y U
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//Lámpara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -0.95f, 20.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara_M.RenderModel();

		//Carro sin llantas y cofre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -10.0f));
		model = glm::translate(model, glm::vec3(mainWindow.getTransladaCarro(), 0.0f, 0.0f));	// Mover(transladar) con 1 y 2
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		KitCarro_M.RenderModel();		//Muestra carro y ojos

		//Llanta derecha delantera
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.1f, 0.7f, -1.65f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotaLlantas()), glm::vec3(0.0f, 0.0f, 1.0f));	//Rotar con Z y X
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaDerDelantera_M.RenderModel();		//Muestra Llanta

		//Rin derecha delantera
		model = modelaux2;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin_M.RenderModel();		//Muestra rin

		//Llanta derecha trasera
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.7f, 0.7f, -1.65f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotaLlantas()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaDerTrasera_M.RenderModel();		//Muestra Llanta

		//Rin derecha delantera
		model = modelaux2;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin_M.RenderModel();		//Muestra rin

		//Llanta Izquierda trasera
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.7f, 0.7f, 1.65f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotaLlantas()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaIzqTrasera_M.RenderModel();		//Muestra Llanta

		//Rin Izquierda trasera
		model = modelaux2;
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin_M.RenderModel();		//Muestra rin

		//Llanta Izquierda Delantera
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.1f, 0.7f, 1.65f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotaLlantas()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaIzqDelantera_M.RenderModel();		//Muestra Llanta

		//Rin Izquierda Delantera
		model = modelaux2;
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin_M.RenderModel();		//Muestra rin

		//Cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.15f, 1.99f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotaCofre()), glm::vec3(0.0f, 0.0f, 1.0f));	//Rotar con V y B
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cofre_M.RenderModel();		//Muestra cofre

		//Parrilla
		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.82f, 0.95f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Parrilla_M.RenderModel();		//Muestra parrilla

		//Pared
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		/**/

		//Dado de Opengl
		//Ejercicio 1: Agregar su dado de 8 caras y editar sus normales para que las caras del dado sean iluminadas correctamente.
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 5.0f, -5.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));	//Rotar con T
		model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));	//Rotar con R
		model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));	//Rotar con E
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		octaedroTexture.UseTexture();
		meshList[4]->RenderMesh();

		//Ejercicio 3
		//Modelo del fantasma
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 5.0f, 5.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fantasma_M.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
