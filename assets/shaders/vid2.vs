attribute vec3 a_position;
attribute vec3 a_color;

uniform mat4 mat;

varying vec3 color;


void main() {
	vec4 pos = vec4(a_position, 1.0);
	gl_Position = mat * pos;
	color = a_color;
}
