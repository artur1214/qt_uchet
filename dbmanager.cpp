#include "dbmanager.h"
#include <QtSql>
#include <QtDebug>
#include <QVariant>
#include "appsettings.h"
DBManager * DBManager::p_instance =nullptr;

short DBManager::addWork(QString date, QString desc, QString requestId)
{

    q.prepare("INSERT INTO works (date_column, description, request_id, user_id) VALUES ( :date , :desc , :id , :user );");
    q.bindValue(":date", date);
    q.bindValue(":desc", desc);
    q.bindValue(":id", requestId);
    q.bindValue(":user", AppSettings::curUser);
    if(!q.exec()){
        if(q.lastError().number() == 19){
            return 19;
        }
        else{
            qDebug() << q.lastError() << "" << q.lastError().number();
            qDebug()<<q.lastQuery() + " " + desc;
            qDebug() << " не удалось сделать запрос добавления работы";
            exit(-2);
            return -2;
        }
    }
    else{
        return 1;
    }
}

DBManager::~DBManager()
{
    //delete instance;
}
//DBManager* DBManager::p_instance = nullptr;
DBManager::DBManager(QString dbName)
{

    //this почти везде можно не писать, но я пишу, чтоб быть увереным, что всё нормально
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(dbName);
    this->q = QSqlQuery(sdb);
    if(dbName == ""){
        qDebug() << "Забыли название БД";
        exit(-2);
    }
    if (!sdb.open()) {
        qDebug() << "БД не работает";
        qDebug() << sdb.lastError().text();
        exit(-2);
    }
    else {
        qDebug()<<"База данных подключена "<< dbName;
        q = QSqlQuery(sdb);

    }
}

DBManager::DBManager(){
}

QList<DBManager::User> DBManager::getAllUsers()
{
    QList<DBManager::User> users;
    q.prepare("SELECT id, name, client_id FROM users;");
    if(!q.exec()){
        qDebug() << " не удалось сделать запрос получения списка пользователей";
        exit(-2);
    }
    while(q.next()){
        if(!q.value(2).isNull()){
            users.append(DBManager::User(q.value(0).toString(), q.value(1).toString(), q.value(2).toString()));
        }
        else {
            users.append(DBManager::User(q.value(0).toString(), q.value(1).toString(), ""));
        }
        //qDebug() << q.value(2).isNull();
    }
    return users;
    //return false;
}

QList<DBManager::User> DBManager::getAllUsers(QString clientId)
{
    QList<DBManager::User> users;
    if( clientId == ""){
        q.prepare("SELECT id, name, client_id FROM users where client_id is NULL;");
    }
    else{
        q.prepare("SELECT id, name, client_id FROM users where client_id is :clientId ;");
        q.bindValue(":clientId", clientId.toInt());
    }
    if(!q.exec()){
        qDebug() << " не удалось сделать запрос получения списка пользователей";
        exit(-2);
    }
    while(q.next()){
        if(!q.value(2).isNull()){
            users.append(DBManager::User(q.value(0).toString(), q.value(1).toString(), q.value(2).toString()));
        }
        else {
            users.append(DBManager::User(q.value(0).toString(), q.value(1).toString(), ""));
        }
    }
    return users;
}

bool DBManager::login(QString login, QString password){


    q.prepare("SELECT * FROM users WHERE users.login = :login AND users.password = :password");
    q.bindValue(":login", login);
    q.bindValue(":password", password);
    if(!q.exec()){
        qDebug() << " не удалось сделать запрос";
        exit(-2);
    }
    if(q.next()){
        if(q.value(3).toInt()==0){
            return false;
        }
        //user = q.value(0).toInt();
        AppSettings::curUser = q.value(0).toString();
        return true;
    }
    return false;
}

int DBManager::addDeviceType(QString name)
{
    q.prepare("INSERT into device_types (name) VALUES ( :name );");
    q.bindValue(":name", name);
    if(!q.exec()){
        if(q.lastError().number() == 19){
            return 19;
        }
        else{

            qDebug() << q.lastError() << "" << q.lastError().number();
            qDebug()<<q.lastQuery() + " " + name;
            qDebug() << " не удалось сделать запрос добавления типа девайса";
            exit(-2);
            return -2;
        }
    }
    else{
        return 1;
    }
}

