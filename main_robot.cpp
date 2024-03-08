#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

#include<unistd.h> // for sleep on unix


int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker"); // Ret til det schema navn du har valgt
    db.setUserName("frhag");  // Ret brugernavn
    db.setPassword("password");  // Ret password
    db.open();
  
    QString robot_name = argv[1];
  
    QSqlQuery query;
    
    query.prepare("INSERT INTO robot (name)"
                  "VALUES (?)");
    query.addBindValue(robot_name);        
    qDebug() << "Insert robot into database " << query.exec();
    
    while(true)
    {
        qDebug() << query.exec("SELECT task_id, description, time FROM task LEFT JOIN robot ON current_task = task_id WHERE name is null");
        
        qDebug() << "Number of rows:" << query.size();
       
        if(query.size() == 0)
            break;
        
        if( query.next() ){

            int id = query.value(0).toInt();
            QString desc  = query.value(1).toString();
            int time = query.value(2).toInt();
            qDebug() << "Task id" << id << "Desc:" << desc << "Time:" << time;

            query.prepare("UPDATE robot "
                            "SET current_task = ? "
                            "WHERE robot.name = ?;");
            query.addBindValue(id);    
            query.addBindValue(robot_name);
            qDebug() << query.exec();
           
            sleep(time);

            query.prepare("UPDATE robot "
                            "SET current_task = NULL "
                            "WHERE robot.name = ?;"  );  
            query.addBindValue(robot_name);
            qDebug() << "NULL:" << query.exec();
            // qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();        


            query.prepare("DELETE FROM task WHERE task_id = ?");
            query.addBindValue(id);
            qDebug() << "DELETE:" << query.exec();
            // qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        }
    }
    
    query.prepare("DELETE FROM robot WHERE name = ?");
    query.addBindValue(robot_name);
    qDebug() << "ROBOT DELETE:" << query.exec();
    
    return 1;
}
