precision mediump float;

uniform sampler2D t_color;
uniform sampler2D t_color2;
uniform sampler2D t_buf;

uniform float br;
uniform float contrast;
uniform float distort;

varying vec2 tc, tc2, tc3;

void main() {
	vec2 tcx = tc;
	vec2 tc3x = tc3;
	float a, b, c;
	a = fract(sin(tc2.x + cos(fract(tcx.x*4.27)*15.1)*19.32))*distort;
	b = fract(cos(tc2.x + sin(fract(tc3x.x*5.12)*21.7)*13.11))*distort;
	c = fract(sin(a + sin(fract(b))*55.5))*distort*0.2;
	tcx += vec2(c, a);
	tc3x -= vec2(c, b);
	vec4 col = texture2D(t_buf, tcx) * vec4(0.9, 0.6, 0.9, 0.5) + texture2D(t_buf, tc3x) * vec4(0.6, 0.9, 0.6, 0.5);
	vec4 col2 = col * (texture2D(t_color, tc) * texture2D(t_color2, tc2) * contrast);
	gl_FragColor = (col2 - 0.5)*contrast+0.5;
	//gl_FragColor = texture2D(t_color, tc) * br + texture2D(t_color2, tc2);
}
