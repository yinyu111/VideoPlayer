//
// Created by 尹玉 on 2024/4/8.
//

#include "videoPlayer.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "VideoThread/videoThread.h"

void threadFunction(int i) {
    printf("Thread Function: %d\n", i);
}

void threadFun(int threadIndex) {
    for (int i = 0; i < 100; i++) {
        printf("Thread: %d, index: %d\n", threadIndex, i);
    }
}

int main2() {
    //std::thread t(threadFunction, 10);
    //二选一
    //t.join();   //阻塞状态
    //t.detach();  //子线程于主线程分离 资源由操作系统回收
    //t.joinable();   //回收时检查 是否是joinable状态 不是在return时会异常

    std::cout << "Hello, videoPlayer!" << std::endl;
    std::thread t1(threadFun, 1);
    std::thread t2(threadFun, 2);

    t1.join();
    t2.join();

    return 0;
}

class  videoPlayerThread : public videoThread
{
private:
    int a;
public:
    videoPlayerThread(int _a) {
        a = _a;
    }

    virtual void run() {
        std::cout << "Hello, videoPlayerThread!" << std::endl;
    }
};

int main_thread()
{
     videoPlayerThread t(1);
     t.Start();

     std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}


#include "AVReader/AVReader.h"
#include <iostream>

int main() {
    std::cout << "Hello, videoPlayer + AVReader!" << std::endl;

    AVReader reader;
    int ret = reader.Open("/Users/yinyu/code/testVideo/mumu.mp4");
    if (ret) {
        std::cout << "open file failed!" << std::endl;
        std::cout << "ret: " << ret << std::endl;
    }

    std::vector<AVDecoder*> decoderList;
    int streamCount = reader.GetStreamCount();
    for (int i = 0; i < streamCount; ++i) {
//        AVReaderStream* readerStream = new AVReaderStream();
//        reader.GetStream(readerStream, i);
        AVReaderStream readerStream;
        ret = reader.GetStream(&readerStream, i);
        if (ret) {
            std::cout << "GetStream failed!" << std::endl;
        }

        std::cout << "readerStreamIndex:" << i <<  " get success!" << std::endl;

        AVDecoder* avReaderDecoder = new AVDecoder();
        ret = avReaderDecoder->Init(&readerStream);
        if (ret) {
            std::cout << "AVDecoder Init failed!" << std::endl;
        }

        decoderList.emplace_back(avReaderDecoder);
        std::cout << "readerStreamIndex:" << i <<  " push success!" << std::endl;
    }

    int i = 100;
    while (i) {
        AVReaderPacket* packet = new AVReaderPacket();
        ret = reader.Read(packet);
        if (ret) {
            std::cout << "read frame failed! i:" << i << std::endl;
            break;
        }

        int streamID = packet->GetIndex();
        AVDecoder* avReaderDecoder = decoderList[streamID];

        ret = avReaderDecoder->SendPacket(packet);
        if (ret) {
            std::cout << "Send Packet failed! i:" << i << std::endl;
            break;
        }

        while (1) {
            AVReaderFrame* readerFrame = new AVReaderFrame();
            ret = avReaderDecoder->RecvFrame(&readerFrame);
            if (ret) {
                break;
            }

            std::cout << "frame recv success!" << std::endl;
        }


        std::cout << "read frame success! i:" << i << std::endl;
        i--;
    }

    for (int i = 0; i < streamCount; ++i) {
        AVDecoder* avReaderDecoder = decoderList[i];

        ret = avReaderDecoder->SendPacket(nullptr);
        if (ret) {
            std::cout << "Send Packet failed! i:" << i << std::endl;
            break;
        }

        while (1) {
            AVReaderFrame* readerFrame;
            ret = avReaderDecoder->RecvFrame(&readerFrame);
            if (ret) {
                break;
            }

            std::cout << "frame recv success!" << std::endl;
        }
    }

    reader.Close();

    for (int i = 0; i < streamCount; ++i) {
        AVDecoder* avReaderDecoder = decoderList[i];
        avReaderDecoder->Close();
        delete avReaderDecoder;
    }
    decoderList.clear();

    std::cout << "videoPlayer + AVReader end!" << std::endl;
    return 0;
}