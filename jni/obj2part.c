
#include <float.h>

#define MAXPARTS 16384


#define SLOT_LENGTH 512
#define NUM_SLOTS 512
#define UNUSED 0xFFFF

typedef struct{
  unsigned short index;
  float pos[3];
} datorz;

static datorz partitions[SLOT_LENGTH*NUM_SLOTS];
static float minX, maxX;

int add_vert(float *pos, unsigned short index, float psize) {
  float npos = (pos[0] - minX) / (maxX-minX);
  int slotnum = round(npos * (NUM_SLOTS-1));
  int i, j;

  // test collision
  for (i=clamp(slotnum-1, 0, NUM_SLOTS-1); i<clamp(slotnum+1, 0, NUM_SLOTS-1); i++) {
    for (j=0; j<SLOT_LENGTH; j++) {
      if (partitions[i*SLOT_LENGTH+j].index==UNUSED) break;
      float *opos = partitions[i*SLOT_LENGTH+j].pos;
      if (vdist(opos, pos) < psize*1.25) return 0;
    }
  }

  for (i=0; i<SLOT_LENGTH; i++) {
    if (partitions[slotnum*SLOT_LENGTH+i].index==UNUSED) {
      partitions[slotnum*SLOT_LENGTH+i].index=index;
      partitions[slotnum*SLOT_LENGTH+i].pos[0]=pos[0];
      partitions[slotnum*SLOT_LENGTH+i].pos[1]=pos[1];
      partitions[slotnum*SLOT_LENGTH+i].pos[2]=pos[2];
      return 1;
    }
  }

  LOGI("voihan nenä, loppu taulukko kesken");
  return 0;
}