short DBManager::addStatus(QString desc, QString hex)
{
    q.prepare("INSERT into statuses (desc, color) VALUES ( :desc , :hex );");
    q.bindValue(":desc", desc);
    q.bindValue(":hex", hex);
    if(!q.exec()){
        if(q.lastError().number()){
            q.prepare("SELECT * from statuses WHERE desc = :desc");
            q.bindValue(":desc", desc);
            if(q.exec()){
                if(q.next()){
                    return 19;  //если есть имя
                }
                else{
                    return 20; // eсли цвет
                }
            }
            //return 19;
        }
        qDebug() << q.lastError() << "" << q.lastError().number();
        qDebug() << "Не могу добавить статус";
        exit(-2);
    }
    else {
        return 1;
    }
}

AppSettings::RequestStatus DBManager::getStatus(QString id)
{
    q.prepare("select * from statuses where id = :id");
    q.bindValue(":id", id);
    if(q.exec())
        if(q.next())
            return AppSettings::RequestStatus(id, q.value(1).toString(), q.value(2).toString());
    exit(-2);
}


DBManager *DBManager::instance(QString name)
{
    QMutex mutex;
    if(!p_instance){
        mutex.lock();
        if (!p_instance)
            p_instance = new DBManager(name);
        mutex.unlock();
    }
    return p_instance;
}

short DBManager::removeWork(QString id)
{
    q.prepare("DELETE FROM works WHERE id = :id ;");
    q.bindValue(":id", id);
    if(!q.exec()){
        if(q.lastError().number() == 19){
            return 19;
        }
        else{
            qDebug() << q.lastError() << "" << q.lastError().number();
            qDebug()<<q.lastQuery() + " " + id;
            qDebug() << " не удалось сделать запрос Удаления Работы";
            exit(-2);
            return -2;
        }
    }
    else{
        return 1;
    }
}

short DBManager::removeRequest(QString id)
{
    q.prepare("DELETE from works where request_id = :id ");
    q.bindValue(":id", id);
    q.exec();
    q.prepare("DELETE FROM requests WHERE id = :id ;");
    q.bindValue(":id", id);
    if(!q.exec()){
        if(q.lastError().number() == 19){
            return 19;
        }
        else{
            qDebug() << q.lastError() << "" << q.lastError().number();
            qDebug()<<q.lastQuery() + " " + id;
            qDebug() << " не удалось сделать запрос Удаления Работы";
            exit(-2);
            return -2;
        }
    }
    else{
        return 1;
    }
}

short DBManager::addRequest(QString userId, QString modelId, QString problem, QString date)
{
    q.prepare("INSERT into requests (user_id, model_id, problem, date) VALUES ( :userId , :modelId , :problem, :date );");
    q.bindValue(":userId", userId);
    q.bindValue(":modelId", modelId);
    q.bindValue(":problem", problem);
    q.bindValue(":date", date);
    if(!q.exec()){
        if(q.lastError().number() == 19){
            return 19;
        }
        else{
            qDebug() << q.lastError() << "" << q.lastError().number();
            //qDebug()<<q.lastQuery() + " " + name;
            qDebug() << " не удалось сделать запрос добавления типа девайса";
            exit(-2);
            return -2;
        }
    }
    else{
        return 1;
    }
}

QList<AppSettings::RequestStatus> DBManager::getAllRequestStatuses()
{
    QList<AppSettings::RequestStatus> res;
    q.prepare("select * from statuses");
    if(!q.exec()){
        qDebug() << q.lastError() << " Не могу получить все статусы (dbmanager::241) ";
        exit(-2);
    }
    else{
        while (q.next()) {
            res.append(AppSettings::RequestStatus(q.value(0).toString(), q.value(1).toString(), q.value(2).toString()));
        }
    }
    return res;
}


