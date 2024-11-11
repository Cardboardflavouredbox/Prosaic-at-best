#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <deque>
#include <string.h>


using namespace std;
std::deque<char>dirkeys,ukey,ikey,okey,kkey,dirkeys2,ukey2,ikey2,okey2,kkey2;
std::deque<int> animq1,animq2;

short p1frame=0,p1act=0,p1col=0,p1rec=0,p1anim[64][2],
        p2frame=0,p2act=0,p2col=0,p2rec=0,p2anim[64][2],
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
                   hurtboxcount[256]={2,3,3,2,2,2,3,3,2},
                   hitboxcount[256]={0,1,1,0,0,0,1,1,0};
float p1x=100.0,p1y=192.0,p1jumpx=0.0,p1jumpy=0.0,
        p2x=156.0,p2y=192.0,p2jumpx=0.0,p2jumpy=0.0,
colbox[256][2][2]={{{-7,-10},{9,32}},//standing
                    {{-7,-1},{9,32},},//crouching
                    },
hurtbox[256][8][2][2]={{{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //idle (0)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{4,0},{18,9}}},
                    //stand u1 (1)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{4,0},{20,6}}},
                    //stand u2 (2)
                    {{{-11,0},{14,32}},{{-7,-15},{9,0}}},
                    //stand i1 (3)
                    {{{-11,0},{15,32}},{{-7,-15},{9,0}}},
                    //stand i2 (4)
                    {{{-11,0},{14,32}},{{-7,-15},{9,0}}},
                    //stand i3 (5)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{0,12},{24,19}}},
                    //stand i4 (6)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{4,12},{26,18}}},
                    //stand i5 (7)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},
                    //crouch (8)
                    },
hitbox[256][8][2][2]={{-1},
                    //idle (0)
                    {{{4,-1},{19,10}}},
                    //stand u1 (1)
                    {{{4,-1},{22,7}}},
                    //stand u2 (2)
                    {-1},
                    //stand i1 (3)
                    {-1},
                    //stand i2 (4)
                    {-1},
                    //stand i3 (5)
                    {{{0,12},{24,19}}},
                    //stand i4 (6)
                    {{{5,11},{30,20}}},
                    //stand i5 (7)
                    {-1},
                    //crouch (8)
                    };
bool p1air=false,p2air=false,seeboxes=true,F1key=false,pause=false,Enterkey=false,p1cancel[256],p2cancel[256],p1right=true,p2right=false;

struct character : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))
            return false;
        m_tileset.setRepeated(true);

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

    void setanim(short anim[][2],bool right){
            for (unsigned int i = 0; i < 8; ++i)
                for (unsigned int j = 0; j < 8; ++j){
                if(right==true){
                    sf::Vertex* quad = &m_vertices[(j + i * 8) * 4];
                    quad[0].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16);
                    quad[1].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16);
                    quad[2].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16+16);
                    quad[3].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16+16);
                }
                else{
                    sf::Vertex* quad = &m_vertices[(7-j + i * 8) * 4];
                    quad[0].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16);
                    quad[1].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16);
                    quad[2].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16+16);
                    quad[3].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16+16);
                }
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

bool cmdcheck(int playercode,int len,char s[][5]){
    //s[][0]==num,s[][1]==u,s[][2]==i,s[][3]==o,s[][4]==k
    short temp=0;
    for(int i=0;i<15;i++){
        if(playercode==1){
            if((dirkeys[i]!=s[temp][0]&&dirkeys[i]!=s[temp-1][0])||ukey[i]!=s[temp][1]||ikey[i]!=s[temp][2]||okey[i]!=s[temp][3]||kkey[i]!=s[temp][4])break;
            if(dirkeys[i]==s[temp][0]&&ukey[i]==s[temp][1]&&ikey[i]==s[temp][2]&&okey[i]==s[temp][3]&&kkey[i]==s[temp][4])temp++;
        }
        else if(playercode==2){
            if((dirkeys2[i]!=s[temp][0]&&dirkeys2[i]!=s[temp-1][0])||ukey2[i]!=s[temp][1]||ikey2[i]!=s[temp][2]||okey2[i]!=s[temp][3]||kkey2[i]!=s[temp][4])break;
            if(dirkeys2[i]==s[temp][0]&&ukey2[i]==s[temp][1]&&ikey2[i]==s[temp][2]&&okey2[i]==s[temp][3]&&kkey2[i]==s[temp][4])temp++;
        }
        if(temp==len)break;
    }
    if(temp==len)return true;
    else return false;

}

