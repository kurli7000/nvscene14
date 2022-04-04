/*
finaalibuild:
- siivoo assetit
- remote export
- poista debug-versio
- boottaa
- EXIT_TIME
- anal.h:
  - #define FINAL
  - #define SYNC_PLAYER
- Manifest:
  - writing permission pois
  - internet-permission pois
- kopsaa rocketin data /sdcard/tmp -> assets
- release build
 
- screenshotit 160x90, 400x...
- videocap: 
	- bluestacks: adb connect localhost
	- tee /sdcard/tmp/diskwrite
	- write permission manifestiin
	- anal.h:sta definet
	- 32bit framebufferi: DEMOView.java
	- ilman filemaskia: adb pull /sdcard/tmp/diskwrite . 
- google play, screenshotit
- youtube
- infofile
- zip

*/


/////////////////////////////////////////////////////////////////////
// define stuff that goes into ANAL

// bass
#define SOUNDTRACK_FILENAME "wubz.mp3"
#define BPM 142.0
#define EXIT_TIME 4400

// rocket
#define ROCKET_VARIABLES \
	const struct sync_track *sync_fxnum;\
	const struct sync_track *sync_fxbr;\
	const struct sync_track *sync_morph;\
	const struct sync_track *sync_blow;\
	const struct sync_track *sync_blow2;\
	const struct sync_track *sync_vatkain1;\
	const struct sync_track *sync_vatkain2;\
	const struct sync_track *sync_vatkain3;\
	const struct sync_track *sync_vatkain4;\
	const struct sync_track *sync_frame;\
	const struct sync_track *sync_textnum;\
	const struct sync_track *sync_textcnt;\
	const struct sync_track *sync_textbr;\
	const struct sync_track *sync_textxpos;\
	const struct sync_track *sync_textypos;\
	const struct sync_track *sync_textsize;\
	const struct sync_track *sync_textcenter;\
	const struct sync_track *sync_distort;\
	const struct sync_track *sync_contrast;\
	const struct sync_track *sync_focus;\


#define ROCKET_TRACKS \
	sync_fxnum = sync_get_track(rocket, "fxnum");\
	sync_fxbr = sync_get_track(rocket, "fxbr");\
	sync_morph = sync_get_track(rocket, "morph");\
	sync_blow = sync_get_track(rocket, "blow");\
	sync_blow2 = sync_get_track(rocket, "blow2");\
	sync_vatkain1 = sync_get_track(rocket, "vatkain1");\
	sync_vatkain2 = sync_get_track(rocket, "vatkain2");\
	sync_vatkain3 = sync_get_track(rocket, "vatkain3");\
	sync_vatkain4 = sync_get_track(rocket, "vatkain4");\
	sync_frame = sync_get_track(rocket, "frame");\
	sync_textnum = sync_get_track(rocket, "text_num");\
	sync_textcnt = sync_get_track(rocket, "text_count");\
	sync_textbr = sync_get_track(rocket, "text_br");\
	sync_textxpos = sync_get_track(rocket, "text_xpos");\
	sync_textypos = sync_get_track(rocket, "text_ypos");\
	sync_textsize = sync_get_track(rocket, "text_size");\
	sync_textcenter = sync_get_track(rocket, "text_center");\
	sync_distort = sync_get_track(rocket, "distort");\
	sync_contrast = sync_get_track(rocket, "contrast");\
	sync_focus = sync_get_track(rocket, "focus");\


#define ROCKET_HOST "192.168.11.15"

// shader vertexattribpointer names
#define POSITION_ARRAY_NAME "a_position"
#define NORMAL_ARRAY_NAME "a_normal"
#define TEXCOORD_ARRAY_NAME "a_texcoord"
#define COLOR_ARRAY_NAME "a_color"
#define DATA0_ARRAY_NAME "a_data0"
#define DATA1_ARRAY_NAME "a_data1"


/////////////////////////////////////////////////////////////////////
// Android Native App Library (ANAL2.0b)
#include "anal.c"

// kludges
char errormessage[100]="you are not supposed to see this :)";
//static BOOL NEED_TO_INIT_FBOS = TRUE; // FBO reload flag

/////////////////////////////////////////////////////////////////////////////////////////
// STUFF

#include "font.c"
Font *font;

//#define PSIZE 0.015
//#define PWRITE

#ifdef PWRITE
#include "obj2part.c"
#include "text1.inc"
#include "text2.inc"
#include "text3.inc"
#include "nasselod.inc"
#else
#include "particles1.inc"
#include "particles2.inc"
#include "particles3.inc"
#include "particles_nasse.inc"
#endif

//Mesh *m_sphere;
//Mesh *m_cube;
Mesh *m_part_text1;
Mesh *m_part_text2;
Mesh *m_part_muhmu;
Mesh *m_part_vatkain;

Mesh *m_part_nasse;

#include "villelod.inc"
#include "logos.inc"
#include "breakmesh.c"
Mesh *m_broken;
Mesh *m_flat;
//Mesh *m_flatlogo;
Mesh *m_brokenlogo;

#include "kewlmation.c"
Kewlmation *vid;

// textures
int t_pallo;
int t_pallo2;
int t_pallo3;
int t_back1;
int t_back2;
int t_noise;
int t_back3;
int t_back4;
int t_back5;
int t_back6;
int t_vignette;

// shaders
int s_basic;
//int s_minif16;
//int s_glowcombine;
//int s_blur;
int s_particle_basic;
int s_particle_morph;
int s_particle_muhmu;
int s_particle_muhmu2;
int s_overlay;
int s_overlay2;
int s_ssao;
int s_smartblur;
int s_blowsh;
int s_blowdepth;
int s_particle_vatkain;
//int s_depthenv;
//int s_marcher;
int s_particle_nasse;
int s_vid;
//int s_vid2;
//int s_viddepth;
//int s_blowflat;
int s_blowsh2;
int s_blowdepth2;
int s_minif_dof;
int s_dof;


// fbos
//Fbo *f_glow1;
//Fbo *f_glow2;
//Fbo *f_glow3;
//Fbo *f_glow4;
Fbo *f_depth;
Fbo *f_shadow;
Fbo *f_fx;
Fbo *f_fx2;

Fbo *f_full;
Fbo *f_half;
Fbo *f_quarter;
Fbo *f_eighth;


/////////////////////////////////////////////////////////////////////////////////////////
// INIT

