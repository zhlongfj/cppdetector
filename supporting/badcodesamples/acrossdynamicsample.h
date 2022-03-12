#pragma once

class OUTPUT Test1() {
    static Test1& getInstance() {
        static Test1 test;
        return test;
    }
}

class OUTPUT Test2() {
    static Test2& getInstance() {
        static Test2 test;
        return test;
    }
}