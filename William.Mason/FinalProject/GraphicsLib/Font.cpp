#include "Font.h"
#include "Font.h"
#include <cassert>

using namespace std;

Font::Font(const std::string& filename, int size)
{
	//call al_load_font
	mSize = size;
	//mpFont = al_load_ttf_font(filename.c_str(), size, 0);

	mpFont = new sf::Font();

	mpFont->loadFromFile(filename);
}

Font::~Font()
{
	//call al_destroy_font
	delete mpFont;
	mpFont = nullptr;
}

//int Font::getAllegroFontAlignFlag(Font::Alignment align)
//{
//	int flag = 0;
//	switch (align)
//	{
//	case Font::LEFT:
//		flag = ALLEGRO_ALIGN_LEFT;
//		break;
//	case Font::CENTER:
//		flag = ALLEGRO_ALIGN_CENTER;
//		break;
//	case Font::RIGHT:
//		flag = ALLEGRO_ALIGN_RIGHT;
//		break;
//	default:
//		break;
//	}
//	//map the align variable to one of the allegro alignment flags
//
//	return flag;
//}