void load_shaders() {
	s_basic = loadshader("basic.vs", "basic.fs");
	//s_minif16 = loadshader("minif16.vs", "minif16.fs");
	//s_glowcombine = loadshader("glowcombine.vs", "glowcombine.fs");
	//s_blur = loadshader("blur.vs", "blur.fs");
	s_particle_basic = loadshader("particle_basic.vs", "particle_basic.fs");
	s_particle_morph = loadshader("particle_morph.vs", "particle_morph.fs");
	s_particle_muhmu = loadshader("particle_muhmu.vs", "particle_muhmu.fs");
	s_particle_muhmu2 = loadshader("particle_muhmu2.vs", "particle_muhmu2.fs");
	s_overlay = loadshader("overlay.vs", "overlay.fs");
	s_overlay2 = loadshader("overlay2.vs", "overlay2.fs");
	s_ssao = loadshader("ssao.vs", "ssao.fs");
	s_smartblur = loadshader("smartblur.vs", "smartblur.fs");
	s_blowsh = loadshader("blowsh.vs", "blowsh.fs");
	s_blowdepth = loadshader("blowdepth.vs", "blowdepth.fs");
	s_particle_vatkain = loadshader("particle_vatkain.vs", "particle_vatkain.fs");
	//s_depthenv = loadshader("depthenv.vs", "depthenv.fs");
	//s_marcher = loadshader("marcher.vs", "marcher.fs");
	s_particle_nasse = loadshader("particle_nasse.vs", "particle_nasse.fs");
	s_vid = loadshader("vid.vs", "vid.fs");
	//s_vid2 = loadshader("vid2.vs", "vid2.fs");
	//s_viddepth = loadshader("viddepth.vs", "viddepth.fs");
	s_blowsh2 = loadshader("blowsh2.vs", "blowsh2.fs");
	//s_blowflat = loadshader("blowflat.vs", "blowflat.fs");
	s_blowdepth2 = loadshader("blowdepth2.vs", "blowdepth2.fs");
    s_minif_dof = loadshader("minif_dof.vs", "minif_dof.fs");
    s_dof = loadshader("dof.vs", "dof.fs");

}

void load_textures() {
	font = loadfont("font_c.png", "font_a.png", font_index);
	t_pallo = loadtexture("pallo.png", "pallo2.png");
	t_pallo2 = loadtexture("pallo4.png", 0);
	t_pallo3 = loadtexture("pallo3_c.png", "pallo3_a.png");
	t_back1 = loadtexture("background1.png", 0);
	t_back2 = loadtexture("background2.png", 0);
	t_noise = loadtexture("noise.png", 0);
	t_back3 = loadtexture("background3.png", 0);
	t_back4 = loadtexture("background4.png", 0);
	t_back5 = loadtexture("background5.png", 0);
	t_back6 = loadtexture("background6.png", 0);
	t_vignette = loadtexture("vignette.png", 0);
}


#define MUHMUCNT 512

void precalc_muhmu_particles() {
	int x;
	float *pos = malloc(sizeof(float)*MUHMUCNT*3);
	
	for (x=0; x<MUHMUCNT; x++) {
		float dist = 10.0;
		pos[x*3+0] = ranf() * dist;
		pos[x*3+1] = ranf() * dist;
		pos[x*3+2] = ranf() * dist;
	}
	m_part_muhmu = loadparticles(pos, 0, MUHMUCNT, 0.0);
}


#define VATKAINCNT 25*25*25

void precalc_vatkain_particles() {
	int x, y, z, i=0;
	float *pos = malloc(sizeof(float)*VATKAINCNT*3);
	
	for (z=0; z<25; z++) for (y=0; y<25; y++) for (x=0; x<25; x++) {
		pos[i++] = (float)x-12.5f;
		pos[i++] = (float)y-12.5f;
		pos[i++] = (float)z-12.5f;
	}
	m_part_vatkain = loadparticles(pos, 0, VATKAINCNT, 0.0);
}





void load_meshes() {
	//m_sphere = sphere(32, 32, 1);
	//m_cube = cube(1.0);
	//load_kewlers();

	//obj2part(char *name, float *src_verts, float *src_norms, unsigned int vcount, unsigned int fcount, unsigned short *src_indices, 
	//float amount, int override_numperpoly, float **vert, float **norm, int *cnt, float normalmove, float scale, float psize)
#ifdef PWRITE
	float *particles1, *particles2, *particles3;
	int particles1_count, particles2_count, particles3_count;
	obj2part("particles1", text1_vertices, 0, text1_vc, text1_fc, text1_indices, 400.0, 0, &particles1, 0, &particles1_count, 0.0, 1.0, 0.015);
	obj2part("particles2", text2_vertices, 0, text2_vc, text2_fc, text2_indices, 400.0, 0, &particles2, 0, &particles2_count, 0.0, 1.0, 0.015);
	obj2part("particles3", text3_vertices, 0, text3_vc, text3_fc, text3_indices, 400.0, 0, &particles3, 0, &particles3_count, 0.0, 1.0, 0.015);

	float *particles_nasse;
	int particles_nasse_count;
	obj2part("particles_nasse", nasselod_vertices, 0, nasselod_vc, nasselod_fc, nasselod_indices, 5.0, 0, &particles_nasse, 0, &particles_nasse_count, 0.0, 1.0, 0.33);
#endif

	//m_part_kewlers = loadparticles(particles1, particles2, particles1_count, 0.0);
	m_part_text1 = loadparticles(particles1, particles2, particles1_count, 0.0);
	m_part_text2 = loadparticles(particles2, particles3, particles2_count, 0.0);
	m_part_nasse = loadparticles(particles_nasse, 0, particles_nasse_count, 0.0);
#ifdef PWRITE
	free(particles1); 
	free(particles2);
	free(particles_nasse);
#endif

	precalc_muhmu_particles();
	precalc_vatkain_particles();

	m_broken = breakmesh(villelod_vertices, 0, villelod_indices, villelod_vc, villelod_fc, 2.0);
	m_flat = flatmesh(villelod_vertices, villelod_indices, villelod_vc, villelod_fc);

	m_brokenlogo = breakmesh(logos_vertices, logos_normals, logos_indices, logos_vc, logos_fc, 0.05);
	//m_flatlogo = flatmesh(logos_vertices, logos_indices, logos_vc, logos_fc);
	//load_logos();


}


