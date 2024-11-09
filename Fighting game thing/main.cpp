#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <deque>
#include <string.h>

using namespace std;
std::deque<char>dirkeys,ukey,ikey,okey,kkey;
std::deque<int> animq;
bool p1cancel[256];

struct testchar : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))
            return false;

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(256);

        for (unsigned int i = 0; i < 8; ++i)
            for (unsigned int j = 0; j < 8; ++j)
            {
                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(j + i * 8) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(0+j*16,0+i*16);
                quad[1].position = sf::Vector2f(16+j*16,0+i*16);
                quad[2].position = sf::Vector2f(16+j*16,16+i*16);
                quad[3].position = sf::Vector2f(0+j*16,16+i*16);
            }
        return true;
    }

    void setanim(short anim[][2]){
        for (unsigned int i = 0; i < 8; ++i)
            for (unsigned int j = 0; j < 8; ++j){
            sf::Vertex* quad = &m_vertices[(j + i * 8) * 4];
            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16);
            quad[1].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16);
            quad[2].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16+16);
            quad[3].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16+16);
            }
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

bool cmdcheck(int len,char s[][5]){
    //s[][0]==num,s[][1]==u,s[][2]==i,s[][3]==o,s[][4]==k
    short temp=0;
    for(int i=0;i<15;i++){
        if((dirkeys[i]!=s[temp][0]&&dirkeys[i]!=s[temp-1][0])||ukey[i]!=s[temp][1]||ikey[i]!=s[temp][2]||okey[i]!=s[temp][3]||kkey[i]!=s[temp][4])break;
        if(dirkeys[i]==s[temp][0]&&ukey[i]==s[temp][1]&&ikey[i]==s[temp][2]&&okey[i]==s[temp][3]&&kkey[i]==s[temp][4])temp++;
        if(temp==len)break;
    }
    if(temp==len)return true;
    else return false;

}

