precision mediump float;

uniform sampler2D t_color;
uniform sampler2D t_depth;
uniform float znear, zfar;
uniform vec2 texelsize;

varying vec2 tc;

float lin(float z) {
	float z_n = 2.0 * z - 1.0;
	return 2.0 * znear * zfar / (zfar + znear - z_n * (zfar - znear));
}


float getdepth(vec2 texcoord) {
	vec2 offset1 = vec2(texelsize.x, 0.0);
	vec2 offset2 = vec2(0.0, texelsize.y);
	vec2 offset3 = vec2(-texelsize.x, 0.0);
	vec2 offset4 = vec2(0.0, -texelsize.y);

	float d1 = texture2D(t_depth, texcoord + offset1).r;	
	float d2 = texture2D(t_depth, texcoord + offset2).r;	
	float d3 = texture2D(t_depth, texcoord + offset3).r;	
	float d4 = texture2D(t_depth, texcoord + offset4).r;	
	return lin((d1+d2+d3+d4)/4.0);
}


vec3 getnormal(vec2 texcoord, float depth) {
	vec2 offset1 = vec2(texelsize.x, 0.0);
	vec2 offset2 = vec2(0.0, texelsize.y);
	float depthx = getdepth(tc + offset1);
	float depthy = getdepth(tc + offset2);

	vec3 dir1 = vec3(offset1, depthx - depth);
	vec3 dir2 = vec3(offset2, depthy - depth);
	vec3 normal = cross(dir1, dir2);
	normal.z = -normal.z;
  	return normalize(normal);
}


void main() {
	float depth = getdepth(tc);
	vec3 normal = getnormal(tc, depth);
	vec3 light = vec3(-1.0);
	vec3 col = vec3(dot(normal, light));

	gl_FragColor = vec4(col, 1.0);
}
