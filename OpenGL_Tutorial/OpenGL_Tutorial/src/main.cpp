#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void processInput( GLFWwindow* window );

// 스크린 크기 설정
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 쉐이더 GLSL 코드
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
	/* GLFW 초기화 및 옵션 설정 */
	glfwInit();

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	/* 윈도우 개체 생성 */
	GLFWwindow* window = glfwCreateWindow( 800, 600, "LearnOpenGL", NULL, NULL );
	if( window == NULL )
	{
		std::cout << "GLFW 윈도우 생성 실패" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent( window );
	glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

	/* GLAD 초기화 */
	if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
		std::cout << "GLAD 초기화 실패" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	/* 쉐이더 프로그램 빌드 & 컴파일 */
	// Vertex Shader
	unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );
	// 쉐이더 컴파일 오류 체크
	int success;
	char infoLog[512];
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
		std::cout << "Vertex Shader 컴파일 오류\n" << infoLog << std::endl;
	}

	// Fragment Shader
	unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaerSource, NULL );
	glCompileShader( fragmentShader );
	// 쉐이더 컴파일 오류 체크
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if( !success )
	{
		glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
		std::cout << "Fragment Shader 컴파일 오류\n" << infoLog << std::endl;
	}

	// 쉐이더들 연결하기(link shaders)
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );

	// 링킹 에러 체크
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
	if( !success )
	{
		glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
		std::cout << "쉐이더 링킹 오류\n" << infoLog << std::endl;
	}
	// 생성하여 컴파일해 링킹완료한 쉐이더 오브젝트 제거
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	/* vertex 데이터, 버퍼 세팅 및 vertex attribute 설정 */
	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,	// 왼쪽
		 0.5f, -0.5f, 0.0f, // 오른쪽
		 0.0f,  0.5f, 0.0f  // 위쪽
	};

	unsigned int VBO, VAO;	// VBO : Vertex Buffer Object (GPU 메모리에 많은 꼭짓점들을 저장)
							// VAO : Vertex Array Object (vetex attribute 설정과 VBO들을 저장)

	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );

	// VAO를 먼저 bind 해주고, 그 다음 vertex buffer를 bind 하고 세팅, vertex attributes를 설정.
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
		// 1.사용자 입력 체크
		processInput( window );

		// 2. 렌더링 명령
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		// 삼각형 그리기
		glUseProgram( shaderProgram );
		glBindVertexArray( VAO );
		glDrawArrays( GL_TRIANGLES, 0, 3 );

		// 3. 이벤트 체크 및 버퍼 스왑
		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	// 자원 할당 해제
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
	// escape 키 누를 경우 윈도우 종료하도록 함.
	if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, true );
	}
}