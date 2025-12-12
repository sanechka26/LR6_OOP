#include <gtest/gtest.h>
#include "../include/SUBJECTS.h"
#include "../include/OBSERVER.h"
#include <sstream>
#include <iostream>

class TestObserver : public OBSERVER {
public:
    std::vector<std::string> messages;
    void update(std::string msg) override {
        messages.push_back(msg);
    }
};

TEST(ObserverTest, NotifyWorks) {
    SUBJECTS subject;
    TestObserver obs;
    subject.attach(&obs);

    subject.notifyObservers("Test message");
    EXPECT_EQ(obs.messages.size(), 1);
    EXPECT_EQ(obs.messages[0], "Test message");
}