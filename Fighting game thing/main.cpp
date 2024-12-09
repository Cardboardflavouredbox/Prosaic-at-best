#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <random>
#include <deque>
#include <string.h>
#include <math.h>

using namespace std;
std::deque<char>dirkeys,ukey,ikey,okey,kkey,dirkeys2,ukey2,ikey2,okey2,kkey2;

std::random_device rd;
std::mt19937 gen(rd());

short combo=0,roundframecount=0,
animlib[256][64][2]={
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{1,1},
                    {0,2},{1,2}
                    },//idle (0)
                    {
                    {3,3},{1,3},

                    {0,0},{1,0},{-1},
                    {0,1},{2,0},{3,0},
                    {0,2},{1,2},{-1}
                    },//stand u1 (1)
                    {
                    {3,3},{1,3},

                    {0,0},{1,0},{-1},
                    {0,1},{2,1},{3,1},
                    {0,2},{1,2},{-1}
                    },//stand u2 (2)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{4,0},
                    {0,2},{4,1}
                    },//stand i1 (3)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{5,0},
                    {0,2},{5,1}
                    },//stand i2 (4)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{6,0},
                    {0,2},{6,1}
                    },//stand i3 (5)
                    {
                    {3,3},{1,3},

                    {0,0},{1,0},{-1},
                    {0,1},{7,0},{8,0},
                    {0,2},{7,1},{8,1}
                    },//stand i4 (6)
                    {
                    {3,3},{1,3},

                    {0,0},{1,0},{-1},
                    {0,1},{9,0},{10,0},
                    {0,2},{9,1},{10,1}
                    },//stand i5 (7)
                    {
                    {2,3},{1,3},

                    {0,3},{1,3},
                    {0,4},{1,4},
                    {0,5},{1,5}
                    },//crouch (8)
                    {
                    {2,3},{1,3},

                    {4,9},{5,9},
                    {4,10},{5,10},
                    {4,11},{5,11}
                    },//hit (9)
                    {
                    {3,3},{1,3},

                    {0,3},{1,3},{-1},
                    {0,4},{1,4},{-1},
                    {0,5},{0,7},{1,7}
                    },//crouch u1 (10)
                    {
                    {3,3},{1,3},

                    {0,3},{1,3},{-1},
                    {0,4},{1,4},{-1},
                    {0,5},{0,6},{1,6}
                    },//crouch u2 (11)
                    {
                    {2,3},{1,3},

                    {0,3},{2,3},
                    {0,4},{2,4},
                    {0,5},{2,5}
                    },//crouch i1 (12)
                    {
                    {2,3},{1,3},

                    {0,3},{3,3},
                    {0,4},{3,4},
                    {0,5},{3,5}
                    },//crouch i2 (13)
                    {
                    {2,3},{1,3},

                    {0,3},{4,3},
                    {0,4},{4,4},
                    {0,5},{4,5}
                    },//crouch i3 (14)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{1,1},
                    {5,4},{6,4}
                    },//walk left1 (15)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{1,1},
                    {7,4},{8,4}
                    },//walk left2 (16)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{1,1},
                    {5,5},{6,5}
                    },//walk right1 (17)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,1},{1,1},
                    {7,5},{8,5}
                    },//walk right2 (18)
                    {
                    {4,1},{2,1},

                    {2,8},{3,8},{4,8},{-1}
                    },//knockdown (19)
                    {
                    {2,3},{1,3},

                    {5,2},{6,2},
                    {5,3},{6,3},
                    {0,2},{1,2}
                    },//specialA1 (20)
                    {
                    {2,3},{1,3},

                    {7,2},{8,2},
                    {7,3},{8,3},
                    {0,2},{1,2}
                    },//specialA2 (21)
                    {
                    {2,3},{1,3},

                    {9,2},{10,2},
                    {9,3},{10,3},
                    {0,2},{1,2}
                    },//specialA3 (22)
                    {
                    {2,3},{1,3},

                    {11,2},{12,2},
                    {11,3},{12,3},
                    {0,2},{1,2}
                    },//specialA4 (23)
                    {
                    {3,3},{1,3},

                    {9,4},{10,4},{-1},
                    {9,5},{10,5},{11,5},
                    {0,2},{1,2},{-1}
                    },//specialA5 (24)
                    {
                    {3,3},{1,3},

                    {12,4},{13,4},{-1},
                    {12,5},{13,5},{14,5},
                    {0,2},{1,2},{-1}
                    },//specialA6 (25)
                    {
                    {2,3},{1,3},

                    {5,6},{6,6},
                    {5,7},{6,7},
                    {5,8},{6,8}
                    },//stand o1 (26)
                    {

                    {3,3},{2,3},

                    {-1},{8,6},{9,6},
                    {7,7},{8,7},{9,7},
                    {-1},{8,8},{9,8},
                    },//stand o2 (27)
                    {
                    {4,3},{2,3},

                    {-1},{11,6},{-1},{-1},
                    {10,7},{11,7},{12,7},{12,6},
                    {10,8},{11,8},{12,8},{-1}
                    },//stand o3 (28)
                    {
                    {3,3},{2,3},

                    {-1},{6,9},{7,9},
                    {7,6},{6,10},{7,10},
                    {-1},{6,11},{7,11}
                    },//stand o4 (29)
                    {
                    {3,3},{1,3},

                    {8,9},{9,9},{-1},
                    {8,10},{9,10},{10,6},
                    {8,11},{9,11},{-1}
                    },//stand o5 (30)
                    {
                    {4,3},{1,3},

                    {-1},{11,9},{12,9},{-1},
                    {10,10},{11,10},{12,10},{10,9},
                    {10,11},{11,11},{12,11},{-1}
                    },//stand o6 (31)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {2,2},{3,2},
                    {0,2},{1,2}
                    },//stand block (32)
                    {
                    {2,3},{1,3},

                    {0,3},{1,3},
                    {2,6},{3,6},
                    {2,7},{3,7}
                    },//crouch block (33)
                    {
                    {2,3},{1,3},

                    {13,0},{14,0},
                    {11,0},{12,0},
                    {11,1},{12,1}
                    },//specialB1 (34)
                    {
                    {2,3},{1,3},

                    {13,1},{14,1},
                    {13,2},{14,2},
                    {13,3},{14,3}
                    },//specialB2 (35)
                    {
                    {2,4},{1,4},

                    {-1},{17,0},
                    {15,0},{16,0},
                    {15,1},{16,1},
                    {15,2},{16,2}
                    },//specialB3 (36)
                    {
                    {2,4},{1,4},

                    {-1},{17,1},
                    {17,5},{17,2},
                    {17,6},{17,3},
                    {17,7},{17,4}
                    },//specialB4 (37)
                    {
                    {2,3},{1,3},

                    {0,3},{1,3},
                    {0,4},{13,6},
                    {0,5},{13,7}
                    },//crouch i1 (38)
                    {
                    {2,3},{1,3},

                    {15,3},{16,3},
                    {15,4},{16,4},
                    {15,5},{16,5}
                    },//crouch i2 (39)
                    {
                    {3,3},{1,3},

                    {0,3},{1,3},{-1},
                    {14,6},{15,6},{16,6},
                    {14,7},{15,7},{-1}
                    },//crouch i3 (40)
                    {
                    {3,3},{1,3},

                    {15,8},{16,8},{-1},
                    {15,9},{16,9},{16,7},
                    {13,8},{14,8},{-1}
                    },//crouch i4 (41)
                    {
                    {3,3},{1,3},

                    {17,10},{17,9},{-1},
                    {15,10},{16,10},{17,11},
                    {15,11},{16,11},{-1}
                    },//crouch i5 (42)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,10},{1,10},
                    {0,11},{1,11}
                    },//jumprise(43)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,8},{1,8},
                    {0,9},{1,9}
                    },//jumpfall(44)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,10},{1,10},
                    {0,11},{2,9}
                    },//jump u1(45)
                    {
                    {2,3},{1,3},

                    {0,0},{1,0},
                    {0,10},{1,10},
                    {0,11},{3,9}
                    },//jump u2(46)
                    {
                    {3,3},{2,3},

                    {-1},{0,0},{1,0},
                    {2,10},{0,12},{1,12},
                    {-1},{0,2},{1,2}
                    },//specialC1 (47)
                    {
                    {3,3},{2,3},

                    {-1},{0,0},{1,0},
                    {2,11},{0,13},{1,13},
                    {-1},{0,2},{1,2}
                    },//specialC2 (48)
                    {
                    {3,3},{2,3},

                    {-1},{0,0},{1,0},
                    {3,10},{2,12},{3,12},
                    {-1},{0,2},{1,2}
                    },//specialC3 (49)
                    {
                    {4,3},{2,3},
                    {-1},{0,0},{1,0},{-1},
                    {3,11},{2,13},{3,13},{4,13},
                    {-1},{0,2},{1,2},{-1}
                    },//specialC4 (50)
                    {
                    {3,3},{1,3},

                    {0,0},{1,0},{-1},
                    {4,12},{5,12},{6,12},
                    {0,2},{1,2},{-1}
                    },//specialC5 (51)
                    {
                    {3,3},{1,3},

                    {0,0},{1,0},{-1},
                    {5,13},{6,13},{7,13},
                    {0,2},{1,2},{-1}
                    },//specialC6 (52)
                    {
                    {2,3},{1,3},

                    {13,9},{14,9},
                    {13,10},{14,10},
                    {13,11},{14,11}
                    },//crouch hit(53)
                    {
                    {1,2},{0,2},

                    {7,12},
                    {-1}
                    },//projectile1(54)
                    {
                    {1,2},{0,2},

                    {8,12},
                    {-1}
                    },//projectile2(55)
                    {
                    {2,3},{1,3},

                    {8,13},{9,13},
                    {10,12},{11,12},
                    {10,13},{11,13}
                    },//hit2 (56)
                    {
                    {2,3},{1,3},

                    {12,12},{12,13},
                    {13,12},{14,12},
                    {13,13},{14,13}
                    },//crouch hit2(57)
                    {
                    {1,3},{0,3},

                    {15,12},
                    {15,13},
                    {-1}
                    },//projectile end1(58)
                    {
                    {1,3},{0,3},

                    {16,12},
                    {16,13},
                    {-1}
                    },//projectile end2(59)
                    {
                    {1,3},{0,3},

                    {17,12},
                    {17,13},
                    {-1}
                    }//projectile end3(60)
                   },
                   hurtboxcount[256]={2,3,3,2,2,2,3,3,2,2,3,3,2,3,3,2,2,2,2,0,2,2,2,2,3,3,2,3,3,3,3,3,2,2,0,2,3,3,2,2,2,3,3,2,2,2,2,2,2,2,3,3,3,2,1,1,2,2,0,0,0},
                   hitboxcount[256]={0,1,1,1,1,1,1,1,1,1,1};
float comboscaling=100.0,
colbox[16][1][2][2]={{{{-7,-10},{9,32}}},//standing
                    {{{-7,-1},{9,32}}},//crouching
                    {{{-31,20},{16,32}}},//knockdown
                    {{{0,0},{0,0}}},//grabbed
                    },
hurtbox[256][8][2][2]={
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//idle (0)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{4,0},{18,9}}},//stand u1 (1)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{4,0},{20,6}}},//stand u2 (2)
                    {{{-11,0},{14,32}},{{-7,-15},{9,0}}},//stand i1 (3)
                    {{{-11,0},{15,32}},{{-7,-15},{9,0}}},//stand i2 (4)
                    {{{-11,0},{14,32}},{{-7,-15},{9,0}}},//stand i3 (5)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{0,12},{24,19}}},//stand i4 (6)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{4,12},{26,18}}},//stand i5 (7)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},//crouch (8)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//hit (9)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{4,24},{22,32}}},//crouch u1 (10)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{4,26},{24,32}}},//crouch u2 (11)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},//crouch i1 (12)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{6,-8},{15,20}}},//crouch i2 (13)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{6,-11},{15,20}}},//crouch i3 (14)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//walk left1 (15)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//walk left2 (16)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//walk right1 (17)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//walk right2 (18)
                    {-1},//knockdown (19)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//specialA1 (20)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//specialA2 (21)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//specialA3 (22)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//specialA4 (23)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-4,0},{24,12}}},//specialA5 (24)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-2,0},{26,12}}},//specialA6 (25)
                    {{{-15,1},{11,32}},{{-9,-14},{7,1}}},//stand o1 (26)
                    {{{-16,0},{9,32}},{{-12,-14},{4,1}},{{4,2},{16,8}}},//stand o2 (27)
                    {{{-22,2},{7,32}},{{-16,-13},{0,2}},{{0,0},{18,9}}},//stand o3 (28)
                    {{{-22,2},{9,32}},{{-15,-14},{6,2}},{{0,0},{16,9}}},//stand o4 (29)
                    {{{-11,0},{11,32}},{{-7,-15},{14,0}},{{4,0},{28,9}}},//stand o5 (30)
                    {{{-11,0},{15,32}},{{2,-13},{19,1}},{{6,1},{35,10}}},//stand o6 (31)
                    {{{-11,0},{14,32}},{{-7,-15},{9,0}}},//stand block (32)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},//crouch block (33)
                    {-1},//specialB1 (34)
                    {{{-11,1},{14,32}},{{-5,-9},{11,6}}},//specialB2 (35)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-5,-26},{15,16}}},//specialB3 (36)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-5,-30},{15,-4}}},//specialB4 (37)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},//crouch i1(38)
                    {{{-12,9},{13,32}},{{-8,-6},{8,9}}},//crouch i2(39)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},//crouch i3(40)
                    {{{-10,9},{13,32}},{{-6,-6},{10,9}},{{9,9},{24,14}}},//crouch i4(41)
                    {{{-10,9},{13,32}},{{-5,-6},{11,9}},{{9,9},{24,14}}},//crouch i5(42)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//jumprise(43)
                    {{{-10,0},{12,29}},{{-7,-15},{9,0}}},//jumpfall(44)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//jump u1(45)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//jump u2(46)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//specialC1 (47)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//specialC2 (48)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//specialC3 (49)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-2,0},{26,12}}},//specialC4 (50)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-2,0},{26,12}}},//specialC5 (51)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-2,0},{26,12}}},//specialC6 (52)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},//crouch hit(53)
                    {{{0,-4},{13,12}}},//projectile1(54)
                    {{{0,-4},{13,12}}},//projectile2(55)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},//hit2 (56)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},//crouch hit2(57)
                    {-1},//projectile end1(58)
                    {-1},//projectile end2(59)
                    {-1},//projectile end3(60)
                    },
hitbox[32][8][2][2]={{0},//idle (0)
                    {{{4,-1},{22,7}}},//stand u(1)
                    {{{5,11},{30,20}}},//stand i(2)
                    {{{5,25},{26,32}}},//crouch u(3)
                    {{{6,-13},{19,20}}},//crouch o(4)
                    {{{-2,-2},{27,14}}},//specialA(5)
                    {{{8,2},{36,9}}},//stand o(6)
                    {{{7,3},{16,18}}},//specialB1(7)
                    {{{-6,-32},{16,-4}}},//specialB2(8)
                    {{{9,8},{27,15}}},//crouch i(9)
                    {{{0,16},{18,32}}},//jump u(10)
                    };
bool flash=true;

class attackdata{
public:
    short movetype,hitstun,blockstun,kdown,hitwait;
    float kback,launch,grab[2];
    bool pushaway=true;

};

