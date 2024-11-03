#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;

int main()
{

	sf::RenderWindow window(sf::VideoMode(256,240), "mildly violent");
	sf::ConvexShape convex;
	sf::Text text,u,i,o,k;
	sf::Font font;
	char keydir='5';
	if(!font.loadFromFile("PerfectDOSVGA437.ttf")){}
	text.setFont(font);
	u.setFont(font);
	i.setFont(font);
	o.setFont(font);
	k.setFont(font);
	text.setCharacterSize(16);
	u.setCharacterSize(16);
	i.setCharacterSize(16);
	o.setCharacterSize(16);
	k.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	u.setFillColor(sf::Color::White);
	i.setFillColor(sf::Color::White);
	o.setFillColor(sf::Color::White);
	k.setFillColor(sf::Color::White);
	convex.setPointCount(4);
	convex.setPoint(0,sf::Vector2f(10, 10));
    convex.setPoint(1,sf::Vector2f(30, 10));
    convex.setPoint(2,sf::Vector2f(30, 30));
    convex.setPoint(3,sf::Vector2f(10, 30));
	vector<sf::ConvexShape>P1Colbox;
	std::deque<char>keys;
	window.setFramerateLimit(60);
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))if (event.type == sf::Event::Closed)window.close();

        float screenWidth = 256.f;
        float screenHeight = 240.f;
        sf::Vector2u size = window.getSize();
        float  heightRatio = screenHeight / screenWidth;
        float  widthRatio = screenWidth / screenHeight;
        if (size.y * widthRatio <= size.x)
        {
            size.x = size.y * widthRatio;
        }
        else if (size.x * heightRatio <= size.y)
        {
            size.y = size.x * heightRatio;
        }
        window.setSize(size);
        bool w=false,a=false,s=false,d=false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))w=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))a=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))s=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))d=true;
        if(w==true&&s==true){w=false;s=false;}
        if(a==true&&d==true){a=false;d=false;}

        if(w==true&&a==false&&s==false&&d==false)keydir='8';
        else if(w==false&&a==true&&s==false&&d==false)keydir='4';
        else if(w==false&&a==false&&s==true&&d==false)keydir='2';
        else if(w==false&&a==false&&s==false&&d==true)keydir='6';
        else if(w==true&&a==true&&s==false&&d==false)keydir='7';
        else if(w==false&&a==true&&s==true&&d==false)keydir='1';
        else if(w==false&&a==false&&s==true&&d==true)keydir='3';
        else if(w==true&&a==false&&s==false&&d==true)keydir='9';
        else keydir='5';

        keys.push_back(keydir);
        if(keys.size()>20)keys.pop_front();
        std::string str(keys.begin(), keys.end());
        text.setString(str);
        text.setPosition(0.f, 0.f);
        u.setPosition(0.f, 16.f);
        i.setPosition(0.f, 32.f);
        o.setPosition(0.f, 48.f);
        k.setPosition(0.f, 64.f);
        convex.setPosition(0.f, 50.f);

		window.clear();
		window.draw(convex);
		window.draw(text);
		window.display();
	}
	return 0;
}