// load FBOs if surface was recreated
void load_fbos(int xres, int yres) {
	/*f_glow1 = framebuffer(xres, yres);
	f_glow2 = framebuffer(xres/4, yres/4);
	f_glow3 = framebuffer(xres/16, yres/16);
	f_glow4 = framebuffer(xres/16, yres/16);*/
	f_fx = framebuffer(xres, yres);
	f_fx2 = framebuffer(xres, yres);
	f_depth = framebuffer_depthtex(xres, yres);
	f_shadow = framebuffer_depthtex(1024, 1024);

	f_full = framebuffer(xres, yres);
	f_half = framebuffer(xres/2, yres/2);
	f_quarter = framebuffer(xres/4, yres/4);
	f_eighth = framebuffer(xres/8, yres/8);

}



static unsigned char texts[50][32];


// load all assets here, except FBOs
void init() {
	load_meshes();
 	//precalc_sphere_particles();
	load_textures();
	load_shaders();

	vid = loadKewlmation("jazz.dat");

	sprintf(texts[0], "kewlers");
	sprintf(texts[1], "invite");
	sprintf(texts[2], "programming");
	sprintf(texts[3], "curly brace");
	sprintf(texts[4], "nvscene");
	sprintf(texts[5], "2014");
	sprintf(texts[6], "san jose");
	sprintf(texts[7], "california");
	sprintf(texts[8], "march 25-27");
	sprintf(texts[9], "2014");
	sprintf(texts[10], "dead roman");
	sprintf(texts[11], "cncd");
	sprintf(texts[12], "rgba");
	sprintf(texts[13], "fairlight");
	sprintf(texts[14], "vrtx");
	sprintf(texts[15], "satori");
	sprintf(texts[16], "farbrausch");
	sprintf(texts[17], "brainstorm");
	sprintf(texts[18], "elude");
	sprintf(texts[19], "outracks");
	sprintf(texts[20], "madwizards");
	sprintf(texts[21], "traction");
	sprintf(texts[22], "spaceballs");
	sprintf(texts[23], "hbc");
	sprintf(texts[24], "dekadence");
	sprintf(texts[25], "adapt");
	sprintf(texts[26], "excess");
	sprintf(texts[27], "komplex");
	sprintf(texts[28], "flo");
	sprintf(texts[29], "jamm");
	sprintf(texts[30], "mcenery");
	sprintf(texts[31], "convention");
	sprintf(texts[32], "center");
	sprintf(texts[33], "pc demo");
	sprintf(texts[34], "android demo");
	sprintf(texts[35], "4k exe gfx");
	sprintf(texts[36], "and more");
	sprintf(texts[37], "free food");
	sprintf(texts[38], "and drinks");
	sprintf(texts[39], "free entry to");
	sprintf(texts[40], "gtc exhibition");
	sprintf(texts[41], "greetings to");
	sprintf(texts[42], "music");
	sprintf(texts[43], "little bitchard");
	sprintf(texts[44], "support");
	sprintf(texts[45], "gloom");
	sprintf(texts[46], "support");
	sprintf(texts[47], "tron jeremy");




}


/////////////////////////////////////////////////////////////////////////////////////////
// FILTERS

/*
void minification16(Fbo *src) {
	float psize[] = {1.0/src->xres, 1.0/src->yres};

	renderflags(NOCULL | NODEPTH | NOBLEND);
	bindshader(s_minif16);
	bindtexture("t_color", src->texnum, 0); 
	texflags(LINEAR);
	uniform2fv("psize", psize);
	poly2d();
}


void blur(Fbo *f1, Fbo *f2) {
	float xdir[] = {1.0/(float)f1->xres, 0.0};
	float ydir[] = {0.0, 1.0/(float)f2->yres};

	ydir[1] *= 0.25;

	renderflags(NOCULL | NODEPTH | NOBLEND);

	bindfbo(f2);
	clear(black);
	bindshader(s_blur);
	bindtexture("t_color", f1->texnum, 0); 
	texflags(LINEAR);
	uniform2fv("dir", xdir);
	poly2d();

	bindfbo(f1);
	clear(black);
	bindshader(s_blur);
	bindtexture("t_color", f2->texnum, 0); 
	texflags(LINEAR);
	uniform2fv("dir", ydir);
	poly2d();

	bindfbo(0);
}


void glowcombine(int origtex, int blurtex, float fxbr, float glowbr, float glowdim) {
	bindshader(s_glowcombine);
	bindtexture("t_orig", origtex, 0);
	texflags(NEAREST);
	bindtexture("t_blur", blurtex, 1);
	texflags(LINEAR);
	uniform1f("fxbr", fxbr);
	uniform1f("glowbr", glowbr);
	uniform1f("glowdim", glowdim);
	//uniform2fv("contrast", contrast);
	//uniform3fv("biits", biits);
	//bindtexture("t_leiska", t_overlay[SYNCi(sync_overlaynum, row)], 2);
	//texflags(LINEAR);
	//uniform1f("leiskabr", SYNC(sync_overlaybr, row));
	poly2d();
}


void glowfilter(double row) {
	bindfbo(f_glow2);
	clear(black);
	minification16(f_glow1);
	bindfbo(f_glow3);
	clear(black);
	minification16(f_glow2);
	blur(f_glow3, f_glow4);
	bindfbo(0);
	renderflags(NOCULL | NODEPTH | NOBLEND);
	glowcombine(f_glow1->texnum, f_glow3->texnum, SYNC(sync_fxbr, row), SYNC(sync_glowbr, row), SYNC(sync_glowdim, row));
}
*/


void minification_dof(Fbo *src) {
	float psize[] = {1.0/src->xres, 1.0/src->yres};

	renderflags(NOCULL | NODEPTH | NOBLEND);
	bindshader(s_minif_dof);
	bindtexture("t_color", src->texnum, 0); 
	texflags(LINEAR);
	uniform2fv("psize", psize);
	poly2d();
}

void doffilter(Fbo *target, Fbo *src1, Fbo *src2, Fbo *src3, Fbo *src4/*, float bork*/) {

	renderflags(NOCULL | NODEPTH | NOBLEND);

	bindfbo(src2);
	minification_dof(src1);
	bindfbo(src3);
	minification_dof(src2);
	bindfbo(src4);
	minification_dof(src3);
	
	bindfbo(target);

	bindshader(s_dof);
	bindtexture("t_tex1", src1->texnum, 0);
	texflags(LINEAR | CLAMP);
	//texflags(NEAREST | CLAMP);
	bindtexture("t_tex2", src2->texnum, 1);
	texflags(LINEAR | CLAMP);
	//texflags(NEAREST | CLAMP);
	bindtexture("t_tex3", src3->texnum, 2);
	texflags(LINEAR | CLAMP);
	//texflags(NEAREST | CLAMP);
	bindtexture("t_tex4", src4->texnum, 3);
	texflags(LINEAR | CLAMP);
	//texflags(NEAREST | CLAMP);

	//uniform1f("bork", bork);

	poly2d();
}