class projectile
{
public:
    float x,y,movex,movey,dmg,kback,mgain,launch;
    short movetype,animloop=0,looplen=0,loopanim[256]={},
    frame=0,hitstop,hitstun,blockstun,hitcount=0,hitstopped=0,knockdown=0;
    bool right,hit=false,multihit=false;
    std::deque<int>endanim;
};

class characterselect : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(64);
        return true;
    }
    void setcharselect(short xlen,short ylen,short x, short y){
        float spacingx=48,spacingy=48;
        for(short i=0;i<ylen;i++)
            for(short j=0;j<xlen;j++){
            sf::Vertex* tri = &m_vertices[6*(i*xlen+j)];
            tri[0].position = sf::Vector2f(x+spacingx*j,y+spacingy*i);
            tri[1].position = sf::Vector2f(x+32+spacingx*j,y+spacingy*i);
            tri[2].position = sf::Vector2f(x+spacingx*j,y+32+spacingy*i);
            tri[3].position = sf::Vector2f(x+spacingx*j,y+32+spacingy*i);
            tri[4].position = sf::Vector2f(x+32+spacingx*j,y+spacingy*i);
            tri[5].position = sf::Vector2f(x+32+spacingx*j,y+32+spacingy*i);
            tri[0].texCoords = sf::Vector2f((i*xlen+j)*32,0);
            tri[1].texCoords = sf::Vector2f((i*xlen+j+1)*32,0);
            tri[2].texCoords = sf::Vector2f((i*xlen+j)*32,32);
            tri[3].texCoords = sf::Vector2f((i*xlen+j)*32,32);
            tri[4].texCoords = sf::Vector2f((i*xlen+j+1)*32,0);
            tri[5].texCoords = sf::Vector2f((i*xlen+j+1)*32,32);
        }
    }

    void setselect(short xlen,short ylen,short x, short y){
        for(short i=0;i<ylen;i++)
            for(short j=0;j<xlen;j++){
            sf::Vertex* tri = &m_vertices[6*(i*xlen+j)];
            for(short k=0;k<6;k++){
                if(x==j&&y==i)tri[k].color=sf::Color(255,255,255,255);
                else tri[k].color=sf::Color(170,170,170,255);
            }
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

class menu : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(64);
        return true;
    }
    void setmenu(short cnt,float x,float y,float spacingx, float spacingy,short tcode){
        for(short i=0;i<cnt;i++){
            sf::Vertex* tri = &m_vertices[6*i];
            tri[0].position = sf::Vector2f(x+spacingx*i,y+spacingy*i);
            tri[1].position = sf::Vector2f(x+64+spacingx*i,y+spacingy*i);
            tri[2].position = sf::Vector2f(x+spacingx*i,y+16+spacingy*i);
            tri[3].position = sf::Vector2f(x+spacingx*i,y+16+spacingy*i);
            tri[4].position = sf::Vector2f(x+64+spacingx*i,y+spacingy*i);
            tri[5].position = sf::Vector2f(x+64+spacingx*i,y+16+spacingy*i);
            tri[0].texCoords = sf::Vector2f(tcode*64,i*16);
            tri[1].texCoords = sf::Vector2f(64+tcode*64,i*16);
            tri[2].texCoords = sf::Vector2f(tcode*64,i*16+16);
            tri[3].texCoords = sf::Vector2f(tcode*64,i*16+16);
            tri[4].texCoords = sf::Vector2f(64+tcode*64,i*16);
            tri[5].texCoords = sf::Vector2f(64+tcode*64,i*16+16);
        }

    }

    void setcolor(short cnt,bool invisible,short placeinput){
        for(short i=0;i<cnt;i++){
            sf::Vertex* tri = &m_vertices[6*i];
            for(short j=0;j<6;j++){
                if(invisible)tri[j].color=sf::Color::Transparent;
                else if(placeinput==i)tri[j].color=sf::Color(85,85,85,255);
                else tri[j].color=sf::Color(255,255,255,255);
            }
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


class character : public sf::Drawable, public sf::Transformable
{
public:

    void load(const sf::Texture tread,bool shadow)
    {
        m_tileset=tread;

        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(300);

        for (unsigned int i = 0; i < 6; ++i)
            for (unsigned int j = 0; j < 8; ++j)
            {
                sf::Vertex* tri = &m_vertices[(j + i * 8) * 6];
                if(shadow){
                    tri[0].position = sf::Vector2f(0+j*16,0+i*4);
                    tri[1].position = sf::Vector2f(16+j*16,0+i*4);
                    tri[2].position = sf::Vector2f(0+j*16,4+i*4);
                    tri[3].position = sf::Vector2f(0+j*16,4+i*4);
                    tri[4].position = sf::Vector2f(16+j*16,0+i*4);
                    tri[5].position = sf::Vector2f(16+j*16,4+i*4);
                    for(unsigned k=0;k<6;k++)tri[k].color=sf::Color::Black;
                }
                else{
                    tri[0].position = sf::Vector2f(0+j*16,0+i*16);
                    tri[1].position = sf::Vector2f(16+j*16,0+i*16);
                    tri[2].position = sf::Vector2f(0+j*16,16+i*16);
                    tri[3].position = sf::Vector2f(0+j*16,16+i*16);
                    tri[4].position = sf::Vector2f(16+j*16,0+i*16);
                    tri[5].position = sf::Vector2f(16+j*16,16+i*16);
                }
            }
    }

    void setanim(short anim[][2],bool right){
        short sizex=anim[0][0],sizey=anim[0][1],basex=anim[1][0],basey=anim[1][1];
        for (unsigned int i = 0; i < 6; ++i)
            for (unsigned int j = 0; j < 8; ++j){
            if(j<4-basex||4+sizex-basex<=j||i<6-basey||6+sizey-basey<=i){
                if(right){sf::Vertex* tri = &m_vertices[(j + i * 8) * 6];for(short k=0;k<6;k++)tri[k].texCoords= sf::Vector2f(0,0);}
                else{sf::Vertex* tri = &m_vertices[(7-j + i * 8) * 6];for(short k=0;k<6;k++)tri[k].texCoords= sf::Vector2f(0,0);}
            }
            else{
                short temp=j-4+basex+sizex*(i-6+basey)+2,tempx=anim[temp][0],tempy=anim[temp][1];
                if(right){
                    sf::Vertex* tri = &m_vertices[(j + i * 8) * 6];
                    tri[0].texCoords = sf::Vector2f(tempx*16, tempy*16);
                    tri[1].texCoords = sf::Vector2f(tempx*16+16, tempy*16);
                    tri[2].texCoords = sf::Vector2f(tempx*16, tempy*16+16);
                    tri[3].texCoords = sf::Vector2f(tempx*16, tempy*16+16);
                    tri[4].texCoords = sf::Vector2f(tempx*16+16, tempy*16);
                    tri[5].texCoords = sf::Vector2f(tempx*16+16, tempy*16+16);

                }
                else{
                    sf::Vertex* tri = &m_vertices[(7-j + i * 8) * 6];
                    tri[0].texCoords = sf::Vector2f(tempx*16+16, tempy*16);
                    tri[1].texCoords = sf::Vector2f(tempx*16, tempy*16);
                    tri[2].texCoords = sf::Vector2f(tempx*16+16, tempy*16+16);
                    tri[3].texCoords = sf::Vector2f(tempx*16+16, tempy*16+16);
                    tri[4].texCoords = sf::Vector2f(tempx*16, tempy*16);
                    tri[5].texCoords = sf::Vector2f(tempx*16, tempy*16+16);

                }
            }
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
class hitflash : public sf::Drawable, public sf::Transformable
{
public:
    void create(float px,float py,bool hit){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        if(hit){
            for(unsigned int i=0;i<3;i++){
                float x,y,x2,y2;
                std::uniform_int_distribution<int> dis(0,1);
                if(dis(gen)==0){
                    if(dis(gen)==0)y=0;
                    else y=240;
                    std::uniform_int_distribution<int> dis(0,256);
                    x=dis(gen);
                    std::uniform_int_distribution<int> dis2(-16,16);
                    x2=x+dis2(gen);
                    y2=y;
                }
                else {
                    if(dis(gen)==0)x=0;
                    else x=256;
                    std::uniform_int_distribution<int> dis(0,240);
                    y=dis(gen);
                    std::uniform_int_distribution<int> dis2(-16,16);
                    x2=x;
                    y2=y+dis2(gen);
                }
                sf::Vertex* triangles = &m_vertices[i*3];
                triangles[i*3].position = sf::Vector2f(px,py);
                triangles[i*3+1].position = sf::Vector2f(x,y);
                triangles[i*3+2].position = sf::Vector2f(x2,y2);
            }
        }
        else{
            for(unsigned int i=0;i<3;i++){
                sf::Vertex* triangles = &m_vertices[i*3];
                triangles[i*3].position = sf::Vector2f(0,0);
                triangles[i*3+1].position = sf::Vector2f(0,0);
                triangles[i*3+2].position = sf::Vector2f(0,0);
            }
        }
        m_lines.setPrimitiveType(sf::Lines);
        m_lines.resize(32);
        for(unsigned int i=0;i<8;i++){
            float angle=i * 3.14f / 4.f;
            float x=std::cos(angle),y=std::sin(angle);
            sf::Vertex* line = &m_lines[i*2];
            line[i*2].position = sf::Vector2f(px+x,py+y);
            line[i*2+1].position = sf::Vector2f(x*16+px,y*16+py);
            if(hit){line[i*2].color=sf::Color::White;line[i*2+1].color=sf::Color::White;}
            else {line[i*2].color=sf::Color (85, 255, 255);line[i*2+1].color=sf::Color (85, 255, 255);}
        }
        m_circle.setPrimitiveType(sf::Lines);
        m_circle.resize(64);
        sf::Vertex* circle = &m_circle[32];
        for(unsigned int i=0;i<12;i++){
            float angle=i * 3.14f / 6.f,angle2=(i+1) * 3.14f / 6.f;;
            circle[i*2].position = sf::Vector2f((std::cos(angle))*4+px,(std::sin(angle))*4+py);
            circle[i*2+1].position = sf::Vector2f((std::cos(angle2))*4+px,(std::sin(angle2))*4+py);
            if(hit){circle[i*2].color=sf::Color::White;circle[i*2+1].color=sf::Color::White;}
            else {circle[i*2].color=sf::Color (85, 255, 255);circle[i*2+1].color=sf::Color (85, 255, 255);}
        }
    }


    void update(float px,float py,bool hit){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        for(unsigned int i=0;i<3;i++){
            sf::Vertex* triangles = &m_vertices[i*3];
            if(frame%2==0&&frame>3&&flash){
            triangles[i*3].color = sf::Color::Transparent;
            triangles[i*3+1].color = sf::Color::Transparent;
            triangles[i*3+2].color = sf::Color::Transparent;
            }
            else{
            triangles[i*3].color = sf::Color::White;
            triangles[i*3+1].color = sf::Color::White;
            triangles[i*3+2].color = sf::Color::White;
            }
        }
        m_lines.setPrimitiveType(sf::Lines);
        m_lines.resize(32);
        for(unsigned int i=0;i<8;i++){
            float angle=i * 3.14f / 4.f;
            float x=std::cos(angle),y=std::sin(angle);
            sf::Vertex* line = &m_lines[i*2];
            line[i*2].position = sf::Vector2f(px+x*(frame+8),py+y*(frame+8));
            line[i*2+1].position = sf::Vector2f(x*(float(frame)/8+16)+px,y*(float(frame)/8+16)+py);
            if(frame>3&&frame%2==1&&flash){line[i*2].color=sf::Color::Transparent;line[i*2+1].color=sf::Color::Transparent;}
            else {
                    if(hit){line[i*2].color=sf::Color::White;line[i*2+1].color=sf::Color::White;}
                    else {line[i*2].color=sf::Color (85, 255, 255);line[i*2+1].color=sf::Color (85, 255, 255);}
            }
        }
        m_circle.setPrimitiveType(sf::Lines);
        m_circle.resize(64);
        sf::Vertex* circle = &m_circle[32];
        for(unsigned int i=0;i<12;i++){
            float angle=i * 3.14f / 6.f,angle2=(i+1) * 3.14f / 6.f;;
            circle[i*2].position = sf::Vector2f((std::cos(angle))*(4+frame)+px,(std::sin(angle))*(4+frame)+py);
            circle[i*2+1].position = sf::Vector2f((std::cos(angle2))*(4+frame)+px,(std::sin(angle2))*(4+frame)+py);

            if(frame>3&&frame%2==1&&flash){circle[i*2].color=sf::Color::Transparent;circle[i*2+1].color=sf::Color::Transparent;}
            else {
                    if(hit){circle[i*2].color=sf::Color::White;circle[i*2+1].color=sf::Color::White;}
                    else {circle[i*2].color=sf::Color (85, 255, 255);circle[i*2+1].color=sf::Color (85, 255, 255);}
            }
        }
    }
    short frame;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = NULL;

        target.draw(m_vertices);
        target.draw(m_lines);
        target.draw(m_circle, states);
    }
   sf::VertexArray m_vertices,m_lines,m_circle;

};

class meterbar : public sf::Drawable, public sf::Transformable
{
public:
    void create(float meter,float meter2){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices2.setPrimitiveType(sf::Triangles);
        m_vertices3.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        m_vertices2.resize(32);
        m_vertices3.resize(32);
        sf::Vertex* triangles = &m_vertices[12];
        triangles[0].position = sf::Vector2f(35,221);
        triangles[1].position = sf::Vector2f(93,221);
        triangles[2].position = sf::Vector2f(35,227);
        triangles[3].position = sf::Vector2f(35,227);
        triangles[4].position = sf::Vector2f(93,221);
        triangles[5].position = sf::Vector2f(93,227);

        triangles[6].position = sf::Vector2f(163,221);
        triangles[7].position = sf::Vector2f(221,221);
        triangles[8].position = sf::Vector2f(163,227);
        triangles[9].position = sf::Vector2f(163,227);
        triangles[10].position = sf::Vector2f(221,221);
        triangles[11].position = sf::Vector2f(221,227);
        sf::Vertex* tri = &m_vertices2[12];
        sf::Vertex* tri2 = &m_vertices3[12];
        float temp=(meter-(int(meter)/100)*100);
        temp=temp*58/100;
        tri[0].position = sf::Vector2f(35,221);
        tri[1].position = sf::Vector2f(35+temp,221);
        tri[2].position = sf::Vector2f(35,227);
        tri[3].position = sf::Vector2f(35,227);
        tri[4].position = sf::Vector2f(35+temp,221);
        tri[5].position = sf::Vector2f(35+temp,227);
        tri2[0].position = sf::Vector2f(35,225);
        tri2[1].position = sf::Vector2f(35+temp,225);
        tri2[2].position = sf::Vector2f(35,227);
        tri2[3].position = sf::Vector2f(35,227);
        tri2[4].position = sf::Vector2f(35+temp,225);
        tri2[5].position = sf::Vector2f(35+temp,227);
        temp=(meter2-(int(meter2)/100)*100);
        temp=temp*58/100;
        tri[6].position = sf::Vector2f(221-temp,221);
        tri[7].position = sf::Vector2f(221,221);
        tri[8].position = sf::Vector2f(221-temp,227);
        tri[9].position = sf::Vector2f(221-temp,227);
        tri[10].position = sf::Vector2f(221,221);
        tri[11].position = sf::Vector2f(221,227);
        tri2[6].position = sf::Vector2f(221-temp,225);
        tri2[7].position = sf::Vector2f(221,225);
        tri2[8].position = sf::Vector2f(221-temp,227);
        tri2[9].position = sf::Vector2f(221-temp,227);
        tri2[10].position = sf::Vector2f(221,225);
        tri2[11].position = sf::Vector2f(221,227);
        for(unsigned int i=0;i<12;i++){triangles[i].color = sf::Color (0, 0, 0);tri[i].color = sf::Color (85, 255, 255);tri2[i].color = sf::Color (0, 170, 170);}
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = NULL;

        target.draw(m_vertices,states);
        target.draw(m_vertices2,states);
        target.draw(m_vertices3,states);
    }
   sf::VertexArray m_vertices,m_vertices2,m_vertices3;

};

class healthbar : public sf::Drawable, public sf::Transformable
{
public:
    void create(float hp,float hp2){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices2.setPrimitiveType(sf::Triangles);
        m_vertices3.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        m_vertices2.resize(32);
        m_vertices3.resize(32);
        sf::Vertex* triangles = &m_vertices[12];
        triangles[0].position = sf::Vector2f(18,10);
        triangles[1].position = sf::Vector2f(106,10);
        triangles[2].position = sf::Vector2f(22,18);
        triangles[3].position = sf::Vector2f(22,18);
        triangles[4].position = sf::Vector2f(106,10);
        triangles[5].position = sf::Vector2f(110,18);

        triangles[6].position = sf::Vector2f(146,18);
        triangles[7].position = sf::Vector2f(234,18);
        triangles[8].position = sf::Vector2f(150,10);
        triangles[9].position = sf::Vector2f(150,10);
        triangles[10].position = sf::Vector2f(234,18);
        triangles[11].position = sf::Vector2f(238,10);
        sf::Vertex* tri = &m_vertices2[12];
        sf::Vertex* tri2 = &m_vertices3[12];
        float temp=hp/1000*88;
        tri[0].position = sf::Vector2f(106-temp,10);
        tri[1].position = sf::Vector2f(106,10);
        tri[2].position = sf::Vector2f(110-temp,18);
        tri[3].position = sf::Vector2f(110-temp,18);
        tri[4].position = sf::Vector2f(106,10);
        tri[5].position = sf::Vector2f(110,18);
        tri2[0].position = sf::Vector2f(109-temp,16);
        tri2[1].position = sf::Vector2f(109,16);
        tri2[2].position = sf::Vector2f(110-temp,18);
        tri2[3].position = sf::Vector2f(110-temp,18);
        tri2[4].position = sf::Vector2f(109,16);
        tri2[5].position = sf::Vector2f(110,18);
        temp=hp2*88/1000;
        tri[6].position = sf::Vector2f(146,18);
        tri[7].position = sf::Vector2f(146+temp,18);
        tri[8].position = sf::Vector2f(150,10);
        tri[9].position = sf::Vector2f(150,10);
        tri[10].position = sf::Vector2f(146+temp,18);
        tri[11].position = sf::Vector2f(150+temp,10);
        tri2[6].position = sf::Vector2f(146,18);
        tri2[7].position = sf::Vector2f(146+temp,18);
        tri2[8].position = sf::Vector2f(147,16);
        tri2[9].position = sf::Vector2f(147,16);
        tri2[10].position = sf::Vector2f(146+temp,18);
        tri2[11].position = sf::Vector2f(147+temp,16);
        for(unsigned int i=0;i<12;i++){triangles[i].color = sf::Color (85, 85, 85);tri[i].color = sf::Color (85, 255, 85);tri2[i].color = sf::Color (0, 170, 0);}
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = NULL;

        target.draw(m_vertices,states);
        target.draw(m_vertices2,states);
        target.draw(m_vertices3,states);
    }
   sf::VertexArray m_vertices,m_vertices2,m_vertices3;

};

class timeui : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
        return true;
    }
    void create(){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        sf::Vertex* triangles = &m_vertices[12];
        triangles[0].position = sf::Vector2f(120,8);
        triangles[1].position = sf::Vector2f(120,24);
        triangles[2].position = sf::Vector2f(128,8);
        triangles[3].position = sf::Vector2f(128,8);
        triangles[4].position = sf::Vector2f(120,24);
        triangles[5].position = sf::Vector2f(128,24);

        triangles[6].position = sf::Vector2f(128,8);
        triangles[7].position = sf::Vector2f(128,24);
        triangles[8].position = sf::Vector2f(136,8);
        triangles[9].position = sf::Vector2f(136,8);
        triangles[10].position = sf::Vector2f(128,24);
        triangles[11].position = sf::Vector2f(136,24);
    }
    void timeset(short time){
        sf::Vertex* tri = &m_vertices[12];
        short temp=(time/10+1)*8;
        tri[0].texCoords = sf::Vector2f(temp,0);
        tri[1].texCoords = sf::Vector2f(temp,16);
        tri[2].texCoords = sf::Vector2f(temp+8,0);
        tri[3].texCoords = sf::Vector2f(temp+8,0);
        tri[4].texCoords = sf::Vector2f(temp,16);
        tri[5].texCoords = sf::Vector2f(temp+8,16);
        temp=(time%10+1)*8;
        tri[6].texCoords = sf::Vector2f(temp,0);
        tri[7].texCoords = sf::Vector2f(temp,16);
        tri[8].texCoords = sf::Vector2f(temp+8,0);
        tri[9].texCoords = sf::Vector2f(temp+8,0);
        tri[10].texCoords = sf::Vector2f(temp,16);
        tri[11].texCoords = sf::Vector2f(temp+8,16);
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices,states);

    }
   sf::VertexArray m_vertices;
   sf::Texture m_tileset;

};


class comboui : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
        return true;
    }
    void create(bool right,float slide){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(16);
        m_tileset.setRepeated(true);
        sf::Vertex* tri = &m_vertices[6];
        if(right){
            tri[0].position = sf::Vector2f(0-slide,32);
            tri[1].position = sf::Vector2f(0-slide,80);
            tri[2].position = sf::Vector2f(48-slide,32);
            tri[3].position = sf::Vector2f(48-slide,32);
            tri[4].position = sf::Vector2f(0-slide,80);
            tri[5].position = sf::Vector2f(48-slide,80);
        }
        else{
            tri[0].position = sf::Vector2f(256+slide,32);
            tri[1].position = sf::Vector2f(256+slide,80);
            tri[2].position = sf::Vector2f(208+slide,32);
            tri[3].position = sf::Vector2f(208+slide,32);
            tri[4].position = sf::Vector2f(256+slide,80);
            tri[5].position = sf::Vector2f(208+slide,80);
        }
        tri[0].texCoords = sf::Vector2f(0,0);
        tri[1].texCoords = sf::Vector2f(0,48);
        tri[2].texCoords = sf::Vector2f(48,0);
        tri[3].texCoords = sf::Vector2f(48,0);
        tri[4].texCoords = sf::Vector2f(0,48);
        tri[5].texCoords = sf::Vector2f(48,48);
        m_vertices2.setPrimitiveType(sf::Triangles);
        m_vertices2.resize(16);
        sf::Vertex* tri2 = &m_vertices2[6];
        float temp=comboscaling/100*42;
        if(right){
            tri2[0].position = sf::Vector2f(2-slide,68);
            tri2[1].position = sf::Vector2f(2-slide,74);
            tri2[2].position = sf::Vector2f(2+temp-slide,68);
            tri2[3].position = sf::Vector2f(2+temp-slide,68);
            tri2[4].position = sf::Vector2f(2-slide,74);
            tri2[5].position = sf::Vector2f(2+temp-slide,74);
        }
        else{
            tri2[0].position = sf::Vector2f(254+slide,68);
            tri2[1].position = sf::Vector2f(254+slide,74);
            tri2[2].position = sf::Vector2f(254-temp+slide,68);
            tri2[3].position = sf::Vector2f(254-temp+slide,68);
            tri2[4].position = sf::Vector2f(254+slide,74);
            tri2[5].position = sf::Vector2f(254-temp+slide,74);
        }
        m_vertices3.setPrimitiveType(sf::Triangles);
        m_vertices3.resize(16);
        sf::Vertex* tri3 = &m_vertices3[6];
        if(right){
            tri3[0].position = sf::Vector2f(0-slide,64);
            tri3[1].position = sf::Vector2f(0-slide,80);
            tri3[2].position = sf::Vector2f(44-slide,64);
            tri3[3].position = sf::Vector2f(44-slide,64);
            tri3[4].position = sf::Vector2f(0-slide,80);
            tri3[5].position = sf::Vector2f(44-slide,80);
        }
        else{
            tri3[0].position = sf::Vector2f(256+slide,64);
            tri3[1].position = sf::Vector2f(256+slide,80);
            tri3[2].position = sf::Vector2f(212+slide,64);
            tri3[3].position = sf::Vector2f(212+slide,64);
            tri3[4].position = sf::Vector2f(256+slide,80);
            tri3[5].position = sf::Vector2f(212+slide,80);
        }
        for(short i=0;i<6;i++)tri3[i].color=sf::Color (85, 85, 85);
    }


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices3);
        target.draw(m_vertices2);
        target.draw(m_vertices,states);
    }
   sf::VertexArray m_vertices,m_vertices2,m_vertices3;
   sf::Texture m_tileset;

};




