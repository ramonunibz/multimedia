#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

#define USE_INDEX_BUFFER 1

#ifdef USE_INDEX_BUFFER
  #define NUM_VERTICES 6
  #define NUM_INDICES 9
#else
  #define NUM_VERTICES 9
#endif

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int shaderProgram;
int vertexShader, fragmentShader;
int positionID, colorID;
int numberVertices;

//i need this to know how many lines triangles there are
int findNumber() {
	int number=0;
	std::ifstream myfile;
	myfile.open("original.obj");
	if (myfile.is_open()) {
		string line;
		while (std::getline(myfile, line)) {
			if (line.empty()) {
				number++;
			}
		}
		myfile.close();
	}
	return number;
}


#ifdef USE_INDEX_BUFFER
GLfloat vertices[922*3];
GLfloat colors[922 * 3];

 void ReplaceAll(string &str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}

void createVertices() {
	int i = 0;
	int count = 0;
	ifstream myfile;
	ofstream myResult;
	myfile.open("original.txt");
	myResult.open("result.txt");
	if (myfile.is_open()) {
		if (myfile.is_open()) {
			string line;
			while (getline(myfile, line)) {
				if (line.rfind("v ", 0) == 0) {
					string importantInfo = line.substr(2, line.size());
					myResult << importantInfo << endl;
				}
				if (line.rfind("usemtl ", 0) == 0) {
					string importantInfo = line.substr(14, line.size());
					ReplaceAll(importantInfo, string("_"), string(" "));
					myResult << importantInfo << " 1.0" << endl;
				}
			}
			myfile.close();
			myResult.close();
		}
	}
}		

void vertexConvertor(string str, GLfloat vertices[], int *vertexPos) {
	int pos;
	string a[3];


	// Find position of ':' using find()
	int pos1 = str.find(" ");
	string sub1= str.substr(pos1+1, str.size());
	int pos2 = sub1.find(" ");
	// Copy substring after pos
	a[0] = str.substr(0, pos1);
	a[1] = str.substr(pos1+1, str.find(" "));
	a[2] = str.substr(pos2, str.size());

	// prints the result


	pos = *vertexPos;
	vertices[pos] = stoi(a[0]);
	pos++;
	vertices[pos] = stoi(a[0]);
	pos++;
	vertices[pos] = stoi(a[0]);
	pos++;
}

GLfloat colorConvertor(string rgb) {
	int r, g, b, p = 0;
	GLfloat newR, newG, newB, newTest=0;
	float full = 255;
	string a[4];
	string S, T;  // declare string variables  
	stringstream ss;

	stringstream X(rgb); // X is an object of stringstream that references the S string  

	// use while loop to check the getline() function condition  
	while (getline(X, T, ' ')) {
		/* X represents to read the string from stringstream, T use for store the token string and,
		 ' ' whitespace represents to split the string where whitespace is found. */

		a[p] = T; // print split string
		p++;
	}
	p = 0;
	r = stoi(a[0]);
	g = stoi(a[1]);
	b = stoi(a[2]);
	newR = r / full;
	newG = g / full;
	newB = b / full;

	return newTest;
}

void fillArrays() {
	int lineCount = 1;
	int vertexPos = 0;
	int colorPos = 0;
	ifstream myfile;
	myfile.open("result.txt");
	if (myfile.is_open()) {
		string line;
		while (getline(myfile, line)) {
			if ((lineCount % 4) != 0) {
				//cout << "HI" << endl;
				vertexConvertor(line, vertices, &vertexPos);
			}
			else {
				
			}
		}
	}
}


GLuint indices[] = { 0, 1, 2, 1, 3, 4, 2, 4, 5 };

#else
GLfloat vertices[];

GLfloat colors[];
#endif

unsigned int vbo;
unsigned int vao;
unsigned int indexBufferID;

// loadFile - loads text file into char* fname
std::string loadFile(const char *fname) {
	std::ifstream file(fname);
	if (!file.is_open()) {
		std::cout << "Unable to open file " << fname << std::endl;
		exit(1);
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}

int loadShaders() {

	int vlength, flength;
	
	std::string vertexShaderString = loadFile("colorShader.vert");
	std::string fragmentShaderString = loadFile("colorShader.frag");
	vlength = vertexShaderString.length();
	flength = fragmentShaderString.length();

	if (vertexShaderString.empty() || fragmentShaderString.empty()) {
		return -1;
	}

	// vertex shader
	const char *vertexShaderCStr = vertexShaderString.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar **)&vertexShaderCStr, &vlength);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	const char *fragmentShaderCStr = fragmentShaderString.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentShaderCStr, &flength);
	glCompileShader(fragmentShader);
	
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void initBuffers() {
	createVertices();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, 7 * NUM_VERTICES * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * NUM_VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * NUM_VERTICES * sizeof(GLfloat), 4 * NUM_VERTICES * sizeof(GLfloat), colors);

#ifdef USE_INDEX_BUFFER
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);
#endif
	positionID = glGetAttribLocation(shaderProgram, "inVertex");
	colorID = glGetAttribLocation(shaderProgram, "inColor");

	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));

	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	// uncomment this call to draw in wireframe polygons.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// initialize

void renderScene() {
#ifdef USE_INDEX_BUFFER
	glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, NULL);
#else
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
#endif
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "IBO - Multiple Triangles - Example", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	if (!loadShaders()) {
		std::cout << "Failed to initialize shaders" << std::endl;
		return -1;
	}

	int num = findNumber();
	cout << num;
	fillArrays();
	cout << vertices[0];
	initBuffers();
	
	// Main Loop
	while (!glfwWindowShouldClose(window)) {
	
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}