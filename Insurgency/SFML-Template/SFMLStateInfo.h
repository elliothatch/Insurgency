#pragma once
#include <memory>
class SFMLStateInfo
{
public:
	typedef std::unique_ptr<SFMLStateInfo> ptr;
	SFMLStateInfo(void){}
	virtual ~SFMLStateInfo(void){}
};

class InventoryComponent;
class SFMLStateInfo_InventoryComponent :public SFMLStateInfo
{
public:
	SFMLStateInfo_InventoryComponent(InventoryComponent* lInvComponent)
		:m_invComponent(lInvComponent) {}
	virtual ~SFMLStateInfo_InventoryComponent() {}
	InventoryComponent* m_invComponent;
};
