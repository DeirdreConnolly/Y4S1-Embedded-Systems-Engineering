#include "peak.c"
#include <stdio.h>

int streamGet(struct Stream *s, int *finished) {
    *finished = 0;
    //printf("streamGet cnt = %d size =%d\n",s->cnt,s->size);
    if (s->cnt < s->size) {
        // printf("streamGet %d\n",s->buffer[s->cnt]);
        return s->buffer[s->cnt++];
    } else
        *finished = 1;
    return -1;
}

/*
peak examples from
http://sofdem.github.io/gccat/gccat/Cpeak.html
(2,⟨1,1,4,8,6,2,7,1⟩)
(0,⟨1,1,4,4,4,6,7,7⟩)
(4,⟨1,5,4,9,4,6,2,7,6⟩)
*/
main() {

    int data1[] = {1, 1, 4, 8, 6, 2, 7, 1};         // peaks = 8, 7
    int data2[] = {1, 5, 4, 9, 4, 6, 2, 7, 6};      // peaks = 5, 9, 6, 7
    int data3[] = {1, 4, 8, 6, 7, 7, 1, 5, 2, 6};   // valleys = 3
    int data4[] = {1, 5, 5, 4, 3, 5, 2, 2, 7, 4};   // increasing peak = 2
    int data5[] = {1, 5, 9, 4, 3, 5, 2, 2, 7, 4};   //
    struct Stream s;

    // Peaks
    s.buffer = data1;
    s.size = 8;
    s.cnt = 0;

    int val = peak(&s, 2);  // There are 2 peaks in this dataframe
    printf("result for peak({1,1,4,8,6,2,7,1},2) i.e. are there 2 peaks in the data? %d\n", val);


    // Peaks
    s.buffer = data2;
    s.size = 9;
    s.cnt = 0;

    val = peak(&s, 4);  // There are 4 peaks in this dataframe = true = returns 1
    printf("result for peak({1,5,4,9,4,6,2,7,6},4) i.e. are there 4 peaks in the data? %d\n", val);

    s.buffer = data2;
    s.size = 10;
    s.cnt = 0;

    val = peak(&s, 5);  // There are 5 peaks in this dataframe =  false = returns 0
    printf("result for peak({1,5,4,9,4,6,2,7,6},5) i.e. are there 5 peaks in the data? %d\n", val);


    // Valleys
    s.buffer = data3;
    s.size = 10;
    s.cnt = 0;

    val = valley(&s, 3);  // There are 3 valleys in this dataframe = true = returns 1
    printf("result for valley({1, 4, 8, 6, 7, 7, 1, 5, 2, 6},3) i.e. are there 3 valleys in the data? %d\n", val);

    s.buffer = data3;
    s.size = 10;
    s.cnt = 0;

    val = valley(&s, 6);  // There are 6 valleys in this dataframe = false = returns 0
    printf("result for valley({1, 4, 8, 6, 7, 7, 1, 5, 2, 6},6) i.e. are there 6 valleys in the data? %d\n", val);

    // Increasing Peaks
    s.buffer = data4;
    s.size = 10;
    s.cnt = 0;

    val = increasingPeak(&s);  // There are 3 increasing peaks in this dataframe = true = returns 1
    printf("result for increasing peak({1, 5, 5, 4, 3, 5, 2, 2, 7, 4},3) i.e. are there 3 increased peaks in the data? %d\n",
           val);

    s.buffer = data5;
    s.size = 10;
    s.cnt = 0;

    val = increasingPeak(&s);  // There are 5 increasing peaks in this dataframe = false = returns 0
    printf("result for increasing peak({1, 5, 5, 4, 3, 5, 2, 2, 7, 4},5) i.e. are there 5 increased peaks in the data? %d\n",
           val);

}

