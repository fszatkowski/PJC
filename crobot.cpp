#include "crobot.h"
#include "cmath"
#include <QRandomGenerator>
#include "cmap.h"

CRobot::CRobot(CMap *m)
    :CMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              0,
              100, m)
{
    objectShape = Rect;
    width = robot_width;
    height = robot_height;
}

CRobot::CRobot(qreal xv, qreal yv, CMap *m)
    :CMovable(xv, yv, 0, 100, m)
{
    objectShape = Rect;
    width = robot_width;
    height = robot_height;
}

CRobot::CRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
    :CMovable(xv, yv, anglev, rangev, m)
{
    objectShape = Rect;
    width = robot_width;
    height = robot_height;
}

void CRobot::moveRandomly()
{
    //randomly change angle a little bit
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

void CRobot::returnToMap()
{
    qreal rate = M_PI/9 * QRandomGenerator::global()->bounded(0, 3);

    qreal dist_plus = 0;
    qreal dist_minus = 0;

    qreal x_test = x + cos(angle + rate) * robot_speed;
    qreal y_test = y + sin(angle + rate) * robot_speed;

    if(x <= -map_size/2)
    {
        dist_plus += std::abs(-map_size/2 - x_test);
    }
    else if(x >= map_size/2)
    {
        dist_plus += std::abs(map_size/2 - x_test);
    }
    else if(y <= -map_size/2)
    {
        dist_plus += std::abs(-map_size/2 - y_test);
    }
    else if(y >= map_size/2)
    {
        dist_plus += std::abs(map_size/2 - y_test);
    }

    x_test = x + cos(angle - rate) * robot_speed;
    y_test = y + sin(angle - rate) * robot_speed;

    if(x <= -map_size/2)
    {
        dist_minus += std::abs(-map_size/2 - x_test);
    }
    else if(x >= map_size/2)
    {
        dist_minus += std::abs(map_size/2 - x_test);
    }
    else if(y <= -map_size/2)
    {
        dist_minus += std::abs(-map_size/2 - y_test);
    }
    else if(y >= map_size/2)
    {
        dist_minus += std::abs(map_size/2 - y_test);
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

void CRobot::goTo(CObject *o)
{
    qreal rate = M_PI/9;

    x += robot_speed*cos(angle);
    y += robot_speed*sin(angle);

    qreal x1 = cos(angle);
    qreal y1 = sin(angle);
    qreal x2 = (o->getX()-x);
    qreal y2 = (o->getY()-y);
    qreal dot = x1*x2 + y1*y2;
    qreal det = x1*y2 - y1*x2;

    qreal diff = atan2(det, dot);

    if(std::abs(diff) > rate/2 && std::abs(diff) <= M_PI)
    {
        if(diff > 0)
            angle += rate;
        else
            angle -= rate;
    }
    if(std::abs(diff) > rate/2 && std::abs(diff) > M_PI)
    {
        if(diff < 0)
            angle += rate;
        else
            angle -= rate;
    }
}

void CRobot::avoid(std::vector<CNonMovable*> o, std::vector<CRobot*> r, std::vector<CObstacle*> ob)
{
    qreal rate = M_PI/36 * QRandomGenerator::global()->bounded(3, 5);

    bool stay = false;
    bool rotate = false;
    bool doNothing = false;

    for(unsigned int i = 0; i<o.size(); i++)
    {
        if(willCollide(o[i], robot_speed, 0))
            rotate = true;
    }

//    for(unsigned int i = 0; i<o.size(); i++)
//    {
//        if(collidesWith(o[i]))
//            collides = 1;
//    }
//    for(unsigned int i = 0; i<r.size(); i++)
//    {
//        if(collidesWith(r[i]))
//            collides = 1;
//    }
    for(unsigned int i = 0; i<r.size(); i++)
    {
        if(willCollide(r[i], robot_speed, robot_speed && !collidesWith(r[i])))
        {
            rotate = true;
            if(angle < r[i]->getAngle())
                stay = true;
        }
    }

    for(unsigned int i = 0; i<ob.size(); i++)
    {
        if(willCollide(ob[i], robot_speed, obstacle_speed) && !collidesWith(ob[i]))
        {
            rotate = true;
            stay = true;
        }
        else if (willCollide(ob[i], robot_speed, obstacle_speed) && collidesWith(ob[i]))
        {
            stay = false;
        }
    }

//    for(unsigned int i = 0; i<ob.size(); i++)
//    {
//        if(collidesWith(ob[i]))
//            collides_obstacle = 1;
//    }

    if(rotate && !doNothing)
    {
        qreal dist_plus = 0;
        qreal dist_minus = 0;

        qreal x_test = x + cos(angle + rate) * robot_speed;
        qreal y_test = y + sin(angle + rate) * robot_speed;
        for(unsigned int i = 0; i<o.size(); i++)
        {
            qreal distance = (o[i]->getX()-x_test)*(o[i]->getX()-x_test)+(o[i]->getY()-y_test)*(o[i]->getY()-y_test);
            distance = sqrt(distance);
            dist_plus += distance;
        }
        for(unsigned int i = 0; i<r.size(); i++)
        {
            qreal distance = (r[i]->getX()-x_test)*(r[i]->getX()-x_test)+(r[i]->getY()-y_test)*(r[i]->getY()-y_test);
            distance = sqrt(distance);
            dist_plus += distance;
        }
        for(unsigned int i=0; i<ob.size(); i++)
        {
            qreal distance = (ob[i]->getX()-x_test)*(ob[i]->getX()-x_test)+(ob[i]->getY()-y_test)*(ob[i]->getY()-y_test);
            distance = sqrt(distance);
            dist_plus += distance;
        }

        x_test = x + cos(angle - rate) * robot_speed;
        y_test = y + sin(angle - rate) * robot_speed;
        for(unsigned int i = 0; i<o.size(); i++)
        {
            qreal distance = (o[i]->getX()-x_test)*(o[i]->getX()-x_test)+(o[i]->getY()-y_test)*(o[i]->getY()-y_test);
            distance = sqrt(distance);
            dist_minus += distance;
        }
        for(unsigned int i = 0; i<r.size(); i++)
        {
            qreal distance = (r[i]->getX()-x_test)*(r[i]->getX()-x_test)+(r[i]->getY()-y_test)*(r[i]->getY()-y_test);
            distance = sqrt(distance);
            dist_minus += distance;
        }
        for(unsigned int i=0; i<ob.size(); i++)
        {
            qreal distance = (ob[i]->getX()-x_test)*(ob[i]->getX()-x_test)+(ob[i]->getY()-y_test)*(ob[i]->getY()-y_test);
            distance = sqrt(distance);
            dist_minus += distance;
        }

        if(dist_plus >= dist_minus)
            angle += rate;
        else
            angle -= rate;
    }
    if(!stay && !doNothing)
    {
        x += robot_speed * cos(angle);
        y += robot_speed * sin(angle);
    }
}
