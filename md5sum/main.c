#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

static int calculate_md5sum(const char *fileName, unsigned char *digest) {
    FILE *fp;
    MD5_CTX mdContext;
    int bytes;
    unsigned char buffer[1024];
    unsigned char result[MD5_DIGEST_LENGTH];

    fp = fopen(fileName, "rb");
    if (!fp) {
	printf("Open file failed\n");
	return -1;
    }

    MD5_Init(&mdContext);
    while ((bytes = fread(buffer, 1, 1024, fp)) != 0) {
        MD5_Update(&mdContext, buffer, bytes);
    }
    MD5_Final(digest, &mdContext);

    fclose(fp);

    return 0;
}

int main() {
	unsigned char md5Result[MD5_DIGEST_LENGTH];

	if (calculate_md5sum("test.txt", md5Result)) {
		printf("Failed to md5sum\n");
	} else {
		printf("MD5SUM: ");
		for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
			printf("%02x", md5Result[i]);
		}
		printf("\n");
	}
	

	return 0;
}