int chooseaction(int playercode, bool p1air, char keydir, char u, char i, char o){
            if(p1air==false){
                if(keydir=='1'||keydir=='2'||keydir=='3'){
                    //crouching actions
                    if(o=='2'){
                        //strong normals
                        return 14;
                    }
                    if(i=='2'){
                        //middle normals
                        return 13;
                    }
                    else if(u=='2'){
                        //weak normals
                        return 12;
                    }
                    else{
                        return 11;
                    }
                }
                else{
                    //grounded actions
                    if(o=='2'){
                        //strong normals
                        return 10;
                    }
                    if(i=='2'){
                        //middle normals
                        return 9;
                    }
                    else if(u=='2'){
                        //weak normals
                        return 8;
                    }
                    else if(keydir=='4'){
                        char temp[3][5]={{'4','0','0','0','0'},{'5','0','0','0','0'},{'4','0','0','0','0'}};
                        if(cmdcheck(playercode,3,temp)){
                            //leftdash
                            return 2;
                        }
                        //leftwalk
                        else{
                            return 1;
                        }
                    }
                    else if(keydir=='6'){
                        char temp[3][5]={{'6','0','0','0','0'},{'5','0','0','0','0'},{'6','0','0','0','0'}};
                        if(cmdcheck(playercode,3,temp)){
                            //rightdash
                            return 4;
                        }
                        //rightwalk
                        else{
                            return 3;
                        }
                    }
                    else if(keydir=='8'){
                        //upjump
                        return 5;
                    }
                    else if(keydir=='7'){
                        //leftjump
                        return 6;
                    }
                    else if(keydir=='9'){
                        //rightjump
                        return 7;
                    }
                    else{
                        return 0;
                    }
                }
            }
            else{
                //jump actions
                return 0;
                }
}

