#include <SST.h>

// Blue LED, indicator
//uint8_t LEDpin = D4;
//bool LEDstatus = HIGH;

const int NUM_IN_PORTS = 0;
const int inPorts[NUM_IN_PORTS] = {
    // Tere is no input port configured
};

const int NUM_OUT_PORTS = 4;
const int outPorts[NUM_OUT_PORTS] = {
    D5, // The output to RELAY-1
    D6, // The output to RELAY-2
    D7, // The output to RELAY-3
    D4  // The output to RELAY-4
};

void setupIoPorts(void) {
    Serial.println("Setup I/O ports for relays");

    // Set port modes, and reset out ports
    for ( int p = 0; p < NUM_IN_PORTS; p++) {
        pinMode(inPorts[p], INPUT);
    }

    for ( int p = 0; p < NUM_OUT_PORTS; p++) {
        pinMode(outPorts[p], OUTPUT);
        digitalWrite(outPorts[p], HIGH);
    }
}

void stateChangeCb(int portIdx, enum SstState portState); // Needed because the strange way how arduino handles the enum declarations
void stateChangeCb(int portIdx, enum SstState portState) {
    Serial.println("stateChangeCb port: " + String(portIdx) + " state: " + ((portState == ON) ? "ON" : "OFF"));
    digitalWrite(outPorts[portIdx], (portState==ON) ? LOW : HIGH);
}

SST relays[] = {
    SST(0, stateChangeCb, getTimeOfDay),
    SST(1, stateChangeCb, getTimeOfDay),
    SST(2, stateChangeCb, getTimeOfDay),
    SST(3, stateChangeCb, getTimeOfDay)
};

#define numberOfRelays (sizeof(relays)/sizeof(SST))

void resetRelays(void) {
    Serial.println("Reset the relay control SST channels");
    // Update the relays one-by-one
    for(int s=0; s<numberOfRelays; s++) {
        relays[s].reset();
    }
}

void reset(const char* buf) {
    resetRelays();
    //setupRelays();
    //operations.responseOk(buf, 0L);
}

void setupSstRelays() {
    Serial.println("Setup SST Relays");

    // Setup the I/O ports
    setupIoPorts();

    // Reset the relay control SST channels
    resetRelays();

    // TODO: Replace this fixed settings with dynamic configuration
    // relays[0].set(0, AUTO, 7, 1, 7, 2);
    // relays[1].set(1, AUTO, 7, 2, 7, 3);
    // relays[2].set(2, AUTO, 7, 3, 7, 4);
    // relays[3].set(3, AUTO, 7, 4, 7, 5);

    // KERT_1
    relays[0].set(0, AUTO, 8, 0, 9, 29);
    relays[1].set(1, AUTO, 8, 1, 9, 29);
    relays[2].set(2, AUTO, 9, 30, 11, 0);
    relays[3].set(3, AUTO, 9, 31, 11, 0);

    // KERT_2
    // relays[0].set(0, AUTO, 5, 0, 6, 29);
    // relays[1].set(1, AUTO, 5, 1, 6, 29);
    // relays[2].set(2, AUTO, 6, 30, 7, 59);
    // relays[3].set(3, AUTO, 6, 31, 7, 59);
}

/** Update SST Relay channels */
void updateSstRelays(void) {
    Serial.println("Update SST Relay channels at " + getTimeStr());
    for(int s=0; s<numberOfRelays; s++) {
        relays[s].update();
    }
}
