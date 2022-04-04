precision mediump float;

uniform sampler2D t_color;
uniform sampler2D t_depth;
uniform float znear, zfar;
uniform vec2 texelsize;
uniform float rad;
uniform float u_br;
uniform float time;

varying vec2 tc;

const float dimming = 0.1;
const float zoffset = 0.001;

float lin(float z) {
	float z_n = 2.0 * z - 1.0;
	return 2.0 * znear * zfar / (zfar + znear - z_n * (zfar - znear));
}

void main() {
	float depth = texture2D(t_depth, tc).r;
	vec3 col = texture2D(t_color, tc).rgb;
	float br = 1.0;
	float oolindepth = 1.0 / lin(depth);
	float angle = fract(sin(tc.x * 4125.5 + tc.y * 4624.28) * 555.21) * 12867.58 * depth;
	float radius = rad * oolindepth;
	mat2 mat = mat2(
		cos(angle) * radius, -sin(angle) * radius,
		sin(angle) * radius,  cos(angle) * radius);
	float offset = zoffset * (1.0 + fract(angle)*4.0);

	vec2 tc1 = tc + mat * vec2( 0.05, -0.03);
	vec2 tc2 = tc + mat * vec2( 0.09,  0.08);
	vec2 tc3 = tc + mat * vec2( 0.12,  0.15);
	vec2 tc4 = tc + mat * vec2(-0.11, -0.22);
	vec2 tc5 = tc + mat * vec2(-0.06, -0.31);
	vec2 tc6 = tc + mat * vec2(-0.25, -0.28);
	vec2 tc7 = tc + mat * vec2( 0.44,  0.01);
	vec2 tc8 = tc + mat * vec2( 0.36,  0.34);
	vec2 tc9 = tc + mat * vec2(-0.09, -0.56);
	vec2 tc10 = tc + mat * vec2(-0.47, -0.41);
	vec2 tc11 = tc + mat * vec2( 0.44,  0.53);
	vec2 tc12 = tc + mat * vec2( 0.71,  0.23);
	//vec2 tc13 = tc + mat * vec2(-0.11,  0.81);
	//vec2 tc14 = tc + mat * vec2(-0.88, -0.00);
	//vec2 tc15 = tc + mat * vec2( 0.46, -0.82);
	//vec2 tc16 = tc + mat * vec2( 0.64, -0.77);

	if (depth < 0.999)
	{
		depth -= offset * oolindepth;

		float depth1 = texture2D(t_depth, tc1).r;
		float depth2 = texture2D(t_depth, tc2).r;
		float depth3 = texture2D(t_depth, tc3).r;
		float depth4 = texture2D(t_depth, tc4).r;
		float depth5 = texture2D(t_depth, tc5).r;
		float depth6 = texture2D(t_depth, tc6).r;
		float depth7 = texture2D(t_depth, tc7).r;
		float depth8 = texture2D(t_depth, tc8).r;
		float depth9 = texture2D(t_depth, tc9).r;
		float depth10 = texture2D(t_depth, tc10).r;
		float depth11 = texture2D(t_depth, tc11).r;
		float depth12 = texture2D(t_depth, tc12).r;
		//float depth13 = texture2D(t_depth, tc13).r;
		//float depth14 = texture2D(t_depth, tc14).r;
		//float depth15 = texture2D(t_depth, tc15).r;
		//float depth16 = texture2D(t_depth, tc16).r;

		if (depth1 < depth) br -= dimming;
		if (depth2 < depth) br -= dimming;
		if (depth3 < depth) br -= dimming;
		if (depth4 < depth) br -= dimming;
		if (depth5 < depth) br -= dimming;
		if (depth6 < depth) br -= dimming;
		if (depth7 < depth) br -= dimming;
		if (depth8 < depth) br -= dimming;
		if (depth9 < depth) br -= dimming;
		if (depth10 < depth) br -= dimming;
		if (depth11 < depth) br -= dimming;
		if (depth12 < depth) br -= dimming;
		//if (depth13 < depth) br -= dimming;
		//if (depth14 < depth) br -= dimming;
		//if (depth15 < depth) br -= dimming;
		//if (depth16 < depth) br -= dimming;
	}

	gl_FragColor = vec4(col * br * u_br, lin(depth)/zfar);
}
