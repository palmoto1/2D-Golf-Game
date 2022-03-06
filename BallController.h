#ifndef PROJECTILEINPUTHANDLER_H
#define PROJECTILEINPUTHANDLER_H
#include "Component.h"
#include "Ball.h"


/*handles ball inputs*/

class BallController: public Component
{
public:

	void initialize() override;
	void update() override;

	void reset();
	void setAble(bool able);

	

private:
	Ball* ball;

	Uint32 mouseDown = 0u;
	Uint32 mouseUp = 0u;

	bool able;

};

#endif

