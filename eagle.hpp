#include <cstdio>
#include <cstring>
#include <ctgmath>

#define DEG 57.2957           /* 1rad = 57,29deg */
#define PI 3.1415
#define MOON_ACC 1.622        /* Moon acceleration [m/s^2]*/
#define MAX_MAIN_THRUST 45000 /* Max mainthrust [N] */
#define MID_MAIN_THRUST 27000 /* 60% mainthrust */
#define LOW_MAIN_THRUST 4500  /* 10% mainthrust */
#define OFF_MAIN_THRUST 0
#define SHIP_MASS 15000       /* The ship mass [kg] */


class CEagle {

	public:
		/* constructor */
		CEagle(float px, float py);

		/* get the ship x position */
		float getPosx();

		/* get the ship y position */
		float getPosy();

		/* get the raw angle in deg [0, +359]*/
		float getRawAngDeg();

		/* get printable angle in deg: [-180, +180] */
		float getPrintAngDeg();

		/* get a printable thrust in %: [0, 100] */
		unsigned short getPrintThrust();

		/* rotate d DEG left */
		void rotLeft(float d);

		/* rotate d DEG right */
		void rotRight(float d);

		/* activate left rotation */
		void actRotLeft();

		/* deactivate left rotation */
		void deactRotLeft();

		/* activate right rotation */
		void actRotRight();

		/* deactivate right rotation */
		void deactRotRight();

		/* activate main engine */
		short actMainEngine(short e);

		/* deactivate thrust */
		void deactMainEngine();

		/* get the main engine state */
		unsigned short getMainEngineStatus();

		/* update ship state */
		unsigned short update(unsigned short td);

		/* Get s string containing the ship status info */
		char* getShipInfoStr(char *s);

		/* show ship info */
		void showTermInfo();

	private:
		/* class atributes */
		float posx;
		float posy;
		float velx;
		float vely;
		float accx;
		float accy;
		float ang;
		float fuel;
		float oxigen;
		unsigned short rotleft;
		unsigned short rotright;
		unsigned short mainthrust;

		/* private methodes */
		float degToRad(float a);
		float radToDeg(float a);
		float normAng(float a);
		unsigned short mainThrustToPerc(unsigned short t);
};
