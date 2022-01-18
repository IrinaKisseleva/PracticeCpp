#include <iostream>
#include <ctime>

int Rand(const int MAX) {
    return rand() % MAX;
}

class Hero {
private:            
    int power = 0;
    int salary = 0;

public:

    Hero() {}

    Hero(int power, int salary) : power(power), salary(salary) {
    }

    int valuePower() {
       return power;
    }

    int valueSalary() {
        return salary;
    }

    void SetPower(int power) {
        if (power > 0)
            this->power = power;
    }

    void SetSalary(int salary) {
        if (salary > 0)
            this->salary = salary;
    }

    virtual void printActions() {}
};

class Warrior : public Hero {
public:
    Warrior(int power, int salary) {
        power = valuePower();
        salary = valueSalary();
    }

    void printActions() override {
        std::cout << "Сражаться";
    }
};

class Hunter : public Hero {
public:
    Hunter(int power, int salary) {
        power = valuePower();
        salary = valueSalary();
    }

    void printActions() override {
        std::cout << "Стрелять";
    }
};

class Castle {
public:
    static const int N = 10;
    const int MAX = 100 + 1;
    Hero* heroes[N];

    Castle(){
        selectHeroes();
    }

    void selectHeroes() {
        for (int i = 0; i < N; i++) {
            if (Rand(2) == 0) {
                heroes[i] = new Warrior(Rand(MAX), Rand(MAX));
            }
            else {
                heroes[i] = new Hunter(Rand(MAX), Rand(MAX));
            }
        }
    }

    ~Castle(){
        for (int i = 0; i < N; i++) {
            delete heroes[i];
        }
    }

    void selectionOfTheArmy(int min_power, int money) {
        bool paid = false;
        int count = 0;

        while (!paid) {
            int sum_salary = 0;

            for (int i = 0; i < N; i++) {
                if (heroes[i]->valuePower() < min_power) {
                    heroes[i]->SetSalary((100 * heroes[i]->valuePower()) / min_power);
                    heroes[i]->SetPower(min_power);
                }
                sum_salary += heroes[i]->valueSalary();
            }

            count += 1;

            if (money >= sum_salary) {
                paid = true;
                std::cout << "Команда успешно собрана";
            }
            else if (count > 3) {
                std::cout << "К сожалению, за такую сумму нельзя собрать команду выбранной силы";
                break;
            }
            else{
                for (int i = 0; i < N; i++) {
                    delete heroes[i];
                }
                selectHeroes();
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));

    int min_power = 45;
    int money = 1000;

    Castle castle = Castle();
    castle.selectionOfTheArmy(min_power, money);
    
    return 0;
}