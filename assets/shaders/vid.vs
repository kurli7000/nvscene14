attribute vec3 a_position;
attribute vec3 a_color;
attribute vec3 a_normal;

uniform mat4 mat;
uniform mat4 smat;

varying vec3 color;
varying vec3 v_tc;

const float C1 = 0.429043;
const float C2 = 0.511664;
const float C3 = 0.743125;
const float C4 = 0.886227;
const float C5 = 0.247708;
const vec3 L00  = vec3(  0.3168843,  0.3073441,  0.3495361);
const vec3 L1m1 = vec3(  0.3711289,  0.3682168,  0.4292092);
const vec3 L10  = vec3( -0.0034406, -0.0031891, -0.0039797);
const vec3 L11  = vec3( -0.0084237, -0.0087049, -0.0116718);
const vec3 L2m2 = vec3( -0.0190313, -0.0192164, -0.0250836);
const vec3 L2m1 = vec3( -0.0110002, -0.0102972, -0.0119522);
const vec3 L20  = vec3( -0.2787319, -0.2752035, -0.3184335);
const vec3 L21  = vec3(  0.0011448,  0.0009613,  0.0008975);
const vec3 L22  = vec3( -0.2419374, -0.2410955, -0.2842899);


vec3 calc_sh(vec3 normal) {
	vec3 tnorm = normalize(normal);
	return vec3(0.8, 1.0, 0.8) * (C1 * L22 * (tnorm.x * tnorm.x - tnorm.y * tnorm.y) +
		C3 * L20 *  tnorm.z * tnorm.z +
		C4 * L00 - C5 * L20 +
		2.0 * C1 * L2m2 * tnorm.x * tnorm.y + 
		2.0 * C1 * L21 * tnorm.x * tnorm.z + 
		2.0 * C1 * L2m1 * tnorm.y * tnorm.z + 
		2.0 * C2 * L11 * tnorm.x+
		2.0 * C2 * L1m1 * tnorm.y +
		2.0 * C2 * L10 * tnorm.z);
}


void main() {
	vec4 pos = vec4(a_position, 1.0);
	gl_Position = mat * pos;
	vec3 norm = reflect(normalize(-pos.xyz), a_normal);
	color = calc_sh(norm) * a_color * 2.0;
	//color = a_color;
	//color = color * color * color;
	//vec4 smaptc = smat * pos;
	//v_tc = (smaptc.xyz / smaptc.w) * 0.5 + 0.5;
}
