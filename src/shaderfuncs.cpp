#include <shaderfuncs.hpp>
#include <math_vector.hpp>
#include <math_matrix.hpp>
#include <file.hpp>

std::string vfn = "./src/vertex.vs", ffn = "./src/fragment.fs";
GLint gScaleLocation;
GLint transformationLocation;

// Basic read function, get results from out_str
void ReadShaderFile(std::string filename, std::string& out_str) {
	File file{ filename };
	file.read();
	out_str = file.contents;
}

void AddShader(GLuint program, const char* contents, GLenum type) {
	GLuint shader_obj = glCreateShader(type);

	if (shader_obj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", type);
		exit(0);
	}
	const GLchar* p[1] = { contents };
	GLint lengths[1] = { strlen(contents) };

	// Get all source files and load them into shader obj
	glShaderSource(shader_obj, 1, p, lengths);

	// Compile all source files in shader obj
	glCompileShader(shader_obj);

	// Check that compilation was successful
	GLint success;
	glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &success);

	if (!success) {
		// Error log
		GLchar info_log[1024];
		glGetShaderInfoLog(shader_obj, 1024, NULL, info_log);
		fprintf(stderr, "Failed to compile shader type %d with following error: %s\n", type, info_log);
		exit(1);
	}

	// Attach fully compiled and check shader obj to program
	glAttachShader(program, shader_obj);
}

void CompileShaders() {

	GLuint shader = glCreateProgram();
	
	if (shader == 0) {
		fprintf(stderr, "Error creating shader");
	}

	std::string fs, vs;
	
	ReadShaderFile(vfn, vs);

	if (vs.empty()) {
		fprintf(stderr, "Failed to read vertex shader\n");
		exit(1);
	}

	AddShader(shader, vs.c_str(), GL_VERTEX_SHADER);

	ReadShaderFile(ffn, fs);

	if (fs.empty()) {
		fprintf(stderr, "Failed to read fragment shader\n");
		exit(1);
	}
	
	AddShader(shader, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar log[1024] = {0};
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shader, sizeof(log), NULL, log);
		fprintf(stderr, "Failed to link shader: %s\n", log);
		exit(1);
	}
	
	gScaleLocation = glGetUniformLocation(shader, "gScale");
	if (gScaleLocation == -1) {
		printf("Error getting location of gScale\n");
		exit(1);
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shader, sizeof(log), NULL, log);
		fprintf(stderr, "Failed to validate shader: %s\n", log);
		exit(1);
	}
	
	glUseProgram(shader);
}