class inputlist : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
        return true;
    }
    void create(std::deque<char>keylist,bool right){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(768);
        m_tileset.setRepeated(true);
        for(short i=0;i<keylist.size()/5;i++)
            for(short j=0;j<4;j++){
                sf::Vertex* tri = &m_vertices[6*(j+i*4)];
                if(right){
                    tri[6*(j+i*4)].position = sf::Vector2f(j*16,80+16*i);
                    tri[1+6*(j+i*4)].position = sf::Vector2f(j*16,96+16*i);
                    tri[2+6*(j+i*4)].position = sf::Vector2f(j*16+16,80+16*i);
                    tri[3+6*(j+i*4)].position = sf::Vector2f(j*16+16,80+16*i);
                    tri[4+6*(j+i*4)].position = sf::Vector2f(j*16,96+16*i);
                    tri[5+6*(j+i*4)].position = sf::Vector2f(j*16+16,96+16*i);
                }
                else{
                    tri[6*(j+i*4)].position = sf::Vector2f(240-j*16,80+16*i);
                    tri[1+6*(j+i*4)].position = sf::Vector2f(240+-j*16,96+16*i);
                    tri[2+6*(j+i*4)].position = sf::Vector2f(240-j*16+16,80+16*i);
                    tri[3+6*(j+i*4)].position = sf::Vector2f(240-j*16+16,80+16*i);
                    tri[4+6*(j+i*4)].position = sf::Vector2f(240-j*16,96+16*i);
                    tri[5+6*(j+i*4)].position = sf::Vector2f(240-j*16+16,96+16*i);
                }
            }
        for(short i=0;i<keylist.size()/5;i++){
            char temp[5]={'0','0','0','0','0'};
            short tempcnt=0;
            if(keylist[i*5+4]!='0'&&keylist[i*5]!='5')temp[tempcnt++]=keylist[i*5+4];
            if(keylist[i*5+3]=='u')temp[tempcnt++]='u';
            if(keylist[i*5+2]=='i')temp[tempcnt++]='i';
            if(keylist[i*5+1]=='o')temp[tempcnt++]='o';
            if(keylist[i*5]=='k')temp[tempcnt++]='k';
            for(short j=0;j<4;j++){
                sf::Vertex* tri = &m_vertices[6*(j+i*4)];
                if(temp[j]=='0'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(0,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(0,0);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(0,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(0,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(0,0);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(0,0);
                }
                else if(temp[j]=='u'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(0,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(0,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(16,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(16,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(0,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(16,16);
                }
                else if(temp[j]=='i'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(16,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(16,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(32,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(32,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(16,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(32,16);
                }
                else if(temp[j]=='o'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(32,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(32,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(48,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(48,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(32,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(48,16);
                }
                else if(temp[j]=='k'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(48,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(48,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(48,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(64,16);
                }
                else if(temp[j]=='1'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(96,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(96,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(96,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                }
                else if(temp[j]=='2'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(64,16);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                }
                else if(temp[j]=='3'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(96,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(96,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(96,16);
                }
                else if(temp[j]=='4'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(64,16);
                }
                else if(temp[j]=='6'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(64,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(64,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                }
                else if(temp[j]=='7'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(96,16);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(96,0);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(96,0);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                }
                else if(temp[j]=='8'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(64,16);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(64,16);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(64,0);
                }
                else if(temp[j]=='9'){
                    tri[6*(j+i*4)].texCoords = sf::Vector2f(80,16);
                    tri[1+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[2+6*(j+i*4)].texCoords = sf::Vector2f(96,16);
                    tri[3+6*(j+i*4)].texCoords = sf::Vector2f(96,16);
                    tri[4+6*(j+i*4)].texCoords = sf::Vector2f(80,0);
                    tri[5+6*(j+i*4)].texCoords = sf::Vector2f(96,0);
                }
            }
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices,states);

    }
   sf::VertexArray m_vertices;
   sf::Texture m_tileset;

};

class box : public sf::Drawable, public sf::Transformable
{
public:
    void create(float px,float py,float xy[][2][2],bool right,short count,sf::Color col){
        m_vertices.setPrimitiveType(sf::Lines);
        m_vertices.resize(64);
        for(unsigned int i=0;i<count;i++){
            sf::Vertex* box = &m_vertices[i*8];
            if(right){
            box[i*8].position = sf::Vector2f(xy[i][0][0]+px,xy[i][0][1]+py);
            box[i*8+1].position = sf::Vector2f(xy[i][1][0]+px,xy[i][0][1]+py);
            box[i*8+2].position = sf::Vector2f(xy[i][1][0]+px,xy[i][0][1]+py);
            box[i*8+3].position = sf::Vector2f(xy[i][1][0]+px,xy[i][1][1]+py);
            box[i*8+4].position = sf::Vector2f(xy[i][1][0]+px,xy[i][1][1]+py);
            box[i*8+5].position = sf::Vector2f(xy[i][0][0]+px,xy[i][1][1]+py);
            box[i*8+6].position = sf::Vector2f(xy[i][0][0]+px,xy[i][1][1]+py);
            box[i*8+7].position = sf::Vector2f(xy[i][0][0]+px,xy[i][0][1]+py);
            }
            else{
            box[i*8].position = sf::Vector2f(-xy[i][1][0]+px,xy[i][0][1]+py);
            box[i*8+1].position = sf::Vector2f(-xy[i][0][0]+px,xy[i][0][1]+py);
            box[i*8+2].position = sf::Vector2f(-xy[i][0][0]+px,xy[i][0][1]+py);
            box[i*8+3].position = sf::Vector2f(-xy[i][0][0]+px,xy[i][1][1]+py);
            box[i*8+4].position = sf::Vector2f(-xy[i][0][0]+px,xy[i][1][1]+py);
            box[i*8+5].position = sf::Vector2f(-xy[i][1][0]+px,xy[i][1][1]+py);
            box[i*8+6].position = sf::Vector2f(-xy[i][1][0]+px,xy[i][1][1]+py);
            box[i*8+7].position = sf::Vector2f(-xy[i][1][0]+px,xy[i][0][1]+py);
            }
            for(unsigned int j=0;j<8;j++)box[i*8+j].color = col;
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        // draw the vertex array
        target.draw(m_vertices,states);
    }
   sf::VertexArray m_vertices;

};

void keypresscheck(sf::Keyboard::Key keycode,char *key){
    if(sf::Keyboard::isKeyPressed(keycode)){if(*key=='0')*key='2';else if(*key=='2')*key='1';}else *key='0';
}

bool cmdcheck(int playercode,int len,char s[][5]){
    //s[][0]==num,s[][1]==u,s[][2]==i,s[][3]==o,s[][4]==k
    short temp=0;
    for(int j=0;j<15;j++){
        char dir,u,i,o,k;
        bool skip=false;
        if(playercode==1)dir=dirkeys[j],u=ukey[j],i=ikey[j],o=okey[j],k=kkey[j];
        else if(playercode==2)dir=dirkeys2[j],u=ukey2[j],i=ikey2[j],o=okey2[j],k=kkey2[j];
        //if(u=='1')u='0';if(i=='1')i='0';if(o=='1')o='0';if(k=='1')k='0';
        if(s[temp][0]=='0'&&(dir=='5'||dir==s[temp+1][0])){s[temp][0]=dir;skip=true;}

        if((dir!=s[temp][0]&&dir!=s[temp-1][0]))break;
        if(dir==s[temp][0]&&u==s[temp][1]&&i==s[temp][2]&&o==s[temp][3]&&k==s[temp][4]){temp++;if(skip)temp++;}
        if(temp>=len)break;
    }
    if(temp>=len)return true;
    else return false;

}

int chooseaction(int playercode, bool air, char keydir, char u, char i, char o,char k,float meter){
    char c236[4][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}},
        c214[4][5]={{'0','0','0','0','0'},{'4','0','0','0','0'},{'1','0','0','0','0'},{'2','0','0','0','0'}},
        c623[4][5]={{'0','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'6','0','0','0','0'}},
        c323[4][5]={{'0','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'3','0','0','0','0'}},
        c626[4][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'2','0','0','0','0'},{'6','0','0','0','0'}},
        c636[4][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'6','0','0','0','0'}},
        c63236[6][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'3','0','0','0','0'},{'6','0','0','0','0'}},
        c6236[5][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'6','0','0','0','0'}};
            if(!air){
                if(keydir=='1'||keydir=='2'||keydir=='3'){
                    //crouching actions
                    if(o=='2'){
                        c623[0][3]='2';c323[0][3]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 23;//special B strong
                        else return 14;//strong normal
                        c623[0][3]='0';c323[0][3]='0';
                    }
                    else if(i=='2'){
                        c623[0][2]='2';c323[0][2]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 22;//special B middle
                        else return 13;//middle normal
                        c623[0][2]='0';c323[0][2]='0';
                    }
                    else if(u=='2'){
                        c623[0][1]='2';c323[0][1]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 21;//special B weak
                        else return 12;//weak normal
                        c623[0][1]='0';c323[0][1]='0';
                    }
                    else if(k=='2'){
                        c623[0][4]='2';c323[0][4]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 24;//special B gimmick
                        else return 15;//gimmick
                        c623[0][4]='0';c323[0][4]='0';
                    }
                    else if(keydir=='1')return 20;//crouching block
                    else return 11;//crouch
                }
                else{
                    //grounded actions
                    if(u=='2'&&i=='2'){
                        c214[0][1]='2';c214[0][2]='2';
                        if(cmdcheck(playercode,4,c214)&&meter>=100)return 32;//super
                        else return 25;//grab
                        c214[0][1]='0';c214[0][2]='0';
                    }
                    if(o=='2'){
                        c214[0][3]='2';c236[0][3]='2';c636[0][3]='2';c626[0][3]='2';c63236[0][3]='2';c6236[0][3]='2';
                        if(cmdcheck(playercode,4,c214))return 30;//special C strong
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 23;//special B strong
                        else if(cmdcheck(playercode,4,c236))return 18;//special A strong
                        else if(u=='2'||i=='2')return 25;//grab
                        else return 10;//strong normal
                        c214[0][3]='0';c236[0][3]='0';c636[0][3]='0';c626[0][3]='0';c63236[0][3]='0';c6236[0][3]='0';
                    }
                    else if(i=='2'){
                        c214[0][2]='2';c236[0][2]='2';c636[0][2]='2';c626[0][2]='2';c63236[0][2]='2';c6236[0][2]='2';
                        if(cmdcheck(playercode,4,c214))return 29;//special C middle
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 22;//special B middle
                        else if(cmdcheck(playercode,4,c236))return 17;//special A middle
                        else return 9;//middle normal
                        c214[0][2]='0';c236[0][2]='0';c636[0][2]='0';c626[0][2]='0';c63236[0][2]='0';c6236[0][2]='0';
                    }
                    else if(u=='2'){
                        c214[0][1]='2';c236[0][1]='2';c636[0][1]='2';c626[0][1]='2';c63236[0][1]='2';c6236[0][1]='2';
                        if(cmdcheck(playercode,4,c214))return 28;//special C weak
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 21;//special B weak
                        else if(cmdcheck(playercode,4,c236))return 16;//special A weak
                        else return 8;//weak normal
                        c214[0][1]='0';c236[0][1]='0';c636[0][1]='0';c626[0][1]='0';c63236[0][1]='0';c6236[0][1]='0';
                    }
                    else if(k=='2'){
                        c214[0][4]='2';c236[0][4]='2';c636[0][4]='2';c626[0][4]='2';c63236[0][4]='2';c6236[0][4]='2';
                        if(cmdcheck(playercode,4,c214))return 31;//special C gimmick
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 24;//special B gimmick
                        else if(cmdcheck(playercode,4,c236))return 19;//special A gimmick
                        else return 15;//gimmick
                        c214[0][4]='0';c236[0][4]='0';c636[0][4]='0';c626[0][4]='0';c63236[0][4]='0';c6236[0][4]='0';
                    }
                    else if(keydir=='4'){
                        char temp[3][5]={{'4','0','0','0','0'},{'5','0','0','0','0'},{'4','0','0','0','0'}};
                        if(cmdcheck(playercode,3,temp))return 2;//leftdash
                        else return 1;//leftwalk
                    }
                    else if(keydir=='6'){
                        char temp[3][5]={{'6','0','0','0','0'},{'5','0','0','0','0'},{'6','0','0','0','0'}};
                        if(cmdcheck(playercode,3,temp))return 4;//rightdash
                        else return 3;//rightwalk
                    }
                    else if(keydir=='8')return 5;//upjump
                    else if(keydir=='7')return 6;//leftjump
                    else if(keydir=='9')return 7;//rightjump
                    else return 0;//neutural

                }
            }
            else{
                //jump actions
                if(u=='2')return 8;//weak normal
                else if(i=='2')return 9;//middle normal
                else if(o=='2')return 10;//strong normal
                return 0;
                }
}

void boolfill(bool *arr,bool value,short a[]){
    short temp=0;
    for(int i=0;i<64;i++){
        if(a[temp]==i){arr[i]=value;temp++;}
        else if(value)arr[i]=false;
        else arr[i]=true;
    }
}


void characterdata(std::deque<int> &animq,std::deque<int> &hitboxanim,std::deque<int> &atkfx,std::deque<projectile> &c_projectile,short *hbframe,bool cancel[],bool *air,short anim[][2],short *act,short *col,short *frame,
    bool *whiff,float *x,float *y,float *jumpx,float *jumpy,bool *right,bool *hit,short *block,float enemyx,float enemyy,short *hitstun,
    float *kback,bool *slide,bool *multihit,short *hitstop,short *buffer,bool *neutural,float *launch,
    float *hp, float enemyhp, float *dmg,bool *comboed,short *kdown,short *kdowned,short *movewaitx,short *movewaity, float *pushaway,float *enemypaway,
    short *movetype,short *blockstun,float grab[],short *grabstate,short enemygstate,short *landdelay,float *meter,float *mgain,attackdata enemy,short *superstop){
    if(*kdowned>0&&animq.size()<10&&!*comboed&&!*act==0&&*hp>0){
        for(short i=0;i<3;i++){animq.push_back(8);}
        *kdowned=0;combo=0;
    }
    if(*hit){
        *hit=false;animq.clear();hitboxanim.clear();atkfx.clear();
        *movetype=-1;grab[0]=0;grab[1]=0;*grabstate=-1;*landdelay=0;*movewaitx=-1;*movewaity=-1;*mgain=0;
        if(*air&&enemy.launch==0){
                *jumpy=enemy.kback/6*5*(comboscaling+100)/200;
                if(*jumpy>0)*jumpy*=-1;
        }
        else *jumpy=0;
        if(*hp<=0)*block=-1;
        if(((enemy.movetype==1||enemy.movetype==2)&&*block==1)||((enemy.movetype==3||enemy.movetype==2)&&*block==0)||*block==2){
            *slide=true;
            if(*block==2){
                if(enemy.movetype==1)*block=1;
                else *block=0;
            }
            if(*block==0)for(short i=0;i<enemy.hitwait+enemy.blockstun;i++)animq.push_back(32);
            if(*block==1)for(short i=0;i<enemy.hitwait+enemy.blockstun;i++)animq.push_back(33);
            *block=2;
        }
        else{
            if(enemy.launch>0){*jumpy=-enemy.launch*(comboscaling+100)/200;*air=true;}
            if(*air||(enemy.grab[0]!=0||enemy.grab[1]!=0))*slide=false;
            else *slide=true;
            *comboed=true;
            if(enemy.grab[0]!=0||enemy.grab[1]!=0)*col=3;
            if(*col==1)for(short i=0;i<enemy.hitwait+enemy.hitstun;i++)animq.push_back(53);
            else for(short i=0;i<enemy.hitwait+enemy.hitstun;i++)animq.push_back(9);
            if(enemy.kdown==2||*hp<=0)*kdowned=2;
            else if(enemy.kdown==1||enemy.launch>0||*air)*kdowned=1;
            else *kdowned=0;
        }
        if((*x<-110||*x>360)&&enemy.kback!=0&&(enemy.grab[0]==0&&enemy.grab[1]==0)&&enemy.pushaway){
                if(enemy.kback>0)*pushaway+=enemy.kback;
                else*pushaway-=enemy.kback;
                *pushaway+=int(enemy.launch/2);
        }
        else if(enemy.grab[0]==0&&enemy.grab[1]==0){
                if(*air&&enemy.launch==0){
                    *jumpx=-int(enemy.kback/3);
                }
                else{
                    *jumpx=-enemy.kback;
                }
        }
        short temp[1]={-1};boolfill(cancel,true,temp);
    }
    else if(animq.empty()&&*movewaitx==-1&&*movewaity==-1&&!*air){
        if(*comboed&&*kdowned>0){
            *col=2;*comboed=false;
            for(short i=0;i<32;i++){animq.push_back(19);}
        }
        else if(*kdowned>0&&*hp>0){
            for(short i=0;i<3;i++){animq.push_back(8);}
            *kdowned=0;combo=0;
        }
        else {
            short temp[1]={-1};boolfill(cancel,true,temp);
            if(!*neutural){*jumpx=0;*jumpy=0;}
            *neutural=true;*hitstun=0;*blockstun=0;*kback=0;*hit=false;
            *slide=false;*multihit=false;*dmg=0;*launch=0;*kdown=0;*mgain=0;
            *movetype=-1;*block=-1;grab[0]=0;grab[1]=0;*grabstate=-1;
            if(*comboed){combo=0;*comboed=false;}
        }
    }

    if(enemygstate==3&&*act==25){
            *grabstate=0;
            *slide=true;
            if(*x<enemyx)*jumpx=-8;
            else *jumpx=4;
            *pushaway=8;
            animq.clear();hitboxanim.clear();atkfx.clear();
            for(short i=0;i<enemy.hitwait;i++)animq.push_back(32);
        }

    if(enemyhp<=0||roundframecount/60>=99)*act=0;
    if(*grabstate==1&&!*whiff)*grabstate=3;
    if(*grabstate==2&&!*whiff)*grabstate=3;
    if(*grabstate==3){
            if(enemygstate==0)*grabstate=-1;
            else if(animq.size()<12){
                if(*act==1)*act=27;
                else *act=26;
            }
    }
    if(!*hit&&((animq.empty()&&*movewaitx==-1&&*movewaity==-1)||((cancel[*act]==true)&&((!*whiff)||*movetype==0||*grabstate==3)))){
        if(cancel[*act]==true){
            *buffer=0;*slide=false;*hitstun=0;*blockstun=0;*kback=0;*dmg=0;*launch=0;*kdown=0;*movewaitx=-1;*movewaity=-1;
            *movetype=-1;grab[0]=0;grab[1]=0;*landdelay=0;if(!*air){*jumpx=0;*jumpy=0;}*mgain=0;
            short temp[0]={};boolfill(cancel,true,temp);
            animq.clear();hitboxanim.clear();atkfx.clear();
        }

        if(*act==1)*block=0;
        else if(*act==20)*block=1;
        else *block=-1;

        if(*act==0){//neutural
            if(!*air){
                if(*x<enemyx)*right=true;
                else *right=false;
                memcpy(anim,animlib[0],sizeof(animlib[0]));
            }
            *col=0;*frame=0;*block=-1;
        }
        else if(*act==1){//left walk
            *col=0;
            memcpy(anim,animlib[15],sizeof(animlib[0]));
            if(*right)*x-=3;else *x+=3;
            if(*x<enemyx)*right=true;else *right=false;
        }
        else if(*act==2){*col=0;*air=true;*jumpy=-2.0;if(*right)*jumpx=-7;else*jumpx=7;*landdelay=7;}//left dash
        else if(*act==3){//right walk
            *col=0;
            memcpy(anim,animlib[17],sizeof(animlib[0]));
            if(*right)*x+=3;else *x-=3;
            if(*x<enemyx)*right=true;else *right=false;
        }
        else if(*act==4){*col=0;*air=true;*jumpy=-2.0;if(*right)*jumpx=7;else*jumpx=-7;*landdelay=7;}//right dash
        else if(*act==5){*col=0;*jumpy=-12.0;*movewaity=4;animq.insert(animq.begin(),{8,8,8,43});*landdelay=5;}//up jump
        else if(*act==6){*col=0;*jumpy=-12.0;*movewaitx=4;*movewaity=4;if(*right)*jumpx=-3;else*jumpx=3;animq.insert(animq.begin(),{8,8,8,43});*landdelay=3;}//left jump
        else if(*act==7){*col=0;*jumpy=-12.0;*movewaitx=4;*movewaity=4;if(*right)*jumpx=3;else*jumpx=-3;animq.insert(animq.begin(),{8,8,8,43});*landdelay=3;}//right jump
        else if(*act==8){//u (light normal)
            if(*air){
                *col=0;*multihit=false;*hitstop=12;*kback=2;*hitstun=8;*blockstun=1;*dmg=12;*movetype=3;*landdelay=3;*mgain=4;
                animq.insert(animq.begin(),{43,43,45,45,46,46,46});
                hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,10,10,10,10,10,10,10,10});
            }
            else{
                *col=0;*multihit=false;*hitstop=12;*kback=4;*hitstun=4;*blockstun=1;*dmg=12;*movetype=2;*mgain=4;
                animq.insert(animq.begin(),{1,1,1,2,2,2,1,1,1});
                hitboxanim.insert(hitboxanim.begin(),{0,0,0,1});
                short temp[15]={9,10,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill(cancel,true,temp);
            }
        }
        else if(*act==9){//i (middle normal)
            if(*air){
                *col=0;*multihit=false;*hitstop=13;*kback=3;*hitstun=10;*blockstun=3;*dmg=25;*movetype=3;*landdelay=3;*mgain=6;
                animq.insert(animq.begin(),{3,4,5,5,5,6,7,7,7,7});
                hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,2,2,2,2});
            }
            else{
                *col=0;*multihit=false;*hitstop=13;*kback=5;*hitstun=1;*blockstun=-6;*slide=true;*dmg=27;*movetype=2;*mgain=6;
                animq.insert(animq.begin(),{3,4,5,5,5,5,5,6,7,7,7,7,7,6,5,5,4,4,3,3});
                hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,2,2});
                short temp[14]={10,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill(cancel,true,temp);
                *movewaitx=7;
                if(*right)*jumpx=3;
                else *jumpx=-3;
            }
        }
        else if(*act==10){//o (heavy normal)
            if(*air){
                *col=0;*multihit=false;*hitstop=14;*kback=3;*hitstun=12;*blockstun=6;*dmg=33;*movetype=3;*landdelay=3;*mgain=8;
                animq.insert(animq.begin(),{3,4,5,5,5,5,5,6,7,7,7,7,7});
                hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,2,2,2,2,2,2});
            }
            else{
                *col=0;*multihit=false;*hitstop=14;*kback=6;*hitstun=-1;*blockstun=-8;*slide=true;*dmg=35;*movetype=2;*mgain=8;
                animq.insert(animq.begin(),{26,26,27,27,28,28,28,28,28,29,30,31,31,31,31,31,31,31,30,29,28,28,28,27,27,27,26,26,26});
                hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,0,6,6,6});
                short temp[13]={16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill(cancel,true,temp);
                *movewaitx=9;
                if(*right)*jumpx=5;
                else *jumpx=-5;
            }
        }
        else if(*act==11||*act==20){//crouch & crouch block
            if(*x<enemyx)*right=true;
            else *right=false;
            *col=1;*frame=8;
            memcpy(anim,animlib[8],sizeof(animlib[8]));
        }
        else if(*act==12){//crouch u
            *col=1;*multihit=false;*hitstop=12;*kback=5;*hitstun=4;*blockstun=0;*dmg=11;*movetype=1;*mgain=4;
            animq.insert(animq.begin(),{10,10,10,11,11,11,10,10,10});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,3});
            short temp[15]={13,14,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill(cancel,true,temp);
        }
        else if(*act==13){//crouch i
            *col=1;*multihit=false;*hitstop=13;*kback=5;*hitstun=1;*blockstun=-4;*slide=true;*dmg=24;*movetype=1;*mgain=6;
            animq.insert(animq.begin(),{38,38,39,39,39,39,40,41,42,42,42,41,41,40,40,39,39,39,38,38,38,38});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,9,9,9});
            short temp[14]={14,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill(cancel,true,temp);
            *movewaitx=7;
            if(*right)*jumpx=2;
            else *jumpx=-2;
        }
        else if(*act==14){//crouch o
            *col=1;*multihit=false;*hitstop=14;*kback=3;*hitstun=1;*blockstun=-5;*slide=true;*movewaitx=7;*dmg=35;*launch=10;*kdown=1;*movetype=2;*mgain=8;
            animq.insert(animq.begin(),{12,12,12,12,12,12,13,14,14,14,14,14,14,13,12,12,12,12,12});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,4,4,4,4,4});
            if(*right)*jumpx=4;else *jumpx=-4;
            short temp[13]={16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill(cancel,true,temp);
        }
        else if(*act==15){}//k (gimmick)
        else if(*act==16){//special A (u)
            *col=0;*multihit=false;*hitstop=12;*kback=7;*hitstun=1;*blockstun=-3;*slide=true;*movewaitx=6;*dmg=22;*movetype=2;*mgain=7;
            animq.insert(animq.begin(),{20,21,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,22,21,20,20});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,5,5});
            cancel[32]=true;
            if(*right)*jumpx=5;else *jumpx=-5;
        }
        else if(*act==17){//special A (i)
            *col=0;*multihit=false;*hitstop=13;*kback=7;*hitstun=-1;*blockstun=-4;*slide=true;*movewaitx=9;*dmg=29;*kdown=2;*movetype=2;*mgain=8;
            animq.insert(animq.begin(),{20,20,21,21,22,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,23,22,22,21,21,20,20});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,0,5,5});
            cancel[32]=true;
            if(*right)*jumpx=6;else *jumpx=-6;
        }
        else if(*act==18){//special A (o)
            *col=0;*multihit=false;*hitstop=14;*kback=0;*hitstun=0;*blockstun=-5;*slide=true;*movewaitx=10;*dmg=36;*kdown=1;*launch=11;*movetype=2;*mgain=9;
            animq.insert(animq.begin(),{20,20,20,21,21,22,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,23,22,22,22,21,21,20,20,20});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,5,5});
            cancel[32]=true;
            if(*right)*jumpx=7;else *jumpx=-7;
        }
        else if(*act==19){//special A (k)
            *col=0;*multihit=false;*slide=true;*movewaitx=6;*movetype=0;
            animq.insert(animq.begin(),{20,21,22,22,22,22,21,20});
            cancel[32]=true;
            if(*right)*jumpx=4;else *jumpx=-4;
        }
        else if(*act==21){//special B(u)
            *col=0;*multihit=false;*hitstop=13;*kback=5;*hitstun=5;*blockstun=-5;*slide=true;*movewaity=4;*movewaitx=4;*dmg=28;*mgain=7;
            *kdown=2;*launch=8;*movetype=2;*jumpy=-11;*landdelay=5;
            animq.insert(animq.begin(),{34,34,34,35,35,35,36,37,37,37,37,37,37,37,37,37});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,7,0,0,0,8,8,8,8,8,8,8,8,8});
            cancel[32]=true;
            if(*right)*jumpx=6;else *jumpx=-6;
        }
        else if(*act==22){//special B(i)
            *col=0;*multihit=false;*hitstop=14;*kback=5;*hitstun=5;*blockstun=-5;*slide=true;*movewaity=4;*movewaitx=2;*dmg=39;*mgain=8;
            *kdown=2;*launch=9;*movetype=2;*jumpy=-12;*landdelay=5;
            animq.insert(animq.begin(),{34,34,34,35,35,35,36,37,37,37,37,37,37,37,37,37,37});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,7,0,0,0,8,8,8,8,8,8,8,8,8,8});
            cancel[32]=true;
            if(*right)*jumpx=7;else *jumpx=-7;
        }
        else if(*act==23){//special B(o)
            *col=0;*multihit=false;*hitstop=15;*kback=5;*hitstun=5;*blockstun=-5;*slide=true;*movewaity=5;*dmg=51;*mgain=9;
            *kdown=2;*launch=10;*movetype=2;*jumpy=-13;*landdelay=5;
            animq.insert(animq.begin(),{34,34,34,34,34,35,35,35,36,37,37,37,37,37,37,37,37,37,37,37});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,7,0,0,0,0,8,8,8,8,8,8,8,8,8,8,8,8});
            cancel[32]=true;
            if(*right)*jumpx=8;else *jumpx=-8;
        }
        else if(*act==24){//special B(k)
            *col=0;*multihit=false;*slide=true;*movewaity=4;*jumpy=-1;
            animq.insert(animq.begin(),{34,34,34,34});
            cancel[32]=true;
            if(*right)*jumpx=6;else *jumpx=-6;
        }
        else if(*act==25){//grab
            *col=0;*multihit=false;*hitstop=0;*kback=0;*hitstun=0;*blockstun=31;*slide=true;*movewaitx=6;*dmg=0;*movetype=4;grab[0]=21;grab[1]=0;*grabstate=1;
            animq.insert(animq.begin(),{20,20,21,21,22,22,22,22,23,24,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,24,24,23,23,22,22,21,21,20,20});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,5});
            if(*right)*jumpx=5;else *jumpx=-5;
            short temp[2]={26,27};boolfill(cancel,true,temp);
        }
        else if(*act==26){//grab attack forward
            *col=1;*multihit=false;*hitstop=15;*kback=3;*hitstun=1;*blockstun=0;*slide=true;*movewaitx=3;*dmg=100;*launch=10;*kdown=2;*movetype=4;*grabstate=-1;*mgain=12;
            animq.insert(animq.begin(),{12,12,12,13,14,14,14,14,14,14,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,4});
            if(*right)*jumpx=4;else *jumpx=-4;
        }
        else if(*act==27){//grab attack backward
            *col=1;*multihit=false;*hitstop=15;*kback=-3;*hitstun=1;*blockstun=0;*slide=true;*movewaitx=3;*dmg=100;*launch=10;*kdown=2;*movetype=4;*grabstate=-1;*mgain=12;
            animq.insert(animq.begin(),{12,12,12,13,14,14,14,14,14,14,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12});
            hitboxanim.insert(hitboxanim.begin(),{0,0,0,0,4});
            if(*right)*jumpx=4;else *jumpx=-4;
        }
        else if(*act==28){//special C (u)
            *col=0;*multihit=false;*hitstop=12;*kback=3;*hitstun=3;*blockstun=1;*dmg=22;*movetype=2;*mgain=7;
            animq.insert(animq.begin(),{47,47,47,48,49,49,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            atkfx.insert(atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1});
            cancel[32]=true;
        }
        else if(*act==29){//special C (i)
            *col=0;*multihit=false;*hitstop=12;*kback=3;*hitstun=4;*blockstun=2;*dmg=22;*movetype=2;*mgain=8;
            animq.insert(animq.begin(),{47,47,47,48,49,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            atkfx.insert(atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,0,2});
            cancel[32]=true;
        }
        else if(*act==30){//special C (o)
            *col=0;*multihit=false;*hitstop=12;*kback=3;*hitstun=5;*blockstun=3;*dmg=22;*movetype=2;*mgain=9;
            animq.insert(animq.begin(),{47,47,47,48,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            atkfx.insert(atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,3});
            cancel[32]=true;
        }
        else if(*act==31){//special C (k)
            *col=0;*multihit=false;
            animq.insert(animq.begin(),{47,47,47,48,49,49,49,50,50,51,51,51,51,51,52,52});
            cancel[32]=true;
        }
        else if(*act==32){//super
            *col=0;*multihit=false;*hitstop=14;*kback=8;*launch=5;*hitstun=6;*blockstun=5;*slide=true;*movewaitx=15;*dmg=150;*movetype=2;*mgain=0;*meter-=100;
            animq.insert(animq.begin(),{47,47,47,48,49,49,49,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            atkfx.insert(atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,4});
            if(*right)*jumpx=-9;else *jumpx=9;
        }
    }
    if(*movewaitx>0)*movewaitx-=1;
    else{*x+=*jumpx;*movewaitx=-1;}
    if(*movewaity>0)*movewaity-=1;
    else{if(*jumpy<0)*air=true;*y+=*jumpy;*movewaity=-1;}
    if(*slide&&*movewaitx==-1){
        if(*jumpx>0)*jumpx-=1;
        else if(*jumpx<0)*jumpx+=1;
    }
    if(*enemypaway>0){
            if(*air)*enemypaway=0;
            else{if(*x<enemyx)*x-=*enemypaway;else if(*x>enemyx)*x+=*enemypaway;*enemypaway-=1;}
    }
    if(*air){
            *block=-1;
            if(*comboed)*jumpy+=0.75;
            else *jumpy+=0.8;
            if(*jumpy>0){
                if(*neutural){memcpy(anim,animlib[44],sizeof(animlib[44]));*frame=44;}
            }
            if(*y>175){
                if(*kdowned>0){}//add downed landing animation
                if(!*comboed){*col=1;animq.clear();hitboxanim.clear();atkfx.clear();for(short i=0;i<*landdelay;i++)animq.push_back(8);}
                *landdelay=0;
                *movetype=0;
                *jumpx=0;*jumpy=0;*y=176;*air=false;
            }
        }
    if(!hitboxanim.empty()){
        *hbframe=hitboxanim[0];
        hitboxanim.pop_front();
    }
    else *hbframe=0;
    if(!animq.empty()){
        *neutural=false;*frame=animq[0];
        memcpy(anim,animlib[animq[0]],sizeof(animlib[animq[0]]));
        if(!(animq[0]==19&&*hp<=0)&&!(*air&&animq.size()==1))animq.pop_front();
    }
    if(enemygstate==3||enemygstate==4){
        if(*x<enemyx)*x=enemyx-enemy.grab[0];
        else *x=enemyx+enemy.grab[0];
        *y=enemyy-enemy.grab[1];
    }
    if(!atkfx.empty()){
        if(atkfx[0]==5)*superstop=20;
        if(atkfx[0]==1||atkfx[0]==2||atkfx[0]==3||atkfx[0]==4){//projectile
            *meter+=*mgain;
            projectile temp;
            temp.movetype=*movetype;
            temp.x=*x;temp.y=*y;
            if(atkfx[0]==1)temp.movex=4;
            else if(atkfx[0]==2)temp.movex=5;
            else if(atkfx[0]==3)temp.movex=6;
            else if(atkfx[0]==4)temp.movex=12;
            temp.movey=0;
            temp.hitcount=1;
            temp.hitstop=*hitstop;
            temp.hitstun=*hitstun;temp.blockstun=*blockstun;
            temp.dmg=*dmg;
            temp.mgain=*mgain;
            temp.kback=*kback;
            temp.right=*right;
            temp.multihit=*multihit;
            temp.looplen=2;
            temp.knockdown=*kdown;
            temp.loopanim[0]=54;
            temp.loopanim[1]=55;
            temp.launch=*launch;
            temp.endanim.insert(temp.endanim.begin(),{58,59,60});
            if(c_projectile.size()<8)c_projectile.push_back(temp);
                }
        atkfx.pop_front();
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(256,240), "Prosaic at Best");
    sf::Event event;
    sf::Sprite title;
    sf::Texture titletexture;
    if (!titletexture.loadFromFile("title.png"))window.close();
    title.setTexture(titletexture);
	menu menus;
	if (!menus.load("menu.png")){}
	menus.setmenu(6,144,120,0,16,0);
    window.setFramerateLimit(60);
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(256, 240)){}
    sf::Font font;
    if(!font.loadFromFile("PerfectDOSVGA437.ttf"))window.close();
    char keydir1='5',keydir2='5',u='0',i='0',o='0',k='0',u2='0',i2='0',o2='0',k2='0',menuup='0',menudown='0',menuleft='0',menuright='0',menuconfirm='0',menucancel='0';
    short menuselect=0;
    bool w,a,s,d,w2,a2,s2,d2,gamequit=false;
    float screenWidth = 256.f,screenHeight = 240.f;

    while(window.isOpen()){
        while (window.pollEvent(event))if (event.type == sf::Event::Closed)window.close();

        sf::Vector2u size = window.getSize();
        float  heightRatio = screenHeight / screenWidth,widthRatio = screenWidth / screenHeight;
        if (size.y * widthRatio <= size.x)size.x = size.y * widthRatio;
        else if (size.x * heightRatio <= size.y)size.y = size.x * heightRatio;
        window.setSize(size);

        keypresscheck(sf::Keyboard::U,&menuconfirm);
        keypresscheck(sf::Keyboard::W,&menuup);
        keypresscheck(sf::Keyboard::S,&menudown);

        if(menuup=='2'){menuselect--;if(menuselect<0)menuselect=5;}
        else if(menudown=='2'){menuselect++;if(menuselect>5)menuselect=0;}
        menus.setcolor(6,false,menuselect);

        window.clear();
        renderTexture.clear();

        renderTexture.draw(title);
        renderTexture.draw(menus);
        renderTexture.display();
        const sf::Texture& texture = renderTexture.getTexture();
        sf::Sprite rt(texture);
        window.draw(rt);
        window.display();

        if(menuconfirm=='2'&&menuselect==5)window.close();
        else if(menuconfirm=='2'&&menuselect!=4){

        characterselect charselect;
        if (!charselect.load("charactericon.png")){}
        charselect.setcharselect(4,2,32,144);
        short menux=0,menuy=0;
        while (window.isOpen()&&!gamequit){
            sf::Vector2u size = window.getSize();
            float  heightRatio = screenHeight / screenWidth,widthRatio = screenWidth / screenHeight;
            if (size.y * widthRatio <= size.x)size.x = size.y * widthRatio;
            else if (size.x * heightRatio <= size.y)size.y = size.x * heightRatio;
            window.setSize(size);
            while (window.pollEvent(event))if (event.type == sf::Event::Closed)window.close();
            keypresscheck(sf::Keyboard::U,&menuconfirm);
            keypresscheck(sf::Keyboard::I,&menucancel);
            keypresscheck(sf::Keyboard::W,&menuup);
            keypresscheck(sf::Keyboard::S,&menudown);
            keypresscheck(sf::Keyboard::A,&menuleft);
            keypresscheck(sf::Keyboard::D,&menuright);
            if(menuright=='2'&&menuleft!='2'){menux++;if(menux>3)menux=0;}
            if(menuright!='2'&&menuleft=='2'){menux--;if(menux<0)menux=3;}
            if(menudown=='2'&&menuup!='2'){menuy++;if(menuy>1)menuy=0;}
            if(menudown!='2'&&menuup=='2'){menuy--;if(menuy<0)menuy=1;}
            if(menuconfirm=='2')break;
            if(menucancel=='2'){gamequit=true;break;}
            charselect.setselect(4,2,menux,menuy);
            sf::RectangleShape rect(sf::Vector2f(256.f, 32.f)),rect2(sf::Vector2f(256.f, 112.f));
            rect.setFillColor(sf::Color(85, 85, 85));rect2.setFillColor(sf::Color(85, 85, 85));
            rect2.setPosition(0,128);
            sf::Texture bgtexture;
            if (!bgtexture.loadFromFile("stage1.png")){}
            sf::Sprite bg(bgtexture);
            bg.setPosition(-125.f,0.f);

            window.clear();
            renderTexture.clear();
            renderTexture.draw(bg);
            renderTexture.draw(rect);
            renderTexture.draw(rect2);
            renderTexture.draw(charselect);
            renderTexture.display();
            const sf::Texture& texture = renderTexture.getTexture();
            sf::Sprite rt(texture);
            window.draw(rt);
            window.display();
        }

        if(!gamequit){
            bool training=false;
            if(menuselect==3)training=true;

            menus.setmenu(6,92,72,0,16,1);
            hitflash hf;
            healthbar hb;
            meterbar mb;
            timeui time;time.create();
            comboui cui;
            inputlist p1ilist,p2ilist;
            sf::Texture bgtexture,hutexture,p1texture,p2texture,metertexture;
            if(!p1ilist.load("inputicon.png")||!p2ilist.load("inputicon.png"))window.close();
            if(!time.load("time_ui.png")||!cui.load("combo_ui.png")||!metertexture.loadFromFile("meter_ui.png"))window.close();
            if(!bgtexture.loadFromFile("stage1.png")||!hutexture.loadFromFile("health_ui.png"))window.close();
            if(!p1texture.loadFromFile("char_sprites.png")||!p2texture.loadFromFile("char_sprites.png"))window.close();
            character p1,p2,p1shadow,p2shadow;

            p1.load(p1texture,false);p2.load(p2texture,false);
            p1shadow.load(p1texture,true);p2shadow.load(p2texture,true);
            sf::Sprite background,healthui,meterui;
            background.setTexture(bgtexture);healthui.setTexture(hutexture);meterui.setTexture(metertexture);
            sf::Text combotext;
            combotext.setFont(font);combotext.setCharacterSize(32);combotext.setFillColor(sf::Color::Black);
            std::deque<char>p1keylist,p2keylist;
            std::deque<int> animq1,animq2,hitboxanim1,hitboxanim2,p1atkfx,p2atkfx;
            std::deque<projectile> p1p,p2p;
            attackdata attack1,attack2;
            float overlap[2],overlap2[2],comboslide=0,comboslide2=0,p1x=100.0,p1y=176.0,p1jumpx=0.0,p1jumpy=0.0,p1kback=0.0,p1launch=0.0,p1hp=1000.0,p1maxhp=1000.0,p1dmg=0.0,p1paway=0.0,p1grab[2]={0,0},
                p2x=156.0,p2y=176.0,p2jumpx=0.0,p2jumpy=0.0,p2kback=0.0,p2launch=0.0,p2hp=1000.0,p2maxhp=1000.0,p2dmg=0.0,p2paway=0.0,p2grab[2]={0,0},
                bgx=0,p1meter=100.0,p2meter=100.0,p1mgain=0,p2mgain=0;
            short p1frame=0,p1act=0,p1col=0,p1anim[64][2]={},p1hitstun=0,p1blockstun=0,p1hitstop=0,p1buffer=0,p1movewaitx=0,p1movewaity=0,p1block=-1,//-1=not blocking,0=stand blocking,1=crouch blocking.2=all blocking
                p2frame=0,p2act=0,p2col=0,p2anim[64][2]={},p2hitstun=0,p2blockstun=0,p2hitstop=0,p2buffer=0,p2movewaitx=0,p2movewaity=0,p2block=-1,
                p1hbframe=0,p2hbframe=0,p1grabstate=-1,p2grabstate=-1,//-1=neutural,0=grab escape,1=normal grab,2=command grab,3=grab confirmed normal,4=grab confirmed command
                p1hitstopped=0,p2hitstopped=0,p1hitwait=0,p2hitwait=0,p1movetype=-1,p2movetype=-1,//-1=can't do anything,0=whiff cancelable,1=low,2=middle,3=overhead,4=unblockable
                p1landdelay=0,p2landdelay=0,p1knockdown=0,p2knockdown=0,p1kdowned=0,p2kdowned=0,superstop=0;
            bool p1air=false,p2air=false,seeboxes=false,F3key=false,pause=false,Enterkey=false,nextframe=false,backslash=false,p1cancel[64],p2cancel[64],
                p1whiff=true,p2whiff=true,p1neutural,p2neutural,p1right=true,p2right=false,
                p1hit=false,p2hit=false,p1slide=false,p2slide=false,hitbefore=false,hitbefore2=false,p1multihit=false,p2multihit=false,
                p1comboed=false,p2comboed=false,playertop=false,keylistshow=false;

            while (window.isOpen()&&!gamequit){
                while (window.pollEvent(event))if (event.type == sf::Event::Closed)window.close();
                sf::Vector2u size = window.getSize();
                heightRatio = screenHeight / screenWidth;widthRatio = screenWidth / screenHeight;
                if (size.y * widthRatio <= size.x)size.x = size.y * widthRatio;
                else if (size.x * heightRatio <= size.y)size.y = size.x * heightRatio;
                window.setSize(size);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){if(!F3key){F3key=true;if(flash)flash=false;else flash=true;}}else F3key=false;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){if(!Enterkey){menuselect=0;Enterkey=true;if(pause)pause=false;else pause=true;}}else Enterkey=false;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backslash)){if(backslash==false){backslash=true;nextframe=true;}}else backslash=false;

                w=false;a=false;s=false;d=false;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))w=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))a=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))s=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))d=true;
                if(w&&s){w=true;s=false;}
                if(a&&d){a=false;d=false;}

                w2=false;a2=false;s2=false;d2=false;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))w2=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))a2=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))s2=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))d2=true;
                if(w2==true&&s2==true){w2=true;s2=false;}
                if(a2==true&&d2==true){a2=false;d2=false;}

                keypresscheck(sf::Keyboard::U,&u);
                keypresscheck(sf::Keyboard::I,&i);
                keypresscheck(sf::Keyboard::O,&o);
                keypresscheck(sf::Keyboard::K,&k);

                keypresscheck(sf::Keyboard::Z,&u2);
                keypresscheck(sf::Keyboard::X,&i2);
                keypresscheck(sf::Keyboard::C,&o2);
                keypresscheck(sf::Keyboard::LAlt,&k2);

                if(w&&!a&&!s&&!d)keydir1='8';
                else if(!w&&a&&!s&&!d)keydir1='4';
                else if(!w&&!a&&s&&!d)keydir1='2';
                else if(!w&&!a&&!s&&d)keydir1='6';
                else if(w&&a&&!s&&!d)keydir1='7';
                else if(!w&&a&&s&&!d)keydir1='1';
                else if(!w&&!a&&s&&d)keydir1='3';
                else if(w&&!a&&!s&&d)keydir1='9';
                else keydir1='5';
                if(!p1right){
                    if(keydir1=='7')keydir1='9';
                    else if(keydir1=='9')keydir1='7';
                    else if(keydir1=='4')keydir1='6';
                    else if(keydir1=='6')keydir1='4';
                    else if(keydir1=='3')keydir1='1';
                    else if(keydir1=='1')keydir1='3';
                }

                if(w2&&!a2&&!s2&&!d2)keydir2='8';
                else if(!w2&&a2&&!s2&&!d2)keydir2='4';
                else if(!w2&&!a2&&s2&&!d2)keydir2='2';
                else if(!w2&&!a2&&!s2&&d2)keydir2='6';
                else if(w2&&a2&&!s2&&!d2)keydir2='7';
                else if(!w2&&a2&&s2&&!d2)keydir2='1';
                else if(!w2&&!a2&&s2&&d2)keydir2='3';
                else if(w2&&!a2&&!s2&&d2)keydir2='9';
                else keydir2='5';
                if(!p2right){
                    if(keydir2=='7')keydir2='9';
                    else if(keydir2=='9')keydir2='7';
                    else if(keydir2=='4')keydir2='6';
                    else if(keydir2=='6')keydir2='4';
                    else if(keydir2=='3')keydir2='1';
                    else if(keydir2=='1')keydir2='3';
                }

                if(!pause){
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

                    if(p1buffer==0&&!animq1.empty()){
                            p1buffer=chooseaction(1,p1air,keydir1,u,i,o,k,p1meter);
                            if(p1cancel[p1buffer]==false&&animq1.size()>10)p1buffer=0;
                            else if(p1buffer==1||p1buffer==3||p1buffer==11||p1buffer==20||(p1air&&p1jumpy<5))p1buffer=0;
                    }
                    if(p2buffer==0&&!animq2.empty()){
                            p2buffer=chooseaction(2,p2air,keydir2,u2,i2,o2,k2,p2meter);
                            if(p2cancel[p2buffer]==false&&animq2.size()>10)p2buffer=0;
                            else if(p2buffer==1||p2buffer==3||p2buffer==11||p2buffer==20||(p2air&&p2jumpy<5))p2buffer=0;
                    }
                }
                if((!pause||(pause&&nextframe))&&!training)roundframecount++;
                if((pause==false||(pause&&nextframe))){
                    nextframe=false;

                    if(p1buffer==0)p1act=chooseaction(1,p1air,keydir1,u,i,o,k,p1meter);
                    else if(!animq1.empty()&&!p1whiff)p1act=p1buffer;
                    if(animq1.empty()){if(!p1whiff){p1act=p1buffer;}p1buffer=0;}

                    if(p2buffer==0)p2act=chooseaction(2,p2air,keydir2,u2,i2,o2,k2,p2meter);
                    else if(!animq2.empty()&&!p2whiff)p2act=p2buffer;
                    if(animq2.empty()){if(!p2whiff){p2act=p2buffer;}p2buffer=0;}

                    //make an attack clashing system at some point
                    if(p1hit){
                        if(p1hitstopped==0&&superstop==0)
                        characterdata(animq1,hitboxanim1,p1atkfx,p1p,&p1hbframe,p1cancel,&p1air,p1anim,&p1act,&p1col,&p1frame,&p1whiff,&p1x,&p1y,&p1jumpx,&p1jumpy,&p1right,&p1hit,
                                      &p1block,p2x,p2y,&p1hitstun,&p1kback,&p1slide,&p1multihit,&p1hitstop,&p1buffer,&p1neutural,
                                      &p1launch,&p1hp,p2hp,&p1dmg,&p1comboed,&p1knockdown,&p1kdowned,&p1movewaitx,&p1movewaity,&p1paway,&p2paway,
                                      &p1movetype,&p1blockstun,p1grab,&p1grabstate,p2grabstate,&p1landdelay,&p1meter,&p1mgain,attack1,&superstop);
                        if(p2hitstopped==0&&superstop==0)
                        characterdata(animq2,hitboxanim2,p2atkfx,p2p,&p2hbframe,p2cancel,&p2air,p2anim,&p2act,&p2col,&p2frame,&p2whiff,&p2x,&p2y,&p2jumpx,&p2jumpy,&p2right,&p2hit,
                                      &p2block,p1x,p1y,&p2hitstun,&p2kback,&p2slide,&p2multihit,&p2hitstop,&p2buffer,&p2neutural,
                                      &p2launch,&p2hp,p1hp,&p2dmg,&p2comboed,&p2knockdown,&p2kdowned,&p2movewaitx,&p2movewaity,&p2paway,&p1paway,
                                      &p2movetype,&p2blockstun,p2grab,&p2grabstate,p1grabstate,&p2landdelay,&p2meter,&p2mgain,attack2,&superstop);
                                        }
                    else{
                        if(p2hitstopped==0&&superstop==0)
                        characterdata(animq2,hitboxanim2,p2atkfx,p2p,&p2hbframe,p2cancel,&p2air,p2anim,&p2act,&p2col,&p2frame,&p2whiff,&p2x,&p2y,&p2jumpx,&p2jumpy,&p2right,&p2hit,
                                      &p2block,p1x,p1y,&p2hitstun,&p2kback,&p2slide,&p2multihit,&p2hitstop,&p2buffer,&p2neutural,
                                      &p2launch,&p2hp,p1hp,&p2dmg,&p2comboed,&p2knockdown,&p2kdowned,&p2movewaitx,&p2movewaity,&p2paway,&p1paway,
                                      &p2movetype,&p2blockstun,p2grab,&p2grabstate,p1grabstate,&p2landdelay,&p2meter,&p2mgain,attack2,&superstop);
                        if(p1hitstopped==0&&superstop==0)
                        characterdata(animq1,hitboxanim1,p1atkfx,p1p,&p1hbframe,p1cancel,&p1air,p1anim,&p1act,&p1col,&p1frame,&p1whiff,&p1x,&p1y,&p1jumpx,&p1jumpy,&p1right,&p1hit,
                                      &p1block,p2x,p2y,&p1hitstun,&p1kback,&p1slide,&p1multihit,&p1hitstop,&p1buffer,&p1neutural,
                                      &p1launch,&p1hp,p2hp,&p1dmg,&p1comboed,&p1knockdown,&p1kdowned,&p1movewaitx,&p1movewaity,&p1paway,&p2paway,
                                      &p1movetype,&p1blockstun,p1grab,&p1grabstate,p2grabstate,&p1landdelay,&p1meter,&p1mgain,attack1,&superstop);
                                        }
                    if(!p1p.empty()){
                        if(p1p[0].x<-128||p1p[0].x>384||p1p[0].y<0||p1p[0].y>240)p1p.pop_front();
                        for(short i=0;i<p1p.size();i++){
                            if(p1p[i].hitstopped>0&&superstop==0)p1p[i].hitstopped-=1;
                            else if(superstop==0){
                                if(p1p[i].hit){p1p[i].hit=false;p1p[i].hitcount--;}
                                if(p1p[i].hitcount<=0){
                                    if(p1p[i].endanim.empty())p1p[i].y=333;
                                    else{
                                        p1p[i].frame=p1p[i].endanim[0];
                                        p1p[i].endanim.pop_front();
                                    }
                                }
                                else{
                                    if(p1p[i].right)p1p[i].x+=p1p[i].movex;
                                    else p1p[i].x-=p1p[i].movex;
                                    p1p[i].y+=p1p[i].movey;
                                    p1p[i].animloop+=1;
                                    if(p1p[i].looplen<=p1p[i].animloop)p1p[i].animloop=0;
                                    p1p[i].frame=p1p[i].loopanim[p1p[i].animloop];
                                }
                            }
                        }
                    }
                    if(!p2p.empty()){
                        if(p2p[0].x<-128||p2p[0].x>384||p2p[0].y<0||p2p[0].y>240)p2p.pop_front();
                        for(short i=0;i<p2p.size();i++){
                            if(p2p[i].hitstopped>0&&superstop==0)p2p[i].hitstopped-=1;
                            else if(superstop==0){
                                if(p2p[i].hit){p2p[i].hit=false;p2p[i].hitcount--;}
                                if(p2p[i].hitcount<=0){
                                    if(p2p[i].endanim.empty())p2p[i].y=333;
                                    else{
                                        p2p[i].frame=p2p[i].endanim[0];
                                        p2p[i].endanim.pop_front();
                                    }
                                }
                                else{
                                    if(p2p[i].right)p2p[i].x+=p2p[i].movex;
                                    else p2p[i].x-=p2p[i].movex;
                                    p2p[i].y+=p2p[i].movey;
                                    p2p[i].animloop++;
                                    if(p2p[i].looplen<=p2p[i].animloop)p2p[i].animloop=0;
                                    p2p[i].frame=p2p[i].loopanim[p2p[i].animloop];
                                }
                            }
                        }
                    }
                    if(combo==0)comboscaling=100;
                    if(training&&combo==0&&p1hp<p1maxhp)p1hp+=10;
                    if(training&&combo==0&&p2hp<p2maxhp)p2hp+=10;
                    if(p1hp>p1maxhp)p1hp=p1maxhp;
                    if(p2hp>p2maxhp)p2hp=p2maxhp;
                    if(comboscaling<20)comboscaling=20;
                    float temp[2],temp2[2],temp3[2],temp4[2];
                    if(p1right==true){
                        temp[0]=colbox[p1col][0][0][0]+int(p1x);
                        temp[1]=colbox[p1col][0][0][1]+int(p1y);
                        temp2[0]=colbox[p1col][0][1][0]+int(p1x);
                        temp2[1]=colbox[p1col][0][1][1]+int(p1y);
                    }
                    else{
                        temp[0]=-colbox[p1col][0][1][0]+int(p1x);
                        temp[1]=colbox[p1col][0][0][1]+int(p1y);
                        temp2[0]=-colbox[p1col][0][0][0]+int(p1x);
                        temp2[1]=colbox[p1col][0][1][1]+int(p1y);
                    }
                    if(p2right==true){
                        temp3[0]=colbox[p2col][0][0][0]+int(p2x);
                        temp3[1]=colbox[p2col][0][0][1]+int(p2y);
                        temp4[0]=colbox[p2col][0][1][0]+int(p2x);
                        temp4[1]=colbox[p2col][0][1][1]+int(p2y);
                    }
                    else{
                        temp3[0]=-colbox[p2col][0][1][0]+int(p2x);
                        temp3[1]=colbox[p2col][0][0][1]+int(p2y);
                        temp4[0]=-colbox[p2col][0][0][0]+int(p2x);
                        temp4[1]=colbox[p2col][0][1][1]+int(p2y);
                    }
                    while(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
                        if(p1x<p2x){
                            p1x-=1;
                            temp[0]-=1;
                            p2x+=1;
                            temp3[0]+=1;
                        }
                        else{
                            p1x+=1;
                            temp[0]+=1;
                            p2x-=1;
                            temp3[0]-=1;
                        }
                    }
                    if(p1air)p1hitwait=0;
                    else p1hitwait=animq1.size();
                    if(p2air)p2hitwait=0;
                    else p2hitwait=animq2.size();

                    if(p1hitstopped==0&&superstop==0){
                        for(int i=hurtboxcount[p1frame]-1;i>=0;i--){
                        if(p1right==true){
                            temp[0]=hurtbox[p1frame][i][0][0]+int(p1x);
                            temp[1]=hurtbox[p1frame][i][0][1]+int(p1y);
                            temp2[0]=hurtbox[p1frame][i][1][0]+int(p1x);
                            temp2[1]=hurtbox[p1frame][i][1][1]+int(p1y);
                        }
                        else{
                            temp[0]=-hurtbox[p1frame][i][1][0]+int(p1x);
                            temp[1]=hurtbox[p1frame][i][0][1]+int(p1y);
                            temp2[0]=-hurtbox[p1frame][i][0][0]+int(p1x);
                            temp2[1]=hurtbox[p1frame][i][1][1]+int(p1y);
                        }
                        for(int j=0;j<hitboxcount[p2hbframe];j++){
                            if(p2right==true){
                                temp3[0]=hitbox[p2hbframe][j][0][0]+int(p2x);
                                temp3[1]=hitbox[p2hbframe][j][0][1]+int(p2y);
                                temp4[0]=hitbox[p2hbframe][j][1][0]+int(p2x);
                                temp4[1]=hitbox[p2hbframe][j][1][1]+int(p2y);
                            }
                            else{
                                temp3[0]=-hitbox[p2hbframe][j][1][0]+int(p2x);
                                temp3[1]=hitbox[p2hbframe][j][0][1]+int(p2y);
                                temp4[0]=-hitbox[p2hbframe][j][0][0]+int(p2x);
                                temp4[1]=hitbox[p2hbframe][j][1][1]+int(p2y);
                            }
                            if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
                                p1hit=true;
                                if(temp2[0]<temp4[0])overlap[0]=temp2[0];
                                else overlap[0]=temp4[0];
                                if(temp[0]<temp3[0])overlap[0]+=temp3[0];
                                else overlap[0]+=temp[0];
                                overlap[0]/=2;
                                if(temp2[1]<temp4[1])overlap[1]=temp2[1];
                                else overlap[1]=temp4[1];
                                if(temp[1]<temp3[1])overlap[1]+=temp3[1];
                                else overlap[1]+=temp[1];
                                overlap[1]/=2;
                                break;
                                }
                            }
                        for(short j=0;j<p2p.size();j++){
                            if(p2p[j].hitstopped==0){
                            for(short k=0;k<hurtboxcount[p2p[j].frame];k++){
                                if(p2p[j].right==true){
                                    temp3[0]=hurtbox[p2p[j].frame][j][0][0]+int(p2p[j].x);
                                    temp3[1]=hurtbox[p2p[j].frame][j][0][1]+int(p2p[j].y);
                                    temp4[0]=hurtbox[p2p[j].frame][j][1][0]+int(p2p[j].x);
                                    temp4[1]=hurtbox[p2p[j].frame][j][1][1]+int(p2p[j].y);
                                }
                                else{
                                    temp3[0]=-hurtbox[p2p[j].frame][j][1][0]+int(p2p[j].x);
                                    temp3[1]=hurtbox[p2p[j].frame][j][0][1]+int(p2p[j].y);
                                    temp4[0]=-hurtbox[p2p[j].frame][j][0][0]+int(p2p[j].x);
                                    temp4[1]=hurtbox[p2p[j].frame][j][1][1]+int(p2p[j].y);
                                }
                            }
                            if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
                                p2p[j].hit=true;
                                if(temp2[0]<temp4[0])overlap[0]=temp2[0];
                                else overlap[0]=temp4[0];
                                if(temp[0]<temp3[0])overlap[0]+=temp3[0];
                                else overlap[0]+=temp[0];
                                overlap[0]/=2;
                                if(temp2[1]<temp4[1])overlap[1]=temp2[1];
                                else overlap[1]=temp4[1];
                                if(temp[1]<temp3[1])overlap[1]+=temp3[1];
                                else overlap[1]+=temp[1];
                                overlap[1]/=2;
                                break;
                                }
                            }
                            }
                        }
                        for(short i=0;i<p2p.size();i++){
                            if(p1hit)p2p[i].hit=false;
                            else if(p2p[i].hit){
                                    p1hit=true;
                                    p2movetype=p2p[i].movetype;
                                    p2hitwait=0;
                                    p2knockdown=p2p[i].knockdown;
                                    p2kback=p2p[i].kback;
                                    p2dmg=p2p[i].dmg;
                                    p2hitstun=p2p[i].hitstun;
                                    p2blockstun=p2p[i].blockstun;
                                    p2launch=p2p[i].launch;
                                    p2multihit=p2p[i].multihit;
                                    break;
                                }
                        }
                        if((p2grabstate==1|p2grabstate==2)&&p2movetype==4&&(p1air||p1comboed))p1hit=false;
                        if(p1hit==true)p2whiff=false;
                        if(p1hit==false){hitbefore=false;p2whiff=true;}
                        else if(p1hit==true&&p2multihit==false&&hitbefore==false)hitbefore=true;
                        else if(hitbefore==true)p1hit=false;
                        if(p1hit==true){
                            if(((p2movetype==1||p2movetype==2)&&p1block==1)||((p2movetype==3||p2movetype==2)&&p1block==0)||p1block==2){
                                if(p1block==1)memcpy(p1anim,animlib[33],sizeof(animlib[33]));
                                else memcpy(p1anim,animlib[32],sizeof(animlib[32]));
                                p1meter+=p2mgain/10*11;
                                p2meter+=p2mgain;
                                p2dmg/=5;
                                p1hitstopped=p2hitstop*5/4;
                                p2hitstopped=p1hitstopped;
                            }
                            else{
                                if(p1col==1)memcpy(p1anim,animlib[57],sizeof(animlib[57]));else memcpy(p1anim,animlib[56],sizeof(animlib[56]));
                                if(p2hitstop!=0||p2dmg!=0)combo++;
                                if(combo>3)comboscaling=comboscaling/10*9;
                                p1meter+=p2mgain/7*8;
                                p2meter+=p2mgain;
                                p2dmg=p2dmg/100*comboscaling;
                                p1hitstopped=p2hitstop;
                                p2hitstopped=p1hitstopped;
                            }
                            attack1.hitwait=p2hitwait;
                            attack1.movetype=p2movetype;
                            attack1.hitstun=p2hitstun;
                            attack1.blockstun=p2blockstun;
                            attack1.kback=p2kback;
                            if(p2right)attack1.kback*=-1;
                            attack1.launch=p2launch;
                            attack1.grab[0]=p2grab[0];
                            attack1.grab[1]=p2grab[1];
                            attack1.kdown=p2knockdown;
                            attack1.pushaway=true;
                            p1hp-=p2dmg;
                            }
                        for(short i=0;i<p2p.size();i++){
                            if(p2p[i].hit){
                                p2hitstopped=0;
                                p2whiff=true;
                                attack1.pushaway=false;
                                attack1.kback=p2kback;
                                if(p2p[i].right)attack1.kback*=-1;
                                //p2p[i].hitstopped=p1hitstopped;
                                break;
                            }
                        }
                    }//p1hitstopped

                    if(p2hitstopped==0&&superstop==0){
                        for(int i=hurtboxcount[p2frame]-1;i>=0;i--){
                        if(p2right==true){
                            temp[0]=hurtbox[p2frame][i][0][0]+int(p2x);
                            temp[1]=hurtbox[p2frame][i][0][1]+int(p2y);
                            temp2[0]=hurtbox[p2frame][i][1][0]+int(p2x);
                            temp2[1]=hurtbox[p2frame][i][1][1]+int(p2y);
                        }
                        else{
                            temp[0]=-hurtbox[p2frame][i][1][0]+int(p2x);
                            temp[1]=hurtbox[p2frame][i][0][1]+int(p2y);
                            temp2[0]=-hurtbox[p2frame][i][0][0]+int(p2x);
                            temp2[1]=hurtbox[p2frame][i][1][1]+int(p2y);
                        }
                        for(int j=0;j<hitboxcount[p1hbframe];j++){
                            if(p1right==true){
                                temp3[0]=hitbox[p1hbframe][j][0][0]+int(p1x);
                                temp3[1]=hitbox[p1hbframe][j][0][1]+int(p1y);
                                temp4[0]=hitbox[p1hbframe][j][1][0]+int(p1x);
                                temp4[1]=hitbox[p1hbframe][j][1][1]+int(p1y);
                            }
                            else{
                                temp3[0]=-hitbox[p1hbframe][j][1][0]+int(p1x);
                                temp3[1]=hitbox[p1hbframe][j][0][1]+int(p1y);
                                temp4[0]=-hitbox[p1hbframe][j][0][0]+int(p1x);
                                temp4[1]=hitbox[p1hbframe][j][1][1]+int(p1y);
                            }
                            if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
                                p2hit=true;
                                if(temp2[0]<temp4[0])overlap2[0]=temp2[0];
                                else overlap2[0]=temp4[0];
                                if(temp[0]<temp3[0])overlap2[0]+=temp3[0];
                                else overlap2[0]+=temp[0];
                                overlap2[0]/=2;
                                if(temp2[1]<temp4[1])overlap2[1]=temp2[1];
                                else overlap2[1]=temp4[1];
                                if(temp[1]<temp3[1])overlap2[1]+=temp3[1];
                                else overlap2[1]+=temp[1];
                                overlap2[1]/=2;
                                break;
                                }
                            }
                        for(short j=0;j<p1p.size();j++){
                            if(p1p[j].hitstopped==0){
                            for(short k=0;k<hurtboxcount[p1p[j].frame];k++){
                                if(p1p[j].right==true){
                                    temp3[0]=hurtbox[p1p[j].frame][j][0][0]+int(p1p[j].x);
                                    temp3[1]=hurtbox[p1p[j].frame][j][0][1]+int(p1p[j].y);
                                    temp4[0]=hurtbox[p1p[j].frame][j][1][0]+int(p1p[j].x);
                                    temp4[1]=hurtbox[p1p[j].frame][j][1][1]+int(p1p[j].y);
                                }
                                else{
                                    temp3[0]=-hurtbox[p1p[j].frame][j][1][0]+int(p1p[j].x);
                                    temp3[1]=hurtbox[p1p[j].frame][j][0][1]+int(p1p[j].y);
                                    temp4[0]=-hurtbox[p1p[j].frame][j][0][0]+int(p1p[j].x);
                                    temp4[1]=hurtbox[p1p[j].frame][j][1][1]+int(p1p[j].y);
                                }
                            }
                            if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
                                p1p[j].hit=true;
                                if(temp2[0]<temp4[0])overlap2[0]=temp2[0];
                                else overlap2[0]=temp4[0];
                                if(temp[0]<temp3[0])overlap2[0]+=temp3[0];
                                else overlap2[0]+=temp[0];
                                overlap2[0]/=2;
                                if(temp2[1]<temp4[1])overlap2[1]=temp2[1];
                                else overlap2[1]=temp4[1];
                                if(temp[1]<temp3[1])overlap2[1]+=temp3[1];
                                else overlap2[1]+=temp[1];
                                overlap2[1]/=2;
                                break;
                                }
                            }
                            }
                        }
                        for(short i=0;i<p1p.size();i++){
                            if(p2hit)p1p[i].hit=false;
                            else if(p1p[i].hit){
                                    p2hit=true;
                                    p1movetype=p1p[i].movetype;
                                    p1hitwait=0;
                                    p1knockdown=p1p[i].knockdown;
                                    p1kback=p1p[i].kback;
                                    p1dmg=p1p[i].dmg;
                                    p1hitstun=p1p[i].hitstun;
                                    p1blockstun=p1p[i].blockstun;
                                    p1launch=p1p[i].launch;
                                    p1multihit=p1p[i].multihit;
                                    break;
                                }
                        }
                        if((p1grabstate==1||p1grabstate==2)&&p1movetype==4&&(p2air||p2comboed))p2hit=false;
                        if(p2hit==true)p1whiff=false;
                        if(p2hit==false){hitbefore2=false;p1whiff=true;}
                        else if(p2hit==true&&p1multihit==false&&hitbefore2==false)hitbefore2=true;
                        else if(hitbefore2==true)p2hit=false;
                        if(p2hit==true){
                            if(((p1movetype==1||p1movetype==2)&&p2block==1)||((p1movetype==3||p1movetype==2)&&p2block==0)||p2block==2){
                                if(p2block==1)memcpy(p2anim,animlib[33],sizeof(animlib[33]));
                                else memcpy(p2anim,animlib[32],sizeof(animlib[32]));
                                p2meter+=p1mgain/10*11;
                                p1meter+=p1mgain;
                                p1dmg/=5;
                                p1hitstopped=p1hitstop/4*5;
                                p2hitstopped=p1hitstopped;
                            }
                            else{
                                if(p2col==1)memcpy(p2anim,animlib[57],sizeof(animlib[57]));else memcpy(p2anim,animlib[56],sizeof(animlib[56]));
                                if(p1hitstop!=0||p1dmg!=0)combo++;
                                if(combo>3)comboscaling=comboscaling/10*9;
                                p2meter+=p1mgain/7*8;
                                p1meter+=p1mgain;
                                p1dmg=p1dmg/100*comboscaling;
                                p1hitstopped=p1hitstop;
                                p2hitstopped=p1hitstopped;
                            }
                            attack2.hitwait=p1hitwait;
                            attack2.movetype=p1movetype;
                            attack2.hitstun=p1hitstun;
                            attack2.blockstun=p1blockstun;
                            attack2.kback=p1kback;
                            if(p1right)attack2.kback*=-1;
                            attack2.launch=p1launch;
                            attack2.grab[0]=p1grab[0];
                            attack2.grab[1]=p1grab[1];
                            attack2.kdown=p1knockdown;
                            attack2.pushaway=true;
                            p2hp-=p1dmg;
                        }
                    for(short i=0;i<p1p.size();i++){
                            if(p1p[i].hit){
                                p1hitstopped=0;
                                p1whiff=true;
                                attack2.pushaway=false;
                                attack2.kback=p1kback;
                                if(p1p[i].right)attack2.kback*=-1;
                                //p1p[i].hitstopped=p2hitstopped;
                                break;
                            }
                        }
                    }//p2hitstopped
                    if(p1meter>1000)p1meter=1000;
                    if(p2meter>1000)p2meter=1000;

                    while((p1x+bgx<32&&p2x+bgx<224)||(p2x+bgx<32&&p1x+bgx<224)){
                            if(bgx<125)bgx+=1;
                            else break;
                    }
                    while((p1x+bgx>224&&p2x+bgx>32)||(p2x+bgx>224&&p1x+bgx>32)){
                            if(bgx>-119)bgx-=1;
                            else break;
                    }
                    while(p1x+bgx<11)p1x++;
                    while(p1x+bgx>245)p1x--;
                    while(p2x+bgx<11)p2x++;
                    while(p2x+bgx>245)p2x--;
                }

                if(!pause){
                    char keytemp=dirkeys[1],keytemp2=keydir1;
                    if(!p1right){
                        if(keytemp=='7')keytemp='9';
                        else if(keytemp=='9')keytemp='7';
                        else if(keytemp=='4')keytemp='6';
                        else if(keytemp=='6')keytemp='4';
                        else if(keytemp=='3')keytemp='1';
                        else if(keytemp=='1')keytemp='3';
                        if(keytemp2=='7')keytemp2='9';
                        else if(keytemp2=='9')keytemp2='7';
                        else if(keytemp2=='4')keytemp2='6';
                        else if(keytemp2=='6')keytemp2='4';
                        else if(keytemp2=='3')keytemp2='1';
                        else if(keytemp2=='1')keytemp2='3';
                    }

                    if(keytemp2!=keytemp)p1keylist.push_front(keytemp2);else p1keylist.push_front('0');
                    if(u=='2')p1keylist.push_front('u');else p1keylist.push_front('0');
                    if(i=='2')p1keylist.push_front('i');else p1keylist.push_front('0');
                    if(o=='2')p1keylist.push_front('o');else p1keylist.push_front('0');
                    if(k=='2')p1keylist.push_front('k');else p1keylist.push_front('0');
                    if(p1keylist[0]=='0'&&p1keylist[1]=='0'&&p1keylist[2]=='0'&&p1keylist[3]=='0'&&p1keylist[4]=='0')for(short i=0;i<5;i++)p1keylist.pop_front();
                    if(p1keylist.size()>40)for(short i=0;i<5;i++)p1keylist.pop_back();


                    keytemp=dirkeys2[1],keytemp2=keydir2;
                    if(!p2right){
                        if(keytemp=='7')keytemp='9';
                        else if(keytemp=='9')keytemp='7';
                        else if(keytemp=='4')keytemp='6';
                        else if(keytemp=='6')keytemp='4';
                        else if(keytemp=='3')keytemp='1';
                        else if(keytemp=='1')keytemp='3';
                        if(keytemp2=='7')keytemp2='9';
                        else if(keytemp2=='9')keytemp2='7';
                        else if(keytemp2=='4')keytemp2='6';
                        else if(keytemp2=='6')keytemp2='4';
                        else if(keytemp2=='3')keytemp2='1';
                        else if(keytemp2=='1')keytemp2='3';
                    }

                    if(keytemp2!=keytemp)p2keylist.push_front(keytemp2);else p2keylist.push_front('0');
                    if(u2=='2')p2keylist.push_front('u');else p2keylist.push_front('0');
                    if(i2=='2')p2keylist.push_front('i');else p2keylist.push_front('0');
                    if(o2=='2')p2keylist.push_front('o');else p2keylist.push_front('0');
                    if(k2=='2')p2keylist.push_front('k');else p2keylist.push_front('0');
                    if(p2keylist[0]=='0'&&p2keylist[1]=='0'&&p2keylist[2]=='0'&&p2keylist[3]=='0'&&p2keylist[4]=='0')for(short i=0;i<5;i++)p2keylist.pop_front();
                    if(p2keylist.size()>40)for(short i=0;i<5;i++)p2keylist.pop_back();
                }

                if(p1hitstopped>0&&(!pause||nextframe))p1hitstopped--;
                if(p2hitstopped>0&&(!pause||nextframe))p2hitstopped--;
                if(superstop>0&&(!pause||nextframe))superstop--;

                box collisionbox1,collisionbox2,Hitbox1,Hurtbox1,Hitbox2,Hurtbox2,P_Hitbox1[8],P_Hitbox2[8];
                collisionbox1.create(p1x+bgx,int(p1y),colbox[p1col],p1right,1,sf::Color::White);
                collisionbox2.create(p2x+bgx,int(p2y),colbox[p2col],p2right,1,sf::Color::White);
                Hurtbox1.create(p1x+bgx,int(p1y),hurtbox[p1frame],p1right,hurtboxcount[p1frame],sf::Color::Blue);
                Hitbox1.create(p1x+bgx,int(p1y),hitbox[p1hbframe],p1right,hitboxcount[p1hbframe],sf::Color::Red);
                Hurtbox2.create(p2x+bgx,int(p2y),hurtbox[p2frame],p2right,hurtboxcount[p2frame],sf::Color::Blue);
                Hitbox2.create(p2x+bgx,int(p2y),hitbox[p2hbframe],p2right,hitboxcount[p2hbframe],sf::Color::Red);
                for(short i=0;i<p1p.size();i++)P_Hitbox1[i].create(p1p[i].x+bgx,int(p1p[i].y),hurtbox[p1p[i].frame],p1p[i].right,hurtboxcount[p1p[i].frame],sf::Color::Red);
                for(short i=0;i<p2p.size();i++)P_Hitbox2[i].create(p2p[i].x+bgx,int(p2p[i].y),hurtbox[p2p[i].frame],p2p[i].right,hurtboxcount[p2p[i].frame],sf::Color::Red);

                if(p1hitstopped==0&&p2hitstopped==0)hf.frame=0;
                if(p1hit&&!p2hit&&(!pause||nextframe)&&hf.frame==0){
                    hf.create(overlap[0]+bgx,overlap[1],combo>0);
                    hf.frame=1;
                }
                else if(p2hit&&!p1hit&&(!pause||nextframe)&&hf.frame==0){
                    hf.create(overlap2[0]+bgx,overlap2[1],combo>0);
                    hf.frame=1;
                }
                else if(hf.frame>0&&p1hit&&!p2hit&&(!pause||nextframe)){
                    hf.update(overlap[0]+bgx,overlap[1],combo>0);
                    hf.frame++;
                }
                else if(hf.frame>0&&!p1hit&&p2hit&&(!pause||nextframe)){
                    hf.update(overlap2[0]+bgx,overlap2[1],combo>0);
                    hf.frame++;
                }
                if(combo>1&&comboslide==0&&comboslide2==0){comboslide=64;comboslide2=12;}
                if(comboslide>0)comboslide-=comboslide2--;
                if(comboslide<0){comboslide=0;}
                if(comboslide==0&&combo==0)comboslide2=0;
                std::string tempstr;
                tempstr = std::to_string(combo);
                combotext.setString(tempstr);
                combotext.setOrigin(combotext.getLocalBounds().width,0);
                if (combo>1)cui.create(p2comboed||p2kdowned,comboslide);

                p1ilist.create(p1keylist,true);
                p2ilist.create(p2keylist,false);
                hb.create(p1hp,p2hp);
                mb.create(p1meter,p2meter);

                healthui.setPosition(0.f,0.f);
                if(p2comboed||p2kdowned)combotext.setPosition(36.f-comboslide,25.f);
                else combotext.setPosition(248.f+comboslide,25.f);
                p1.setPosition(int(p1x-64+bgx),int(p1y-64));
                p1shadow.setPosition(p1x-64+bgx,184+(p1y-176)/8);
                p2.setPosition(int(p2x-64+bgx),int(p2y-64));
                p2shadow.setPosition(p2x-64+bgx,184+(p2y-176)/8);
                background.setPosition(bgx-125,0.f);

                menus.setcolor(6,!pause,menuselect);
                if(pause){
                    keypresscheck(sf::Keyboard::U,&menuconfirm);
                    keypresscheck(sf::Keyboard::I,&menucancel);
                    keypresscheck(sf::Keyboard::W,&menuup);
                    keypresscheck(sf::Keyboard::S,&menudown);
                    if(menuup=='2'){menuselect--;if(menuselect<0)menuselect=5;}
                    else if(menudown=='2'){menuselect++;if(menuselect>5)menuselect=0;}
                    if((menuconfirm=='2'&&menuselect==0)||menucancel=='2')pause=false;
                    else if(menuconfirm=='2'&&menuselect==1)if(seeboxes)seeboxes=false;else seeboxes=true;
                    else if(menuconfirm=='2'&&menuselect==2)if(keylistshow)keylistshow=false;else keylistshow=true;
                    else if(menuconfirm=='2'&&menuselect==5)gamequit=true;
                }

                sf::RectangleShape blackscreen(sf::Vector2f(256.f, 240.f));
                blackscreen.setFillColor(sf::Color(0,0,0,170));

                p1.setanim(p1anim,p1right);
                p2.setanim(p2anim,p2right);
                p1shadow.setanim(p1anim,p1right);
                p2shadow.setanim(p2anim,p2right);

                window.clear();
                renderTexture.clear();
                renderTexture.draw(background);
                renderTexture.draw(p1shadow);
                renderTexture.draw(p2shadow);

                if(superstop>0)renderTexture.draw(blackscreen);

                if(p1hit)playertop=true;
                else if(p2hit) playertop=false;
                if(playertop){
                    renderTexture.draw(p1);
                    renderTexture.draw(p2);
                }
                else{
                    renderTexture.draw(p2);
                    renderTexture.draw(p1);
                }

                if(!p1p.empty()){
                character p_graphics[p1p.size()];
                    for(short i=0;i<p1p.size();i++){
                        p_graphics[i].load(p1texture,false);
                        p_graphics[i].setanim(animlib[p1p[i].frame],p1p[i].right);
                        p_graphics[i].setPosition(int(p1p[i].x-64+bgx),int(p1p[i].y-64));
                        renderTexture.draw(p_graphics[i]);
                    }
                }
                if(!p2p.empty()){
                character p_graphics[p2p.size()];
                    for(short i=0;i<p2p.size();i++){
                        p_graphics[i].load(p2texture,false);
                        p_graphics[i].setanim(animlib[p2p[i].frame],p2p[i].right);
                        p_graphics[i].setPosition(int(p2p[i].x-64+bgx),int(p2p[i].y-64));
                        renderTexture.draw(p_graphics[i]);
                    }
                }

                if(p1hitstopped>0||p2hitstopped)renderTexture.draw(hf);


                renderTexture.draw(hb);
                renderTexture.draw(healthui);

                meterui.setPosition(0,208);
                meterui.setScale(1.0f,1.0f);
                renderTexture.draw(meterui);
                meterui.setPosition(256,208);
                meterui.setScale(-1.0f,1.0f);
                renderTexture.draw(meterui);
                renderTexture.draw(mb);

                if(roundframecount/60<99)time.timeset(99-roundframecount/60);
                else time.timeset(0);
                time.setPosition(0,0);
                renderTexture.draw(time);

                time.timeset(p1meter/100);
                time.setPosition(-107,208);
                renderTexture.draw(time);

                time.timeset(p2meter/100);
                time.setPosition(109,208);
                renderTexture.draw(time);

                if(keylistshow){renderTexture.draw(p1ilist);renderTexture.draw(p2ilist);}

                if(combo>1){renderTexture.draw(cui);renderTexture.draw(combotext);}
                if(pause){renderTexture.draw(blackscreen);renderTexture.draw(menus);}
                renderTexture.display();
                const sf::Texture& texture = renderTexture.getTexture();
                sf::Sprite rt(texture);

                window.draw(rt);

                if(seeboxes){
                    window.draw(collisionbox1);
                    window.draw(collisionbox2);
                    window.draw(Hurtbox1);
                    window.draw(Hurtbox2);
                    window.draw(Hitbox1);
                    window.draw(Hitbox2);
                    for(short i=0;i<p1p.size();i++)window.draw(P_Hitbox1[i]);
                    for(short i=0;i<p2p.size();i++)window.draw(P_Hitbox2[i]);
                }
                window.display();
            }
        }
        menuselect=0;combo=0;roundframecount=0;comboscaling=100.0;gamequit=false;
        dirkeys.clear();ukey.clear();ikey.clear();okey.clear();kkey.clear();
        dirkeys2.clear();ukey2.clear();ikey2.clear();okey2.clear();kkey2.clear();
        menus.setmenu(6,144,120,0,16,0);
        }

    }
	return 0;
}
