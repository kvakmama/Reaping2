#include "i_core.h"
#include "input/i_input.h"

PlayerController::PlayerController()
: mCurrentMovement(0)
, mDirty(true)
{
	Keyboard& Keys=Keyboard::Get();
	mKeyId=EventServer<KeyEvent>::Get().Subscribe(boost::bind(&PlayerController::OnKeyEvent,this,_1));
	mMouseMoveId=EventServer<MouseMoveEvent>::Get().Subscribe(boost::bind(&PlayerController::OnMouseMoveEvent,this,_1));
	mMousePressId=EventServer<MousePressEvent>::Get().Subscribe(boost::bind(&PlayerController::OnMousePressEvent,this,_1));
}

void PlayerController::OnKeyEvent(const KeyEvent& Event)
{
	uint32_t OldMovement=mCurrentMovement;
	uint32_t Mod=0;
	if(Event.Key==GLFW_KEY_W)Mod=MF_Up;
	else if(Event.Key==GLFW_KEY_A)Mod=MF_Left;
	else if(Event.Key==GLFW_KEY_S)Mod=MF_Down;
	else if(Event.Key==GLFW_KEY_D)Mod=MF_Right;
	if(Event.State==KeyState::Down)
		mCurrentMovement|=Mod;
	else
		mCurrentMovement&=~Mod;
	mDirty=mDirty||mCurrentMovement!=OldMovement;
}

void PlayerController::Update( double Seconds )
{
	UpdateRotation();
	if(!mActor)return;
	if(!mDirty)return;
	mDirty=false;
	int x=((mCurrentMovement&MF_Left)?-1:0)+((mCurrentMovement&MF_Right)?1:0);
	int y=((mCurrentMovement&MF_Up)?1:0)+((mCurrentMovement&MF_Down)?-1:0);
	mActor->SetSpeed(std::max<double>(std::abs(x),std::abs(y))*.35);
	if(x==0&&y==0)return;
	double Heading=0;
	static const double pi=boost::math::constants::pi<double>();
	if(x==0)
		Heading=(y<0)?-pi/2:pi/2;
	else if(y==0)
		Heading=(x<0)?-pi:0;
	else if(y>0)
		Heading=(x<0)?pi*0.75:pi/4;
	else
		Heading=(x<0)?pi*1.25:pi*1.75;

	mActor->SetHeading(Heading);
}

PlayerController::~PlayerController()
{
}

void PlayerController::OnMouseMoveEvent(const MouseMoveEvent& Event)
{
	mX=Event.Pos.x;
	mY=Event.Pos.y;
	UpdateRotation();
}

void PlayerController::UpdateRotation()
{
	double Rot=atan2(mY-mActor->GetY(),mX-mActor->GetX());
	mActor->SetOrientation(Rot);
}

void PlayerController::OnMousePressEvent(const MousePressEvent& Event)
{
	// ez itt pusztan funkcionalitas tesztelesre van, dummy implementacio
	static const double Cooldown=0.2;
	static double PrevTime=0;
	const double CurTime=glfwGetTime();
	if(CurTime-PrevTime<Cooldown) return;
	PrevTime=CurTime;
	if (Event.Button==Mouse::Button_Right) Scene::Get().AddActor(new Creep(mActor,Event.Pos.x,Event.Pos.y));
	else Scene::Get().AddActor(new Creep(Event.Pos.x,Event.Pos.y));
}
