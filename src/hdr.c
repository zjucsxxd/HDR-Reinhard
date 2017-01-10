#include "hdr.h"

static const unsigned char hdr_weights[256] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 127,
126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98,
97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62,
61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,
25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

/* calculate this using "gsolve.m" referenced in "Debevec, P. 1998. Recovering High Dynamic Range Radiance Maps from Photographs." */
static const float g_green[256] = { -4.495188567858563f, -4.376902513824406f, -4.258616459790245f, -4.140330405756109f, -4.022044351722f,
-3.903766473016247f, -3.785547869485901f, -3.667789300052836f, -3.551086595145196f, -3.436443977173664f, -3.325015236888474f, -3.217456992113802f,
-3.113965559539528f, -3.014726021015882f, -2.919869682341458f, -2.829899534716569f, -2.745142383458001f, -2.665612551770399f, -2.591088334999103f,
-2.521223959666765f, -2.455638040972245f, -2.393937998479167f, -2.335706727051395f, -2.280478859631515f, -2.227791072411007f, -2.177242254491476f,
-2.128582200748065f, -2.081592130588677f, -2.036078430150703f, -1.991921757663193f, -1.949147418988918f, -1.907838707310797f, -1.867967173164509f,
-1.82941743403727f, -1.792079196995946f, -1.755962771057843f, -1.721079154224879f, -1.687422632879139f, -1.654924568076226f, -1.623502552784026f,
-1.593128088531818f, -1.563828166581599f, -1.535444773377969f, -1.507828087942594f, -1.480793539376492f, -1.454172353227419f, -1.427836927920927f,
-1.401732295679401f, -1.37575393723451f, -1.349860662445201f, -1.324046353051506f, -1.298326317000189f, -1.272758238248259f, -1.247442878212544f,
-1.222534187351445f, -1.198174644643426f, -1.174496192288205f, -1.151621081967457f, -1.129631546734315f, -1.108549860024433f, -1.088337097443043f,
-1.068967506886988f, -1.050397638917214f, -1.032545900744024f, -1.01533337950493f, -0.9985966138610081f, -0.9821931349342679f, -0.9659626535259955f,
-0.9497852760683522f, -0.9335480348733147f, -0.9171391616315456f, -0.9004788268484102f, -0.8835003410404735f, -0.8661305116060189f, -0.848300248430941f,
-0.8299772056760178f, -0.811130914822457f, -0.7917444008674416f, -0.7718590949879803f, -0.7515966110548782f, -0.7309894820569609f, -0.7100659232696552f,
-0.6888436568014721f, -0.6673438812223302f, -0.645624045491676f, -0.6237757768369305f, -0.6018945948542633f, -0.5800735301568039f, -0.5584544075789513f,
-0.5372399336028693f, -0.5165682638315363f, -0.4965378063506874f, -0.4772425362868266f, -0.4588109724326463f, -0.4413411644911276f, -0.4248803351492261f,
-0.4094163204785795f, -0.3949372417790737f, -0.3813102756217481f, -0.3684200811256404f, -0.3561621885807329f, -0.3444161840745683f, -0.3330479535717519f,
-0.3219322740906242f, -0.3109814149696172f, -0.3001060326232261f, -0.2891943522628176f, -0.2781540572342218f, -0.2669259558543653f, -0.2554501400408598f,
-0.243679635153109f, -0.2316393252330284f, -0.2193589408548617f, -0.2068750324958519f, -0.1942229001386251f, -0.1814090770763475f, -0.1684398957855264f,
-0.1553320497868689f, -0.1421016870196481f, -0.1287208238424733f, -0.1152014142211266f, -0.101522180753788f, -0.08767181558481973f, -0.07363940156440968f,
-0.05939599025907261f, -0.04491358696996217f, -0.03016511625292084f, -0.01518317860296658f, -2.987161629164348e-010f, 0.01535585455083899f, 0.03085811841309066f,
0.04646192624422962f, 0.06211629925816364f, 0.07776858065913483f, 0.09336437332886716f, 0.1088696161660568f, 0.1242508266013549f, 0.1394734046606767f,
0.1545015903352507f, 0.1692984190038875f, 0.1838256748021809f, 0.1980438418267614f, 0.2119120530555998f, 0.2253880368578245f, 0.238428060958243f,
0.2510035443845262f, 0.2631399817605737f, 0.2748254312991421f, 0.28610880887382f, 0.297037263282879f, 0.3076824356841423f, 0.3181291022546697f,
0.3284952388327596f, 0.3389019037788978f, 0.3494610593836137f, 0.3602588150778692f, 0.3713497299088395f, 0.3828040624192637f, 0.3947239572526446f,
0.4071811184582126f, 0.4202124981761335f, 0.4337972658276763f, 0.4479132773251115f, 0.4625373030604675f, 0.4776559139349011f, 0.4932641037542644f,
0.5092641942802232f, 0.525598094113605f, 0.5422049551201327f, 0.5590210272675598f, 0.5759795043536228f, 0.5930513142983744f, 0.6102317809772161f,
0.6275053540837148f, 0.6449113669681764f, 0.6624396429636334f, 0.6800810066821195f, 0.6979566812187769f, 0.7161520775396826f, 0.7346359751309774f,
0.7533753887764382f, 0.7723354597419969f, 0.791479338984089f, 0.8107620351232172f, 0.830135968987339f, 0.8495978090823741f, 0.8689652768439686f,
0.8881747429444479f, 0.9071408918636873f, 0.9257856445160277f, 0.9440262656169104f, 0.961830888000559f, 0.9791726957613827f, 0.9960233765859706f,
1.012390702541488f, 1.028286122788909f, 1.043722939670784f, 1.058707208784036f, 1.073254338052837f, 1.087383620352974f, 1.101172019613268f,
1.114702424286893f, 1.128064153365038f, 1.141282048874175f, 1.154346744193161f, 1.167201483080542f, 1.179975693981454f, 1.192809653631343f,
1.205855520164373f, 1.219278485009415f, 1.233171424219742f, 1.247635188784494f, 1.262779416638736f, 1.27867615268749f, 1.295368083668602f,
1.31284853344622f, 1.331109155932061f, 1.350139701211712f, 1.369927745664234f, 1.39045837962871f, 1.41166214936591f, 1.433460337781512f,
1.455763666163052f, 1.478420255508945f, 1.501327046200211f, 1.52449445186896f, 1.547933741769982f, 1.571657146563662f, 1.595677981766039f,
1.619942557469689f, 1.644387884963924f, 1.668896033223513f, 1.693328378959243f, 1.717570559958985f, 1.741487261543596f, 1.764867004572483f,
1.788039635270343f, 1.811331913831321f, 1.834910078934323f, 1.858939805916749f, 1.883480804847351f, 1.908442906949248f, 1.933704043787625f,
1.959273703191545f, 1.985160514114911f, 2.011371286393902f, 2.037909346965433f, 2.064771584505865f, 2.091943007041721f, 2.119386212127226f,
2.147019607494937f, 2.174721206745915f, 2.202489539377733f, 2.230283821969566f, 2.258107298266413f, 2.285930774563247f };

