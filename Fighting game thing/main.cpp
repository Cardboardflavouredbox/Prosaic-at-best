#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <random>
#include <deque>
#include <string.h>
#include <math.h>
#include "ggponet.h"

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
                   hurtboxcount[256]={2,3,3,2,2,2,3,3,2,2,3,3,2,3,3,2,2,2,2,0,2,2,2,2,3,3,2,3,3,3,3,3,2,2,0,2,3,3,2,2,2,3,3,2,2,2,2,2,2,2,3,3,3,2,1,1,2,2,1,1,1},
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



class player
{
public:
    std::deque<int> animq,hitboxanim,atkfx;
    std::deque<projectile> proj;
    attackdata attack;
    short hbframe=0,anim[64][2]={},act=0,col=0,frame=0,block=-1,//-1=not blocking,0=stand blocking,1=crouch blocking.2=all blocking
    hitstun=0,blockstun=0,hitstop=0,hitwait=0,
    buffer=0,kdown=0,kdowned=0,movewaitx=0,movewaity=0,movetype=0,//-1=can't do anything,0=whiff cancelable,1=low,2=middle,3=overhead,4=unblockable
    landdelay=0,hitstopped=0,grabstate=-1;//-1=neutural,0=grab escape,1=normal grab,2=command grab,3=grab confirmed normal,4=grab confirmed command
    bool cancel[64]={},air=false,whiff=true,right,hit=false,slide=false,multihit=false,neutural=true,comboed=false,hitbefore=false,super=false;
    float x=0,y=176.0,jumpx=0,jumpy=0,kback=0,launch=0,hp=1000.0,maxhp=1000.0,dmg=0,pushaway=0,grab[2]={},meter=100,mgain=0;
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

class superflash : public sf::Drawable, public sf::Transformable
{
public:
    void create(short frame,float py){
        frame=frame/2-4;
        if(frame<1)frame=1;
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(16);
        sf::Vertex* triangles = &m_vertices[6];
        triangles[0].position = sf::Vector2f(0,py-frame+1);
        triangles[1].position = sf::Vector2f(256,py-frame+1);
        triangles[2].position = sf::Vector2f(0,py+frame);
        triangles[3].position = sf::Vector2f(0,py+frame);
        triangles[4].position = sf::Vector2f(256,py+frame);
        triangles[5].position = sf::Vector2f(256,py-frame+1);
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = NULL;

        target.draw(m_vertices, states);
    }
   sf::VertexArray m_vertices;

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
    void create(bool right){
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
float slide=0,slide2=0;

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
void keyread(char keydir,bool right){

}

void collisionchecks(player *p1,player *p2,float overlap[]){
    float temp[2],temp2[2],temp3[2],temp4[2];
    for(int i=hurtboxcount[(*p1).frame]-1;i>=0;i--){
    if((*p1).right==true){
        temp[0]=hurtbox[(*p1).frame][i][0][0]+int((*p1).x);
        temp[1]=hurtbox[(*p1).frame][i][0][1]+int((*p1).y);
        temp2[0]=hurtbox[(*p1).frame][i][1][0]+int((*p1).x);
        temp2[1]=hurtbox[(*p1).frame][i][1][1]+int((*p1).y);
    }
    else{
        temp[0]=-hurtbox[(*p1).frame][i][1][0]+int((*p1).x);
        temp[1]=hurtbox[(*p1).frame][i][0][1]+int((*p1).y);
        temp2[0]=-hurtbox[(*p1).frame][i][0][0]+int((*p1).x);
        temp2[1]=hurtbox[(*p1).frame][i][1][1]+int((*p1).y);
    }
    for(int j=0;j<hitboxcount[(*p2).hbframe];j++){
        if((*p2).right==true){
            temp3[0]=hitbox[(*p2).hbframe][j][0][0]+int((*p2).x);
            temp3[1]=hitbox[(*p2).hbframe][j][0][1]+int((*p2).y);
            temp4[0]=hitbox[(*p2).hbframe][j][1][0]+int((*p2).x);
            temp4[1]=hitbox[(*p2).hbframe][j][1][1]+int((*p2).y);
        }
        else{
            temp3[0]=-hitbox[(*p2).hbframe][j][1][0]+int((*p2).x);
            temp3[1]=hitbox[(*p2).hbframe][j][0][1]+int((*p2).y);
            temp4[0]=-hitbox[(*p2).hbframe][j][0][0]+int((*p2).x);
            temp4[1]=hitbox[(*p2).hbframe][j][1][1]+int((*p2).y);
        }
        if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
            (*p1).hit=true;
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
    for(short j=0;j<(*p2).proj.size();j++){
        if((*p2).proj[j].hitstopped==0){
        for(short k=0;k<hurtboxcount[(*p2).proj[j].frame];k++){
            if((*p2).proj[j].right==true){
                temp3[0]=hurtbox[(*p2).proj[j].frame][k][0][0]+int((*p2).proj[j].x);
                temp3[1]=hurtbox[(*p2).proj[j].frame][k][0][1]+int((*p2).proj[j].y);
                temp4[0]=hurtbox[(*p2).proj[j].frame][k][1][0]+int((*p2).proj[j].x);
                temp4[1]=hurtbox[(*p2).proj[j].frame][k][1][1]+int((*p2).proj[j].y);
            }
            else{
                temp3[0]=-hurtbox[(*p2).proj[j].frame][k][1][0]+int((*p2).proj[j].x);
                temp3[1]=hurtbox[(*p2).proj[j].frame][k][0][1]+int((*p2).proj[j].y);
                temp4[0]=-hurtbox[(*p2).proj[j].frame][k][0][0]+int((*p2).proj[j].x);
                temp4[1]=hurtbox[(*p2).proj[j].frame][k][1][1]+int((*p2).proj[j].y);
            }
        }
        if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
            (*p2).proj[j].hit=true;
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
    for(short i=0;i<(*p2).proj.size();i++){
        if((*p1).hit)(*p2).proj[i].hit=false;
        else if((*p2).proj[i].hit){
                (*p1).hit=true;
                (*p2).grabstate=-1;
                (*p2).grab[0]=0;
                (*p2).grab[1]=0;
                (*p2).movetype=(*p2).proj[i].movetype;
                (*p2).hitwait=0;
                (*p2).kdown=(*p2).proj[i].knockdown;
                (*p2).kback=(*p2).proj[i].kback;
                (*p2).dmg=(*p2).proj[i].dmg;
                (*p2).hitstun=(*p2).proj[i].hitstun;
                (*p2).blockstun=(*p2).proj[i].blockstun;
                (*p2).launch=(*p2).proj[i].launch;
                (*p2).multihit=(*p2).proj[i].multihit;
                (*p2).mgain=(*p2).proj[i].mgain;
                break;
            }
    }
    if(((*p2).grabstate==1|(*p2).grabstate==2)&&(*p2).movetype==4&&((*p1).air||(*p1).comboed))(*p1).hit=false;
    if((*p1).hit==true)(*p2).whiff=false;
    if((*p1).hit==false){(*p1).hitbefore=false;(*p2).whiff=true;}
    else if((*p1).hit==true&&(*p2).multihit==false&&(*p1).hitbefore==false)(*p1).hitbefore=true;
    else if((*p1).hitbefore==true)(*p1).hit=false;
    if((*p1).hit==true){
        if((((*p2).movetype==1||(*p2).movetype==2)&&(*p1).block==1)||(((*p2).movetype==3||(*p2).movetype==2)&&(*p1).block==0)||(*p1).block==2){
            if((*p1).block==1)memcpy((*p1).anim,animlib[33],sizeof(animlib[33]));
            else memcpy((*p1).anim,animlib[32],sizeof(animlib[32]));
            (*p1).meter+=(*p2).mgain/10*11;
            (*p2).meter+=(*p2).mgain;
            (*p2).dmg/=5;
            (*p1).hitstopped=(*p2).hitstop*5/4;
            (*p2).hitstopped=(*p1).hitstopped;
        }
        else{
            if((*p1).col==1)memcpy((*p1).anim,animlib[57],sizeof(animlib[57]));else memcpy((*p1).anim,animlib[56],sizeof(animlib[56]));
            if((*p2).hitstop!=0||(*p2).dmg!=0)combo++;
            if(combo>3)comboscaling=comboscaling/10*9;
            (*p1).meter+=(*p2).mgain/7*8;
            (*p2).meter+=(*p2).mgain;
            (*p2).dmg=(*p2).dmg/100*comboscaling;
            (*p1).hitstopped=(*p2).hitstop;
            (*p2).hitstopped=(*p1).hitstopped;
        }
        (*p1).attack.hitwait=(*p2).hitwait;
        (*p1).attack.movetype=(*p2).movetype;
        (*p1).attack.hitstun=(*p2).hitstun;
        (*p1).attack.blockstun=(*p2).blockstun;
        (*p1).attack.kback=(*p2).kback;
        if((*p2).right)(*p1).attack.kback*=-1;
        (*p1).attack.launch=(*p2).launch;
        (*p1).attack.grab[0]=(*p2).grab[0];
        (*p1).attack.grab[1]=(*p2).grab[1];
        (*p1).attack.kdown=(*p2).kdown;
        (*p1).attack.pushaway=true;
        (*p1).hp-=(*p2).dmg;
        }
    for(short i=0;i<(*p2).proj.size();i++){
        if((*p2).proj[i].hit){
            (*p2).hitstopped=0;
            (*p2).whiff=true;
            (*p1).attack.pushaway=false;
            (*p1).attack.kback=(*p2).kback;
            if((*p2).proj[i].right)(*p1).attack.kback*=-1;
            (*p2).proj[i].hitstopped=(*p1).hitstopped;
            break;
        }
    }

}

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

int chooseaction(int playercode, bool air, char keyinput[], float meter){
    char c236[4][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}},
        c214[4][5]={{'0','0','0','0','0'},{'4','0','0','0','0'},{'1','0','0','0','0'},{'2','0','0','0','0'}},
        c623[4][5]={{'0','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'6','0','0','0','0'}},
        c323[4][5]={{'0','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'3','0','0','0','0'}},
        c626[4][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'2','0','0','0','0'},{'6','0','0','0','0'}},
        c636[4][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'6','0','0','0','0'}},
        c63236[6][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'3','0','0','0','0'},{'6','0','0','0','0'}},
        c6236[5][5]={{'0','0','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'},{'6','0','0','0','0'}};
            if(!air){
                if(keyinput[0]=='1'||keyinput[0]=='2'||keyinput[0]=='3'){
                    //crouching actions
                    if(keyinput[3]=='2'){
                        c623[0][3]='2';c323[0][3]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 23;//special B strong
                        else return 14;//strong normal
                        c623[0][3]='0';c323[0][3]='0';
                    }
                    else if(keyinput[2]=='2'){
                        c623[0][2]='2';c323[0][2]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 22;//special B middle
                        else return 13;//middle normal
                        c623[0][2]='0';c323[0][2]='0';
                    }
                    else if(keyinput[1]=='2'){
                        c623[0][1]='2';c323[0][1]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 21;//special B weak
                        else return 12;//weak normal
                        c623[0][1]='0';c323[0][1]='0';
                    }
                    else if(keyinput[4]=='2'){
                        c623[0][4]='2';c323[0][4]='2';
                        if(cmdcheck(playercode,4,c623)||cmdcheck(playercode,4,c323))return 24;//special B gimmick
                        else return 15;//gimmick
                        c623[0][4]='0';c323[0][4]='0';
                    }
                    else if(keyinput[0]=='1')return 20;//crouching block
                    else return 11;//crouch
                }
                else{
                    //grounded actions
                    if(keyinput[1]=='2'&&keyinput[2]=='2'){
                        c214[0][1]='2';c214[0][2]='2';
                        if(cmdcheck(playercode,4,c214)&&meter>=100)return 32;//super
                        else return 25;//grab
                        c214[0][1]='0';c214[0][2]='0';
                    }
                    if(keyinput[3]=='2'){
                        c214[0][3]='2';c236[0][3]='2';c636[0][3]='2';c626[0][3]='2';c63236[0][3]='2';c6236[0][3]='2';
                        if(cmdcheck(playercode,4,c214))return 30;//special C strong
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 23;//special B strong
                        else if(cmdcheck(playercode,4,c236))return 18;//special A strong
                        else if(keyinput[1]=='2'||keyinput[2]=='2')return 25;//grab
                        else return 10;//strong normal
                        c214[0][3]='0';c236[0][3]='0';c636[0][3]='0';c626[0][3]='0';c63236[0][3]='0';c6236[0][3]='0';
                    }
                    else if(keyinput[2]=='2'){
                        c214[0][2]='2';c236[0][2]='2';c636[0][2]='2';c626[0][2]='2';c63236[0][2]='2';c6236[0][2]='2';
                        if(cmdcheck(playercode,4,c214))return 29;//special C middle
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 22;//special B middle
                        else if(cmdcheck(playercode,4,c236))return 17;//special A middle
                        else return 9;//middle normal
                        c214[0][2]='0';c236[0][2]='0';c636[0][2]='0';c626[0][2]='0';c63236[0][2]='0';c6236[0][2]='0';
                    }
                    else if(keyinput[1]=='2'){
                        c214[0][1]='2';c236[0][1]='2';c636[0][1]='2';c626[0][1]='2';c63236[0][1]='2';c6236[0][1]='2';
                        if(cmdcheck(playercode,4,c214))return 28;//special C weak
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 21;//special B weak
                        else if(cmdcheck(playercode,4,c236))return 16;//special A weak
                        else return 8;//weak normal
                        c214[0][1]='0';c236[0][1]='0';c636[0][1]='0';c626[0][1]='0';c63236[0][1]='0';c6236[0][1]='0';
                    }
                    else if(keyinput[4]=='2'){
                        c214[0][4]='2';c236[0][4]='2';c636[0][4]='2';c626[0][4]='2';c63236[0][4]='2';c6236[0][4]='2';
                        if(cmdcheck(playercode,4,c214))return 31;//special C gimmick
                        else if(cmdcheck(playercode,4,c636)||cmdcheck(playercode,6,c63236)||cmdcheck(playercode,4,c626)||cmdcheck(playercode,5,c6236))return 24;//special B gimmick
                        else if(cmdcheck(playercode,4,c236))return 19;//special A gimmick
                        else return 15;//gimmick
                        c214[0][4]='0';c236[0][4]='0';c636[0][4]='0';c626[0][4]='0';c63236[0][4]='0';c6236[0][4]='0';
                    }
                    else if(keyinput[0]=='4'){
                        char temp[3][5]={{'4','0','0','0','0'},{'5','0','0','0','0'},{'4','0','0','0','0'}};
                        if(cmdcheck(playercode,3,temp))return 2;//leftdash
                        else return 1;//leftwalk
                    }
                    else if(keyinput[0]=='6'){
                        char temp[3][5]={{'6','0','0','0','0'},{'5','0','0','0','0'},{'6','0','0','0','0'}};
                        if(cmdcheck(playercode,3,temp))return 4;//rightdash
                        else return 3;//rightwalk
                    }
                    else if(keyinput[0]=='8')return 5;//upjump
                    else if(keyinput[0]=='7')return 6;//leftjump
                    else if(keyinput[0]=='9')return 7;//rightjump
                    else return 0;//neutural

                }
            }
            else{
                //jump actions
                if(keyinput[1]=='2')return 8;//weak normal
                else if(keyinput[2]=='2')return 9;//middle normal
                else if(keyinput[3]=='2')return 10;//strong normal
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

void projectiledata(player *p1,short superstop){
if((*p1).proj[0].x<-128||(*p1).proj[0].x>384||(*p1).proj[0].y<0||(*p1).proj[0].y>240)(*p1).proj.pop_front();
    for(short i=0;i<(*p1).proj.size();i++){
        if(superstop==0){
            if((*p1).proj[i].hit){(*p1).proj[i].hit=false;(*p1).proj[i].hitcount--;}
            if((*p1).proj[i].hitcount<=0){
                if((*p1).proj[i].endanim.empty())(*p1).proj[i].y=333;
                else{
                    (*p1).proj[i].frame=(*p1).proj[i].endanim[0];
                    (*p1).proj[i].endanim.pop_front();
                }
            }
            else if((*p1).proj[i].hitstopped>0&&superstop==0)(*p1).proj[i].hitstopped-=1;
            else{
                if((*p1).proj[i].right)(*p1).proj[i].x+=(*p1).proj[i].movex;
                else (*p1).proj[i].x-=(*p1).proj[i].movex;
                (*p1).proj[i].y+=(*p1).proj[i].movey;
                (*p1).proj[i].animloop+=1;
                if((*p1).proj[i].looplen<=(*p1).proj[i].animloop)(*p1).proj[i].animloop=0;
                (*p1).proj[i].frame=(*p1).proj[i].loopanim[(*p1).proj[i].animloop];
            }
        }
    }
}

void characterdata(player *P,float enemyx,float enemyy,float enemyhp,float *enemypaway,short enemygstate,short *superstop){
    if((*P).kdowned==1&&(*P).animq.size()<28&&!(*P).comboed&&(*P).act==1&&(*P).hp>0){
        (*P).slide=true;
        if((*P).right)(*P).jumpx=-5;else (*P).jumpx=5;
        (*P).animq.clear();
        for(short i=0;i<7;i++){(*P).animq.push_back(8);}
        (*P).kdowned=0;combo=0;
    }
    if((*P).hit){
        (*P).hit=false;(*P).animq.clear();(*P).hitboxanim.clear();(*P).atkfx.clear();
        (*P).movetype=-1;(*P).grab[0]=0;(*P).grab[1]=0;(*P).grabstate=-1;(*P).landdelay=0;(*P).movewaitx=-1;(*P).movewaity=-1;
        (*P).mgain=0;(*P).super=false;
        if((*P).air&&(*P).attack.launch==0){
                (*P).jumpy=(*P).attack.kback/6*5*(comboscaling+100)/200;
                if((*P).jumpy>0)(*P).jumpy*=-1;
        }
        else (*P).jumpy=0;
        if((*P).hp<=0)(*P).block=-1;
        if((((*P).attack.movetype==1||(*P).attack.movetype==2)&&(*P).block==1)||(((*P).attack.movetype==3||(*P).attack.movetype==2)&&(*P).block==0)||(*P).block==2){
            (*P).slide=true;
            if((*P).block==2){
                if((*P).attack.movetype==1)(*P).block=1;
                else (*P).block=0;
            }
            if((*P).block==0)for(short i=0;i<(*P).attack.hitwait+(*P).attack.blockstun;i++)(*P).animq.push_back(32);
            if((*P).block==1)for(short i=0;i<(*P).attack.hitwait+(*P).attack.blockstun;i++)(*P).animq.push_back(33);
            (*P).block=2;
        }
        else{
            if((*P).attack.launch>0){(*P).jumpy=-(*P).attack.launch*(comboscaling+100)/200;(*P).air=true;}
            if((*P).air||((*P).attack.grab[0]!=0||(*P).attack.grab[1]!=0))(*P).slide=false;
            else (*P).slide=true;
            (*P).comboed=true;
            if((*P).attack.grab[0]!=0||(*P).attack.grab[1]!=0)(*P).col=3;
            if((*P).col==1)for(short i=0;i<(*P).attack.hitwait+(*P).attack.hitstun;i++)(*P).animq.push_back(53);
            else for(short i=0;i<(*P).attack.hitwait+(*P).attack.hitstun;i++)(*P).animq.push_back(9);
            if((*P).attack.kdown==2||(*P).hp<=0)(*P).kdowned=2;
            else if((*P).attack.kdown==1||(*P).attack.launch>0||(*P).air)(*P).kdowned=1;
            else (*P).kdowned=0;
        }
        if((((*P).x<-110&&(*P).attack.kback>0)||((*P).x>360&&(*P).attack.kback<0))&&((*P).attack.grab[0]==0&&(*P).attack.grab[1]==0)&&(*P).attack.pushaway){
                if((*P).attack.kback>0)(*P).pushaway+=(*P).attack.kback;
                else (*P).pushaway-=(*P).attack.kback;
                (*P).pushaway+=int((*P).attack.launch/2);
        }
        else if((*P).attack.grab[0]==0&&(*P).attack.grab[1]==0){
                if((*P).air&&(*P).attack.launch==0){
                    (*P).jumpx=-int((*P).attack.kback/3);
                }
                else{
                    (*P).jumpx=-(*P).attack.kback;
                }
        }
        short temp[1]={-1};boolfill((*P).cancel,true,temp);
    }
    else if((*P).animq.empty()&&(*P).movewaitx==-1&&(*P).movewaity==-1&&!(*P).air){
        if((*P).comboed&&(*P).kdowned>0){
            (*P).col=2;(*P).comboed=false;
            for(short i=0;i<32;i++){(*P).animq.push_back(19);}
        }
        else if((*P).kdowned>0&&(*P).hp>0){
            for(short i=0;i<3;i++){(*P).animq.push_back(8);}
            (*P).kdowned=0;combo=0;
        }
        else {
            short temp[1]={-1};boolfill((*P).cancel,true,temp);
            if(!(*P).neutural){(*P).jumpx=0;(*P).jumpy=0;}
            (*P).neutural=true;(*P).hitstun=0;(*P).blockstun=0;(*P).kback=0;(*P).hit=false;
            (*P).slide=false;(*P).multihit=false;(*P).dmg=0;(*P).launch=0;(*P).kdown=0;(*P).mgain=0;(*P).super=false;
            (*P).movetype=-1;(*P).block=-1;(*P).grab[0]=0;(*P).grab[1]=0;(*P).grabstate=-1;
            if((*P).comboed){combo=0;(*P).comboed=false;}
        }
    }

    if(enemygstate==3&&(*P).act==25){
            (*P).grabstate=0;
            (*P).slide=true;
            if((*P).x<enemyx)(*P).jumpx=-8;
            else (*P).jumpx=4;
            (*P).pushaway=8;
            (*P).animq.clear();(*P).hitboxanim.clear();(*P).atkfx.clear();
            for(short i=0;i<(*P).attack.hitwait;i++)(*P).animq.push_back(32);
        }

    if(enemyhp<=0||roundframecount/60>=99)(*P).act=0;
    if((*P).grabstate==1&&!(*P).whiff)(*P).grabstate=3;
    if((*P).grabstate==2&&!(*P).whiff)(*P).grabstate=3;
    if((*P).grabstate==3){
            if(enemygstate==0)(*P).grabstate=-1;
            else if((*P).animq.size()<12){
                if((*P).act==1)(*P).act=27;
                else (*P).act=26;
            }
    }
    if(!(*P).hit&&(((*P).animq.empty()&&(*P).movewaitx==-1&&(*P).movewaity==-1)||(((*P).cancel[(*P).act]==true)&&((!(*P).whiff)||(*P).movetype==0||(*P).grabstate==3)))){
        if((*P).cancel[(*P).act]==true){
            (*P).buffer=0;(*P).slide=false;(*P).hitstun=0;(*P).blockstun=0;(*P).kback=0;(*P).dmg=0;(*P).launch=0;(*P).kdown=0;(*P).movewaitx=-1;(*P).movewaity=-1;
            (*P).movetype=-1;(*P).grab[0]=0;(*P).grab[1]=0;(*P).landdelay=0;if(!(*P).air){(*P).jumpx=0;(*P).jumpy=0;}(*P).mgain=0;(*P).super=false;
            short temp[0]={};boolfill((*P).cancel,true,temp);
            (*P).animq.clear();(*P).hitboxanim.clear();(*P).atkfx.clear();
        }

        if((*P).act==1)(*P).block=0;
        else if((*P).act==20)(*P).block=1;
        else (*P).block=-1;

        if((*P).act==0){//neutural
            if(!(*P).air){
                if((*P).x<enemyx)(*P).right=true;
                else (*P).right=false;
                memcpy((*P).anim,animlib[0],sizeof(animlib[0]));
            }
            (*P).col=0;(*P).frame=0;(*P).block=-1;
        }
        else if((*P).act==1){//left walk
            (*P).col=0;
            memcpy((*P).anim,animlib[15],sizeof(animlib[0]));
            if((*P).right)(*P).x-=3;else (*P).x+=3;
            if((*P).x<enemyx)(*P).right=true;else (*P).right=false;
        }
        else if((*P).act==2){(*P).col=0;(*P).air=true;(*P).jumpy=-2.0;if((*P).right)(*P).jumpx=-7;else (*P).jumpx=7;(*P).landdelay=7;}//left dash
        else if((*P).act==3){//right walk
            (*P).col=0;
            memcpy((*P).anim,animlib[17],sizeof(animlib[0]));
            if((*P).right)(*P).x+=3;else (*P).x-=3;
            if((*P).x<enemyx)(*P).right=true;else (*P).right=false;
        }
        else if((*P).act==4){(*P).col=0;(*P).air=true;(*P).jumpy=-2.0;if((*P).right)(*P).jumpx=7;else (*P).jumpx=-7;(*P).landdelay=7;}//right dash
        else if((*P).act==5){(*P).col=0;(*P).jumpy=-12.0;(*P).movewaity=4;(*P).animq.insert((*P).animq.begin(),{8,8,8,43});(*P).landdelay=5;}//up jump
        else if((*P).act==6){(*P).col=0;(*P).jumpy=-12.0;(*P).movewaitx=4;(*P).movewaity=4;if((*P).right)(*P).jumpx=-3;else (*P).jumpx=3;(*P).animq.insert((*P).animq.begin(),{8,8,8,43});(*P).landdelay=3;}//left jump
        else if((*P).act==7){(*P).col=0;(*P).jumpy=-12.0;(*P).movewaitx=4;(*P).movewaity=4;if((*P).right)(*P).jumpx=3;else (*P).jumpx=-3;(*P).animq.insert((*P).animq.begin(),{8,8,8,43});(*P).landdelay=3;}//(*P).right jump
        else if((*P).act==8){//u (light normal)
            if((*P).air){
                (*P).col=0;(*P).multihit=false;(*P).hitstop=12;(*P).kback=2;(*P).hitstun=8;(*P).blockstun=1;(*P).dmg=12;(*P).movetype=3;(*P).landdelay=3;(*P).mgain=4;
                (*P).animq.insert((*P).animq.begin(),{43,43,45,45,46,46,46});
                (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,10,10,10,10,10,10,10,10});
            }
            else{
                (*P).col=0;(*P).multihit=false;(*P).hitstop=12;(*P).kback=4;(*P).hitstun=4;(*P).blockstun=1;(*P).dmg=12;(*P).movetype=2;(*P).mgain=4;
                (*P).animq.insert((*P).animq.begin(),{1,1,1,2,2,2,1,1,1});
                (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,1});
                short temp[15]={9,10,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill((*P).cancel,true,temp);
            }
        }
        else if((*P).act==9){//i (middle normal)
            if((*P).air){
                (*P).col=0;(*P).multihit=false;(*P).hitstop=13;(*P).kback=3;(*P).hitstun=10;(*P).blockstun=3;(*P).dmg=25;(*P).movetype=3;(*P).landdelay=3;(*P).mgain=6;
                (*P).animq.insert((*P).animq.begin(),{3,4,5,5,5,6,7,7,7,7});
                (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,2,2,2,2});
            }
            else{
                (*P).col=0;(*P).multihit=false;(*P).hitstop=13;(*P).kback=5;(*P).hitstun=1;(*P).blockstun=-6;(*P).slide=true;(*P).dmg=27;(*P).movetype=2;(*P).mgain=6;
                (*P).animq.insert((*P).animq.begin(),{3,4,5,5,5,5,5,6,7,7,7,7,7,6,5,5,4,4,3,3});
                (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,2,2});
                short temp[14]={10,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill((*P).cancel,true,temp);
                (*P).movewaitx=7;
                if((*P).right)(*P).jumpx=3;
                else (*P).jumpx=-3;
            }
        }
        else if((*P).act==10){//o (heavy normal)
            if((*P).air){
                (*P).col=0;(*P).multihit=false;(*P).hitstop=14;(*P).kback=3;(*P).hitstun=12;(*P).blockstun=6;(*P).dmg=33;(*P).movetype=3;(*P).landdelay=3;(*P).mgain=8;
                (*P).animq.insert((*P).animq.begin(),{3,4,5,5,5,5,5,6,7,7,7,7,7});
                (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,2,2,2,2,2,2});
            }
            else{
                (*P).col=0;(*P).multihit=false;(*P).hitstop=14;(*P).kback=6;(*P).hitstun=-1;(*P).blockstun=-8;(*P).slide=true;(*P).dmg=35;(*P).movetype=2;(*P).mgain=8;
                (*P).animq.insert((*P).animq.begin(),{26,26,27,27,28,28,28,28,28,29,30,31,31,31,31,31,31,31,30,29,28,28,28,27,27,27,26,26,26});
                (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,0,6,6,6});
                short temp[13]={16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill((*P).cancel,true,temp);
                (*P).movewaitx=9;
                if((*P).right)(*P).jumpx=5;
                else (*P).jumpx=-5;
            }
        }
        else if((*P).act==11||(*P).act==20){//crouch & crouch block
            if((*P).x<enemyx)(*P).right=true;
            else (*P).right=false;
            (*P).col=1;(*P).frame=8;
            memcpy((*P).anim,animlib[8],sizeof(animlib[8]));
        }
        else if((*P).act==12){//crouch u
            (*P).col=1;(*P).multihit=false;(*P).hitstop=12;(*P).kback=5;(*P).hitstun=4;(*P).blockstun=0;(*P).dmg=11;(*P).movetype=1;(*P).mgain=4;
            (*P).animq.insert((*P).animq.begin(),{10,10,10,11,11,11,10,10,10});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,3});
            short temp[15]={13,14,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill((*P).cancel,true,temp);
        }
        else if((*P).act==13){//crouch i
            (*P).col=1;(*P).multihit=false;(*P).hitstop=13;(*P).kback=5;(*P).hitstun=1;(*P).blockstun=-4;(*P).slide=true;(*P).dmg=24;(*P).movetype=1;(*P).mgain=6;
            (*P).animq.insert((*P).animq.begin(),{38,38,39,39,39,39,40,41,42,42,42,41,41,40,40,39,39,39,38,38,38,38});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,9,9,9});
            short temp[14]={14,16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill((*P).cancel,true,temp);
            (*P).movewaitx=7;
            if((*P).right)(*P).jumpx=2;
            else (*P).jumpx=-2;
        }
        else if((*P).act==14){//crouch o
            (*P).col=1;(*P).multihit=false;(*P).hitstop=14;(*P).kback=3;(*P).hitstun=1;(*P).blockstun=-5;(*P).slide=true;(*P).movewaitx=7;(*P).dmg=35;(*P).launch=10;(*P).kdown=1;(*P).movetype=2;(*P).mgain=8;
            (*P).animq.insert((*P).animq.begin(),{12,12,12,12,12,12,13,14,14,14,14,14,14,13,12,12,12,12,12});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,4,4,4,4,4});
            if((*P).right)(*P).jumpx=4;else (*P).jumpx=-4;
            short temp[13]={16,17,18,19,21,22,23,24,28,29,30,31,32};boolfill((*P).cancel,true,temp);
        }
        else if((*P).act==15){}//k (gimmick)
        else if((*P).act==16){//special A (u)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=12;(*P).kback=7;(*P).hitstun=1;(*P).blockstun=-3;(*P).slide=true;(*P).movewaitx=6;(*P).dmg=22;(*P).movetype=2;(*P).mgain=7;
            (*P).animq.insert((*P).animq.begin(),{20,21,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,22,21,20,20});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,5,5});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=5;else (*P).jumpx=-5;
        }
        else if((*P).act==17){//special A (i)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=13;(*P).kback=7;(*P).hitstun=-1;(*P).blockstun=-4;(*P).slide=true;(*P).movewaitx=9;(*P).dmg=29;(*P).kdown=2;(*P).movetype=2;(*P).mgain=8;
            (*P).animq.insert((*P).animq.begin(),{20,20,21,21,22,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,23,22,22,21,21,20,20});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,0,5,5});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=6;else (*P).jumpx=-6;
        }
        else if((*P).act==18){//special A (o)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=14;(*P).kback=0;(*P).hitstun=0;(*P).blockstun=-5;(*P).slide=true;(*P).movewaitx=10;(*P).dmg=36;(*P).kdown=1;(*P).launch=11;(*P).movetype=2;(*P).mgain=9;
            (*P).animq.insert((*P).animq.begin(),{20,20,20,21,21,22,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,23,22,22,22,21,21,20,20,20});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,5,5});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=7;else (*P).jumpx=-7;
        }
        else if((*P).act==19){//special A (k)
            (*P).col=0;(*P).multihit=false;(*P).slide=true;(*P).movewaitx=6;(*P).movetype=0;
            (*P).animq.insert((*P).animq.begin(),{20,21,22,22,22,22,21,20});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=4;else (*P).jumpx=-4;
        }
        else if((*P).act==21){//special B(u)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=13;(*P).kback=5;(*P).hitstun=5;(*P).blockstun=-5;(*P).slide=true;(*P).movewaity=4;(*P).movewaitx=4;(*P).dmg=28;(*P).mgain=7;
            (*P).kdown=1;(*P).launch=8;(*P).movetype=2;(*P).jumpy=-11;(*P).landdelay=5;
            (*P).animq.insert((*P).animq.begin(),{34,34,34,35,35,35,36,37,37,37,37,37,37,37,37,37});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,7,0,0,0,8,8,8,8,8,8,8,8,8});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=6;else (*P).jumpx=-6;
        }
        else if((*P).act==22){//special B(i)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=14;(*P).kback=5;(*P).hitstun=5;(*P).blockstun=-5;(*P).slide=true;(*P).movewaity=4;(*P).movewaitx=2;(*P).dmg=39;(*P).mgain=8;
            (*P).kdown=1;(*P).launch=9;(*P).movetype=2;(*P).jumpy=-12;(*P).landdelay=5;
            (*P).animq.insert((*P).animq.begin(),{34,34,34,35,35,35,36,37,37,37,37,37,37,37,37,37,37});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,7,0,0,0,8,8,8,8,8,8,8,8,8,8});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=7;else (*P).jumpx=-7;
        }
        else if((*P).act==23){//special B(o)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=15;(*P).kback=5;(*P).hitstun=5;(*P).blockstun=-5;(*P).slide=true;(*P).movewaity=5;(*P).dmg=51;(*P).mgain=9;
            (*P).kdown=1;(*P).launch=10;(*P).movetype=2;(*P).jumpy=-13;(*P).landdelay=5;
            (*P).animq.insert((*P).animq.begin(),{34,34,34,34,34,35,35,35,36,37,37,37,37,37,37,37,37,37,37,37});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,7,0,0,0,0,8,8,8,8,8,8,8,8,8,8,8,8});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=8;else (*P).jumpx=-8;
        }
        else if((*P).act==24){//special B(k)
            (*P).col=0;(*P).multihit=false;(*P).slide=true;(*P).movewaity=4;(*P).jumpy=-1;
            (*P).animq.insert((*P).animq.begin(),{34,34,34,34});
            (*P).cancel[32]=true;
            if((*P).right)(*P).jumpx=6;else (*P).jumpx=-6;
        }
        else if((*P).act==25){//grab
            (*P).col=0;(*P).multihit=false;(*P).hitstop=0;(*P).kback=0;(*P).hitstun=0;(*P).blockstun=0;(*P).slide=true;(*P).movewaitx=6;(*P).dmg=0;(*P).movetype=4;(*P).grab[0]=21;(*P).grab[1]=0;(*P).grabstate=1;
            (*P).animq.insert((*P).animq.begin(),{20,20,21,21,22,22,22,22,23,24,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,24,24,23,23,22,22,21,21,20,20});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,0,0,0,0,0,0,5});
            if((*P).right)(*P).jumpx=5;else (*P).jumpx=-5;
            short temp[2]={26,27};boolfill((*P).cancel,true,temp);
        }
        else if((*P).act==26){//grab attack forward
            (*P).col=1;(*P).multihit=false;(*P).hitstop=15;(*P).kback=3;(*P).hitstun=1;(*P).blockstun=0;(*P).slide=true;(*P).movewaitx=3;(*P).dmg=100;(*P).launch=10;(*P).kdown=2;(*P).movetype=4;(*P).grabstate=-1;(*P).mgain=12;
            (*P).animq.insert((*P).animq.begin(),{12,12,12,13,14,14,14,14,14,14,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,4});
            if((*P).right)(*P).jumpx=4;else (*P).jumpx=-4;
        }
        else if((*P).act==27){//grab attack backward
            (*P).col=1;(*P).multihit=false;(*P).hitstop=15;(*P).kback=-3;(*P).hitstun=1;(*P).blockstun=0;(*P).slide=true;(*P).movewaitx=3;(*P).dmg=100;(*P).launch=10;(*P).kdown=2;(*P).movetype=4;(*P).grabstate=-1;(*P).mgain=12;
            (*P).animq.insert((*P).animq.begin(),{12,12,12,13,14,14,14,14,14,14,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12});
            (*P).hitboxanim.insert((*P).hitboxanim.begin(),{0,0,0,0,4});
            if((*P).right)(*P).jumpx=4;else (*P).jumpx=-4;
        }
        else if((*P).act==28){//special C (u)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=12;(*P).kback=3;(*P).hitstun=3;(*P).blockstun=1;(*P).dmg=22;(*P).movetype=2;(*P).mgain=7;
            (*P).animq.insert((*P).animq.begin(),{47,47,47,48,49,49,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            (*P).atkfx.insert((*P).atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1});
            (*P).cancel[32]=true;
        }
        else if((*P).act==29){//special C (i)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=12;(*P).kback=3;(*P).hitstun=4;(*P).blockstun=2;(*P).dmg=22;(*P).movetype=2;(*P).mgain=8;
            (*P).animq.insert((*P).animq.begin(),{47,47,47,48,49,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            (*P).atkfx.insert((*P).atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,0,2});
            (*P).cancel[32]=true;
        }
        else if((*P).act==30){//special C (o)
            (*P).col=0;(*P).multihit=false;(*P).hitstop=12;(*P).kback=3;(*P).hitstun=5;(*P).blockstun=3;(*P).dmg=22;(*P).movetype=2;(*P).mgain=9;
            (*P).animq.insert((*P).animq.begin(),{47,47,47,48,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            (*P).atkfx.insert((*P).atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,3});
            (*P).cancel[32]=true;
        }
        else if((*P).act==31){//special C (k)
            (*P).col=0;(*P).multihit=false;
            (*P).animq.insert((*P).animq.begin(),{47,47,47,48,49,49,49,50,50,51,51,51,51,51,52,52});
            (*P).cancel[32]=true;
        }
        else if((*P).act==32){//super
            (*P).col=0;(*P).multihit=false;(*P).hitstop=14;(*P).kback=8;(*P).launch=5;(*P).hitstun=6;(*P).blockstun=5;(*P).slide=true;(*P).movewaitx=15;(*P).dmg=150;(*P).movetype=2;(*P).mgain=0;(*P).meter-=100;
            (*P).animq.insert((*P).animq.begin(),{47,47,47,48,49,49,49,49,49,49,49,49,49,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52});
            (*P).atkfx.insert((*P).atkfx.begin(),{0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,4});
            if((*P).right)(*P).jumpx=-9;else (*P).jumpx=9;
        }
    }
    if((*P).movewaitx>0)(*P).movewaitx-=1;
    else{(*P).x+=(*P).jumpx;(*P).movewaitx=-1;}
    if((*P).movewaity>0)(*P).movewaity-=1;
    else{if((*P).jumpy<0)(*P).air=true;(*P).y+=(*P).jumpy;(*P).movewaity=-1;}
    if((*P).slide&&(*P).movewaitx==-1){
        if((*P).jumpx>0)(*P).jumpx-=1;
        else if((*P).jumpx<0)(*P).jumpx+=1;
    }
    if(*enemypaway>0){
            if((*P).air)*enemypaway=0;
            else{if((*P).x<enemyx)(*P).x-=*enemypaway;else if((*P).x>enemyx)(*P).x+=*enemypaway;*enemypaway-=1;}
    }
    if((*P).air){
            (*P).block=-1;
            if((*P).comboed)(*P).jumpy+=0.75;
            else (*P).jumpy+=0.8;
            if((*P).jumpy>0){
                if((*P).neutural){memcpy((*P).anim,animlib[44],sizeof(animlib[44]));(*P).frame=44;}
            }
            if((*P).y>175){
                if((*P).kdowned>0){}//add downed landing animation
                if(!(*P).comboed){(*P).col=1;(*P).animq.clear();(*P).hitboxanim.clear();(*P).atkfx.clear();for(short i=0;i<(*P).landdelay;i++)(*P).animq.push_back(8);}
                (*P).landdelay=0;
                (*P).movetype=0;
                (*P).jumpx=0;(*P).jumpy=0;(*P).y=176;(*P).air=false;
            }
        }
    if(!(*P).hitboxanim.empty()){
        (*P).hbframe=(*P).hitboxanim[0];
        (*P).hitboxanim.pop_front();
    }
    else (*P).hbframe=0;
    if(!(*P).animq.empty()){
        (*P).neutural=false;(*P).frame=(*P).animq[0];
        memcpy((*P).anim,animlib[(*P).animq[0]],sizeof(animlib[(*P).animq[0]]));
        if(!((*P).animq[0]==19&&(*P).hp<=0)&&!((*P).air&&(*P).animq.size()==1))(*P).animq.pop_front();
    }
    if(enemygstate==3||enemygstate==4){
        if((*P).x<enemyx)(*P).x=enemyx-(*P).attack.grab[0];
        else (*P).x=enemyx+(*P).attack.grab[0];
        (*P).y=enemyy-(*P).attack.grab[1];
    }
    if(!(*P).atkfx.empty()){
        if((*P).atkfx[0]==5){*superstop=20;(*P).super=true;}
        if((*P).atkfx[0]==1||(*P).atkfx[0]==2||(*P).atkfx[0]==3||(*P).atkfx[0]==4){//projectile
            (*P).meter+=(*P).mgain;
            projectile temp;
            temp.movetype=(*P).movetype;
            temp.x=(*P).x;temp.y=(*P).y;
            if((*P).atkfx[0]==1)temp.movex=4;
            else if((*P).atkfx[0]==2)temp.movex=5;
            else if((*P).atkfx[0]==3)temp.movex=6;
            else if((*P).atkfx[0]==4)temp.movex=12;
            temp.movey=0;
            temp.hitcount=1;
            temp.hitstop=(*P).hitstop;
            temp.hitstun=(*P).hitstun;temp.blockstun=(*P).blockstun;
            temp.dmg=(*P).dmg;
            temp.mgain=(*P).mgain;
            temp.kback=(*P).kback;
            temp.right=(*P).right;
            temp.multihit=(*P).multihit;
            temp.looplen=2;
            temp.knockdown=(*P).kdown;
            temp.loopanim[0]=54;
            temp.loopanim[1]=55;
            temp.launch=(*P).launch;
            temp.endanim.insert(temp.endanim.begin(),{58,59,60});
            if((*P).proj.size()<8)(*P).proj.push_back(temp);
                }
        (*P).atkfx.pop_front();
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(256,240), "Prosaic at Best");
    sf::Event event;
    sf::Keyboard::Key upkey1=sf::Keyboard::W,downkey1=sf::Keyboard::S,leftkey1=sf::Keyboard::A,rightkey1=sf::Keyboard::D,
                lightkey1=sf::Keyboard::U,mediumkey1=sf::Keyboard::I,heavykey1=sf::Keyboard::O,
                grabkey1=sf::Keyboard::H,specialkey1=sf::Keyboard::K,assistkey1=sf::Keyboard::L;
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
    char p1input[5]={'5','0'},p2input[5]={'5','0'},menuup='0',menudown='0',menuleft='0',menuright='0',menuconfirm='0',menucancel='0';
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

        keypresscheck(lightkey1,&menuconfirm);
        keypresscheck(upkey1,&menuup);
        keypresscheck(downkey1,&menudown);

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
            keypresscheck(lightkey1,&menuconfirm);
            keypresscheck(mediumkey1,&menucancel);
            keypresscheck(upkey1,&menuup);
            keypresscheck(downkey1,&menudown);
            keypresscheck(leftkey1,&menuleft);
            keypresscheck(downkey1,&menuright);
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

            menus.setmenu(6,92,72,0,16,1);
            hitflash hf;superflash sf;
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
            character p1graphics,p2graphics,p1shadow,p2shadow;

            p1graphics.load(p1texture,false);p2graphics.load(p2texture,false);
            p1shadow.load(p1texture,true);p2shadow.load(p2texture,true);
            sf::Sprite background,healthui,meterui;
            background.setTexture(bgtexture);healthui.setTexture(hutexture);meterui.setTexture(metertexture);
            sf::Text combotext;
            combotext.setFont(font);combotext.setCharacterSize(32);combotext.setFillColor(sf::Color::Black);
            std::deque<char>p1keylist,p2keylist;

            player p1,p2;

            float overlap[2],overlap2[2],bgx=0;
                p1.x=100.0;p1.y=176.0;p1.hp=1000.0;p1.maxhp=1000.0;
                p2.x=156.0;p2.y=176.0;p2.hp=1000.0;p2.maxhp=1000.0;

                p1.meter=100.0;
                p2.meter=100.0;
            short superstop=0;
            bool seeboxes=false,F3key=false,pause=false,Enterkey=false,nextframe=false,backslash=false,playertop=false,keylistshow=false;
                p1.right=true;
                p2.right=false;

            if(menuselect==3)training=true;
            /*if(menuselect==2){
                GGPOSession* ggpo;
                GGPOErrorCode result;
                GGPOSessionCallbacks cb;
                cb.begin_game = ;
                cb.advance_frame = ;
                cb.load_game_state = ;
                cb.save_game_state = ;
                cb.free_buffer = ;
                cb.on_event = ;
            }*/

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
                if(sf::Keyboard::isKeyPressed(upkey1))w=true;
                if(sf::Keyboard::isKeyPressed(leftkey1))a=true;
                if(sf::Keyboard::isKeyPressed(downkey1))s=true;
                if(sf::Keyboard::isKeyPressed(rightkey1))d=true;
                if(w&&s){w=true;s=false;}
                if(a&&d){a=false;d=false;}

                w2=false;a2=false;s2=false;d2=false;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))w2=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))a2=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))s2=true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))d2=true;
                if(w2==true&&s2==true){w2=true;s2=false;}
                if(a2==true&&d2==true){a2=false;d2=false;}

                keypresscheck(lightkey1,&p1input[1]);
                keypresscheck(mediumkey1,&p1input[2]);
                keypresscheck(heavykey1,&p1input[3]);
                keypresscheck(specialkey1,&p1input[4]);

                keypresscheck(sf::Keyboard::Z,&p2input[1]);
                keypresscheck(sf::Keyboard::X,&p2input[2]);
                keypresscheck(sf::Keyboard::C,&p2input[3]);
                keypresscheck(sf::Keyboard::LAlt,&p2input[4]);

                if(w&&!a&&!s&&!d)p1input[0]='8';
                else if(!w&&a&&!s&&!d)p1input[0]='4';
                else if(!w&&!a&&s&&!d)p1input[0]='2';
                else if(!w&&!a&&!s&&d)p1input[0]='6';
                else if(w&&a&&!s&&!d)p1input[0]='7';
                else if(!w&&a&&s&&!d)p1input[0]='1';
                else if(!w&&!a&&s&&d)p1input[0]='3';
                else if(w&&!a&&!s&&d)p1input[0]='9';
                else p1input[0]='5';
                if(!p1.right){
                    if(p1input[0]=='7')p1input[0]='9';
                    else if(p1input[0]=='9')p1input[0]='7';
                    else if(p1input[0]=='4')p1input[0]='6';
                    else if(p1input[0]=='6')p1input[0]='4';
                    else if(p1input[0]=='3')p1input[0]='1';
                    else if(p1input[0]=='1')p1input[0]='3';
                }

                if(w2&&!a2&&!s2&&!d2)p2input[0]='8';
                else if(!w2&&a2&&!s2&&!d2)p2input[0]='4';
                else if(!w2&&!a2&&s2&&!d2)p2input[0]='2';
                else if(!w2&&!a2&&!s2&&d2)p2input[0]='6';
                else if(w2&&a2&&!s2&&!d2)p2input[0]='7';
                else if(!w2&&a2&&s2&&!d2)p2input[0]='1';
                else if(!w2&&!a2&&s2&&d2)p2input[0]='3';
                else if(w2&&!a2&&!s2&&d2)p2input[0]='9';
                else p2input[0]='5';
                if(!p2.right){
                    if(p2input[0]=='7')p2input[0]='9';
                    else if(p2input[0]=='9')p2input[0]='7';
                    else if(p2input[0]=='4')p2input[0]='6';
                    else if(p2input[0]=='6')p2input[0]='4';
                    else if(p2input[0]=='3')p2input[0]='1';
                    else if(p2input[0]=='1')p2input[0]='3';
                }

                if(!pause){
                    dirkeys.push_front(p1input[0]);
                    ukey.push_front(p1input[1]);
                    ikey.push_front(p1input[2]);
                    okey.push_front(p1input[3]);
                    kkey.push_front(p1input[4]);
                    if(dirkeys.size()>20)dirkeys.pop_back();
                    if(ukey.size()>20)ukey.pop_back();
                    if(ikey.size()>20)ikey.pop_back();
                    if(okey.size()>20)okey.pop_back();
                    if(kkey.size()>20)kkey.pop_back();

                    dirkeys2.push_front(p2input[0]);
                    ukey2.push_front(p2input[1]);
                    ikey2.push_front(p2input[2]);
                    okey2.push_front(p2input[3]);
                    kkey2.push_front(p2input[4]);
                    if(dirkeys2.size()>20)dirkeys2.pop_back();
                    if(ukey2.size()>20)ukey2.pop_back();
                    if(ikey2.size()>20)ikey2.pop_back();
                    if(okey2.size()>20)okey2.pop_back();
                    if(kkey2.size()>20)kkey2.pop_back();

                    if(p1.buffer==0&&!p1.animq.empty()){
                            p1.buffer=chooseaction(1,p1.air,p1input,p1.meter);
                            if(p1.cancel[p1.buffer]==false&&p1.animq.size()>10)p1.buffer=0;
                            else if(p1.buffer==1||p1.buffer==3||p1.buffer==11||p1.buffer==20||(p1.air&&p1.jumpy<5))p1.buffer=0;
                    }
                    if(p2.buffer==0&&!p2.animq.empty()){
                            p2.buffer=chooseaction(2,p2.air,p2input,p2.meter);
                            if(p2.cancel[p2.buffer]==false&&p2.animq.size()>10)p2.buffer=0;
                            else if(p2.buffer==1||p2.buffer==3||p2.buffer==11||p2.buffer==20||(p2.air&&p2.jumpy<5))p2.buffer=0;
                    }
                }
                if((!pause||(pause&&nextframe))&&!training)roundframecount++;
                if((pause==false||(pause&&nextframe))){
                    nextframe=false;

                    if(p1.buffer==0)p1.act=chooseaction(1,p1.air,p1input,p1.meter);
                    else if(!p1.animq.empty()&&!p1.whiff)p1.act=p1.buffer;
                    if(p1.animq.empty()){if(!p1.whiff){p1.act=p1.buffer;}p1.buffer=0;}

                    if(p2.buffer==0)p2.act=chooseaction(2,p2.air,p2input,p2.meter);
                    else if(!p2.animq.empty()&&!p2.whiff)p2.act=p2.buffer;
                    if(p2.animq.empty()){if(!p2.whiff){p2.act=p2.buffer;}p2.buffer=0;}

                    //make an attack clashing system at some point
                    if(p1.hit){
                        if(p1.hitstopped==0&&superstop==0)characterdata(&p1,p2.x,p2.y,p2.hp,&p2.pushaway,p2.grabstate,&superstop);
                        if(p2.hitstopped==0&&superstop==0)characterdata(&p2,p1.x,p1.y,p1.hp,&p1.pushaway,p1.grabstate,&superstop);
                                        }
                    else{
                        if(p2.hitstopped==0&&superstop==0)characterdata(&p2,p1.x,p1.y,p1.hp,&p1.pushaway,p1.grabstate,&superstop);
                        if(p1.hitstopped==0&&superstop==0)characterdata(&p1,p2.x,p2.y,p2.hp,&p2.pushaway,p2.grabstate,&superstop);
                                        }
                    if(!p1.proj.empty())projectiledata(&p1,superstop);
                    if(!p2.proj.empty())projectiledata(&p2,superstop);
                    if(combo==0)comboscaling=100;
                    if(training&&combo==0&&p1.hp<p1.maxhp)p1.hp+=10;
                    if(training&&combo==0&&p2.hp<p2.maxhp)p2.hp+=10;
                    if(p1.hp>p1.maxhp)p1.hp=p1.maxhp;
                    if(p2.hp>p2.maxhp)p2.hp=p2.maxhp;
                    if(comboscaling<20)comboscaling=20;
                    float temp[2]={},temp2[2]={},temp3[2]={},temp4[2]={};
                    if(p1.right==true){
                        temp[0]=colbox[p1.col][0][0][0]+int(p1.x);
                        temp[1]=colbox[p1.col][0][0][1]+int(p1.y);
                        temp2[0]=colbox[p1.col][0][1][0]+int(p1.x);
                        temp2[1]=colbox[p1.col][0][1][1]+int(p1.y);
                    }
                    else{
                        temp[0]=-colbox[p1.col][0][1][0]+int(p1.x);
                        temp[1]=colbox[p1.col][0][0][1]+int(p1.y);
                        temp2[0]=-colbox[p1.col][0][0][0]+int(p1.x);
                        temp2[1]=colbox[p1.col][0][1][1]+int(p1.y);
                    }
                    if(p2.right==true){
                        temp3[0]=colbox[p2.col][0][0][0]+int(p2.x);
                        temp3[1]=colbox[p2.col][0][0][1]+int(p2.y);
                        temp4[0]=colbox[p2.col][0][1][0]+int(p2.x);
                        temp4[1]=colbox[p2.col][0][1][1]+int(p2.y);
                    }
                    else{
                        temp3[0]=-colbox[p2.col][0][1][0]+int(p2.x);
                        temp3[1]=colbox[p2.col][0][0][1]+int(p2.y);
                        temp4[0]=-colbox[p2.col][0][0][0]+int(p2.x);
                        temp4[1]=colbox[p2.col][0][1][1]+int(p2.y);
                    }
                    while(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){
                        if(p1.x<p2.x){
                            p1.x-=1;
                            temp[0]-=1;
                            p2.x+=1;
                            temp3[0]+=1;
                        }
                        else{
                            p1.x+=1;
                            temp[0]+=1;
                            p2.x-=1;
                            temp3[0]-=1;
                        }
                    }
                    if(p1.air)p1.hitwait=0;
                    else p1.hitwait=p1.animq.size();
                    if(p2.air)p2.hitwait=0;
                    else p2.hitwait=p2.animq.size();

                    if(p1.hitstopped==0&&superstop==0)collisionchecks(&p1,&p2,overlap);
                    if(p2.hitstopped==0&&superstop==0)collisionchecks(&p2,&p1,overlap2);


                    for(short j=0;j<p1.proj.size();j++){
                            if(p1.proj[j].hitstopped==0){
                            for(short i=0;i<hurtboxcount[p1.proj[j].frame];i++){
                            if(p1.proj[j].right==true){
                                temp[0]=hurtbox[p1.proj[j].frame][i][0][0]+int(p1.proj[j].x);
                                temp[1]=hurtbox[p1.proj[j].frame][i][0][1]+int(p1.proj[j].y);
                                temp2[0]=hurtbox[p1.proj[j].frame][i][1][0]+int(p1.proj[j].x);
                                temp2[1]=hurtbox[p1.proj[j].frame][i][1][1]+int(p1.proj[j].y);
                            }
                            else{
                                temp[0]=-hurtbox[p1.proj[j].frame][i][1][0]+int(p1.proj[j].x);
                                temp[1]=hurtbox[p1.proj[j].frame][i][0][1]+int(p1.proj[j].y);
                                temp2[0]=-hurtbox[p1.proj[j].frame][i][0][0]+int(p1.proj[j].x);
                                temp2[1]=hurtbox[p1.proj[j].frame][i][1][1]+int(p1.proj[j].y);
                            }

                            for(short l=0;l<p2.proj.size();l++){
                                if(p2.proj[l].hitstopped==0){
                                for(short k=0;k<hurtboxcount[p2.proj[l].frame];k++){
                                    if(p2.proj[l].right==true){
                                        temp3[0]=hurtbox[p2.proj[l].frame][k][0][0]+int(p2.proj[l].x);
                                        temp3[1]=hurtbox[p2.proj[l].frame][k][0][1]+int(p2.proj[l].y);
                                        temp4[0]=hurtbox[p2.proj[l].frame][k][1][0]+int(p2.proj[l].x);
                                        temp4[1]=hurtbox[p2.proj[l].frame][k][1][1]+int(p2.proj[l].y);
                                    }
                                    else{
                                        temp3[0]=-hurtbox[p2.proj[l].frame][k][1][0]+int(p2.proj[l].x);
                                        temp3[1]=hurtbox[p2.proj[l].frame][k][0][1]+int(p2.proj[l].y);
                                        temp4[0]=-hurtbox[p2.proj[l].frame][k][0][0]+int(p2.proj[l].x);
                                        temp4[1]=hurtbox[p2.proj[l].frame][k][1][1]+int(p2.proj[l].y);
                                    }
                                }
                                if(!(temp[0]>=temp4[0]||temp2[0]<=temp3[0]||temp[1]>=temp4[1]||temp2[1]<=temp3[1])){p1.proj[j].hitcount--;p2.proj[j].hitcount--;break;}
                                    }
                                }
                            }
                            }
                    }



                    if(p1.meter>1000)p1.meter=1000;
                    if(p2.meter>1000)p2.meter=1000;

                    while((p1.x+bgx<32&&p2.x+bgx<224)||(p2.x+bgx<32&&p1.x+bgx<224)){
                            if(bgx<125)bgx+=1;
                            else break;
                    }
                    while((p1.x+bgx>224&&p2.x+bgx>32)||(p2.x+bgx>224&&p1.x+bgx>32)){
                            if(bgx>-119)bgx-=1;
                            else break;
                    }
                    while(p1.x+bgx<11)p1.x++;
                    while(p1.x+bgx>245)p1.x--;
                    while(p2.x+bgx<11)p2.x++;
                    while(p2.x+bgx>245)p2.x--;
                }

                if(!pause){
                    char keytemp=dirkeys[1],keytemp2=p1input[0];
                    if(!p1.right){
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
                    if(p1input[1]=='2')p1keylist.push_front('u');else p1keylist.push_front('0');
                    if(p1input[2]=='2')p1keylist.push_front('i');else p1keylist.push_front('0');
                    if(p1input[3]=='2')p1keylist.push_front('o');else p1keylist.push_front('0');
                    if(p1input[4]=='2')p1keylist.push_front('k');else p1keylist.push_front('0');
                    if(p1keylist[0]=='0'&&p1keylist[1]=='0'&&p1keylist[2]=='0'&&p1keylist[3]=='0'&&p1keylist[4]=='0')for(short i=0;i<5;i++)p1keylist.pop_front();
                    if(p1keylist.size()>40)for(short i=0;i<5;i++)p1keylist.pop_back();


                    keytemp=dirkeys2[1],keytemp2=p2input[0];
                    if(!p2.right){
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
                    if(p2input[1]=='2')p2keylist.push_front('u');else p2keylist.push_front('0');
                    if(p2input[2]=='2')p2keylist.push_front('i');else p2keylist.push_front('0');
                    if(p2input[3]=='2')p2keylist.push_front('o');else p2keylist.push_front('0');
                    if(p2input[4]=='2')p2keylist.push_front('k');else p2keylist.push_front('0');
                    if(p2keylist[0]=='0'&&p2keylist[1]=='0'&&p2keylist[2]=='0'&&p2keylist[3]=='0'&&p2keylist[4]=='0')for(short i=0;i<5;i++)p2keylist.pop_front();
                    if(p2keylist.size()>40)for(short i=0;i<5;i++)p2keylist.pop_back();
                }

                if(p1.hitstopped>0&&(!pause||nextframe))p1.hitstopped--;
                if(p2.hitstopped>0&&(!pause||nextframe))p2.hitstopped--;
                if(superstop>0&&(!pause||nextframe))superstop--;

                box collisionbox1,collisionbox2,Hitbox1,Hurtbox1,Hitbox2,Hurtbox2,P_Hitbox1[8],P_Hitbox2[8];
                collisionbox1.create(p1.x+bgx,int(p1.y),colbox[p1.col],p1.right,1,sf::Color::White);
                collisionbox2.create(p2.x+bgx,int(p2.y),colbox[p2.col],p2.right,1,sf::Color::White);
                Hurtbox1.create(p1.x+bgx,int(p1.y),hurtbox[p1.frame],p1.right,hurtboxcount[p1.frame],sf::Color::Blue);
                Hitbox1.create(p1.x+bgx,int(p1.y),hitbox[p1.hbframe],p1.right,hitboxcount[p1.hbframe],sf::Color::Red);
                Hurtbox2.create(p2.x+bgx,int(p2.y),hurtbox[p2.frame],p2.right,hurtboxcount[p2.frame],sf::Color::Blue);
                Hitbox2.create(p2.x+bgx,int(p2.y),hitbox[p2.hbframe],p2.right,hitboxcount[p2.hbframe],sf::Color::Red);
                for(short i=0;i<p1.proj.size();i++)P_Hitbox1[i].create(p1.proj[i].x+bgx,int(p1.proj[i].y),hurtbox[p1.proj[i].frame],p1.proj[i].right,hurtboxcount[p1.proj[i].frame],sf::Color::Red);
                for(short i=0;i<p2.proj.size();i++)P_Hitbox2[i].create(p2.proj[i].x+bgx,int(p2.proj[i].y),hurtbox[p2.proj[i].frame],p2.proj[i].right,hurtboxcount[p2.proj[i].frame],sf::Color::Red);

                if(p1.hitstopped==0&&p2.hitstopped==0)hf.frame=0;
                if(p1.hit&&!p2.hit&&(!pause||nextframe)&&hf.frame==0){
                    hf.create(overlap[0]+bgx,overlap[1],combo>0);
                    hf.frame=1;
                }
                else if(p2.hit&&!p1.hit&&(!pause||nextframe)&&hf.frame==0){
                    hf.create(overlap2[0]+bgx,overlap2[1],combo>0);
                    hf.frame=1;
                }
                else if(hf.frame>0&&p1.hit&&!p2.hit&&(!pause||nextframe)){
                    hf.update(overlap[0]+bgx,overlap[1],combo>0);
                    hf.frame++;
                }
                else if(hf.frame>0&&!p1.hit&&p2.hit&&(!pause||nextframe)){
                    hf.update(overlap2[0]+bgx,overlap2[1],combo>0);
                    hf.frame++;
                }

                if(superstop>0){if(p1.super)sf.create(superstop,p1.y-8);else if(p2.super)sf.create(superstop,p2.y-8);}

                if(combo>1&&cui.slide==0&&cui.slide2==0){cui.slide=64;cui.slide2=12;}
                if(cui.slide>0)cui.slide-=cui.slide2--;
                if(cui.slide<0){cui.slide=0;}
                if(cui.slide==0&&combo==0)cui.slide2=0;
                std::string tempstr;
                tempstr = std::to_string(combo);
                combotext.setString(tempstr);
                combotext.setOrigin(combotext.getLocalBounds().width,0);
                if (combo>1)cui.create(p2.comboed||p2.kdowned);

                p1ilist.create(p1keylist,true);
                p2ilist.create(p2keylist,false);
                hb.create(p1.hp,p2.hp);
                mb.create(p1.meter,p2.meter);

                healthui.setPosition(0.f,0.f);
                sf.setPosition(0,0);
                if(p2.comboed||p2.kdowned)combotext.setPosition(36.f-cui.slide,25.f);
                else combotext.setPosition(248.f+cui.slide,25.f);
                p1graphics.setPosition(int(p1.x-64+bgx),int(p1.y-64));
                p1shadow.setPosition(p1.x-64+bgx,184+(p1.y-176)/8);
                p2graphics.setPosition(int(p2.x-64+bgx),int(p2.y-64));
                p2shadow.setPosition(p2.x-64+bgx,184+(p2.y-176)/8);
                background.setPosition(bgx-125,0.f);

                menus.setcolor(6,!pause,menuselect);
                if(pause){
                    keypresscheck(lightkey1,&menuconfirm);
                    keypresscheck(mediumkey1,&menucancel);
                    keypresscheck(upkey1,&menuup);
                    keypresscheck(downkey1,&menudown);
                    if(menuup=='2'){menuselect--;if(menuselect<0)menuselect=5;}
                    else if(menudown=='2'){menuselect++;if(menuselect>5)menuselect=0;}
                    if((menuconfirm=='2'&&menuselect==0)||menucancel=='2')pause=false;
                    else if(menuconfirm=='2'&&menuselect==1)if(seeboxes)seeboxes=false;else seeboxes=true;
                    else if(menuconfirm=='2'&&menuselect==2)if(keylistshow)keylistshow=false;else keylistshow=true;
                    else if(menuconfirm=='2'&&menuselect==5)gamequit=true;
                }

                sf::RectangleShape blackscreen(sf::Vector2f(256.f, 240.f));
                blackscreen.setFillColor(sf::Color(0,0,0,170));

                p1graphics.setanim(p1.anim,p1.right);
                p2graphics.setanim(p2.anim,p2.right);
                p1shadow.setanim(p1.anim,p1.right);
                p2shadow.setanim(p2.anim,p2.right);

                window.clear();
                renderTexture.clear();
                renderTexture.draw(background);
                renderTexture.draw(p1shadow);
                renderTexture.draw(p2shadow);

                if(superstop>0){renderTexture.draw(blackscreen);renderTexture.draw(sf);}

                if(p1.hit)playertop=true;
                else if(p2.hit) playertop=false;
                if(playertop){
                    renderTexture.draw(p1graphics);
                    renderTexture.draw(p2graphics);
                }
                else{
                    renderTexture.draw(p2graphics);
                    renderTexture.draw(p1graphics);
                }

                if(!p1.proj.empty()){
                character p_graphics[p1.proj.size()];
                    for(short i=0;i<p1.proj.size();i++){
                        p_graphics[i].load(p1texture,false);
                        p_graphics[i].setanim(animlib[p1.proj[i].frame],p1.proj[i].right);
                        p_graphics[i].setPosition(int(p1.proj[i].x-64+bgx),int(p1.proj[i].y-64));
                        renderTexture.draw(p_graphics[i]);
                    }
                }
                if(!p2.proj.empty()){
                character p_graphics[p2.proj.size()];
                    for(short i=0;i<p2.proj.size();i++){
                        p_graphics[i].load(p2texture,false);
                        p_graphics[i].setanim(animlib[p2.proj[i].frame],p2.proj[i].right);
                        p_graphics[i].setPosition(int(p2.proj[i].x-64+bgx),int(p2.proj[i].y-64));
                        renderTexture.draw(p_graphics[i]);
                    }
                }

                if(p1.hitstopped>0||p2.hitstopped)renderTexture.draw(hf);


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

                time.timeset(p1.meter/100);
                time.setPosition(-107,208);
                renderTexture.draw(time);

                time.timeset(p2.meter/100);
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
                    for(short i=0;i<p1.proj.size();i++)window.draw(P_Hitbox1[i]);
                    for(short i=0;i<p2.proj.size();i++)window.draw(P_Hitbox2[i]);
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
