#pragma once
#include<SFML/Graphics.hpp>

class Loginwindow
{
	sf::RectangleShape loginbox;
	sf::Text showtext;
	bool checkpass;
	bool checkstatus;
	char buffer[100];
	int bufferlength;

public:
	Loginwindow(float posx, float posy, float wide, float high, sf::Font& font, bool pass=false);
	void manageevents(sf::Event& event);
	void drawscreen(sf::RenderWindow& window);
	const char* getvalue() const;
	void cleartext();
	void setstatus(bool stat);
	bool getstatus() const;
	sf::FloatRect getGlobalBounds()const;


};