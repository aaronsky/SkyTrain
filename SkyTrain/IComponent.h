#pragma once
class IComponent
{
public:
	IComponent();
	~IComponent();
	virtual void Update(float dT) = 0;
};

