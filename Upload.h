#ifndef UPLOAD_H
#define UPLOAD_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"

class Upload : public Command{
private:
    string* m_pathTrain;
    string* m_pathWrite;
    int m_client;
public:
    Upload(int client, string* pathTrain, string* pathWrite);
    void execute();
    ~Upload();
};

Upload::Upload(int client, string* pathTrain, string* pathWrite) {
    m_dio = new SocketIO(client);
    m_description = "1";
    m_pathTrain = pathTrain;
    m_pathWrite = pathWrite;
    m_client = client;
}

void Upload::execute(){
    int vecSize = -1;
    string line = "";
    MyFileReader file1, file2;
    m_dio->write("Please upload your local train CSV file.");
    file1.create(m_dio->read() + to_string(m_client), m_dio, &vecSize, 0);
    m_dio->write("Please upload your local test CSV file.");
    file2.create(m_dio->read() + to_string(m_client), m_dio, &vecSize, 1);
}

Upload::~Upload() {
    delete m_dio;
}

#endif