#include "mainwindow.h"

Base::Base(MainWindow *parent)
{
    qDebug() << this->width();
}

void Base::size_input(QSize size)
{
    qDebug() << size;
}

void Base::add(QString name_variable_temp, QString variable_temp, QString user_name_temp)
{
    QMap < QString,QMap<QString,QString> >::iterator it = base.begin();

    for(; it != base.end(); ++it)
    {
        if(it.key() == user_name_temp)
        {
            it.value().insert(name_variable_temp,variable_temp);
            break;
        }
    }
}

void Base::addUser(QString new_user)
{
    base[new_user];
}

QString Base::take(QString user_name, QString variable_name)
{

    QMap < QString,QMap<QString,QString> >::iterator it = base.find(user_name);
    QMap <QString,QString>::iterator it_value = it.value().begin();

    for(; it_value != it.value().end(); ++it_value)
    {
        if(it_value.key() == variable_name)
            return it_value.value();
    }

    qDebug() << "Елемент не найден!";
    return "0";
}

bool Base::read(QString name_user)
{
    if(name_user == "all")
    {
        qDebug() << "read all";
        return true;
    }
    else
    {
        qDebug() << "read user";
        return true;
    }
}

bool Base::save(QString name_user)
{
    if(name_user == "all")
    {
        qDebug() << "save all";
        return true;
    }
    else
    {
        qDebug() << "save user";
        return true;
    }
}

void Base::rename(QString name_temp, QString new_name_temp)
{

}

void Base::show()
{
    QMap < QString,QMap<QString,QString> >::iterator it = base.begin();
    QString temp_str;

    for(; it != base.end(); ++it)
    {
        QMap <QString,QString>::iterator it_value = it.value().begin();
        for(; it_value != it.value().end(); ++it_value)
        {
            if(temp_str != it.key())
            {
                qDebug() << "User name: " << it.key();
                temp_str = it.key();
            }
            qDebug() << "Name variable: " << it_value.key() << " value = " << it_value.value();
        }
    }
}

Base::~Base()
{

}
