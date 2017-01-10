#include "utils.h"
#include "hdr.h"

static HDR_struct *hdrinfo = NULL;

void hdr_free(void){
    free_stack();
}

void hdr_init(const int NUM_EXPOSURES, float *exposure_values, unsigned char **exposure_images, const int IMWIDTH, const int IMHEIGHT){
    init_stack();
    hdrinfo = (HDR_struct*)alloc_from_stack(sizeof(HDR_struct));
    hdrinfo->num_exposure = NUM_EXPOSURES;
    hdrinfo->exposure_values = exposure_values;
    hdrinfo->exposure_images = exposure_images;
    hdrinfo->imwidth = IMWIDTH;
    hdrinfo->imheight = IMHEIGHT;
    hdrinfo->hdr_im = (float*)alloc_from_stack(3 * IMWIDTH * IMHEIGHT * sizeof(float));
    hdrinfo->ldr_im = (unsigned char*)alloc_from_stack(3 * IMWIDTH * IMHEIGHT * sizeof(unsigned char));
}

const unsigned char *hdr_main(HDR_TONE_MAPPING_APPROACH tonemapping_method){
    /* recover hdr */
    build_hdr_image(hdrinfo);
    /* hdr to ldr */
    switch (tonemapping_method){
        case HDR_REINHARD_GLOBAL:
            tone_mapping_reinhard_global(hdrinfo);
            break;
        case HDR_REINHARD_LOCAL:
            tone_mapping_reinhard_local(hdrinfo);
            break;
    }
    return hdrinfo->ldr_im;
}