QList<DBManager::RequestsQuerryRes> DBManager::getAllRequests()
{
    QList<RequestsQuerryRes> rows;
    QStringList ids;
    if(!q.exec(QString("select requests.id, users.name, users.phone, requests.problem, devices.name,")
                + " requests.date, requests.status_id from requests inner join users inner join devices where " +
               "requests.user_id = users.id and requests.model_id = devices.id")){
            qDebug() << q.lastError() << "" << q.lastError().number();
            qDebug()<<q.lastQuery();
            qDebug() << " не удалось сделать запросполучения id запросов";
            exit(-2);
            //return -2;
    }
    else{
        while (q.next()) {
            QString id = q.value(0).toString();
            ids.append(id);
            rows.append(RequestsQuerryRes(q.value(0).toString(), q.value(1).toString(), q.value(2).toString(), q.value(3).toString(), q.value(4).toString(), q.value(5).toString(), q.value(6).toString()));
        }
    }
    for (int i = 0; i < rows.length(); i++) {
        q.prepare("select * from works where works.request_id = :id ");
        q.bindValue(":id", rows[i].id->text());
        if(!q.exec()){
            qDebug() << q.lastError() << "" << q.lastError().number();
            qDebug()<<q.lastQuery();
            qDebug() << " не удалось сделать запрос получения работ";
        }
        else{

            if(q.size()!= 0){
                while (q.next()) {
                    DBManager::Work work(q.value(0).toString(), q.value(1).toString(), q.value(2).toString(), q.value(3).toString(), q.value(4).toString());
                    rows[i].works.append(work);
                    //row.append(q.value(0).toString());
                    //row.append(q.value(1).toString());
                    //row.append(q.value(2).toString());
                    //row.append(q.value(3).toString());
                    //row.append(q.value(4).toString());
                    //rows[i].works.append(row);
                    qDebug() << q.value(2).toString();
                }
                rows[i].createStatus();
            }
            else {

            }
        }
    }


    return rows;
}

QList<DBManager::Client> DBManager::getAllClients()
{
    QList<DBManager::Client> clients;
    q.prepare("SELECT id, name FROM clients;");
    if(!q.exec()){
        qDebug() << " не удалось сделать запрос получения списка клиентов";
        exit(-2);
    }
    while(q.next()){
        clients.append(DBManager::Client(q.value(0).toString(), q.value(1).toString()));
    }
    return clients;
    //return false;
}

DBManager::Client DBManager::getClient(QString id)
{

    q.prepare("SELECT id, name FROM clients WHERE id = :id ;");
    q.bindValue(":id", id.toInt());
    if(!q.exec()){
        qDebug() << " не удалось сделать запрос получения списка клиентов";
        exit(-2);
    }
    if(q.next()){
        return Client(q.value(0).toString(), q.value(1).toString());
    }
    else {
        exit(-2);
    }
    //return clients;
}


short DBManager::addClient(QString name)
{
    q.prepare("INSERT into clients (name) VALUES ( :name );");
    q.bindValue(":name", name);
    if(!q.exec()){
        if(q.lastError().number() == 19){
            return 19;
        }
        else{
            qDebug() << q.lastError() << " " << q.lastError().number();
            qDebug() << " не удалось сделать запрос добавления типа девайса";
            exit(-2);
            return -2;
        }
    }
    else{
        return 1;
    }
}

short DBManager::addUser(QString name, QString clientId, QString contact)
{
    q.prepare("INSERT into users (name, client_id, phone) VALUES ( :name , :clientId, :contact );");
    q.bindValue(":name", name);
    if(clientId == ""){
        q.bindValue(":clientId", QVariant(NULL));
    }
    else{
        q.bindValue("clientId", clientId);
    }
    q.bindValue(":contact", contact);
    if(!q.exec()){
        if(q.lastError().number() == 19){
            return 19;
        }
        else{
            qDebug() << q.lastError() << " " << q.lastError().number();
            qDebug() << " не удалось сделать запрос добавления пользователя";
            exit(-2);
            //return -2;
        }
    }
    else{
        return 1;
    }
}

short DBManager::addDevice(QString name, QString typeId)
{
    q.prepare("INSERT into devices (name, device_type_id) VALUES ( :name , :typeId );");
    q.bindValue(":name", name);
    q.bindValue(":typeId", typeId.toInt());
    if(!q.exec()){
        qDebug() << q.lastError() << " " << q.lastError().number();
        qDebug() << " не удалось добавить девайс";
        exit(-2);
        //return -2;
    }
    else{
        return 1;
    }
}

