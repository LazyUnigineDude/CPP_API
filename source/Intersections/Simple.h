#pragma once
#include <UnigineWorld.h>
#include <UnigineComponentSystem.h>
#include <UnigineVisualizer.h>

struct SimpleDetect : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(SimpleDetect, ComponentBase);
	COMPONENT_INIT(Init);
	COMPONENT_UPDATE(Update);
	COMPONENT_SHUTDOWN(Shutdown);
	
	PROP_PARAM(Mask, MaskVal, 0x02);

protected:
	void Init(), Update(), Shutdown();

private:
	Unigine::WorldIntersectionPtr Ptr;
	Unigine::WidgetLabelPtr Label;
	Unigine::Math::Vec3 P0, P1;
	int Distance = 10;
};