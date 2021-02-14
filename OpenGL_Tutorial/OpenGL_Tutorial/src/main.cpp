#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void processInput( GLFWwindow* window );

// ��ũ�� ũ�� ����
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ���̴� GLSL �ڵ�
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4( aPos.x, aPos.y, aPos.z, 1.0 ); \n"
	"}\0";

const char* fragmentShaerSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
	"}\n\0";

int main()
{
	/* GLFW �ʱ�ȭ �� �ɼ� ���� */
	glfwInit();

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	/* ������ ��ü ���� */
	GLFWwindow* window = glfwCreateWindow( 800, 600, "LearnOpenGL", NULL, NULL );
	if( window == NULL )
	{
		std::cout << "GLFW ������ ���� ����" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent( window );
	glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

	/* GLAD �ʱ�ȭ */
	if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
		std::cout << "GLAD �ʱ�ȭ ����" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	/* ���̴� ���α׷� ���� & ������ */
	// Vertex Shader
	unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );
	// ���̴� ������ ���� üũ
	int success;
	char infoLog[512];
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
		std::cout << "Vertex Shader ������ ����\n" << infoLog << std::endl;
	}

	// Fragment Shader
	unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaerSource, NULL );
	glCompileShader( fragmentShader );
	// ���̴� ������ ���� üũ
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
		std::cout << "Fragment Shader ������ ����\n" << infoLog << std::endl;
	}

	// ���̴��� �����ϱ�(link shaders)
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );

	// ��ŷ ���� üũ
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
	if( !success )
	{
		glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
		std::cout << "���̴� ��ŷ ����\n" << infoLog << std::endl;
	}
	// �����Ͽ� �������� ��ŷ�Ϸ��� ���̴� ������Ʈ ����
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	/* vertex ������, ���� ���� �� vertex attribute ���� */
	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,	// ����
		 0.5f, -0.5f, 0.0f, // ������
		 0.0f,  0.5f, 0.0f  // ����
	};

	unsigned int VBO, VAO;	// VBO : Vertex Buffer Object (GPU �޸𸮿� ���� ���������� ����)
							// VAO : Vertex Array Object (vetex attribute ������ VBO���� ����)

	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );

	// VAO�� ���� bind ���ְ�, �� ���� vertex buffer�� bind �ϰ� ����, vertex attributes�� ����.
	glBindVertexArray( VAO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	// Render Loop
	while( !glfwWindowShouldClose( window ) )
	{
		// 1.����� �Է� üũ
		processInput( window );

		// 2. ������ ���
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		// �ﰢ�� �׸���
		glUseProgram( shaderProgram );
		glBindVertexArray( VAO );
		glDrawArrays( GL_TRIANGLES, 0, 3 );

		// 3. �̺�Ʈ üũ �� ���� ����
		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	// �ڿ� �Ҵ� ����
	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );
	glDeleteProgram( shaderProgram );

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback( GLFWwindow* window, int width, int height )
{
	glViewport( 0, 0, width, height );
}

void processInput( GLFWwindow* window )
{
	// escape Ű ���� ��� ������ �����ϵ��� ��.
	if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, true );
	}
}