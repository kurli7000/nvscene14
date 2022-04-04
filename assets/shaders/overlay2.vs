attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec2 a_data0;

uniform float distort;

varying vec2 tc, tc2, tc3;

void main() {
	gl_Position = a_position;
	tc = a_texcoord;
	tc2 = a_data0;
	tc3 = a_texcoord;
	//tc3.x = (a_texcoord.x - 0.45) * (1.0 + distort) + 0.45;
 	//tc3.y = (a_texcoord.y - 0.55) * (1.0 + distort) + 0.55;
}
