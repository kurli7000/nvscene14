precision mediump float;

uniform float br;

varying vec3 color;

void main() {
	if (color.r*br > 0.5) discard;
	gl_FragColor = vec4((vec3(1.0)-color)*br, 1.0);
}
