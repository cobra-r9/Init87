#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("./output/out1.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[128];
    ssize_t bytes;

    while ((bytes = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[bytes] = '\0';
        printf("%s", buf);
    }

    close(fd);
    return 0;
}
