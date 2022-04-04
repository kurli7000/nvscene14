attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

uniform mat4 mat;
uniform vec3 up, right;
uniform float size;
uniform vec3 params;
uniform float blow;

varying vec2 tc;

void main() {
	vec3 blowdir = a_position - params;
	float blowpow = 1.0 / length(blowdir) * blow;
	blowpow = blowpow + a_normal.z * blowpow * 0.3;
	blowpow *= blowpow * blowpow;
	normalize(blowdir);
	vec3 pos = a_position + blowdir * blowpow;
 	gl_Position = mat * vec4(up * a_normal.x * size + right * a_normal.y * size + pos, 1.0);
	tc = a_texcoord;
}
