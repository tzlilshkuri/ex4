#include "Download.h"
#include "MyFileReader.h"

/*
client - client's id socket
mys - pointer to the types of the flowers
haveFiles - pointer that tell me if i upload files
constructor
*/
Download::Download(int client, vector<string>* mys, bool* haveFiles) {
    m_dio = new SocketIO(client);
    m_description = "5";
    m_mys = mys;
    m_haveFiles = haveFiles;
}

/*
the function that activate the command
*/
void Download::execute() {
    string error = "0-";
    if (m_mys->size() == 0) {
        error = "please classify the data.";
    }
    if (!*m_haveFiles) {
        if (error == "0-") {
            error = "please upload data.";
        } else {
            error = "please upload data.\n" + error;
        }
    }
    m_dio->write(error);
    if (error != "0-") {
        m_dio->read();
        return;
    }
    m_dio->read();
    for (int i = 0; i < m_mys->size(); i++) {
        string line = to_string(i + 1) + "	" + (*m_mys)[i];
        m_dio->write(to_string(line.size()) + "-" + line);
        m_dio->read();
    }
    m_dio->write("0-");
    //m_dio->read();
    if (m_dio->read() == "1-") {
        return;
    }
}

/*
destructor
*/
Download::~Download() {
    delete m_dio;
}