void overlay(int tnum, float br, int tflags, int flags) {

	renderflags(flags);
	bindshader(s_overlay);
	bindtexture("t_color", tnum, 0);
	texflags(CLAMP | tflags);
	uniform1f("br", br); 
	poly2dflip();
}


void ssaofilter(int tnum, int dtnum, float znear, float zfar, float rad, float br) {
	float t = ranf();

	clear(black);
	renderflags(NOCULL | NODEPTH | NOBLEND);
	bindshader(s_ssao);
	bindtexture("t_color", tnum, 0);
	bindtexture("t_depth", dtnum, 1);
	uniform1f("znear", znear);
	uniform1f("zfar", zfar);
	uniform1f("rad", rad * 1.3333);	
	uniform1f("time", t);	
	float texel[] = {1.0 / (float)anal_xres, 1.0 / (float)anal_yres};
	uniform1f("u_br", br);
	uniform2fv("texelsize", texel);
	poly2d();

}

void smartblur(Fbo *f) {
	float texel[] = {1.0/(float)f->xres, 1.0/(float)f->yres};

	renderflags(NOCULL | NODEPTH | NOBLEND);
	clear(black);
	bindshader(s_smartblur);
	bindtexture("t_color", f->texnum, 0); 
	uniform2fv("texel", texel);
	poly2d();
}


