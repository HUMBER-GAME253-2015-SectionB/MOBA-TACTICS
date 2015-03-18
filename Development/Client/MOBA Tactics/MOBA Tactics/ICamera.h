//Author:	Mathieu Violette
//Date:		3/18/2015(MV)

#ifndef ICAMERA_H
#define ICAMERA_H

class ICamera
{
public:
	virtual ~ICamera() = 0;
};

inline ICamera::~ICamera(){}

#endif