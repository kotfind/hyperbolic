#include "Leap.h"

class LeapMotion : public Leap::Controller {
    public:
        LeapMotion();

        double horDir = 0;
        double vertDir = 0;
        bool validDirs = false;

    private:
        class Listener : public Leap::Listener {
            public:
                Listener(double& horDir, double& vertDir, bool& validDirs);

                void onConnected(const Leap::Controller&);
                void onDisconnected(const Leap::Controller&);
                void onFrame(const Leap::Controller&);

                double& horDir;
                double& vertDir;
                bool& validDirs;
        };

        Listener listener;
};
