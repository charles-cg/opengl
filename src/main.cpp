#include "config.h"

// array with vertices coordinates
std::vector<GLfloat> vertices = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // inner down
};

// array for indices
std::vector<GLuint> indices = {
    0, 3, 5, // lower left triangle
    3, 2, 4, // lower right triangle
    5, 4, 1  // upper triangle
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

    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, vertices.size() * sizeof(GLfloat));
    EBO EBO1(indices, indices.size() * sizeof(GLuint));

    VAO1.linkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

	// loop to check if the close button has been pressed
	while (!glfwWindowShouldClose(window)) {
        // specify a color to display
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // clean back buffer and assign it this color buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// specify opengl which shader program to use
        shaderProgram.Activate();
		// bind the vao so opengl know how to use it
		VAO1.Bind();
		// call the triangle primitive to draw it
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	    // swap the front buffer with this back buffer
		glfwSwapBuffers(window);
		// take care of glfw buffers
		glfwPollEvents();
	}

	// delete VAO, VBO and program to clean up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// if the button is pressed destroy the window instantiation
	glfwDestroyWindow(window);

	// terminate the program
	glfwTerminate();
	return 0;
}