void characterdata(short playercode,std::deque<int>animq,bool cancel[256],bool air,short anim[64][2],short act,short col,short frame,short rec,float x,float y,float jumpx,float jumpy,bool right,float enemyx){
    if(animq.empty()||((cancel[act]==true)&&(rec==0))){
        if(cancel[act]==true){
            memset(cancel,false,sizeof(cancel));
            if(playercode==1)memset(p1cancel,false,sizeof(p1cancel));
            else if(playercode==2)memset(p2cancel,false,sizeof(p2cancel));
            animq.clear();
        }
        if(act==0){
            if(air==false){
                if(x<enemyx)right=true;
                else right=false;
            }
            col=0;
            memcpy(anim,animlib[0],sizeof(animlib[0]));
            frame=0;
        }
        else if(act==1){
            col=0;
            x-=3;
        }
        else if(act==2){
            col=0;
            air=true;
            jumpy=-3.0;
            jumpx=-7;
        }
        else if(act==3){
            col=0;
            x+=3;
        }
        if(act==4){
            col=0;
            air=true;
            jumpy=-3.0;
            jumpx=7;
        }
        else if(act==5){
            col=0;
            air=true;
            jumpy=-14.0;
        }
        else if(act==6){
            col=0;
            air=true;
            jumpy=-14.0;
            jumpx=-3;
        }
        else if(act==7){
            col=0;
            air=true;
            jumpy=-14.0;
            jumpx=3;
        }
        else if(act==8){
            col=0;
            animq.insert(animq.begin(), {1,2,2,2,1,1,1});
            cancel[9]=true;
            rec=4;
        }
        else if(act==9){
            col=0;
            animq.insert(animq.begin(), {3,5,6,7,7,7,7,6,5,5,5,4,4,3,3});
            cancel[10]=true;
            rec=7;
        }
        else if(act==11){
            if(x<enemyx)right=true;
            else right=false;
            col=1;
            memcpy(anim,animlib[8],sizeof(animlib[8]));
            frame=8;
        }
}
else{
    memcpy(anim,animlib[animq[0]],sizeof(animlib[animq[0]]));
    frame=animq[0];
    animq.pop_front();
    if(rec>0)rec--;
    if(animq.empty())memset(cancel,false,sizeof(cancel));
}
if(air==true){
        x+=jumpx;
        y+=jumpy;
        jumpy+=1;
        if(y>191){
            air=false;
            if(x<enemyx)right=true;
                else right=false;
            if(jumpx!=7&&jumpx!=-7){
                    rec=0;
                    col=1;
                    animq.insert(animq.begin(), {8,8,8,8});
            }
            else {
                    rec=0;
                    col=1;
                    animq.insert(animq.begin(), {8,8,8,8,8,8,8,8});
            }
            cancel[8]=true;
            cancel[9]=true;
            jumpx=0;
            jumpy=0;
            y=192;
        }
    }
if(playercode==1){
    p1right=right;
    animq1.clear();
    animq1.insert(animq1.begin(), animq.begin(),animq.end());
    memcpy(p1cancel,cancel,sizeof(cancel));
    p1air=air;
    memcpy(p1anim,anim,sizeof(anim));
    p1act=act;
    p1col=col;
    p1frame=frame;
    p1rec=rec;
    p1x=x,p1y=y;
    p1jumpx=jumpx;
    p1jumpy=jumpy;
}
else if(playercode==2){
    p2right=right;
    animq2.clear();
    animq2.insert(animq2.begin(), animq.begin(),animq.end());
    memcpy(p2cancel,cancel,sizeof(cancel));
    p2air=air;
    memcpy(p2anim,anim,sizeof(anim));
    p2act=act;
    p2col=col;
    p2frame=frame;
    p2rec=rec;
    p2x=x,p2y=y;
    p2jumpx=jumpx;
    p2jumpy=jumpy;
}
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(256,240), "fighting game thingy");
	sf::Text pausetext;
	sf::Font font;
	character p1;
	if (!p1.load("char_sprites.png")){}
	character p2;
	if (!p2.load("char_sprites.png")){}
	sf::Texture bgtexture;
	if (!bgtexture.loadFromFile("teststage.png")){}
    sf::Sprite background;
    background.setTexture(bgtexture);
	char keydir1='5',keydir2='5';
	if(!font.loadFromFile("PerfectDOSVGA437.ttf")){}
	pausetext.setFont(font);
	pausetext.setCharacterSize(16);
	pausetext.setFillColor(sf::Color::White);
    char u='0',i='0',o='0',k='0',u2='0',i2='0',o2='0',k2='0';
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


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
            if(F1key==false){
                F1key=true;
                if(seeboxes==true)seeboxes=false;
                else seeboxes=true;
            }
        }
        else F1key=false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if(Enterkey==false){
                Enterkey=true;
                if(pause==true)pause=false;
                else pause=true;
            }
        }
        else Enterkey=false;

        bool w=false,a=false,s=false,d=false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))w=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))a=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))s=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))d=true;
        if(w==true&&s==true){w=true;s=false;}
        if(a==true&&d==true){a=false;d=false;}

        bool w2=false,a2=false,s2=false,d2=false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))w2=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))a2=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))s2=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))d2=true;
        if(w2==true&&s2==true){w2=true;s2=false;}
        if(a2==true&&d2==true){a2=false;d2=false;}

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


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                if(u2=='0')u2='2';
                else if(u2=='2')u2='1';
                }
        else u2='0';
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                if(i2=='0')i2='2';
                else if(i2=='2')i2='1';
                }
        else i2='0';
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                if(o2=='0')o2='2';
                else if(o2=='2')o2='1';
                }
        else o2='0';
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)){
                if(k2=='0')k2='2';
                else if(k2=='2')k2='1';
                }
        else k2='0';


        if(w==true&&a==false&&s==false&&d==false)keydir1='8';
        else if(w==false&&a==true&&s==false&&d==false)keydir1='4';
        else if(w==false&&a==false&&s==true&&d==false)keydir1='2';
        else if(w==false&&a==false&&s==false&&d==true)keydir1='6';
        else if(w==true&&a==true&&s==false&&d==false)keydir1='7';
        else if(w==false&&a==true&&s==true&&d==false)keydir1='1';
        else if(w==false&&a==false&&s==true&&d==true)keydir1='3';
        else if(w==true&&a==false&&s==false&&d==true)keydir1='9';
        else keydir1='5';


        if(w2==true&&a2==false&&s2==false&&d2==false)keydir2='8';
        else if(w2==false&&a2==true&&s2==false&&d2==false)keydir2='4';
        else if(w2==false&&a2==false&&s2==true&&d2==false)keydir2='2';
        else if(w2==false&&a2==false&&s2==false&&d2==true)keydir2='6';
        else if(w2==true&&a2==true&&s2==false&&d2==false)keydir2='7';
        else if(w2==false&&a2==true&&s2==true&&d2==false)keydir2='1';
        else if(w2==false&&a2==false&&s2==true&&d2==true)keydir2='3';
        else if(w2==true&&a2==false&&s2==false&&d2==true)keydir2='9';
        else keydir2='5';


        if(pause==false){
            dirkeys.push_front(keydir1);
            ukey.push_front(u);
            ikey.push_front(i);
            okey.push_front(o);
            kkey.push_front(k);
            if(dirkeys.size()>20)dirkeys.pop_back();
            if(ukey.size()>20)ukey.pop_back();
            if(ikey.size()>20)ikey.pop_back();
            if(okey.size()>20)okey.pop_back();
            if(kkey.size()>20)kkey.pop_back();

            dirkeys2.push_front(keydir2);
            ukey2.push_front(u2);
            ikey2.push_front(i2);
            okey2.push_front(o2);
            kkey2.push_front(k2);
            if(dirkeys2.size()>20)dirkeys2.pop_back();
            if(ukey2.size()>20)ukey2.pop_back();
            if(ikey2.size()>20)ikey2.pop_back();
            if(okey2.size()>20)okey2.pop_back();
            if(kkey2.size()>20)kkey2.pop_back();

            characterdata(1,animq1,p1cancel,p1air,p1anim,chooseaction(1,p1air,keydir1,u,i,o),p1col,p1frame,p1rec,p1x,p1y,p1jumpx,p1jumpy,p1right,p2x);
            characterdata(2,animq2,p2cancel,p2air,p2anim,chooseaction(2,p2air,keydir2,u2,i2,o2),p2col,p2frame,p2rec,p2x,p2y,p2jumpx,p2jumpy,p2right,p1x);
            p1.setanim(p1anim,p1right);
            p2.setanim(p2anim,p2right);

            float temp[2],temp2[2],temp3[2],temp4[2];
            if(p1right==true){
                temp[0]=colbox[p1col][0][0]+p1x;
                temp[1]=colbox[p1col][0][1]+p1y;
                temp2[0]=colbox[p1col][1][0]+p1x;
                temp2[1]=colbox[p1col][1][1]+p1y;
            }
            else{
                temp[0]=-colbox[p1col][1][0]+p1x;
                temp[1]=colbox[p1col][0][1]+p1y;
                temp2[0]=-colbox[p1col][0][0]+p1x;
                temp2[1]=colbox[p1col][1][1]+p1y;
            }
            if(p2right==true){
                temp3[0]=colbox[p2col][0][0]+p2x;
                temp3[1]=colbox[p2col][0][1]+p2y;
                temp4[0]=colbox[p2col][1][0]+p2x;
                temp4[1]=colbox[p2col][1][1]+p2y;
            }
            else{
                temp3[0]=-colbox[p2col][1][0]+p2x;
                temp3[1]=colbox[p2col][0][1]+p2y;
                temp4[0]=-colbox[p2col][0][0]+p2x;
                temp4[1]=colbox[p2col][1][1]+p2y;
            }
            if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
                if(p1x<p2x){
                    p1x-=3;
                    p2x+=3;
                }
                else{
                    p1x+=3;
                    p2x-=3;
                }
            }

        }

        sf::VertexArray collisionbox1(sf::LinesStrip, 5);
        if(p1right==true){
        collisionbox1[0].position = sf::Vector2f(colbox[p1col][0][0]+p1x, colbox[p1col][0][1]+p1y);
        collisionbox1[1].position = sf::Vector2f(colbox[p1col][1][0]+p1x, colbox[p1col][0][1]+p1y);
        collisionbox1[2].position = sf::Vector2f(colbox[p1col][1][0]+p1x, colbox[p1col][1][1]+p1y);
        collisionbox1[3].position = sf::Vector2f(colbox[p1col][0][0]+p1x, colbox[p1col][1][1]+p1y);
        collisionbox1[4].position = sf::Vector2f(colbox[p1col][0][0]+p1x, colbox[p1col][0][1]+p1y);
        }
        else{
        collisionbox1[1].position = sf::Vector2f(-colbox[p1col][0][0]+p1x, colbox[p1col][0][1]+p1y);
        collisionbox1[0].position = sf::Vector2f(-colbox[p1col][1][0]+p1x, colbox[p1col][0][1]+p1y);
        collisionbox1[3].position = sf::Vector2f(-colbox[p1col][1][0]+p1x, colbox[p1col][1][1]+p1y);
        collisionbox1[2].position = sf::Vector2f(-colbox[p1col][0][0]+p1x, colbox[p1col][1][1]+p1y);
        collisionbox1[4].position = sf::Vector2f(-colbox[p1col][1][0]+p1x, colbox[p1col][0][1]+p1y);
        }

        sf::VertexArray Hurtbox1(sf::Lines,hurtboxcount[p1frame]*8);
        for(int i=0;i<hurtboxcount[p1frame];i++){
            Hurtbox1[0+i*8].color=sf::Color::Blue;
            Hurtbox1[1+i*8].color=sf::Color::Blue;
            Hurtbox1[2+i*8].color=sf::Color::Blue;
            Hurtbox1[3+i*8].color=sf::Color::Blue;
            Hurtbox1[4+i*8].color=sf::Color::Blue;
            Hurtbox1[5+i*8].color=sf::Color::Blue;
            Hurtbox1[6+i*8].color=sf::Color::Blue;
            Hurtbox1[7+i*8].color=sf::Color::Blue;
            if(p1right==true){
            Hurtbox1[0+i*8].position = sf::Vector2f(hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox1[1+i*8].position = sf::Vector2f(hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox1[2+i*8].position = sf::Vector2f(hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox1[3+i*8].position = sf::Vector2f(hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[4+i*8].position = sf::Vector2f(hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[5+i*8].position = sf::Vector2f(hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[6+i*8].position = sf::Vector2f(hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[7+i*8].position = sf::Vector2f(hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            }
            else{
            Hurtbox1[1+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox1[0+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox1[7+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            Hurtbox1[5+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[6+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][1][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[3+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[4+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][1][1]+p1y);
            Hurtbox1[2+i*8].position = sf::Vector2f(-hurtbox[p1frame][i][0][0]+p1x, hurtbox[p1frame][i][0][1]+p1y);
            }
        }

        sf::VertexArray Hitbox1(sf::Lines,hitboxcount[p1frame]*8);
        for(int i=0;i<hitboxcount[p1frame];i++){
            Hitbox1[0+i*8].color=sf::Color::Red;
            Hitbox1[1+i*8].color=sf::Color::Red;
            Hitbox1[2+i*8].color=sf::Color::Red;
            Hitbox1[3+i*8].color=sf::Color::Red;
            Hitbox1[4+i*8].color=sf::Color::Red;
            Hitbox1[5+i*8].color=sf::Color::Red;
            Hitbox1[6+i*8].color=sf::Color::Red;
            Hitbox1[7+i*8].color=sf::Color::Red;
            if(p1right==true){
            Hitbox1[0+i*8].position = sf::Vector2f(hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            Hitbox1[1+i*8].position = sf::Vector2f(hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            Hitbox1[2+i*8].position = sf::Vector2f(hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            Hitbox1[3+i*8].position = sf::Vector2f(hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[4+i*8].position = sf::Vector2f(hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[5+i*8].position = sf::Vector2f(hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[6+i*8].position = sf::Vector2f(hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[7+i*8].position = sf::Vector2f(hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            }
            else{
            Hitbox1[1+i*8].position = sf::Vector2f(-hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            Hitbox1[0+i*8].position = sf::Vector2f(-hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            Hitbox1[7+i*8].position = sf::Vector2f(-hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            Hitbox1[5+i*8].position = sf::Vector2f(-hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[6+i*8].position = sf::Vector2f(-hitbox[p1frame][i][1][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[3+i*8].position = sf::Vector2f(-hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[4+i*8].position = sf::Vector2f(-hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][1][1]+p1y);
            Hitbox1[2+i*8].position = sf::Vector2f(-hitbox[p1frame][i][0][0]+p1x, hitbox[p1frame][i][0][1]+p1y);
            }
        }


        sf::VertexArray collisionbox2(sf::LinesStrip, 5);
        if(p2right==true){
        collisionbox2[0].position = sf::Vector2f(colbox[p2col][0][0]+p2x, colbox[p2col][0][1]+p2y);
        collisionbox2[1].position = sf::Vector2f(colbox[p2col][1][0]+p2x, colbox[p2col][0][1]+p2y);
        collisionbox2[2].position = sf::Vector2f(colbox[p2col][1][0]+p2x, colbox[p2col][1][1]+p2y);
        collisionbox2[3].position = sf::Vector2f(colbox[p2col][0][0]+p2x, colbox[p2col][1][1]+p2y);
        collisionbox2[4].position = sf::Vector2f(colbox[p2col][0][0]+p2x, colbox[p2col][0][1]+p2y);
        }
        else{
        collisionbox2[1].position = sf::Vector2f(-colbox[p2col][0][0]+p2x, colbox[p2col][0][1]+p2y);
        collisionbox2[0].position = sf::Vector2f(-colbox[p2col][1][0]+p2x, colbox[p2col][0][1]+p2y);
        collisionbox2[3].position = sf::Vector2f(-colbox[p2col][1][0]+p2x, colbox[p2col][1][1]+p2y);
        collisionbox2[2].position = sf::Vector2f(-colbox[p2col][0][0]+p2x, colbox[p2col][1][1]+p2y);
        collisionbox2[4].position = sf::Vector2f(-colbox[p2col][1][0]+p2x, colbox[p2col][0][1]+p2y);
        }

        sf::VertexArray Hurtbox2(sf::Lines,hurtboxcount[p2frame]*8);
        for(int i=0;i<hurtboxcount[p2frame];i++){
            Hurtbox2[0+i*8].color=sf::Color::Blue;
            Hurtbox2[1+i*8].color=sf::Color::Blue;
            Hurtbox2[2+i*8].color=sf::Color::Blue;
            Hurtbox2[3+i*8].color=sf::Color::Blue;
            Hurtbox2[4+i*8].color=sf::Color::Blue;
            Hurtbox2[5+i*8].color=sf::Color::Blue;
            Hurtbox2[6+i*8].color=sf::Color::Blue;
            Hurtbox2[7+i*8].color=sf::Color::Blue;
            if(p2right==true){
            Hurtbox2[0+i*8].position = sf::Vector2f(hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            Hurtbox2[1+i*8].position = sf::Vector2f(hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            Hurtbox2[2+i*8].position = sf::Vector2f(hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            Hurtbox2[3+i*8].position = sf::Vector2f(hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[4+i*8].position = sf::Vector2f(hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[5+i*8].position = sf::Vector2f(hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[6+i*8].position = sf::Vector2f(hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[7+i*8].position = sf::Vector2f(hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            }
            else{
            Hurtbox2[1+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            Hurtbox2[0+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            Hurtbox2[7+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            Hurtbox2[5+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[6+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][1][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[3+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[4+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][1][1]+p2y);
            Hurtbox2[2+i*8].position = sf::Vector2f(-hurtbox[p2frame][i][0][0]+p2x, hurtbox[p2frame][i][0][1]+p2y);
            }
        }

        sf::VertexArray Hitbox2(sf::Lines,hitboxcount[p2frame]*8);
        for(int i=0;i<hitboxcount[p2frame];i++){
            Hitbox2[0+i*8].color=sf::Color::Red;
            Hitbox2[1+i*8].color=sf::Color::Red;
            Hitbox2[2+i*8].color=sf::Color::Red;
            Hitbox2[3+i*8].color=sf::Color::Red;
            Hitbox2[4+i*8].color=sf::Color::Red;
            Hitbox2[5+i*8].color=sf::Color::Red;
            Hitbox2[6+i*8].color=sf::Color::Red;
            Hitbox2[7+i*8].color=sf::Color::Red;
            if(p2right==true){
            Hitbox2[0+i*8].position = sf::Vector2f(hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            Hitbox2[1+i*8].position = sf::Vector2f(hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            Hitbox2[2+i*8].position = sf::Vector2f(hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            Hitbox2[3+i*8].position = sf::Vector2f(hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[4+i*8].position = sf::Vector2f(hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[5+i*8].position = sf::Vector2f(hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[6+i*8].position = sf::Vector2f(hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[7+i*8].position = sf::Vector2f(hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            }
            else{
            Hitbox2[1+i*8].position = sf::Vector2f(-hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            Hitbox2[0+i*8].position = sf::Vector2f(-hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            Hitbox2[7+i*8].position = sf::Vector2f(-hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            Hitbox2[5+i*8].position = sf::Vector2f(-hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[6+i*8].position = sf::Vector2f(-hitbox[p2frame][i][1][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[3+i*8].position = sf::Vector2f(-hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[4+i*8].position = sf::Vector2f(-hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][1][1]+p2y);
            Hitbox2[2+i*8].position = sf::Vector2f(-hitbox[p2frame][i][0][0]+p2x, hitbox[p2frame][i][0][1]+p2y);
            }
        }

        pausetext.setString("Paused");

        pausetext.setPosition(200.f, 0.f);
        p1.setPosition(p1x-64,p1y-64);
        p2.setPosition(p2x-64,p2y-64);

		window.clear();
		window.draw(background);
		window.draw(p1);
		window.draw(p2);

		if(seeboxes==true){
            window.draw(collisionbox1);
            window.draw(Hurtbox1);
            window.draw(Hitbox1);
            window.draw(collisionbox2);
            window.draw(Hurtbox2);
            window.draw(Hitbox2);
		}
		if(pause==true)window.draw(pausetext);
		window.display();
	}
	return 0;
}
