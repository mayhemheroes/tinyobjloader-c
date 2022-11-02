#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "../tinyobj_loader_c.h"

uint8_t* tmpBuffer;
size_t input_data_size;

void loadFile(void *ctx, const char * filename, const int is_mtl, const char *obj_filename, char ** buffer, size_t * len)
{
    *buffer = tmpBuffer;
    *len = input_data_size;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    if (Size > 0) {
        input_data_size = Size-1;
        tmpBuffer = (uint8_t*) malloc(Size-1);
        memcpy(tmpBuffer, Data+1, Size-1);
        if (Data[0] % 2 == 0) {
            tinyobj_material_t * material;
            size_t num_materials;
            tinyobj_parse_mtl_file(&material, &num_materials, "", /* obj filename */NULL, loadFile, NULL);
        } else {
            tinyobj_shape_t * shape = NULL;
            tinyobj_material_t * material = NULL;
            tinyobj_attrib_t attrib;

            unsigned long num_shapes;
            unsigned long num_materials;

            tinyobj_attrib_init(&attrib);

            tinyobj_parse_obj(&attrib, &shape, &num_shapes, &material, &num_materials, "", loadFile, NULL, TINYOBJ_FLAG_TRIANGULATE);
        }
        free(tmpBuffer);
    }
    return 0;
}