/* sigma = 0.35355 */
static const float gaussian_kernel1[3] = { 0.017668f, 0.964663f, 0.017668f };
/* sigma = 0.56569 */
static const float gaussian_kernel2[5] = { 0.0013565f, 0.1472938f, 0.7026994f, 0.1472938f, 0.0013565f };
/* sigma = 0.90510 */
static const float gaussian_kernel3[5] = { 0.038506f, 0.240294f, 0.442400f, 0.240294f, 0.038506f };
/* sigma = 1.4482 */
static const float gaussian_kernel4[7] = { 0.032672f, 0.107622f, 0.220055f, 0.279303f, 0.220055f, 0.107622f, 0.032672f };
/* sigma = 2.3170 */
static const float gaussian_kernel5[11] = { 0.017066f, 0.039460f, 0.075733f, 0.120648f, 0.159537f, 0.175109f, 0.159537f, 0.120648f,
0.075733f, 0.039460f, 0.017066f };
/* sigma = 3.7073 */
static const float gaussian_kernel6[17] = { 0.010718f, 0.018497f, 0.029682f, 0.044288f, 0.061445f, 0.079265f, 0.095078f, 0.106042f,
0.109971f, 0.106042f, 0.095078f, 0.079265f, 0.061445f, 0.044288f, 0.029682f, 0.018497f, 0.010718f };

