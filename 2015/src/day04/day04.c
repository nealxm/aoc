#include "day04.h"

#include "utils.h"

//#include "CommonCrypto/CommonDigest.h"
#include <openssl/md5.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day04_main(void) {
    char* input = file_to_string("./src/day04/data/input.txt");
    printf("2015:d04p1 - %u\n", day04_part1(input));
    printf("2015:d04p2 - %u\n", day04_part2(input));
    free(input);
}

uint32_t day04_part1(char* input) {
    return find_md5_suffix(input, check_5_zeros);
}

uint32_t day04_part2(char* input) {
    return find_md5_suffix(input, check_6_zeros);
}

bool check_5_zeros(const unsigned char* md5) {
    return (bool)(md5[0] == 0 && md5[1] == 0 && md5[2] < 0x10);
}

bool check_6_zeros(const unsigned char* md5) {
    return (bool)(md5[0] == 0 && md5[1] == 0 && md5[2] == 0);
}

uint32_t find_md5_suffix(char* input, zero_checker check_zeros) {
    uint64_t      base_len = strlen(input);
    char          curr[64];
    unsigned char md5[MD5_DIGEST_LENGTH];
    strcpy(curr, input);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    MD5_CTX base_ctx;
    MD5_Init(&base_ctx);
    MD5_Update(&base_ctx, curr, base_len);

    for (uint32_t suf = 1;; ++suf) {
        size_t curr_len = (size_t)snprintf(curr + base_len, sizeof(curr) - base_len, "%u", suf);

        MD5_CTX curr_ctx = base_ctx;
        MD5_Update(&curr_ctx, curr + base_len, curr_len);
        MD5_Final(md5, &curr_ctx);
#pragma clang diagnostic pop

        if (check_zeros(md5)) {
            return suf;
        }
    }
}
