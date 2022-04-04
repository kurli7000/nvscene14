precision mediump float;

uniform float br;

varying vec3 v_color;

void main() {
	gl_FragColor = vec4(v_color, 1.0);
}
