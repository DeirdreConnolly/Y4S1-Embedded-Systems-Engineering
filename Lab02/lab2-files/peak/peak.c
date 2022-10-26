#include <stdio.h>
#include "Stream.h"

int peak(struct Stream *s, int n) {

    int prev;
    int c = 0;
    int state = 0;
    int finish = 0;
//printf("peak1 cnt = %d size =%d\n",s->cnt,s->size);
    if (n == 0) return 0;
    prev = streamGet(s, &finish);
//printf("peak2 cnt = %d size =%d\n",s->cnt,s->size);
    if (finish) return 0;
    int curr = streamGet(s, &finish);
    while (!finish && c < n) {
//printf("here1 state = %d\n",state);
//printf("peak3 c=%d cnt = %d size =%d\n",c,s->cnt,s->size);
        switch (state) {
            case 0:
                if (prev < curr)
                    state = 1;
                break;
            case 1:
                if (prev > curr) {
                    state = 0;
                    c++; // found a peak
                }
                break;
        }
        prev = curr;
        curr = streamGet(s, &finish);
    }

    // n refers to number of peaks we are checking that dataframe against
    if (c == n) return 1;   // peak will return 1 or 0, i.e. true or false
    return 0;
}


int valley(struct Stream *s, int n) {

    int prev;
    int c = 0;
    int state = 0;
    int finish = 0;
//printf("peak1 cnt = %d size =%d\n",s->cnt,s->size);
    if (n == 0) return 0;
    prev = streamGet(s, &finish);
//printf("peak2 cnt = %d size =%d\n",s->cnt,s->size);
    if (finish) return 0;
    int curr = streamGet(s, &finish);
    while (!finish && c < n) {
//printf("here1 state = %d\n",state);
//printf("peak3 c=%d cnt = %d size =%d\n",c,s->cnt,s->size);
        switch (state) {
            case 0:
                if (prev > curr)
                    state = 1;
                break;
            case 1:
                if (prev < curr) {
                    state = 0;
                    c++; // found a valley
                }
                break;
        }
        prev = curr;
        curr = streamGet(s, &finish);
    }

    // n refers to number of valley we are checking that dataframe against
    if (c == n) return 1;   // valley will return 1 or 0, i.e. true or false
    return 0;
}


int increasingPeak(struct Stream *s) {

    int prev;
    int state = 0;
    int finish = 0;
    int prevPeak = 0;
//printf("peak1 cnt = %d size =%d\n",s->cnt,s->size);
    prev = streamGet(s, &finish);
//printf("peak2 cnt = %d size =%d\n",s->cnt,s->size);
    if (finish) return 0;
    int curr = streamGet(s, &finish);
    while (!finish) {
//printf("here1 state = %d\n",state);
//printf("peak3 c=%d cnt = %d size =%d\n",c,s->cnt,s->size);
        switch (state) {
            case 0:
                if (prev < curr)
                    state = 1;  // Left side of mountain
                break;

            case 1:
                if (prev >= curr) { // We have a peak

                    if (prev >= prevPeak) {
                        prevPeak = prev;

                    } else {
                        return 0;   // If peak is smaller than previous peaks, it cannot be an increasing peak, so we ends the loop
                    }
                    state = 0;      // Right side of mountain

                }
                break;


        }
        prev = curr;
        curr = streamGet(s, &finish);
    }

    // n refers to number of increasing peaks we are checking that dataframe against
    return 1;   // increasing peaks will return 1 or 0, i.e. true or false

    // If there are no increasing peaks, return 0, break and stop
}




