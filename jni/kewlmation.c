
typedef unsigned short uint16;

#define BW


#ifdef BW
#define stride 9
#define tristride 3
#else
#define stride 12
#define tristride 4
#endif

typedef struct {
	unsigned int numframes;
	unsigned int datasize;
	unsigned int *frameinfo;
	unsigned char *frames; 
} Kewlmation;

Kewlmation *loadKewlmation(unsigned char *filename)
{
	Kewlmation *km; 
	FILE *in;
	
	km = malloc(sizeof(Kewlmation));
	Assetloader al = loadasset(filename);

	memcpy(&km->numframes, al.data, 4);
	memcpy(&km->datasize, al.data+4, 4);
	km->frameinfo = malloc(sizeof(unsigned int)*km->numframes*2);
	memcpy(km->frameinfo, al.data+8, km->numframes*8);
	km->frames = malloc(km->datasize);
	memcpy(km->frames, al.data+8+km->numframes*8, km->datasize);
	free(al.data);
	LOGI("Loaded kewlmation, frames = %i, datasize = %i", km->numframes, km->datasize);

	return km;
}

#define MAXTRIANGLES 8000

void renderFrame(Kewlmation *km, int frame, BOOL depth)
{
	frame = frame % km->numframes;
	unsigned int numTriangles = km->frameinfo[(int)frame*2+1];
	unsigned char *data = km->frames+km->frameinfo[(int)frame*2+0];
	unsigned int i, j;
	static float colors[MAXTRIANGLES*3*3];
	static float norms[MAXTRIANGLES*3*3];
	static float vertices[MAXTRIANGLES*3*3];
	int poshandle, colorhandle, normhandle;

	//LOGI("framenum %i triangles %i", frame, numTriangles);

	if (numTriangles > MAXTRIANGLES) {
		numTriangles = MAXTRIANGLES;
		LOGE("too much trianges in video");
	}

	float bulge = ((float)frame)/610.0-0.5;
	float *cpos = colors;
	float *vpos = vertices;
	float *npos = norms;

	for (i = 0; i < numTriangles; i++)
	{
		for (j = 0; j < 3; j++)
		{
#ifdef BW
			float bw = data[i*stride+j*tristride+2]/255.0;
#else
			uint16 col = data[i*stride+j*tristride+2]*256 + data[i*stride+j*tristride+3];
			float r, g, b;
			r = (float)(col>>11)/31.0;
			g = (float)((col>>5)&63)/63.0; 
			b = (float)(col&31)/31.0;
#endif
			*vpos++ = (float)(data[i*stride+j*tristride+0]/255.0)*2.0-1.0;
			*vpos++ = bw * 0.2f;
			*vpos++ = (float)(data[i*stride+j*tristride+1]/255.0)*2.0-1.0;
/*
			float v1 = (float)(data[i*stride+j*tristride+0]/255.0);
			float v2 = (float)(data[i*stride+j*tristride+1]/255.0);

			//float d = (r+g+b) * 0.005+0.025;
			float d = bw * 0.015+0.025;
			float a = v1*pi*2.0;
			float x, y, z;
			x = cos(a) * d;
			y = v2-0.5;
			z = sin(a) * d;
			float dir[3] = {x, y-bulge, z};
			float dist = 0.01 / sqrt(x * x + dir[1] * dir[1] + z * z);
			normalize(dir);
			if (y > bulge) y = bulge;
			*vpos++ = x * 3.0 + dir[0] * dist;
			*vpos++ = y + dir[1] * dist;
			*vpos++ = z * 3.0 + dir[2] * dist;
*/
			//float br = dist * 4.0 + bw * 0.5;
			if (!depth) 
			{
				*cpos++ = bw;
				*cpos++ = bw;
				*cpos++ = bw;
			}

		}
		if (!depth) 
		{
			float norm[3];
			calc_fnorm(vpos-9, vpos-6, vpos-3, norm);
			for (j = 0; j < 3; j++)
			{
				*npos++ = norm[0];
				*npos++ = norm[1];
				*npos++ = norm[2];
			}
		}

	}

	poshandle = glGetAttribLocation(currentshader, POSITION_ARRAY_NAME);
    glVertexAttribPointer(poshandle, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(poshandle);
    if (!depth) 
    {
		colorhandle = glGetAttribLocation(currentshader, COLOR_ARRAY_NAME);
		glVertexAttribPointer(colorhandle, 3, GL_FLOAT, GL_FALSE, 0, colors);
	    glEnableVertexAttribArray(colorhandle);
		normhandle = glGetAttribLocation(currentshader, NORMAL_ARRAY_NAME);
		glVertexAttribPointer(normhandle, 3, GL_FLOAT, GL_FALSE, 0, norms);
	    glEnableVertexAttribArray(normhandle);
    }
    glDrawArrays(GL_TRIANGLES, 0, numTriangles*3);    

}

/*
void renderFrame2(Kewlmation *km, int frame, float zpos)
{
	frame = frame % km->numframes;
	unsigned int numTriangles = km->frameinfo[(int)frame*2+1];
	unsigned char *data = km->frames+km->frameinfo[(int)frame*2+0];
	unsigned int i, j;
	static float colors[MAXTRIANGLES*3*3];
	static float vertices[MAXTRIANGLES*3*3];
	int poshandle, colorhandle;

	if (numTriangles > MAXTRIANGLES) {
		numTriangles = MAXTRIANGLES;
		LOGE("too much trianges in video");
	}

	float *cpos = colors;
	float *vpos = vertices;

	for (i = 0; i < numTriangles; i++)
	{
		for (j = 0; j < 3; j++)
		{
#ifdef BW
			float bw = data[i*stride+j*tristride+2]/255.0;
#else
			uint16 col = data[i*stride+j*tristride+2]*256 + data[i*stride+j*tristride+3];
			float r, g, b;
			r = (float)(col>>11)/31.0;
			g = (float)((col>>5)&63)/63.0; 
			b = (float)(col&31)/31.0;
#endif
			*vpos++ = (float)(data[i*stride+j*tristride+0]/255.0)-0.5;
			*vpos++ = (float)(data[i*stride+j*tristride+1]/255.0)-0.5;
			*vpos++ = zpos;

			*cpos++ = bw;
			*cpos++ = bw;
			*cpos++ = bw;
		}
	}

	poshandle = glGetAttribLocation(currentshader, POSITION_ARRAY_NAME);
	checkerror("a");	
    glVertexAttribPointer(poshandle, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	checkerror("b");
    glEnableVertexAttribArray(poshandle);
   	checkerror("c");
	colorhandle = glGetAttribLocation(currentshader, COLOR_ARRAY_NAME);
	checkerror("d");
	glVertexAttribPointer(colorhandle, 3, GL_FLOAT, GL_FALSE, 0, colors);
	checkerror("e");
    glEnableVertexAttribArray(colorhandle);
	checkerror("f");
    glDrawArrays(GL_TRIANGLES, 0, numTriangles*3);    
	checkerror("g");


}
*/

    
