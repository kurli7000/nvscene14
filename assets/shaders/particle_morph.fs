precision mediump float;

uniform sampler2D t_color;
uniform vec4 br;

varying vec2 tc;

void main() {
	vec4 tcol = texture2D(t_color, tc);
	if (tcol.a < 0.5) discard;
	gl_FragColor = tcol;
}
