#include <gl/glew.h>
#include <gl/freeglut.h>

enum StitchType {
	Knit,
	Purl,
	SlipYF,
	SlipYB
};

void generate_points(GLuint vertex_buffer, size_t vb_size, size_t start, StitchType type);

