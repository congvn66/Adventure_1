#include "stdafx.h"
#include "TextTagSystem.h"

void TextTagSystem::InitVal()
{

}

void TextTagSystem::InitTagTemplates()
{
	this->tagTemplates[TagType::DEFAULT_TAG] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, Color::White, 15, 100.f,true, 100.f, 200.f);
	this->tagTemplates[TagType::NEGATIVE_TAG] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, Color::Red, 15, 100.f,true, 150.f,200.f);
	this->tagTemplates[TagType::EXPERIENCE_TAG] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, Color::Cyan, 20, 200.f,true, 200.f,200.f);
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

void TextTagSystem::AddTextTag(unsigned tagType, const float posX, const float posY, const string text,	const string prefix, const string postfix)
{
	stringstream ss;
	ss << prefix << " " << text << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tagType],posX,posY,ss.str()));
}
void TextTagSystem::AddTextTag(unsigned tagType, const float posX, const float posY, const int val, const string prefix, const string postfix)
{
	stringstream ss;
	ss<< prefix<<" " << val << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tagType], posX, posY, ss.str()));
}
void TextTagSystem::AddTextTag(unsigned tagType, const float posX, const float posY, const float val, const string prefix, const string postfix)
{
	stringstream ss;
	ss << prefix << " " << val << " " << postfix;
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
