//业务操作
class Stream {
public:
    virtual char Read(int number) = 0;
    virtual void Seek(int position) = 0;
    virtual void Write(char data) = 0;

    virtual ~Stream() {}
};

//主体类
class FileStream : public Stream {
public:
    virtual char Read(int number) {
        //读文件流
    }
    virtual void Seek(int position) {
        //定位文件流
    }
    virtual void Write(char data) {
        //写文件流
    }

};

class NetworkStream :public Stream {
public:
    virtual char Read(int number) {
        //读网络流
    }
    virtual void Seek(int position) {
        //定位网络流
    }
    virtual void Write(char data) {
        //写网络流
    }

};

class MemoryStream :public Stream {
public:
    virtual char Read(int number) {
        //读内存流
    }
    virtual void Seek(int position) {
        //定位内存流
    }
    virtual void Write(char data) {
        //写内存流
    }

};