static const int gaussian_kernel_sizes[SCALE_SPACE_COUNT] = { 3, 5, 5, 7, 11, 17 };

static const float *gaussian_kernels[SCALE_SPACE_COUNT] = { gaussian_kernel1, gaussian_kernel2, gaussian_kernel3, gaussian_kernel4,
gaussian_kernel5, gaussian_kernel6 };

void build_hdr_image(const HDR_struct *hdr_info){
    const int HDR_IMG_SIZE = hdr_info->imwidth * hdr_info->imheight;
    const int HDR_IMG_SIZEX2 = HDR_IMG_SIZE << 1;
    float *log_exposure_time = (float*)alloc_from_stack(hdr_info->num_exposure * sizeof(float));
    int exposures_idx = 0;
    int position_idx = 0;
    float radiance_temp = 0.0f;
    /* approximate the log radiance from the smallest e.v. picture in case pixel is saturated in every pictures */
    int least_ev_index = hdr_info->num_exposure - 1;
    for (exposures_idx = 0; exposures_idx < hdr_info->num_exposure; ++exposures_idx){
        log_exposure_time[exposures_idx] = (float)log((double)hdr_info->exposure_values[exposures_idx]);
    }
    for (position_idx = 0; position_idx < HDR_IMG_SIZE; ++position_idx){
        float weighted_log_radiance_blue = 0.0f;
        float weighted_log_radiance_green = 0.0f;
        float weighted_log_radiance_red = 0.0f;
        int weight_sum_blue = 0;
        int weight_sum_green = 0;
        int weight_sum_red = 0;
        for (exposures_idx = 0; exposures_idx < hdr_info->num_exposure; ++exposures_idx){
            unsigned char zb = hdr_info->exposure_images[exposures_idx][3 * position_idx];
            unsigned char zg = hdr_info->exposure_images[exposures_idx][3 * position_idx + 1];
            unsigned char zr = hdr_info->exposure_images[exposures_idx][3 * position_idx + 2];
            if (zb == 0xFF || zg == 0xFF || zr == 0xFF){ /* saturation protection */
                weighted_log_radiance_blue = 0.0f;
                weighted_log_radiance_green = 0.0f;
                weighted_log_radiance_red = 0.0f;
                weight_sum_blue = 0;
                weight_sum_green = 0;
                weight_sum_red = 0;
            }
            else{
                weighted_log_radiance_blue += hdr_weights[zb] * (g_green[zb] - log_exposure_time[exposures_idx]);
                weighted_log_radiance_green += hdr_weights[zg] * (g_green[zg] - log_exposure_time[exposures_idx]);
                weighted_log_radiance_red += hdr_weights[zr] * (g_green[zr] - log_exposure_time[exposures_idx]);
                weight_sum_blue += hdr_weights[zb];
                weight_sum_green += hdr_weights[zg];
                weight_sum_red += hdr_weights[zr];
            }
        }
        /* blue */
        if (weight_sum_blue == 0){
            unsigned char pixel_value = hdr_info->exposure_images[least_ev_index][3 * position_idx];
            radiance_temp = g_green[pixel_value] - log_exposure_time[least_ev_index];
        }
        else{
            radiance_temp = weighted_log_radiance_blue / weight_sum_blue;
        }
        hdr_info->hdr_im[position_idx] = (float)exp((double)radiance_temp);
        /* green */
        if (weight_sum_green == 0){
            unsigned char pixel_value = hdr_info->exposure_images[least_ev_index][3 * position_idx + 1];
            radiance_temp = g_green[pixel_value] - log_exposure_time[least_ev_index];
        }
        else{
            radiance_temp = weighted_log_radiance_green / weight_sum_green;
        }
        hdr_info->hdr_im[HDR_IMG_SIZE + position_idx] = (float)exp((double)radiance_temp);
        /* red */
        if (weight_sum_red == 0){
            unsigned char pixel_value = hdr_info->exposure_images[least_ev_index][3 * position_idx + 2];
            radiance_temp = g_green[pixel_value] - log_exposure_time[least_ev_index];
        }
        else{
            radiance_temp = weighted_log_radiance_red / weight_sum_red;
        }
        hdr_info->hdr_im[HDR_IMG_SIZEX2 + position_idx] = (float)exp((double)radiance_temp);
    }
    partial_free_from_stack(hdr_info->num_exposure * sizeof(float));
}

