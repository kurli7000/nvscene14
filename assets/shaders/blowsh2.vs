attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec3 a_data0;

uniform mat4 mat;
uniform mat3 nmat;
uniform mat4 smat;
uniform float blow;
uniform vec3 blowpos;
uniform vec3 lightpos;
uniform float focus;

varying vec3 v_diffuse;
varying vec3 v_ambient;
varying vec3 v_tc;
varying float dist;


const float C1 = 0.429043;
const float C2 = 0.511664;
const float C3 = 0.743125;
const float C4 = 0.886227;
const float C5 = 0.247708;
const vec3 L00  = vec3( 0.3783264,  0.4260425,  0.4504587);
const vec3 L1m1 = vec3( 0.2887813,  0.3586803,  0.4147053);
const vec3 L10  = vec3( 0.0379030,  0.0295216,  0.0098567);
const vec3 L11  = vec3(-0.1033028, -0.1031690, -0.0884924);
const vec3 L2m2 = vec3(-0.0621750, -0.0554432, -0.0396779);
const vec3 L2m1 = vec3( 0.0077820, -0.0148312, -0.0471301);
const vec3 L20  = vec3(-0.0935561, -0.1254260, -0.1525629);
const vec3 L21  = vec3(-0.0572703, -0.0502192, -0.0363410);
const vec3 L22  = vec3( 0.0203348, -0.0044201, -0.0452180);


vec3 calc_sh(vec3 normal) {
	vec3 tnorm   = normalize(nmat * normal);
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

mat3 rotationMatrix(vec3 axis, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat3(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c);
}

void main() {
	vec3 blowdir = a_data0 - blowpos;
	float blowpow = 1.0 / length(blowdir) * blow;
	blowpow *= blowpow * blowpow;
	normalize(blowdir);
	vec3 rotaxis = cross(vec3(0.0, 0.0, 1.0), blowdir);
	mat3 rotmat = rotationMatrix(normalize(rotaxis), -blowpow*1.5);
	vec3 rotated = rotmat * (a_position - a_data0) + a_data0;
	vec4 pos = vec4(rotated + blowdir * blowpow, 1.0);
	gl_Position = mat * pos;
	vec3 norm = normalize(nmat * a_normal);
	norm = normalize(rotmat * norm);
	vec3 refl = reflect(normalize(pos.xyz), norm);
	v_ambient = calc_sh(refl)*0.3;
	vec4 smaptc = smat * pos;
	v_tc = (smaptc.xyz / smaptc.w) * 0.5 + 0.5;
	float diff = dot(norm, normalize(nmat * lightpos));
	diff = max(diff, 0.0)*0.65;
	v_diffuse = vec3(diff);
	dist = 1.0 - gl_Position.z / gl_Position.w - focus;

}


