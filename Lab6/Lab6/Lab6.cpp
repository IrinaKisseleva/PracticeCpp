#include <iostream>
#include <cmath>
#include <ctime>


int randomInt(const int MAX, const int MIN) {
	return MIN + rand() % (MAX - MIN + 1);
}


class Target {
	double distance = 0.0;

public:
	Target() {}

	Target(double distance) : distance(distance) {}

	double setDistance(double distance) {
		this->distance = distance;
		return this->distance;
	}

	double getDistance() {
		return distance;
	}
};

class AWeapon
{
public:
	double caliber = 0.0; // калибр
	int cartridges = 0; // патроны на данный момент
	int burst_shots_num = 0; // Количество выстрелов очередью
	int cartridges_capacity = 0; //  количество патронов всего
	int shooting_modes_num = 0; //  количество режимов стрельбы
	double weight = 0.0; // вес
	double aiming_range_of_fire = 0.0; // прицельная дальность стрельбы
	double distance_dependece = 0.0; // коэфффициент падения вероятности попадания с ростом расстояния [1; 10]
	int modiifications_num = 0; //  количество устанавливаемых модификаций
	double shot_time = 0.0; // Время одного выстрела (с момента нажатия на курок до момента полного заряда нового патрона)

	virtual double reload(int cartridges) = 0;
	virtual void print() = 0;
	virtual int singleShoot(Target target, int shots_num) = 0;
	virtual int burstShoot(Target target, int shots_num) = 0;
	virtual int automaticShoot(Target target, int shots_num) = 0;
};

class Weapon : public AWeapon {

public:

	void print() {
		std::cout << "Калибр: " << caliber << " мм" << '\n'
			<< "Текущее количество патрон: " << cartridges << '\n'
			<< "Количество выcтрелов очередью: " << burst_shots_num << '\n'
			<< "Количество патрон: " << cartridges_capacity << '\n'
			<< "Количество режимов стрельбы: " << shooting_modes_num << '\n'
			<< "Вес: " << weight << " кг" << '\n'
			<< "Прицельная дальность стрельбы: " << aiming_range_of_fire << " м" << '\n'
			<< "Количество устанавливаемых модификаций: " << modiifications_num << '\n'
			<< "Коэффициент падения точности от расстояния: " << distance_dependece << '\n';
	}

	// одиночная стрельба
	int singleShoot(Target target, int shots_num) {

		double probability = getHitProbability(target.getDistance(), 1);
		int hit_count = 0; // количество попаданий

		for (int i = 0; i < shots_num; i++) {
			if (cartridges <= 0) break;
			if (double(rand()) / double(RAND_MAX) < probability) {
				hit_count++;
			}
			cartridges--;
		}

		return hit_count;
	}

	// стрельба очередями
	int burstShoot(Target target, int shots_num) {

		int hit_count = 0; // количество попаданий

		for (int i = 0; i < shots_num; i++) {
			if (cartridges <= 0) break;
			if (double(rand()) / double(RAND_MAX) < getHitProbability(target.getDistance(), (i % burst_shots_num + 1))) {
				hit_count++;
			}
			cartridges--;
		}

		return hit_count;
	}

	// автоматическая стрельба
	int automaticShoot(Target target, int shots_num) {

		int hit_count = 0; // количество попаданий

		for (int i = 0; i < shots_num; i++) {
			if (cartridges <= 0) break;
			if (double(rand()) / RAND_MAX < getHitProbability(target.getDistance(), i + 1)) {
				hit_count++;
			}
			cartridges--;
		}

		return hit_count;
	}

private:
	double getHitProbability(double target_distance, int shot_num) {
		double distance_probability; // вероятность попадания в зависимости от расстояния
		if (target_distance <= aiming_range_of_fire) {
			distance_probability = 1;
		}
		else {
			distance_probability = 1 / pow(exp((target_distance - aiming_range_of_fire)/1000), distance_dependece);
		}

		return distance_probability / shot_num;
	}

};

class WeaponWithRemovableMagazine : public Weapon {

public:

	double reload(int cartridges) {
		double time = 0.0;

		if (cartridges <= cartridges_capacity) {
			this->cartridges = cartridges;
			time = 1.0;
		}

		return time;
	}
};

class WeaponWithNonRemovableMagazine : public Weapon {

public:

