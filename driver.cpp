#include "driver.h"

Driver::Driver() {

}
Driver::~Driver(){

}
void Driver::activate(){

}
void Driver::deactivate(){

}
uint32_t Driver::reset() {
	return 0;
}

DriverManager::DriverManager() {
	driverCount = 0;
}
void DriverManager::addDriver(Driver* driver) {
	drivers[driverCount] = driver;
	driverCount++;
};
void DriverManager::activateAll() {
	for(int i = 0; i < driverCount; i++) {
		drivers[i]->activate();
	}
}