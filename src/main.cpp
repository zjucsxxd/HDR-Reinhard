#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#include "entryfunc.h"

int get_num_exposures(const char *list_file_path, int *imwidth, int *imheight){
    FILE *fp = fopen(list_file_path, "r");
    char buf[128] = { 0 };
    int num_line = 0;
    while (fgets(buf, 128, fp) != NULL){
        ++num_line;
    }
    fclose(fp);
    sscanf(buf, "%s ", buf);
    Mat im = imread(buf);
    *imwidth = im.cols;
    *imheight = im.rows;
    return num_line;
}

/* opencv read image */
void parse_list(const char *list_file_path, const int NUM_EXPOSURES, float *exposure_values, unsigned char **exposure_images){
    FILE* fp = fopen(list_file_path, "r");
    char buf[128] = { 0 };
    int exposures_idx = 0;
    for (exposures_idx = 0; exposures_idx < NUM_EXPOSURES; ++exposures_idx){
        fscanf(fp, "%s %f\n", buf, &(exposure_values[exposures_idx]));
        Mat im = imread(buf);
        memcpy(exposure_images[exposures_idx], im.data, 3 * im.rows * im.cols * sizeof(unsigned char));
    }
    fclose(fp);
}

/* opencv display image */
void display_result(const unsigned char* output, const int IMWIDTH, const int IMHEIGHT){
    Mat im = Mat(IMHEIGHT, IMWIDTH, CV_8UC3, (void*)output);
    imshow("result", im);
    waitKey(0);
}

int main(int ac, char **av){
    if (ac != 2){
        printf("Usage: hdr_reinhard [exposure list file]\n");
        exit(-1);
    }
    int imwidth = 0;
    int imheight = 0;
    int num_exposure = get_num_exposures(av[1], &imwidth, & imheight);
    float* exposure_vals = (float*)malloc(num_exposure * sizeof(float));
    unsigned char** exposure_ims = (unsigned char**)malloc(num_exposure * sizeof(unsigned char*));
    int exposures_idx = 0;
    for (exposures_idx = 0; exposures_idx < num_exposure; ++exposures_idx){
        exposure_ims[exposures_idx] = (unsigned char*)malloc(3 * imwidth * imheight * sizeof(unsigned char));
    }
    parse_list(av[1], num_exposure, exposure_vals, exposure_ims);

    hdr_init(num_exposure, exposure_vals, exposure_ims, imwidth, imheight);
    const unsigned char* output_image = hdr_main(HDR_REINHARD_GLOBAL);
    display_result(output_image, imwidth, imheight);
    hdr_free();

    free(exposure_vals);
    for (exposures_idx = 0; exposures_idx < num_exposure; ++exposures_idx){
        free(exposure_ims[exposures_idx]);
    }
    free(exposure_ims);
    return 0;
}