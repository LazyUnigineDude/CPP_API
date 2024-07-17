#include "TriggerExample.h"
REGISTER_COMPONENT(TriggerExample);


static void Enter(const Unigine::NodePtr& Obj) {
	Unigine::Log::message("Object Entered: %s\n", Obj->getName());
}

static void Leave(const Unigine::NodePtr& Obj) {
	Unigine::Log::message("Object Left: %s\n", Obj->getName());
}

void TriggerExample::Move(const Unigine::NodeTriggerPtr& Obj) {
	
	
	if (Label) Label->setText(Unigine::String::format("%.2f %.2f", Obj->getWorldPosition().x, Obj->getWorldPosition().y));
}

static void EnterPhysical(const Unigine::BodyPtr& Body) {
	Unigine::Log::message("Physics Entered\n");
}

static void LeavePhysical(const Unigine::BodyPtr& Body) {
	Unigine::Log::message("Physics Left\n");
}

void TriggerExample::Init() {

	Label = Unigine::WidgetLabel::create(" ");
	Label->setFontSize(21);
	Label->setFontOutline(2);	
	Label->setFontColor(Unigine::Math::vec4_green);

	Unigine::GuiPtr GUI = Unigine::Gui::getCurrent();
	GUI->addChild(Label, GUI->ALIGN_CENTER);

	_NT = Unigine::static_ptr_cast<Unigine::NodeTrigger>(NTNode.get());
	_PT = Unigine::static_ptr_cast<Unigine::PhysicalTrigger>(PTNode.get());
	_WT = Unigine::static_ptr_cast<Unigine::WorldTrigger>(WTNode.get());

	if (_NT) {
		_NT->getEventPosition().connect(this, &TriggerExample::Move);
	}

	if (_PT) {
		_PT->getEventEnter().connect(&EnterPhysical);
		_PT->getEventLeave().connect(&LeavePhysical);
	}

	if (_WT) {
		_WT->getEventEnter().connect(EC, &Enter);
		_WT->getEventLeave().connect(LC, &Leave);
	}  
}

void TriggerExample::Update() {

	if (_PT) _PT->renderVisualizer();
	if (_WT) _WT->renderVisualizer();

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_U)) { EC.disconnectAll(); }
	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_I)) { LC.disconnectAll(); }
}

void TriggerExample::Shutdown() {

	Unigine::GuiPtr GUI = Unigine::Gui::getCurrent();
	if (GUI->isChild(Label)) GUI->removeChild(Label);
	Label.deleteLater();
}