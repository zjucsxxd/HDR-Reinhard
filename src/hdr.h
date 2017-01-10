#if !defined HDR_H
#define HDR_H

#include "utils.h"

/* increase epsilon or phi will have more detail, but may suffer from halo effect */
#define DOG_THRESHOLD_EPSILON (0.05f)
#define SHARPENING_PARAMETER_PHI (14.0)
/* overall luminance key, candidate: 0.045, 0.09, 0.18, 0.36, 0.72 */
#define IMAGE_KEY_A (0.72f)
/* color saturation factor */
#define COLOR_SATURATION (0.4545)
#define SCALE_SPACE_COUNT (6)

typedef enum{
    HDR_REINHARD_GLOBAL,
    HDR_REINHARD_LOCAL
}HDR_TONE_MAPPING_APPROACH;

typedef struct{
    int num_exposure;
    float *exposure_values;
    unsigned char **exposure_images;
    int imwidth;
    int imheight;
    float *hdr_im;
    unsigned char *ldr_im; /* output */
}HDR_struct;

void build_hdr_image(const HDR_struct *hdr_wksp);

void tone_mapping_reinhard_global(HDR_struct *hdr_wksp);

void tone_mapping_reinhard_local(HDR_struct *hdr_wksp);

#endif /* HDR_H */