static void gaussian_smooth(const float *src, const float *kernel, const int kernel_size, const int IMWIDTH, const int IMHEIGHT, float *dst, float *tempbuf){
    const int HDR_IMG_SIZE = IMWIDTH * IMHEIGHT;
    /* x direction (src -> tempbuf) */
    int i = 0;
    int j = 0;
    int k = 0;
    int kernel_radius = kernel_size >> 1;
    int begin = kernel_radius;
    int end = HDR_IMG_SIZE - kernel_radius;
    /* wrap border */
    for (i = begin; i < end; ++i){
        float dotsum = src[i] * kernel[kernel_radius];
        for (j = 1; j <= kernel_radius; ++j){
            dotsum += (src[i - j] * kernel[kernel_radius - j]);
            dotsum += (src[i + j] * kernel[kernel_radius + j]);
        }
        tempbuf[i] = dotsum;
    }
    for (i = 0; i < kernel_radius; ++i){
        tempbuf[i] = tempbuf[kernel_radius];
    }
    for (i = end; i < HDR_IMG_SIZE; ++i){
        tempbuf[i] = tempbuf[end - 1];
    }
    /* y direction (tempbuf -> dst) */
    /* main part */
    begin = kernel_radius * IMWIDTH;
    end = HDR_IMG_SIZE - (kernel_radius * IMWIDTH);
    for (i = begin; i < end; ++i){
        float dotsum = tempbuf[i] * kernel[kernel_radius];
        for (j = 1; j <= kernel_radius; ++j){
            int delta = j * IMWIDTH;
            dotsum += (tempbuf[i - delta] * kernel[kernel_radius - j]);
            dotsum += (tempbuf[i + delta] * kernel[kernel_radius + j]);
        }
        dst[i] = dotsum;
    }
    /* up side part, zero border */
    for (i = 0; i < kernel_radius; ++i){
        for (j = 0; j < IMWIDTH; ++j){
            int idx = j + i * IMWIDTH;
            float dotsum = tempbuf[idx] * kernel[kernel_radius];
            for (k = 1; k <= kernel_radius; ++k){
                int delta = k * IMWIDTH;
                if (i >= k){
                    dotsum += (tempbuf[idx - delta] * kernel[kernel_radius - k]);
                }
                dotsum += (tempbuf[idx + delta] * kernel[kernel_radius + k]);
            }
            dst[idx] = dotsum;
        }
    }
    /* down side part, zero border */
    for (i = IMHEIGHT - kernel_radius; i < IMHEIGHT; ++i){
        for (j = 0; j < IMWIDTH; ++j){
            int idx = j + i * IMWIDTH;
            float dotsum = tempbuf[idx] * kernel[kernel_radius];
            for (k = 1; k <= kernel_radius; ++k){
                int delta = k * IMWIDTH;
                dotsum += (tempbuf[idx - delta] * kernel[kernel_radius - k]);
                if (i + k < IMHEIGHT){
                    dotsum += (tempbuf[idx + delta] * kernel[kernel_radius + k]);
                }
            }
            dst[idx] = dotsum;
        }
    }
}

