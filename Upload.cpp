#include "Upload.h"

/*
client - the client's id for socket
pathTrain - pointer to the updates path of the classified file
pathWrite - pointer to the updates path of the unclassified file
haveFiles - tell me if i have files or not
constructor
*/
Upload::Upload(int client, string* pathTrain, string* pathWrite, bool *haveFiles) {
    m_dio = new SocketIO(client);
    m_description = "1";
    m_files = haveFiles;
    m_pathTrain = pathTrain;
    m_pathWrite = pathWrite;
    m_client = client;
}

/*
the function that activate the command
*/
void Upload::execute(){
    int vecSize = -1;
    string line = "", pathT;
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
    if (!file1.create(line, m_dio, &vecSize, 0)) {
        return;
    }
    pathT = line;
    m_dio->write("Please upload your local test CSV file.");
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
    if (!file2.create(line, m_dio, &vecSize, 1)) {
        return;
    }
    *m_files = true;
    *m_pathTrain = pathT;
    *m_pathWrite = line;
}

/*
destructor
*/
Upload::~Upload() {
    delete m_dio;
}