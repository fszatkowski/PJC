#include "crobot.h"
#include "cmath"
#include <QRandomGenerator>

CRobot::CRobot(CMap *m)
    :CMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              0,
              100, m)
{
}

CRobot::CRobot(qreal xv, qreal yv, CMap *m)
    :CMovable(xv, yv, 0, 100, m)
{
}

CRobot::CRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
    :CMovable(xv, yv, anglev, rangev, m)
{
}

void CRobot::move_randomly()
{

    int change_angle = (QRandomGenerator::global()->bounded(10));
    if(!change_angle)
    {
        qreal rate = M_PI/18;
        if(rand()%2)
            angle -= rate;
        else
            angle += rate;
    }
    x += robot_speed*cos(angle);
    y += robot_speed*sin(angle);
}

void CRobot::avoid_boundaries()
{
    qreal rate = M_PI/9 * QRandomGenerator::global()->bounded(0, 3);

    qreal dist_plus = 0;
    qreal dist_minus = 0;

    qreal x_test = x + cos(angle + rate) * robot_speed;
    qreal y_test = y + sin(angle + rate) * robot_speed;

    if(x <= -map_size/2)
    {
        dist_plus += abs(-map_size/2 - x_test);
    }
    else if(x >= map_size/2)
    {
        dist_plus += abs(map_size/2 - x_test);
    }
    else if(y <- -map_size/2)
    {
        dist_plus += abs(-map_size/2 - y_test);
    }
    else if(y >= map_size/2)
    {
        dist_plus += abs(map_size/2 - y_test);
    }

    x_test = x + cos(angle - rate) * robot_speed;
    y_test = y + sin(angle - rate) * robot_speed;

    if(x <= -map_size/2)
    {
        dist_minus += abs(-map_size/2 - x_test);
    }
    else if(x >= map_size/2)
    {
        dist_minus += abs(map_size/2 - x_test);
    }
    else if(y <- -map_size/2)
    {
        dist_minus += abs(-map_size/2 - y_test);
    }
    else if(y >= map_size/2)
    {
        dist_minus += abs(map_size/2 - y_test);
    }

    if(dist_plus <= dist_minus)
        angle += rate;
    else
        angle -= rate;

    x += cos(angle) * robot_speed;
    y += sin(angle) * robot_speed;
}

void CRobot::addItem(CNonMovable *item)
{
    items.push_back(item);
}

void CRobot::go_to(CObject *o)
{
    qreal rate = M_PI/9;

    x += robot_speed*cos(angle);
    y += robot_speed*sin(angle);

    qreal x1 = cos(angle);
    qreal y1 = sin(angle);
    qreal x2 = (o->getx()-x);
    qreal y2 = (o->gety()-y);
    qreal dot = x1*x2 + y1*y2;
    qreal det = x1*y2 - y1*x2;

    qreal diff = atan2(det, dot);
    if(abs(diff) > rate/2 && abs(diff) <= M_PI)
    {
        if(diff > 0)
            angle += rate;
        else
            angle -= rate;
    }
    if(abs(diff) > rate/2 && abs(diff) > M_PI)
    {
        if(diff < 0)
            angle += rate;
        else
            angle -= rate;
    }
}

void CRobot::avoid(std::vector<CNonMovable*> o, std::vector<CRobot*> r)
{
    qreal rate = M_PI/9; //* QRandomGenerator::global()->bounded(3, 5);

    qreal x_test = x + robot_speed * cos(angle);
    qreal y_test = y + robot_speed * sin(angle);
    bool collides = 0;
    bool will_collide = 1;

    for(unsigned int i = 0; i<o.size(); i++)
    {
        qreal distance = (o[i]->getx()-x_test)*(o[i]->getx()-x_test)+(o[i]->gety()-y_test)*(o[i]->gety()-y_test);
        distance = sqrt(distance);
        if(distance < ((1.5*robot_height+robot_width)/2+o[i]->getvalue()/2))
            will_collide = 1;
    }
    for(unsigned int i = 0; i<o.size(); i++)
    {
        qreal distance = (o[i]->getx()-x)*(o[i]->getx()-x)+(o[i]->gety()-y)*(o[i]->gety()-y);
        distance = sqrt(distance);
        if(distance < ((1.5*robot_height+robot_width)/3+o[i]->getvalue()/2))
            will_collide = 1;
    }
    for(unsigned int i = 0; i<r.size(); i++)
    {
        qreal distance = (r[i]->getx()-x)*(r[i]->getx()-x)+(r[i]->gety()-y)*(r[i]->gety()-y);
        distance = sqrt(distance);
        if(distance < 1.5*(robot_height+robot_width))
            collides = 1;
    }
    for(unsigned int i = 0; i<r.size(); i++)
    {
        qreal distance = (r[i]->getx()+robot_speed*cos(r[i]->getangle())-x_test)
                *(r[i]->getx()+robot_speed*cos(r[i]->getangle())-x_test)
                +(r[i]->gety()+robot_speed*sin(r[i]->getangle())-y_test)
                *(r[i]->gety()+robot_speed*sin(r[i]->getangle())-y_test);
        distance = sqrt(distance);
        if(distance < 1.5*(robot_height+robot_width))
            will_collide = 1;
    }

    if(!collides || (collides && !will_collide && r.size()+o.size() > 3))
    {
        x += robot_speed * cos(angle);
        y += robot_speed * sin(angle);
    }

    else
    {
        qreal dist_plus = 0;
        qreal dist_minus = 0;

        qreal x_test = x + cos(angle + rate) * robot_speed;
        qreal y_test = y + sin(angle + rate) * robot_speed;
        for(unsigned int i = 0; i<o.size(); i++)
        {
            qreal distance = (o[i]->getx()-x_test)*(o[i]->getx()-x_test)+(o[i]->gety()-y_test)*(o[i]->gety()-y_test);
            distance = sqrt(distance);
            dist_plus += distance;
        }
        for(unsigned int i = 0; i<r.size(); i++)
        {
            qreal distance = (r[i]->getx()-x_test)*(r[i]->getx()-x_test)+(r[i]->gety()-y_test)*(r[i]->gety()-y_test);
            distance = sqrt(distance);
            dist_plus += distance;
        }

        x_test = x + cos(angle - rate) * robot_speed;
        y_test = y + sin(angle - rate) * robot_speed;
        for(unsigned int i = 0; i<o.size(); i++)
        {
            qreal distance = (o[i]->getx()-x_test)*(o[i]->getx()-x_test)+(o[i]->gety()-y_test)*(o[i]->gety()-y_test);
            distance = sqrt(distance);
            dist_minus += distance;
        }
        for(unsigned int i = 0; i<r.size(); i++)
        {
            qreal distance = (r[i]->getx()-x_test)*(r[i]->getx()-x_test)+(r[i]->gety()-y_test)*(r[i]->gety()-y_test);
            distance = sqrt(distance);
            dist_minus += distance;
        }

        if(dist_plus >= dist_minus)
            angle += rate;
        else
            angle -= rate;
    }
}
