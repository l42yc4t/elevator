#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
// git clone test!
const int NUM_FLOORS = 10;
const int ELEVATOR_SPEED = 1; // 一層樓的運行時間（秒）

class Elevator {
private:
    int current_floor;
    int num;
    // bool not_picked = false; 

public:
    // bool not_picked = false;
    Elevator(int n) : current_floor(0) {num = n;}

    void display_floor() {
        std::cout << "Elevator" << num << " is currently on floor " << current_floor << std::endl;
    }

    void move(int floor) {
        if (floor < 0 || floor >= NUM_FLOORS) {
            std::cout << "Invalid floor number. Please enter a number between 0 and " << NUM_FLOORS - 1 << std::endl;
            return;
        }

        while (current_floor != floor) {
            display_floor();
            std::this_thread::sleep_for(std::chrono::seconds(ELEVATOR_SPEED));
            if (current_floor < floor) {
                current_floor++;
            } else {
                current_floor--;
            }


            // std::this_thread::sleep_for(std::chrono::seconds(ELEVATOR_SPEED));
        }
        display_floor();
        // not_picked = !not_picked;
    }

    int getCurrentFloor() const {
        return current_floor;
    }
};

int main() {
    Elevator elevator1(1);
    Elevator elevator2(2);
    bool server = false;
    std::string s1, s2;
    int ctrl_elenum, ctrl_floornum, target_floor;

    while (true) {
        int current_floor, desired_floor;
        std::cout << "Enter your current floor (0-" << NUM_FLOORS - 1 << "): ";
        std::cin >> current_floor;

        std::cout << "Enter your desired floor (0-" << NUM_FLOORS - 1 << "): ";
        std::cin >> desired_floor;
        
        if (current_floor < 0 || current_floor >= NUM_FLOORS || desired_floor < 0 || desired_floor >= NUM_FLOORS) {
            std::cout << "Invalid floor number. Please enter a number between 0 and " << NUM_FLOORS - 1 << std::endl;
            continue;
        }

        // 計算兩部電梯目前位置和目標位置的距離
        int distance1 = abs(elevator1.getCurrentFloor() - current_floor);
        int distance2 = abs(elevator2.getCurrentFloor() - current_floor);

        // 選擇最近的電梯
        Elevator& closest_elevator = (distance1 <= distance2) ? elevator1 : elevator2;
        std::cout << "Moving closest elevator to your curent floor..." << std::endl;
        closest_elevator.move(current_floor);

        std::cout << "Moving closest elevator to your desired floor..." << std::endl;
        closest_elevator.move(desired_floor);

        std::cout << "Transform to server mode? (y/n): " << std::endl;
        std::cin >> s1;
        while(s1 == "y") {
            while(true) {
                std::cout << "Which elevator you want to control? (1/2): " << std::endl;
                std::cin >> ctrl_elenum;
                if(ctrl_elenum < 1 || ctrl_elenum > 2) {
                    std::cout << "Invalid elevator number. Please enter a number: (1or2)"<< std::endl;
                    continue;
                }
                break;
            }
            while(true) {
                std::cout << "Which floor you want controled elevator to go? (0 and " << NUM_FLOORS - 1 << "):" << std::endl;
                std::cin >> ctrl_floornum;
                if (ctrl_floornum < 0 || ctrl_floornum >= NUM_FLOORS) {
                    std::cout << "Invalid floor number. Please enter a number between 0 and " << NUM_FLOORS - 1 << std::endl;
                    continue;
                }
                break;
            }
            Elevator& target_elevator = (ctrl_elenum == 1) ? elevator1 : elevator2;
            std::cout << "Moving target elevator to your target floor..." << std::endl;
            target_elevator.move(ctrl_floornum);
            
            std::cout << "Release server mode? (y/n): " << std::endl;
            std::cin >> s2;
            if(s2 == "y") {
                s1 = "n";
            }
        }
    }

    return 0;
}
