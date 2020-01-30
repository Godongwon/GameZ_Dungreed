#include "stdafx.h"
#include "CharactorSelect.h"
//============================================
//##			ĳ���� ���þ�					##
//============================================
void CharactorSelect::check_chooseCharactor()
{
	auto iter = _cards.begin();
	for (;iter != _cards.end();iter++)
	{
		if ((*iter)->is_chooseCharactor() == true)
		{
//============================================
//##			�� ü����						##
//============================================
			PLAYER->set_type((*iter)->get_type());
			SCENEMANAGER->changeScene("TownScene");
			break;
		}// ĳ���͸� ����ٸ�
	}
}
void CharactorSelect::check_clickCard()
{
	make_mouseRect();
	auto iter = _cards.begin();
	for (;iter != _cards.end();iter++)
	{
		if (IntersectRect(&RECT(), &_mouseRect, &(*iter)->get_rect()))
		{
			(*iter)->set_fClickCard(true);
		}// ���� ī�带 Ŭ���ϸ�
	}
}
void CharactorSelect::check_mouseOnCard()
{
	make_mouseRect();
	auto iter = _cards.begin();
	for (;iter != _cards.end();iter++)
	{
		if (IntersectRect(&RECT(), &_mouseRect, &(*iter)->get_rect()))
		{
			(*iter)->set_fMouseOnCard(true);
		}// ���� ī�忡 ���콺�� ���
	}
}
RECT CharactorSelect::make_mouseRect()
{
	_mouseRect = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, 5, 5);
	return _mouseRect;
}
void CharactorSelect::init_cards()
{
	Card * card;
	card = new Card;
	card->init();
	card->init_card("Gobugi");
	_cards.push_back(card);
	card = nullptr;
	card = new Card;
	card->init();
	card->init_card("Pikachu");
	_cards.push_back(card);
	card = nullptr;
	card = new Card;
	card->init();
	card->init_card("Hanuts");
	_cards.push_back(card);
	card = nullptr;
}
void CharactorSelect::delete_cardsAll()
{
	auto iter = _cards.begin();
	for (;iter != _cards.end();)
	{
		(*iter)->release();
		iter = _cards.erase(iter);
	}
	swap(_cards, vCards());
}
void CharactorSelect::update_cards()
{
	auto iter = _cards.begin();
	for (;iter != _cards.end();iter++)
	{
		(*iter)->update();
	}
}
void CharactorSelect::draw_cards()
{
	auto iter = _cards.begin();
	for (;iter != _cards.end();iter++)
	{
		(*iter)->render();
	}
}
CharactorSelect::CharactorSelect()
{
}
CharactorSelect::~CharactorSelect()
{
}
HRESULT CharactorSelect::init()
{
	_width = 1024;
	_height = 694;
	_backGround = IMAGEMANAGER->addImage("BackGround",
		"images/CharactorSelect/BackGround.bmp", _width, _height, false, RGB(255, 0, 255));
	init_cards();
	return S_OK;
}
void CharactorSelect::release()
{
	// ����� ī�带 �����.
	delete_cardsAll();
	// ����� ������.
	IMAGEMANAGER->deleteImage("BackGround");
	_backGround = nullptr;
}
void CharactorSelect::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		check_clickCard();
	}
	else
	{
		check_mouseOnCard();
	}
	// ĳ���͸� ����ٸ� ���� �ٲ۴�.
	check_chooseCharactor();
	// ī�� ������Ʈ
	update_cards();
}
void CharactorSelect::render()
{
	_backGround->render(getMemDC(), 0, (int)((WINSIZEY - _height)*0.5));
	draw_cards();
}
//============================================
//##		ī�带 �����ϴ� Ŭ����				##
//============================================
void Card::blink_card()
{
	_blinkCounter++;
	_blinkTimer--;
	if (_blinkCounter >= _blinkDelay)
	{
//============================================
//##			ī�� �����̱�					##
//============================================
		if (_fBlink == false) { _alpha = 180; }
		else { _alpha = 255; } // _fBlink�� false�� _alpha�� 255
		_fBlink = !_fBlink;
		_blinkCounter = 0;
	}
}
void Card::init_forBlink()
{
	_fClickCard = false;
	_fBlink = false;
	_blinkCounter = 0;
	_blinkDelay = 10;
	_blinkTimer = 90;
}
void Card::init_card(string type)
{
	// Ÿ�԰� ������ǥ, �󸶳� �� ������� ���Ѵ�.
	_type = type;
	_rect = RectMakeCenter((int)(WINSIZEX*0.5), (int)(WINSIZEY*0.5),
		_width, _height);
	double blank = (WINSIZEX - _width * 3) * 0.25;
	// front �̹����� ��ǥ�� ��Ƽ� RECT�� �����Ѵ�.
	RECT frontRect;
	if (type.compare("Gobugi") == 0)
	{
		_rect.left -= (int)(blank + _width);
		_rect.right -= (int)(blank + _width);
		_frontImg = IMAGEMANAGER->addImage(type,
			"images/CharactorSelect/Gobugi.bmp", 183, 183, true, RGB(255, 0, 255));
		// �տ� ����� �̹��� ��ġ �ʱ�ȭ
		frontRect = RectMakeCenter((int)(_rect.left + _width * 0.5),
			(int)(_rect.top + _height * 0.5), 183, 183);
		_frontImg->setX((float)(frontRect.left));
		_frontImg->setY((float)(frontRect.top));
	}
	else if (type.compare("Pikachu") == 0)
	{
		_frontImg = IMAGEMANAGER->addImage(type,
			"images/CharactorSelect/Pikachu.bmp", 183, 271, true, RGB(255, 0, 255));
		// �տ� ����� �̹��� ��ġ �ʱ�ȭ
		frontRect = RectMakeCenter((int)(_rect.left + _width * 0.5),
			(int)(_rect.top + _height * 0.5), 183, 271);
		_frontImg->setX((float)(frontRect.left));
		_frontImg->setY((float)(frontRect.top));
	}
	else if (type.compare("Hanuts") == 0)
	{
		_rect.left += (int)(blank + _width);
		_rect.right += (int)(blank + _width);
		_frontImg = IMAGEMANAGER->addImage(type,
			"images/CharactorSelect/Hanuts.bmp", 183, 183, true, RGB(255, 0, 255));
		// �տ� ����� �̹��� ��ġ �ʱ�ȭ
		frontRect = RectMakeCenter((int)(_rect.left + _width * 0.5),
			(int)(_rect.top + _height * 0.5), 183, 183);
		_frontImg->setX((float)(frontRect.left));
		_frontImg->setY((float)(frontRect.top));
	}
}
Card::Card()
{
}
Card::~Card()
{
}
HRESULT Card::init()
{
	_width = 280;
	_height = 374;
	_backImg = IMAGEMANAGER->addImage("CardBack",
		"images/CharactorSelect/CardBack.bmp", _width, _height, false, RGB(255, 0, 255));
	// ���콺�� ī�忡 �÷��� ��
	_fMouseOnCard = false;
	_alpha = 255;
	init_forBlink();
	// �� ü������ ���� ����
	_fChooseCharactor = false;
	return S_OK;
}

void Card::release()
{
	_backImg = nullptr;
}

void Card::update()
{
	if (_fClickCard == true)
	{
		blink_card();
	}
	else {}

	// �����̴°� ���� �� ������ ���� �ٲ۴�.
	if (_blinkTimer <= 0)
	{
		_fClickCard = false;
		_fChooseCharactor = true;
	}
}

void Card::render()
{
	if (_fMouseOnCard == true && _fClickCard == false) { _alpha = 180; }
	else if(_fMouseOnCard == false && _fClickCard == false) { _alpha = 255; }

	_backImg->alphaRender(getMemDC(), _rect.left, _rect.top, _alpha);
	_frontImg->alphaRender(getMemDC(),
		(int)(_frontImg->getX()), (int)(_frontImg->getY()), _alpha);
	_fMouseOnCard = false;
}
