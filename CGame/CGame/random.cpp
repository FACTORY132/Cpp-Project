#define cast static_cast

#include <math.h>
#include <stdlib.h>
#include "random.h"


double random() {
	double old = 0.00003014;
	return cast<double>(rand()) * old;
}

double next(int bits) {
	return random() * (pow(2, bits - 1) - 1);
}

int next_int() {
	return  cast<int>(next(32));
}

int next_int(int max) {
	return cast<int>((random() * (max + 1) - 1));
}

int next_int(int min, int max) {
	return cast<int>((random() * (max - min + 1) + 1) + min - 1);
}

long next_long() {
	return cast<long>(next(64));
}

long next_long(long max) {
	return cast<long>(next_int(max));
}

long next_long(long min, long max) {
	return cast<long>(next_int(min, max));
}

float next_float() {
	return cast<float>(next(32));
}

float next_float(float max) {
	return cast<float>(next_int(max));
}

float next_float(float min, float max) {
	return cast<float>(next_int(min, max));
}

double next_double() {
	return next(64);
}

double next_double(double max) {
	return cast<double>(next_long(max));
}

double  next_double(double min, double max) {
	return cast<double>(next_long(min, max));
}

bool chance(double percent) {
	return random() <= percent / 100;
}

bool next_bool() {
	return chance(50);
}
