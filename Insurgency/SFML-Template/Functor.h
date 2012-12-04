#pragma once
class GameStateBase;

class TFunctorBase
{
public:
	TFunctorBase(void) {}
	virtual ~TFunctorBase(void) {}
	virtual void operator()(void) = 0;
	virtual bool equals(const TFunctorBase& rhs) const = 0;
};

// derived template class
template <class TClass> class TFunctor : public TFunctorBase
{
private:
	void (TClass::*fpt)();   // pointer to member function
	TClass* pt2Object;                  // pointer to object

public:
	TFunctor(TClass* _pt2Object, void(TClass::*_fpt)())
	{ pt2Object = _pt2Object; fpt = _fpt;};

	virtual void operator()(void)
	{ (*pt2Object.*fpt)();};              // execute member function

	virtual bool equals(const TFunctorBase& rhs) const
	{
		const TFunctor<TClass>* obj = dynamic_cast<const TFunctor<TClass>*>(&rhs);
		if(obj == nullptr)
			return false;
		return (obj->fpt == fpt && obj->pt2Object == pt2Object);
	}
};