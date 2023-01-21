#include "Settings.h"
#include "BuildVector.h"


Settings::Settings(int client, int* k, string* mat) {
    m_description = "2";
    m_dio = new SocketIO(client);
    m_k = k;
    m_mat = mat;
}

bool validK(string k) {
    for (int i = 0; i < k.size(); i++) {
        if (k[i] < '0' || k[i] > '9') {
            return false;
        }  
    }
    if (k == "" || !stoi(k)) {
        return false;
    } 
    return true;
}

void Settings::execute() {
    m_dio->write("The current KNN parameters are: k = " + to_string(*m_k)
     + ", distance metric = " + *m_mat);
    string rec = m_dio->read();
    if (rec != "0-") {
        string snd = "";
        BuildVector bv;
        int find = rec.find('-') + 1;
        rec = rec.substr(find, rec.size() - find);
        vector<string> vec = bv.splitEnd(rec, ' ', 1);
        if (vec[1] == "") {
            vec[1] = vec[0];
            vec[0] = "";
        }
        if (!validK(vec[1])) {
            snd = "invalid value for K";
        }
        if (vec[0] != "MAN" && vec[0] != "MIN" && vec[0] != "AUC" &&
            vec[0] != "CAN" && vec[0] != "CHB") {
            if (snd == "") {
                snd = "invalid value for metric";
            } else {
                snd += "\ninvalid value for metric";
            }
        }
        if (snd == "") {
            *m_mat = vec[0];
            *m_k = stoi(vec[1]);
            m_dio->write("0-");
        } else {
            m_dio->write(snd);
        }
    } else {
        m_dio->write("0-");
    }
    m_dio->read();
}

Settings::~Settings() {
    delete m_dio;
}