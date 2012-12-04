#pragma once
#include <memory>
class SFMLStateInfo
{
public:
	typedef std::unique_ptr<SFMLStateInfo> ptr;
	SFMLStateInfo(void){}
	virtual ~SFMLStateInfo(void){}
};