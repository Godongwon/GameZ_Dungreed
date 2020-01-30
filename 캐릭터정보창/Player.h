#pragma once
#include "singletonBase.h"
#include "gameNode.h"

class Player: public singletonBase<Player>, public gameNode
{
private:
	image * _img;
	RECT _rect;
	string _type;
protected:
	void init_gobugi();
	void init_pikachu();
	void init_hanuts();
	void delete_img();
public:
	// ��� �÷��̾ �ε����� �޴´�.
	void set_type(string str) { _type = str; }
public:
	Player();
	~Player();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
#define PLAYER				Player::getSingleton()
