#include <stdio.h>
#include <inttypes.h>
#include "test_data.h"

typedef struct {
    int16_t i, j;
    _Bool ok;
} TwoSum;

TwoSum twosum(int32_t *nums, int16_t count, int32_t target);

#define nums nums_10000
int main(void)
{
    printf("Tarea 2 ELO320 2026-1\n");

    int32_t target = -864197532L;
    TwoSum ts  = twosum(nums, sizeof(nums)/sizeof(*nums), target);
    if(ts.ok) {
        printf("i: %d j: %d\n", ts.i, ts.j);
        printf("Sanity check: Target=%d nums[%d]+nums[%d]=%d\n", target, ts.i, ts.j,
               nums[ts.i]+nums[ts.j]);
    }
    else
        printf("Target no detectado.\n");
    return 0;
}


TwoSum twosum(int32_t *nums, int16_t count, int32_t target)
{
    TwoSum r = {0};
    uint16_t seen[?] = {0};
    for (int16_t n = 0; n < count; n++) {
        int32_t complement = ?;
        int32_t key = ?;  // maximo entre complement y nums[n]
        uint32_t hash = ?;
        unsigned mask = ?;
        unsigned step = ?;
        unsigned i = hash;
        while(1) {
            int16_t j = seen[i & mask] - 1;  // unbias
            if (j < 0) {
                seen[i & mask] = n + 1;  // bias and insert
                break;
            } else if (?) {
                r.i = ?;
                r.j = ?;
                r.ok = 1;
                return r;
            }
            i += 1;
        }
    }
    return r;
}
