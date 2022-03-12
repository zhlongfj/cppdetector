#pragma once

class Test() {
public:
    static Test* getInstance();
private:
    static Test* m_tt;
}