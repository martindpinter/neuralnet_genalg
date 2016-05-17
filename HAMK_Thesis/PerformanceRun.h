#pragma once
#include "Manager.h"

class PerformanceRun : public Manager {
public:
	PerformanceRun() {}

	virtual bool Simulate(float angle) override;

};