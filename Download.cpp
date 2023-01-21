#include "Download.h"
#include "MyFileReader.h"

Download::Download(int client, string* path, bool* send) {
    m_send = send;
    m_dio = new SocketIO(client);
    m_description = "5";
    m_path = path;
}

void Download::execute() {
    if (!m_send) {
        m_dio->write("0-");
        m_dio->read();
        return;
    }
    if (m_dio->read() == "1-"){
        return;
    }
    MyFileReader file;
    file.load(/**m_path*/"i_c.csv");
    vector<Flower> flowers = file.getGarden();
    for(int i = 0; i < flowers.size(); i++) {
        string line = to_string(i + 1) + "\t" + flowers[i].getType();
        m_dio->write(to_string(line.size()) + "-" + line);
        m_dio->read();
    }
    m_dio->write("0-");
    m_dio->read();
}

Download::~Download() {
    delete m_dio;
}