#ifndef UPLOAD_H
#define UPLOAD_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"

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
    BuildVector bv;
    vector<string> partsFile;
    m_dio->write("Please upload your local train CSV file.");
    line = m_dio->read();
    if (line == "1-") {
        return;
    }
    line = line.substr(line.find('-') + 1);
    partsFile = bv.splitEnd(line, '.', 1);
    if (partsFile[0] == "csv" && partsFile[1] != "") {
        line = partsFile[1] + to_string(m_client) + ".csv";
    } else {
        m_dio->write("invalid input");
        m_dio->read();
        return;
    }
    file1.create(line, m_dio, &vecSize, 0);
    m_dio->write("Please upload your local test CSV file.");
    line = m_dio->read();
    line = line.substr(line.find('-') + 1);
    partsFile = bv.splitEnd(line, '.', 1);
    if (partsFile[0] == "csv" && partsFile[1] != "") {
        line = partsFile[1] + to_string(m_client) + ".csv";
    } else {
        m_dio->write("invalid input");
        m_dio->read();
        return;
    }
    file2.create(line, m_dio, &vecSize, 1);
}

Upload::~Upload() {
    delete m_dio;
}

#endif