#include <SFML/Graphics.hpp>
#include <stdio.h>

class Map : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, unsigned char* tiles)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(10* 9 * 4);

        for (unsigned int i = 0; i < 10; ++i)
            for (unsigned int j = 0; j < 9; ++j)
            {
                // get the current tile number
                int tilenum = int(tiles[j + i*9])-32;

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(j + i * 9) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i*16,j*16);
                quad[1].position = sf::Vector2f(16+i*16,j*16);
                quad[2].position = sf::Vector2f(16+i*16,16+j*16);
                quad[3].position = sf::Vector2f(i*16,16+j*16);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f((tilenum%10)*16, 16*(tilenum/10));
                quad[1].texCoords = sf::Vector2f((tilenum%10)*16+16, 16*(tilenum/10));
                quad[2].texCoords = sf::Vector2f((tilenum%10)*16+16, 16*(tilenum/10)+16);
                quad[3].texCoords = sf::Vector2f((tilenum%10)*16, 16*(tilenum/10)+16);
            }
        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


class Textbox : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, unsigned int* tiles)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(20* 5 * 4);

        for (unsigned int i = 0; i < 3; ++i)
            for (unsigned int j = 0; j < 18; ++j)
            {
                // get the current tile number
                int textnum = tiles[j + i * 18];

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(j + i * 18) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(8+j*8,112+i*8);
                quad[1].position = sf::Vector2f(16+j*8,112+i*8);
                quad[2].position = sf::Vector2f(16+j*8,120+i*8);
                quad[3].position = sf::Vector2f(8+j*8,120+i*8);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f((textnum%32)*8, 8*(textnum/32));
                quad[1].texCoords = sf::Vector2f((textnum%32)*8+8, 8*(textnum/32));
                quad[2].texCoords = sf::Vector2f((textnum%32)*8+8, 8*(textnum/32)+8);
                quad[3].texCoords = sf::Vector2f((textnum%32)*8, 8*(textnum/32)+8);
            }
        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


class Textframe : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, unsigned int x,unsigned int y, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width*(height+1) * 4);

        for(unsigned int j=0;j<width;j++){
            sf::Vertex* quad = &m_vertices[j*4];

            quad[0].position = sf::Vector2f(x+j*8,y);
            quad[1].position = sf::Vector2f(x+8+j*8,y);
            quad[2].position = sf::Vector2f(x+8+j*8,y+8);
            quad[3].position = sf::Vector2f(x+j*8,y+8);
            if(j==0){
                quad[0].texCoords = sf::Vector2f(0,0);
                quad[1].texCoords = sf::Vector2f(8,0);
                quad[2].texCoords = sf::Vector2f(8,8);
                quad[3].texCoords = sf::Vector2f(0,8);
            }
            if(j==width-1){
                quad[0].texCoords = sf::Vector2f(24,0);
                quad[1].texCoords = sf::Vector2f(32,0);
                quad[2].texCoords = sf::Vector2f(32,8);
                quad[3].texCoords = sf::Vector2f(24,8);
            }
            if(j!=width-1&&j!=0){
                quad[0].texCoords = sf::Vector2f(8,0);
                quad[1].texCoords = sf::Vector2f(16,0);
                quad[2].texCoords = sf::Vector2f(16,8);
                quad[3].texCoords = sf::Vector2f(8,8);
            }

        }

        for (unsigned int i = 1; i < height-1; i++)
            for (unsigned int j = 0; j < width; j++){

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i*width+j)*4];

                quad[0].position = sf::Vector2f(x+j*8,y+i*8);
                quad[1].position = sf::Vector2f(x+8+j*8,y+i*8);
                quad[2].position = sf::Vector2f(x+8+j*8,y+8+i*8);
                quad[3].position = sf::Vector2f(x+j*8,y+8+i*8);
                if(j==0){
                    quad[0].texCoords = sf::Vector2f(0,8);
                    quad[1].texCoords = sf::Vector2f(8,8);
                    quad[2].texCoords = sf::Vector2f(8,16);
                    quad[3].texCoords = sf::Vector2f(0,16);
                }
                else if(j==width-1){
                    if(height/2==i){
                    quad[0].texCoords = sf::Vector2f(24,16);
                    quad[1].texCoords = sf::Vector2f(32,16);
                    quad[2].texCoords = sf::Vector2f(32,24);
                    quad[3].texCoords = sf::Vector2f(24,24);
                    }
                    else{
                    quad[0].texCoords = sf::Vector2f(24,8);
                    quad[1].texCoords = sf::Vector2f(32,8);
                    quad[2].texCoords = sf::Vector2f(32,16);
                    quad[3].texCoords = sf::Vector2f(24,16);
                    }
                }
                else{
                    quad[0].texCoords = sf::Vector2f(8,8);
                    quad[1].texCoords = sf::Vector2f(16,8);
                    quad[2].texCoords = sf::Vector2f(16,16);
                    quad[3].texCoords = sf::Vector2f(8,16);
                }
            }

            for(unsigned int j=0;j<width;j++){
            sf::Vertex* quad = &m_vertices[(height*(width-1)+j)*4];

            quad[0].position = sf::Vector2f(x+j*8,y+height*8-8);
            quad[1].position = sf::Vector2f(x+8+j*8,y+height*8-8);
            quad[2].position = sf::Vector2f(x+8+j*8,y+height*8);
            quad[3].position = sf::Vector2f(x+j*8,y+height*8);
            if(j==0){
                quad[0].texCoords = sf::Vector2f(0,24);
                quad[1].texCoords = sf::Vector2f(8,24);
                quad[2].texCoords = sf::Vector2f(8,32);
                quad[3].texCoords = sf::Vector2f(0,32);
            }
            if(j==width-1){
                quad[0].texCoords = sf::Vector2f(24,24);
                quad[1].texCoords = sf::Vector2f(32,24);
                quad[2].texCoords = sf::Vector2f(32,32);
                quad[3].texCoords = sf::Vector2f(24,32);
            }
            if(j!=width-1&&j!=0){
                quad[0].texCoords = sf::Vector2f(8,24);
                quad[1].texCoords = sf::Vector2f(16,24);
                quad[2].texCoords = sf::Vector2f(16,32);
                quad[3].texCoords = sf::Vector2f(8,32);
            }

        }
        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};



