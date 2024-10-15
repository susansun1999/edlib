#include <cstdio>
#include "edlib.h"

int main() {
    EdlibAlignResult result = edlibAlign("hello", 5, "world!", 6, edlibDefaultAlignConfig());
    if (result.status == EDLIB_STATUS_OK) {
        printf("edit_distance('hello', 'world!') = %d\n", result.editDistance);
    }
    edlibFreeAlignResult(result);
}