	double reload(int cartridges) {
		double time = 0;
		if (cartridges <= cartridges_capacity) {
			this->cartridges += cartridges;
			time = cartridges;
		}

		return time;
	}
};

class Pistol : public WeaponWithRemovableMagazine {

public:
	int automaticShoot(Target target, int shots_num) {
		std::cout << "Данный вид оружия не поддерживает режим автоматический режим стрельбы";
		return 0;
	}

	Pistol(double caliber, int number_of_cartridges, int burst_shots_num, int shooting_modes_num, double weight, double aiming_range_of_fire, int modiifications_num) {
		this->caliber = caliber;
		this->cartridges_capacity = number_of_cartridges;
		this->burst_shots_num = burst_shots_num;
		this->shooting_modes_num = shooting_modes_num;
		this->weight = weight;
		this->aiming_range_of_fire = aiming_range_of_fire;
		this->modiifications_num = modiifications_num;
		this->distance_dependece = 4;
		this->shot_time = 0.5;
	}

};

class Rifle : public WeaponWithRemovableMagazine {

public:

	Rifle(double caliber, int number_of_cartridges, int burst_shots_num, int shooting_modes_num, double weight, double aiming_range_of_fire, int modiifications_num) {
		this->caliber = caliber;
		this->cartridges_capacity = number_of_cartridges;
		this->burst_shots_num = burst_shots_num;
		this->shooting_modes_num = shooting_modes_num;
		this->weight = weight;
		this->aiming_range_of_fire = aiming_range_of_fire;
		this->modiifications_num = modiifications_num;
		this->distance_dependece = 2;
		this->shot_time = 0.1;
	}

};

class Shotgun : public WeaponWithRemovableMagazine {

public:
	double accuracy = 0;

	int burstShoot(Target target, int shots_num) {
		std::cout << "Данный вид оружия не поддерживает режим стрельбы очередью";
		return 0;
	}

	int automaticShoot(Target target, int shots_num) {
		std::cout << "Данный вид оружия не поддерживает режим автоматический режим стрельбы";
		return 0;
	}

	Shotgun(double caliber, int number_of_cartridges, int shooting_modes_num, double weight, double aiming_range_of_fire, int modiifications_num, double accuracy) {
		this->caliber = caliber;
		this->cartridges_capacity = number_of_cartridges;
		this->shooting_modes_num = shooting_modes_num;
		this->weight = weight;
		this->aiming_range_of_fire = aiming_range_of_fire;
		this->modiifications_num = modiifications_num;
		this->accuracy = accuracy;
		this->distance_dependece = 10;
		this->shot_time = 0.8;
	}

};

class SingleShotRifle : public WeaponWithNonRemovableMagazine {

public:
	int burstShoot(Target target, int shots_num) {
		std::cout << "Данный вид оружия не поддерживает режим стрельбы очередью";
		return 0;
	}

	int automaticShoot(Target target, int shots_num) {
		std::cout << "Данный вид оружия не поддерживает режим автоматический режим стрельбы";
		return 0;
	}

	SingleShotRifle(double caliber, int number_of_cartridges, int shooting_modes_num, double weight, double aiming_range_of_fire, int modiifications_num) {
		this->caliber = caliber;
		this->cartridges_capacity = number_of_cartridges;
		this->shooting_modes_num = shooting_modes_num;
		this->weight = weight;
		this->aiming_range_of_fire = aiming_range_of_fire;
		this->modiifications_num = modiifications_num;
		this->distance_dependece = 2;
		this->shot_time = 1.0;
	}

};

class PumpShotgun : public WeaponWithNonRemovableMagazine {

public:
	double accuracy = 0;

	int burstShoot(Target target, int shots_num) {
		std::cout << "Данный вид оружия не поддерживает режим стрельбы очередью";
		return 0;
	}

	int automaticShoot(Target target, int shots_num) {
		std::cout << "Данный вид оружия не поддерживает режим автоматический режим стрельбы";
		return 0;
	}

	PumpShotgun(double caliber, int number_of_cartridges, int shooting_modes_num, double weight, double aiming_range_of_fire, int modiifications_num, double accuracy) {
		this->caliber = caliber;
		this->cartridges_capacity = number_of_cartridges;
		this->shooting_modes_num = shooting_modes_num;
		this->weight = weight;
		this->aiming_range_of_fire = aiming_range_of_fire;
		this->modiifications_num = modiifications_num;
		this->accuracy = accuracy;
		this->distance_dependece = 10;
		this->shot_time = 0.9;
	}
};

