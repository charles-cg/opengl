#include "config.h"

// array with vertices coordinates
std::vector<GLfloat> vertices = {
//     coordinates    /     color       /  tex coord  //
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // lower left corner
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // upper left corner
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // upper  rightcorner
     0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // lower left
};

// array for indices
std::vector<GLuint> indices = {
	0, 2, 1, // upper triangle
	0, 3, 2  // lower triangle
};

int main() {
	// initialize glfw
	glfwInit();

	// specify the version used, this has to be the same as the GLAD version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// instantiate a GLFWwindow object, the constructor is (width, height, title, fullscreen, share resources)
	GLFWwindow* window = glfwCreateWindow(800, 800, "Graphics Programming", NULL, NULL);
	// error handling if the window could not be created
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}
	
	// introduce this new window into the context
	glfwMakeContextCurrent(window);

	// GLAD configures open gl
	gladLoadGL();

	// viewport of open gl
	glViewport(0, 0, 800, 800);

	// instantiate shader program reading from files
    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");

	// instantiate VAO
    VAO VAO1;
	// Bind this new VAO
    VAO1.Bind();

	// Instantiate VBO
    VBO VBO1(vertices, vertices.size() * sizeof(GLfloat));
	// Instantiate EBO
    EBO EBO1(indices, indices.size() * sizeof(GLuint));

	// bind VBO to the VBO
    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind VAO, VBO and EBO
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// texture

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("../textures/pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	Texture popCat("../textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// loop to check if the close button has been pressed
	while (!glfwWindowShouldClose(window)) {
        // specify a color to display
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // clean back buffer and assign it this color buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// specify opengl which shader program to use
        shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		popCat.Bind();
		// bind the vao so opengl know how to use it
		VAO1.Bind();
		// call the triangle primitive to draw it
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	    // swap the front buffer with this back buffer
		glfwSwapBuffers(window);
		// take care of glfw buffers
		glfwPollEvents();
	}

	// delete VAO, VBO and program to clean up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	// if the button is pressed destroy the window instantiation
	glfwDestroyWindow(window);

	// terminate the program
	glfwTerminate();
	return 0;
}