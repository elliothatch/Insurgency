#include "StdAfx.h"
#include "SFMLCursesTextBox.h"


SFMLCursesTextBox::SFMLCursesTextBox(const sf::Window& window, const sf::Vector2i& lCursesSize)
	:SFMLCursesWindow(window, lCursesSize),
	m_text(),
	m_alignment(Alignment::Left),
	finalCharPosition(0,0),
	m_textColor(sf::Color::White),
	m_backColor(sf::Color::Black)
{
}


SFMLCursesTextBox::~SFMLCursesTextBox(void)
{
}

void SFMLCursesTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	SFMLCursesWindow::draw(target,states);
}
sf::FloatRect SFMLCursesTextBox::getLocalBounds(void) const
{
	return m_rectangle.getLocalBounds();
}
sf::FloatRect SFMLCursesTextBox::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_rectangle.getGlobalBounds());
}

void SFMLCursesTextBox::setText(const std::string& text)
{
	m_text = text;
	updateTextBox();
}
const std::string& SFMLCursesTextBox::getText() const
{
	return m_text;
}
void SFMLCursesTextBox::setAlignment(SFMLCursesTextBox::Alignment::E alignment)
{
	m_alignment = alignment;
	updateTextBox();
}
SFMLCursesTextBox::Alignment::E SFMLCursesTextBox::getAlignment() const
{
	return m_alignment;
}

void SFMLCursesTextBox::updateTextBox()
{
	/*
	std::string word = "";
	int col = 0;
	int line = 0;
	for(std::string::iterator stringIt(m_text.begin()); stringIt != m_text.end(); stringIt++)
	{
		if(*stringIt == ' ' || stringIt == m_text.end() - 1) //word is complete
		{
			//WARNING: If a word is longer than the width that word and any after will not be printed
			//needs mid-word linebreaking
			//left justified
			if(stringIt == m_text.end() - 1)
				word += *stringIt;
			if(word.length() > static_cast<unsigned int>(m_cursesSize.y))
				break;
			if(word.length() > static_cast<unsigned int>(m_cursesSize.y - col)) //word too long for this line, move onto next one
			{
				line++;
				col = 0;
			}
			if(line >= m_cursesSize.x) //past the last line
				break;
			for(std::string::iterator wordIt(word.begin()); wordIt != word.end(); wordIt++)
			{
				setTile(SFMLCursesChar(m_window, std::string("") + *wordIt), sf::Vector2i(line,col));
				col++;
			}
			if(col < m_cursesSize.y - 1)
			{
				setTile(SFMLCursesChar(m_window, " "), sf::Vector2i(line,col));
				col++;
			}
			word = "";
		}
		else
		{
			word += *stringIt;
		}

	}
	*/
	clearTiles(" ", m_textColor, m_backColor);
	std::string::const_iterator lineBegin(m_text.begin());
	std::string::const_iterator lineEnd(m_text.begin());
	unsigned int line = 0;
	while(lineBegin != m_text.end())
	{
		std::string::const_iterator lastLineEnd(lineEnd);
		unsigned int position = m_text.find(" ", lineEnd - m_text.begin() + 1);
		if(position != std::string::npos)
			lineEnd = m_text.begin() + position;
		else
			lineEnd = m_text.end();
		if(lineEnd - lineBegin  > m_cursesSize.y || lineEnd == m_text.end()) //too much for this line
		{
			if(!(lineEnd - lineBegin > m_cursesSize.y))
				lastLineEnd = lineEnd;
			//backtrack, print, next line
			unsigned int col = 0;
			unsigned int spacePadding = 0;
			unsigned int wordCount = std::count(lineBegin, lastLineEnd, ' ') + 1;
			unsigned int wordCountRemaining = wordCount;
			unsigned int extraSpace = m_cursesSize.y - (lastLineEnd - lineBegin);
			unsigned int extraSpaceRemaining = extraSpace;
			//print with proper alignment
			switch(m_alignment)
			{
			case Alignment::Left:
				col = 0;
				break;
			case Alignment::Right:
				col = m_cursesSize.y - (lastLineEnd - lineBegin);
				break;
			case Alignment::Center:
				col = m_cursesSize.y/2 - (lastLineEnd - lineBegin)/2;
				break;
			case Alignment::Justify:
				col = 0;
				break;
			}
			for(lineBegin; lineBegin != lastLineEnd; lineBegin++)
			{
				setTile(SFMLCursesChar(m_window, std::string("") + *lineBegin, m_textColor, m_backColor), sf::Vector2i(line,col));
				switch(m_alignment)
				{
				case Alignment::Left:
				case Alignment::Right:
				case Alignment::Center:
					col++;
					break;
				case Alignment::Justify:
					col++;
					if(extraSpaceRemaining > 0 && *lineBegin == ' ' && lastLineEnd != m_text.end())
					{
						col++;
						extraSpaceRemaining--;
						if(extraSpaceRemaining >= wordCountRemaining - 1)
						{
							col++;
							extraSpaceRemaining--;
						}
						wordCountRemaining--;
					}
					break;
				}
			}
			if(lineBegin != m_text.end())
				lineBegin++;
			else 
				break;
			line++;
			wordCount = 0;
		}
		if(line >= static_cast<unsigned int>(m_cursesSize.x))
			break;
	}

}

void SFMLCursesTextBox::setTextColor(const sf::Color& color)
{
	m_textColor = color;
	updateTextBox();
}
const sf::Color& SFMLCursesTextBox::getTextColor() const
{
	return m_textColor;
}
void SFMLCursesTextBox::setBackgroundColor(const sf::Color& color)
{
	m_backColor = color;
	updateTextBox();
}
const sf::Color& SFMLCursesTextBox::getBackgroundColor() const
{
	return m_backColor;
}

void SFMLCursesTextBox::append(const std::string& text)
{
	setText(m_text.append(text));
}