QList<DBManager::DeviceType> DBManager::getDeviceTypes()
{
    QList<DBManager::DeviceType> deviceTypes;
    q.prepare("SELECT * FROM device_types;");
    if(!q.exec()){
        qDebug() << q.lastError() << " " << q.lastError().number();
        qDebug() << " не удалось сделать запрос получения типов девайсов";
        exit(-2);
        //return -2;
    }
    else {
        while(q.next()) {
            deviceTypes.append(DBManager::DeviceType(q.value(0).toString(), q.value(1).toString()));
        }

    }
    return deviceTypes;
}

QList<DBManager::Device> DBManager::getDevices(QString typeId)
{
    QList<DBManager::Device> devices;
    if(typeId == ""){
        q.prepare("SELECT * FROM devices ;");
    }
    else {
        q.prepare("SELECT * FROM devices where device_type_id = :typeId ;");
        q.bindValue(":typeId", typeId);
    }
    if(!q.exec()){
        qDebug() << q.lastError() << " " << q.lastError().number();
        qDebug() << " не удалось сделать запрос получения девайсов";
        exit(-2);
        //return -2;
    }
    else {
        while(q.next()) {
            devices.append(DBManager::Device(q.value(0).toString(), q.value(1).toString(), q.value(2).toString()));
        }

    }
    return devices;

}

short DBManager::changeWork(QString id, QString newDate, QString newDesc)
{
    q.prepare("UPDATE works SET date_column = :date , description = :desc WHERE id = :id ;");
    q.bindValue(":date", newDate);
    q.bindValue(":desc", newDesc);
    q.bindValue(":id", id);
    if(!q.exec()){
        qDebug() << q.lastError() << " " << q.lastError().number();
        qDebug() << " не удалось сделать запрос получения типов девайсов";
        exit(-2);
        //return -2;
    }
    else {
        return 1;
    }
}

DBManager::Work DBManager::getWork(QString id)
{
    q.prepare("SELECT * FROM works where id = :id ;");
    q.bindValue(":id", id);
    if(!q.exec()){
        qDebug() << q.lastError() << " " << q.lastError().number();
        qDebug() << " не удалось сделать запрос получения Работы";
        exit(-2);
        //return -2;
    }
    else {
        //qDebug() << "Парсю";
        if(q.next())
            return Work(id, q.value(1).toString(), q.value(2).toString(), q.value(3).toString(), q.value(4).toString());
    }
}


void DBManager::RequestsQuerryRes::createStatus()
{
    this->status = DBManager::instance()->getStatus(this->status.id);
    this->id->setData(Qt::BackgroundRole, QColor(this->status.color));
    this->id->setToolTip("Cтатус: " + this->status.desc);
    this->id->setWhatsThis("Статус:" + this->status.desc);
    //this->user->setData(Qt::BackgroundRole, QColor(this->status.color));
    //this->date->setData(Qt::BackgroundRole, QColor(this->status.color));
    //this->problem->setData(Qt::BackgroundRole, QColor(this->status.color));
    //this->model->setData(Qt::BackgroundRole, QColor(this->status.color));
}

DBManager::RequestsQuerryRes::RequestsQuerryRes(QString id, QString user, QString userPhone, QString model, QString problem, QString date, QString status_id) :
    status(AppSettings::RequestStatus(status_id, "", ""))
{
    this->id = new QTableWidgetItem(); this->id->setText(id);

    this->user = new QTableWidgetItem(); this->user->setText(user + "\n" + userPhone);
    this->model = new QTableWidgetItem(); this->model->setText(model);
    this->problem = new QTableWidgetItem(); this->problem->setText(problem);
    this->date = new QTableWidgetItem(); this-> date ->setText(date);
    //this->status = status_id;

}

DBManager::User::User(QString id, QString name, QString clientId)
{
    this->id = id;
    this->name = name;
    this->clientId = clientId;
}

DBManager::Client::Client(QString id, QString name)
{
    this->id = id;
    this->name = name;
}

DBManager::Device::Device(QString id, QString name, QString type)
{
    this->id = id;
    this->name = name;
    this->type = type;
}

DBManager::DeviceType::DeviceType(QString id, QString name)
{
    this->id = id;
    this->name = name;
}

DBManager::Work::Work(QString id, QString date, QString desc, QString request, QString user)
{
    this->id = id;
    this->date = date;
    this->desc = desc;
    this->user = user;
    this->request_id = request;
}







