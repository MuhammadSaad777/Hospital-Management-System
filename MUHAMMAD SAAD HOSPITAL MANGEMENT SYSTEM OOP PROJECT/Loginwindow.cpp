#include"Loginwindow.h"

Loginwindow::Loginwindow(float posx, float posy, float wide, float high, sf::Font& font, bool pass):showtext(font)
{
	loginbox.setSize({ wide,high });
	loginbox.setPosition({ posx,posy });
	loginbox.setFillColor(sf::Color::White);

	showtext.setCharacterSize(28);
	showtext.setFillColor(sf::Color::Red);
	showtext.setPosition({ posx + 10.f,posy + 8.f });


	bufferlength = 0;
	buffer[0] = '\0';
	checkpass = pass;
	checkstatus = false;


}
void Loginwindow::manageevents(sf::Event& event)
{
	if (checkstatus == false)
	{
		return;
	}
	if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
	{
		unsigned int unicode = textEvent->unicode;

		//checking for backspace
		if (unicode == 8)
		{
			if (bufferlength > 0)
			{
				bufferlength--;
				buffer[bufferlength] = '\0';
			}
		}
		else if (unicode >= 32 && unicode < 127 && bufferlength < 99)
		{
			buffer[bufferlength] = (char)unicode;
			bufferlength++;
			buffer[bufferlength] = '\0';
		}
		if (checkpass == true)
		{
			char hide[100];
			for (int i = 0; i < bufferlength; i++)
			{
				hide[i] = '*';
			}
			hide[bufferlength] = '\0';
			showtext.setString(hide);
		}
		else
		{
			showtext.setString(buffer);
		}

	}
}

void Loginwindow::drawscreen(sf::RenderWindow& window)
{
	window.draw(loginbox);
	window.draw(showtext);
}

const char* Loginwindow::getvalue() const
{
	return buffer;
}

void Loginwindow::cleartext()
{
	bufferlength = 0;
	buffer[0] = '\0';
	showtext.setString("");

}


void Loginwindow::setstatus(bool stat)
{
	checkstatus = stat;
}

bool Loginwindow::getstatus() const
{
	return checkstatus;
}
sf::FloatRect Loginwindow::getGlobalBounds()const
{
	return loginbox.getGlobalBounds();
}