static void center_surround(const float *center, const float *surround, const int IMWIDTH, const int IMHEIGHT, float *dst){
    const int HDR_IMG_SIZE = IMWIDTH * IMHEIGHT;
    /* scale factor square, not sure the proper value, use (1.6 ^ 5)^2 here */
    const float sqrs = 109.951163f;
    const float denominator = ((float)pow(2.0, SHARPENING_PARAMETER_PHI) * IMAGE_KEY_A / sqrs);
    int position_idx = 0;
    for (position_idx = 0; position_idx < HDR_IMG_SIZE; ++position_idx){
        dst[position_idx] = (float)fabs((double)(center[position_idx] - surround[position_idx])) / (denominator + center[position_idx]);
    }
}

void tone_mapping_reinhard_local(HDR_struct *hdr_info){
    const int HDR_IMG_SIZE = hdr_info->imwidth * hdr_info->imheight;
    const int HDR_IMG_SIZEX2 = HDR_IMG_SIZE << 1;
    float *relative_luminance = (float*)alloc_from_stack(HDR_IMG_SIZE * sizeof(float));
    float *gaussian_smoothed_images = (float*)alloc_from_stack(SCALE_SPACE_COUNT * HDR_IMG_SIZE * sizeof(float));
    float *DoG = (float*)alloc_from_stack((SCALE_SPACE_COUNT - 2)* HDR_IMG_SIZE * sizeof(float));
    float *V1[SCALE_SPACE_COUNT] = { gaussian_smoothed_images, gaussian_smoothed_images + HDR_IMG_SIZE,
        gaussian_smoothed_images + 2 * HDR_IMG_SIZE, gaussian_smoothed_images + 3 * HDR_IMG_SIZE,
        gaussian_smoothed_images + 4 * HDR_IMG_SIZE, gaussian_smoothed_images + 5 * HDR_IMG_SIZE };
    float *V[SCALE_SPACE_COUNT - 2] = { DoG, DoG + HDR_IMG_SIZE, DoG + 2 * HDR_IMG_SIZE, DoG + 3 * HDR_IMG_SIZE };
    double log_luminance_sum = 0.0;
    double average_luminance = 0.0;
    double key_ratio = 0.0;
    int position_idx = 0;
    int layer_idx = 0;
    unsigned char *dst = hdr_info->ldr_im;
    for (position_idx = 0; position_idx < HDR_IMG_SIZE; ++position_idx){
        relative_luminance[position_idx] = 0.0721f * hdr_info->hdr_im[position_idx] +
            0.7154f * hdr_info->hdr_im[HDR_IMG_SIZE + position_idx] +
            0.2125f * hdr_info->hdr_im[HDR_IMG_SIZEX2 + position_idx];
    }
    /* create SCALE_SPACE_COUNT number of Gaussian filtered HDR image, and get SCALE_SPACE_COUNT - 2 number of DoG image (ignore scale 1 DoG) */
    /* build pyramid */
    for (layer_idx = 0; layer_idx < SCALE_SPACE_COUNT; ++layer_idx){
        gaussian_smooth(relative_luminance, gaussian_kernels[layer_idx], gaussian_kernel_sizes[layer_idx],
                        hdr_info->imwidth, hdr_info->imheight, V1[layer_idx], V[0]); //V[0] for temp buffer
    }
    /* create DoG, start from 2nd scale level */
    for (layer_idx = 0; layer_idx < SCALE_SPACE_COUNT - 2; ++layer_idx){
        center_surround(V1[layer_idx + 1], V1[layer_idx + 2], hdr_info->imwidth, hdr_info->imheight, V[layer_idx]);
    }
    for (position_idx = 0; position_idx < HDR_IMG_SIZE; ++position_idx){
        /* select the proper scale */
        /* to reserve details, default select the biggest scale */
        int scale = SCALE_SPACE_COUNT - 2;
        for (layer_idx = 0; layer_idx < SCALE_SPACE_COUNT - 2; ++layer_idx){
            if (V[layer_idx][position_idx] > DOG_THRESHOLD_EPSILON){
                scale = layer_idx;
                break;
            }
        }
        /* V1[SCALE_SPACE_COUNT] for temp buffer (final local luminance) */
        V1[SCALE_SPACE_COUNT - 1][position_idx] = V1[scale][position_idx];
        log_luminance_sum += log((double)V1[scale][position_idx] + 0.0001);
    }
    average_luminance = exp(log_luminance_sum / HDR_IMG_SIZE);
    key_ratio = IMAGE_KEY_A / average_luminance;
    for (position_idx = 0; position_idx < HDR_IMG_SIZE; ++position_idx){
        double scaled_luminance = V1[SCALE_SPACE_COUNT - 1][position_idx] * key_ratio;
        double luminance_final = (relative_luminance[position_idx] * key_ratio) / (1 + scaled_luminance);
        double blue = pow(hdr_info->hdr_im[position_idx] / relative_luminance[position_idx], COLOR_SATURATION) * luminance_final;
        *dst = (unsigned char)(min(255.0, 255.0 * blue) + 0.5);
        ++dst;
        double green = pow(hdr_info->hdr_im[HDR_IMG_SIZE + position_idx] / relative_luminance[position_idx], COLOR_SATURATION) * luminance_final;
        *dst = (unsigned char)(min(255.0, 255.0 * green) + 0.5);
        ++dst;
        double red = pow(hdr_info->hdr_im[HDR_IMG_SIZEX2 + position_idx] / relative_luminance[position_idx], COLOR_SATURATION) * luminance_final;
        *dst = (unsigned char)(min(255.0, 255.0 * red) + 0.5);
        ++dst;
    }
    partial_free_from_stack((SCALE_SPACE_COUNT + SCALE_SPACE_COUNT - 1) * HDR_IMG_SIZE * sizeof(float));
}