int main()
{
	int i=0,charx=0,chary=0,walk=0;
	unsigned char map[90]={};
	unsigned int dir=0,facing=3;
	FILE *fp;
	fp = fopen("map.txt", "r");
	fread(map, 90, 1, fp);
	fclose(fp);

	sf::RenderWindow window(sf::VideoMode(160,144), "Rpg game thing");
	window.setFramerateLimit(60);
	sf::Texture texture;
	sf::Texture CGAfont;
	if (!CGAfont.loadFromFile("CGAfont.png")){}
	sf::Font font;
	if(!font.loadFromFile("PerfectDOSVGA437.ttf")){}
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text1.setString("Placeholder");
	text2.setString("Start");
	text3.setString("Mapedit");
	text1.setCharacterSize(16);
	text2.setCharacterSize(8);
	text3.setCharacterSize(8);
	text1.setFillColor(sf::Color::White);
	text2.setFillColor(sf::Color::White);
	text3.setFillColor(sf::Color::White);
	text1.setPosition(25.f,10.f);
	text2.setPosition(70.f,50.f);
	text3.setPosition(70.f,75.f);
	sf::CircleShape cursor(2.f,3);
	cursor.setFillColor(sf::Color::White);
	cursor.rotate(90.f);
	cursor.setPosition(68.f,50.f);
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))if (event.type == sf::Event::Closed)window.close();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			i=0;
			cursor.setPosition(68.f,50.f);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			i=1;
			cursor.setPosition(68.f,75.f);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
			break;
		}

        float screenWidth = 160.f;
        float screenHeight = 144.f;
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

		window.clear();
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(cursor);
		window.display();
	}
	if (!texture.loadFromFile("Sinclairwalk.png")){}
	Map mapdraw;
	if (!mapdraw.load("citytile.png",map)){}
	sf::Sprite Sinclair;
	Sinclair.setPosition(0.f,0.f);
	Sinclair.setTexture(texture);
	unsigned int line[54]={68, 97,109,110,46};
	walk=0;
	Textbox box;
	if (!box.load("CGAfont.png", line)){}
	Textframe frame;
	if (!frame.load("Textbox.png", 0,104,20,5)){}
	if(i==0){
        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event))if (event.type == sf::Event::Closed){window.close();}
            sf::Texture texture;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){dir=4;charx-=1;}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){dir=1;charx+=1;}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){dir=3;chary-=1;}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){dir=2;chary+=1;}
            else dir=0;

            if(dir!=0)facing=dir;

            Sinclair.setTextureRect(sf::IntRect(facing*48-32,0,16,16));
            Sinclair.setPosition(16*float(charx),16*float(chary));
            float screenWidth = 160.f;
            float screenHeight = 144.f;
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


            window.clear();
            window.draw(mapdraw);
            window.draw(Sinclair);
            window.draw(frame);
            window.draw(box);
            window.display();
            }
	}
	else{
        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event))if (event.type == sf::Event::Closed){window.close();}
            sf::Texture texture;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){charx-=1;}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){charx+=1;}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){chary-=1;}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){chary+=1;}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))map[charx*9+chary]++;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))map[charx*9+chary]--;

            if (!mapdraw.load("citytile.png",map)){}
            Sinclair.setTextureRect(sf::IntRect(facing*48-32,0,16,16));
            Sinclair.setPosition(16*float(charx),16*float(chary));

            float screenWidth = 160.f;
            float screenHeight = 144.f;
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


            window.clear();
            window.draw(mapdraw);
            window.draw(Sinclair);
            window.display();
            }
	}
	return 0;
}
