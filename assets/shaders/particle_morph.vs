attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;
attribute vec3 a_data0;

uniform mat4 mat;
uniform vec3 up, right;
uniform float size;
uniform float morph;
uniform float time;
varying vec2 tc;

void main() {
	float m = clamp(morph * 2.0 + a_position.x * 0.25 + a_normal.z * 0.02 , 0.0, 1.0);
	vec3 pos = mix(a_position, a_data0, m);
	float wob2 = sin(m * 3.141593);
	float wob = 0.15 + wob2;
	wob2 = 1.0 - wob2 * 0.5;
	vec3 wave = vec3(
		sin(pos.y * 2.5 + time * 6.0), 
		sin(pos.z * 2.7 + time * 5.1), 
		sin(pos.x * 1.9 - time * 5.8)) * wob;
	pos += wave;
	pos.yz *= wob2;
	vec3 corner = up * a_normal.x * size + right * a_normal.y * size;
 	gl_Position = mat * vec4(corner + pos, 1.0);
	tc = a_texcoord;
}
