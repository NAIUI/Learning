class Messager {
protected:
    MessagerImp* messagerImp;
public:
    virtual void Login(string username, string password) = 0;
    virtual void SendMessage(string message) = 0;
    virtual void SendPicture(Image image) = 0;

    virtual ~Messager() {}
};

class MessagerImp {
public:
    virtual void PlaySound() = 0;
    virtual void DrawShape() = 0;
    virtual void WriteText() = 0;
    virtual void Connect() = 0;

    virtual MessagerImp() {}
};


//平台实现

class PCMessagerBase : public MessagerImp {
    {
public:

    virtual void PlaySound() {
        //**********
    }
    virtual void DrawShape() {
        //**********
    }
    virtual void WriteText() {
        //**********
    }
    virtual void Connect() {
        //**********
    }
};

class MobileMessagerBase : public MessagerImp {
public:

    virtual void PlaySound() {
        //==========
    }
    virtual void DrawShape() {
        //==========
    }
    virtual void WriteText() {
        //==========
    }
    virtual void Connect() {
        //==========
    }
};

//业务抽象

class MessagerLite : public Messager{
public:

    virtual void Login(string username, string password) {

        messagerImp->Connect();
        //........
    }
    virtual void SendMessage(string message) {

        messagerImp->WriteText();
        //........
    }
    virtual void SendPicture(Image image) {

        messagerImp->DrawShape();
        //........
    }
};



class MessagerPerfect : public Messager{
    Messager* messager;
public:

    virtual void Login(string username, string password) {

        messagerImp->PlaySound();
        //********
        messagerImp->Connect();
        //........
    }
    virtual void SendMessage(string message) {

        messagerImp->PlaySound();
        //********
        messagerImp->WriteText();
        //........
    }
    virtual void SendPicture(Image image) {

        messagerImp->PlaySound();
        //********
        messagerImp->DrawShape();
        //........
    }
};



void Process() {
    MessagerImp* mImp = new PCMessagerImp();
    Messager* m = new Messager(mImp);
}


