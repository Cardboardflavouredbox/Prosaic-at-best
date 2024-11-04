#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;

int main()
{

	sf::RenderWindow window(sf::VideoMode(256,240), "mildly violent");
	sf::ConvexShape convex;
	sf::Text text,utext,itext,otext,ktext;
	sf::Font font;
	char keydir='5';
	float p1x=100.0,p1y=100.0,p1jump=0.0;
	bool p1air=false;
	if(!font.loadFromFile("PerfectDOSVGA437.ttf")){}
	text.setFont(font);
	utext.setFont(font);
	itext.setFont(font);
	otext.setFont(font);
	ktext.setFont(font);
	text.setCharacterSize(16);
	utext.setCharacterSize(16);
	itext.setCharacterSize(16);
	otext.setCharacterSize(16);
	ktext.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	utext.setFillColor(sf::Color::White);
	itext.setFillColor(sf::Color::White);
	otext.setFillColor(sf::Color::White);
	ktext.setFillColor(sf::Color::White);

	convex.setPointCount(4);
	convex.setPoint(0,sf::Vector2f(10, 10));
    convex.setPoint(1,sf::Vector2f(30, 10));
    convex.setPoint(2,sf::Vector2f(30, 30));
    convex.setPoint(3,sf::Vector2f(10, 30));

    char u='0',i='0',o='0',k='0';
	vector<sf::ConvexShape>P1Colbox;
	std::deque<char>dirkeys,ukey,ikey,okey,kkey;
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
        if(w==true&&s==true){w=true;s=false;}
        if(a==true&&d==true){a=false;d=false;}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
                if(u=='0')u='2';
                else if(u=='2')u='1';
                }
        else u='0';
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                if(i=='0')i='2';
                else if(i=='2')i='1';
                }
        else i='0';
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
                if(o=='0')o='2';
                else if(o=='2')o='1';
                }
        else o='0';
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                if(k=='0')k='2';
                else if(k=='2')k='1';
                }
        else k='0';

        if(w==true&&a==false&&s==false&&d==false)keydir='8';
        else if(w==false&&a==true&&s==false&&d==false)keydir='4';
        else if(w==false&&a==false&&s==true&&d==false)keydir='2';
        else if(w==false&&a==false&&s==false&&d==true)keydir='6';
        else if(w==true&&a==true&&s==false&&d==false)keydir='7';
        else if(w==false&&a==true&&s==true&&d==false)keydir='1';
        else if(w==false&&a==false&&s==true&&d==true)keydir='3';
        else if(w==true&&a==false&&s==false&&d==true)keydir='9';
        else keydir='5';

        if(keydir=='4') p1x-=4;
        else if(keydir=='6') p1x+=4;

        dirkeys.push_back(keydir);
        ukey.push_back(u);
        ikey.push_back(i);
        okey.push_back(o);
        kkey.push_back(k);
        if(dirkeys.size()>20)dirkeys.pop_front();
        if(ukey.size()>20)ukey.pop_front();
        if(ikey.size()>20)ikey.pop_front();
        if(okey.size()>20)okey.pop_front();
        if(kkey.size()>20)kkey.pop_front();

        std::string str(dirkeys.begin(), dirkeys.end());
        text.setString(str);
        std::string str2(ukey.begin(), ukey.end());
        utext.setString(str2);
        std::string str3(ikey.begin(), ikey.end());
        itext.setString(str3);
        std::string str4(okey.begin(), okey.end());
        otext.setString(str4);
        std::string str5(kkey.begin(), kkey.end());
        ktext.setString(str5);

        text.setPosition(0.f, 160.f);
        utext.setPosition(0.f, 176.f);
        itext.setPosition(0.f, 192.f);
        otext.setPosition(0.f, 208.f);
        ktext.setPosition(0.f, 224.f);
        convex.setPosition(p1x, p1y);

		window.clear();
		window.draw(convex);
		window.draw(text);
		window.draw(utext);
		window.draw(itext);
		window.draw(otext);
		window.draw(ktext);
		window.display();
	}
	return 0;
}