void obj2part(char *name, float *src_verts, float *src_norms, unsigned int vcount, unsigned int fcount, unsigned short *src_indices, 
  float amount, int override_numperpoly, float **vert, float **norm, int *cnt, float normalmove, float scale, float psize)
{  
  int x, y;
  int vpos=0;
  static float tenp_vert[MAXPARTS*3], tenp_norm[MAXPARTS*3];
  int i=0;
  int colcnt=0;

  for (i=0; i<SLOT_LENGTH*NUM_SLOTS; i++) partitions[i].index=UNUSED;

  maxX=-FLT_MAX;
  minX=FLT_MAX;
  for (i=0; i<vcount; i++) {
    float xpos=src_verts[i*3];
    if (xpos<minX) minX=xpos;
    if (xpos>maxX) maxX=xpos;
  }
  LOGI("object %s, xsize %5.2f - %5.2f", name, minX, maxX);

  i=0;
  while (vpos < MAXPARTS)
  {
    i++;
    for (x=0; x<fcount; x++) {
      float v1[3], v2[3], v3[3];
      float n1[3], n2[3], n3[3];
      //float blaa;
      int jee;

      v1[0]=src_verts[src_indices[x*3+0]*3+0];
      v1[1]=src_verts[src_indices[x*3+0]*3+1];
      v1[2]=src_verts[src_indices[x*3+0]*3+2];

      v2[0]=src_verts[src_indices[x*3+1]*3+0];
      v2[1]=src_verts[src_indices[x*3+1]*3+1];
      v2[2]=src_verts[src_indices[x*3+1]*3+2];

      v3[0]=src_verts[src_indices[x*3+2]*3+0];
      v3[1]=src_verts[src_indices[x*3+2]*3+1];
      v3[2]=src_verts[src_indices[x*3+2]*3+2];

      if (src_norms) {
        n1[0]=src_norms[src_indices[x*3+0]*3+0];
        n1[1]=src_norms[src_indices[x*3+0]*3+1];
        n1[2]=src_norms[src_indices[x*3+0]*3+2];

        n2[0]=src_norms[src_indices[x*3+1]*3+0];
        n2[1]=src_norms[src_indices[x*3+1]*3+1];
        n2[2]=src_norms[src_indices[x*3+1]*3+2];

        n3[0]=src_norms[src_indices[x*3+2]*3+0];
        n3[1]=src_norms[src_indices[x*3+2]*3+1];
        n3[2]=src_norms[src_indices[x*3+2]*3+2];
      }
      //blaa=vdist(v1, v2)+vdist(v2, v3)+vdist(v3, v1);
      //blaa*=blaa;
      float va[3], vb[3], cp[3];
      vminus(va, v2, v1);
      vminus(vb, v3, v1);
      cross(cp, va, vb);
      float area=0.5*vlen(cp);

      if (override_numperpoly) jee=override_numperpoly;
      else jee=ceil(area*amount);

      for (y=0; y<jee; y++) {
        float a, b;
        float point[3], norm[3];

        a=ranf();
        b=ranf();
        if (a+b>1) a=1-a, b=1-b;

        point[0] = v1[0] + a*(v2[0]-v1[0]) + b*(v3[0]-v1[0]);
        point[1] = v1[1] + a*(v2[1]-v1[1]) + b*(v3[1]-v1[1]);
        point[2] = v1[2] + a*(v2[2]-v1[2]) + b*(v3[2]-v1[2]);
        if (src_norms) {      
          norm[0] = n1[0] + a*(n2[0]-n1[0]) + b*(n3[0]-n1[0]);
          norm[1] = n1[1] + a*(n2[1]-n1[1]) + b*(n3[1]-n1[1]);
          norm[2] = n1[2] + a*(n2[2]-n1[2]) + b*(n3[2]-n1[2]);
      
          point[0]+=norm[0]*normalmove;
          point[1]+=norm[1]*normalmove;
          point[2]+=norm[2]*normalmove;
        }
        point[0]*=scale;
        point[1]*=scale;
        point[2]*=scale;
        
        if (add_vert(point,0,psize)) {
          tenp_vert[vpos*3+0]=point[0];
          tenp_vert[vpos*3+1]=point[1];
          tenp_vert[vpos*3+2]=point[2];
          if (src_norms) {
            tenp_norm[vpos*3+0]=norm[0];
            tenp_norm[vpos*3+1]=norm[1];
            tenp_norm[vpos*3+2]=norm[2];
          }
          vpos++;
        } else {
          colcnt++;
        }

        if (vpos == MAXPARTS) break;
      }
      if (vpos == MAXPARTS) break;
    }
    LOGI("obj2part iteration %i", i);
  }
  LOGI("collisions %i", colcnt);

  vert[0]=malloc(sizeof(float)*vpos*3);
  if (src_norms) norm[0]=malloc(sizeof(float)*vpos*3);

  /*
  memcpy(vert[0], tenp_vert, sizeof(float)*vpos*3);
  if (src_norms) memcpy(norm[0], tenp_norm, sizeof(float)*vpos*3);
  */

  for (x=0; x<vpos; x++) {
    radix_buffer1[x].f = tenp_vert[x*3+0];
    radix_buffer1[x].i = x;
  }

  radixsort(vpos);

  float *dst = vert[0];
  float *normdst;
  if (src_norms) normdst = norm[0];
  for (x=0; x<vpos; x++) {
    int i = radix_buffer1[x].i;
    dst[x*3+0] = tenp_vert[i*3+0];
    dst[x*3+1] = tenp_vert[i*3+1];
    dst[x*3+2] = tenp_vert[i*3+2];
    if (src_norms) {
      normdst[x*3+0] = tenp_norm[i*3+0];
      normdst[x*3+1] = tenp_norm[i*3+1];
      normdst[x*3+2] = tenp_norm[i*3+2];
    }
  }

  cnt[0]=vpos;

  // dump
  FILE *f;
  char fname[128];
  sprintf(fname, "/sdcard/tmp/%s.inc", name);
  f = fopen(fname, "w");
  fprintf(f, "#define %s_count %i\n", name, vpos);
  fprintf(f, "static float %s[%s_count*3] = {\n", name, name);
  for (x=0; x<vpos; x++) {
    fprintf(f, "\t%7.4f, %7.4f, %7.4f,\n", dst[x*3+0], dst[x*3+1], dst[x*3+2]);
  }
  fprintf(f, "};\n\n");
  fclose(f);



}

