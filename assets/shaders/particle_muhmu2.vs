attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

uniform mat4 mat;
uniform vec3 up, right;
uniform float size;
uniform vec3 campos;
uniform float time;

varying float brz;

varying vec2 tc;

void main() {
	vec3 pos = a_position;
	pos.x += sin(a_position.z*8.72+time*4.1)*0.15;
	pos.y += time;
	pos.z += sin(a_position.x*7.19+time*5.3)*0.15;
	pos = mod(pos - campos, 10.0) + campos - vec3(5.0);

	brz = 1.0 - length(pos - campos) / 8.0;
 	gl_Position = mat * vec4(up * a_normal.x * size + right * a_normal.y * size + pos, 1.0);
	tc = a_texcoord;
}