void cancellist(int len,int s[]){
    for(int i=0;i<len;i++){
        p1cancel[s[i]]=true;
    }
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(256,240), "fighting game thingy");
	sf::Text text,utext,itext,otext,ktext;
	sf::Font font;
	testchar p1;
	if (!p1.load("char_sprites.png")){}
	sf::Texture bgtexture;
	if (!bgtexture.loadFromFile("teststage.png")){}
    sf::Sprite background;
    background.setTexture(bgtexture);
	char keydir='5';
	short p1frame=0,p1act=0,p1col=0,p1rec=0,p1anim[64][2],
	animlib[256][64][2]={{{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{1,1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //idle (0)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{2,0},{3,0},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //stand u1 (1)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{2,1},{3,1},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //stand u2 (2)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{4,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{4,1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //stand i1 (3)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{5,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{5,1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //stand i2 (4)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{6,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{6,1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //stand i3 (5)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{7,0},{8,0},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{7,1},{8,1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //stand i4 (6)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,1},{9,0},{10,0},{-1},{-1},
                       {-1},{-1},{-1},{0,2},{9,1},{10,1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                       //stand i5 (7)
                       {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,3},{1,3},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,4},{1,4},{-1},{-1},{-1},
                       {-1},{-1},{-1},{0,5},{1,5},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                       {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}}
                       //crouch (8)
                       },
                       hurtboxcount[256]={2,3,3,1};
    float p1x=100.0,p1y=192.0,p1jumpx=0.0,p1jumpy=0.0,
    colbox[256][4][2]={{{-7,-10},{9,-10},{9,32},{-7,32}},//standing
                        {{-7,0},{9,0},{9,32},{-7,32}},//crouching
                        },
    hurtbox[256][16][4][2]={{{{-11,0},{11,0},{11,32},{-11,32}},{{-7,-15},{9,-15},{9,0},{-7,0}}},
                        //idle (0)
                        {{{-11,0},{11,0},{11,32},{-11,32}},{{-7,-15},{9,-15},{9,0},{-7,0}},{{0,4},{16,4},{16,16},{0,16}}},
                        //stand u1 (1)
                        {{{-11,0},{11,0},{11,32},{-11,32}},{{-7,-15},{9,-15},{9,0},{-7,0}},{{0,4},{16,4},{16,16},{0,16}}},
                        //stand u2 (2)
                        //stand i1 (3)
                        //stand i2 (4)
                        //stand i3 (5)
                        //stand i4 (6)
                        //stand i5 (7)
                        {{{-8,-6},{10,-6},{10,32},{-8,32}}},
                        //crouch (8)
                        };
	bool p1air=false,seeboxes=true,F1key=false;
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
    char u='0',i='0',o='0',k='0';
	window.setFramerateLimit(60);
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))if (event.type == sf::Event::Closed)window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
            if(F1key==false){
                F1key=true;
                if(seeboxes==true)seeboxes=false;
                else seeboxes=true;
            }
        }
        else F1key=false;

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

        dirkeys.push_front(keydir);
        ukey.push_front(u);
        ikey.push_front(i);
        okey.push_front(o);
        kkey.push_front(k);
        if(dirkeys.size()>20)dirkeys.pop_back();
        if(ukey.size()>20)ukey.pop_back();
        if(ikey.size()>20)ikey.pop_back();
        if(okey.size()>20)okey.pop_back();
        if(kkey.size()>20)kkey.pop_back();


        if(p1air==false){
            if(keydir=='1'||keydir=='2'||keydir=='3'){
                //crouching actions
                if(o=='2'){
                    //strong normals
                    p1act=14;
                }
                if(i=='2'){
                    //middle normals
                    p1act=13;
                }
                else if(u=='2'){
                    //weak normals
                    p1act=12;
                }
                else{
                    p1act=11;
                }
            }
            else{
                //grounded actions
                if(o=='2'){
                    //strong normals
                    p1act=10;
                }
                if(i=='2'){
                    //middle normals
                    p1act=9;
                }
                else if(u=='2'){
                    //weak normals
                    p1act=8;
                }
                else if(keydir=='4'){
                    char temp[3][5]={{'4','0','0','0','0'},{'5','0','0','0','0'},{'4','0','0','0','0'}};
                    if(cmdcheck(3,temp)){
                        //leftdash
                        p1act=2;
                    }
                    //leftwalk
                    else{
                        p1act=1;
                    }
                }
                else if(keydir=='6'){
                    char temp[3][5]={{'6','0','0','0','0'},{'5','0','0','0','0'},{'6','0','0','0','0'}};
                    if(cmdcheck(3,temp)){
                        //rightdash
                        p1act=4;
                    }
                    //rightwalk
                    else{
                        p1act=3;
                    }
                }
                else if(keydir=='8'){
                    //upjump
                    p1act=5;
                }
                else if(keydir=='7'){
                    //leftjump
                    p1act=6;
                }
                else if(keydir=='9'){
                    //rightjump
                    p1act=7;
                }
                else{
                    p1act=0;
                }
            }
        }
        else{
            //jump actions
            p1act=0;
            }

        if(animq.empty()||(p1cancel[p1act]==true)){
                if(p1cancel[p1act]==true){
                    animq.clear();
                    memset(p1cancel,false,sizeof(p1cancel));
                }
                if(p1act==0){
                    p1col=0;
                    memcpy(p1anim,animlib[0],sizeof(animlib[0]));
                    p1frame=0;
                }
                else if(p1act==1){
                    p1col=0;
                    p1x-=3;
                }
                else if(p1act==2){
                    p1col=0;
                    p1air=true;
                    p1jumpy=-3.0;
                    p1jumpx=-7;
                }
                else if(p1act==3){
                    p1col=0;
                    p1x+=3;
                }
                if(p1act==4){
                    p1col=0;
                    p1air=true;
                    p1jumpy=-3.0;
                    p1jumpx=7;
                }
                else if(p1act==5){
                    p1col=0;
                    p1air=true;
                    p1jumpy=-14.0;
                }
                else if(p1act==6){
                    p1col=0;
                    p1air=true;
                    p1jumpy=-14.0;
                    p1jumpx=-3;
                }
                else if(p1act==7){
                    p1col=0;
                    p1air=true;
                    p1jumpy=-14.0;
                    p1jumpx=3;
                }
                else if(p1act==8){
                    p1col=0;
                    animq.insert(animq.begin(), {1,2,2,2,1,1,1});
                    int temp[1]={9};
                    cancellist(1,temp);
                    p1rec=4;
                }
                else if(p1act==9){
                    p1col=0;
                    animq.insert(animq.begin(), {3,5,6,7,7,7,7,6,5,5,5,4,4,4,3,3,3});
                    int temp[1]={10};
                    cancellist(1,temp);
                    p1rec=7;
                }
                else if(p1act==11){
                    p1col=1;
                    memcpy(p1anim,animlib[8],sizeof(animlib[8]));
                    p1frame=8;
                }
        }
        else{
            memcpy(p1anim,animlib[animq[0]],sizeof(animlib[animq[0]]));
            p1frame=animq[0];
            animq.pop_front();
            if(p1rec>0)p1rec--;
            if(animq.empty())memset(p1cancel,false,sizeof(p1cancel));
        }
        if(p1air==true){
                p1x+=p1jumpx;
                p1y+=p1jumpy;
                p1jumpy+=1;
                if(p1y>191){
                    p1air=false;
                    if(p1jumpx!=7&&p1jumpx!=-7){
                            p1rec=0;
                            p1col=1;
                            animq.insert(animq.begin(), {8,8,8,8});
                    }
                    else {
                            p1rec=0;
                            p1col=1;
                            animq.insert(animq.begin(), {8,8,8,8,8,8,8,8});
                    }
                    int temp[2]={8,9};
                    cancellist(2,temp);
                    p1jumpx=0;
                    p1jumpy=0;
                    p1y=192;
                }
            }


        p1.setanim(p1anim);


        sf::VertexArray collisionbox(sf::LinesStrip, 5);
        collisionbox[0].position = sf::Vector2f(colbox[p1col][0][0]+p1x, colbox[p1col][0][1]+p1y);
        collisionbox[1].position = sf::Vector2f(colbox[p1col][1][0]+p1x, colbox[p1col][1][1]+p1y);
        collisionbox[2].position = sf::Vector2f(colbox[p1col][2][0]+p1x, colbox[p1col][2][1]+p1y);
        collisionbox[3].position = sf::Vector2f(colbox[p1col][3][0]+p1x, colbox[p1col][3][1]+p1y);
        collisionbox[4].position = sf::Vector2f(colbox[p1col][0][0]+p1x, colbox[p1col][0][1]+p1y);

        sf::VertexArray Hurtbox(sf::Lines,hurtboxcount[p1frame]*8);
        for(int i=0;i<hurtboxcount[p1frame];i++){
            Hurtbox[0+i*8].position = sf::Vector2f(hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox[0+i*8].color  = sf::Color::Blue;
            Hurtbox[1+i*8].position = sf::Vector2f(hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox[1+i*8].color  = sf::Color::Blue;
            Hurtbox[2+i*8].position = sf::Vector2f(hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox[2+i*8].color  = sf::Color::Blue;
            Hurtbox[3+i*8].position = sf::Vector2f(hurtbox[p1frame][i][2][0]+p1x, hurtbox[p1frame][i][2][1]+p1y);
            Hurtbox[3+i*8].color  = sf::Color::Blue;
            Hurtbox[4+i*8].position = sf::Vector2f(hurtbox[p1frame][i][2][0]+p1x, hurtbox[p1frame][i][2][1]+p1y);
            Hurtbox[4+i*8].color  = sf::Color::Blue;
            Hurtbox[5+i*8].position = sf::Vector2f(hurtbox[p1frame][i][3][0]+p1x, hurtbox[p1frame][i][3][1]+p1y);
            Hurtbox[5+i*8].color  = sf::Color::Blue;
            Hurtbox[6+i*8].position = sf::Vector2f(hurtbox[p1frame][i][3][0]+p1x, hurtbox[p1frame][i][3][1]+p1y);
            Hurtbox[6+i*8].color  = sf::Color::Blue;
            Hurtbox[7+i*8].position = sf::Vector2f(hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox[7+i*8].color  = sf::Color::Blue;

        }


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

        text.setPosition(0.f, 0.f);
        utext.setPosition(0.f, 16.f);
        itext.setPosition(0.f, 32.f);
        otext.setPosition(0.f, 48.f);
        ktext.setPosition(0.f, 64.f);
        p1.setPosition(p1x-64,p1y-64);


		window.clear();
		window.draw(background);
		window.draw(p1);
		window.draw(text);
		window.draw(utext);
		window.draw(itext);
		window.draw(otext);
		window.draw(ktext);
		if(seeboxes==true){
            window.draw(collisionbox);
            window.draw(Hurtbox);
		}
		window.display();
	}
	return 0;
}
