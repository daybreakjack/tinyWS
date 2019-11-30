#ifndef TINYWS_PROCESSPOOL_H
#define TINYWS_PROCESSPOOL_H

#include <utility>
#include <functional>
#include <memory>
#include <vector>
#include <deque>
#include <string>

#include "Process.h"

namespace tinyWS_process {

    class EventLoop;
    class SocketPair;
    class Socket;

    class ProcessPool {
    public:
        using ForkCallback = std::function<void(bool)>;

    private:
        EventLoop* baseLoop_; // 父进程事件循环
        std::unique_ptr<Process> process_; // 子进程
        std::vector<std::unique_ptr<SocketPair>> pipes_;
        std::vector<pid_t> pids_;

//        std::string name_;
        bool running_;
        int next_;

        ForkCallback forkFunction_;
        Process::ChildConnectionCallback childConnectionCallback_;

    public:
        explicit ProcessPool(EventLoop *loop);

        ~ProcessPool();

        void createProccesses(int numProcesses);

        void start();

        void sendToChild(Socket socket);

        void setForkFunction(const ForkCallback& cb);

        void setChildConnectionCallback(const Process::ChildConnectionCallback& cb);

        void newChildConnection(EventLoop* loop, Socket socket);
    };
}


#endif //TINYWS_PROCESSPOOL_H