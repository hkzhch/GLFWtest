#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION

#include "LightDirection.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
//unsigned int LoadTexture(const char* name);
float alpha = 0.2;
bool firstMouse = true;
float offset = 0.0f;
double lastX;
double lastY;

Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), 0.0f, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));


int main(int agrc,char* argv[])
{
	std::string exePath = argv[0];
	//GLFW initialize
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLTest", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Faild to Create GLFW Window" << std::endl;
		glfwTerminate();

		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	//glad initialize
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faile to initialize GLAD" << std::endl;
		return -1;
	}

	//Viewport initialize
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//vertex init
	float vertices2[] =
	{	//**location**       **color**     **texture**					
		//-0.5f,-0.5f, 0.0f, 1.0f,0.0f,0.0f,  0.0f,0.0f,		 						   //¶‰º
		// 0.5f,-0.5f, 0.0f, 0.0f,1.0f,0.0f,  1.0f,0.0f,								   //‰E‰º
		//-0.5f, 0.5f, 0.0f, 0.2f,0.3f,0.6f,  0.0f,1.0f,								   //¶ã
		// 0.5f, 0.5f, 0.0f, 0.0f,0.0f,1.0f,  1.0f,1.0f								   //‰Eã
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,					//1
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,					//2
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,					//3
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,					//4
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,					//5
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,					//6
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,					//7
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,					//8

	};

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,			//0.0f,0.1f
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,			//1.0f,0.1f
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,			//1.0f,1.1f
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,			//1.0f,1.1f
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,			//0.0f,1.1f
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,			//0.0f,0.1f

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	unsigned int indices[] =
	{
		0,1,2,2,3,1,
		4,5,6,6,7,4,
		7,3,0,0,4,7,
		6,2,1,1,5,6,
		0,1,5,5,4,0,
		3,2,6,6,7,3
	};

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//
	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//
	//
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//Mesh cube(vertices);
	Model mymodel(exePath.substr(0, exePath.find_last_of("\\")) + "\\model\\nanosuit.obj");
	Shader* myShader = new Shader("vertexShader.vert", "fragmentShader.frag");
	/*Material* myMaterial = new Material(myShader, glm::vec3(1.0f, 1.0f, 1.0f),
		LoadTexture("container2.png"),
		LoadTexture("container2_specular.png"),
		LoadTexture("emission.jpg"),
		256);*/
	LightDirection myLightDirection(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(45.0f), glm::radians(180.0f), 0.0f));
	LightPoint myLightPoint(glm::vec3(15.0f, -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	LightSpot myLightSpot(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
	myShader->use();
	//myShader->setInt("material.diffuse", myMaterial->diffuse);
	//myShader->setInt("ourTexture2", 1);

	//depth test enable
	glEnable(GL_DEPTH_TEST);
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);
		//render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		//myShader->setFloat("xOffset", 0.5f);
		myShader->use();
		//glActiveTexture(GL_TEXTURE0 + myMaterial->Diffuse);
		//glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
		//glActiveTexture(GL_TEXTURE0 + myMaterial->Specular);
		//glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
		//glActiveTexture(GL_TEXTURE0 + myMaterial->Emission);
		//glBindTexture(GL_TEXTURE_2D, myMaterial->emission);
		myShader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);

#pragma region DirectionLightUniform
		myShader->setVec3("lightDir.direction", myLightDirection.direction);
		myShader->setVec3("lightDir.position", myLightDirection.position);
		myShader->setVec3("lightDir.color", myLightDirection.color);
#pragma endregion

#pragma region PointLightUniform
		myShader->setVec3("lightPoint.color", myLightPoint.color);
		myShader->setVec3("lightPoint.position", myLightPoint.position);
		myShader->setFloat("lightPoint.constant", myLightPoint.constant);
		myShader->setFloat("lightPoint.linear", myLightPoint.linear);
		myShader->setFloat("lightPoint.quadratic", myLightPoint.quadratic);
#pragma endregion

#pragma region SpotLightUniform
		myShader->setVec3("lightSpot.color", myLightSpot.color);
		myShader->setVec3("lightSpot.position", myLightSpot.position);
		myShader->setVec3("lightSpot.direction", myLightSpot.direction);
		myShader->setFloat("lightSpot.cosPhyInner", myLightSpot.cosPhyInner);
		myShader->setFloat("lightSpot.cosPhyOuter", myLightSpot.cosPhyOuter);
#pragma endregion

		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		//unsigned int loc = glGetUniformLocation(myShader->ID, "transform");
		//glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(trans));
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.getViewMatrix();
		//float radius = 10.0f;
		//float camx = sin(glfwGetTime()) * radius;
		//float camz = cos(glfwGetTime()) * radius;
		//view = glm::lookAt(glm::vec3(camx, 0.0f, camz), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		myShader->setFloat("alpha", alpha);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//for (int i = 0; i < 1; i++)
		//{
		//	//float angle = 20.0 * i;
		//	//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	//cube.Draw(myShader);
		//	//glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		model = glm::mat4(1.0f);    // model initialize
		//model = glm::translate(model, cubePositions[i]);
		myShader->setMat4("model", model);
		float emissionMove = glfwGetTime() * 0.5;
		myShader->setVec3("colorT", glm::vec3(1.0f, 0.0, 0.0));
		myShader->setFloat("emissionMove", emissionMove);
		myShader->setMat4("model", model);
		myShader->setMat4("view", view);
		myShader->setMat4("projection", projection);
		myShader->setVec3("viewPos", camera.Position);
		//myShader->setVec3("material.ambient", myMaterial->ambient);
		//myShader->setInt("material.diffuse", myMaterial->Diffuse);
		//myShader->setInt("material.specular", myMaterial->Specular);
		//myShader->setInt("material.emission", myMaterial->Emission);
		//myShader->setFloat("material.shininess", myMaterial->shininess);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		mymodel.Draw(myShader);


		//check events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.updateCameraPositions();
	}
	//glDeleteBuffers(1, &VBO);
	//glDeleteVertexArrays(1, &VAO);
	//	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;


}

/// <summary>
/// window size reset
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	offset += 0.001f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	offset -= 0.001f;
	//}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -1.0f;
	}
	else
	{
		camera.speedZ = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 1.0f;
	}
	else
	{
		camera.speedX = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.speedY = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.speedY = -1.0f;
	}
	else
	{
		camera.speedY = 0.0f;
	}
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


//unsigned int LoadTexture(const char* name)
//{
//	unsigned int texture;
//	glGenTextures(1, &texture);
//
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 0);
//
//	if (data)
//	{
//		GLenum format;
//		if (nrChannels == 1)
//			format = GL_RED;
//		else if (nrChannels == 3)
//			format = GL_RGB;
//		else if (nrChannels == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	}
//	else
//	{
//		std::cout << "failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	return texture;
//}