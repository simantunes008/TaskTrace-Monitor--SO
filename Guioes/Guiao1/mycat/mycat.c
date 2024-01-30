#include "mycat.h"

/*EOP = CTRL+D*/

int mycat() {
    int read_bytes = 0;
    char buf[20];

    while ((read_bytes = read(STDIN_FILENO, buf,20)) > 0) {
        write(STDOUT_FILENO, buf, read_bytes);
    }

    return 0;
}

int main (int argc, char const * argv[]) {
    return mycat();
}
