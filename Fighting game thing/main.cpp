#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <random>
#include <deque>
#include <string.h>
#include <math.h>


using namespace std;
std::deque<char>dirkeys,ukey,ikey,okey,kkey,dirkeys2,ukey2,ikey2,okey2,kkey2,p1keylist,p2keylist;
std::deque<int> animq1,animq2;
std::random_device rd;
std::mt19937 gen(rd());

short p1frame=0,p1act=0,p1col=0,p1anim[64][2],p1hitstun=0,p1hitstop=0,p1buffer=0,combo=0,p1movewait=0,
        p2frame=0,p2act=0,p2col=0,p2anim[64][2],p2hitstun=0,p2hitstop=0,p2buffer,roundframecount=0,p2movewait=0,
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
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //crouch (8)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{4,9},{5,9},{-1},{-1},{-1},
                   {-1},{-1},{-1},{4,10},{5,10},{-1},{-1},{-1},
                   {-1},{-1},{-1},{4,11},{5,11},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //hit (9)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,3},{1,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,4},{1,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,5},{0,7},{1,7},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //crouch u1 (10)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,3},{1,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,4},{1,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,5},{0,6},{1,6},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //crouch u2 (11)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,3},{2,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,4},{2,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,5},{2,5},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //crouch i1 (12)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,3},{3,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,4},{3,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,5},{3,5},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //crouch i2 (13)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,3},{4,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,4},{4,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,5},{4,5},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //crouch i3 (14)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,1},{1,1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{5,4},{6,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //walk left1 (15)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,1},{1,1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{7,4},{8,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //walk left2 (16)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,1},{1,1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{5,5},{6,5},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //walk right1 (17)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,0},{1,0},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,1},{1,1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{7,5},{8,5},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //walk right2 (18)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{2,8},{3,8},{4,8},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //knockdown (19)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{5,2},{6,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{5,3},{6,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //specialA1 (20)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{7,2},{8,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{7,3},{8,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //specialA2 (21)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{9,2},{10,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{9,3},{10,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //specialA3 (22)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{11,2},{12,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{11,3},{12,3},{-1},{-1},{-1},
                   {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //specialA4 (23)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{9,4},{10,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{9,5},{10,5},{11,5},{-1},{-1},
                   {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //specialA5 (24)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{12,4},{13,4},{-1},{-1},{-1},
                   {-1},{-1},{-1},{12,5},{13,5},{14,5},{-1},{-1},
                   {-1},{-1},{-1},{0,2},{1,2},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //specialA6 (25)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{5,6},{6,6},{-1},{-1},{-1},
                   {-1},{-1},{-1},{5,7},{6,7},{-1},{-1},{-1},
                   {-1},{-1},{-1},{5,8},{6,8},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //stand o1 (26)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{8,6},{9,6},{-1},{-1},{-1},
                   {-1},{-1},{7,7},{8,7},{9,7},{-1},{-1},{-1},
                   {-1},{-1},{-1},{8,8},{9,8},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //stand o2 (27)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{11,6},{-1},{-1},{-1},{-1},
                   {-1},{-1},{10,7},{11,7},{12,7},{13,7},{-1},{-1},
                   {-1},{-1},{10,8},{11,8},{12,8},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //stand o3 (28)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{6,9},{7,9},{-1},{-1},{-1},
                   {-1},{-1},{7,6},{6,10},{7,10},{-1},{-1},{-1},
                   {-1},{-1},{-1},{6,11},{7,11},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //stand o4 (29)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{8,9},{9,9},{-1},{-1},{-1},
                   {-1},{-1},{-1},{8,10},{9,10},{10,6},{-1},{-1},
                   {-1},{-1},{-1},{8,11},{9,11},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //stand o5 (30)
                   {{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{11,9},{12,9},{-1},{-1},
                   {-1},{-1},{-1},{10,10},{11,10},{12,10},{10,9},{-1},
                   {-1},{-1},{-1},{10,11},{11,11},{12,11},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},
                   {-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}},
                   //stand o6 (31)
                   },
                   hurtboxcount[256]={2,3,3,2,2,2,3,3,2,2,3,3,2,3,3,2,2,2,2,0,2,2,2,2,3,3,2,3,3,3,3,3},
                   hitboxcount[256]={0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1};
float p1x=100.0,p1y=176.0,p1jumpx=0.0,p1jumpy=0.0,p1kback=0.0,p1launch=0.0,p1hp=500.0,p1dmg=0.0,p1paway=0.0,
        p2x=156.0,p2y=176.0,p2jumpx=0.0,p2jumpy=0.0,p2kback=0.0,p2launch=0.0,p2hp=500.0,p2dmg=0.0,p2paway=0.0,
        bgx=0,
colbox[256][1][2][2]={{{{-7,-10},{9,32}}},//standing
                    {{{-7,-1},{9,32}}},//crouching
                    {{{-31,20},{16,32}}},//knockdown
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
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //hit (9)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{4,24},{22,32}}},
                    //crouch u1 (10)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{4,26},{24,32}}},
                    //crouch u2 (11)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}}},
                    //crouch i1 (12)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{6,-8},{15,20}}},
                    //crouch i2 (13)
                    {{{-11,9},{13,32}},{{-7,-6},{9,9}},{{6,-11},{15,20}}},
                    //crouch i3 (14)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //walk left1 (15)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //walk left2 (16)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //walk right1 (17)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //walk right2 (18)
                    {-1},
                    //knockdown (19)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //specialA1 (20)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //specialA2 (21)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //specialA3 (22)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}}},
                    //specialA4 (23)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-4,0},{24,12}}},
                    //specialA5 (24)
                    {{{-11,0},{11,32}},{{-7,-15},{9,0}},{{-2,0},{26,12}}},
                    //specialA6 (25)
                    {{{-15,1},{11,32}},{{-9,-14},{7,1}}},
                    //stand o1 (26)
                    {{{-16,0},{9,32}},{{-12,-14},{4,1}},{{4,2},{16,8}}},
                    //stand o2 (27)
                    {{{-22,2},{7,32}},{{-16,-13},{0,2}},{{0,0},{18,9}}},
                    //stand o3 (28)
                    {{{-22,2},{9,32}},{{-15,-14},{6,2}},{{0,0},{16,9}}},
                    //stand o4 (29)
                    {{{-11,0},{11,32}},{{-7,-15},{14,0}},{{4,0},{28,9}}},
                    //stand o5 (30)
                    {{{-11,0},{15,32}},{{2,-13},{19,1}},{{6,1},{35,10}}},
                    //stand o6 (31)
                    },
hitbox[256][8][2][2]={{0},
                    //idle (0)
                    {0},
                    //stand u1 (1)
                    {{{4,-1},{22,7}}},
                    //stand u2 (2)
                    {0},
                    //stand i1 (3)
                    {0},
                    //stand i2 (4)
                    {0},
                    //stand i3 (5)
                    {0},
                    //stand i4 (6)
                    {{{5,11},{30,20}}},
                    //stand i5 (7)
                    {0},
                    //crouch (8)
                    {0},
                    //hit (9)
                    {0},
                    //crouch u1 (10)
                    {{{5,25},{26,32}}},
                    //crouch u2 (11)
                    {0},
                    //crouch i1 (12)
                    {0},
                    //crouch i2 (13)
                    {{{6,-13},{19,20}}},
                    //crouch i3 (14)
                    {0},
                    //walk left1 (15)
                    {0},
                    //walk left2 (16)
                    {0},
                    //walk right1 (17)
                    {0},
                    //walk right2 (18)
                    {0},
                    //knockdown (19)
                    {0},
                    //specialA1 (20)
                    {0},
                    //specialA2 (21)
                    {0},
                    //specialA3 (22)
                    {0},
                    //specialA4 (23)
                    {0},
                    //specialA5 (24)
                    {{{10,-6},{29,16}}},
                    //specialA6 (25)
                    {0},
                    //stand o1 (26)
                    {0},
                    //stand o2 (27)
                    {0},
                    //stand o3 (28)
                    {0},
                    //stand o4 (29)
                    {0},
                    //stand o5 (30)
                    {{{8,2},{36,9}}},
                    //stand o6 (31)
                    };
bool p1air=false,p2air=false,seeboxes=false,F1key=false,F2key=false,F3key=false,
pause=false,Enterkey=false,nextframe=false,backslash=false,p1cancel[256],p2cancel[256],
p1whiff=false,p2whiff=false,p1neutural,p2neutural,p1right=true,p2right=false,
p1hit=false,p2hit=false,p1block=false,p2block=false,p1slide=false,p2slide=false,
hitbefore=false,hitbefore2=false,p1multihit=false,p2multihit=false,flash=true,
p1knockdown=false,p2knockdown=false,p1damaged=false,p2damaged=false,p1comboed=false,p2comboed=false,
p1kdowned=false,p2kdowned=false,playertop=false,keylistshow=false;


struct character : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))
            return false;
        m_tileset.setRepeated(true);

        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(512);

        for (unsigned int i = 0; i < 8; ++i)
            for (unsigned int j = 0; j < 8; ++j)
            {
                sf::Vertex* tri = &m_vertices[(j + i * 8) * 6];

                tri[0].position = sf::Vector2f(0+j*16,0+i*16);
                tri[1].position = sf::Vector2f(16+j*16,0+i*16);
                tri[2].position = sf::Vector2f(0+j*16,16+i*16);
                tri[3].position = sf::Vector2f(0+j*16,16+i*16);
                tri[4].position = sf::Vector2f(16+j*16,0+i*16);
                tri[5].position = sf::Vector2f(16+j*16,16+i*16);
            }
        return true;
    }

    void setanim(short anim[][2],bool right){
            for (unsigned int i = 0; i < 8; ++i)
                for (unsigned int j = 0; j < 8; ++j){
                if(right==true){
                    sf::Vertex* tri = &m_vertices[(j + i * 8) * 6];
                    tri[0].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16);
                    tri[1].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16);
                    tri[2].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16+16);
                    tri[3].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16+16);
                    tri[4].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16);
                    tri[5].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16+16);

                }
                else{
                    sf::Vertex* tri = &m_vertices[(7-j + i * 8) * 6];
                    tri[0].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16);
                    tri[1].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16);
                    tri[2].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16+16);
                    tri[3].texCoords = sf::Vector2f(anim[j+i*8][0]*16+16, anim[j+i*8][1]*16+16);
                    tri[4].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16);
                    tri[5].texCoords = sf::Vector2f(anim[j+i*8][0]*16, anim[j+i*8][1]*16+16);

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

