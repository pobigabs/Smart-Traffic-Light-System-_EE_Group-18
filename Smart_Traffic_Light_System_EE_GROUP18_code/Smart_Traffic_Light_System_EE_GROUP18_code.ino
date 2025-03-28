// Smart Traffic Light System with Dynamic Congestion Control

const int trigPins[4] = {8, 10, 12, A0};
const int echoPins[4] = {9, 11, 13,A1};
const int redPins[4] = {2, 5, A2, A7};
const int yellowPins[4] = {3, 6, A3, A6};
const int greenPins[4] = {4, 7, A4, A5};

const int greenTimeBase = 5000; // Minimum green time (5s)
const int extraTimePerCar = 500; // Additional time per car (0.5s)
const int maxGreenTime = 20000; // Max green time (20s)
const int detectionThreshold = 50; // Vehicle detection range (cm)
const int cycleTime = 30000; // 30s cycle time

int vehicleCounts[4] = {0, 0, 0, 0};
bool prevDetection[4] = {false, false, false, false};
unsigned long lastCheckTime = 0;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 4; i++) {
        pinMode(trigPins[i], OUTPUT);
        pinMode(echoPins[i], INPUT);
        pinMode(redPins[i], OUTPUT);
        pinMode(yellowPins[i], OUTPUT);
        pinMode(greenPins[i], OUTPUT);
        digitalWrite(redPins[i], HIGH); // Start with all red
    }
    lastCheckTime = millis();
}

long getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH, 30000);
    return (duration == 0) ? 9999 : duration * 0.034 / 2;
}

void updateVehicleCounts() {
    for (int i = 0; i < 4; i++) {
        bool currentDetection = (getDistance(trigPins[i], echoPins[i]) <= detectionThreshold);
        if (currentDetection && !prevDetection[i]) {
            vehicleCounts[i]++;
        }
        prevDetection[i] = currentDetection;
    }
}

void displayVehicleCounts() {
    Serial.println("\nVehicle Counts:");
    for (int i = 0; i < 4; i++) {
        Serial.print("Lane "); Serial.print(i + 1);
        Serial.print(": "); Serial.println(vehicleCounts[i]);
    }
}

void getMostCongestedLanes(bool lanes[4]) {
    int maxCount = -1;
    for (int i = 0; i < 4; i++) {
        if (vehicleCounts[i] > maxCount) {
            maxCount = vehicleCounts[i];
        }
    }
    for (int i = 0; i < 4; i++) {
        lanes[i] = (vehicleCounts[i] == maxCount && maxCount > 0);
    }
}

void resetTrafficLights() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(redPins[i], LOW);
        digitalWrite(yellowPins[i], LOW);
        digitalWrite(greenPins[i], LOW);
    }
}

void controlTraffic() {
    bool lanes[4] = {false, false, false, false};
    getMostCongestedLanes(lanes);

    bool anyLaneActive = false;
    for (int i = 0; i < 4; i++) {
        if (lanes[i]) {
            anyLaneActive = true;
            int greenTime = min(greenTimeBase + vehicleCounts[i] * extraTimePerCar, maxGreenTime);
            resetTrafficLights();
            digitalWrite(redPins[i], LOW);
            digitalWrite(greenPins[i], HIGH);
            delay(greenTime);
            digitalWrite(greenPins[i], LOW);
            digitalWrite(yellowPins[i], HIGH);
            delay(3000);
            digitalWrite(yellowPins[i], LOW);
            digitalWrite(redPins[i], HIGH);
        }
    }
    if (!anyLaneActive) {
        Serial.println("No vehicles detected. Turning off all lights.");
        resetTrafficLights();
    }
}

void loop() {
    updateVehicleCounts();
    if (millis() - lastCheckTime >= cycleTime) {
        displayVehicleCounts();
        controlTraffic();
        memset(vehicleCounts, 0, sizeof(vehicleCounts));
        lastCheckTime = millis();
    }
}
