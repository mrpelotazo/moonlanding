#include "eagle.hpp"

using namespace std;

CEagle::CEagle(float px, float py) {
	posx = px;
	posy = py;
	velx = 0.0;
	vely = 0.0;
	accx = 0.0;
	accy = 0.0;
	ang = 0.0;
	fuel = 100.0;
	oxigen = 100.0;
	rotleft = 0;
	rotright = 0;
	mainthrust = OFF_MAIN_THRUST;
}

float CEagle::getPosx() {
	return posx;
}

float CEagle::getPosy() {
	return posy;
}

float CEagle::getRawAngDeg() {
	return radToDeg(ang);
}

float CEagle::getPrintAngDeg() {

	if ((ang > PI) && (ang < (2 * PI)))
		return radToDeg(ang - (2 * PI));

	return radToDeg(ang);
}

unsigned short CEagle::getPrintThrust() {
	return mainThrustToPerc(mainthrust);
}

void CEagle::rotLeft(float d) {
	ang = normAng((((2 * PI) + ang) - degToRad(d)));
}

void CEagle::rotRight(float d) {
	ang = normAng(ang + degToRad(d));
}

void CEagle::actRotLeft() {
	rotleft = 1;
}

void CEagle::deactRotLeft() {
	rotleft = 0;
}

void CEagle::actRotRight() {
	rotright = 1;
}

void CEagle::deactRotRight() {
	rotright = 0;
}

short CEagle::actMainEngine(short e) {
	if (fuel > 0) {
		switch (e) {
			case 0:
				mainthrust = LOW_MAIN_THRUST;
				break;
			case 1:
				mainthrust = MID_MAIN_THRUST;
				break;
			case 2:
				mainthrust = MAX_MAIN_THRUST;
				break;
			default:
				return -1;
				break;
		}
	}
	return 0;
}

void CEagle::deactMainEngine() {
	mainthrust = OFF_MAIN_THRUST;
}

unsigned short CEagle::getMainEngineStatus() {
	return mainthrust;
}

unsigned short CEagle::update(unsigned short td) {
	float tdsecs;

	if (rotleft) {
		rotLeft(0.1);
	}
	if (rotright) {
		rotRight(0.1);
	}

	/* time delta to secs */
	tdsecs = td / 1000.0;

	/* update position, velocity and acceleration */
	posx += velx * tdsecs;
	posy += vely * tdsecs;
	velx += accx * tdsecs;
	vely += accy * tdsecs;
	accx = mainthrust * sin(ang) / SHIP_MASS;
	accy = (mainthrust * cos(ang) - (SHIP_MASS * MOON_ACC)) / SHIP_MASS;

	/* update fuel */
	if (fuel > 0.0) {
		fuel -= (float)(mainthrust) / (float)(MAX_MAIN_THRUST) * tdsecs;
		if (fuel < 0.0) {
			fuel = 0.0;

		}
	}

	/* if run out of fuel deactivate the engine */
	if ((fuel == 0) && (getMainEngineStatus())) {
		deactMainEngine();
	}

	/* update oxigen */
	if (oxigen > 0.0) {
		oxigen -= tdsecs / 100.0;
		if (oxigen < 0.0) {
			oxigen = 0;
		}
	}
}

char* CEagle::getShipInfoStr(char *s) {
	sprintf(s, "PosX  :%7.2f PosY  :%7.2f VelX  :%7.2f VelY  :%7.2f Angle  :%7.2f\nThrust:%7u Fuel  :%7.2f Oxigen:%7.2f\0", posx, posy, velx, vely, getPrintAngDeg(), fuel, oxigen, getPrintThrust());
	return s;
}

void CEagle::showTermInfo() {
	printf("PosX  :%7.2f  PosY  :%7.2f\n", posx, posy);
	printf("VelX  :%7.2f  VelY  :%7.2f  Ang   :%7.2f\n", velx, vely, getPrintAngDeg());
	printf("Fuel  :%7.2f  Oxigen:%7.2f\n", fuel, oxigen);
	printf("Thrust:%7u\n", getPrintThrust());
}

/* Private methodes */
float CEagle::degToRad(float a) {
	return a / DEG;
}

float CEagle::radToDeg(float a) {
	return a * DEG;
}

float CEagle::normAng(float a) {
	return fmod(a, (float)(2 * PI));
}

unsigned short CEagle::mainThrustToPerc(unsigned short t) {
	unsigned short retval;
	switch (t) {
		case MAX_MAIN_THRUST:
			retval = 100;
			break;
		case MID_MAIN_THRUST:
			retval = 60;
			break;
		case LOW_MAIN_THRUST:
			retval = 10;
			break;
		case OFF_MAIN_THRUST:
			retval = 0;
			break;
		default:
			retval = -1;
	}
	return retval;
}
