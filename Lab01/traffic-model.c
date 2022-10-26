#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>

/* NOTES
 *
 * State:           Describes which road has authority
 * Goal:            Prevent southbound cars to enter the intersection at the same time as westbound cars
 * Light pattern:   Defines which road has right of way over the other
 * Two inputs:      Car sensors on North and East roads, connected to Port E bits 1–0
 * Six outputs:     One for each light in the traffic signal, interfaced to Port B bits 5–0
 *
 * PE1=0, PE0=0     No cars exist on either road
 * PE1=0, PE0=1     There are cars on the East road
 * PE1=1, PE0=0     There are cars on the North road
 * PE1=1, PE0=1     There are cars on both roads
 *
 * goN,             PB5-0 = 100001      Green on North and red on East
 * waitN,           PB5-0 = 100010      Yellow on North and red on East
 * goE,             PB5-0 = 001100      Red on North and green on East
 * waitE,           PB5-0 = 010100      Red on North and yellow on East
 *
 * If no cars are coming, stay in a green state, but which one doesn't matter
 * To change from green to red, implement a yellow light of exactly 5 seconds
 * Green lights will last at least 30 seconds
 * If cars are only coming in one direction, move to and stay green in that direction
 * If cars are coming in both directions, cycle through all four states
 *
 * 1. Initialize timer and direction registers
 * 2. Specify initial state
 * 3. Perform FSM controller
 *      a) Output to traffic lights, which depends on the state
 *      b) Delay, which depends on the state
 *      c) Input from sensors
 *      d) Change states, which depends on the state and the input
 *
 *
 * */





struct State {
    unsigned long Out;
    unsigned long Time;
    unsigned long Next[4];
};
typedef const struct State STyp;

#define goN   0     // PB5-0 = 100001   Green on North and red on East
#define waitN 1     // PB5-0 = 100010   Yellow on North and red on East
#define goE   2     // PB5-0 = 001100   Red on North and green on East
#define waitE 3     // PB5-0 = 010100   Red on North and yellow on East

STyp FSM[4] = {
        {0x21, 3000, {goN, waitN, goN,   waitN}},
        {0x22, 500,  {goE, goE,   goE,   goE}},
        {0x0C, 3000, {goE, goE,   waitE, waitE}},
        {0x14, 500,  {goN, goN,   goN,   goN}}};

unsigned long S;  // index to the current state

unsigned long Input = 0;


// cc.byexamples.com calls this int kbhit(), to mirror the Windows console
//  function of the same name.  Otherwise, the code is the same.
int inputAvailable() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return (FD_ISSET(0, &fds));
}

int main() {
    char data[200];
    int oldOutput = 0;

    S = goN;
    while (1) {
        usleep(100);

        /* add in here your emulation of the code */

/* TODO replace the following line with a printf of the current value of lights
        The value of the lights is in FSM[S].Out */

        // Convert hex to bin
        // 0x21     0x22    0x0C    0x14
        // 100001   100010  001100  010100

//        LIGHT = FSM[S].Out;
        unsigned long hex = FSM[S].Out;

        if (oldOutput == 1) {
            // Using bit-wise operator
            if (hex & 1) {          // Triggers S[0] only
                printf("Green on North and red on East\n");
            } else if (hex & 2) {   // Triggers S[1] only
                printf("Yellow on North and red on East\n");
            } else if (hex & 8) {   // Triggers S[2] only
                printf("Red on North and green on East\n");
            } else if (hex & 16) {  // Triggers S[3] only
                printf("Red on North and yellow on East\n");
            }
            oldOutput = 0;
        }



        //  SysTick_Wait10ms(FSM[S].Time);   // no need of this line in initial testing
        // use usleep() instead of Syst=Tick_Wait

        //Input = SENSOR;             // read sensors the input value is set in the
        // if statement below

        if (inputAvailable()) {
            Input = 0;
            scanf("%s", data);
//                printf("you entered %s\n", data);

/* TODO  Set the input value to 00 or 01 or 10 or 11 binary i.e. 0,1,2,3 decimal depending on the input.
         For example If the user enters N set Input to 2 decimal i.e. 10 binary. */

            if (data[0] == 'N') {
                Input = 2;
            } else if (data[0] == 'E') {
                Input = 1;
            } else if (data[0] == 'B') {
                Input = 3;
            } else {
                Input = 0;
            }
        }
        S = FSM[S].Next[Input];     // keep this line as is
    }
}
