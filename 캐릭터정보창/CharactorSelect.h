#pragma once
#include "Player.h"
class Card;
class CharactorSelect:public gameNode
{
private:
	typedef vector<Card *> vCards;
private:
	image * _backGround;
	int _width, _height;
	// ī�� ���� vector
	vCards _cards;
	// �� ���콺�� ī�忡 ��Ҵ��� ����
	RECT _mouseRect;
protected:
	// ĳ���͸� ������� Ȯ���Ѵ�.
	void check_chooseCharactor();
	// ���콺�� ī�� �浹
	void check_clickCard();
	void check_mouseOnCard();
	RECT make_mouseRect();
	// ī��
	void init_cards();
	void delete_cardsAll();
	void update_cards();
	void draw_cards();
public:
	CharactorSelect();
	~CharactorSelect();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

class Card : public gameNode
{
private:
	image * _backImg;
	image * _frontImg;
	string _type;
	int _width, _height;
	RECT _rect;
	// ���콺�� ī�忡 ������
	int _alpha;
	bool _fMouseOnCard;
	// ī�尡 �����Ÿ��� ���� ����
	bool _fClickCard;
	bool _fBlink;
	int _blinkCounter;
	int _blinkDelay;
	int _blinkTimer;
	// ĳ���͸� �������
	bool _fChooseCharactor;
protected:
	// ī�� �����̱�
	void blink_card();
public:
	// �� �ٲܶ�
	bool is_chooseCharactor() { return _fChooseCharactor; }
	// ���콺�� ī�忡 ������
	void init_forBlink();
	void set_fClickCard(bool fResult) { _fClickCard = fResult; }
	void set_fMouseOnCard(bool fResult) { _fMouseOnCard = fResult; }
	// ī�� ��ġ�� RECT�� �ѱ��.
	RECT get_rect() { return _rect; }
	// Ÿ���� �޾Ƽ� ī�带 �����.
	void init_card(string type);
	string get_type() { return _type; }
public:
	Card();
	~Card();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};