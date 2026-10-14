
#include "app/app.h"

int main(int argc, char *argv[]) {
    sk_app_t app;
    if (run(&app) != 0) {
        return -1; 
    }
	return 0;
}