void noiselayer(float br, float contrast, float distort) {
	float s = 2.0;

	renderflags(NOCULL | NODEPTH | NOBLEND);
	bindshader(s_overlay2);
	bindtexture("t_color", t_vignette, 0);
	texflags(CLAMP);
	bindtexture("t_color2", t_noise, 1);
	texflags(WRAP);
	bindtexture("t_buf", f_fx2->texnum, 2);

	uniform1f("br", 0.05*br); 
	uniform1f("contrast", contrast);
	uniform1f("distort", distort);

	float xpos = ranf();
	float ypos = ranf();
	static float vertices[16] = { -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f };
	static float data[16];
	static float texcoords[] = { 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };	
	int poshandle, texhandle, datahandle;

	 data[0] = (0.0f+xpos)*s; data[1] = (0.0f+ypos)*s;
	 data[2] = (1.0f*0.5+xpos)*s; data[3] = (0.56f*0.5+ypos)*s;
	 data[4] = (0.0f+xpos)*s; data[5] = (0.56f*0.5+ypos)*s;
	 data[6] = (0.0f+xpos)*s; data[7] = (0.0f+ypos)*s;
	 data[8] = (1.0f*0.5+xpos)*s; data[9] = (0.0f+ypos)*s;
	 data[10] = (1.0f*0.5+xpos)*s; data[11] = (0.56f*0.5+ypos)*s;

	poshandle = glGetAttribLocation(currentshader, POSITION_ARRAY_NAME);
    glVertexAttribPointer(poshandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(poshandle);
	datahandle = glGetAttribLocation(currentshader, DATA0_ARRAY_NAME);
	glVertexAttribPointer(datahandle, 2, GL_FLOAT, GL_FALSE, 0, data);     
    glEnableVertexAttribArray(datahandle);
	texhandle = glGetAttribLocation(currentshader, TEXCOORD_ARRAY_NAME);
	glVertexAttribPointer(texhandle, 2, GL_FLOAT, GL_FALSE, 0, texcoords);     
    glEnableVertexAttribArray(texhandle);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

/*
void depthenvfilter(int dtnum, float znear, float zfar) {

	renderflags(NOCULL | NODEPTH | NOBLEND);
	bindshader(s_depthenv);
	bindtexture("t_depth", dtnum, 0);
	uniform1f("znear", znear);
	uniform1f("zfar", zfar);
	float texel[] = {1.0 / (float)anal_xres, 1.0 / (float)anal_yres};
	uniform2fv("texelsize", texel);
	poly2d();

}
*/

/////////////////////////////////////////////////////////////////////////////////////////
// EFFECTS



void draw_textpart(float *mat, float *cmat, float morph, float time, int textnum) {
	float up[3], right[3];

	bindshader(s_particle_morph);
	up[0] = cmat[1]; up[1] = cmat[5]; up[2] = cmat[9];
	right[0] = cmat[0]; right[1] = cmat[4];	right[2] = cmat[8];
	bindtexture("t_color", t_pallo3, 0);
	uniformmatrix4fv("mat", mat);
	uniform3fv("up", up);
	uniform3fv("right", right);
	uniform1f("size", 0.015);
	uniform1f("morph", morph);
	uniform1f("time", time);
	renderflags(NOCULL | NOBLEND | DEPTH);
	if (textnum == 0) drawparticles(m_part_text1, rocketcamerapos, rocketcameratgt, 0);
	else drawparticles(m_part_text2, rocketcamerapos, rocketcameratgt, 0);
}

void draw_muhmu(float *mat, float *cmat, int blend, float size, BOOL movecam, float br) {
	float up[3], right[3];

	bindshader(s_particle_muhmu);
	up[0] = cmat[1]; up[1] = cmat[5]; up[2] = cmat[9];
	right[0] = cmat[0]; right[1] = cmat[4];	right[2] = cmat[8];
	bindtexture("t_color", t_pallo2, 0);
	uniformmatrix4fv("mat", mat);
	uniform3fv("up", up);
	uniform3fv("right", right);
	uniform1f("size", size*1.333);
	float brz[]={br, br, br, 0.0};
	uniform4fv("br", brz);
	if (movecam) uniform3fv("campos", rocketcamerapos);
	else {
		float c[3]={0.0, 0.0, 0.0};
		uniform3fv("campos", c);
	}
	renderflags(NOCULL | blend | CHECKDEPTH);
	drawparticles(m_part_muhmu, rocketcamerapos, rocketcameratgt, 0);
}

void draw_muhmu2(float *mat, float *cmat, int blend, float size, float br, float row) {
	float up[3], right[3];

	bindshader(s_particle_muhmu2);
	up[0] = cmat[1]; up[1] = cmat[5]; up[2] = cmat[9];
	right[0] = cmat[0]; right[1] = cmat[4];	right[2] = cmat[8];
	bindtexture("t_color", t_pallo2, 0);
	uniformmatrix4fv("mat", mat);
	uniform3fv("up", up);
	uniform3fv("right", right);
	uniform1f("size", size*1.333);
	float brz[]={br, br, br, 0.0};
	uniform4fv("br", brz);
	uniform1f("time", row);
	uniform3fv("campos", rocketcamerapos);
	renderflags(NOCULL | blend | CHECKDEPTH);
	drawparticles(m_part_muhmu, rocketcamerapos, rocketcameratgt, 0);
}


void draw_vatkain(float *mat, float *cmat, float time, float *params) {
	float up[3], right[3];

	bindshader(s_particle_vatkain);
	up[0] = cmat[1]; up[1] = cmat[5]; up[2] = cmat[9];
	right[0] = cmat[0]; right[1] = cmat[4];	right[2] = cmat[8];
	bindtexture("t_color", t_pallo, 0);
	uniformmatrix4fv("mat", mat);
	uniform3fv("up", up);
	uniform3fv("right", right);
	uniform1f("size", 0.35);
	uniform1f("time", time);
	uniform4fv("params", params);
	renderflags(NOCULL | NOBLEND | DEPTH);
	drawparticles(m_part_vatkain, rocketcamerapos, rocketcameratgt, 0);
}



void logofx(double row) {
	//float mat[16], prmat[16], cmat[16], mvmat[16], nmat[9], omat[16];
	float mat[16], prmat[16], cmat[16], mvmat[16];
	//float znear = 0.1, zfar = 30.0;
	float br = SYNC(sync_fxbr, row);

	bindfbo(f_depth);
	
	clear(black);
	overlay(t_back1, br, 0, NOCULL | NODEPTH | NOBLEND);

	rocketcamera(prmat, cmat, row);
	memcpy(mvmat, cmat, sizeof(float)*16);
	multmatrix(mat, prmat, mvmat); // modelviewprojection matrix 
	draw_textpart(mat, cmat, SYNC(sync_morph, row), row/128.0, SYNCi(sync_vatkain1, row));
	draw_muhmu(mat, cmat, BLEND, 0.1, TRUE, 0.07);

	bindfbo(f_fx);
	ssaofilter(f_depth->texnum, f_depth->dtexnum, rocketcameraznear, rocketcamerazfar, 0.1, br);
	bindfbo(f_fx2);
	smartblur(f_fx);

}

static float lightpos[3] = {400.0, 400.0, 500.0};

void render_shadow(float *dst, float blow, float blow2, double row) {
	float mat[16], prmat[16], cmat[16];
	float znear = 50.0, zfar = 1000.0;
	//float campos[]={0.0, 600.0, 400.0};
	float camtgt[]={0.0, 0.0, 50.0};
	float yvec[]={0.0, 1.0, 0.0};
	float s = 250.0;

	bindfbo(f_shadow);
	clear(black);

	identity(cmat);
	lookat(cmat, lightpos, camtgt, yvec);
	ortho(prmat, -s, s, -s, s, znear, zfar);
	multmatrix(mat, prmat, cmat);
	memcpy(dst, mat, sizeof(float)*16);

	bindshader(s_blowdepth);
	uniformmatrix4fv("mat", mat);
	uniform1f("blow", blow);
	uniform1f("blow2", blow2);
	renderflags(DEPTH | INVCULL | NOBLEND);
	if (blow < 0.00001) drawmesh(m_flat);
	else drawmesh(m_broken);
}


void xploder(double row) {
	float mat[16], prmat[16], cmat[16], nmat[16], mvmat[16];
	float smat[16];
	//float znear = 5.0, zfar = 1000.0;
	float blow = SYNC(sync_blow, row);
	float blow2 = SYNC(sync_blow2, row);
	float br = SYNC(sync_fxbr, row);
	//bindfbo(f_depth);

	lightpos[0] = SYNC(sync_vatkain1, row);

	render_shadow(smat, blow, blow2, row);

	//bindfbo(f_fx2);
	bindfbo(f_full);

	clear(black);
	overlay(t_back2, br, 0, NOCULL | NODEPTH | NOBLEND);
	rocketcamera(prmat, cmat, row);
	normalmatrix(nmat, cmat);
	multmatrix(mat, prmat, cmat);

	renderflags(CULL | DEPTH | NOBLEND);
	bindshader(s_blowsh);
	uniformmatrix4fv("mat", mat);
	uniformmatrix3fv("nmat", nmat);
	uniformmatrix4fv("smat", smat);
	uniform1f("blow", blow);
	uniform1f("blow2", blow2);
	uniform1f("focus", SYNC(sync_focus, row));
	float ldir[3];
	vcopy(ldir, lightpos);
	normalize(ldir);
	uniform3fv("lightdir", ldir);
	uniform1f("br", br);
	bindtexture("t_shadow", f_shadow->dtexnum, 0);

	if (blow < 0.00001) drawmesh(m_flat);
	else drawmesh(m_broken);

	memcpy(mvmat, cmat, sizeof(float)*16);
	scalef(mvmat, 40.0, 40.0, 40.0);
	multmatrix(mat, prmat, mvmat);
	draw_muhmu(mat, cmat, MINUSBLEND, 0.05, FALSE, 0.666);

	doffilter(f_fx2, f_full, f_half, f_quarter, f_eighth);//, SYNC(sync_bork, row));

	//overlay(f_shadow->texnum, 1.0, 0, NOCULL | NODEPTH | NOBLEND);
}



void vatkainfx(double row) {
	float mat[16], prmat[16], cmat[16], mvmat[16];
	//float znear = 0.5, zfar = 120.0;
	float br = SYNC(sync_fxbr, row);

	bindfbo(f_depth);
	
	clear(black);
	overlay(t_back3, 1.0, 0, NOCULL | NODEPTH | NOBLEND);

	rocketcamera(prmat, cmat, row);
	memcpy(mvmat, cmat, sizeof(float)*16);
	multmatrix(mat, prmat, mvmat); // modelviewprojection matrix 
	float params[4];
	SYNC4(params, sync_vatkain1, sync_vatkain2, sync_vatkain3, sync_vatkain4, row);
	draw_vatkain(mat, cmat, row/64.0, params);

//	bindfbo(0);
//	depthenvfilter(f_depth->dtexnum, znear, zfar);

	bindfbo(f_fx);
	ssaofilter(f_depth->texnum, f_depth->dtexnum, rocketcameraznear, rocketcamerazfar, 1.0, br);
	bindfbo(f_fx2);
	smartblur(f_fx);

}


/*
void marcher(double row) {
	float x0, x1, y0, y1;
	float cmat[16], prmat[16];

	clear(black);
	renderflags(NOCULL | NODEPTH | NOBLEND);
	rocketcamera(prmat, cmat, 0.1, 10.0, row);
	bindshader(s_marcher);
	uniformmatrix4fv("mat", cmat);
	float params[3];
	SYNC3(params, sync_vatkain1, sync_vatkain2, sync_vatkain3, row);
	uniform3fv("params", params);	

	float xsize = 0.5;
	float ysize = xsize * anal_aspect;
	x0 = -xsize;
	x1 = xsize;
	y0 = -ysize;
	y1 = ysize;
	float vertices[16] = { x0, y0, x1, y1, x0, y1, x0, y0, x1, y0, x1, y1 };
	static float texcoords[] = { -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f };
	int poshandle, texhandle;
	poshandle = glGetAttribLocation(currentshader, POSITION_ARRAY_NAME);
    glVertexAttribPointer(poshandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(poshandle);
	texhandle = glGetAttribLocation(currentshader, TEXCOORD_ARRAY_NAME);
	glVertexAttribPointer(texhandle, 2, GL_FLOAT, GL_FALSE, 0, texcoords);     
    glEnableVertexAttribArray(texhandle);
    glDrawArrays(GL_TRIANGLES, 0, 6);    
}
*/


void draw_nasse(float *mat, float *cmat, float blow, float *params) {
	float up[3], right[3];

	bindshader(s_particle_nasse);
	up[0] = cmat[1]; up[1] = cmat[5]; up[2] = cmat[9];
	right[0] = cmat[0]; right[1] = cmat[4];	right[2] = cmat[8];
	bindtexture("t_color", t_pallo3, 0);
	uniformmatrix4fv("mat", mat);
	uniform3fv("up", up);
	uniform3fv("right", right);
	uniform1f("size", 0.15);
	uniform1f("blow", blow);
	uniform3fv("params", params);
	renderflags(NOCULL | NOBLEND | DEPTH);
	drawparticles(m_part_nasse, rocketcamerapos, rocketcameratgt, 0);
}

void nassefx(double row) {
	float mat[16], prmat[16], cmat[16], mvmat[16];
	//float znear = 1.0, zfar = 1024.0;
	float br = SYNC(sync_fxbr, row);


	bindfbo(f_depth);
	
	clear(black);
	overlay(t_back6, 1.0, 0, NOCULL | NODEPTH | NOBLEND);

	rocketcamera(prmat, cmat, row);
	memcpy(mvmat, cmat, sizeof(float)*16);
	multmatrix(mat, prmat, mvmat); // modelviewprojection matrix 
	float params[3];
	SYNC3(params, sync_vatkain1, sync_vatkain2, sync_vatkain3, row);
	draw_nasse(mat, cmat, SYNC(sync_blow, row), params);
	
	//memcpy(mvmat, cmat, sizeof(float)*16);
	//scalef(mvmat, 0.5, 0.5, 0.5);
	//multmatrix(mat, prmat, mvmat);
	draw_muhmu(mat, cmat, BLEND, 0.05, TRUE, 0.15);
//	bindfbo(0);
//	depthenvfilter(f_depth->dtexnum, znear, zfar);

	bindfbo(f_fx);
	ssaofilter(f_depth->texnum, f_depth->dtexnum, rocketcameraznear, rocketcamerazfar, 1.0, br);
	bindfbo(f_fx2);
	smartblur(f_fx);

}

/*

void render_vid_shadow(float *dst, int frame) {
	float mat[16], prmat[16], cmat[16];
	float znear = 30.0, zfar = 40.0;
	float lpos[]={30.0, 10.0, 0.0};
	float ltgt[]={0.0, 0.0, 0.0};
	float yvec[]={0.0, 1.0, 0.0};
	float sx = 1.1;
	float sy = 0.4;

	bindfbo(f_shadow);
	clear(black);

	identity(cmat);
	lookat(cmat, lpos, ltgt, yvec);
	ortho(prmat, -sx, sx, -sy, sy, znear, zfar);
	multmatrix(mat, prmat, cmat);
	memcpy(dst, mat, sizeof(float)*16);

	bindshader(s_viddepth);
	uniformmatrix4fv("mat", mat);
	renderflags(DEPTH | INVCULL | NOBLEND);

	renderFrame(vid, frame, TRUE);
	//renderFrame(vid, frame+1, TRUE);
	//renderFrame(vid, frame+2, TRUE);	

	bindfbo(0);
}

*/

void vidfx(double row) {
	float mat[16], prmat[16], cmat[16], mvmat[16], smat[16];
	int frame1 = (int)floor(SYNC(sync_frame, row));
	int frame2 = (int)floor(SYNC(sync_frame, row+4.0));
	int frame3 = (int)floor(SYNC(sync_frame, row+8.0));
/*	int frame4 = (int)floor(SYNC(sync_frame, row)+1.0);
	int frame5 = (int)floor(SYNC(sync_frame, row)+1.3333);*/
	float br = SYNC(sync_fxbr, row);
	//float f1 = smth2(fmodf(SYNC(sync_frame, row), 1.0));
	//float f2 = smth2(fmodf(SYNC(sync_frame, row+10.0)+1.0, 1.0));
	//float f3 = smth2(fmodf(SYNC(sync_frame, row+20.0)+2.0, 1.0));

	//render_vid_shadow(smat, frame1);

	bindfbo(f_depth);

	clear(black);
	overlay(t_back4, br, 0, NOCULL | NODEPTH | NOBLEND);


	rocketcamera(prmat, cmat, row);
	memcpy(mvmat, cmat, sizeof(float)*16);
	multmatrix(mat, prmat, mvmat); // modelviewprojection matrix 

	renderflags(NOCULL | DEPTH | NOBLEND);
	bindshader(s_vid);
	uniformmatrix4fv("mat", mat);
	uniform1f("br", br);
	//uniformmatrix4fv("smat", smat);
	//bindtexture("t_shadow", f_shadow->dtexnum, 0);

	renderFrame(vid, frame1, FALSE);
	renderFrame(vid, frame2, FALSE);
	renderFrame(vid, frame3, FALSE);
	//renderFrame(vid, frame1+3, FALSE);
	//renderFrame(vid, frame1+4, FALSE);

	memcpy(mvmat, cmat, sizeof(float)*16);
	scalef(mvmat, 0.25, 0.25, 0.25);
	multmatrix(mat, prmat, mvmat);
	draw_muhmu2(mat, cmat, BLEND, 0.05, 0.15, row/64.0);

/*
	renderflags(NOCULL | CHECKDEPTH | BLEND);
	uniform1f("br", br*0.1);
	renderFrame(vid, frame2, FALSE);
	renderFrame(vid, frame3, FALSE);
	renderFrame(vid, frame4, FALSE);
	renderFrame(vid, frame5, FALSE);
*/
	//draw_muhmu(mat, cmat);


	bindfbo(f_fx);
	ssaofilter(f_depth->texnum, f_depth->dtexnum, rocketcameraznear, rocketcamerazfar, 0.01, br);
	bindfbo(f_fx2);
	smartblur(f_fx);

	//ßoverlay(f_shadow->texnum, 1.0, 0, NOCULL | NODEPTH | NOBLEND);
}


/*
void vidfx2(double row) {
	float mat[16], prmat[16], cmat[16], mvmat[16];
	int frame1 = (int)floor(SYNC(sync_frame, row));
	float br = SYNC(sync_fxbr, row);
	int i;

	bindfbo(f_depth);

	clear(black);
//	overlay(t_back4, br, 0, NOCULL | NODEPTH | NOBLEND);

	rocketcamera(prmat, cmat, row);
	memcpy(mvmat, cmat, sizeof(float)*16);
	multmatrix(mat, prmat, mvmat); // modelviewprojection matrix 

	renderflags(NOCULL | DEPTH | NOBLEND);
	bindshader(s_vid2);
	uniformmatrix4fv("mat", mat);
	uniform1f("br", br);
	//uniformmatrix4fv("smat", smat);
	//bindtexture("t_shadow", f_shadow->dtexnum, 0);

	for (i=0; i<16; i++) {
		renderFrame2(vid, frame1+i, (float)i*0.02-0.1);
	}

	bindfbo(f_fx);
	clear(black);
	ssaofilter(f_depth->texnum, f_depth->dtexnum, rocketcameraznear, rocketcamerazfar, 0.1, br);
	bindfbo(0);
	smartblur(f_fx);
}*/



static float logolpos[] = {30, 40, 20};

void render_shadow2(float *dst, float blow, float *blowpos, double row) {
	float mat[16], prmat[16], cmat[16];
	float znear = 20.0, zfar = 70.0;
	float camtgt[]={0.0, 0.0, 1.0};
	float yvec[]={0.0, 1.0, 0.0};
	float s = 2.5;

	bindfbo(f_shadow);
	clear(black);

	identity(cmat);
	lookat(cmat, logolpos, camtgt, yvec);
	ortho(prmat, -s, s, -s, s, znear, zfar);
	multmatrix(mat, prmat, cmat);
	memcpy(dst, mat, sizeof(float)*16);

	bindshader(s_blowdepth2);
	uniformmatrix4fv("mat", mat);
	uniform1f("blow", blow);
	uniform3fv("blowpos", blowpos);
	renderflags(DEPTH | INVCULL | NOBLEND);
	drawmesh(m_brokenlogo);

}



void logobreaker(double row) {
	float mat[16], prmat[16], cmat[16], nmat[16], mvmat[16];
	float smat[16];
	float blow = SYNC(sync_blow, row);
	//float blow2 = SYNC(sync_blow2, row);
	float br = SYNC(sync_fxbr, row);
	float blowpos[3];
	SYNC3(blowpos, sync_vatkain1, sync_vatkain2, sync_vatkain3, row);

	render_shadow2(smat, blow, blowpos, row);

	//bindfbo(f_fx2);
	bindfbo(f_full);

	clear(black);
	overlay(t_back5, br, 0, NOCULL | NODEPTH | NOBLEND);
	rocketcamera(prmat, cmat, row);
	normalmatrix(nmat, cmat);
	multmatrix(mat, prmat, cmat);

	renderflags(CULL | DEPTH | NOBLEND);

	bindshader(s_blowsh2);
	uniformmatrix4fv("mat", mat);
	uniformmatrix3fv("nmat", nmat);
	uniform3fv("blowpos", blowpos);
	uniform1f("blow", blow);
	uniformmatrix4fv("smat", smat);
	uniform3fv("lightpos", logolpos);
	bindtexture("t_shadow", f_shadow->dtexnum, 0);
	uniform1f("br", br);
	drawmesh(m_brokenlogo);

	memcpy(mvmat, cmat, sizeof(float)*16);
	scalef(mvmat, blow+0.1, blow+0.1, blow+0.1);
	multmatrix(mat, prmat, mvmat);
	draw_muhmu(mat, cmat, MINUSBLEND, 0.07, FALSE, 0.5);

	doffilter(f_fx2, f_full, f_half, f_quarter, f_eighth);//, SYNC(sync_bork, row));

	//overlay(f_shadow->texnum, 1.0, 0, NOCULL | NODEPTH | NOBLEND);

}



/////////////////////////////////////////////////////////////////////////////////////////
// MAINLOOP



void step(double row) {
	int fxnum = SYNCi(sync_fxnum, row);
	float br = SYNC(sync_fxbr, row);

	if (fxnum == 0) clear(black);
	else if (fxnum == 1) logofx(row);
	else if (fxnum == 2) xploder(row);
	else if (fxnum == 3) vatkainfx(row);
	else if (fxnum == 4) nassefx(row);
	else if (fxnum == 5) vidfx(row);
	else if (fxnum == 6) logobreaker(row);

	int textnum = SYNCi(sync_textnum, row);
	float textbr = SYNC(sync_textbr, row);
	//float xpos = SYNC(sync_textxpos, row);
	//float ypos = SYNC(sync_textypos, row);
	float textpos[2];
	SYNC2(textpos, sync_textxpos, sync_textypos, row);
	float textsize = SYNC(sync_textsize, row);
	int textcount = SYNCi(sync_textcnt, row);

	//const struct sync_track *sync_glowbr;\
	//const struct sync_track *sync_glowdim;\

	int i;
	float mat[16];
	identity(mat);
	renderflags(ALPHABLEND | NOCULL | NODEPTH);
	bindshader(s_overlay);
	uniformmatrix4fv("mat", mat);
	uniform1f("br", textbr);
	//fontprint(Font *f, float* pos, float scale, float spacing, int center, char *fmt, ...) {
	for (i = 0; i < textcount; i++) {
		fontprint(font, textpos, textsize, 0.04, SYNCi(sync_textcenter, row), texts[textnum+i]);
		if (textnum+i == 1) {
			uniform1f("br", SYNC(sync_vatkain1, row));
			fontprint_kikka3(font, textpos, textsize, 0.04, SYNCi(sync_textcenter, row), texts[textnum+i]);
		}
		textpos[1] -= textsize*2.5;
	}

	bindfbo(0);
	noiselayer(br, SYNC(sync_contrast, row), SYNC(sync_distort, row));

}



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// JAVA SCHEISSE 


jboolean Java_com_kewlers_nvscene14_DEMOLib_initgl(JNIEnv * env, jobject obj, jobject assetManager) {
    int r, g, b, a, d, s;
    GLint err;
    
	if (stream) {
		LOGI("bass was open, closing now");
		close_bass();
	}
	
    LOGI("# START ######################################################");
    LOGI("init assmgr");
    
    // get assetmanager
    assmgr = AAssetManager_fromJava(env, assetManager);
    if (!assmgr) {
    	sprintf(errormessage, "Assetmanager init failed");
    	return FALSE;
    }
    
    LOGI("init BASS");
   	if (!init_bass()) {
   		sprintf(errormessage, "BASS init failed");
   		return FALSE;
   	}
   	
    LOGI("init graphics");
	initanal();
	
    printglstring("Version", GL_VERSION);
   	printglstring("Vendor", GL_VENDOR);
    printglstring("Renderer", GL_RENDERER);
    printglstring("Extensions", GL_EXTENSIONS);
	glGetIntegerv(GL_RED_BITS, &r);
	glGetIntegerv(GL_GREEN_BITS, &g);
	glGetIntegerv(GL_BLUE_BITS, &b);
	glGetIntegerv(GL_ALPHA_BITS, &a);
	glGetIntegerv(GL_DEPTH_BITS, &d);
	glGetIntegerv(GL_STENCIL_BITS, &s);
	LOGI("GL_BITS (r/g/b/a/depth/stencil): %i/%i/%i/%i/%i/%i", r, g, b, a, d, s);
#ifdef DISKWRITE
	int i;
	if (r<8 || g<8 || b<8) for (i = 0; i < 100; i++)  LOGI("WARNING: TRYING TO DO DISKWRITE WITHOUT 24BPP");
#endif

/*
	int i;
	for (i = 0; i < 50; i++) ranf();
	for (i = 0; i < 16; i++) {
		float pier[3];
		pier[0] = ranf() - 0.5;
		pier[1] = ranf() - 0.5;
		pier[2] = 0.0;
		normalize(pier);
		float len = (float)(i+1) / 16.0;
		pier[0] *= len;
		pier[1] *= len;
		LOGI("vec2(%5.2f, %5.2f)", pier[0], pier[1]);
	}
*/

#ifdef DEPTH_TEXTURE
	if (!checkext("GL_OES_depth_texture")) {
		sprintf(errormessage, "Required extension GL_OES_depth_texture not supported, sorry");
		return FALSE;
	}
#endif

	// load stuff
	LOGI("load assets");
	init();
	checkerror("init");

	LOGI("start playing");
	bass_startplaying();

	// flag for onSurfaceChanged event that FBOs need reloading\
	//NEED_TO_INIT_FBOS = TRUE;

	return TRUE;
}


static float avgfps_fps=0.0;
static float avgfps_cnt=0.0;

jboolean Java_com_kewlers_nvscene14_DEMOLib_step(JNIEnv * env, jobject obj) {
	static long prevmsec, msec;
	static int frames=0;

#ifdef DISKWRITE
	// change to 24bit surface from DEMOView.java before using this
	static int dw_frame = DISKWRITE_START;
	double row = dw_frame / DISKWRITE_FPS / 60.0 * BPM * rpb;
	LOGI("diskwrite frame %i", dw_frame);
#else
	double row = bass_get_row(stream);
#endif
	
	ONCE(
		prevmsec=getmsec();
	);
	BASS_Update(0);
	step(row);
	msec = getmsec();
#ifndef DISKWRITE
	if (msec >= (prevmsec+1000)) {
		prevmsec = msec;
		LOGI("fps: %i", frames);
		avgfps_fps+=frames;
		avgfps_cnt+=1.0;
		frames = 0;
	} else frames++;
#endif

#ifndef SYNC_PLAYER

	if (sync_update(rocket, (int)floor(row))) {
		//LOGI("sync_update (before connect) %lu ms", getmsec()-msec);
		sync_connect(rocket, ROCKET_HOST, SYNC_DEFAULT_PORT);
		//LOGI("sync_update (after connect) %lu ms", getmsec()-msec);
	} else {
		//LOGI("sync_update %lu ms", getmsec()-msec);
	}
#endif

#ifdef FINAL
	if (row >= EXIT_TIME) return FALSE;
#endif

#ifdef DISKWRITE
	checkerror("effect");
	glFlush();
	checkerror("flush");
	char filename[128];
	sprintf(filename, "/sdcard/tmp/diskwrite/kwl_%05i.bmp", dw_frame);
	writeBmp(filename, anal_xres, anal_yres);
	dw_frame++;
	checkerror("writeBmp");
	if (dw_frame >= DISKWRITE_END) return FALSE;
#endif

	return TRUE;
}

void Java_com_kewlers_nvscene14_DEMOLib_stop(JNIEnv * env, jobject obj) {
	close_bass();
	LOGI("avg fps = %5.2f", avgfps_fps/avgfps_cnt);
    LOGI("# END ########################################################");
}

void Java_com_kewlers_nvscene14_DEMOLib_pause(JNIEnv * env, jobject obj, jboolean pause) {
	if (pause) BASS_ChannelPause((HSTREAM)stream);
	else BASS_ChannelPlay((HSTREAM)stream, FALSE);
}

void Java_com_kewlers_nvscene14_DEMOLib_touchevent(JNIEnv * env, jobject obj) {
#ifndef FINAL
	load_shaders();
#endif
}

void Java_com_kewlers_nvscene14_DEMOLib_resizegl(JNIEnv * env, jobject obj, jint width, jint height) {
	resizeanal(width, height);
	load_fbos(width, height);
}

jstring *Java_com_kewlers_nvscene14_DEMOLib_getmessage(JNIEnv * env, jobject obj) {
	return (*env)->NewStringUTF(env, errormessage);
}