struct hitflash : public sf::Drawable, public sf::Transformable
{
public:
    void create(float px,float py){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        for(unsigned int i=0;i<3;i++){
            float x,y,x2,y2;
            std::uniform_int_distribution<int> dis(0,1);
            if(dis(gen)==0){
                if(dis(gen)==0)y=0;
                else y=239;
                std::uniform_int_distribution<int> dis(0,255);
                x=dis(gen);
                std::uniform_int_distribution<int> dis2(-16,16);
                x2=x+dis2(gen);
                y2=y;
            }
            else {
                if(dis(gen)==0)x=0;
                else x=255;
                std::uniform_int_distribution<int> dis(0,239);
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
        m_lines.setPrimitiveType(sf::Lines);
        m_lines.resize(32);
        for(unsigned int i=0;i<8;i++){
            float angle=i * 3.14f / 4.f;
            float x=std::cos(angle),y=std::sin(angle);
            sf::Vertex* line = &m_lines[i*2];
            line[i*2].position = sf::Vector2f(px+x,py+y);
            line[i*2+1].position = sf::Vector2f(x*16+px,y*16+py);
        }
        m_circle.setPrimitiveType(sf::Lines);
        m_circle.resize(64);
        sf::Vertex* circle = &m_circle[32];
        for(unsigned int i=0;i<12;i++){
            float angle=i * 3.14f / 6.f,angle2=(i+1) * 3.14f / 6.f;;
            circle[i*2].position = sf::Vector2f((std::cos(angle))*4+px,(std::sin(angle))*4+py);
            circle[i*2+1].position = sf::Vector2f((std::cos(angle2))*4+px,(std::sin(angle2))*4+py);
        }
    }


    void update(float px,float py,int pass){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        for(unsigned int i=0;i<3;i++){
            sf::Vertex* triangles = &m_vertices[i*3];
            if(pass%2==0&&pass>3&&flash){
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
            line[i*2].position = sf::Vector2f(px+x*(pass+8),py+y*(pass+8));
            line[i*2+1].position = sf::Vector2f(x*(float(pass)/8+16)+px,y*(float(pass)/8+16)+py);
            if(pass>3&&pass%2==1&&flash){line[i*2].color=sf::Color::Transparent;line[i*2+1].color=sf::Color::Transparent;}
            else {line[i*2].color=sf::Color::White;line[i*2+1].color=sf::Color::White;}
        }
        m_circle.setPrimitiveType(sf::Lines);
        m_circle.resize(64);
        sf::Vertex* circle = &m_circle[32];
        for(unsigned int i=0;i<12;i++){
            float angle=i * 3.14f / 6.f,angle2=(i+1) * 3.14f / 6.f;;
            circle[i*2].position = sf::Vector2f((std::cos(angle))*(4+pass)+px,(std::sin(angle))*(4+pass)+py);
            circle[i*2+1].position = sf::Vector2f((std::cos(angle2))*(4+pass)+px,(std::sin(angle2))*(4+pass)+py);

            if(pass>3&&pass%2==1&&flash){circle[i*2].color=sf::Color::Transparent;circle[i*2+1].color=sf::Color::Transparent;}
            else {circle[i*2].color=sf::Color::White;circle[i*2+1].color=sf::Color::White;}
        }
    }

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

struct healthbar : public sf::Drawable, public sf::Transformable
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
        float temp=hp/500*88;
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
        temp=hp2*88/500;
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

struct timeui : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
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


struct comboui : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
    }
    void create(bool right,float slide){
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(32);
        m_tileset.setRepeated(true);
        sf::Vertex* tri = &m_vertices[6];
        if(right){
            tri[0].position = sf::Vector2f(0-slide,32);
            tri[1].position = sf::Vector2f(0-slide,80);
            tri[2].position = sf::Vector2f(64-slide,32);
            tri[3].position = sf::Vector2f(64-slide,32);
            tri[4].position = sf::Vector2f(0-slide,80);
            tri[5].position = sf::Vector2f(64-slide,80);
        }
        else{
            tri[0].position = sf::Vector2f(181+slide,32);
            tri[1].position = sf::Vector2f(181+slide,80);
            tri[2].position = sf::Vector2f(245+slide,32);
            tri[3].position = sf::Vector2f(245+slide,32);
            tri[4].position = sf::Vector2f(181+slide,80);
            tri[5].position = sf::Vector2f(245+slide,80);
        }
        tri[0].texCoords = sf::Vector2f(0,0);
        tri[1].texCoords = sf::Vector2f(0,48);
        tri[2].texCoords = sf::Vector2f(64,0);
        tri[3].texCoords = sf::Vector2f(64,0);
        tri[4].texCoords = sf::Vector2f(0,48);
        tri[5].texCoords = sf::Vector2f(64,48);
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




struct inputlist : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset)
    {
        if (!m_tileset.loadFromFile(tileset))return false;
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

struct box : public sf::Drawable, public sf::Transformable
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

bool cmdcheck(int playercode,int len,char s[][5]){
    //s[][0]==num,s[][1]==u,s[][2]==i,s[][3]==o,s[][4]==k
    short temp=0;
    for(int j=0;j<15;j++){
        char dir,u,i,o,k;
        if(playercode==1)dir=dirkeys[j],u=ukey[j],i=ikey[j],o=okey[j],k=kkey[j];
        else if(playercode==2)dir=dirkeys2[j],u=ukey2[j],i=ikey2[j],o=okey2[j],k=kkey2[j];
        if(u=='1')u='0';
        if(i=='1')i='0';
        if(o=='1')o='0';
        if(k=='1')k='0';

        if((dir!=s[temp][0]&&dir!=s[temp-1][0])||(u!=s[temp][1]||i!=s[temp][2]||o!=s[temp][3]||k!=s[temp][4])&&temp!=len-1)break;
        if(dir==s[temp][0]&&u==s[temp][1]&&i==s[temp][2]&&o==s[temp][3]&&k==s[temp][4])temp++;
        if(temp==len)break;
    }
    if(temp==len)return true;
    else return false;

}

int chooseaction(int playercode, bool p1air, char keydir, char u, char i, char o,char k){
            if(p1air==false){
                if(keydir=='1'||keydir=='2'||keydir=='3'){
                    //crouching actions
                    if(o=='2')return 14;//strong normal
                    else if(i=='2')return 13;//middle normal
                    else if(u=='2')return 12;//weak normal
                    else return 11;//crouch
                }
                else{
                    //grounded actions
                    if(o=='2'){
                        char temp[4][5]={{'6','0','0','2','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}},
                            temp2[4][5]={{'5','0','0','2','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}};
                        if(cmdcheck(playercode,4,temp)||cmdcheck(playercode,4,temp2))return 18;//special A strong
                        else return 10;//strong normal
                    }
                    if(i=='2'){
                        char temp[4][5]={{'6','0','2','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}},
                            temp2[4][5]={{'5','0','2','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}};
                        if(cmdcheck(playercode,4,temp)||cmdcheck(playercode,4,temp2))return 17;//special A middle
                        else return 9;//middle normal
                    }
                    else if(u=='2'){
                        char temp[4][5]={{'6','2','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}},
                            temp2[4][5]={{'5','2','0','0','0'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}};
                        if(cmdcheck(playercode,4,temp)||cmdcheck(playercode,4,temp2))return 16;//special A weak
                        else return 8;//weak normal
                    }
                    else if(k=='2'){
                        char temp[4][5]={{'6','0','0','0','2'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}},
                            temp2[4][5]={{'5','0','0','0','2'},{'6','0','0','0','0'},{'3','0','0','0','0'},{'2','0','0','0','0'}};
                        if(cmdcheck(playercode,4,temp)||cmdcheck(playercode,4,temp2))return 19;//special A gimmick
                        else return 15;//gimmick
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
                        if(cmdcheck(playercode,3,temp))return 4;//rightdash
                        else return 3;//rightwalk
                    }
                    else if(keydir=='8'){
                        return 5;//upjump
                    }
                    else if(keydir=='7'){
                        return 6;//leftjump
                    }
                    else if(keydir=='9'){
                        return 7;//rightjump
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

void boolfill(bool *arr,bool value,short a[],int len){
    for(int i=0;i<len;i++){
        arr[a[i]]=value;
    }
}


void characterdata(std::deque<int> &animq,bool cancel[],bool *air,short anim[][2],short *act,short *col,short *frame,
    bool *whiff,float *x,float *y,float *jumpx,float *jumpy,bool *right,bool *hit,bool *block,float enemyx,short *hitstun,short enemyhitstun,
    float *kback,float enemykback,bool *slide,bool *multihit,short *hitstop,unsigned int hitwait,short *buffer,bool *neutural,float *launch,float enemylaunch,
    float *hp, float enemyhp, float *dmg,bool *comboed,bool *kdown,bool enemykdown,bool *kdowned,short *movewait,float *pushaway,float *enemypaway){
    if(*kdowned&&animq.size()<10&&!*comboed&&!*act==0){
        for(short i=0;i<3;i++){animq.push_back(8);}
        *kdowned=false;combo=0;
    }
    if(*hit){
        *hit=false;animq.clear();*col=0;*jumpy=0,*comboed=true;*movewait=-1;
        for(short i=0;i<hitwait+enemyhitstun;i++)animq.push_back(9);
        if(*x<-110||*x>360){*pushaway+=enemykback;*pushaway+=int(enemylaunch/2);}
        else{if(*x<enemyx)*jumpx=-enemykback;else if(*x>enemyx) *jumpx=enemykback;}
        if(enemylaunch>0){*jumpy=-enemylaunch;*air=true;}
        if(*air)*slide=false;
        else *slide=true;
        if(enemykdown)*kdowned=true;
        else *kdowned=false;
        memset(cancel,false,256);
    }
    else if(animq.empty()&&*movewait==-1){
        if((*comboed&&(*jumpy<5||*kdowned)&&*air)||(*comboed&&!(*jumpy<5)&&*air&&*act==0))animq.push_back(9);
        else if(*comboed&&!*air&&*kdowned){
            *col=2;*comboed=false;
            for(short i=0;i<48;i++){animq.push_back(19);}
        }
        else if(*kdowned){
            for(short i=0;i<3;i++){animq.push_back(8);}
            *kdowned=false;combo=0;
        }
        else{
            memset(cancel,false,256);
            if(!*neutural&&!*air){*jumpx=0;*jumpy=0;}
            *hitstun=0;*kback=0;*hit=false;*slide=false;*multihit=false;*dmg=0;*launch=0;*neutural=true;*kdown=false;
            if(*comboed){combo=0;*comboed=0;}
        }
    }
    if(!*hit&&(animq.empty()&&*movewait==-1||((cancel[*act]==true)&&(!*whiff)))){
        if(cancel[*act]==true){
            *buffer=0;*slide=false;*hitstun=0;*kback=0;*dmg=0;*launch=0;*kdown=false;*movewait=-1;
            memset(cancel,false,256);
            animq.clear();
        }
        if(*act==0){
            if(!*air){
                if(*x<enemyx)*right=true;
                else *right=false;
            }
            *col=0;*frame=0;
            memcpy(anim,animlib[0],sizeof(animlib[0]));
        }
        else if(*act==1){
            *col=0;
            memcpy(anim,animlib[15],sizeof(animlib[0]));
            if(*right)*x-=3;else *x+=3;
        }
        else if(*act==2){*col=0;*air=true;*jumpy=-3.0;if(*right)*jumpx=-7;else*jumpx=7;}
        else if(*act==3){
            *col=0;
            memcpy(anim,animlib[17],sizeof(animlib[0]));
            if(*right)*x+=3;else *x-=3;
        }
        else if(*act==4){*col=0;*air=true;*jumpy=-3.0;if(*right)*jumpx=7;else*jumpx=-7;}
        else if(*act==5){*col=0;*jumpy=-14.0;*movewait=4;animq.insert(animq.begin(), {8,8,8,0});}
        else if(*act==6){*col=0;*jumpy=-14.0;*movewait=4;if(*right)*jumpx=-3;else*jumpx=3;animq.insert(animq.begin(), {8,8,8,0});}
        else if(*act==7){*col=0;*jumpy=-14.0;*movewait=4;if(*right)*jumpx=3;else*jumpx=-3;animq.insert(animq.begin(), {8,8,8,0});}
        else if(*act==8){
            *col=0;*multihit=false;*hitstop=10;*kback=4;*hitstun=4;*dmg=7;
            animq.insert(animq.begin(), {1,1,1,2,2,2,1,1,1});
            short temp[6]={9,10,16,17,18,19};boolfill(cancel,true,temp,6);
        }
        else if(*act==9){
            *col=0;*multihit=false;*hitstop=14;*kback=5;*hitstun=1;*slide=true;*dmg=10;
            animq.insert(animq.begin(), {3,4,5,5,5,5,5,6,7,7,7,7,7,6,5,5,4,4,3,3});
            short temp[5]={10,16,17,18,19};boolfill(cancel,true,temp,5);
            *movewait=7;
            if(*right)*jumpx=3;
            else *jumpx=-3;
        }
        else if(*act==10){
            *col=0;*multihit=false;*hitstop=16;*kback=6;*hitstun=-1;*slide=true;*dmg=16;
            animq.insert(animq.begin(), {26,26,27,27,28,28,28,28,28,29,30,31,31,31,31,31,31,31,30,29,28,28,28,27,27,27,26,26,26});
            short temp[4]={16,17,18,19};boolfill(cancel,true,temp,4);
            *movewait=9;
            if(*right)*jumpx=5;
            else *jumpx=-5;
        }
        else if(*act==11){
            if(*x<enemyx)*right=true;
            else *right=false;
            *col=1;*frame=8;
            memcpy(anim,animlib[8],sizeof(animlib[8]));
        }
        else if(*act==12){
            *col=1;*multihit=false;*hitstop=10;*kback=5;*hitstun=4;*dmg=7;
            animq.insert(animq.begin(), {10,10,10,11,11,11,10,10,10});
            short temp[6]={13,14,16,17,18,19};boolfill(cancel,true,temp,6);
        }
        else if(*act==13){}//crouch middle
        else if(*act==14){
            *col=1;*multihit=false;*hitstop=14;*kback=3;*hitstun=1;*slide=true;*dmg=15;*launch=10;*kdown=true;
            animq.insert(animq.begin(), {12,12,12,13,14,14,14,14,14,14,13,12,12,12});
            if(*right)*jumpx=4;else *jumpx=-4;
            short temp[4]={16,17,18,19};boolfill(cancel,true,temp,4);
        }
        else if(*act==15){}//maybe a taunt move?
        else if(*act==16){
            *col=0;*multihit=false;*hitstop=16;*kback=7;*hitstun=1;*slide=true;*movewait=6;*dmg=10;
            animq.insert(animq.begin(), {20,21,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,22,21,20,20});
            if(*right)*jumpx=5;else *jumpx=-5;
        }
        else if(*act==17){
            *col=0;*multihit=false;*hitstop=18;*kback=7;*hitstun=-1;*slide=true;*movewait=9;*dmg=14;*kdown=true;
            animq.insert(animq.begin(), {20,20,21,21,22,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,23,22,22,21,21,20,20});
            if(*right)*jumpx=6;else *jumpx=-6;
        }
        else if(*act==18){
            *col=0;*multihit=false;*hitstop=21;*kback=0;*hitstun=0;*slide=true;*movewait=10;*dmg=17;*kdown=true;*launch=11;
            animq.insert(animq.begin(), {20,20,20,21,21,22,22,22,22,22,23,24,25,25,25,25,25,25,24,24,23,23,22,22,21,21,20,20});
            if(*right)*jumpx=7;else *jumpx=-7;
        }
        else if(*act==19){
            *col=0;*multihit=false;*slide=true;*movewait=6;
            animq.insert(animq.begin(), {20,21,22,22,22,22,21,20});
            if(*right)*jumpx=4;else *jumpx=-4;
        }
    }
    if(*movewait>0)*movewait-=1;
    else{*x+=*jumpx;if(*jumpy<0)*air=true;*y+=*jumpy;*movewait=-1;}
    if(*slide&&*movewait==-1){
        if(*jumpx>0)*jumpx-=1;
        else if(*jumpx<0)*jumpx+=1;
    }
    if(*enemypaway>0){if(*x<enemyx)*x-=*enemypaway;else if(*x>enemyx)*x+=*enemypaway;*enemypaway-=1;}
    if(!animq.empty()){
        *neutural=false;*frame=animq[0];
        memcpy(anim,animlib[animq[0]],sizeof(animlib[animq[0]]));
        animq.pop_front();
    }
    if(*air){
            *jumpy+=1;
            if(*y>175){
                if(*x<enemyx)*right=true;else *right=false;
                if(*kdowned){}//add downed landing animation
                else if(*jumpx!=7&&*jumpx!=-7){*col=1;animq.insert(animq.begin(), {8,8,8,8});}
                else {*col=1;animq.insert(animq.begin(), {8,8,8,8,8,8,8,8});}
                cancel[8]=true;cancel[9]=true;
                *jumpx=0;*jumpy=0;*y=176;*air=false;
            }
        }
}

int main()
{
    hitflash hf;
    healthbar hb;
    timeui time;
    comboui cui;
    inputlist p1ilist,p2ilist;
    if (!p1ilist.load("inputicon.png")){}
    if (!p2ilist.load("inputicon.png")){}
    if (!time.load("time_ui.png")){}
    if (!cui.load("combo_ui.png")){}
    short hitstop=0,p1hitwait=0,p2hitwait=0,sfx=0;
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(256, 240)){}
    float overlap[2],overlap2[2],comboslide=0,comboslide2=0;
	sf::RenderWindow window(sf::VideoMode(256,240), "fighting game thingy");
	sf::Text pausetext;
	sf::Text combotext;
	sf::Font font;
	character p1;
	if (!p1.load("char_sprites.png")){}
	character p2;
	if (!p2.load("char_sprites.png")){}
	sf::Texture bgtexture,hutexture;
	if (!bgtexture.loadFromFile("teststage.png")){}
	if (!hutexture.loadFromFile("health_ui.png")){}
    sf::Sprite background,healthui;
    background.setTexture(bgtexture);
    healthui.setTexture(hutexture);
	char keydir1='5',keydir2='5';
	if(!font.loadFromFile("PerfectDOSVGA437.ttf")){}
	pausetext.setFont(font);
	pausetext.setCharacterSize(16);
	pausetext.setFillColor(sf::Color::White);
	combotext.setFont(font);
	combotext.setCharacterSize(32);
	combotext.setFillColor(sf::Color::Black);
    char u='0',i='0',o='0',k='0',u2='0',i2='0',o2='0',k2='0';
    time.create();
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
            if(!F1key){
                F1key=true;
                if(seeboxes)seeboxes=false;
                else seeboxes=true;
            }
        }
        else F1key=false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
            if(!F2key){
                F2key=true;
                if(keylistshow)keylistshow=false;
                else keylistshow=true;
            }
        }
        else F2key=false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
            if(!F3key){
                F3key=true;
                if(flash)flash=false;
                else flash=true;
            }
        }
        else F3key=false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if(!Enterkey){
                Enterkey=true;
                if(pause)pause=false;
                else pause=true;
            }
        }
        else Enterkey=false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backslash)){
            if(backslash==false){
                backslash=true;
                nextframe=true;
            }
        }
        else backslash=false;

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
        if(!p1right){
            if(keydir1=='7')keydir1='9';
            else if(keydir1=='9')keydir1='7';
            else if(keydir1=='4')keydir1='6';
            else if(keydir1=='6')keydir1='4';
            else if(keydir1=='3')keydir1='1';
            else if(keydir1=='1')keydir1='3';
        }

        if(w2==true&&a2==false&&s2==false&&d2==false)keydir2='8';
        else if(w2==false&&a2==true&&s2==false&&d2==false)keydir2='4';
        else if(w2==false&&a2==false&&s2==true&&d2==false)keydir2='2';
        else if(w2==false&&a2==false&&s2==false&&d2==true)keydir2='6';
        else if(w2==true&&a2==true&&s2==false&&d2==false)keydir2='7';
        else if(w2==false&&a2==true&&s2==true&&d2==false)keydir2='1';
        else if(w2==false&&a2==false&&s2==true&&d2==true)keydir2='3';
        else if(w2==true&&a2==false&&s2==false&&d2==true)keydir2='9';
        else keydir2='5';
        if(!p2right){
            if(keydir2=='7')keydir2='9';
            else if(keydir2=='9')keydir2='7';
            else if(keydir2=='4')keydir2='6';
            else if(keydir2=='6')keydir2='4';
            else if(keydir2=='3')keydir2='1';
            else if(keydir2=='1')keydir2='3';
        }

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
                p1buffer=chooseaction(1,p1air,keydir1,u,i,o,k);
                if(p1cancel[p1buffer]==false&&animq1.size()>5)p1buffer=0;
                else if(p1buffer==1||p1buffer==3||p1buffer==11)p1buffer=0;
        }
        if(p2buffer==0&&!animq2.empty()){
                p2buffer=chooseaction(2,p2air,keydir2,u2,i2,o2,k2);
                if(p2cancel[p2buffer]==false&&animq2.size()>5)p2buffer=0;
                else if(p2buffer==1||p2buffer==3||p2buffer==11)p2buffer=0;
        }

        if(p1damaged){
                if(combo>19)p2dmg/=10;
                else if(combo>3)p2dmg=p2dmg*(21-combo)/20;
                p1hp-=p2dmg;p1damaged=false;
        }
        else if(p2damaged){
                if(combo>19)p1dmg/=10;
                else if(combo>3)p1dmg=p1dmg*(21-combo)/20;
                p2hp-=p1dmg;p2damaged=false;
        }
        if(!pause||pause&&nextframe)roundframecount++;
        if((pause==false||(pause==true&&nextframe==true))&&hitstop==0){
            nextframe=false;

            if(p1buffer==0)p1act=chooseaction(1,p1air,keydir1,u,i,o,k);
            else if(!animq1.empty()&&!p1whiff)p1act=p1buffer;
            if(animq1.empty()){if(!p1whiff){p1act=p1buffer;}p1buffer=0;}

            if(p2buffer==0)p2act=chooseaction(2,p2air,keydir2,u2,i2,o2,k2);
            else if(!animq2.empty()&&!p2whiff)p2act=p2buffer;
            if(animq2.empty()){if(!p2whiff){p2act=p2buffer;}p2buffer=0;}

            //make an attack clashing system at some point

            if(p1hit){
                characterdata(animq1,p1cancel,&p1air,p1anim,&p1act,&p1col,&p1frame,&p1whiff,&p1x,&p1y,&p1jumpx,&p1jumpy,&p1right,&p1hit,
                              &p1block,p2x,&p1hitstun,p2hitstun,&p1kback,p2kback,&p1slide,&p1multihit,&p1hitstop,p2hitwait,&p1buffer,&p1neutural,
                              &p1launch,p2launch,&p1hp,p2hp,&p1dmg,&p1comboed,&p1knockdown,p2knockdown,&p1kdowned,&p1movewait,&p1paway,&p2paway);
                characterdata(animq2,p2cancel,&p2air,p2anim,&p2act,&p2col,&p2frame,&p2whiff,&p2x,&p2y,&p2jumpx,&p2jumpy,&p2right,&p2hit,
                              &p2block,p1x,&p2hitstun,p1hitstun,&p2kback,p1kback,&p2slide,&p2multihit,&p2hitstop,p1hitwait,&p2buffer,&p2neutural,
                              &p2launch,p1launch,&p2hp,p1hp,&p2dmg,&p1comboed,&p2knockdown,p1knockdown,&p2kdowned,&p2movewait,&p2paway,&p1paway);}
            else{
                characterdata(animq2,p2cancel,&p2air,p2anim,&p2act,&p2col,&p2frame,&p2whiff,&p2x,&p2y,&p2jumpx,&p2jumpy,&p2right,&p2hit,
                              &p2block,p1x,&p2hitstun,p1hitstun,&p2kback,p1kback,&p2slide,&p2multihit,&p2hitstop,p1hitwait,&p2buffer,&p2neutural,
                              &p2launch,p1launch,&p2hp,p1hp,&p2dmg,&p2comboed,&p2knockdown,p1knockdown,&p2kdowned,&p2movewait,&p2paway,&p1paway);
                characterdata(animq1,p1cancel,&p1air,p1anim,&p1act,&p1col,&p1frame,&p1whiff,&p1x,&p1y,&p1jumpx,&p1jumpy,&p1right,&p1hit,
                              &p1block,p2x,&p1hitstun,p2hitstun,&p1kback,p2kback,&p1slide,&p1multihit,&p1hitstop,p2hitwait,&p1buffer,&p1neutural,
                              &p1launch,p2launch,&p1hp,p2hp,&p1dmg,&p1comboed,&p1knockdown,p2knockdown,&p1kdowned,&p1movewait,&p1paway,&p2paway);
            }

            float temp[2],temp2[2],temp3[2],temp4[2];
            if(p1right==true){
                temp[0]=colbox[p1col][0][0][0]+p1x;
                temp[1]=colbox[p1col][0][0][1]+p1y;
                temp2[0]=colbox[p1col][0][1][0]+p1x;
                temp2[1]=colbox[p1col][0][1][1]+p1y;
            }
            else{
                temp[0]=-colbox[p1col][0][1][0]+p1x;
                temp[1]=colbox[p1col][0][0][1]+p1y;
                temp2[0]=-colbox[p1col][0][0][0]+p1x;
                temp2[1]=colbox[p1col][0][1][1]+p1y;
            }
            if(p2right==true){
                temp3[0]=colbox[p2col][0][0][0]+p2x;
                temp3[1]=colbox[p2col][0][0][1]+p2y;
                temp4[0]=colbox[p2col][0][1][0]+p2x;
                temp4[1]=colbox[p2col][0][1][1]+p2y;
            }
            else{
                temp3[0]=-colbox[p2col][0][1][0]+p2x;
                temp3[1]=colbox[p2col][0][0][1]+p2y;
                temp4[0]=-colbox[p2col][0][0][0]+p2x;
                temp4[1]=colbox[p2col][0][1][1]+p2y;
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
            p1hitwait=animq1.size();
            p2hitwait=animq2.size();
            for(int i=hurtboxcount[p1frame]-1;i>=0;i--){
                if(p1right==true){
                    temp[0]=hurtbox[p1frame][i][0][0]+p1x;
                    temp[1]=hurtbox[p1frame][i][0][1]+p1y;
                    temp2[0]=hurtbox[p1frame][i][1][0]+p1x;
                    temp2[1]=hurtbox[p1frame][i][1][1]+p1y;
                }
                else{
                    temp[0]=-hurtbox[p1frame][i][1][0]+p1x;
                    temp[1]=hurtbox[p1frame][i][0][1]+p1y;
                    temp2[0]=-hurtbox[p1frame][i][0][0]+p1x;
                    temp2[1]=hurtbox[p1frame][i][1][1]+p1y;
                }
                for(int j=0;j<hitboxcount[p2frame];j++){
                    if(p2right==true){
                        temp3[0]=hitbox[p2frame][j][0][0]+p2x;
                        temp3[1]=hitbox[p2frame][j][0][1]+p2y;
                        temp4[0]=hitbox[p2frame][j][1][0]+p2x;
                        temp4[1]=hitbox[p2frame][j][1][1]+p2y;
                    }
                    else{
                        temp3[0]=-hitbox[p2frame][j][1][0]+p2x;
                        temp3[1]=hitbox[p2frame][j][0][1]+p2y;
                        temp4[0]=-hitbox[p2frame][j][0][0]+p2x;
                        temp4[1]=hitbox[p2frame][j][1][1]+p2y;
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
            }
            if(p1hit==true)p2whiff=false;
            if(p1hit==false){hitbefore=false;p2whiff=true;}
            else if(p1hit==true&&p2multihit==false&&hitbefore==false)hitbefore=true;
            else if(hitbefore==true)p1hit=false;
            if(p1hit==true){hitstop=p2hitstop;memcpy(p1anim,animlib[9],sizeof(animlib[9]));combo++;p1damaged=true;}

            for(int i=hurtboxcount[p2frame]-1;i>=0;i--){
                if(p2right==true){
                    temp[0]=hurtbox[p2frame][i][0][0]+p2x;
                    temp[1]=hurtbox[p2frame][i][0][1]+p2y;
                    temp2[0]=hurtbox[p2frame][i][1][0]+p2x;
                    temp2[1]=hurtbox[p2frame][i][1][1]+p2y;
                }
                else{
                    temp[0]=-hurtbox[p2frame][i][1][0]+p2x;
                    temp[1]=hurtbox[p2frame][i][0][1]+p2y;
                    temp2[0]=-hurtbox[p2frame][i][0][0]+p2x;
                    temp2[1]=hurtbox[p2frame][i][1][1]+p2y;
                }
                for(int j=0;j<hitboxcount[p1frame];j++){
                    if(p1right==true){
                        temp3[0]=hitbox[p1frame][j][0][0]+p1x;
                        temp3[1]=hitbox[p1frame][j][0][1]+p1y;
                        temp4[0]=hitbox[p1frame][j][1][0]+p1x;
                        temp4[1]=hitbox[p1frame][j][1][1]+p1y;
                    }
                    else{
                        temp3[0]=-hitbox[p1frame][j][1][0]+p1x;
                        temp3[1]=hitbox[p1frame][j][0][1]+p1y;
                        temp4[0]=-hitbox[p1frame][j][0][0]+p1x;
                        temp4[1]=hitbox[p1frame][j][1][1]+p1y;
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
            }
            if(p2hit==true)p1whiff=false;
            if(p2hit==false){hitbefore2=false;p1whiff=true;}
            else if(p2hit==true&&p1multihit==false&&hitbefore2==false)hitbefore2=true;
            else if(hitbefore2==true)p2hit=false;
            if(p2hit==true){hitstop=p1hitstop;memcpy(p2anim,animlib[9],sizeof(animlib[9]));combo++;p2damaged=true;}

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
        if(p1keylist.size()>50)for(short i=0;i<5;i++)p1keylist.pop_back();


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
        if(p2keylist.size()>50)for(short i=0;i<5;i++)p2keylist.pop_back();


        if(hitstop>0&&(!pause||nextframe))hitstop--;

        box collisionbox1,collisionbox2,Hitbox1,Hurtbox1,Hitbox2,Hurtbox2;
        collisionbox1.create(p1x+bgx,p1y,colbox[p1col],p1right,1,sf::Color::White);
        collisionbox2.create(p2x+bgx,p2y,colbox[p2col],p2right,1,sf::Color::White);
        Hurtbox1.create(p1x+bgx,p1y,hurtbox[p1frame],p1right,hurtboxcount[p1frame],sf::Color::Blue);
        Hitbox1.create(p1x+bgx,p1y,hitbox[p1frame],p1right,hitboxcount[p1frame],sf::Color::Red);
        Hurtbox2.create(p2x+bgx,p2y,hurtbox[p2frame],p2right,hurtboxcount[p2frame],sf::Color::Blue);
        Hitbox2.create(p2x+bgx,p2y,hitbox[p2frame],p2right,hitboxcount[p2frame],sf::Color::Red);

        if(hitstop==0)sfx=0;
        if(p1hit&&!p2hit&&!pause&&sfx==0){
            sfx=1;
            hf.create(overlap[0]+bgx,overlap[1]);
        }
        else if(p2hit&&!p1hit&&!pause&&sfx==0){
            sfx=1;
            hf.create(overlap2[0]+bgx,overlap2[1]);
        }
        else if(sfx>0&&p1hit&&!p2hit&&!pause){
            sfx++;
            hf.update(overlap[0]+bgx,overlap[1],sfx);
        }
        else if(sfx>0&&!p1hit&&p2hit&&!pause){
            sfx++;
            hf.update(overlap2[0]+bgx,overlap2[1],sfx);
        }
        if(combo>1&&comboslide==0&&comboslide2==0){comboslide=64;comboslide2=12;}
        if(comboslide>0)comboslide-=comboslide2--;
        if(comboslide<0){comboslide=0;}
        if(comboslide==0&&combo==0)comboslide2=0;
        std::string tempstr;
        tempstr = std::to_string(combo);
        combotext.setString(tempstr);
        if (combo>1)cui.create(p2comboed||p2kdowned,comboslide);
        pausetext.setString("Paused");

        p1ilist.create(p1keylist,true);
        p2ilist.create(p2keylist,false);
        hb.create(p1hp,p2hp);
        if(roundframecount/60<99)time.timeset(99-roundframecount/60);
        else time.timeset(0);

        healthui.setPosition(0.f,0.f);
        if(p2comboed||p2kdowned)combotext.setPosition(22.f-comboslide,25.f);
        else combotext.setPosition(203.f+comboslide,25.f);
        pausetext.setPosition(200.f, 16.f);
        p1.setPosition(p1x-64+bgx,p1y-64);
        p2.setPosition(p2x-64+bgx,p2y-64);
        background.setPosition(bgx-125,0.f);

        p1.setanim(p1anim,p1right);
        p2.setanim(p2anim,p2right);

		window.clear();
		renderTexture.clear();
		renderTexture.draw(background);
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
		if(keylistshow){renderTexture.draw(p1ilist);renderTexture.draw(p2ilist);}
		renderTexture.draw(hb);
		renderTexture.draw(healthui);
		renderTexture.draw(time);
		if(combo>1){renderTexture.draw(cui);renderTexture.draw(combotext);}
		if(pause)renderTexture.draw(pausetext);
		if(hitstop>0)renderTexture.draw(hf);

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
		}
		window.display();
	}
	return 0;
}
