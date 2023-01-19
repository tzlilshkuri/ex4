#ifndef SETTINGS_H
#define SETTINGS_H
#include "Command.h"
#include "SocketIO.h"

class Settings : public Command {
private:
    int* m_k;
    string* m_mat;
public:
    Settings(int client, int* m_k, string* m_mat);
    void execute();
    ~Settings();
};

#endif