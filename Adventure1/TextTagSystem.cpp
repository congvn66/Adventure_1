#include "stdafx.h"
#include "TextTagSystem.h"

void TextTagSystem::InitVal()
{

}

void TextTagSystem::InitTagTemplates()
{
	this->tagTemplates[TagType::DEFAULT_TAG] = new TextTag(this->font, "bruh", 0.f, 0.f, 1.f, 1.f, Color::White, 12, 1000.f, 200.f);
}

void TextTagSystem::InitFont(string fontFile)
{
	if (this->font.loadFromFile(fontFile))
	{
		cout << "TextTagSystem: loaded font!" << endl;
	}
}

TextTagSystem::TextTagSystem(string fontFile)
{
	this->InitFont(fontFile);
	this->InitVal();
	this->InitTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
}

void TextTagSystem::AddTextTag(unsigned tagType)
{
}

void TextTagSystem::RemoveTextTag()
{
}

void TextTagSystem::Update(const float& dt)
{
	for (auto& tag : this->tags)
	{
		tag->Update(dt);
	}
}

void TextTagSystem::Render(RenderTarget* target)
{
	for (auto& tag : this->tags)
	{
		tag->Render(target);
	}
}
