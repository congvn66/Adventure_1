#include "stdafx.h"
#include "TextTagSystem.h"

void TextTagSystem::InitVal()
{

}

void TextTagSystem::InitTagTemplates()
{
	this->tagTemplates[TagType::DEFAULT_TAG] = new TextTag(this->font, "", 0.f, 0.f, 0.f, -1.f, Color::White, 40, 10.f, 200.f);
	this->tagTemplates[TagType::NEGATIVE_TAG] = new TextTag(this->font, "", 0.f, 0.f, 0.f, -1.f, Color::Red, 40, 100.f, 250.f);
	this->tagTemplates[TagType::EXPERIENCE_TAG] = new TextTag(this->font, "", 0.f, 0.f, 0.f, -1.f, Color::Yellow, 55, 150.f, 250.f);
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
	//clean tags
	for (auto* tag : this->tags)
	{
		delete tag;
	}

	//clean templates
	for (auto& tag : this->tagTemplates)
	{
		delete tag.second;
	}
}

void TextTagSystem::AddTextTag(unsigned tagType, const float posX, const float posY, const string text)
{
	this->tags.push_back(new TextTag(this->tagTemplates[tagType],posX,posY,text));
}
void TextTagSystem::AddTextTag(unsigned tagType, const float posX, const float posY, const int val)
{
	stringstream ss;
	ss << val;
	this->tags.push_back(new TextTag(this->tagTemplates[tagType], posX, posY, ss.str()));
}
void TextTagSystem::AddTextTag(unsigned tagType, const float posX, const float posY, const float val)
{
	stringstream ss;
	ss << val;
	this->tags.push_back(new TextTag(this->tagTemplates[tagType], posX, posY, ss.str()));
}


void TextTagSystem::Update(const float& dt)
{
	for (size_t i = 0; i < this->tags.size(); i++)
	{
		this->tags[i]->Update(dt);

		//if out of lifetime
		if (this->tags[i]->CanBeDeleted())
		{
			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);	
		}
	}
	
}

void TextTagSystem::Render(RenderTarget& target)
{
	for (auto& tag : this->tags)
	{
		tag->Render(target);
	}
}
