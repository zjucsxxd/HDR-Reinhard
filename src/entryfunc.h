#if !defined ENTRYFUNC_H
#define ENTRYFUNC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "utils.h"
#include "hdr.h"

void hdr_free(void);

void hdr_init(const int NUM_EXPOSURES, float *exposure_values, unsigned char **exposure_images, const int IMWIDTH, const int IMHEIGHT);

const unsigned char *hdr_main(HDR_TONE_MAPPING_APPROACH tonemapping_method);

#ifdef __cplusplus
}
#endif

#endif /* ENTRYFUNC_H */