class ShootingRange {
private:
	static const int WEAPONS_NUM = 5;
	static const int TARGETS_NUM = 10;
	static const int MAX = 1000;
	static const int MIN = 1;

	AWeapon* weapons[WEAPONS_NUM];
	Target targets[TARGETS_NUM];

public:
	ShootingRange() {
		weapons[0] = new Pistol(0.45, 7, 2, 2, 0.7, 50, 2);
		weapons[1] = new Rifle(7.62, 30, 3, 3, 2.5, 500, 4);
		weapons[2] = new Shotgun(5.5, 14, 1, 5, 35, 3, 0.8);
		weapons[3] = new SingleShotRifle(7.62, 10, 1, 3, 600, 4);
		weapons[4] = new PumpShotgun(5.5, 7, 1, 4, 40, 3, 0.6);

		for (int i = 0; i < TARGETS_NUM; i++) {
			targets[i] = Target(randomInt(MAX, MIN));
		}
	}

	void simulate() {
		const int SHOTS_NUM = 100;
		int hit_count = 0;
		int shots_stop = 0, shots_remain = 0;
		double reload_time = 0.0, shooting_time = 0.0;

		for (int i = 0; i < WEAPONS_NUM; i++) {
			weapons[i]->print();
			std::cout << "\n";

			reload_time = 0.0;
			shooting_time = 0.0;
			shots_stop = SHOTS_NUM / weapons[i]->cartridges_capacity;
			shots_remain = SHOTS_NUM - shots_stop * weapons[i]->cartridges_capacity;

			for (int j = 0; j < TARGETS_NUM; j++) {
				hit_count = 0;

				std::cout << "Одиночная стрельба:" << '\n';
				for (int k = 0; k < shots_stop; k++) {
					reload_time += weapons[i]->reload(weapons[i]->cartridges_capacity);
					hit_count += weapons[i]->singleShoot(targets[j], weapons[i]->cartridges_capacity);
				}
				reload_time += weapons[i]->reload(shots_remain);
				hit_count += weapons[i]->singleShoot(targets[j], shots_remain);
				std::cout << "Точность по мишени " << targets[j].getDistance() << " м: " << double(hit_count) / SHOTS_NUM << "\n";

				if (weapons[i]->shooting_modes_num > 1) {
					hit_count = 0;
					std::cout << "Cтрельба очередью:" << '\n';
					for (int k = 0; k < shots_stop; k++) {
						reload_time += weapons[i]->reload(weapons[i]->cartridges_capacity);
						hit_count += weapons[i]->burstShoot(targets[j], weapons[i]->cartridges_capacity);
					}
					reload_time += weapons[i]->reload(shots_remain);
					hit_count += weapons[i]->burstShoot(targets[j], shots_remain);
					std::cout << "Точность по мишени " << targets[j].getDistance() << " м: " << double(hit_count) / SHOTS_NUM << "\n";
				}

				if (weapons[i]->shooting_modes_num > 2) {
					hit_count = 0;
					std::cout << "Автоматическая стрельба:" << '\n';
					for (int k = 0; k < shots_stop; k++) {
						reload_time += weapons[i]->reload(weapons[i]->cartridges_capacity);
						hit_count += weapons[i]->automaticShoot(targets[j], weapons[i]->cartridges_capacity);
					}
					reload_time += weapons[i]->reload(shots_remain);
					hit_count += weapons[i]->automaticShoot(targets[j], shots_remain);
					std::cout << "Точность по мишени " << targets[j].getDistance() << " м: " << double(hit_count) / SHOTS_NUM << "\n";
				}

				shooting_time += SHOTS_NUM / (SHOTS_NUM * weapons[i]->shot_time + reload_time);
			}
			std::cout << "Средняя скорострельность: " << (shooting_time * 60 / TARGETS_NUM) << "\n";
			std::cout << "\n\n";
		}
	}

	~ShootingRange() {
		for (int i = 0; i < WEAPONS_NUM; i++) {
			delete weapons[i];
		}
	}

};


int main() {

	srand(static_cast<unsigned int>(time(0)));
	setlocale(LC_ALL, "Russian");

	ShootingRange shooting_range = ShootingRange();
	shooting_range.simulate();

	return 0;
}
