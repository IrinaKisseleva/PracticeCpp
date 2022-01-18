#include <iostream>
#include <ctime>
#include <vector>
#include <queue>

int randomInt(int max, int min) {
	return min + rand() % (max - min + 1);
}

double randomDouble() { // от 0 до 1
	return double(rand()) / RAND_MAX;
}

enum VisitorType {
	KID,
	ADULT,
	OLDMAN
};

struct VisitorsStatistics {
	int live_quantity;
	int appointment_quantity;
	int managed;
	int time;
};

struct ProbabilityRange {
	double start;
	double end;

	bool isInRange(double probability){
		if (probability >= start && probability <= end)
			return true;
		return false;
	}

};

class Visitor
{
protected:
	VisitorType visitor_type;

public:
	static double creation_probability; //вероятность появления
	int duration_visit; // длительность посещения
	double probability_preregistration; // вероятность предварительной записи

	VisitorType getVisitorType() {
		return visitor_type;
	}

};

class Kid : public Visitor
{
public:
	Kid() {
		this->visitor_type = VisitorType::KID;
		this->duration_visit = randomInt(5, 10);
		this->probability_preregistration = 0.01;
	}

};

class Adult : public Visitor
{
public:
	Adult() {
		this->visitor_type = VisitorType::ADULT;
		this->duration_visit = randomInt(2, 5);
		this->probability_preregistration = 0.7;
	}

};

class OldMan : public Visitor
{
public:
	OldMan() {
		this->visitor_type = VisitorType::OLDMAN;
		this->duration_visit = randomInt(7, 9);
		this->probability_preregistration = 0.5;
	}

};

class Queue
{
private:
	std::queue<Visitor*> visitors;
	
public:

	void addVisitor(Visitor* visitor) {
		visitors.push(visitor);
	}

	Visitor* popVisitor() {
		Visitor* visitor = visitors.front();
		visitors.pop();

		return visitor;
	}

	int getSize() {
		return visitors.size();
	}

	bool isEmpty() {
		return visitors.empty();
	}

};

class LiveQueue : public Queue
{

};

class AppointmentQueue : public Queue
{

};

class Division
{
private:
	int working_minutes = 480;
	int start_lunch = 240;
	int end_lunch = 300;
	int visitor_change_time = 0;
	int init_visitors_num = randomInt(1, 10);
	double kid_creation_probability = 0.05;
	double adult_creation_probability = 0.4;
	double oldman_creation_probability = 0.3;

	LiveQueue live_queue = LiveQueue();
	AppointmentQueue appointment_queue = AppointmentQueue();

	VisitorsStatistics kid_statistics = VisitorsStatistics();
	VisitorsStatistics adult_statistics = VisitorsStatistics();
	VisitorsStatistics oldman_statistics = VisitorsStatistics();

	ProbabilityRange kid_probability = { 0.0, kid_creation_probability };
	ProbabilityRange adult_probability = { kid_creation_probability, kid_creation_probability + adult_creation_probability };
	ProbabilityRange oldman_probability = { kid_creation_probability + adult_creation_probability ,  kid_creation_probability + adult_creation_probability + oldman_creation_probability };

public:
	Division(int working_minutes, int start_lunch, int end_lunch) {
		this->working_minutes = working_minutes;
		this->start_lunch = start_lunch;
		this->end_lunch = end_lunch;
	}

	Visitor* createVisitor() {
		double probability = randomDouble();

		if (kid_probability.isInRange(probability)) {
			return new Kid;
		}


		if (adult_probability.isInRange(probability)) {
			return new Adult;
		}


		if (oldman_probability.isInRange(probability)) {
			return new OldMan;
		}

		return nullptr;
	}

	VisitorsStatistics* getVisitorStatistics(Visitor* visitor) {
		switch (visitor->getVisitorType()) {
		case KID:
			return &kid_statistics;
		case ADULT:
			return &adult_statistics;
		case OLDMAN:
			return &oldman_statistics;
		default:
			return nullptr;
		}
	}

	void sortToQueue(Visitor* visitor, int time) {

		VisitorsStatistics* visitor_statistics = getVisitorStatistics(visitor);

		if (visitor && (time >= start_lunch) && (time < end_lunch)) {
			live_queue.addVisitor(visitor);
			visitor_statistics->live_quantity++;
		}
		else {
			double prereg_probability = randomDouble();
			if (prereg_probability < visitor->probability_preregistration) {
				visitor_statistics->appointment_quantity++;
				appointment_queue.addVisitor(visitor);

			}
			else {
				live_queue.addVisitor(visitor);
				visitor_statistics->live_quantity++;
			}
		}

	}

	int generateVisitors(int visitors_num, int time) {
		int visitors_generated = 0;

		for (int i = 0; i < visitors_num; i++) {
			Visitor* visitor = createVisitor();

			if (visitor) {
				sortToQueue(visitor, time);
				visitors_generated++;
			}
		}

		return visitors_generated;
	}

	Visitor* getVisitorFromQueue(){
		if (!appointment_queue.isEmpty()) {
			return appointment_queue.popVisitor();
		}
		else {
			return live_queue.popVisitor();
		}
	}

	void print(int total_visitors, int total_managed) {
		std::cout << "Общее количество посетителей:" << total_visitors << "\n" << "Успело пройти:" << total_managed << "\n"
			<< "Количество детей в живой очереди:" << kid_statistics.live_quantity << "\n" << "Количество детей в электронной очереди:" << kid_statistics.appointment_quantity << "\n"
			<< "Количество детей, которых приняли:" << kid_statistics.managed << "\n" << "Время потраченное на детей:" << kid_statistics.time << "\n"
			<< "Количество взрослых в живой очереди:" << adult_statistics.live_quantity << "\n" << "Количество взрослых в электронной очереди:" << adult_statistics.appointment_quantity << "\n"
			<< "Количество взрослых, которых приняли:" << adult_statistics.managed << "\n" << "Время потраченное на взрослых:" << adult_statistics.time << "\n"
			<< "Количество стариков в живой очереди:" << oldman_statistics.live_quantity << "\n" << "Количество стариков в электронной очереди:" << oldman_statistics.appointment_quantity << "\n"
			<< "Количество стариков, которых приняли:" << oldman_statistics.managed << "\n" << "Время потраченное на стариков:" << oldman_statistics.time << "\n";

	}

	void workDay() {
		int total_visitors = 0;
		int total_managed = 0;

		Visitor* current_visitor = nullptr;

		for (int time = 0; time < working_minutes; time ++) {
			if (time % 10 == 0) {
				total_visitors += generateVisitors(randomInt(0, 2), time);
			}

			if (time == visitor_change_time) {
				total_managed++;
				if (time != 0) {
					VisitorsStatistics* visitor_statistics = getVisitorStatistics(current_visitor);
					visitor_statistics->managed++;
					visitor_statistics->time += current_visitor->duration_visit;
				}

				current_visitor = getVisitorFromQueue();
				visitor_change_time = time + current_visitor->duration_visit;
			}
		}

		print(total_visitors, total_managed);

	}

	~Division(){
		//print(total_visitors, total_managed);
	}

};

int main() {

	srand(static_cast<unsigned int>(time(0)));
	setlocale(LC_ALL, "Russian");

	Division devision = Division(480, 240, 300);
	devision.workDay();

	return 0;
}