void tone_mapping_reinhard_global(HDR_struct *hdr_info){
    const int HDR_IMG_SIZE = hdr_info->imwidth * hdr_info->imheight;
    const int HDR_IMG_SIZEX2 = HDR_IMG_SIZE << 1;
    float *relative_luminance = (float*)alloc_from_stack(HDR_IMG_SIZE * sizeof(float));
    double log_luminance_sum = 0.0;
    double current_key = 0.0;
    double key_scale = 0.0;
    int position_idx = 0;
    unsigned char *dst = hdr_info->ldr_im;
    for (position_idx = 0; position_idx < HDR_IMG_SIZE; ++position_idx){
        relative_luminance[position_idx] = 0.0721f * hdr_info->hdr_im[position_idx] +
            0.7154f * hdr_info->hdr_im[HDR_IMG_SIZE + position_idx] +
            0.2125f * hdr_info->hdr_im[HDR_IMG_SIZEX2 + position_idx];
        log_luminance_sum += log(relative_luminance[position_idx] + 0.0001);
    }
    /* compute the key of image */
    current_key = exp(log_luminance_sum / HDR_IMG_SIZE);
    key_scale = IMAGE_KEY_A / current_key;
    for (position_idx = 0; position_idx < HDR_IMG_SIZE; ++position_idx){
        double scaled_luminance = relative_luminance[position_idx] * key_scale;
        double luminance_final = scaled_luminance / (1 + scaled_luminance);
        float relative_luminance_reciprocal = 1 / relative_luminance[position_idx];
        double blue = pow(hdr_info->hdr_im[position_idx] * relative_luminance_reciprocal, COLOR_SATURATION) * luminance_final;
        *dst = (unsigned char)(min(255.0, 255.0 * blue) + 0.5);
        ++dst;
        double green = pow(hdr_info->hdr_im[HDR_IMG_SIZE + position_idx] * relative_luminance_reciprocal, COLOR_SATURATION) * luminance_final;
        *dst = (unsigned char)(min(255.0, 255.0 * green) + 0.5);
        ++dst;
        double red = pow(hdr_info->hdr_im[HDR_IMG_SIZEX2 + position_idx] * relative_luminance_reciprocal, COLOR_SATURATION) * luminance_final;
        *dst = (unsigned char)(min(255.0, 255.0 * red) + 0.5);
        ++dst;
    }
    partial_free_from_stack(HDR_IMG_SIZE * sizeof(float));
}