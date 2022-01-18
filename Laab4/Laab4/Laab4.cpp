#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <cstdio>
#include <string>

class Cat {
public:
    std::string name;
    std::string breed;
    int friskiness;
    const int MAX = 50 + 1;

    void Sleep() {
        if (friskiness <= 50) {
            printf("Действие уложить спать выполнено успешно");
            friskiness += rand() % MAX;
        }
        else
            printf("Питомец сейчас не хочет спать, попробуйте позже");
        printf("\n\n");
    }

    void Play() {
        if (friskiness > 50) {
            printf("Действие играть выполнено успешно");
            friskiness -= rand() % MAX;
        }
        else
            printf("Питомец слишком устал, чтобы играть, попробуйте позже");
        printf("\n\n");
    }

};

class Dog {
public:
    std::string name;
    std::string breed;
    int friskiness;
    const int MAX = 50 + 1;

    void Sleep() {
        if (friskiness <= 50) {
            printf("Действие уложить спать выполнено успешно");
            friskiness += rand() % MAX;
        }
        else
            printf("Питомец сейчас не хочет спать, попробуйте позже");
        printf("\n\n");
    }

    void Play() {
        if (friskiness > 50) {
            printf("Действие играть выполнено успешно");
            friskiness -= rand() % MAX;
        }
        else
            printf("Питомец слишком устал, чтобы играть, попробуйте позже");
        printf("\n\n");
    }
};

int main(){

    int number = 0;
    srand(static_cast<unsigned int>(time(0)));//получение текущего времени, преоразованию к типу int
    setlocale(LC_ALL, "Russian"); 

    bool a = true;
    while (a) {
        printf("Введите количество животных:\n");
        scanf("%d", &number);
        if (number < 5 && number > 0) {
            a = false;
        }
    }

    std::string name_cats[5]{ "Сиренька", "Лучок", "Лидка", "Феникс", "Карелия"};
    std::string breed_cats[5]{"Азиатская", "Балийская", "Сомалийская", "Сиамская", "Манчкин"};
    int friskiness_cats[5]{99, 77, 88, 44, 43};

    std::string name_dogs[5]{"Мишка", "Ёжа", "Бэмби", "Горчица", "Чек"};
    std::string breed_dogs[5]{"Акита-Ину", "Алабай", "Басенджи", "Бигль", "Доберман"};
    int friskiness_dogs[5]{ 99, 77, 88, 44, 43 };

    Cat* cats = new Cat [number - 1];
    Dog* dogs = new Dog [number - 1];

    for(int i = 0; i < number - 1; i++) {
        cats[i].name = name_cats[rand() % 5];
        cats[i].breed = breed_cats[rand() % 5];
        cats[i].friskiness = friskiness_cats[rand() % 5];
    }

    for (int i = 0; i < number - 1; i++) {
        cats[i].name = name_dogs[rand() % 5];
        cats[i].breed = breed_dogs[rand() % 5];
        cats[i].friskiness = friskiness_dogs[rand() % 5];
    }

    /*cats[0].name = "Мурка";
    cats[0].breed = "Мейн-Кун";
    cats[0].friskiness = 67;

    cats[1].name = "Рейчел";
    cats[1].breed = "Сиамская";
    cats[1].friskiness = 34;

    dogs[0].name = "Джек";
    dogs[0].breed = "Овчарка";
    dogs[0].friskiness = 70;

    dogs[1].name = "Михалыч";
    dogs[1].breed = "Алабай";
    dogs[1].friskiness = 85; */

    int pet_type = 0;
    int pet_num = 0;
    int activity = 0;

    while (true)
    {
        printf("Выберите животное:\n1-кошка\n2-собака\n");
        scanf("%d", &pet_type);
        printf("Выберите питомца: ");
        scanf("%d", &pet_num);
        printf("Выберите действие:\n1-спать\n2-играть\n");
        scanf("%d", &activity);

        switch (pet_type) {
        case 1:
            if (pet_num > 0 && pet_num <= number) {
                switch (activity) {
                case 1:
                    cats[pet_num - 1].Sleep();
                    break;
                case 2:
                    cats[pet_num - 1].Play();
                    break;
                default:
                    printf("Прочитайте внимательно и введите нужное значение\n\n");
                    break;
                }
            }
            else {
                printf("У нас не так много животных\n\n");
            }
            break;
        case 2:
            if (pet_num > 0 && pet_num <= number) {
                switch (activity) {
                case 1:
                    dogs[pet_num - 1].Sleep();
                    break;
                case 2:
                    dogs[pet_num - 1].Play();
                    break;
                default:
                    printf("Прочитайте внимательно и введите нужное значение\n\n");
                    break;
                }
            }
            else {
                printf("У нас не так много животных\n\n");
            }
            break;
        default:
            printf("Прочитайте внимательно и введите нужное значение\n\n");
            break;
        }
    }
}